#include "InputManager.h"
#include "..\GFX\Camera.h"

using namespace P2DE::INPUT;

bool InputManager::IsKeyDown(const BYTE& VK_Keycode)
{
	SHORT keyState = GetAsyncKeyState(VK_Keycode);

	if ((1 << 16) & keyState)
		return true;
	else
		return false;
}

bool InputManager::IsKeyUp(const BYTE& VK_Keycode)
{
	if (!IsKeyDown(VK_Keycode))
		return true;
	else
		return false;
}

bool InputManager::IsKeyPressed(const BYTE& VK_Keycode)
{
	if (IsKeyDown(VK_Keycode) && (m_CurrentKeysPressed[VK_Keycode] == false))
	{
		m_CurrentKeysPressed.at(VK_Keycode) = true;
		return true;
	}
	else if (IsKeyUp(VK_Keycode))
	{
		m_CurrentKeysPressed.at(VK_Keycode) = false;
		return false;
	}
	else
		return false;
}

// Returns Screen coordinates
bool InputManager::GetScreenMousePos(HWND targetWindow, POINT* mousePos)
{
	if (GetCursorPos(mousePos))
		return ScreenToClient(targetWindow, mousePos) == 1 ? true : false;
	else
		return false;
}

bool InputManager::GetGameMousePos(HWND targetWindow, POINT* mousePos, P2DE::GFX::Camera* cam)
{
	if (GetScreenMousePos(targetWindow, mousePos))
	{
		mousePos->x += (long)cam->GetCameraPos().x;
		mousePos->y += (long)cam->GetCameraPos().y;

		return true;
	}
	else
		return false;
}

bool InputManager::IsMouseDown(const BYTE& button)
{
	BYTE mouseButton = 0;
	switch (button)
	{
		case 0:
			mouseButton = VK_LBUTTON;
			break;
		case 1:
			mouseButton = VK_MBUTTON;
			break;
		case 2:
			mouseButton = VK_RBUTTON;
			break;
		default:
			mouseButton = VK_LBUTTON;
			break;
	}

	return IsKeyDown(mouseButton);
}

bool InputManager::IsMouseUp(const BYTE& button)
{
	BYTE mouseButton = 0;
	switch (button)
	{
		case 0:
			mouseButton = VK_LBUTTON;
			break;
		case 1:
			mouseButton = VK_MBUTTON;
			break;
		case 2:
			mouseButton = VK_RBUTTON;
			break;
		default:
			mouseButton = VK_LBUTTON;
			break;
	}

	return IsKeyUp(mouseButton);
}

bool InputManager::IsMouseClicked(const BYTE& button)
{
	BYTE mouseButton = 0;
	switch (button)
	{
		case 0:
			mouseButton = VK_LBUTTON;
			break;
		case 1:
			mouseButton = VK_MBUTTON;
			break;
		case 2:
			mouseButton = VK_RBUTTON;
			break;
		default:
			mouseButton = VK_LBUTTON;
			break;
	}

	return IsKeyPressed(mouseButton);
}