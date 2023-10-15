#include "idt/idt.h"
#include "memory/memory.h"
#include "terminal/terminal.h"
#include "io/io.h"

struct idt_entry    interrupt_descriptor_table[IDT_ENTRIES];

void idt_register(uint32_t interrupt, void *function)
{
    struct idt_entry *entry = &interrupt_descriptor_table[interrupt];

    entry->offset_low = (uint32_t)function & 0x0000ffff;
    entry->selector = KERNEL_CODE_SEGMENT_OFFSET;
    entry->zero = 0;
    entry->type_attributes = 0x8E;
    entry->offset_high = (uint32_t)function >> 16;
}

void idt_load(void *idt);

void int0_handler(void);
void int21_handler(void);
void ozaazaa(void);

void handle_zero(void)
{
    terminal_putchar('#');
}

void idt_init(void)
{
    bzero(interrupt_descriptor_table, sizeof(interrupt_descriptor_table));
    struct idt_ptr  idt_header;

    idt_header.limit = sizeof(interrupt_descriptor_table) - 1;
    idt_header.base = (uint32_t)interrupt_descriptor_table;

    for (int i = 0; i < IDT_ENTRIES; i++)
    {
        idt_register(i, ozaazaa);
    }

    idt_register(0, int0_handler);
    idt_register(0x21, int21_handler);

    idt_load(&idt_header);
}