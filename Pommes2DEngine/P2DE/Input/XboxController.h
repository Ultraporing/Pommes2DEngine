#pragma once

// Set minimum system version to windows vista
#define _WIN32_WINNT   0x0600
#include <Windows.h>
#include <Xinput.h>

#pragma comment(lib, "XInput.lib")

namespace P2DE
{
	namespace INPUT
	{
		class XboxController
		{
			private:
			XINPUT_STATE m_ControllerState;
			int m_ControllerNum;

			public:
			XboxController(int playerNumber);
			XINPUT_STATE GetState();
			bool IsConnected();
			void Vibrate(int leftVal = 0, int rightVal = 0);
		};
	}
}
