#include "XboxController.h"

using namespace P2DE::INPUT;

XboxController::XboxController(int playerNumber)
{
	// Set the Controller Number
	m_ControllerNum = playerNumber - 1;
}

XINPUT_STATE XboxController::GetState()
{
	// Zeroise the state
	ZeroMemory(&m_ControllerState, sizeof(XINPUT_STATE));

	// Get the state
	XInputGetState(m_ControllerNum, &m_ControllerState);

	return m_ControllerState;
}

bool XboxController::IsConnected()
{
	// Zeroise the state
	ZeroMemory(&m_ControllerState, sizeof(XINPUT_STATE));

	// Get the state
	DWORD Result = XInputGetState(m_ControllerNum, &m_ControllerState);

	if (Result == ERROR_SUCCESS)
	{
		return true;
	}
	else
	{
		return false;
	}
}

void XboxController::Vibrate(int leftVal, int rightVal)
{
	// Create a Vibraton State
	XINPUT_VIBRATION Vibration;

	// Zeroise the Vibration
	ZeroMemory(&Vibration, sizeof(XINPUT_VIBRATION));

	// Set the Vibration Values
	Vibration.wLeftMotorSpeed = leftVal;
	Vibration.wRightMotorSpeed = rightVal;

	// Vibrate the controller
	XInputSetState(m_ControllerNum, &Vibration);
}
