#ifndef RTIAW_CAMERA_H_
#define RTIAW_CAMERA_H_

#include "ray.h"
#include "vec3.h"

namespace rtiaw {
	
	class Camera {
	public:
		Camera(Point3 origin, double aspect_ratio, double viewport_height, double focal_length)
			: origin_(origin) {

			auto viewport_width = aspect_ratio * viewport_height;

			viewport_horizontal_ = Vec3(viewport_width, 0, 0);
			viewport_vertical_ = Vec3(0, viewport_height, 0);

			viewport_bottom_left_ = origin - viewport_horizontal_ / 2 - viewport_vertical_ / 2 - Vec3(0, 0, focal_length);
		}

		Ray get_ray(double u, double v) const {
			return Ray(origin_, viewport_bottom_left_ + u * viewport_horizontal_ + v * viewport_vertical_ - origin_);
		}

	private:
		Point3 origin_;
		Point3 viewport_bottom_left_;
		Vec3 viewport_horizontal_;
		Vec3 viewport_vertical_;
	};
}

#endif // !RTIAW_CAMERA_H_
