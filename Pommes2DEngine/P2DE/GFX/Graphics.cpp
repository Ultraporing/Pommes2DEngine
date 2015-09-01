#include "Graphics.h"

#include <dxgi1_2.h>
#include <comdef.h>
#include <sstream>

#include "WICTextureLoader.h"

using namespace P2DE::GFX;

// This flag adds support for surfaces with a different color channel ordering than the API default.
// You need it for compatibility with Direct2D.
UINT creationFlags = D3D11_CREATE_DEVICE_BGRA_SUPPORT;

// This array defines the set of DirectX hardware feature levels this app  supports.
// The ordering is important and you should  preserve it.
// Don't forget to declare your app's minimum required feature level in its
// description.  All apps are assumed to support 9.1 unless otherwise stated.
D3D_FEATURE_LEVEL featureLevels[] =
{
	D3D_FEATURE_LEVEL_11_1,
	D3D_FEATURE_LEVEL_11_0,
	D3D_FEATURE_LEVEL_10_1,
	D3D_FEATURE_LEVEL_10_0,
	D3D_FEATURE_LEVEL_9_3,
	D3D_FEATURE_LEVEL_9_2,
	D3D_FEATURE_LEVEL_9_1
};

/// <summary>	The feature level. </summary>
D3D_FEATURE_LEVEL m_FeatureLevel;

Graphics::Graphics()
{
	CoInitializeEx(NULL, COINIT_MULTITHREADED);
}

Graphics::~Graphics()
{
	m_CurrentGame = NULL;
}

#pragma region DirectX_Init
bool Graphics::Init(HWND hWnd, DWORD dwStyle, DWORD dwStyleEx)
{
	RECT rect;
	GetClientRect(hWnd, &rect);

	m_GameWindowHandle = hWnd;
	m_GameWindowSize = rect;
	m_GameWindowStyle = dwStyle;
	m_GameWindowStyleEx = dwStyleEx;

	HRESULT hr = D3D11CreateDevice(nullptr, D3D_DRIVER_TYPE_HARDWARE, 0, creationFlags, featureLevels, ARRAYSIZE(featureLevels), D3D11_SDK_VERSION, &m_D3D11Device, &m_FeatureLevel, &m_D3D11DeviceContext);
	if (hr != S_OK)
	{
		std::wstringstream wss;
		wss << L"Failed to Init Graphics, D3D11CreateDevice. Error: " << _com_error(hr).ErrorMessage();
		MessageBox(NULL, wss.str().c_str(), L"Graphics Init Failed!", MB_OK);
		return false;
	}
		
	ComPtr<IDXGIDevice> dxgiDevice;
	hr = m_D3D11Device.As(&dxgiDevice);
	if (hr != S_OK)
	{
		std::wstringstream wss;
		wss << L"Failed to Init Graphics, m_D3D11Device.QueryInterface. Error: " << _com_error(hr).ErrorMessage();
		MessageBox(NULL, wss.str().c_str(), L"Graphics Init Failed!", MB_OK);
		return false;
	}

	// Allocate a descriptor.
	DXGI_SWAP_CHAIN_DESC1 swapChainDesc = { 0 };
	swapChainDesc.Width = 0;                           // use automatic sizing
	swapChainDesc.Height = 0;
	swapChainDesc.Format = DXGI_FORMAT_B8G8R8A8_UNORM; // this is the most common swapchain format
	swapChainDesc.Stereo = false;
	swapChainDesc.SampleDesc.Count = 1;                // don't use multi-sampling
	swapChainDesc.SampleDesc.Quality = 0;
	swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	swapChainDesc.BufferCount = 2;                     // use double buffering to enable flip
	swapChainDesc.Scaling = DXGI_SCALING_STRETCH;
	swapChainDesc.SwapEffect = DXGI_SWAP_EFFECT_FLIP_SEQUENTIAL; // all apps must use this SwapEffect
	swapChainDesc.Flags = 0;

	// Identify the physical adapter (GPU or card) this device is runs on.
	ComPtr<IDXGIAdapter> dxgiAdapter;
	hr = dxgiDevice->GetAdapter(&dxgiAdapter);
	if (hr != S_OK)
	{
		std::wstringstream wss;
		wss << L"Failed to Init Graphics, dxgiDevice->GetAdapter. Error: " << _com_error(hr).ErrorMessage();
		MessageBox(NULL, wss.str().c_str(), L"Graphics Init Failed!", MB_OK);
		return false;
	}
		

	// Get the factory object that created the DXGI device.
	ComPtr<IDXGIFactory2> dxgiFactory;
	hr = dxgiAdapter->GetParent(__uuidof(IDXGIFactory2), &dxgiFactory);
	if (hr != S_OK)
	{
		std::wstringstream wss;
		wss << L"Failed to Init Graphics, dxgiAdapter->GetParent. Error: " << _com_error(hr).ErrorMessage();
		MessageBox(NULL, wss.str().c_str(), L"Graphics Init Failed!", MB_OK);
		return false;
	}
		

	// Get the final swap chain for this window from the DXGI factory.
	hr = dxgiFactory->CreateSwapChainForHwnd(m_D3D11Device.Get(), hWnd, &swapChainDesc, nullptr, nullptr, &m_SwapChain);
	if (hr != S_OK)
	{
		std::wstringstream wss;
		wss << L"Failed to Init Graphics, CreateSwapChainForHwnd. Error: " << _com_error(hr).ErrorMessage();
		MessageBox(NULL, wss.str().c_str(), L"Graphics Init Failed!", MB_OK);
		return false;
	}
		
	// Get the backbuffer for this window which is be the final 3D render target.	
	hr = m_SwapChain->GetBuffer(0, IID_PPV_ARGS(&m_BackBuffer));
	if (hr != S_OK)
	{
		std::wstringstream wss;
		wss << L"Failed to Init Graphics, m_SwapChain->GetBuffer backBuffer. Error: " << _com_error(hr).ErrorMessage();
		MessageBox(NULL, wss.str().c_str(), L"Graphics Init Failed!", MB_OK);
		return false;
	}

	hr = m_D3D11Device->CreateRenderTargetView(m_BackBuffer.Get(), nullptr, &m_RenderTargetView);
	if (hr != S_OK)
	{
		std::wstringstream wss;
		wss << L"Failed to Init Graphics, m_D3D11Device->CreateRenderTargetView. Error: " << _com_error(hr).ErrorMessage();
		MessageBox(NULL, wss.str().c_str(), L"Graphics Init Failed!", MB_OK);
		return false;
	}

	return true;
}

