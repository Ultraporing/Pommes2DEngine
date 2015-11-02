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
	if (IsKeyDown(VK_Keycode) && (InputManager::m_CurrentKeysPressed[VK_Keycode] == false))
	{
		InputManager::m_CurrentKeysPressed.at(VK_Keycode) = true;
		return true;
	}
	else if (IsKeyUp(VK_Keycode))
	{
		InputManager::m_CurrentKeysPressed.at(VK_Keycode) = false;
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

void InputManager::SetMousewheelState(WPARAM wParam)
{
	if (GET_WHEEL_DELTA_WPARAM(wParam) > 0)
		InputManager::m_MousewheelState = 1;
	else if (GET_WHEEL_DELTA_WPARAM(wParam) < 0)
		InputManager::m_MousewheelState = -1;
	else
		InputManager::m_MousewheelState = 0;
}

bool InputManager::IsMousewheelScrollUp()
{
	return InputManager::m_MousewheelState == 1 ? true : false;
}

bool InputManager::IsMousewheelScrollDown()
{
	return InputManager::m_MousewheelState == -1 ? true : false;
}

int InputManager::GetMousewheelState()
{
	return InputManager::m_MousewheelState;
}

void InputManager::ResetMousewheelState()
{
	InputManager::m_MousewheelState = 0;
}

void InputManager::InitXboxControllers()
{
	for (int i = 1; i < 5; i++)
	{
		InputManager::m_XboxControllers.at(i-1) = new XboxController(i);
	}
}

void InputManager::DeinitializeXboxControllers()
{
	for (int i = 0; i < 4; i++)
	{
		delete InputManager::m_XboxControllers.at(i);
		InputManager::m_XboxControllers.at(i) = NULL;
	}
}

bool InputManager::IsControllerConnected(const BYTE& player)
{
	return InputManager::m_XboxControllers.at(player - 1)->IsConnected();
}

bool InputManager::IsControllerButtonPressed(const BYTE& player, const WORD& xInputGamepadButton)
{
	if (InputManager::IsControllerConnected(player))
		return InputManager::m_XboxControllers.at(player - 1)->GetState().Gamepad.wButtons & xInputGamepadButton ? true : false;
	else
		return false;
}

XboxController* InputManager::GetController(const BYTE& player)
{
	return InputManager::m_XboxControllers.at(player - 1);
}
