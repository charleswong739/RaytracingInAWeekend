#include "world.h"

void rtiaw::World::resolve(const Ray& ray, double t_min, double t_max, HitRecord& hit_record) const
{
	auto closest = t_max;

	for (auto const& object : objects_) {
		object.hit(ray, t_min, closest, hit_record);
		closest = hit_record.t; // hit_record is initialized with t = infinity
	}
}