bool Graphics::Init(HWND hWnd, DWORD dwStyle, DWORD dwStyleEx, P2DE::GAME::BaseGame* game)
{
	SetCurrentGame(game);

	return Init(hWnd, dwStyle, dwStyleEx);
}
#pragma endregion

#pragma region DirectX_Helper
bool Graphics::ReloadDirectX()
{
	m_CurrentGame->UnloadResources(false);

	if (m_BackBuffer)
		m_BackBuffer.~ComPtr();

	if (m_RenderTargetView)
		m_RenderTargetView.~ComPtr();

	if (m_SwapChain)
		m_SwapChain.~ComPtr();

	if (m_D3D11DeviceContext)
		m_D3D11DeviceContext.~ComPtr();

	if (m_D3D11Device)
		m_D3D11Device.~ComPtr();

	if (Init(m_GameWindowHandle, m_GameWindowStyle, m_GameWindowStyleEx) && m_CurrentGame->LoadResources())
		return true;

	return false;
}
#pragma endregion

#pragma region Getter/Setter
void Graphics::SetGameWindowSize(const RECT& newWindowSize)
{
	RECT finalWindowSize = newWindowSize;
	AdjustWindowRectEx(&finalWindowSize, m_GameWindowStyle, false, m_GameWindowStyleEx);
	SetWindowPos(m_GameWindowHandle, HWND_TOP, NULL, NULL, newWindowSize.right - newWindowSize.left, newWindowSize.bottom - newWindowSize.top, SWP_NOMOVE);
	GetClientRect(m_GameWindowHandle, &m_GameWindowSize);

	ReloadDirectX();
}

void Graphics::SetGameWindowPos(const POINT& newWindowPos)
{
	SetWindowPos(m_GameWindowHandle, HWND_TOP, newWindowPos.x, newWindowPos.y, NULL, NULL, SWP_NOSIZE);
	GetClientRect(m_GameWindowHandle, &m_GameWindowSize);
}
#pragma endregion

#pragma region Begin/EndDraw/Clear
void Graphics::BeginDraw()
{ 
	m_D3D11DeviceContext->OMSetRenderTargets(1, m_RenderTargetView.GetAddressOf(), nullptr);
}

void Graphics::EndDraw() 
{ 
	m_SwapChain->Present(1, 0); 
}
	
void Graphics::ClearScreen(float r, float g, float b)
{
	float color[4]{ r, g, b, 1.0f };
	m_D3D11DeviceContext->ClearRenderTargetView(m_RenderTargetView.Get(), color);
}
#pragma endregion

#pragma region Resources_From_File
bool Graphics::LoadBitmapFromFile(LPCWSTR file, ID3D11Resource** texture, ID3D11ShaderResourceView** srv)
{
	HRESULT hr = CreateWICTextureFromFile(m_D3D11Device.Get(), m_D3D11DeviceContext.Get(), file, texture, srv);
	if (FAILED(hr))
		return false;

	return true;
}
#pragma endregion

void Graphics::RenderDrawable(IDrawable drawable)
{
	
}