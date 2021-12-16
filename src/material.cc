#include "material.h"

#include "ray.h"
#include "vec3.h"

bool rtiaw::Material::scatter(const Ray& ray_in, const HitRecord& hit_record, Color3& attenuation, Ray& scattered) const
{

	attenuation = albedo_;

	if (metalness_) {
		auto reflected_ray = reflect(normalize(ray_in.direction()), hit_record.normal);

		scattered = Ray(hit_record.p, reflected_ray + (1 - glossiness_) * random_in_unit_sphere());

		return (dot(scattered.direction(), hit_record.normal) > 0);
	}
	else {
		auto scatter_direction = hit_record.normal + rtiaw::random_unit_vector();

		// Catch degenerate scatter direction (scatter opposite to normal)
		if (scatter_direction.near_zero()) {
			scatter_direction = hit_record.normal;
		}

		scattered = Ray(hit_record.p, scatter_direction);
		return true;
	}
}