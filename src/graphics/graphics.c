#include "graphics/graphics.h"

uint8_t *VRAM = (uint8_t *)0xA0000;
uint8_t DOUBLE_BUFFER[VGA_HEIGHT*VGA_WIDTH];

void blit_buffer(void)
{
    for (int i = 0; i < VGA_WIDTH * VGA_HEIGHT; i++)
    {
        VRAM[i] = DOUBLE_BUFFER[i];
    }
}

void set_pixel(uint16_t x, uint16_t y, uint8_t color)
{
    uint8_t *pixel = DOUBLE_BUFFER + y * VGA_WIDTH + x;
    *pixel = color;
}

void fill_rect(uint16_t x, uint16_t y, uint16_t w, uint16_t h, uint8_t color)
{
    uint8_t *pixel = DOUBLE_BUFFER + y * VGA_WIDTH + x;
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
        DOUBLE_BUFFER[i] = color;
    }
}

static int abs(int n)
{
    return n < 0 ? -n : n;
}

void			draw_line(uint32_t x1, uint32_t y1, uint32_t x2, uint32_t y2, uint8_t color)
{
	int	s[2];
	int d[2];
	int err;
	int e2;

    d[0] = abs(x2 - x1);
	s[0] = x1 < x2 ? 1 : -1;
	d[1] = abs(y2 - y1);
	s[1] = y1 < y2 ? 1 : -1;
	err = (d[0] > d[1] ? d[0] : -d[1]) / 2;
	while (1)
	{
		set_pixel(x1, y1, color);
		if (x1 == x2 && y1 == y2)
			break ;
		e2 = err;
		if (e2 > -d[0])
		{
			err -= d[1];
			x1 += s[0];
		}
		if (e2 < d[1])
		{
			err += d[0];
			y1 += s[1];
		}
	}
}