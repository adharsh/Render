#pragma once

#include <chrono>

namespace ginkgo {

	class Time
	{
	private:
		static double delta;
	public:
		static const long SECOND = 1E9L;

	public:
		static const std::chrono::high_resolution_clock::time_point& getTime();
		static const long getDuration(const std::chrono::high_resolution_clock::time_point& start, const std::chrono::high_resolution_clock::time_point& finish);
		static const double getDelta();
		static void setDelta(double delta);
	

	};

}