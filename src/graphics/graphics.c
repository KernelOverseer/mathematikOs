#include "graphics/graphics.h"

uint8_t *VRAM = (uint8_t *)0xA0000;
int32_t pos_x = VGA_WIDTH/2 - 5;
int32_t pos_y = 50;
int32_t old_x = 0;
int32_t old_y = 0;
int32_t speed_x = 0;
int32_t speed_y = 0;
int32_t acc_x = 0;
int32_t acc_y = 1;



void set_pixel(uint16_t x, uint16_t y, uint8_t color)
{
    uint8_t *pixel = VRAM + y * VGA_WIDTH + x;
    *pixel = color;
}

void fill_rect(uint16_t x, uint16_t y, uint16_t w, uint16_t h, uint8_t color)
{
    uint8_t *pixel = VRAM + y * VGA_WIDTH + x;
    uint16_t i, j;

    for (i = 0; i < h; i++)
    {
        for (j = 0; j < w; j++)
        {
            pixel[j] = color;
        }
        pixel += VGA_WIDTH;
    }
}

void clear_screen(uint8_t color)
{
    for (int i = 0; i < VGA_WIDTH * VGA_HEIGHT; i++)
    {
        VRAM[i] = color;
    }
}

void debug_graphics_main(void)
{
    int iteration = 0;
    int ipf = 5000000;
    while (1)
    {
        if (!(iteration % ipf))
        {
            old_x = pos_x;
            old_y = pos_y;
            speed_x += acc_x;
            speed_y += acc_y;
            pos_x += speed_x;
            pos_y += speed_y;
            if (pos_x < 0)
            {
                pos_x = 0;
                speed_x = -speed_x;
            }
            if (pos_y < 0)
            {
                pos_y = 0;
                speed_y = -speed_y;
            }
            if (pos_x > VGA_WIDTH - 10)
            {
                pos_x = VGA_WIDTH - 10;
                speed_x = -speed_x;
            }
            if (pos_y > VGA_HEIGHT - 10)
            {
                pos_y = VGA_HEIGHT - 10;
                speed_y = -speed_y;
            }

            fill_rect(old_x, old_y, 10, 10, 0x00);
            fill_rect(pos_x, pos_y, 10, 10, 0x0F);
        }
        iteration++;
    }
}