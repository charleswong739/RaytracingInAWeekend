﻿// main.cpp: Entry point of application
//
#include <chrono>
#include <iostream>
#include <vector>

#include "bitmap.h"
#include "camera.h"
#include "color.h"
#include "ray.h"
#include "util.h"
#include "vec3.h"
#include "world.h"

using rtiaw::Vec3;
using rtiaw::Point3;
using rtiaw::Color3;
using rtiaw::Ray;

Color3 ray_color(const Ray& ray, const rtiaw::World& world, unsigned int depth) {
	// bounce limit reached, return black, no added color
	if (depth <= 0) {
		return Color3();
	}

	// calculates the color a ray should be
	rtiaw::HitRecord hit_record;
	world.resolve(ray, 0.0001, rtiaw::infinity, hit_record);

	if (hit_record.t < rtiaw::infinity) { // hit_record is initialized with t = infinity
		Point3 bounce_target = hit_record.p + hit_record.normal + rtiaw::random_unit_vector();
		return 0.5 * ray_color(Ray(hit_record.p, bounce_target - hit_record.p), world, depth - 1);
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
	const unsigned int image_height = 720;
	const unsigned int image_width = (unsigned int)std::floor(image_height * aspect_ratio + 0.5);
	const unsigned int samples_per_pixel = 100;
	const unsigned int max_bounces = 20;

	// World setup
	Point3 origin;

	rtiaw::World world;
	world.addObject(rtiaw::Sphere(Point3(0, 0, -1), 0.5));
	world.addObject(rtiaw::Sphere(Point3(0, -100.5, -1), 100));

	// Camera setup
	rtiaw::Camera camera(origin, aspect_ratio, 2.0, 1.0);

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

	unsigned int completion_counter = 0;
	// Render
	for (int j = image_height - 1; j >= 0; j--) {
		for (int i = 0; i < image_width; i++, completion_counter++) {

			// shoot samples_per_pixel number of random rays and average color results
			Color3 pixel_color;
			for (int k = 0; k < samples_per_pixel; k++) {

				double u = (i + rtiaw::random_double()) / (image_width - 1);
				double v = (j + rtiaw::random_double()) / (image_height - 1);

				pixel_color += ray_color(camera.get_ray(u, v), world, max_bounces);
			}

			// find average
			Vec3 averaged_color = rtiaw::clamp(pixel_color / samples_per_pixel, 0.0, 0.999);

			// apply gamma correction for gamma = 2
			Vec3 gamma_corrected = Vec3(sqrt(averaged_color[0]), sqrt(averaged_color[1]), sqrt(averaged_color[2]));

			// write value
			image_buffer[j * image_width + i] = rtiaw::vec3_to_rgba(gamma_corrected);
		}
		//std::cout << "Progress: " << (completion_counter + 0.0) / (image_width * image_height) << "% [" << completion_counter << "/" << image_width * image_height << "]" << std::endl;
	}

	// Time end
	std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();

	std::cout << "Render took: " << (std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count()) / 1000000.0 << "s" << std::endl;
	//std::cout << "Render took: " << (std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count()) / 1000.0 << "ms" << std::endl;
	//std::cout << "Render took: " << std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count() << "\xE6s" << std::endl;
	//std::cout << "Render took: " << std::chrono::duration_cast<std::chrono::nanoseconds> (end - begin).count() << "[ns]" << std::endl;

	bitmap::write_bitmap("output.bmp", &bmp_header, &dib_header, &image_buffer[0], total_raw_data_size);

	return 0;
}
