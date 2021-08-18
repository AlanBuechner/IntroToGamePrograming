#include "Time.h"
#include <chrono>

double Engine::Time::m_DeltaTime;
double Engine::Time::m_LastFrameTime;

namespace Engine
{
	using namespace std::chrono;
	double Time::GetTime()
	{
		return duration<double>(system_clock::now().time_since_epoch()).count();
	}

	void Time::UpdateDeltaTime()
	{
		double time = GetTime();
		m_DeltaTime = time - m_LastFrameTime;
		m_LastFrameTime = time;
	}

}
