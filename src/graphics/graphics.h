#ifndef GRAPHICS_H
#define GRAPHICS_H
#include <stdint.h>

#define VGA_WIDTH 320
#define VGA_HEIGHT 200

void set_pixel(uint16_t x, uint16_t y, uint8_t color);
void fill_rect(uint16_t x, uint16_t y, uint16_t w, uint16_t h, uint8_t color);
void clear_screen(uint8_t color);
void draw_line(uint32_t x1, uint32_t y1, uint32_t x2, uint32_t y2, uint8_t color);
void blit_buffer(void);

#endif