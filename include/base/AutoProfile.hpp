#ifndef INCLUDE_BASE_AUTOPROFILE_HPP_
#define INCLUDE_BASE_AUTOPROFILE_HPP_

#include "base/Profiler.hpp"
#include "base/Timer.hpp"

#define PROFILER_ON 0

struct AutoProfile
{
	AutoProfile(const char* name)
	{
		m_name = name;
		m_startTime = Timer::getTime();
	}

	~AutoProfile()
	{
		float endTime = Timer::getTime();
		float elapsedTime = endTime - m_startTime;

		Profiler::getInstance().storeSample(m_name, elapsedTime);
	}

	const char* m_name;
	float m_startTime;
};

#if PROFILER_ON
#define PROFILE(name) AutoProfile p(name)
#else
#define PROFILE(name)
#endif

#endif /* INCLUDE_BASE_AUTOPROFILE_HPP_ */
