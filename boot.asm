ORG 0
BITS 16

jmp 0x7c0:start ; jumping to segment 0x7c0 to set code segment

start:
	; setting the interrupt 0
	mov word [0x0], divide_by_zero_handler ; set offset
	mov word [0x2], 0x7c0	; set segment

	cli ; clear interrupts
	mov ax, 0x7c0
	mov ds, ax ; setting the data segment
	mov es, ax ; setting the extra segment
	mov ax, 0x0
	mov ss, ax ; setting the stack segment
	mov sp, 0x7c00 ; setting the stack pointer
	sti ; restore the interrupts

	call read_from_disk ; read sector from disk
	
	mov si, 0x1000
	call print ; printing the string loaded from sector 2

	jmp $

read_from_disk:
	mov ah, 0x2
	mov al, 1 ; read one sector
	mov cl, 2 ; start from the second sector
	mov bx, 0x1000 ; offset where the data will be loaded
	int 0x13
	ret

divide_by_zero_handler:
	mov si, error
	call print
	iret

print_char:
  mov ah, 0xE
  int 0x10
  ret

print:
  mov al, [si]
  call print_char
  inc si
  cmp al, 0
  jne print
  ret

message: db "JeremyCodes bootloader !", 0
error: db "Error !", 0

times 510-($ - $$) db 0
dw 0xAA55
