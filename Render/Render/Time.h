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
		static std::chrono::high_resolution_clock::time_point getTime();
		static long getDuration(std::chrono::high_resolution_clock::time_point start, std::chrono::high_resolution_clock::time_point finish);
		static double getDelta();
		static void setDelta(double delta);
	

	};

}