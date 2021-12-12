// main.cpp: Entry point of application
//
#include <vector>

#include "bitmap.h"
#include "color.h"
#include "vec3.h"

using rtiaw::Vec3;

int main()
{
	const int image_x = 256;
	const int image_y = 256;
	int total_header_size = bitmap::kBMPHeaderSize + bitmap::kDIBHeaderSize;

	bitmap::BMPHeader bmp_header(total_header_size + image_x * image_y * 4, total_header_size);
	bitmap::DIBHeader dib_header(image_x, image_y, 300, 300);

	std::vector<bitmap::Rgba> image_buffer(image_x * image_y); // buffer is read from bottom left to top right

	for (int j = image_y - 1; j >= 0; j--) {
		for (int i = 0; i < image_x; i++) {

			Vec3 color(double(i) / (image_x - 1), double(j) / (image_y - 1), 0.25);
			
			image_buffer[j * image_y + i] = rtiaw::vec3_to_rgba(color);
		}
	}

	bitmap::write_bitmap("output.bmp", &bmp_header, &dib_header, &image_buffer[0], image_x * image_y * 4);

	return 0;
}
