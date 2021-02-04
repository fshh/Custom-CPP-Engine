#ifndef INCLUDE_TIMER_HPP_
#define INCLUDE_TIMER_HPP_

#include <deque>

class Timer {
public:

	static const int sampleSize;

	/**
	 * Returns the current instance of Timer or makes a new one.
	 */
	static Timer* getInstance();

	/**
	 * Removes the current instance from the heap.
	 */
	static void deleteInstance();

	/**
	 * Starts the timer.
	 */
	static void startTimer();

	/**
	 * Gets the amount of time it's been since the timer was started.
	 */
	static float getTime();

	/**
	 * Ends the timer stores the delta time in milliseconds.
	 */
	static void endTimer();

	/**
	 * Gets the most recent delta time measured in seconds.
	 */
	static float deltaTime();

	/**
	 * Gets the average delta time over the last sampleSize or less polls.
	 * @return The average delta time or an invalid time (-1) if there are no polls.
	 */
	static float getAverageDeltaTime();

private:
	std::deque<float> dt_deque;

	float previousDelta;

	unsigned int startTicks;

	static Timer* instance;

	Timer(): previousDelta(-1), startTicks(0) {}  // Private Singleton
	Timer(Timer const&) = delete; // Avoid copy constructor.
	void operator=(Timer const&) = delete; // Don't allow copy assignment.
	Timer(Timer const&&) = delete; // Avoid move constructor.
	void operator=(Timer const&&) = delete; // Don't allow move assignment.
};

#endif /* INCLUDE_TIMER_HPP_ */
