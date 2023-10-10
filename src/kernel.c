#include "kernel.h"
#include "terminal/terminal.h"
#include "idt/idt.h"

void kernel_main()
{
	// char str[] = "Hello World\nthis is an example";
	terminal_clear();
	// terminal_putstr(str);
	// terminal_putchar('\n');
	// terminal_putnbr(-1337);

	idt_init();
}
