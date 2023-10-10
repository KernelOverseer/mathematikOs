section asm
global idt_load
global int0_handler
global int21_handler
global ozaazaa

extern handle_zero
extern ozaazaa_handler
extern keyboard_handler

idt_load:
    push ebp
    mov ebp, esp

    mov eax, [ebp+8]
    lidt [eax]

    sti
    pop ebp
    ret

ozaazaa:
    mov eax, 0x20
    out 0x20, eax
    iret

int0_handler:
    pushad
    call handle_zero
    mov eax, 0x20
    out 0x20, eax
    popad
    iret

int21_handler:
    pushad
    call keyboard_handler
    mov eax, 0x20
    out 0x20, eax
    popad
    iret