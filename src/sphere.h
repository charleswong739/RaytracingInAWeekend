#ifndef RTIAW_SPHERE_H_
#define RTIAW_SPHERE_H_

#include "material.h"
#include "ray.h"

namespace rtiaw {

	class Sphere {
	public:
		Sphere() {}
		Sphere(Point3 center, double radius, Material* material) : center_(center), radius_(radius), material_(material) {}

		void hit(const Ray& ray, double t_min, double t_max, HitRecord& hit_record) const;

	private:
		Point3 center_;
		double radius_;
		Material* material_;
	};
}
#endif // !RTIAW_SPHERE_H_
