#ifndef __PIXEL_ARRAY_H__
#define __PIXEL_ARRAY_H__



#include "led.h"



extern color_t pix_colorz[7];
extern color_t pix_colorx[7];



#define GRID_WIDTH	12
#define GRID_HEIGHT	23
#define GRID_TOTAL	(GRID_WIDTH*GRID_HEIGHT)




class pixelArray : public ws2812b {
public:
	pixelArray(uint8_t led_pin, uint16_t led_width, uint16_t led_height, const uint16_t *led_layout, color_t *led_buffer=NULL)
		:	ws2812b(led_pin, led_width*led_height),
			grid_width( led_width),
			grid_height(led_height) {

		layout	= led_layout;

		grid	= led_buffer
				? led_buffer
				: (color_t*) malloc(total() * sizeof(color_t));
	}




	int16_t index(int8_t x, int8_t y) const {
		if (x < 0  ||  x >= width()  ||  y < 0  ||  y >= height()) return -1;
		return (y * width()) + x;
	}




	INLINE void setPixelColor(uint16_t pos, color_t color) {
		if (pos < total()) grid[pos] = color;
	}




	INLINE color_t getPixelColor(uint16_t pos) const {
		return (pos < total()) ? grid[pos] : color_t::black();
	}




	INLINE color_t *getPixels() {
		return grid;
	}




	INLINE void draw(int8_t x, int8_t y, color_t color) {
		int16_t pos = index(x, y);
		if (pos != -1) setPixelColor(pos, color);
	}




	INLINE color_t read(int8_t x, int8_t y) const {
		int16_t pos = index(x, y);
		return (pos != -1)
			? color_t(getPixelColor(pos))
			: color_t::black();
	}




	color_t swap(int8_t x, int8_t y, color_t color);




	INLINE void symbol(uint8_t c, int8_t x, int8_t y, color_t color) {
		const char z[2] = {c, 0};
		string(z, x, y, color);
	}




	void string(const char *text, int8_t x_offset, int8_t y_offset, color_t color);
	static uint16_t stringWidth(const char *text);




	void show() {
		this->begin();
		for (int y=height()-1; y>=0; y--) {
			uint16_t	row = layout[y];
			int			set = y * width();
			for (int x=0; x<width(); x++) {
				if (row & (1<<x)) {
					if (y & 0x01) {
						pixel(grid[set + ((width() - 1) - x)]);
					} else {
						pixel(grid[set + x]);
					}
				}
			}
		}
		this->end();
	}




	INLINE void clear() {
		memset(grid, 0, this->total() * sizeof(color_t));
	}




	INLINE uint16_t width()		const { return grid_width;	}
	INLINE uint16_t height()	const { return grid_height;	}




protected:
	const uint16_t	grid_width;
	const uint16_t	grid_height;
	const uint16_t	*layout;
	color_t			*grid;
};



#endif //__PIXEL_ARRAY_H__
