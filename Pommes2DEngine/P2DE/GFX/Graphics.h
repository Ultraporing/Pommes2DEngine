//=================================================================================== 
// Copyright (c) 2015 Tobias Lenz.  All rights reserved.                                                                  
//=================================================================================== 

#pragma once
#include <d2d1_1.h>
#include <d2d1effects.h>
#include "..\Utilities\ComPtr.h"
#include "..\Game\BaseGame.h"

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
#pragma region Member_Variables
			HWND m_GameWindowHandle;
			RECT m_GameWindowSize;
			DWORD m_GameWindowStyle;
			DWORD m_GameWindowStyleEx;

			P2DE::UTILITIES::ComPtr<ID2D1Factory1> m_Factory;

			P2DE::UTILITIES::ComPtr<ID3D11DeviceContext> m_D3D11DeviceContext;
			P2DE::UTILITIES::ComPtr<ID3D11Device> m_D3D11Device;

			P2DE::UTILITIES::ComPtr<ID2D1Device> m_D2D1Device;
			P2DE::UTILITIES::ComPtr<ID2D1DeviceContext> m_D2D1DeviceContext;
			P2DE::UTILITIES::ComPtr<ID2D1Bitmap1> m_D2D1TargetBitmap;

			IDXGISwapChain1* m_SwapChain;
			D3D_FEATURE_LEVEL m_FeatureLevel;

			ID2D1SolidColorBrush* m_Brush;

			P2DE::GAME::BaseGame* m_CurrentGame;
#pragma endregion

			private:
#pragma region DirectX_Helper
			bool ResizeDirectX();
#pragma endregion

			public:		
			Graphics();
			~Graphics();

#pragma region DirectX_Init
			bool Init(HWND hWnd, DWORD dwStyle, DWORD dwStyleEx);
			bool Init(HWND hWnd, DWORD dwStyle, DWORD dwStyleEx, P2DE::GAME::BaseGame* game);
#pragma endregion

#pragma region Getter/Setter
			void SetCurrentGame(P2DE::GAME::BaseGame* game) { m_CurrentGame = game; }

			HWND GetGameWindowHandle() { return m_GameWindowHandle; }
			RECT GetGameWindowSize() { return m_GameWindowSize; }
			void SetGameWindowSize(const RECT& newWindowSize);
			void SetGameWindowPos(const POINT& newWindowPos);

			void SetTransform(D2D1_MATRIX_3X2_F& matrix);
			void SetTransform(D2D1_MATRIX_3X2_F* matrix);

			bool CanDraw() { return m_SwapChain ? true : false; }
#pragma endregion

#pragma region Begin/EndDraw/Clear
			void BeginDraw();
			void EndDraw();
			void ClearScreen(float r, float g, float b);
#pragma endregion
			
#pragma region Resources_From_File
			bool LoadBitmapFromFile(LPCWSTR file, ID2D1Bitmap** output);
#pragma endregion

#pragma region Bitmaps/Effects_Creation/Helpers
			bool CreateEffect(REFCLSID effectId, ID2D1Effect** effect);
			bool CreateBitmapTintEffect(ID2D1Effect** effect, ID2D1Image* img, float r, float g, float b, float a = 1.0f);
			bool CreateBitmapScaleEffect(ID2D1Effect** effect, ID2D1Image* img, float scaleX = 1.0f, float scaleY = 1.0f);
			void SetBitmapTintEffectColor(ID2D1Effect* effect, float r, float g, float b, float a = 1.0f);
			void SetBitmapScaleEffectScale(ID2D1Effect* effect, float scaleX = 1.0f, float scaleY = 1.0f);
#pragma endregion

#pragma region Matrix_Helper
			D2D1_MATRIX_5X4_F CreateColorMatrix(float r, float g, float b, float a = 1.0f);
#pragma endregion	

#pragma region Draw_Primitives
			void DrawCircle(float x, float y, float radius, float r, float g, float b, float a, float strokeWidth = 3.0f);
			void DrawCircle(float x, float y, float radius, const D2D1_COLOR_F& color, float strokeWidth = 3.0f);
			void DrawFilledCircle(float x, float y, float radius, float r, float g, float b, float a);
			void DrawFilledCircle(float x, float y, float radius, const D2D1_COLOR_F& color);
			void DrawRectangle(const D2D1_RECT_F& destinationRect, float r, float g, float b, float a, float strokeWidth = 3.0f);
			void DrawRectangle(const D2D1_RECT_F& destinationRect, const D2D1_COLOR_F& color, float strokeWidth = 3.0f);
			void DrawFilledRectangle(const D2D1_RECT_F& destinationRect, float r, float g, float b, float a);
			void DrawFilledRectangle(const D2D1_RECT_F& destinationRect, const D2D1_COLOR_F& color);
#pragma endregion

#pragma region Draw_Bitmaps
			void DrawBitmap(ID2D1Bitmap* bmp, float dstX, float dstY, float dstWidth, float dstHeight, float opacity, D2D1_BITMAP_INTERPOLATION_MODE interpolationMode);
			void DrawBitmap(ID2D1Bitmap* bmp, const D2D1_RECT_F& destinationRect, float opacity, D2D1_BITMAP_INTERPOLATION_MODE interpolationMode);
			void DrawBitmap(ID2D1Bitmap* bmp, float dstX, float dstY, float dstWidth, float dstHeight, float srcX, float srcY, float srcWidth, float srcHeight, float opacity, D2D1_BITMAP_INTERPOLATION_MODE interpolationMode);
			void DrawBitmap(ID2D1Bitmap* bmp, const D2D1_RECT_F& destinationRect, float srcX, float srcY, float srcWidth, float srcHeight, const float& opacity, D2D1_BITMAP_INTERPOLATION_MODE interpolationMode);
			void DrawBitmap(ID2D1Bitmap* bmp, const D2D1_RECT_F& destinationRect, const D2D1_RECT_F& sourceRect, const float& opacity, D2D1_BITMAP_INTERPOLATION_MODE interpolationMode);
			void DrawBitmap(ID2D1Bitmap* bmp, float dstX, float dstY, float dstWidth, float dstHeight, const D2D1_RECT_F& sourceRect, const float& opacity, D2D1_BITMAP_INTERPOLATION_MODE interpolationMode);
#pragma endregion

#pragma region Draw_Effects
			void DrawEffect(ID2D1Effect* effect, const D2D1_POINT_2F& destination, const D2D1_RECT_F& srcRect, D2D1_INTERPOLATION_MODE interpolationMode = D2D1_INTERPOLATION_MODE_LINEAR, D2D1_COMPOSITE_MODE compositeMode = D2D1_COMPOSITE_MODE_SOURCE_OVER);
			void DrawEffect(ID2D1Effect* effect, const D2D1_POINT_2F& destination, D2D1_INTERPOLATION_MODE interpolationMode = D2D1_INTERPOLATION_MODE_LINEAR, D2D1_COMPOSITE_MODE compositeMode = D2D1_COMPOSITE_MODE_SOURCE_OVER);
#pragma endregion
		};
	}
}