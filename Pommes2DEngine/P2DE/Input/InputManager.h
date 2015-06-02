//=================================================================================== 
// Copyright (c) 2015 Tobias Lenz.  All rights reserved.                                                                  
//=================================================================================== 

#pragma once
#include <Windows.h>
#include <array>
#include "XboxController.h"

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
			static std::array<bool, MAXBYTE> m_CurrentKeysPressed;
			/// <summary>	The xbox controllers. </summary>
			static std::array<XboxController*, 4> m_XboxControllers;
			/// <summary>	State of the mousewheel. 1 = mousewheel up, 0 = none, -1 = mousewheel down</summary>
			static int m_MousewheelState;

			public:
			/// <summary>	Query if 'VK_Keycode' is key down. </summary>
			///
			/// <remarks>	Tobias, 22.05.2015. </remarks>
			///
			/// <param name="VK_Keycode">	The vk keycode. </param>
			///
			/// <returns>	true if key down, false if not. </returns>
			static bool IsKeyDown(const BYTE& VK_Keycode);
			/// <summary>	Query if 'VK_Keycode' is key up. </summary>
			///
			/// <remarks>	Tobias, 22.05.2015. </remarks>
			///
			/// <param name="VK_Keycode">	The vk keycode. </param>
			///
			/// <returns>	true if key up, false if not. </returns>
			static bool IsKeyUp(const BYTE& VK_Keycode);
			/// <summary>	Query if 'VK_Keycode' is key pressed once. </summary>
			///
			/// <remarks>	Tobias, 22.05.2015. </remarks>
			///
			/// <param name="VK_Keycode">	The vk keycode. </param>
			///
			/// <returns>	true if key pressed, false if not. </returns>
			static bool IsKeyPressed(const BYTE& VK_Keycode);

			/// <summary>	Gets screen mouse position. </summary>
			///
			/// <remarks>	Tobias, 22.05.2015. </remarks>
			///
			/// <param name="targetWindow">	Handle of the target window. </param>
			/// <param name="mousePos">	   	[in,out] If non-null, the mouse position. </param>
			///
			/// <returns>	true if it succeeds, false if it fails. </returns>
			static bool GetScreenMousePos(HWND targetWindow, POINT* mousePos);
			/// <summary>	Gets game mouse position. </summary>
			///
			/// <remarks>	Tobias, 22.05.2015. </remarks>
			///
			/// <param name="targetWindow">	Handle of the target window. </param>
			/// <param name="mousePos">	   	[in,out] If non-null, the mouse position. </param>
			/// <param name="cam">		   	[in,out] If non-null, the camera. </param>
			///
			/// <returns>	true if it succeeds, false if it fails. </returns>
			static bool GetGameMousePos(HWND targetWindow, POINT* mousePos, P2DE::GFX::Camera* cam);

			/// <summary>	Sets mousewheel state. Prerequesite for using MousewheelScroll Methods. Use this Method in your 'WindowProc' for the Message 'WM_MOUSEWHEEL'.</summary>
			///
			/// <remarks>	Tobias, 02.06.2015. </remarks>
			///
			/// <param name="wParam">	The wParam field of the message. </param>
			static void SetMousewheelState(WPARAM wParam);
			/// <summary>	Query if the mousewheel was scrolled up. </summary>
			///
			/// <remarks>	Tobias, 02.06.2015. </remarks>
			///
			/// <returns>	true if mousewheel scroll up, false if not. </returns>
			static bool IsMousewheelScrollUp();
			/// <summary>	Query if the mousewheel was scrolled down. </summary>
			///
			/// <remarks>	Tobias, 02.06.2015. </remarks>
			///
			/// <returns>	true if mousewheel scroll up, false if not. </returns>
			static bool IsMousewheelScrollDown();
			/// <summary>	Gets mousewheel state. -1 = mousewheel scrolled down, 0 = mousewheel not scrolled, 1 = mousewheel scrolled up.</summary>
			///
			/// <remarks>	Tobias, 02.06.2015. </remarks>
			///
			/// <returns>	The mousewheel state. </returns>
			static int GetMousewheelState();
			/// <summary>	Resets the mousewheel state. This has to be called before the next Update to reset the Mousewheel scroll state. </summary>
			///
			/// <remarks>	Tobias, 02.06.2015. </remarks>
			static void ResetMousewheelState();

			/// <summary>	Query if 'mouseButton' is mouse down. 0 = left, 1 = middle, 2 = right, else = left</summary>
			///
			/// <remarks>	Tobias, 22.05.2015. </remarks>
			///
			/// <param name="mouseButton">	The button. </param>
			///
			/// <returns>	true if mouse down, false if not. </returns>
			static bool IsMouseDown(const BYTE& mouseButton);
			/// <summary>	Query if 'mouseButton' is mouse up. 0 = left, 1 = middle, 2 = right, else = left</summary>
			///
			/// <remarks>	Tobias, 22.05.2015. </remarks>
			///
			/// <param name="mouseButton">	The mouse button. </param>
			///
			/// <returns>	true if mouse up, false if not. </returns>
			static bool IsMouseUp(const BYTE& mouseButton);
			/// <summary>	Query if 'mouseButton' is mouse clicked. 0 = left, 1 = middle, 2 = right, else = left</summary>
			///
			/// <remarks>	Tobias, 22.05.2015. </remarks>
			///
			/// <param name="mouseButton">	The mouse button. </param>
			///
			/// <returns>	true if mouse clicked, false if not. </returns>
			static bool IsMouseClicked(const BYTE& mouseButton);

			/// <summary>	Initialises the xbox controllers. </summary>
			///
			/// <remarks>	Tobias, 03.06.2015. </remarks>
			static void InitXboxControllers();
			/// <summary>	Deinitialize xbox controllers. </summary>
			///
			/// <remarks>	Tobias, 03.06.2015. </remarks>
			static void DeinitializeXboxControllers();
			/// <summary>	Query if 'players' controller is connected. </summary>
			///
			/// <remarks>	Tobias, 03.06.2015. </remarks>
			///
			/// <param name="player">	The player. 1-4 </param>
			///
			/// <returns>	true if controller connected, false if not. </returns>
			static bool IsControllerConnected(const BYTE& player);
			/// <summary>	Query if on 'players' controller button pressed. </summary>
			///
			/// <remarks>	Tobias, 03.06.2015. </remarks>
			///
			/// <param name="player">			  	The player. 1-4 </param>
			/// <param name="xInputGamepadButton">	The input gamepad button. </param>
			///
			/// <returns>	true if controller button pressed, false if not. </returns>
			static bool IsControllerButtonPressed(const BYTE& player, const WORD& xInputGamepadButton);
			/// <summary>	Gets 'players' controller. </summary>
			///
			/// <remarks>	Tobias, 03.06.2015. </remarks>
			///
			/// <param name="player">	The player. 1-4 </param>
			///
			/// <returns>	null if it fails, else the controller. </returns>
			static XboxController* GetController(const BYTE& player);
		};
	}
}