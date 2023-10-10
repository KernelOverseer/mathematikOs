#ifndef TERMINAL_H
#define TERMINAL_H
#include <stdint.h>

#define VGA_ROWS 25
#define VGA_COLS 80

extern uint16_t *VGA_MEMORY;
extern uint8_t TERMINAL_COL;
extern uint8_t TERMINAL_ROW;

void terminal_putstr(char *str);
void terminal_putnbr(uint32_t number);
void terminal_putchar(char c);
void terminal_clear();

#endif