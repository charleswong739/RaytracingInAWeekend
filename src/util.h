#ifndef RTIAW_MAIN_H_
#define RTIAW_MAIN_H_

#include <limits>
#include <random>

namespace rtiaw {

	// Constants
	const double infinity = std::numeric_limits<double>::infinity();
	const double pi = 3.1415926535897932385;

	// Utility
	inline double degrees_to_radians(double degrees) {
		return degrees * pi / 180.0;
	}

	inline double random_double() {
		static std::uniform_real_distribution<double> distribution(0.0, 1.0);
		static std::mt19937 generator;
		return distribution(generator);
	}

	inline double clamp(double x, double min, double max) {
		if (x < min) return min;
		if (x > max) return max;
		return x;
	}
}

#endif