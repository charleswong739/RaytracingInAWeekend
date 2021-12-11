// main.cpp: Entry point of application
//
#include <iostream>
#include <fstream>
#include <vector>

#include "bitmap.h"

int main()
{
	const int imageX = 256;
	const int imageY = 256;
	int totalHeaderSize = bitmap::BMP_HEADER_SIZE + bitmap::DIB_HEADER_SIZE;

	bitmap::BMPHeader bmpHeader(totalHeaderSize + imageX * imageY * 4, totalHeaderSize);
	bitmap::DIBHeader dibHeader(imageX, imageY, 300, 300);

	std::vector<bitmap::Rgba> imageBuffer(imageX * imageY); // buffer is read from bottom left to top right

	for (int j = imageY - 1; j >= 0; j--) {
		for (int i = 0; i < imageX; i++) {

			uint32_t r = (uint32_t) (255.9999 * (double(i) / (imageX - 1)));
			uint32_t g = (uint32_t) (255.9999 * (double(j) / (imageY - 1)));
			uint32_t b = (uint32_t) (255.9999 * 0.25);
			
			imageBuffer[j * imageY + i] = bitmap::Rgba(r, g, b, 0xFF);
		}
	}

	std::ofstream output("output.bmp", std::ios::binary | std::ios::trunc);

	if (output.is_open())
	{
		output.write((char*)&bmpHeader, bitmap::BMP_HEADER_SIZE);
		output.write((char*)&dibHeader, bitmap::DIB_HEADER_SIZE);

		output.write((char*)&imageBuffer[0], imageX * imageY * 4);

		output.close();
	}

	return 0;
}
