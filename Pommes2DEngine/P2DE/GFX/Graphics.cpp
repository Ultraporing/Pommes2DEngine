#include "Graphics.h"

#include <dxgi1_2.h>
#include <comdef.h>
#include <sstream>
#include "../FileIO/FileIO.h"
#include "WICTextureLoader.h"
#include "Drawables\BaseDrawable.h"
#include "Drawables\Primitives\Triangle.h"

using namespace P2DE::GFX;
using namespace P2DE::GFX::DRAWABLES;
typedef unsigned int uint;

// This flag adds support for surfaces with a different color channel ordering than the API default.
// You need it for compatibility with Direct2D.

#if defined(_DEBUG)
// If the project is in a debug build, enable the debug layer.
UINT creationFlags = D3D11_CREATE_DEVICE_BGRA_SUPPORT | D3D11_CREATE_DEVICE_DEBUG;
#else
UINT creationFlags = D3D11_CREATE_DEVICE_BGRA_SUPPORT;
#endif

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

	//Create depth buffer
	D3D11_TEXTURE2D_DESC zBufferDescr;
	ZeroMemory(&zBufferDescr, sizeof(D3D11_TEXTURE2D_DESC));
	zBufferDescr.Width = rect.right;
	zBufferDescr.Height = rect.bottom;
	zBufferDescr.ArraySize = 1;
	zBufferDescr.MipLevels = 1;
	zBufferDescr.SampleDesc.Count = 1;
	zBufferDescr.Format = DXGI_FORMAT_D32_FLOAT;
	zBufferDescr.BindFlags = D3D11_BIND_DEPTH_STENCIL;
	ID3D11Texture2D *zBufferTexture;
	m_D3D11Device->CreateTexture2D(&zBufferDescr, 0, &zBufferTexture);

	D3D11_DEPTH_STENCIL_VIEW_DESC dsvd;
	ZeroMemory(&dsvd, sizeof(D3D11_DEPTH_STENCIL_VIEW_DESC));
	dsvd.Format = DXGI_FORMAT_D32_FLOAT;
	dsvd.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2DMS;
	m_D3D11Device->CreateDepthStencilView(zBufferTexture, &dsvd, m_DepthBuffer.GetAddressOf());
	zBufferTexture->Release();

	ComPtr<ID3D11Texture2D> m_BackBuffer;

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

	m_D3D11DeviceContext->OMSetRenderTargets(1, m_RenderTargetView.GetAddressOf(), m_DepthBuffer.Get());

	// Set the viewport
	D3D11_VIEWPORT viewport;
	ZeroMemory(&viewport, sizeof(D3D11_VIEWPORT));

	viewport.TopLeftX = 0;
	viewport.TopLeftY = 0;
	viewport.Width = float(m_GameWindowSize.right);
	viewport.Height = float(m_GameWindowSize.bottom);
	viewport.MinDepth = 0;
	viewport.MaxDepth = 1;
	m_D3D11DeviceContext->RSSetViewports(1, &viewport);

	#if defined(_DEBUG)
	if (SUCCEEDED(m_D3D11Device.As(&m_D3D11Debug)))
	{
		if (SUCCEEDED(m_D3D11Device.As(&m_D3D11InfoQueue)))
		{
			m_D3D11InfoQueue->SetBreakOnSeverity(D3D11_MESSAGE_SEVERITY_CORRUPTION, true);
			m_D3D11InfoQueue->SetBreakOnSeverity(D3D11_MESSAGE_SEVERITY_ERROR, true);

			D3D11_MESSAGE_ID hide[] =
			{
				D3D11_MESSAGE_ID_SETPRIVATEDATA_CHANGINGPARAMS,
			};
			D3D11_INFO_QUEUE_FILTER filter;
			memset(&filter, 0, sizeof(filter));
			filter.DenyList.NumIDs = _countof(hide);
			filter.DenyList.pIDList = hide;
			m_D3D11InfoQueue->AddStorageFilterEntries(&filter);
		}
	}
	#endif

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
	UnloadDirectX(false);

	if (Init(m_GameWindowHandle, m_GameWindowStyle, m_GameWindowStyleEx) && m_CurrentGame->LoadResources())
		return true;

	return false;
}

