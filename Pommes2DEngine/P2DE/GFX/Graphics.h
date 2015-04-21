//=================================================================================== 
// Copyright (c) 2015 Tobias Lenz.  All rights reserved.                                                                  
//=================================================================================== 

#pragma once
#include <d2d1_1.h>
#include "..\Utilities\ComPtr.h"

#pragma comment (lib, "D3D11.lib")
#pragma comment (lib, "d2d1.lib")

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

			void ClearScreen(float r, float g, float b);
			void DrawCircle(float x, float y, float radius, float r, float g, float b, float a);

			void DrawBitmap(ID2D1Bitmap* bmp, float dstX, float dstY, float dstWidth, float dstHeight, float opacity, D2D1_BITMAP_INTERPOLATION_MODE interpolationMode);
			void DrawBitmap(ID2D1Bitmap* bmp, const D2D1_RECT_F& destinationRect, float opacity, D2D1_BITMAP_INTERPOLATION_MODE interpolationMode);
			void DrawBitmap(ID2D1Bitmap* bmp, float dstX, float dstY, float dstWidth, float dstHeight, float srcX, float srcY, float srcWidth, float srcHeight, float opacity, D2D1_BITMAP_INTERPOLATION_MODE interpolationMode);
			void DrawBitmap(ID2D1Bitmap* bmp, const D2D1_RECT_F& destinationRect, float srcX, float srcY, float srcWidth, float srcHeight, const float& opacity, D2D1_BITMAP_INTERPOLATION_MODE interpolationMode);
			void DrawBitmap(ID2D1Bitmap* bmp, const D2D1_RECT_F& destinationRect, const D2D1_RECT_F& sourceRect, const float& opacity, D2D1_BITMAP_INTERPOLATION_MODE interpolationMode);
			void DrawBitmap(ID2D1Bitmap* bmp, float dstX, float dstY, float dstWidth, float dstHeight, const D2D1_RECT_F& sourceRect, const float& opacity, D2D1_BITMAP_INTERPOLATION_MODE interpolationMode);
		};
	}
}