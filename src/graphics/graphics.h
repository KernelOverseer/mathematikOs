#ifndef GRAPHICS_H
#define GRAPHICS_H
#include <stdint.h>

#define VGA_WIDTH 320
#define VGA_HEIGHT 200

extern int32_t pos_x;
extern int32_t pos_y;
extern int32_t old_x;
extern int32_t old_y;
extern int32_t speed_x;
extern int32_t speed_y;
extern int32_t acc_x;
extern int32_t acc_y;

void debug_graphics_main();

#endif