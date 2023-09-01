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

	call kernel_main

    jmp $

times 512-($ - $$) db 0
