#ifndef RTIAW_BITMAP_H_
#define RTIAW_BITMAP_H_

#include <stdint.h>

#include <cmath>

namespace bitmap {

	const uint8_t kBMPHeaderSize = 14;
	const uint8_t kDIBHeaderSize = 108;

	struct Rgba {
		uint8_t b, g, r, a;

		Rgba() {}

		Rgba(uint8_t r, uint8_t g, uint8_t b, uint8_t a)
			: r(r), g(g), b(b), a(a) {}
	};

#pragma pack(push, 1)
	struct BMPHeader {
		uint16_t type;
		uint32_t size;
		uint16_t reserved1;
		uint16_t reserved2;
		uint32_t offset;

		BMPHeader(uint32_t size, uint32_t offset)
			: type(0x4D42), size(size), reserved1(0), reserved2(0), offset(offset) {}

	};
#pragma pack(pop)

#pragma pack(push, 1)
	struct DIBHeader {
		uint32_t header_size;

		uint32_t bmp_width;
		uint32_t bmp_height;

		uint16_t color_plane;
		uint16_t color_depth;
		uint32_t compression;

		uint32_t raw_size;

		uint32_t res_horizontal;
		uint32_t res_vertical;

		uint32_t num_colors;
		uint32_t important_colors;

		uint32_t r_bit_mask;
		uint32_t g_bit_mask;
		uint32_t b_bit_mask;
		uint32_t a_bit_mask;

		uint32_t lcs_win_color_space;
		uint32_t reserved1[9];
		uint32_t reserved2;
		uint32_t reserved3;
		uint32_t reserved4;

		DIBHeader(uint32_t bmpWidth, uint32_t bmpHeight, uint32_t dpiHorizontal, uint32_t dpiVertical)
			: header_size(108), 
			bmp_width(bmpWidth), bmp_height(bmpHeight),
			color_plane(1), color_depth(32), compression(3),
			num_colors(0), important_colors(0),
			a_bit_mask(0xFF000000), r_bit_mask(0x00FF0000), g_bit_mask(0x0000FF00), b_bit_mask(0x000000FF),
			lcs_win_color_space(0x57696E20), // little endian "win"
			reserved2(0), reserved3(0), reserved4(0) {

			raw_size = bmpWidth * bmpHeight * 4;

			res_horizontal = (uint32_t)std::floor(dpiHorizontal * 39.3701 + 0.5);
			res_vertical = (uint32_t)std::floor(dpiVertical * 39.3701 + 0.5);
		}
	};
#pragma pack(pop)

	void write_bitmap(const char* filename, const BMPHeader* bmpHeader, const DIBHeader* dibHeader, const Rgba* imageBuffer, unsigned int bufferSize);

}
#endif // !RTIAW_SRC_BITMAP_H_
