// main.cpp: Entry point of application
//
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

Color3 ray_color(const Ray& ray) {
	// calculates the color a ray should be

	// lerp from blue to white depending on Y coordinate
	Vec3 normalized_direction = rtiaw::normalize(ray.direction());
	double t = (normalized_direction.y() + 1.0) * 0.5;

	return (1.0 - t) * Color3(1.0, 1.0, 1.0) + t * Color3(0.5, 0.7, 1.0);
}

int main()
{
	// Image setup
	const double aspect_ratio = 16.0f / 9.0f;
	const unsigned int image_width = 1920;
	const unsigned int image_height = (unsigned int)(image_width / aspect_ratio);

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

	// Render
	for (int j = image_height - 1; j >= 0; j--) {
		for (int i = 0; i < image_width; i++) {

			double u = double(i) / (image_width - 1);
			double v = double(j) / (image_height - 1);

			Ray cast(origin, viewport_bottom_left + u * viewport_horizontal + v * viewport_vertical - origin);
			
			image_buffer[j * image_width + i] = rtiaw::vec3_to_rgba(ray_color(cast));
		}
	}

	bitmap::write_bitmap("output.bmp", &bmp_header, &dib_header, &image_buffer[0], total_raw_data_size);

	return 0;
}
