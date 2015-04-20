#include "Graphics.h"
#include <memory>
#include <d3d11.h>
#include <DXGI1_2.h>
#include "..\Utilities\ComHelpers.h"

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

Graphics::Graphics()
{
	m_Brush = NULL;
	m_SwapChain = NULL;
	CoInitializeEx(NULL, COINIT_MULTITHREADED);
}

Graphics::~Graphics()
{
	if (m_Brush)
		m_Brush->Release();

	if (m_SwapChain)
		m_SwapChain->Release();
}

bool Graphics::Init(HWND hWnd)
{
	RECT rect;
	GetClientRect(hWnd, &rect);

	HRESULT hr = D2D1CreateFactory(D2D1_FACTORY_TYPE_MULTI_THREADED, &m_Factory);
	if (hr != S_OK)
		return false;

	hr = D3D11CreateDevice(nullptr, D3D_DRIVER_TYPE_HARDWARE, 0, creationFlags, featureLevels, ARRAYSIZE(featureLevels), D3D11_SDK_VERSION, &m_D3D11Device, &m_FeatureLevel, &m_D3D11DeviceContext);
	if (hr != S_OK)
		return false;

	P2DE::UTILITIES::ComPtr<IDXGIDevice> dxgiDevice;
	hr = m_D3D11Device.QueryInterface<IDXGIDevice>(&dxgiDevice);
	if (hr != S_OK)
		return false;

	hr = m_Factory->CreateDevice(dxgiDevice, &m_D2D1Device);
	if (hr != S_OK)
		return false;

	hr = m_D2D1Device->CreateDeviceContext(D2D1_DEVICE_CONTEXT_OPTIONS_ENABLE_MULTITHREADED_OPTIMIZATIONS, &m_D2D1DeviceContext);
	if (hr != S_OK)
		return false;

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
	swapChainDesc.Scaling = DXGI_SCALING_NONE;
	swapChainDesc.SwapEffect = DXGI_SWAP_EFFECT_FLIP_SEQUENTIAL; // all apps must use this SwapEffect
	swapChainDesc.Flags = 0;

	// Identify the physical adapter (GPU or card) this device is runs on.
	P2DE::UTILITIES::ComPtr<IDXGIAdapter> dxgiAdapter;
	hr = dxgiDevice->GetAdapter(&dxgiAdapter);
	if (hr != S_OK)
		return false;

	// Get the factory object that created the DXGI device.
	P2DE::UTILITIES::ComPtr<IDXGIFactory2> dxgiFactory;
	hr = dxgiAdapter->GetParent(IID_PPV_ARGS(&dxgiFactory));
	if (hr != S_OK)
		return false;

	// Get the final swap chain for this window from the DXGI factory.
	hr = dxgiFactory->CreateSwapChainForHwnd(m_D3D11Device, hWnd, &swapChainDesc, nullptr, nullptr, &m_SwapChain);
	if (hr != S_OK)
		return false;

	// Get the backbuffer for this window which is be the final 3D render target.
	P2DE::UTILITIES::ComPtr<ID3D11Texture2D> backBuffer;
	hr = m_SwapChain->GetBuffer(0, IID_PPV_ARGS(&backBuffer));
	if (hr != S_OK)
		return false;

	// Now we set up the Direct2D render target bitmap linked to the swapchain. 
	// Whenever we render to this bitmap, it is directly rendered to the 
	// swap chain associated with the window.
	D2D1_BITMAP_PROPERTIES1 bitmapProperties =
		D2D1::BitmapProperties1(
		D2D1_BITMAP_OPTIONS_TARGET | D2D1_BITMAP_OPTIONS_CANNOT_DRAW,
		D2D1::PixelFormat(DXGI_FORMAT_B8G8R8A8_UNORM, D2D1_ALPHA_MODE_IGNORE));
	
	// Direct2D needs the dxgi version of the backbuffer surface pointer.
	P2DE::UTILITIES::ComPtr<IDXGISurface> dxgiBackBuffer;
	hr = m_SwapChain->GetBuffer(0, IID_PPV_ARGS(&dxgiBackBuffer));
	if (hr != S_OK)
		return false;

	// Get a D2D surface from the DXGI back buffer to use as the D2D render target.
	hr = m_D2D1DeviceContext->CreateBitmapFromDxgiSurface(dxgiBackBuffer, &bitmapProperties, &m_D2D1TargetBitmap);
	if (hr != S_OK)
		return false;

	// Now we can set the Direct2D render target.
	m_D2D1DeviceContext->SetTarget(m_D2D1TargetBitmap);

	m_D2D1DeviceContext->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::Black), &m_Brush);

	return true;
}

void Graphics::BeginDraw()
{ 
	m_D2D1DeviceContext->BeginDraw(); 
}

void Graphics::EndDraw() 
{ 
	m_D2D1DeviceContext->EndDraw(); 
	m_SwapChain->Present(1, 0); 
}
	
void Graphics::SetTransform(D2D1_MATRIX_3X2_F& matrix) 
{ 
	m_D2D1DeviceContext->SetTransform(matrix); 
}

