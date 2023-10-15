#include "keyboard/keyboard.h"
#include "terminal/terminal.h"
#include "io/io.h"

char kbd_US [128] =
{
    0,  27, '1', '2', '3', '4', '5', '6', '7', '8', '9', '0', '-', '=', '\b',   
  '\t', /* <-- Tab */
  'q', 'w', 'e', 'r', 't', 'y', 'u', 'i', 'o', 'p', '[', ']', '\n',     
    0, /* <-- control key */
  'a', 's', 'd', 'f', 'g', 'h', 'j', 'k', 'l', ';', '\'', '`',  0, '\\', 'z', 'x', 'c', 'v', 'b', 'n', 'm', ',', '.', '/',   0,
  '*',
    0,  /* Alt */
  ' ',  /* Space bar */
    0,  /* Caps lock */
    0,  /* 59 - F1 key ... > */
    0,   0,   0,   0,   0,   0,   0,   0,
    0,  /* < ... F10 */
    0,  /* 69 - Num lock*/
    0,  /* Scroll Lock */
    0,  /* Home key */
    0,  /* Up Arrow */
    0,  /* Page Up */
  '-',
    0,  /* Left Arrow */
    0,
    0,  /* Right Arrow */
  '+',
    0,  /* 79 - End key*/
    0,  /* Down Arrow */
    0,  /* Page Down */
    0,  /* Insert Key */
    0,  /* Delete Key */
    0,   0,   0,
    0,  /* F11 Key */
    0,  /* F12 Key */
    0,  /* All other keys are undefined */
};

char keys_pressed[128] = {0};

void print_scancode(unsigned char scancode[2])
{
    terminal_putstr(" 0x");
    terminal_puthex(scancode[1]);
    terminal_putstr(", 0x");
    terminal_puthex(scancode[0]);
    terminal_putchar('\n');
}

char get_ascii_from_scancode(unsigned char scancode[2])
{
    unsigned char code = scancode[0] & 0x7F;
    
    if (code < 128)
        return kbd_US[code];
    return 0;
}

uint8_t is_key_pressed(uint8_t keycode)
{
    if (keycode < 128)
        return keys_pressed[keycode];
    return 0;
}

void keyboard_handler(void)
{
    static unsigned char scancode[2] = "\0\0";

    scancode[1] = scancode[0];

    scancode[0] = insb(0x60);
    if (scancode[0] != SCANCODE_SPECIAL)
    {
        if (scancode[1] == SCANCODE_SPECIAL)
        {
            if (scancode[0] & SCANCODE_RELEASED)
            {
                // special key released
                keys_pressed[scancode[0] & 0x7F] = 0;
            }
            else
            {
                // special key pressed
                keys_pressed[scancode[0] & 0x7F] = 1;
            }
        }
        else if (scancode[0] & SCANCODE_RELEASED)
        {
            keys_pressed[scancode[0] & 0x7F] = 0;
        }
        else
        {
            terminal_putchar(get_ascii_from_scancode(scancode));
            keys_pressed[scancode[0] & 0x7F] = 1;
        }
    }
}