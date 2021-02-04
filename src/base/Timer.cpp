#include <SDL.h>

#include "base/Timer.hpp"

const int Timer::sampleSize = 60;

Timer* Timer::instance = nullptr;

Timer* Timer::getInstance() {
	if (instance == nullptr) {
		instance = new Timer();
	}
	return instance;
}

void Timer::deleteInstance() {
	delete instance;
	instance = nullptr;
}

void Timer::startTimer() {
	getInstance()->startTicks = SDL_GetTicks();
}

float Timer::getTime() {
	return SDL_GetTicks() - getInstance()->startTicks;
}

void Timer::endTimer() {
	getInstance()->previousDelta = SDL_GetTicks() - getInstance()->startTicks;
	if (getInstance()->dt_deque.size() >= sampleSize) {
		getInstance()->dt_deque.pop_front();
	}
	getInstance()->dt_deque.push_back(getInstance()->previousDelta);
}

float Timer::deltaTime() {
	return getInstance()->previousDelta / 1000.0;
}

float Timer::getAverageDeltaTime() {
	if (getInstance()->dt_deque.size() <= 0) {
		// Invalid time.
		return -1;
	}

	float total = 0;
	for (float dt : getInstance()->dt_deque) {
		total += dt;
	}
	return total / getInstance()->dt_deque.size();
}
