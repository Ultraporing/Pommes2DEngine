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


/// <summary>	Pommes2D Engine Root Namespace. </summary>
///
/// <remarks>	Tobias, 22.05.2015. </remarks>
namespace P2DE
{
	/// <summary>	Pommes2D Engine Rendering Related Namespace. </summary>
	///
	/// <remarks>	Tobias, 22.05.2015. </remarks>
	namespace GFX
	{
		/// <summary>	Graphics Class, Rendering and Wrapping DirectX. As well as helper functions for Rendering. </summary>
		///
		/// <remarks>	Tobias, 22.05.2015. </remarks>
		class Graphics
		{
			private:
#pragma region Member_Variables
			/// <summary>	Handle of the game window. </summary>
			HWND m_GameWindowHandle;
			/// <summary>	Size of the game window. </summary>
			RECT m_GameWindowSize;
			/// <summary>	The game window style. </summary>
			DWORD m_GameWindowStyle;
			/// <summary>	The game window style ex. </summary>
			DWORD m_GameWindowStyleEx;


			/// <summary>	Context for the Direct3D11 device. </summary>
			P2DE::UTILITIES::ComPtr<ID3D11DeviceContext> m_D3D11DeviceContext;
			/// <summary>	The Direct3D11 device. </summary>
			P2DE::UTILITIES::ComPtr<ID3D11Device> m_D3D11Device;

			/// <summary>	The Direct2D1 factory. </summary>
			P2DE::UTILITIES::ComPtr<ID2D1Factory1> m_Factory;
			/// <summary>	The Direct2D1 device. </summary>
			P2DE::UTILITIES::ComPtr<ID2D1Device> m_D2D1Device;
			/// <summary>	Context for the Direct2D1 device. </summary>
			P2DE::UTILITIES::ComPtr<ID2D1DeviceContext> m_D2D1DeviceContext;
			/// <summary>	The Direct2D1 target bitmap. </summary>
			P2DE::UTILITIES::ComPtr<ID2D1Bitmap1> m_D2D1TargetBitmap;

			/// <summary>	The swap chain. </summary>
			IDXGISwapChain1* m_SwapChain;
			/// <summary>	The feature level. </summary>
			D3D_FEATURE_LEVEL m_FeatureLevel;

			/// <summary>	Reused Color brush. </summary>
			ID2D1SolidColorBrush* m_Brush;
			/// <summary>	The current game. </summary>
			P2DE::GAME::BaseGame* m_CurrentGame;
#pragma endregion

			private:
#pragma region DirectX_Helper
			/// <summary>	Reloads DirectX, for changing Window Size ect. </summary>
			///
			/// <remarks>	Tobias, 22.05.2015. </remarks>
			///
			/// <returns>	true if it succeeds, false if it fails. </returns>
			bool ReloadDirectX();
#pragma endregion

