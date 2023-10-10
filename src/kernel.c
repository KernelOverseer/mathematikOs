#include "kernel.h"
#include "graphics/graphics.h"
#include "io/io.h"
#include "idt/idt.h"

void kernel_main()
{
	terminal_clear();
	terminal_putstr("mathematikOs v0.0.1\n");

	idt_init(); // initializing the interrupt descriptor table
	terminal_putstr("[X] IDT initialized\n");

	enable_interrupts();
	terminal_putstr("[X] Interrupts enabled\n");


	terminal_putstr("\n>");
	debug_graphics_main();
}
