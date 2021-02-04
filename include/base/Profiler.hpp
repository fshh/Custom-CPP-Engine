#ifndef INCLUDE_BASE_PROFILER_HPP_
#define INCLUDE_BASE_PROFILER_HPP_

#include <unordered_map>

struct Sample {
public:
	Sample();
	Sample(float initialVal);
	void addSample(float val);
	int n() { return m_n; }
	float avg() { return m_avg; }
private:
	int m_n;
	float m_avg;
};

class Profiler {
private:
	Profiler(); //!< Does nothing. Call Profiler::getInstance() to get the singleton instance and call startUp() on it to initialize.
	Profiler(Profiler const&) = delete; // Avoid copy constructor.
  void operator=(Profiler const&) = delete; // Don't allow copy assignment.
  Profiler(Profiler const&&) = delete; // Avoid move constructor.
  void operator=(Profiler const&&) = delete; // Don't allow move assignment.

  static Profiler* instance; //!< The singleton instance for Profiler.

  std::unordered_map<const char*, Sample> samples;

  unsigned int startTicks;

public:
  static Profiler& getInstance(); //!< Returns a pointer to the singleton instance of Profiler.

  void startUp(); //!< Handles any initialization behavior necessary for the instance of Profiler.
  void shutDown(); //!< Destroys the instance of Profiler and handles any destruction behavior.

  void storeSample(const char* name, const float elapsedTime); //!< Stores a profiling sample for a process.
};

#endif /* INCLUDE_BASE_PROFILER_HPP_ */
