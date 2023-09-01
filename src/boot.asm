ORG  0x7c00
BITS 16

CODE_SEG equ gdt_code - gdt_start
DATA_SEG equ gdt_data - gdt_start

start:
	cli            ; clear interrupts
	mov ax, 0x0
	mov ds, ax     ; setting the data segment
	mov es, ax     ; setting the extra segment
	mov ss, ax     ; setting the stack segment
	mov sp, 0x7c00 ; setting the stack pointer
	sti            ; restore the interrupts

	call read_from_disk

	cli                   ; disable interrupts
	; enabling A20 line
	in   al,   0x92
	or   al,   2
	out  0x92, al
	; loading the GDT
	lgdt [gdt_descriptor]
	; set PE (Protection Enable) bit in CR0 (Control Register 0)
	mov  eax,  cr0
	or   al,   1
	mov  cr0,  eax

	jmp CODE_SEG:0x7E00

read_from_disk:
	mov ah, 0x2
	mov al, 50    ; read 10 sectors
	mov cl, 2     ; start from the second sector
	mov bx, 0x7E00 ; offset where the data will be loaded
	int 0x13
	ret

message: db "JeremyCodes bootloader !", 0

gdt_start: ; Start of our GDT
gdt_null:  ; First Null GDT entry
    dd 0x0
    dd 0x0

gdt_code: ; CS SHOULD POINT TO THIS
    dw 0xffff    ; Segment limit first 0-15 bits
    dw 0         ; Base first 0-15 bits
    db 0         ; Base 16-23 bits
    db 0x9a      ; Access byte
    db 11001111b ; High 4 bit flags and the low 4 bit limit
    db 0         ; Base 24-31 bits

; offset 0x10
gdt_data: ; DS, SS, ES, FS, GS
    dw 0xffff    ; Segment limit first 0-15 bits
    dw 0         ; Base first 0-15 bits
    db 0         ; Base 16-23 bits
    db 0x92      ; Access byte
    db 11001111b ; High 4 bit flags and the low 4 bit limit
    db 0         ; Base 24-31 bits
; end of the GDT
gdt_end:

; GDT Descriptor
gdt_descriptor:
    dw gdt_end - gdt_start-1
    dd gdt_start
	

times 510-($ - $$) db 0
dw 0xAA55
