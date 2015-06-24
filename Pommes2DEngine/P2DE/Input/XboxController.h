#pragma once

#include <Windows.h>
#include <Xinput.h>

#pragma comment(lib, "Xinput9_1_0.lib")

namespace P2DE
{
	namespace INPUT
	{
		/// <summary>	XInput, Xbox controller class. </summary>
		///
		/// <remarks>	Tobias, 03.06.2015. </remarks>
		class XboxController
		{
			private:
			/// <summary>	State of the controller. </summary>
			XINPUT_STATE m_ControllerState;
			/// <summary>	The controller number. </summary>
			int m_ControllerNum;

			public:
			/// <summary>	Default constructor. </summary>
			///
			/// <remarks>	Tobias, 03.06.2015. </remarks>
			XboxController();
			/// <summary>	Constructor. </summary>
			///
			/// <remarks>	Tobias, 03.06.2015. </remarks>
			///
			/// <param name="playerNumber">	The player number. </param>
			XboxController(int playerNumber);
			/// <summary>	Gets the state. </summary>
			///
			/// <remarks>	Tobias, 03.06.2015. </remarks>
			///
			/// <returns>	The state. </returns>
			XINPUT_STATE GetState();
			/// <summary>	Query if this controller is connected. </summary>
			///
			/// <remarks>	Tobias, 03.06.2015. </remarks>
			///
			/// <returns>	true if connected, false if not. </returns>
			bool IsConnected();
			/// <summary>	Vibrates controller motor. left and right motor. </summary>
			///
			/// <remarks>	Tobias, 03.06.2015. </remarks>
			///
			/// <param name="leftVal"> 	The left value. </param>
			/// <param name="rightVal">	The right value. </param>
			void Vibrate(int leftVal = 0, int rightVal = 0);
		};
	}
}
