#ifndef RTIAW_MATERIAL_H_
#define RTIAW_MATERIAL_H_

#include "ray.h"
#include "vec3.h"

namespace rtiaw {

	class Material {
	public:
		Material() {}
		Material(const Color3& albedo) : albedo_(albedo) {}

		void scatter(const Ray& ray_in, const HitRecord& hit_record, Color3& attenuation, Ray& scattered) const;

	private:
		Color3 albedo_;
	};
}

#endif // !RTIAW_MATERIAL_H_
