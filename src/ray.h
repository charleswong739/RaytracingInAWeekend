#ifndef RTIAW_RAY_H_
#define RTIAW_RAY_H_

#include "vec3.h"

namespace rtiaw {

	class Ray {
	public:
		Ray() {}
		Ray(const Point3& origin, const Vec3& direction)
			: origin_(origin), direction_(direction) {}

		Point3 origin() const { return origin_; }
		Vec3 direction() const { return direction_; }

		Point3 at(double t) const {
			return origin_ + direction_ * t;
		}

	private:
		Point3 origin_;
		Vec3 direction_;
	};
}

#endif
