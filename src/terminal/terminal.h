#ifndef TERMINAL_H
#define TERMINAL_H
#define VGA_ROWS 25
#define VGA_COLS 80
#include <stdint.h>

void    terminal_clear(void);
void    terminal_putchar(char c);
void    terminal_putstr(char *str);
void    terminal_putnbr(int32_t num);
void    terminal_puthex(uint32_t num);


#endif