#include "sphere.h"
#include "vec3.h"

bool rtiaw::Sphere::hit(const Ray& ray, double t_min, double t_max, HitRecord& hit_record) const
{
	Vec3 oc = ray.origin() - center;
	double a = ray.direction().square_length();
	double half_b = dot(oc, ray.direction());
	double c = oc.square_length() - radius * radius;
	double discriminant = half_b * half_b - a * c;

	if (discriminant < 0) {
		return false;
	}

	// find the closest root that falls into [t_min, t_max]
	double sqrt_determinant = std::sqrt(discriminant);
	root = (-half_b - sqrt_determinant) / a;

	if (root < t_min || t_max < root) {
		root = (-half_b + sqrt_determinant) / a;

		if (root < t_min || t_max < root) {
			return false;
		}
	}

	// update hit record
	hit_record.t = root;
	hit_record.p = ray.at(root);
	Vec3 outward_normal = (hit_record.p - center) / radius;
	hit_record.set_face_normal(ray, outward_normal);

	return true;
}