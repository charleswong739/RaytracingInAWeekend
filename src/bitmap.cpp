#include "bitmap.h"

#include <fstream>

void bitmap::writeBitmap(const char* filename, const BMPHeader* bmpHeader, const DIBHeader* dibHeader, const Rgba* imageBuffer, unsigned int bufferSize) {
	std::ofstream output(filename, std::ios::binary | std::ios::trunc);

	if (output.is_open())
	{
		output.write((char*)bmpHeader, bitmap::BMP_HEADER_SIZE);
		output.write((char*)dibHeader, bitmap::DIB_HEADER_SIZE);

		output.write((char*)imageBuffer, bufferSize);

		output.close();
	}
}