#include "Graphics.h"

#ifdef _WIN32
	#include <memory>
	#include <d3d11.h>
	#include <dxgi1_2.h>
	#include <comdef.h>
	#include <sstream>
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

		HRESULT hr = D2D1CreateFactory(D2D1_FACTORY_TYPE_MULTI_THREADED, &m_Factory);
		if (hr != S_OK)
		{
			std::wstringstream wss;
			wss << L"Failed to Init Graphics, D2D1CreateFactory. Error: " << _com_error(hr).ErrorMessage();
			MessageBox(NULL, wss.str().c_str(), L"Graphics Init Failed!", MB_OK);
			return false;
		}
		

		hr = D3D11CreateDevice(nullptr, D3D_DRIVER_TYPE_HARDWARE, 0, creationFlags, featureLevels, ARRAYSIZE(featureLevels), D3D11_SDK_VERSION, &m_D3D11Device, &m_FeatureLevel, &m_D3D11DeviceContext);
		if (hr != S_OK)
		{
			std::wstringstream wss;
			wss << L"Failed to Init Graphics, D3D11CreateDevice. Error: " << _com_error(hr).ErrorMessage();
			MessageBox(NULL, wss.str().c_str(), L"Graphics Init Failed!", MB_OK);
			return false;
		}
		

		P2DE::UTILITIES::ComPtr<IDXGIDevice> dxgiDevice;
		hr = m_D3D11Device.QueryInterface<IDXGIDevice>(&dxgiDevice);
		if (hr != S_OK)
		{
			std::wstringstream wss;
			wss << L"Failed to Init Graphics, m_D3D11Device.QueryInterface. Error: " << _com_error(hr).ErrorMessage();
			MessageBox(NULL, wss.str().c_str(), L"Graphics Init Failed!", MB_OK);
			return false;
		}
		
		hr = m_Factory->CreateDevice(dxgiDevice, &m_D2D1Device);
		if (hr != S_OK)
		{
			std::wstringstream wss;
			wss << L"Failed to Init Graphics, CreateDevice. Error: " << _com_error(hr).ErrorMessage();
			MessageBox(NULL, wss.str().c_str(), L"Graphics Init Failed!", MB_OK);
			return false;
		}
		

		hr = m_D2D1Device->CreateDeviceContext(D2D1_DEVICE_CONTEXT_OPTIONS_ENABLE_MULTITHREADED_OPTIMIZATIONS, &m_D2D1DeviceContext);
		if (hr != S_OK)
		{
			std::wstringstream wss;
			wss << L"Failed to Init Graphics, CreateDevice. Error: " << _com_error(hr).ErrorMessage();
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
		swapChainDesc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD; // all apps must use this SwapEffect
		swapChainDesc.Flags = 0;

		// Identify the physical adapter (GPU or card) this device is runs on.
		P2DE::UTILITIES::ComPtr<IDXGIAdapter> dxgiAdapter;
		hr = dxgiDevice->GetAdapter(&dxgiAdapter);
		if (hr != S_OK)
		{
			std::wstringstream wss;
			wss << L"Failed to Init Graphics, dxgiDevice->GetAdapter. Error: " << _com_error(hr).ErrorMessage();
			MessageBox(NULL, wss.str().c_str(), L"Graphics Init Failed!", MB_OK);
			return false;
		}
		

		// Get the factory object that created the DXGI device.
		P2DE::UTILITIES::ComPtr<IDXGIFactory2> dxgiFactory;
		hr = dxgiAdapter->GetParent(IID_PPV_ARGS(&dxgiFactory));
		if (hr != S_OK)
		{
			std::wstringstream wss;
			wss << L"Failed to Init Graphics, dxgiAdapter->GetParent. Error: " << _com_error(hr).ErrorMessage();
			MessageBox(NULL, wss.str().c_str(), L"Graphics Init Failed!", MB_OK);
			return false;
		}
		

		// Get the final swap chain for this window from the DXGI factory.
		hr = dxgiFactory->CreateSwapChainForHwnd(m_D3D11Device, hWnd, &swapChainDesc, nullptr, nullptr, &m_SwapChain);
		if (hr != S_OK)
		{
			std::wstringstream wss;
			wss << L"Failed to Init Graphics, CreateSwapChainForHwnd. Error: " << _com_error(hr).ErrorMessage();
			MessageBox(NULL, wss.str().c_str(), L"Graphics Init Failed!", MB_OK);
			return false;
		}
		

		// Get the backbuffer for this window which is be the final 3D render target.
		P2DE::UTILITIES::ComPtr<ID3D11Texture2D> backBuffer;
		hr = m_SwapChain->GetBuffer(0, IID_PPV_ARGS(&backBuffer));
		if (hr != S_OK)
		{
			std::wstringstream wss;
			wss << L"Failed to Init Graphics, m_SwapChain->GetBuffer backBuffer. Error: " << _com_error(hr).ErrorMessage();
			MessageBox(NULL, wss.str().c_str(), L"Graphics Init Failed!", MB_OK);
			return false;
		}
		

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
		{
			std::wstringstream wss;
			wss << L"Failed to Init Graphics, m_SwapChain->GetBuffer dxgiBackBuffer. Error: " << _com_error(hr).ErrorMessage();
			MessageBox(NULL, wss.str().c_str(), L"Graphics Init Failed!", MB_OK);
			return false;
		}
		

		// Get a D2D surface from the DXGI back buffer to use as the D2D render target.
		hr = m_D2D1DeviceContext->CreateBitmapFromDxgiSurface(dxgiBackBuffer, &bitmapProperties, &m_D2D1TargetBitmap);
		if (hr != S_OK)
		{
			std::wstringstream wss;
			wss << L"Failed to Init Graphics, CreateBitmapFromDxgiSurface. Error: " << _com_error(hr).ErrorMessage();
			MessageBox(NULL, wss.str().c_str(), L"Graphics Init Failed!", MB_OK);
			return false;
		}
		

		// Now we can set the Direct2D render target.
		m_D2D1DeviceContext->SetTarget(m_D2D1TargetBitmap);
	
		m_D2D1DeviceContext->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::Black), &m_Brush);

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

		if (m_D2D1TargetBitmap)
			m_D2D1TargetBitmap.~ComPtr();

		if (m_SwapChain)
			m_SwapChain->Release();
		m_SwapChain = NULL;

		if (m_D2D1DeviceContext)
			m_D2D1DeviceContext.~ComPtr();

		if (m_Factory)
			m_Factory.~ComPtr();

		if (m_D3D11DeviceContext)
			m_D3D11DeviceContext.~ComPtr();

		if (m_D3D11Device)
			m_D3D11Device.~ComPtr();

		if (m_D2D1Device)
			m_D2D1Device.~ComPtr();

		m_Brush->Release();

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

	void Graphics::SetViewportTransform(D2D1_MATRIX_3X2_F& matrix)
	{
		m_D2D1DeviceContext->SetTransform(matrix);
	}

	void Graphics::SetViewportTransform(D2D1_MATRIX_3X2_F* matrix)
	{
		m_D2D1DeviceContext->SetTransform(matrix);
	}
	#pragma endregion

	#pragma region Begin/EndDraw/Clear
	void Graphics::BeginDraw()
	{ 
		m_D2D1DeviceContext->BeginDraw(); 
	}

	void Graphics::EndDraw() 
	{ 
		m_D2D1DeviceContext->EndDraw(); 
		m_SwapChain->Present(1, 0); 
	}
	
	void Graphics::ClearScreen(float r, float g, float b)
	{
		m_D2D1DeviceContext->Clear(D2D1::ColorF(r, g, b));
	}
	#pragma endregion

	#pragma region Resources_From_File
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
	#pragma endregion

	#pragma region Bitmaps/Effects_Creation/Helpers
	bool Graphics::CreateEffect(REFCLSID effectId, ID2D1Effect** effect)
	{
		HRESULT hr = m_D2D1DeviceContext->CreateEffect(effectId, effect);
		if (FAILED(hr))
			return false;

		return true;
	}

	bool Graphics::CreateBitmapTintEffect(ID2D1Effect** effect, ID2D1Image* img, float r, float g, float b, float a)
	{
		if (CreateEffect(CLSID_D2D1ColorMatrix, effect))
		{
			(*effect)->SetInput(0, img);
			(*effect)->SetValue(D2D1_COLORMATRIX_PROP_COLOR_MATRIX, CreateColorMatrix(r, g, b, a));

			return true;
		}
	
		return false;
	}

	bool Graphics::CreateBitmapScaleEffect(ID2D1Effect** effect, ID2D1Image* img, float scaleX, float scaleY)
	{
		if (CreateEffect(CLSID_D2D1Scale, effect))
		{
			(*effect)->SetInput(0, img);
			(*effect)->SetValue(D2D1_SCALE_PROP_SCALE, D2D1::Vector2F(scaleX, scaleY));

			return true;
		}

		return false;
	}

	bool Graphics::CreateBitmapScaleRotateEffect(ID2D1Effect** effect, ID2D1Image* img, float scaleX, float scaleY, float rotateDegrees, D2D1_POINT_2F rotateAround)
	{
		if (CreateEffect(CLSID_D2D12DAffineTransform, effect))
		{
			(*effect)->SetInput(0, img);

			D2D1::Matrix3x2F matrixRotation = D2D1::Matrix3x2F::Rotation(rotateDegrees, rotateAround);
			D2D1::Matrix3x2F matrixScale = D2D1::Matrix3x2F::Scale(scaleX, scaleY);
			D2D1::Matrix3x2F matrixFinal = matrixScale*matrixRotation;

			(*effect)->SetValue(D2D1_2DAFFINETRANSFORM_PROP_TRANSFORM_MATRIX, matrixFinal);

			return true;
		}

		return false;
	}

	void Graphics::SetBitmapTintEffectColor(ID2D1Effect* effect, float r, float g, float b, float a)
	{
		effect->SetValue(D2D1_COLORMATRIX_PROP_COLOR_MATRIX, CreateColorMatrix(r, g, b, a));
	}

	void Graphics::SetBitmapScaleEffectScale(ID2D1Effect* effect, float scaleX, float scaleY)
	{
		effect->SetValue(D2D1_SCALE_PROP_SCALE, D2D1::Vector2F(scaleX, scaleY));
	}

	void Graphics::SetBitmapScaleRotate(ID2D1Effect* effect, float scaleX, float scaleY, float rotateDegrees, D2D1_POINT_2F rotateAround)
	{
		D2D1::Matrix3x2F matrixRotation = D2D1::Matrix3x2F::Rotation(rotateDegrees, rotateAround);
		D2D1::Matrix3x2F matrixScale = D2D1::Matrix3x2F::Scale(scaleX, scaleY);
		D2D1::Matrix3x2F matrixFinal = matrixScale*matrixRotation;
	
		effect->SetValue(D2D1_2DAFFINETRANSFORM_PROP_TRANSFORM_MATRIX, matrixFinal);
	}

	void Graphics::CreateBitmapFromBitmapRegion(ID2D1Bitmap* bmp, D2D1_RECT_U region, ID2D1Bitmap** newBmp)
	{
		float dpiX, dpiY;
		bmp->GetDpi(&dpiX, &dpiY);

		m_D2D1DeviceContext->CreateBitmap(D2D1::SizeU(region.right - region.left, region.bottom - region.top), D2D1::BitmapProperties(bmp->GetPixelFormat(), dpiX, dpiY), newBmp);
	}
	#pragma endregion

	#pragma region Matrix_Helper
	D2D1_MATRIX_5X4_F Graphics::CreateColorMatrix(float r, float g, float b, float a)
	{
		return D2D1::Matrix5x4F(r, 0, 0, 0,
			0, g, 0, 0,
			0, 0, b, 0,
			0, 0, 0, a,
			0, 0, 0, 0);
	}
	#pragma endregion

	#pragma region Draw_Primitives
	void Graphics::DrawCircle(float x, float y, float radius, float r, float g, float b, float a, float strokeWidth)
	{
		m_Brush->SetColor(D2D1::ColorF(r, g, b, a));

		m_D2D1DeviceContext->DrawEllipse(D2D1::Ellipse(D2D1::Point2F(x, y), radius, radius), m_Brush, strokeWidth);
	}

	void Graphics::DrawCircle(float x, float y, float radius, const D2D1_COLOR_F& color, float strokeWidth)
	{
		m_Brush->SetColor(color);

		m_D2D1DeviceContext->DrawEllipse(D2D1::Ellipse(D2D1::Point2F(x, y), radius, radius), m_Brush, strokeWidth);
	}

	void Graphics::DrawFilledCircle(float x, float y, float radius, float r, float g, float b, float a)
	{
		m_Brush->SetColor(D2D1::ColorF(r, g, b, a));

		m_D2D1DeviceContext->FillEllipse(D2D1::Ellipse(D2D1::Point2F(x, y), radius, radius), m_Brush);
	}

	void Graphics::DrawFilledCircle(float x, float y, float radius, const D2D1_COLOR_F& color)
	{
		m_Brush->SetColor(color);

		m_D2D1DeviceContext->FillEllipse(D2D1::Ellipse(D2D1::Point2F(x, y), radius, radius), m_Brush);
	}

	void Graphics::DrawRectangle(const D2D1_RECT_F& destinationRect, float r, float g, float b, float a, float strokeWidth)
	{
		m_Brush->SetColor(D2D1::ColorF(r, g, b, a));

		m_D2D1DeviceContext->DrawRectangle(destinationRect, m_Brush, strokeWidth);
	}

	void Graphics::DrawRectangle(const D2D1_RECT_F& destinationRect, const D2D1_COLOR_F& color, float strokeWidth)
	{
		m_Brush->SetColor(color);

		m_D2D1DeviceContext->DrawRectangle(destinationRect, m_Brush, strokeWidth);
	}

	void Graphics::DrawFilledRectangle(const D2D1_RECT_F& destinationRect, float r, float g, float b, float a)
	{
		m_Brush->SetColor(D2D1::ColorF(r, g, b, a));

		m_D2D1DeviceContext->FillRectangle(destinationRect, m_Brush);
	}

	void Graphics::DrawFilledRectangle(const D2D1_RECT_F& destinationRect, const D2D1_COLOR_F& color)
	{
		m_Brush->SetColor(color);

		m_D2D1DeviceContext->FillRectangle(destinationRect, m_Brush);
	}
	#pragma endregion

	#pragma region Draw_Bitmaps
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
	#pragma endregion

	#pragma region Draw_Effects
	void Graphics::DrawEffect(ID2D1Effect* effect, const D2D1_POINT_2F& destination, const D2D1_RECT_F& srcRect, D2D1_INTERPOLATION_MODE interpolationMode, D2D1_COMPOSITE_MODE compositeMode)
	{
		m_D2D1DeviceContext->DrawImage(effect, destination, srcRect, interpolationMode, compositeMode);
	}

	void Graphics::DrawEffect(ID2D1Effect* effect, const D2D1_POINT_2F& destination, D2D1_INTERPOLATION_MODE interpolationMode, D2D1_COMPOSITE_MODE compositeMode)
	{
		m_D2D1DeviceContext->DrawImage(effect, destination, interpolationMode, compositeMode);
	}
	#pragma endregion
#elif __APPLE__
	// TODO: Mac Code
#endif