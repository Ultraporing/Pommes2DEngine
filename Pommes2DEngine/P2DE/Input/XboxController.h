#pragma once

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
			XboxController();
			XboxController(int playerNumber);
			XINPUT_STATE GetState();
			bool IsConnected();
			void Vibrate(int leftVal = 0, int rightVal = 0);
		};
	}
}
