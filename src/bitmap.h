#ifndef RTIAW_SRC_BITMAP_H_
#define RTIAW_SRC_BITMAP_H_

#include <stdint.h>

#include <cmath>

namespace bitmap {

	const uint8_t BMP_HEADER_SIZE = 14;
	const uint8_t DIB_HEADER_SIZE = 108;

	struct Rgba {
		uint8_t b, g, r, a;

		Rgba() {}

		Rgba(uint8_t r, uint8_t g, uint8_t b, uint8_t a) :
			r(r), g(g), b(b), a(a){
		}
	};

#pragma pack(push, 1)
	struct BMPHeader {
		uint16_t type;
		uint32_t size;
		uint16_t reserved1;
		uint16_t reserved2;
		uint32_t offset;

		BMPHeader(uint32_t size, uint32_t offset) :
			type(0x4D42), size(size), reserved1(0), reserved2(0), offset(offset) {
		}

	};
#pragma pack(pop)

#pragma pack(push, 1)
	struct DIBHeader {
		uint32_t headerSize;

		uint32_t bmpWidth;
		uint32_t bmpHeight;

		uint16_t colorPlane;
		uint16_t colorDepth;
		uint32_t compression;

		uint32_t rawSize;

		uint32_t resHorizontal;
		uint32_t resVertical;

		uint32_t numColors;
		uint32_t importantColors;

		uint32_t rBitMask;
		uint32_t gBitMask;
		uint32_t bBitMask;
		uint32_t aBitMask;

		uint32_t lcsWinColorSpace;
		uint32_t reserved1[9];
		uint32_t reserved2;
		uint32_t reserved3;
		uint32_t reserved4;

		DIBHeader(uint32_t bmpWidth, uint32_t bmpHeight, uint32_t dpiHorizontal, uint32_t dpiVertical) :
			headerSize(108),
			bmpWidth(bmpWidth), bmpHeight(bmpHeight),
			colorPlane(1), colorDepth(32), compression(3),
			numColors(0), importantColors(0),
			aBitMask(0xFF000000), rBitMask(0x00FF0000), gBitMask(0x0000FF00), bBitMask(0x000000FF),
			lcsWinColorSpace(0x57696E20), // little endian "win"
			reserved2(0), reserved3(0), reserved4(0) {

			rawSize = bmpWidth * bmpHeight * 4;

			resHorizontal = (uint32_t) std::floor(dpiHorizontal * 39.3701 + 0.5);
			resVertical = (uint32_t) std::floor(dpiVertical * 39.3701 + 0.5);
		}
	};
#pragma pack(pop)

	void writeBitmap(const char* filename, const BMPHeader* bmpHeader, const DIBHeader* dibHeader, const Rgba* imageBuffer, unsigned int bufferSize);

}
#endif // !RTIAW_SRC_BITMAP_H_