			public:		
			/// <summary>	Default constructor. </summary>
			///
			/// <remarks>	Tobias, 22.05.2015. </remarks>
			Graphics();
			/// <summary>	Destructor. </summary>
			///
			/// <remarks>	Tobias, 22.05.2015. </remarks>
			~Graphics();

#pragma region DirectX_Init
			/// <summary>	Initialises DirectX. </summary>
			///
			/// <remarks>	Tobias, 22.05.2015. </remarks>
			///
			/// <param name="hWnd">			Handle of the window. </param>
			/// <param name="dwStyle">  	The style. </param>
			/// <param name="dwStyleEx">	The style ex. </param>
			///
			/// <returns>	true if it succeeds, false if it fails. </returns>
			bool Init(HWND hWnd, DWORD dwStyle, DWORD dwStyleEx);
			/// <summary>	Initialises DirectX. </summary>
			///
			/// <remarks>	Tobias, 22.05.2015. </remarks>
			///
			/// <param name="hWnd">			Handle of the window. </param>
			/// <param name="dwStyle">  	The style. </param>
			/// <param name="dwStyleEx">	The style ex. </param>
			/// <param name="game">			[in,out] If non-null, the game. </param>
			///
			/// <returns>	true if it succeeds, false if it fails. </returns>
			bool Init(HWND hWnd, DWORD dwStyle, DWORD dwStyleEx, P2DE::GAME::BaseGame* game);
#pragma endregion

#pragma region Getter/Setter
			/// <summary>	Sets current game. </summary>
			///
			/// <remarks>	Tobias, 22.05.2015. </remarks>
			///
			/// <param name="game">	[in,out] If non-null, the game. </param>
			void SetCurrentGame(P2DE::GAME::BaseGame* game) { m_CurrentGame = game; }
			/// <summary>	Gets game window handle. </summary>
			///
			/// <remarks>	Tobias, 22.05.2015. </remarks>
			///
			/// <returns>	The game window handle. </returns>
			HWND GetGameWindowHandle() { return m_GameWindowHandle; }
			/// <summary>	Gets game window size. </summary>
			///
			/// <remarks>	Tobias, 22.05.2015. </remarks>
			///
			/// <returns>	The game window size. </returns>
			RECT GetGameWindowSize() { return m_GameWindowSize; }
			/// <summary>	Sets game window size. </summary>
			///
			/// <remarks>	Tobias, 22.05.2015. </remarks>
			///
			/// <param name="newWindowSize">	Size of the new window. </param>
			void SetGameWindowSize(const RECT& newWindowSize);
			/// <summary>	Sets game window position. </summary>
			///
			/// <remarks>	Tobias, 22.05.2015. </remarks>
			///
			/// <param name="newWindowPos">	The new window position. </param>
			void SetGameWindowPos(const POINT& newWindowPos);
			/// <summary>	Sets the Viewport transform. Used by the Camera to move it.</summary>
			///
			/// <remarks>	Tobias, 22.05.2015. </remarks>
			///
			/// <param name="matrix">	[in,out] The matrix. </param>
			void SetViewportTransform(D2D1_MATRIX_3X2_F& matrix);
			/// <summary>	Sets the Viewport transform. Used by the Camera to move it. </summary>
			///
			/// <remarks>	Tobias, 22.05.2015. </remarks>
			///
			/// <param name="matrix">	[in,out] If non-null, the matrix. </param>
			void SetViewportTransform(D2D1_MATRIX_3X2_F* matrix);
			/// <summary>	Determine if we can draw. </summary>
			///
			/// <remarks>	Tobias, 22.05.2015. </remarks>
			///
			/// <returns>	true if we can draw, false if not. </returns>
			bool CanDraw() { return m_SwapChain ? true : false; }
#pragma endregion

#pragma region Begin/EndDraw/Clear
			/// <summary>	Begins a draw. </summary>
			///
			/// <remarks>	Tobias, 22.05.2015. </remarks>
			void BeginDraw();
			/// <summary>	Ends a draw. </summary>
			///
			/// <remarks>	Tobias, 22.05.2015. </remarks>
			void EndDraw();
			/// <summary>	Clears the screen to Color. </summary>
			///
			/// <remarks>	Tobias, 22.05.2015. </remarks>
			///
			/// <param name="r">	The float to process. </param>
			/// <param name="g">	The float to process. </param>
			/// <param name="b">	The float to process. </param>
			void ClearScreen(float r, float g, float b);
#pragma endregion
			
#pragma region Resources_From_File
			/// <summary>	Loads an image from file. PNG, JPG, BMP supported. </summary>
			///
			/// <remarks>	Tobias, 22.05.2015. </remarks>
			///
			/// <param name="file">  	The file. </param>
			/// <param name="output">	[in,out] If non-null, the output. </param>
			///
			/// <returns>	true if it succeeds, false if it fails. </returns>
			bool LoadBitmapFromFile(LPCWSTR file, ID2D1Bitmap** output);
#pragma endregion

#pragma region Bitmaps/Effects_Creation/Helpers
			/// <summary>	Creates an effect. </summary>
			///
			/// <remarks>	Tobias, 22.05.2015. </remarks>
			///
			/// <param name="effectId">	Identifier for the effect. </param>
			/// <param name="effect">  	[in,out] If non-null, the effect. </param>
			///
			/// <returns>	true if it succeeds, false if it fails. </returns>
			bool CreateEffect(REFCLSID effectId, ID2D1Effect** effect);
			/// <summary>	Creates bitmap tint effect. </summary>
			///
			/// <remarks>	Tobias, 22.05.2015. </remarks>
			///
			/// <param name="effect">	[in,out] If non-null, the effect. </param>
			/// <param name="img">   	[in,out] If non-null, the image. </param>
			/// <param name="r">	 	The float to process. </param>
			/// <param name="g">	 	The float to process. </param>
			/// <param name="b">	 	The float to process. </param>
			/// <param name="a">	 	The float to process. </param>
			///
			/// <returns>	true if it succeeds, false if it fails. </returns>
			bool CreateBitmapTintEffect(ID2D1Effect** effect, ID2D1Image* img, float r, float g, float b, float a = 1.0f);
			/// <summary>	Creates bitmap scale effect. </summary>
			///
			/// <remarks>	Tobias, 22.05.2015. </remarks>
			///
			/// <param name="effect">	[in,out] If non-null, the effect. </param>
			/// <param name="img">   	[in,out] If non-null, the image. </param>
			/// <param name="scaleX">	The scale x coordinate. </param>
			/// <param name="scaleY">	The scale y coordinate. </param>
			///
			/// <returns>	true if it succeeds, false if it fails. </returns>
			bool CreateBitmapScaleEffect(ID2D1Effect** effect, ID2D1Image* img, float scaleX = 1.0f, float scaleY = 1.0f);
			/// <summary>	Sets bitmap TintEffect color. </summary>
			///
			/// <remarks>	Tobias, 22.05.2015. </remarks>
			///
			/// <param name="effect">	[in,out] If non-null, the effect. </param>
			/// <param name="r">	 	The float to process. </param>
			/// <param name="g">	 	The float to process. </param>
			/// <param name="b">	 	The float to process. </param>
			/// <param name="a">	 	The float to process. </param>
			void SetBitmapTintEffectColor(ID2D1Effect* effect, float r, float g, float b, float a = 1.0f);
			/// <summary>	Sets bitmap ScaleEffect scale. </summary>
			///
			/// <remarks>	Tobias, 22.05.2015. </remarks>
			///
			/// <param name="effect">	[in,out] If non-null, the effect. </param>
			/// <param name="scaleX">	The scale x coordinate. </param>
			/// <param name="scaleY">	The scale y coordinate. </param>
			void SetBitmapScaleEffectScale(ID2D1Effect* effect, float scaleX = 1.0f, float scaleY = 1.0f);
#pragma endregion

#pragma region Matrix_Helper
			/// <summary>	Creates color matrix. </summary>
			///
			/// <remarks>	Tobias, 22.05.2015. </remarks>
			///
			/// <param name="r">		  	Red color part. </param>
			/// <param name="g">		  	Green color part. </param>
			/// <param name="b">		  	Blue color part. </param>
			/// <param name="a">		  	Alpha color part. </param>
			///
			/// <returns>	The new color matrix. </returns>
			D2D1_MATRIX_5X4_F CreateColorMatrix(float r, float g, float b, float a = 1.0f);
#pragma endregion	

#pragma region Draw_Primitives
			/// <summary>	Draw circle. </summary>
			///
			/// <remarks>	Tobias, 22.05.2015. </remarks>
			///
			/// <param name="x">		  	The x coordinate. </param>
			/// <param name="y">		  	The y coordinate. </param>
			/// <param name="radius">	  	The radius. </param>
			/// <param name="r">		  	Red color part. </param>
			/// <param name="g">		  	Green color part. </param>
			/// <param name="b">		  	Blue color part. </param>
			/// <param name="a">		  	Alpha color part. </param>
			/// <param name="strokeWidth">	Width of the stroke. </param>
			void DrawCircle(float x, float y, float radius, float r, float g, float b, float a, float strokeWidth = 3.0f);
			/// <summary>	Draw circle. </summary>
			///
			/// <remarks>	Tobias, 22.05.2015. </remarks>
			///
			/// <param name="x">		  	The x coordinate. </param>
			/// <param name="y">		  	The y coordinate. </param>
			/// <param name="radius">	  	The radius. </param>
			/// <param name="color">	  	The color. </param>
			/// <param name="strokeWidth">	Width of the stroke. </param>
			void DrawCircle(float x, float y, float radius, const D2D1_COLOR_F& color, float strokeWidth = 3.0f);