void Graphics::SetTransform(D2D1_MATRIX_3X2_F* matrix) 
{ 
	m_D2D1DeviceContext->SetTransform(matrix); 
}

bool Graphics::LoadBitmapFromFile(LPCWSTR file, ID2D1Bitmap** output)
{
	HRESULT hr;

	P2DE::UTILITIES::ComPtr<IWICBitmapDecoder> decoder;
	P2DE::UTILITIES::ComPtr<IWICBitmapFrameDecode> bitmapSource;
	P2DE::UTILITIES::ComPtr<IWICFormatConverter> converter;
	P2DE::UTILITIES::ComPtr<IWICImagingFactory> factory;

	hr = P2DE::UTILITIES::GetWICFactory(&factory);
	if (FAILED(hr))
		return false;

	hr = factory->CreateDecoderFromFilename(file, nullptr, GENERIC_READ, WICDecodeMetadataCacheOnLoad, &decoder);
	if (FAILED(hr))
		return false;

	hr = decoder->GetFrame(0, &bitmapSource);
	if (FAILED(hr))
		return false;

	hr = factory->CreateFormatConverter(&converter);
	if (FAILED(hr))
		return false;

	hr = converter->Initialize(bitmapSource, GUID_WICPixelFormat32bppPBGRA, WICBitmapDitherTypeNone, nullptr, 0.f, WICBitmapPaletteTypeMedianCut);
	if (FAILED(hr))
		return false;

	// Create a Direct2D bitmap from the WIC bitmap.
	hr = m_D2D1DeviceContext->CreateBitmapFromWicBitmap(converter, nullptr, output);
	if (FAILED(hr))
		return false;

	return true;
}

void Graphics::ClearScreen(float r, float g, float b)
{
	m_D2D1DeviceContext->Clear(D2D1::ColorF(r, g, b));
}

void Graphics::DrawCircle(float x, float y, float radius, float r, float g, float b, float a)
{
	m_Brush->SetColor(D2D1::ColorF(r, g, b, a));

	m_D2D1DeviceContext->DrawEllipse(D2D1::Ellipse(D2D1::Point2F(x, y), radius, radius), m_Brush, 3.0f);
}

void Graphics::DrawBitmap(ID2D1Bitmap* bmp, float dstX, float dstY, float dstWidth, float dstHeight, float opacity, D2D1_BITMAP_INTERPOLATION_MODE interpolationMode)
{
	D2D1_SIZE_F bmpSize = bmp->GetSize();
	m_D2D1DeviceContext->DrawBitmap(bmp, D2D1::RectF(dstX, dstY, dstWidth, dstHeight), opacity, interpolationMode, D2D1::RectF(0, 0, bmpSize.width, bmpSize.height));
}

void Graphics::DrawBitmap(ID2D1Bitmap* bmp, const D2D1_RECT_F& destinationRect, float opacity, D2D1_BITMAP_INTERPOLATION_MODE interpolationMode)
{
	D2D1_SIZE_F bmpSize = bmp->GetSize();
	m_D2D1DeviceContext->DrawBitmap(bmp, destinationRect, opacity, interpolationMode, D2D1::RectF(0, 0, bmpSize.width, bmpSize.height));
}

void Graphics::DrawBitmap(ID2D1Bitmap* bmp, float dstX, float dstY, float dstWidth, float dstHeight, float srcX, float srcY, float srcWidth, float srcHeight, float opacity, D2D1_BITMAP_INTERPOLATION_MODE interpolationMode)
{
	m_D2D1DeviceContext->DrawBitmap(bmp, D2D1::RectF(dstX, dstY, dstWidth, dstHeight), opacity, interpolationMode, D2D1::RectF(srcX, srcY, srcWidth, srcHeight));
}

void Graphics::DrawBitmap(ID2D1Bitmap* bmp, const D2D1_RECT_F& destinationRect, float srcX, float srcY, float srcWidth, float srcHeight, const float& opacity, D2D1_BITMAP_INTERPOLATION_MODE interpolationMode)
{
	m_D2D1DeviceContext->DrawBitmap(bmp, destinationRect, opacity, interpolationMode, D2D1::RectF(srcX, srcY, srcWidth, srcHeight));
}

void Graphics::DrawBitmap(ID2D1Bitmap* bmp, const D2D1_RECT_F& destinationRect, const D2D1_RECT_F& sourceRect, const float& opacity, D2D1_BITMAP_INTERPOLATION_MODE interpolationMode)
{
	m_D2D1DeviceContext->DrawBitmap(bmp, destinationRect, opacity, interpolationMode, sourceRect);
}

void Graphics::DrawBitmap(ID2D1Bitmap* bmp, float dstX, float dstY, float dstWidth, float dstHeight, const D2D1_RECT_F& sourceRect, const float& opacity, D2D1_BITMAP_INTERPOLATION_MODE interpolationMode)
{
	m_D2D1DeviceContext->DrawBitmap(bmp, D2D1::RectF(dstX, dstY, dstWidth, dstHeight), opacity, interpolationMode, sourceRect);
}