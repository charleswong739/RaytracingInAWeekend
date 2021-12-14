// main.cpp: Entry point of application
//
#include <chrono>
#include <iostream>
#include <vector>

#include "bitmap.h"
#include "color.h"
#include "ray.h"
#include "util.h"
#include "vec3.h"
#include "world.h"

using rtiaw::Vec3;
using rtiaw::Point3;
using rtiaw::Color3;
using rtiaw::Ray;

Color3 ray_color(const Ray& ray, const rtiaw::World& world) {
	// calculates the color a ray should be
	rtiaw::HitRecord hit_record;
	world.resolve(ray, 0.0, rtiaw::infinity, hit_record);

	//double t = hit_sphere(sphere_center, sphere_radius, ray);

	if (hit_record.t < rtiaw::infinity) { // hit_record is initialized with t = infinity
		return 0.5 * (hit_record.normal + Color3(1, 1, 1));
	}

	// lerp from blue to white depending on Y coordinate, draw sky
	Vec3 normalized_direction = rtiaw::normalize(ray.direction());
	auto t = (normalized_direction.y() + 1.0) * 0.5; // if reach here, that means ray did not hit sphere, so overwrite t with sky value

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

	rtiaw::World world;
	world.addObject(rtiaw::Sphere(Point3(0, 0, -1), 0.5));
	world.addObject(rtiaw::Sphere(Point3(0, -100.5, -1), 100));

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
			
			image_buffer[j * image_width + i] = rtiaw::vec3_to_rgba(ray_color(cast, world));
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
