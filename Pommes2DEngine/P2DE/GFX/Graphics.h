//=================================================================================== 
// Copyright (c) 2015 Tobias Lenz.  All rights reserved.                                                                  
//=================================================================================== 

#pragma once
#include <wrl\client.h>
using namespace Microsoft::WRL;
#include "..\Game\BaseGame.h"
#include "D3D11Common.h"
#include <d3d11.h>

#pragma comment (lib, "D3D11.lib")
#pragma comment (lib, "dxguid.lib")
#pragma comment (lib, "d3dcompiler.lib")

struct ID3D11DeviceContext;
struct ID3D11Device;
struct IDXGISwapChain1;
struct ID3D11ShaderResourceView;
struct ID3D11Resource;
struct ID3D11Texture2D;
struct ID3D11RenderTargetView;
struct ID3D11DepthStencilView;
struct ID3D11RasterizerState;
struct ID3D11PixelShader;
struct ID3D11VertexShader;
struct ID3D11Buffer;
struct ID3D11InputLayout;
struct ID3D10Blob;

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
			ComPtr<ID3D11DeviceContext> m_D3D11DeviceContext;
			/// <summary>	The Direct3D11 device. </summary>
			ComPtr<ID3D11Device> m_D3D11Device;

			#if defined(_DEBUG)
			ComPtr<ID3D11Debug> m_D3D11Debug;
			ComPtr<ID3D11InfoQueue> m_D3D11InfoQueue;
			#endif

			/// <summary>	The swap chain. </summary>
			ComPtr<IDXGISwapChain1> m_SwapChain;
				
			
			ComPtr<ID3D11DepthStencilView> m_DepthBuffer;
			ComPtr<ID3D11RenderTargetView> m_RenderTargetView;
			ComPtr<ID3D11RasterizerState> m_RasterizerState;

			/// <summary>	The current game. </summary>
			P2DE::GAME::BaseGame* m_CurrentGame;
			#pragma endregion

			private:
			ComPtr<ID3D11PixelShader> m_Ps;
			ComPtr<ID3D11VertexShader> m_Vs;
			ComPtr<ID3D11Buffer> m_VertexBuffer;
			ComPtr<ID3D11Buffer> m_IndexBuffer;
			ComPtr<ID3D11InputLayout> m_InputLayout;
			#pragma region DirectX_Helper
			/// <summary>	Reloads DirectX, for changing Window Size ect. </summary>
			///
			/// <remarks>	Tobias, 22.05.2015. </remarks>
			///
			/// <returns>	true if it succeeds, false if it fails. </returns>
			bool ReloadDirectX();
			
			#pragma endregion

			Graphics(Graphics const&) = delete;
			void operator=(Graphics const&) = delete;
			Graphics();

			public:		
			/// <summary>	Default constructor. </summary>
			///
			/// <remarks>	Tobias, 22.05.2015. </remarks>
			static Graphics& getInstance()
			{
				static Graphics    instance; // Guaranteed to be destroyed.
									  // Instantiated on first use.
				return instance;
			}
			
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

			void UnloadDirectX(bool isGameEnd);
			#pragma endregion

			void RenderDrawable();
			void LoadShaders();
			void UnloadShaders();
			void DisplayDx11DebugInfo();

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
		};
	}
}
#define P2DE_GFX P2DE::GFX::Graphics::getInstance()