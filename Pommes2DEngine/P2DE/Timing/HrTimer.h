//=================================================================================== 
// Copyright (c) 2015 Tobias Lenz.  All rights reserved.                                                                  
//=================================================================================== 

#pragma once
#include <chrono>

namespace P2DE
{
	namespace TIMING
	{
		class HrTimer
		{
			typedef std::chrono::high_resolution_clock Time;
			typedef std::chrono::milliseconds ms;
			typedef std::chrono::duration<float> fsec;
			typedef std::chrono::system_clock::time_point timePoint;

			private:
			timePoint m_LastTime;
			float m_DeltaTime;

			public:
			HrTimer();

			void Update();
			float GetDeltaTime() { return m_DeltaTime; }
		};
	}
}
