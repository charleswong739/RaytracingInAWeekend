#ifndef RTIAW_COLOR_H_
#define RTIAW_COLOR_H_

#include "vec3.h"
#include "bitmap.h"

namespace rtiaw {
	bitmap::Rgba vec3_to_rgba(const Vec3& v) {
		return bitmap::Rgba(
			(uint32_t)(255.9999 * v[0]),
			(uint32_t)(255.9999 * v[1]),
			(uint32_t)(255.9999 * v[2]),
			0xFF);
	}
}

#endif