			/// <summary>	Draw filled circle. </summary>
			///
			/// <remarks>	Tobias, 22.05.2015. </remarks>
			///
			/// <param name="x">	 	The x coordinate. </param>
			/// <param name="y">	 	The y coordinate. </param>
			/// <param name="radius">	The radius. </param>
			/// <param name="r">		Red color part. </param>
			/// <param name="g">		Green color part. </param>
			/// <param name="b">		Blue color part. </param>
			/// <param name="a">		Alpha color part. </param>
			void DrawFilledCircle(float x, float y, float radius, float r, float g, float b, float a);
			/// <summary>	Draw filled circle. </summary>
			///
			/// <remarks>	Tobias, 22.05.2015. </remarks>
			///
			/// <param name="x">	 	The x coordinate. </param>
			/// <param name="y">	 	The y coordinate. </param>
			/// <param name="radius">	The radius. </param>
			/// <param name="color"> 	The color. </param>
			void DrawFilledCircle(float x, float y, float radius, const D2D1_COLOR_F& color);

			/// <summary>	Draw rectangle. </summary>
			///
			/// <remarks>	Tobias, 22.05.2015. </remarks>
			///
			/// <param name="destinationRect">	Destination rectangle. </param>
			/// <param name="r">				Red color part. </param>
			/// <param name="g">				Green color part. </param>
			/// <param name="b">				Blue color part. </param>
			/// <param name="a">				Alpha color part. </param>
			/// <param name="strokeWidth">	  	Width of the stroke. </param>
			void DrawRectangle(const D2D1_RECT_F& destinationRect, float r, float g, float b, float a, float strokeWidth = 3.0f);
			/// <summary>	Draw rectangle. </summary>
			///
			/// <remarks>	Tobias, 22.05.2015. </remarks>
			///
			/// <param name="destinationRect">	Destination rectangle. </param>
			/// <param name="color">		  	The color. </param>
			/// <param name="strokeWidth">	  	Width of the stroke. </param>
			void DrawRectangle(const D2D1_RECT_F& destinationRect, const D2D1_COLOR_F& color, float strokeWidth = 3.0f);

