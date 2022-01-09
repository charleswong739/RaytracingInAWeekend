#ifndef RTIAW_WORLD_H_
#define RTIAW_WORLD_H_

#include <vector>

#include "ray.h"
#include "sphere.h"

namespace rtiaw {

	class World {
	public:
		World() {}
		
		void addObject(Sphere& object) { objects_.push_back(object); }

		void resolve(const Ray& ray, double t_min, double t_max, HitRecord& hit_record) const;

	private:
		std::vector<Sphere> objects_;
	};
}

#endif