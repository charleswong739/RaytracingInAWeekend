// main.cpp: Entry point of application
//
#include <chrono>
#include <iostream>
#include <vector>

#include "bitmap.h"
#include "color.h"
#include "ray.h"
#include "vec3.h"

using rtiaw::Vec3;
using rtiaw::Point3;
using rtiaw::Color3;
using rtiaw::Ray;

double hit_sphere(const Point3& center, double radius, const Ray& ray) {
	// given the center and radius of a sphere, calculate the t value
	// for the ray on the closest hit point, or -1 if none was found
	Vec3 oc = ray.origin() - center;
	double a = ray.direction().square_length();
	double half_b = dot(oc, ray.direction());
	double c = oc.square_length() - radius * radius;
	double discriminant = half_b * half_b -  a * c;
	if (discriminant < 0) {
		return -1.0;
	}
	else {
		return (-half_b - std::sqrt(discriminant)) / a;
	}
}

Color3 ray_color(const Ray& ray) {
	// calculates the color a ray should be
	Point3 sphere_center(0, 0, -1);
	double sphere_radius = 0.5;

	double t = hit_sphere(sphere_center, sphere_radius, ray);

	if (t > 0.0) {
		// unit normal is the normalized vector from the sphere center pointing to the hit point
		Vec3 sphere_normal = rtiaw::normalize(ray.at(t) - sphere_center);

		// scale normal values to [0, 1], make it a color
		return 0.5 * Color3(sphere_normal.x() + 1, sphere_normal.y() + 1, sphere_normal.z() + 1);
	}

	// lerp from blue to white depending on Y coordinate, draw sky
	Vec3 normalized_direction = rtiaw::normalize(ray.direction());
	t = (normalized_direction.y() + 1.0) * 0.5; // if reach here, that means ray did not hit sphere, so overwrite t with sky value

	return (1.0 - t) * Color3(1.0, 1.0, 1.0) + t * Color3(0.5, 0.7, 1.0);
}

int main()
{
	// Image setup
	const double aspect_ratio = 16.0f / 9.0f;
	const unsigned int image_width = 1920;
	const unsigned int image_height = (unsigned int)std::floor(image_width / aspect_ratio + 0.5);

	// World setup
	Point3 origin;

	// Camera setup
	double viewport_height = 2.0f;
	double viewport_width = aspect_ratio * viewport_height;
	double focal_length = 1.0;

	Vec3 viewport_horizontal(viewport_width, 0, 0);
	Vec3 viewport_vertical(0, viewport_height, 0);
	Point3 viewport_bottom_left = origin - viewport_horizontal / 2 - viewport_vertical / 2 - Vec3(0, 0, focal_length);

	// Bitmap output setup
	int total_header_size = bitmap::kBMPHeaderSize + bitmap::kDIBHeaderSize;
	int total_raw_data_size = image_width * image_height * 4;

	bitmap::BMPHeader bmp_header(total_header_size + total_raw_data_size, total_header_size);
	bitmap::DIBHeader dib_header(image_width, image_height, 300, 300);

	std::vector<bitmap::Rgba> image_buffer(image_width * image_height); // buffer is read from bottom left to top right

	std::cout << "Image size: " << image_width << "x" << image_height << std::endl;
	std::cout << "Bitmap filesize: " << (total_header_size + total_raw_data_size) / 1024 << "KB" << std::endl;

	// Time begin
	std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();

	// Render
	for (int j = image_height - 1; j >= 0; j--) {
		for (int i = 0; i < image_width; i++) {

			double u = double(i) / (image_width - 1);
			double v = double(j) / (image_height - 1);

			Ray cast(origin, viewport_bottom_left + u * viewport_horizontal + v * viewport_vertical - origin);
			
			image_buffer[j * image_width + i] = rtiaw::vec3_to_rgba(ray_color(cast));
		}
	}

	// Time end
	std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();

	//std::cout << "Render took: " << (std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count()) / 1000000.0 << "s" << std::endl;
	std::cout << "Render took: " << (std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count()) / 1000.0 << "ms" << std::endl;
	//std::cout << "Render took: " << std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count() << "\xE6s" << std::endl;
	//std::cout << "Render took: " << std::chrono::duration_cast<std::chrono::nanoseconds> (end - begin).count() << "[ns]" << std::endl;

	bitmap::write_bitmap("output.bmp", &bmp_header, &dib_header, &image_buffer[0], total_raw_data_size);

	return 0;
}
