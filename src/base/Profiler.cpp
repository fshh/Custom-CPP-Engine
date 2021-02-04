#include "base/Profiler.hpp"
#include "base/Timer.hpp"
#include <SDL.h>
#include <iostream>

Profiler* Profiler::instance = nullptr;

Profiler::Profiler()
{
}

Profiler&
Profiler::getInstance()
{
	if (instance == nullptr) {
		instance = new Profiler();
	}
	return *instance;
}

void
Profiler::startUp()
{
	std::cout << "Starting up Profiler..." << std::endl;
	startTicks = SDL_GetTicks();
}

void
Profiler::shutDown()
{
	std::cout << "Shutting down Profiler..." << std::endl;
	std::cout << "=========== PROFILING RESULTS ===========" << std::endl;
	float totalTime = SDL_GetTicks() - startTicks;
	std::cout << "TOTAL RUNTIME: " << totalTime << " ms" << std::endl;

	std::cout.precision(5);
	std::cout.setf(std::ios::fixed, std::ios::floatfield);

	for (auto sample : samples) {
		float avg = sample.second.avg();
		int n = sample.second.n();
		float percent = ((avg * (float)n) / totalTime) * 100;
		std::cout << "(" << percent << "%) " << sample.first << ": " << avg << " ms avg, " << n << " samples" << std::endl;
	}
	std::cout << std::endl;
	delete instance;
}

void
Profiler::storeSample(const char* name, const float timeElapsed)
{
	samples[name].addSample(timeElapsed);
}

Sample::Sample():
	m_n(0), m_avg(0)
{
}

Sample::Sample(float initialVal):
	m_n(1), m_avg(initialVal)
{
}

void
Sample::addSample(float val)
{
	m_n++;
	m_avg = (m_avg * ((float)m_n - 1.0f) + val) / (float)m_n;
}

