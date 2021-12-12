#include "bitmap.h"

#include <fstream>

void bitmap::write_bitmap(const char* filename, const BMPHeader* bmpHeader, const DIBHeader* dibHeader, const Rgba* imageBuffer, unsigned int bufferSize) {
	std::ofstream output(filename, std::ios::binary | std::ios::trunc);

	if (output.is_open())
	{
		output.write((char*)bmpHeader, bitmap::kBMPHeaderSize);
		output.write((char*)dibHeader, bitmap::kDIBHeaderSize);

		output.write((char*)imageBuffer, bufferSize);

		output.close();
	}
}