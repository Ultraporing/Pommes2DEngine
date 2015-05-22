//=================================================================================== 
// Copyright (c) 2015 Tobias Lenz.  All rights reserved.                                                                  
//=================================================================================== 

#pragma once
#include <Windows.h>
#include <array>

// Define missing vk keycodes ====
#pragma region Define missing vk keycodes
	#pragma region NUMBER KEYS
	#define VK_KEY_0 0x30
	#define VK_KEY_1 0x31
	#define VK_KEY_2 0x32
	#define VK_KEY_3 0x33
	#define VK_KEY_4 0x34
	#define VK_KEY_5 0x35
	#define VK_KEY_6 0x36
	#define VK_KEY_7 0x37
	#define VK_KEY_8 0x38
	#define VK_KEY_9 0x39
	#pragma endregion
	#pragma region LETTER KEYS
	#define VK_KEY_A 0x41
	#define VK_KEY_B 0x42
	#define VK_KEY_C 0x43
	#define VK_KEY_D 0x44
	#define VK_KEY_E 0x45
	#define VK_KEY_F 0x46
	#define VK_KEY_G 0x47
	#define VK_KEY_H 0x48
	#define VK_KEY_I 0x49
	#define VK_KEY_J 0x4A
	#define VK_KEY_K 0x4B
	#define VK_KEY_L 0x4C
	#define VK_KEY_M 0x4D
	#define VK_KEY_N 0x4E
	#define VK_KEY_O 0x4F
	#define VK_KEY_P 0x50
	#define VK_KEY_Q 0x51
	#define VK_KEY_R 0x52
	#define VK_KEY_S 0x53
	#define VK_KEY_T 0x54
	#define VK_KEY_U 0x55
	#define VK_KEY_V 0x56
	#define VK_KEY_W 0x57
	#define VK_KEY_X 0x58
	#define VK_KEY_Y 0x59
	#define VK_KEY_Z 0x5A
	#pragma endregion
#pragma endregion
// =====================

namespace P2DE
{
	namespace GFX
	{
		class Camera;
	}


	/// <summary>	Pommes2D Engine Input Related Namespace. </summary>
	///
	/// <remarks>	Tobias, 22.05.2015. </remarks>
	namespace INPUT
	{
		/// <summary>	Manager for inputs. Handles Mouse and Keyboard. </summary>
		///
		/// <remarks>	Tobias, 22.05.2015. </remarks>
		class InputManager
		{
			private:
			/// <summary>	The current keys pressed. </summary>
			std::array<bool, MAXBYTE> m_CurrentKeysPressed;

			public:
			/// <summary>	Query if 'VK_Keycode' is key down. </summary>
			///
			/// <remarks>	Tobias, 22.05.2015. </remarks>
			///
			/// <param name="VK_Keycode">	The vk keycode. </param>
			///
			/// <returns>	true if key down, false if not. </returns>
			bool IsKeyDown(const BYTE& VK_Keycode);

			/// <summary>	Query if 'VK_Keycode' is key up. </summary>
			///
			/// <remarks>	Tobias, 22.05.2015. </remarks>
			///
			/// <param name="VK_Keycode">	The vk keycode. </param>
			///
			/// <returns>	true if key up, false if not. </returns>
			bool IsKeyUp(const BYTE& VK_Keycode);

			/// <summary>	Query if 'VK_Keycode' is key pressed once. </summary>
			///
			/// <remarks>	Tobias, 22.05.2015. </remarks>
			///
			/// <param name="VK_Keycode">	The vk keycode. </param>
			///
			/// <returns>	true if key pressed, false if not. </returns>
			bool IsKeyPressed(const BYTE& VK_Keycode);

			/// <summary>	Gets screen mouse position. </summary>
			///
			/// <remarks>	Tobias, 22.05.2015. </remarks>
			///
			/// <param name="targetWindow">	Handle of the target window. </param>
			/// <param name="mousePos">	   	[in,out] If non-null, the mouse position. </param>
			///
			/// <returns>	true if it succeeds, false if it fails. </returns>
			bool GetScreenMousePos(HWND targetWindow, POINT* mousePos);

			/// <summary>	Gets game mouse position. </summary>
			///
			/// <remarks>	Tobias, 22.05.2015. </remarks>
			///
			/// <param name="targetWindow">	Handle of the target window. </param>
			/// <param name="mousePos">	   	[in,out] If non-null, the mouse position. </param>
			/// <param name="cam">		   	[in,out] If non-null, the camera. </param>
			///
			/// <returns>	true if it succeeds, false if it fails. </returns>
			bool GetGameMousePos(HWND targetWindow, POINT* mousePos, P2DE::GFX::Camera* cam);

			/// <summary>	Query if 'mouseButton' is mouse down. 0 = left, 1 = middle, 2 = right, else = left</summary>
			///
			/// <remarks>	Tobias, 22.05.2015. </remarks>
			///
			/// <param name="mouseButton">	The button. </param>
			///
			/// <returns>	true if mouse down, false if not. </returns>
			bool IsMouseDown(const BYTE& mouseButton);

			/// <summary>	Query if 'mouseButton' is mouse up. 0 = left, 1 = middle, 2 = right, else = left</summary>
			///
			/// <remarks>	Tobias, 22.05.2015. </remarks>
			///
			/// <param name="mouseButton">	The mouse button. </param>
			///
			/// <returns>	true if mouse up, false if not. </returns>
			bool IsMouseUp(const BYTE& mouseButton);

			/// <summary>	Query if 'mouseButton' is mouse clicked. 0 = left, 1 = middle, 2 = right, else = left</summary>
			///
			/// <remarks>	Tobias, 22.05.2015. </remarks>
			///
			/// <param name="mouseButton">	The mouse button. </param>
			///
			/// <returns>	true if mouse clicked, false if not. </returns>
			bool IsMouseClicked(const BYTE& mouseButton);
		};
	}
}