void Graphics::UnloadDirectX(bool isGameEnd)
{
	m_CurrentGame->UnloadResources(isGameEnd);

	if (m_RasterizerState)
		m_RasterizerState.~ComPtr();

	if (m_DepthBuffer)
		m_DepthBuffer.~ComPtr();

	if (m_RenderTargetView)
		m_RenderTargetView.~ComPtr();

	if (m_SwapChain)
		m_SwapChain.~ComPtr();

	if (m_D3D11DeviceContext)
		m_D3D11DeviceContext.~ComPtr();

	if (m_D3D11Device)
		m_D3D11Device.~ComPtr();

	#if defined(_DEBUG)
	if (isGameEnd)
		DisplayDx11DebugInfo();

	if (m_D3D11InfoQueue)
		m_D3D11InfoQueue.~ComPtr();

	if (m_D3D11Debug)
		m_D3D11Debug.~ComPtr();
	#endif
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
	m_D3D11DeviceContext->OMSetRenderTargets(1, m_RenderTargetView.GetAddressOf(), m_DepthBuffer.Get());
	
}

void Graphics::EndDraw() 
{ 
	m_SwapChain->Present(1, 0); 
}
	
void Graphics::ClearScreen(float r, float g, float b)
{
	float color[4]{ r, g, b, 1.0f };
	m_D3D11DeviceContext->ClearRenderTargetView(m_RenderTargetView.Get(), color);
	m_D3D11DeviceContext->ClearDepthStencilView(m_DepthBuffer.Get(), D3D11_CLEAR_DEPTH, 1.0f, 0);
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

void Graphics::RenderDrawable()
{
	UINT stride = sizeof(VERTEX);
	UINT offset = 0;
	m_D3D11DeviceContext->IASetVertexBuffers(0, 1, m_VertexBuffer.GetAddressOf(), &stride, &offset);
	m_D3D11DeviceContext->IASetIndexBuffer(m_IndexBuffer.Get(), DXGI_FORMAT_R32_UINT, 0);

	//m_D3D11DeviceContext->VSSetShader(m_Vs.Get(), nullptr, 0);
	//m_D3D11DeviceContext->PSSetShader(m_Ps.Get(), nullptr, 0);
	//m_D3D11DeviceContext->RSSetState(m_RasterizerState.Get());

	// select which primtive type we are using
	m_D3D11DeviceContext->IASetPrimitiveTopology(D3D10_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	

	// draw the vertex buffer to the back buffer
	m_D3D11DeviceContext->DrawIndexed(3, 0, 0);
}
/*
void Graphics::RenderDrawable(BaseDrawable * drawable)
{
}*/

void Graphics::AddShaderToShaderMap(P2DE::GFX::SHADER::EShaderID shaderID)
{
	if (m_ShaderMap.find(shaderID) != m_ShaderMap.end())
		return;

	switch (shaderID)
	{
		case P2DE::GFX::SHADER::EShaderID::BASE:
			m_ShaderMap[shaderID] = new P2DE::GFX::SHADER::Shader();
			m_ShaderMap[shaderID]->LoadShader();
			return;
		case P2DE::GFX::SHADER::EShaderID::COLOR:
			m_ShaderMap[shaderID] = new P2DE::GFX::SHADER::MyClass();
			m_ShaderMap[shaderID]->LoadShader();
			return;
	}
}

void Graphics::AddAllShaders()
{
	for (byte fooByte = P2DE::GFX::SHADER::EShaderID::BASE; fooByte != P2DE::GFX::SHADER::EShaderID::_LAST; fooByte++)
	{
		AddShaderToShaderMap((P2DE::GFX::SHADER::EShaderID)fooByte);
	}
}

void Graphics::RemoveAllShaders()
{
	for (std::map<byte, P2DE::GFX::SHADER::Shader*>::iterator it = m_ShaderMap.begin(); it != m_ShaderMap.end(); ++it)
	{
		it->second->UnloadShader();
		delete(it->second);
	}

	m_ShaderMap.clear();
}

void Graphics::LoadShaders()
{
	
	AddAllShaders();
	RemoveAllShaders();
	//ID3D11PixelShader* ps;
	//ID3D11VertexShader* vs;
	//ID3D11InputLayout* inp;
	//ID3D11Buffer* buf;
	//ComPtr<ID3DBlob> psBlob, vsBlob;

	//D3DReadFileToBlob(L"Assets\\Shaders\\PixelShader.cso", &psBlob);
	std::vector<char> binary = FILEIO::FileIO::ReadToByteArray("Assets\\Shaders\\PixelShader.cso");
	m_D3D11Device->CreatePixelShader(&binary[0], binary.size(), nullptr, &m_Ps);

	binary = FILEIO::FileIO::ReadToByteArray("Assets\\Shaders\\VertexShader.cso");
	//D3DReadFileToBlob(L"Assets\\Shaders\\VertexShader.cso", &vsBlob);
	m_D3D11Device->CreateVertexShader(&binary[0], binary.size(), nullptr, &m_Vs);
		
	m_D3D11DeviceContext->VSSetShader(m_Vs.Get(), NULL, NULL);
	m_D3D11DeviceContext->PSSetShader(m_Ps.Get(), NULL, NULL);

	D3D11_INPUT_ELEMENT_DESC positionLayout[] =
	{
		{ "POSITION", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0 },
	};

	HRESULT hr = m_D3D11Device->CreateInputLayout(positionLayout, 2, &binary[0], binary.size(), m_InputLayout.GetAddressOf());
	m_D3D11DeviceContext->IASetInputLayout(m_InputLayout.Get());

	VERTEX OurVertices[] =
	{
		{ 0.0f, 0.5f, 0.0f, COLOR4(1.0f, 0.0f, 0.0f, 1.0f) },
		{ 0.45f, -0.5, 0.0f, COLOR4(0.0f, 1.0f, 0.0f, 1.0f) },
		{ -0.45f, -0.5f, 0.0f, COLOR4(0.0f, 0.0f, 1.0f, 1.0f) }
	};

	D3D11_BUFFER_DESC bd;
	ZeroMemory(&bd, sizeof(bd));
	bd.Usage = D3D11_USAGE_DYNAMIC;
	bd.ByteWidth = sizeof(VERTEX) * 3;
	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	m_D3D11Device->CreateBuffer(&bd, NULL, m_VertexBuffer.GetAddressOf());

	D3D11_MAPPED_SUBRESOURCE ms;
	m_D3D11DeviceContext->Map(m_VertexBuffer.Get(), NULL, D3D11_MAP_WRITE_DISCARD, NULL, &ms);   // map the buffer
	memcpy(ms.pData, OurVertices, sizeof(OurVertices));                // copy the data
	m_D3D11DeviceContext->Unmap(m_VertexBuffer.Get(), NULL);                                     // unmap the buffer

	DWORD OurIndices[] =
	{
		0, 1, 2
	};

	bd.Usage = D3D11_USAGE_DYNAMIC;
	bd.ByteWidth = sizeof(DWORD) * 3;
	bd.BindFlags = D3D11_BIND_INDEX_BUFFER;
	bd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	bd.MiscFlags = 0;
	m_D3D11Device->CreateBuffer(&bd, NULL, m_IndexBuffer.GetAddressOf());

	m_D3D11DeviceContext->Map(m_IndexBuffer.Get(), NULL, D3D11_MAP_WRITE_DISCARD, NULL, &ms);
	memcpy(ms.pData, OurIndices, sizeof(OurIndices));
	m_D3D11DeviceContext->Unmap(m_IndexBuffer.Get(), NULL);
	
	D3D11_RASTERIZER_DESC rasterizerDesc;
	ZeroMemory(&rasterizerDesc, sizeof(D3D11_RASTERIZER_DESC));
    rasterizerDesc.FillMode = D3D11_FILL_SOLID;
    rasterizerDesc.CullMode = D3D11_CULL_BACK;
    rasterizerDesc.FrontCounterClockwise = false;
    rasterizerDesc.DepthClipEnable = true;

	
	m_D3D11Device->CreateRasterizerState(&rasterizerDesc, m_RasterizerState.GetAddressOf());
	m_D3D11DeviceContext->RSSetState(m_RasterizerState.Get());
}

void Graphics::UnloadShaders()
{
	m_InputLayout.Reset();
	m_InputLayout = nullptr;

	m_IndexBuffer.Reset();
	m_IndexBuffer = nullptr;

	m_VertexBuffer.Reset();
	m_VertexBuffer = nullptr;

	m_Ps.Reset();
	m_Ps = nullptr;

	m_Vs.Reset();
	m_Vs = nullptr;
}

void Graphics::DisplayDx11DebugInfo()
{
#if defined(_DEBUG)
	m_D3D11Debug->ReportLiveDeviceObjects(D3D11_RLDO_SUMMARY | D3D11_RLDO_DETAIL);
#endif
}
