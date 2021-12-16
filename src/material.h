#ifndef RTIAW_MATERIAL_H_
#define RTIAW_MATERIAL_H_

#include "ray.h"
#include "vec3.h"

namespace rtiaw {

	class Material {
	public:
		Material() {}
		Material(const Color3& base_color, double glossiness = 1, bool metalness = false) 
			: base_color_(base_color), 
			glossiness_(glossiness < 1 ? glossiness : 1), 
			metalness_(metalness) {}

		bool scatter(const Ray& ray_in, const HitRecord& hit_record, Color3& attenuation, Ray& scattered) const;

	private:
		Color3 base_color_;
		double glossiness_;
		bool metalness_;
	};
}

#endif // !RTIAW_MATERIAL_H_
