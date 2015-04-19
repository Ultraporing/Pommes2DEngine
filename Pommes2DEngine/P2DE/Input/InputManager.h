#pragma once
#include <Windows.h>
#include <array>

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