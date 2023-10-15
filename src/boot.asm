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

    sti
    call enable_graphics_mode
    cli

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

	jmp CODE_SEG:load32

enable_graphics_mode:
    ; switching to graphics mode
    mov ah, 0
    mov al, 13h ; for vga 8 bit graphics
    int 0x10
    ret

[BITS 32]
load32:
    mov eax, 1
    mov ecx, 100
    mov edi, 0x0100000
    call ata_lba_read
    jmp CODE_SEG:0x0100000

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

ata_lba_read:
    mov ebx, eax, ; Backup the LBA
    ; Send the highest 8 bits of the lba to hard disk controller
    shr eax, 24
    or eax, 0xE0 ; Select the  master drive
    mov dx, 0x1F6
    out dx, al
    ; Finished sending the highest 8 bits of the lba

    ; Send the total sectors to read
    mov eax, ecx
    mov dx, 0x1F2
    out dx, al
    ; Finished sending the total sectors to read

    ; Send more bits of the LBA
    mov eax, ebx ; Restore the backup LBA
    mov dx, 0x1F3
    out dx, al
    ; Finished sending more bits of the LBA

    ; Send more bits of the LBA
    mov dx, 0x1F4
    mov eax, ebx ; Restore the backup LBA
    shr eax, 8
    out dx, al
    ; Finished sending more bits of the LBA

    ; Send upper 16 bits of the LBA
    mov dx, 0x1F5
    mov eax, ebx ; Restore the backup LBA
    shr eax, 16
    out dx, al
    ; Finished sending upper 16 bits of the LBA

    mov dx, 0x1f7
    mov al, 0x20
    out dx, al

    ; Read all sectors into memory
.next_sector:
    push ecx

; Checking if we need to read
.try_again:
    mov dx, 0x1f7
    in al, dx
    test al, 8
    jz .try_again

; We need to read 256 words at a time
    mov ecx, 256
    mov dx, 0x1F0
    rep insw
    pop ecx
    loop .next_sector
    ; End of reading sectors into memory
    ret

times 510-($ - $$) db 0
dw 0xAA55
