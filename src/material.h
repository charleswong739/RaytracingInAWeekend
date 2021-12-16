#ifndef RTIAW_MATERIAL_H_
#define RTIAW_MATERIAL_H_

#include "ray.h"
#include "vec3.h"

namespace rtiaw {

	class Material {
	public:
		Material() {}
		Material(const Color3& albedo, double glossiness = 1, bool metalness = false) 
			: albedo_(albedo), 
			glossiness_(glossiness < 1 ? glossiness : 1), 
			metalness_(metalness) {}

		bool scatter(const Ray& ray_in, const HitRecord& hit_record, Color3& attenuation, Ray& scattered) const;

	private:
		Color3 albedo_;
		double glossiness_;
		bool metalness_;
	};
}

#endif // !RTIAW_MATERIAL_H_
