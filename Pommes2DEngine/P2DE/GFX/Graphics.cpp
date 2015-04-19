#include "Graphics.h"
#include <memory>
#include "..\Utilities\ComPtr.h"
#include "..\Utilities\ComHelpers.h"

using namespace P2DE::GFX;

Graphics::Graphics()
{
	m_Factory = NULL;
	m_RenderTarget = NULL;
	m_Brush = NULL;
	CoInitializeEx(NULL, COINIT_MULTITHREADED);
}

Graphics::~Graphics()
{
	if (m_Factory)
		m_Factory->Release();

	if (m_RenderTarget)
		m_RenderTarget->Release();

	if (m_Brush)
		m_Brush->Release();
}

bool Graphics::Init(HWND hWnd)
{
	HRESULT hr = D2D1CreateFactory(D2D1_FACTORY_TYPE_MULTI_THREADED, &m_Factory);
	if (hr != S_OK)	
		return false;

	RECT rect;
	GetClientRect(hWnd, &rect);

	hr = m_Factory->CreateHwndRenderTarget(D2D1::RenderTargetProperties(), D2D1::HwndRenderTargetProperties(hWnd, D2D1::SizeU(rect.right, rect.bottom)), &m_RenderTarget);
	if (hr != S_OK)
		return false;

	hr = m_RenderTarget->CreateSolidColorBrush(D2D1::ColorF(0, 0, 0, 0), &m_Brush);
	if (hr != S_OK)
		return false;

	return true;
}

bool Graphics::LoadBitmapFromFile(LPCWSTR file, ID2D1Bitmap** output)
{
	HRESULT hr;

	ComPtr<IWICBitmapDecoder> decoder;
	ComPtr<IWICBitmapFrameDecode> bitmapSource;
	ComPtr<IWICFormatConverter> converter;
	ComPtr<IWICImagingFactory> factory;

	hr = GetWICFactory(&factory);
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
	hr = m_RenderTarget->CreateBitmapFromWicBitmap(converter, nullptr, output);
	if (FAILED(hr))
		return false;

	return true;
}

void Graphics::ClearScreen(float r, float g, float b)
{
	m_RenderTarget->Clear(D2D1::ColorF(r, g, b));
}

void Graphics::DrawCircle(float x, float y, float radius, float r, float g, float b, float a)
{
	m_Brush->SetColor(D2D1::ColorF(r, g, b, a));

	m_RenderTarget->DrawEllipse(D2D1::Ellipse(D2D1::Point2F(x, y), radius, radius), m_Brush, 3.0f);
}

void Graphics::DrawBitmap(ID2D1Bitmap* bmp, float dstX, float dstY, float dstWidth, float dstHeight, float opacity, D2D1_BITMAP_INTERPOLATION_MODE interpolationMode)
{
	D2D1_SIZE_F bmpSize = bmp->GetSize();
	m_RenderTarget->DrawBitmap(bmp, D2D1::RectF(dstX, dstY, dstWidth, dstHeight), opacity, interpolationMode, D2D1::RectF(0, 0, bmpSize.width, bmpSize.height));
}

void Graphics::DrawBitmap(ID2D1Bitmap* bmp, const D2D1_RECT_F& destinationRect, float opacity, D2D1_BITMAP_INTERPOLATION_MODE interpolationMode)
{
	D2D1_SIZE_F bmpSize = bmp->GetSize();
	m_RenderTarget->DrawBitmap(bmp, destinationRect, opacity, interpolationMode, D2D1::RectF(0, 0, bmpSize.width, bmpSize.height));
}

void Graphics::DrawBitmap(ID2D1Bitmap* bmp, float dstX, float dstY, float dstWidth, float dstHeight, float srcX, float srcY, float srcWidth, float srcHeight, float opacity, D2D1_BITMAP_INTERPOLATION_MODE interpolationMode)
{
	m_RenderTarget->DrawBitmap(bmp, D2D1::RectF(dstX, dstY, dstWidth, dstHeight), opacity, interpolationMode, D2D1::RectF(srcX, srcY, srcWidth, srcHeight));
}

void Graphics::DrawBitmap(ID2D1Bitmap* bmp, const D2D1_RECT_F& destinationRect, float srcX, float srcY, float srcWidth, float srcHeight, const float& opacity, D2D1_BITMAP_INTERPOLATION_MODE interpolationMode)
{
	m_RenderTarget->DrawBitmap(bmp, destinationRect, opacity, interpolationMode, D2D1::RectF(srcX, srcY, srcWidth, srcHeight));
}

void Graphics::DrawBitmap(ID2D1Bitmap* bmp, const D2D1_RECT_F& destinationRect, const D2D1_RECT_F& sourceRect, const float& opacity, D2D1_BITMAP_INTERPOLATION_MODE interpolationMode)
{
	m_RenderTarget->DrawBitmap(bmp, destinationRect, opacity, interpolationMode, sourceRect);
}

void Graphics::DrawBitmap(ID2D1Bitmap* bmp, float dstX, float dstY, float dstWidth, float dstHeight, const D2D1_RECT_F& sourceRect, const float& opacity, D2D1_BITMAP_INTERPOLATION_MODE interpolationMode)
{
	m_RenderTarget->DrawBitmap(bmp, D2D1::RectF(dstX, dstY, dstWidth, dstHeight), opacity, interpolationMode, sourceRect);
}