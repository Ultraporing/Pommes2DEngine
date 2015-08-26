//=================================================================================== 
// Copyright (c) 2015 Tobias Lenz.  All rights reserved.                                                                  
//=================================================================================== 

#ifndef GRAPHICS_H
	#define GRAPHICS_H
	#ifdef _WIN32
		//#include "..\Utilities\ComPtr.h"
		#include <wrl\client.h>
		using namespace Microsoft::WRL;
		#include "..\Game\BaseGame.h"

		#pragma comment (lib, "D3D11.lib")
		#pragma comment (lib, "dxguid.lib")

		struct ID3D11DeviceContext;
		struct ID3D11Device;
		struct IDXGISwapChain1;
		struct ID3D11ShaderResourceView;
		struct ID3D11Resource;
		struct ID3D11Texture2D;
		struct ID3D11RenderTargetView;

		struct P2DE_COLOR4 { float r, g, b, a; };
		struct P2DE_RECTF { float left, top, bottom, right; };
	#elif __APPLE__
		// TODO: Mac Headers
	#endif

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
				#ifdef _WIN32
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
					ComPtr<ID3D11DeviceContext> m_D3D11DeviceContext;
					/// <summary>	The Direct3D11 device. </summary>
					ComPtr<ID3D11Device> m_D3D11Device;

					/// <summary>	The swap chain. </summary>
					ComPtr<IDXGISwapChain1> m_SwapChain;
				

					ComPtr<ID3D11Texture2D> m_BackBuffer;

					ComPtr<ID3D11RenderTargetView> m_RenderTargetView;

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
					/// <param name="hWnd">			[in] Handle of the window. </param>
					/// <param name="dwStyle">  	[in] The style. </param>
					/// <param name="dwStyleEx">	[in] The style ex. </param>
					///
					/// <returns>	true if it succeeds, false if it fails. </returns>
					bool Init(HWND hWnd, DWORD dwStyle, DWORD dwStyleEx);
					/// <summary>	Initialises DirectX. </summary>
					///
					/// <remarks>	Tobias, 22.05.2015. </remarks>
					///
					/// <param name="hWnd">			[in] Handle of the window. </param>
					/// <param name="dwStyle">  	[in] The style. </param>
					/// <param name="dwStyleEx">	[in] The style ex. </param>
					/// <param name="game">			[in] If non-null, the game using this class. </param>
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
					/// <param name="r">	[in] Red (0-1). </param>
					/// <param name="g">	[in] Green (0-1). </param>
					/// <param name="b">	[in] Blue (0-1). </param>
					void ClearScreen(float r, float g, float b);
					#pragma endregion
			
					#pragma region Resources_From_File
					/// <summary>	Loads an image from file. PNG, JPG, BMP, GIF, TIF supported. </summary>
					///
					/// <remarks>	Tobias, 22.05.2015. </remarks>
					///
					/// <param name="file">  	[in] The Image filepath. </param>
					/// <param name="texture">	[out] If non-null, the output bitmap. </param>
					/// <param name="srv">	[out] If non-null, the shader resource view. </param>
					///
					/// <returns>	true if it succeeds, false if it fails. </returns>
					bool LoadBitmapFromFile(LPCWSTR file, ID3D11Resource** texture, ID3D11ShaderResourceView** srv);
					#pragma endregion

					#pragma region Bitmaps/Effects_Creation/Helpers
					#pragma endregion

					#pragma region Matrix_Helper
					#pragma endregion	

					#pragma region Draw_Primitives
					/// <summary>	Draw circle. </summary>
					///
					/// <remarks>	Tobias, 22.05.2015. </remarks>
					///
					/// <param name="x">		  	[in] The x coordinate. </param>
					/// <param name="y">		  	[in] The y coordinate. </param>
					/// <param name="radius">	  	[in] The radius. </param>
					/// <param name="r">		  	[in] Red color part. </param>
					/// <param name="g">		  	[in] Green color part. </param>
					/// <param name="b">		  	[in] Blue color part. </param>
					/// <param name="a">		  	[in] Alpha color part. </param>
					/// <param name="strokeWidth">	[in] Width of the stroke. </param>
					void DrawCircle(float x, float y, float radius, float r, float g, float b, float a, float strokeWidth = 3.0f);
					/// <summary>	Draw circle. </summary>
					///
					/// <remarks>	Tobias, 22.05.2015. </remarks>
					///
					/// <param name="x">		  	[in] The x coordinate. </param>
					/// <param name="y">		  	[in] The y coordinate. </param>
					/// <param name="radius">	  	[in] The radius. </param>
					/// <param name="color">	  	[in] The color. </param>
					/// <param name="strokeWidth">	[in] Width of the stroke. </param>
					void DrawCircle(float x, float y, float radius, const P2DE_COLOR4 color, float strokeWidth = 3.0f);

					/// <summary>	Draw filled circle. </summary>
					///
					/// <remarks>	Tobias, 22.05.2015. </remarks>
					///
					/// <param name="x">	 	[in] The x coordinate. </param>
					/// <param name="y">	 	[in] The y coordinate. </param>
					/// <param name="radius">	[in] The radius. </param>
					/// <param name="r">		[in] Red color part. </param>
					/// <param name="g">		[in] Green color part. </param>
					/// <param name="b">		[in] Blue color part. </param>
					/// <param name="a">		[in] Alpha color part. </param>
					void DrawFilledCircle(float x, float y, float radius, float r, float g, float b, float a);
					/// <summary>	Draw filled circle. </summary>
					///
					/// <remarks>	Tobias, 22.05.2015. </remarks>
					///
					/// <param name="x">	 	[in] The x coordinate. </param>
					/// <param name="y">	 	[in] The y coordinate. </param>
					/// <param name="radius">	[in] The radius. </param>
					/// <param name="color"> 	[in] The color. </param>
					void DrawFilledCircle(float x, float y, float radius, const P2DE_COLOR4 color);

					/// <summary>	Draw rectangle. </summary>
					///
					/// <remarks>	Tobias, 22.05.2015. </remarks>
					///
					/// <param name="destinationRect">	[in] Destination rectangle. </param>
					/// <param name="r">				[in] Red color part. </param>
					/// <param name="g">				[in] Green color part. </param>
					/// <param name="b">				[in] Blue color part. </param>
					/// <param name="a">				[in] Alpha color part. </param>
					/// <param name="strokeWidth">	  	[in] Width of the stroke. </param>
					void DrawRectangle(const P2DE_RECTF destinationRect, float r, float g, float b, float a, float strokeWidth = 3.0f);
					/// <summary>	Draw rectangle. </summary>
					///
					/// <remarks>	Tobias, 22.05.2015. </remarks>
					///
					/// <param name="destinationRect">	[in] Destination rectangle. </param>
					/// <param name="color">		  	[in] The color. </param>
					/// <param name="strokeWidth">	  	[in] Width of the stroke. </param>
					void DrawRectangle(const P2DE_RECTF destinationRect, const P2DE_COLOR4 color, float strokeWidth = 3.0f);

					/// <summary>	Draw filled rectangle. </summary>
					///
					/// <remarks>	Tobias, 22.05.2015. </remarks>
					///
					/// <param name="destinationRect">	[in] Destination rectangle. </param>
					/// <param name="r">				[in] Red color part. </param>
					/// <param name="g">				[in] Green color part. </param>
					/// <param name="b">				[in] Blue color part. </param>
					/// <param name="a">				[in] Alpha color part. </param>
					void DrawFilledRectangle(const P2DE_RECTF destinationRect, float r, float g, float b, float a);
					/// <summary>	Draw filled rectangle. </summary>
					///
					/// <remarks>	Tobias, 22.05.2015. </remarks>
					///
					/// <param name="destinationRect">	[in] Destination rectangle. </param>
					/// <param name="color">		  	[in] The color. </param>
					void DrawFilledRectangle(const P2DE_RECTF destinationRect, const P2DE_COLOR4 color);
					#pragma endregion

					#pragma region Draw_Bitmaps
					#pragma endregion

					#pragma region Draw_Effects
					#pragma endregion
				#elif __APPLE__
					// TODO: Mac Code
				#endif
			};
		}
	}
#endif