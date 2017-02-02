#include <cmath>

#include "Time.h"

namespace ginkgo {

	double Time::delta = 0;

	std::chrono::high_resolution_clock::time_point Time::getTime()
	{
		return std::chrono::high_resolution_clock::now();
	}

	long Time::getDuration(std::chrono::high_resolution_clock::time_point start, std::chrono::high_resolution_clock::time_point finish)
	{
		return std::chrono::duration_cast<std::chrono::nanoseconds>(abs(finish - start)).count();
	}

	
	double Time::getDelta()
	{
		return Time::delta;
	}

	void Time::setDelta(double delta)
	{
		Time::delta = delta;
	}


}