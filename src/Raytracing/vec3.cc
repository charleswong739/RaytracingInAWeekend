#include "vec3.h"

using rtiaw::Vec3;

Vec3 rtiaw::refract(const Vec3& uv, const Vec3& n, double refraction_ratio)
{
	auto cos_theta = fmin(dot(-uv, n), 1.0);
	Vec3 r_out_perp = refraction_ratio * (uv + cos_theta * n);
	Vec3 r_out_parallel = -sqrt(fabs(1.0 - r_out_perp.square_length())) * n;
	return r_out_perp + r_out_parallel;
}

Vec3 rtiaw::random_in_unit_sphere() {
	while (true) {
		auto p = Vec3(random_double(-1, 1), random_double(-1, 1), random_double(-1, 1));
		if (p.square_length() < 1)
			return p;
	}
}

Vec3 rtiaw::random_unit_vector() {
	return normalize(random_in_unit_sphere());
}