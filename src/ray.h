#ifndef RTIAW_RAY_H_
#define RTIAW_RAY_H_

#include "vec3.h"

namespace rtiaw {

	struct HitRecord {
		Point3 p;
		Vec3 normal;
		double t;
		bool front_face; // whether the ray is hitting the outside of the mesh

		inline void set_face_normal(const Ray& ray, const Vec3& outward_normal) {
			front_face = rtiaw::dot(ray.direction(), outward_normal) < 0.0;
			normal = front_face ? outward_normal : -outward_normal;
		}
	};

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
