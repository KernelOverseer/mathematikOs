#ifndef KEYBOARD_H
#define KEYBOARD_H
#include <stdint.h>

#define KEYBOARD_DATA_PORT 0x60
#define KEYBOARD_STATUS_PORT 0x64

#define SCANCODE_RELEASED 0x80
#define SCANCODE_SPECIAL 0xE0

#define KEY_W 0x11
#define KEY_A 0x1E
#define KEY_S 0x1F
#define KEY_D 0x20

extern char kbd_US[128];

extern char keys_pressed[128];

uint8_t is_key_pressed(uint8_t keycode);

void keyboard_handler(void);

#endif