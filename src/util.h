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
}

#endif