#include "material.h"

#include "ray.h"
#include "vec3.h"

void rtiaw::Material::scatter(const Ray& ray_in, const HitRecord& hit_record, Color3& attenuation, Ray& scattered) const
{
	auto scatter_direction = hit_record.normal + rtiaw::random_unit_vector();

	// Catch degenerate scatter direction (scatter opposite to normal)
	if (scatter_direction.near_zero()) {
		scatter_direction = hit_record.normal;
	}

	scattered = Ray(hit_record.p, scatter_direction);
	attenuation = albedo_;
}