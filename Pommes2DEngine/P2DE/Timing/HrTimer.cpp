#include "HrTimer.h"

using namespace P2DE::TIMING;

HrTimer::HrTimer()
{
	m_LastTime = Time::now();
	m_DeltaTime = 0.0;
}

void HrTimer::Update()
{
	fsec fs = Time::now() - m_LastTime;
	m_LastTime = Time::now();
	m_DeltaTime = fs.count();
}
