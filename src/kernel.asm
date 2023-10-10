[BITS 32]

CODE_SEG equ 0x08
DATA_SEG equ 0x10

global _start
extern kernel_main

_start:

	mov ax,  DATA_SEG
	mov ds,  ax
	mov es,  ax
	mov fs,  ax
	mov gs,  ax
	mov ss,  ax
	mov ebp, 0x00200000
	mov esp, ebp

	; Remap the master PIC
    mov al, 00010001b
    out 0x20, al ; Tell master PIC

    mov al, 0x20 ; Interrupt 0x20 is where master ISR should start
    out 0x21, al

    mov al, 00000001b
    out 0x21, al
    ; End remap of the master PIC

	call kernel_main

    jmp $

times 512-($ - $$) db 0
