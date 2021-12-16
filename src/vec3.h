#ifndef RTIAW_VEC3_H_
#define RTIAW_VEC3_H_

#include <cmath>
#include <random>

#include "util.h"

namespace rtiaw {

	class Vec3 {
	public:
		Vec3() : e_{ 0, 0, 0 } {}
		Vec3(double e0, double e1, double e2) : e_{ e0, e1, e2 } {}

		double x() const { return e_[0]; }
		double y() const { return e_[1]; }
		double z() const { return e_[2]; }

		// for accessing when vec3 is const, since returning by reference allows changing of value
		double operator[](int i) const { return e_[i]; }
		double& operator[](int i) { return e_[i]; }

		Vec3 operator-() const { return Vec3(-e_[0], -e_[1], -e_[2]); }

		Vec3& operator+=(const Vec3& v) {
			e_[0] += v.e_[0];
			e_[1] += v.e_[1];
			e_[2] += v.e_[2];
			return *this;
		}

		Vec3& operator*=(const double d) {
			e_[0] *= d;
			e_[1] *= d;
			e_[2] *= d;
			return *this;
		}

		Vec3& operator/=(const double d) {
			return *this *= 1 / d;
		}

		double length() const {
			return std::sqrt(square_length());
		}

		double square_length() const {
			return e_[0] * e_[0] + e_[1] * e_[1] + e_[2] * e_[2];
		}

		bool near_zero() const {
			auto margin = 1e-8;
			return (fabs(e_[0]) < margin) && (fabs(e_[1]) < margin) && (fabs(e_[2]) < margin);
		}

	private:
		double e_[3];
	};

	// aliases
	using Point3 = Vec3;
	using Color3 = Vec3;

	// other utility functions

	inline Vec3 operator+(const Vec3& u, const Vec3& v) {
		return Vec3(
			u[0] + v[0],
			u[1] + v[1],
			u[2] + v[2]
		);
	}

	inline Vec3 operator-(const Vec3& u, const Vec3& v) {
		return Vec3(
			u[0] - v[0],
			u[1] - v[1],
			u[2] - v[2]
		);
	}

	inline Vec3 operator*(const Vec3& v, const double d) {
		return Vec3(v[0] * d, v[1] * d, v[2] * d);
	}

	inline Vec3 operator*(const double d, const Vec3& v) {
		return v * d;
	}

	inline Vec3 operator*(const Vec3& u, const Vec3& v) {
		return Vec3(u[0] * v[0], u[1] * v[1], u[2] * v[2]);
	}

	inline Vec3 operator/(const Vec3& v, const double d) {
		return Vec3(v[0] / d, v[1] / d, v[2] / d);
	}

	inline double dot(const Vec3& u, const Vec3& v) {
		return u[0] * v[0] + u[1] * v[1] + u[2] * v[2];
	}

	inline Vec3 cross(const Vec3& u, const Vec3& v) {
		return Vec3(
			u[1] * v[2] - u[2] * v[1],
			u[2] * v[0] - u[0] * v[2],
			u[0] * v[1] - u[1] * v[0]
		);
	}

	inline Vec3 normalize(const Vec3& v) {
		return v / v.length();
	}

	inline Vec3 clamp(const Vec3& v, double min, double max) {
		return Vec3(
			clamp(v[0], min, max),
			clamp(v[1], min, max),
			clamp(v[2], min, max)
		);
	}

	inline Vec3 random_in_unit_sphere() {
		while (true) {
			auto p = Vec3(random_double(-1, 1), random_double(-1, 1), random_double(-1, 1));
			if (p.square_length() < 1)
				return p;
		}
	}

	inline Vec3 random_unit_vector() {
		return normalize(random_in_unit_sphere());
	}

	
	inline Vec3 reflect(const Vec3& v, const Vec3& n) {
		return v - 2 * dot(v, n) * n;
	}

}

#endif