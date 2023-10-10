#include "terminal/terminal.h"

uint16_t *VGA_MEMORY = (uint16_t *)0xB8000;
uint8_t TERMINAL_COL = 0;
uint8_t TERMINAL_ROW = 0;

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
	terminal_put_character(TERMINAL_COL, TERMINAL_ROW, c, 3);
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

void terminal_putnbr(uint32_t number)
{
	if (number == -2147483648)
	{
		terminal_putstr("-2147483648");
		return;
	}
	if (number == 0)
	{
		terminal_putchar('0');
		return;
	}
	else if (number < 0)
	{
		terminal_putchar('-');
		number = -number;
	}
	if (number / 10)
		terminal_putnbr(number / 10);
	terminal_putchar(number % 10 + '0');
}
