#include "idt/idt.h"
#include "terminal/terminal.h"
#include "io/io.h"

struct idt_desc idt_descriptors[TOTAL_INTERRUPTS];
struct idtr_desc idtr_descriptor;

extern void idt_load(struct idtr_desc *idtr);

void idt_set(int interrupt_no, void *address)
{
    struct idt_desc *desc = &idt_descriptors[interrupt_no];
    desc->offset_low = (uint32_t) address & 0x0000ffff;
    desc->selector = KERNEL_CODE_SELECTOR;
    desc->zero = 0;
    desc->type_attributes = 0xEE;
    desc->offset_high = (uint32_t) address >> 16;
}

void no_interrupt_handler()
{
    outb(0x20, 0x20);
}

extern void int21h(void);
extern void no_interrupt(void);

void idt_init(void)
{
    bzero(idt_descriptors, sizeof(idt_descriptors));
    idtr_descriptor.limit = sizeof(idt_descriptors) - 1;
    idtr_descriptor.base = (uint32_t) idt_descriptors;

    for (int i = 0; i < TOTAL_INTERRUPTS; i++)
        idt_set(i, no_interrupt);

    idt_set(0x21, int21h);
    
    idt_load(&idtr_descriptor);
}