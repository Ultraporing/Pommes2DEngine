//=================================================================================== 
// Copyright (c) 2015 Tobias Lenz.  All rights reserved.                                                                  
//=================================================================================== 

#pragma once
#include <d2d1.h>
#include <string>

// pommes 2d engine
namespace P2DE
{
	namespace GFX
	{
		class Graphics
		{
			private:
			ID2D1Factory* m_Factory;
			ID2D1HwndRenderTarget* m_RenderTarget;
			ID2D1SolidColorBrush* m_Brush;

			public:
			Graphics();
			~Graphics();

			bool Init(HWND hWnd);

			void BeginDraw() { m_RenderTarget->BeginDraw(); }
			void EndDraw() { m_RenderTarget->EndDraw(); }

			void SetTransform(D2D1_MATRIX_3X2_F& matrix) { m_RenderTarget->SetTransform(matrix); }
			void SetTransform(D2D1_MATRIX_3X2_F* matrix) { m_RenderTarget->SetTransform(matrix); }

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