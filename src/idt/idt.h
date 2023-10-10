#ifndef IDT_H
#define IDT_H
#include "config.h"
#include "memory/memory.h"
#include <stdint.h>

struct idtr_desc
{
    uint16_t limit;
    uint32_t base;
} __attribute__((packed));

struct idt_desc
{
    uint16_t offset_low;
    uint16_t selector;
    uint8_t zero;
    uint8_t type_attributes;
    uint16_t offset_high;
} __attribute__((packed));

void idt_set(int interrupt_no, void *address);
void idt_init(void);
void enable_interrupts();
void disable_interrupts();
#endif