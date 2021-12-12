#ifndef RTIAW_RAY_H_
#define RTIAW_RAY_H_

#include "vec3.h"

namespace rtiaw {

	class Ray {
	public:
		Ray() {}
		Ray(const Point3& origin, const Vec3& direction)
			: origin(origin), direction(direction) {}

		Point3 origin() const { return origin; }
		Vec3 direction() const { return direction; }

		Point3 at(double t) {
			return origin + direction * t;
		}

	private:
		Point3 origin;
		Vec3 direction;
	};
}

#endif