			/// <summary>	Draw filled rectangle. </summary>
			///
			/// <remarks>	Tobias, 22.05.2015. </remarks>
			///
			/// <param name="destinationRect">	Destination rectangle. </param>
			/// <param name="r">				Red color part. </param>
			/// <param name="g">				Green color part. </param>
			/// <param name="b">				Blue color part. </param>
			/// <param name="a">				Alpha color part. </param>
			void DrawFilledRectangle(const D2D1_RECT_F& destinationRect, float r, float g, float b, float a);
			/// <summary>	Draw filled rectangle. </summary>
			///
			/// <remarks>	Tobias, 22.05.2015. </remarks>
			///
			/// <param name="destinationRect">	Destination rectangle. </param>
			/// <param name="color">		  	The color. </param>
			void DrawFilledRectangle(const D2D1_RECT_F& destinationRect, const D2D1_COLOR_F& color);
#pragma endregion

#pragma region Draw_Bitmaps
			/// <summary>	Draws the ID2D1Bitmap. </summary>
			///
			/// <remarks>	Tobias, 22.05.2015. </remarks>
			///
			/// <param name="bmp">					[in,out] If non-null, the bitmap. </param>
			/// <param name="dstX">					Destination x coordinate. </param>
			/// <param name="dstY">					Destination y coordinate. </param>
			/// <param name="dstWidth">				Width of the destination. </param>
			/// <param name="dstHeight">			Height of the destination. </param>
			/// <param name="opacity">				The opacity. </param>
			/// <param name="interpolationMode">	The interpolation mode. </param>
			void DrawBitmap(ID2D1Bitmap* bmp, float dstX, float dstY, float dstWidth, float dstHeight, float opacity, D2D1_BITMAP_INTERPOLATION_MODE interpolationMode);
			/// <summary>	Draws the ID2D1Bitmap. </summary>
			///
			/// <remarks>	Tobias, 22.05.2015. </remarks>
			///
			/// <param name="bmp">					[in,out] If non-null, the bitmap. </param>
			/// <param name="destinationRect">  	Destination rectangle. </param>
			/// <param name="opacity">				The opacity. </param>
			/// <param name="interpolationMode">	The interpolation mode. </param>
			void DrawBitmap(ID2D1Bitmap* bmp, const D2D1_RECT_F& destinationRect, float opacity, D2D1_BITMAP_INTERPOLATION_MODE interpolationMode);
			/// <summary>	Draws the ID2D1Bitmap. </summary>
			///
			/// <remarks>	Tobias, 22.05.2015. </remarks>
			///
			/// <param name="bmp">					[in,out] If non-null, the bitmap. </param>
			/// <param name="dstX">					Destination x coordinate. </param>
			/// <param name="dstY">					Destination y coordinate. </param>
			/// <param name="dstWidth">				Width of the destination. </param>
			/// <param name="dstHeight">			Height of the destination. </param>
			/// <param name="srcX">					Source x coordinate. </param>
			/// <param name="srcY">					Source y coordinate. </param>
			/// <param name="srcWidth">				Width of the source. </param>
			/// <param name="srcHeight">			Height of the source. </param>
			/// <param name="opacity">				The opacity. </param>
			/// <param name="interpolationMode">	The interpolation mode. </param>
			void DrawBitmap(ID2D1Bitmap* bmp, float dstX, float dstY, float dstWidth, float dstHeight, float srcX, float srcY, float srcWidth, float srcHeight, float opacity, D2D1_BITMAP_INTERPOLATION_MODE interpolationMode);
			/// <summary>	Draws the ID2D1Bitmap. </summary>
			///
			/// <remarks>	Tobias, 22.05.2015. </remarks>
			///
			/// <param name="bmp">					[in,out] If non-null, the bitmap. </param>
			/// <param name="destinationRect">  	Destination rectangle. </param>
			/// <param name="srcX">					Source x coordinate. </param>
			/// <param name="srcY">					Source y coordinate. </param>
			/// <param name="srcWidth">				Width of the source. </param>
			/// <param name="srcHeight">			Height of the source. </param>
			/// <param name="opacity">				The opacity. </param>
			/// <param name="interpolationMode">	The interpolation mode. </param>
			void DrawBitmap(ID2D1Bitmap* bmp, const D2D1_RECT_F& destinationRect, float srcX, float srcY, float srcWidth, float srcHeight, const float& opacity, D2D1_BITMAP_INTERPOLATION_MODE interpolationMode);
			/// <summary>	Draws the ID2D1Bitmap. </summary>
			///
			/// <remarks>	Tobias, 22.05.2015. </remarks>
			///
			/// <param name="bmp">					[in,out] If non-null, the bitmap. </param>
			/// <param name="destinationRect">  	Destination rectangle. </param>
			/// <param name="sourceRect">			Source rectangle. </param>
			/// <param name="opacity">				The opacity. </param>
			/// <param name="interpolationMode">	The interpolation mode. </param>
			void DrawBitmap(ID2D1Bitmap* bmp, const D2D1_RECT_F& destinationRect, const D2D1_RECT_F& sourceRect, const float& opacity, D2D1_BITMAP_INTERPOLATION_MODE interpolationMode);
			/// <summary>	Draws the ID2D1Bitmap. </summary>
			///
			/// <remarks>	Tobias, 22.05.2015. </remarks>
			///
			/// <param name="bmp">					[in,out] If non-null, the bitmap. </param>
			/// <param name="dstX">					Destination x coordinate. </param>
			/// <param name="dstY">					Destination y coordinate. </param>
			/// <param name="dstWidth">				Width of the destination. </param>
			/// <param name="dstHeight">			Height of the destination. </param>
			/// <param name="sourceRect">			Source rectangle. </param>
			/// <param name="opacity">				The opacity. </param>
			/// <param name="interpolationMode">	The interpolation mode. </param>
			void DrawBitmap(ID2D1Bitmap* bmp, float dstX, float dstY, float dstWidth, float dstHeight, const D2D1_RECT_F& sourceRect, const float& opacity, D2D1_BITMAP_INTERPOLATION_MODE interpolationMode);
#pragma endregion

#pragma region Draw_Effects
			/// <summary>	Draws the Effect. </summary>
			///
			/// <remarks>	Tobias, 22.05.2015. </remarks>
			///
			/// <param name="effect">				[in,out] If non-null, the effect. </param>
			/// <param name="destination">			Destination for the. </param>
			/// <param name="srcRect">				Source rectangle. </param>
			/// <param name="interpolationMode">	The interpolation mode. </param>
			/// <param name="compositeMode">		The composite mode. </param>
			void DrawEffect(ID2D1Effect* effect, const D2D1_POINT_2F& destination, const D2D1_RECT_F& srcRect, D2D1_INTERPOLATION_MODE interpolationMode = D2D1_INTERPOLATION_MODE_LINEAR, D2D1_COMPOSITE_MODE compositeMode = D2D1_COMPOSITE_MODE_SOURCE_OVER);
			/// <summary>	Draws the Effect. </summary>
			///
			/// <remarks>	Tobias, 22.05.2015. </remarks>
			///
			/// <param name="effect">				[in,out] If non-null, the effect. </param>
			/// <param name="destination">			Destination for the. </param>
			/// <param name="interpolationMode">	The interpolation mode. </param>
			/// <param name="compositeMode">		The composite mode. </param>
			void DrawEffect(ID2D1Effect* effect, const D2D1_POINT_2F& destination, D2D1_INTERPOLATION_MODE interpolationMode = D2D1_INTERPOLATION_MODE_LINEAR, D2D1_COMPOSITE_MODE compositeMode = D2D1_COMPOSITE_MODE_SOURCE_OVER);
#pragma endregion
		};
	}
}