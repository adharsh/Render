#include <cmath>

#include "Time.h"

namespace ginkgo {

	double Time::delta = 0;

	const std::chrono::high_resolution_clock::time_point& Time::getTime()
	{
		return std::chrono::high_resolution_clock::now();
	}

	const long Time::getDuration(const std::chrono::high_resolution_clock::time_point& start, const std::chrono::high_resolution_clock::time_point& finish)
	{
		return std::chrono::duration_cast<std::chrono::nanoseconds>(abs(finish - start)).count();
	}
	
	const double Time::getDelta()
	{
		return Time::delta;
	}

	void Time::setDelta(double delta)
	{
		Time::delta = delta;
	}


}