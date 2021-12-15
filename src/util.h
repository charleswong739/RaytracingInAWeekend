#ifndef RTIAW_MAIN_H_
#define RTIAW_MAIN_H_

#include <limits>

namespace rtiaw {

	// Constants
	const double infinity = std::numeric_limits<double>::infinity();
	const double pi = 3.1415926535897932385;

	// Utility
	inline double degrees_to_radians(double degrees) {
		return degrees * pi / 180.0;
	}

	inline double random_double() {
		// random double in [0, 1)
		return std::rand() / (RAND_MAX + 1.0);
	}

	inline double random_double(double min, double max) {
		// random double in [min, max)
		return min + (max - min) * random_double();
	}

	inline double clamp(double x, double min, double max) {
		if (x < min) return min;
		if (x > max) return max;
		return x;
	}
}

#endif