//=================================================================================== 
// Copyright (c) 2015 Tobias Lenz.  All rights reserved.                                                                  
//=================================================================================== 

#pragma once
#include <chrono>

namespace P2DE
{
	/// <summary>	Pommes2D Engine Timing Related Namespace. </summary>
	///
	/// <remarks>	Tobias, 22.05.2015. </remarks>
	namespace TIMING
	{
		/// <summary>	A High Resolution timer. </summary>
		///
		/// <remarks>	Tobias, 22.05.2015. </remarks>
		class HrTimer
		{
			/// <summary>	Defines an alias representing the time. </summary>
			///
			/// <remarks>	Tobias, 22.05.2015. </remarks>
			typedef std::chrono::high_resolution_clock Time;

			/// <summary>	Defines an alias representing the milliseconds. </summary>
			///
			/// <remarks>	Tobias, 22.05.2015. </remarks>
			typedef std::chrono::milliseconds ms;

			/// <summary>	Defines an alias representing the float duration. </summary>
			///
			/// <remarks>	Tobias, 22.05.2015. </remarks>
			typedef std::chrono::duration<float> fsec;

			/// <summary>	Defines an alias representing the time point. </summary>
			///
			/// <remarks>	Tobias, 22.05.2015. </remarks>
			typedef std::chrono::system_clock::time_point timePoint;

			private:
			/// <summary>	The last time point. </summary>
			timePoint m_LastTime;

			/// <summary>	The delta time. </summary>
			float m_DeltaTime;

			public:

			/// <summary>	Default constructor. </summary>
			///
			/// <remarks>	Tobias, 22.05.2015. </remarks>
			HrTimer();

			/// <summary>	Updates this Timer. </summary>
			///
			/// <remarks>	Tobias, 22.05.2015. </remarks>
			void Update();

			/// <summary>	Gets delta time. </summary>
			///
			/// <remarks>	Tobias, 22.05.2015. </remarks>
			///
			/// <returns>	The delta time. </returns>
			float GetDeltaTime() { return m_DeltaTime; }
		};
	}
}
