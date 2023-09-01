#include "kernel.h"
#define VGA_ROWS 25
#define VGA_COLS 80
#include <stdint.h>

uint16_t *VGA_MEMORY;
uint8_t	TERMINAL_COL;
uint8_t TERMINAL_ROW;

uint16_t terminal_create_char(char character, char color)
{
	return (character | color << 8);
}

void	terminal_put_character(uint8_t col, uint8_t row, char character, char color)
{
	VGA_MEMORY[VGA_COLS * row + col] = terminal_create_char(character, color);
}

void	terminal_clear()
{
	for (int y = 0; y < VGA_ROWS; y++)
	{
		for (int x = 0; x < VGA_COLS; x++)
		{
			terminal_put_character(x, y, ' ', 0);
		}
	}
}

void terminal_putchar(char c)
{
	if (c == '\n')
	{
		TERMINAL_ROW++;
		TERMINAL_COL = 0;
		return;
	}
	terminal_put_character(TERMINAL_COL, TERMINAL_ROW, c, 10);
	TERMINAL_COL++;
	if (TERMINAL_COL > VGA_COLS)
	{
		TERMINAL_COL = 0;
		TERMINAL_ROW++;
	}
}

void terminal_putstr(char *str)
{
	int i = 0;
	while (str[i])
	{
		terminal_putchar(str[i]);
		i++;
	}
}

void kernel_main()
{
	char str[] = "Hello World\nthis is an example";
	VGA_MEMORY = (uint16_t *)0xB8000;
	TERMINAL_COL = 0;
	TERMINAL_ROW = 0;
	terminal_clear();
	terminal_putstr(str);
}
