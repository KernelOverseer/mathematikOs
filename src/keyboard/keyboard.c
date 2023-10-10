#include "keyboard/keyboard.h"
#include "io/io.h"
#include "terminal/terminal.h"
#include "graphics/graphics.h"

uint8_t keyboard_buffer[2] = {0, 0};

void keyboard_handler()
{
    uint8_t scancode = insb(0x60);
    
    keyboard_buffer[1] = keyboard_buffer[0];
    keyboard_buffer[0] = scancode;

    if (keyboard_buffer[0] == 0xE0)
    {
        switch (keyboard_buffer[1])
        {
        case SCANCODE_ARROW_UP:
            terminal_putstr("Up\n");
            break;
        case SCANCODE_ARROW_LEFT:
            speed_x--;
            terminal_putstr("Left\n");
            break;
        case SCANCODE_ARROW_RIGHT:
            speed_x++;
            terminal_putstr("Right\n");
            break;
        case SCANCODE_ARROW_DOWN:
            terminal_putstr("Down\n");
            break;
        default:
            break;
        }
    }

    outb(0x20, 0x20);
}