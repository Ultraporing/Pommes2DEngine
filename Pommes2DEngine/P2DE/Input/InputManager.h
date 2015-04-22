//=================================================================================== 
// Copyright (c) 2015 Tobias Lenz.  All rights reserved.                                                                  
//=================================================================================== 

#pragma once
#include <Windows.h>
#include <array>

// Define missing vk keycodes ====
#pragma region Define missing vk keycodes
// NUMBER KEYS
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
// LETTER KEYS
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
// =====================

namespace P2DE
{
	namespace GFX
	{
		class Camera;
	}

	namespace INPUT
	{
		class InputManager
		{
			private:
			std::array<bool, MAXBYTE> m_CurrentKeysPressed;

			public:
			// checks if key is pressed!
			bool IsKeyDown(const BYTE& VK_Keycode);
			// checks if key is not pressed!
			bool IsKeyUp(const BYTE& VK_Keycode);
			// checks if key was pressed once!
			bool IsKeyPressed(const BYTE& VK_Keycode);

			// Returns Screen coordinates
			bool GetScreenMousePos(HWND targetWindow, POINT* mousePos);
			// Returns Ingame coordinates
			bool GetGameMousePos(HWND targetWindow, POINT* mousePos, P2DE::GFX::Camera* cam);
			// const BYTE& button: 0 = left, 1 = middle, 2 = right, else = left
			bool IsMouseDown(const BYTE& button);
			// const BYTE& button: 0 = left, 1 = middle, 2 = right, else = left
			bool IsMouseUp(const BYTE& button);
			// const BYTE& button: 0 = left, 1 = middle, 2 = right, else = left
			bool IsMouseClicked(const BYTE& button);
		};
	}
}