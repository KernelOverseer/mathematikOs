ORG 0x7c00
BITS 16

start:	
	mov si, message
	call set_video_mode
	mov cx, 100
	mov dx, 100
_loop:
	call get_keystroke
	cmp ah, 0x4B
	je _left
	cmp ah, 0x48
	je _up
	cmp ah, 0x4D
	je _right
	cmp ah, 0x50
	je _down
	jmp _loop
_right:
	inc cx
	jmp _draw
_left:
	dec cx
	jmp _draw
_up:
	dec dx
	jmp _draw
_down:
	inc dx
_draw:
	call write_pixel
	jmp _loop
	
set_video_mode:
	mov ah, 0x0
	mov al, 0xd
	int 0x10
	ret

write_pixel:
	mov ah, 0xc
	mov al, 255
	int 0x10
	ret

get_keystroke:
	mov ah, 0x0
	int 0x16
	ret

print_char:
	mov ah, 0xE
	int 0x10
	ret

print:
	mov al, [si]
	cmp al, 0
	je _end
	call print_char
	inc si
	jmp print
_end:
	ret

message: db "Hello Bootloader!", 0
times 510 - ($ - $$) db 0
dw 0xAA55
