//=================================================================================== 
// Copyright (c) 2015 Tobias Lenz.  All rights reserved.                                                                  
//=================================================================================== 

#pragma once
#include <d2d1_1.h>
#include <d2d1effects.h>
#include "..\Utilities\ComPtr.h"

#pragma comment (lib, "D3D11.lib")
#pragma comment (lib, "d2d1.lib")
#pragma comment (lib, "dxguid.lib")

struct ID3D11DeviceContext;
struct ID3D11Device;
struct IDXGISwapChain1;

// pommes 2d engine
namespace P2DE
{
	namespace GFX
	{
		class Graphics
		{
			private:
			P2DE::UTILITIES::ComPtr<ID2D1Factory1> m_Factory;

			P2DE::UTILITIES::ComPtr<ID3D11DeviceContext> m_D3D11DeviceContext;
			P2DE::UTILITIES::ComPtr<ID3D11Device> m_D3D11Device;

			P2DE::UTILITIES::ComPtr<ID2D1Device> m_D2D1Device;
			P2DE::UTILITIES::ComPtr<ID2D1DeviceContext> m_D2D1DeviceContext;
			P2DE::UTILITIES::ComPtr<ID2D1Bitmap1> m_D2D1TargetBitmap;

			IDXGISwapChain1* m_SwapChain;
			D3D_FEATURE_LEVEL m_FeatureLevel;

			ID2D1SolidColorBrush* m_Brush;

			public:		
			Graphics();
			~Graphics();

			bool Init(HWND hWnd);

			void BeginDraw();
			void EndDraw();

			void SetTransform(D2D1_MATRIX_3X2_F& matrix);
			void SetTransform(D2D1_MATRIX_3X2_F* matrix);

			bool LoadBitmapFromFile(LPCWSTR file, ID2D1Bitmap** output);
			bool CreateEffect(REFCLSID effectId, ID2D1Effect** effect);
			bool CreateBitmapTintEffect(ID2D1Effect** effect, ID2D1Bitmap* bmp, float r, float g, float b, float a = 1.0f);
			void SetBitmapTintEffectColor(ID2D1Effect* effect, float r, float g, float b, float a = 1.0f);

			D2D1_MATRIX_5X4_F CreateColorMatrix(float r, float g, float b, float a = 1.0f);

			void ClearScreen(float r, float g, float b);
			void DrawCircle(float x, float y, float radius, float r, float g, float b, float a);

			void DrawBitmap(ID2D1Bitmap* bmp, float dstX, float dstY, float dstWidth, float dstHeight, float opacity, D2D1_BITMAP_INTERPOLATION_MODE interpolationMode);
			void DrawBitmap(ID2D1Bitmap* bmp, const D2D1_RECT_F& destinationRect, float opacity, D2D1_BITMAP_INTERPOLATION_MODE interpolationMode);
			void DrawBitmap(ID2D1Bitmap* bmp, float dstX, float dstY, float dstWidth, float dstHeight, float srcX, float srcY, float srcWidth, float srcHeight, float opacity, D2D1_BITMAP_INTERPOLATION_MODE interpolationMode);
			void DrawBitmap(ID2D1Bitmap* bmp, const D2D1_RECT_F& destinationRect, float srcX, float srcY, float srcWidth, float srcHeight, const float& opacity, D2D1_BITMAP_INTERPOLATION_MODE interpolationMode);
			void DrawBitmap(ID2D1Bitmap* bmp, const D2D1_RECT_F& destinationRect, const D2D1_RECT_F& sourceRect, const float& opacity, D2D1_BITMAP_INTERPOLATION_MODE interpolationMode);
			void DrawBitmap(ID2D1Bitmap* bmp, float dstX, float dstY, float dstWidth, float dstHeight, const D2D1_RECT_F& sourceRect, const float& opacity, D2D1_BITMAP_INTERPOLATION_MODE interpolationMode);

			void DrawEffect(ID2D1Effect* effect, const D2D1_POINT_2F& destination, const D2D1_RECT_F& srcRect, D2D1_INTERPOLATION_MODE interpolationMode, D2D1_COMPOSITE_MODE compositeMode);
		};
	}
}