#include "terminal.h"

uint16_t *VGA_MEMORY = (uint16_t *)0xB8000;
uint8_t	TERMINAL_COL = 0;
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
	if (c == '\b')
	{
		TERMINAL_COL--;
		if (TERMINAL_COL < 0)
		{
			TERMINAL_COL = VGA_COLS - 1;
			TERMINAL_ROW--;
		}
		terminal_put_character(TERMINAL_COL, TERMINAL_ROW, ' ', 0);
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

void terminal_putnbr(int32_t num)
{
    uint32_t n;

    if (num < 0)
    {
        terminal_putchar('-');
        n = -num;
    }
    else
    {
        n = num;
    }
    if (n / 10)
    {
        terminal_putnbr(n / 10);
    }
    terminal_putchar(n % 10 + '0');
}

void terminal_puthex(uint32_t num)
{
    if (num / 16)
        terminal_puthex(num / 16);
    terminal_putchar("0123456789abcdef"[num % 16]);
}