#include "keyboard.h"
#include "arch/pic.h"
#include "arch/isr.h"

// Extern print helper defined in kernel.c
extern void print_char(char c);

// US QWERTY Keyboard Layout Set 1 Scancodes
const char kbdus[128] =
{
    0,  27, '1', '2', '3', '4', '5', '6', '7', '8',	/* 9 */
  '9', '0', '-', '=', '\b',	/* Backspace */
  '\t',			/* Tab */
  'q', 'w', 'e', 'r',	/* 19 */
  't', 'y', 'u', 'i', 'o', 'p', '[', ']', '\n',	/* Enter key */
    0,			/* 29   - Control */
  'a', 's', 'd', 'f', 'g', 'h', 'j', 'k', 'l', ';',	/* 39 */
 '\'', '`',   0,		/* Left shift */
 '\\', 'z', 'x', 'c', 'v', 'b', 'n', 'm', ',', '.', '/',   0, /* Right shift */
  '*',
    0,	/* Alt */
  ' ',	/* Space bar */
    0,	/* Caps lock */
    0,	/* 59 - F1 key ... > */
    0,   0,   0,   0,   0,   0,   0,   0,
    0,	/* < ... F10 */
    0,	/* 69 - Num lock*/
    0,	/* Scroll Lock */
    0,	/* Home key */
    0,	/* Up Arrow */
    0,	/* Page Up */
  '-',
    0,	/* Left Arrow */
    0,
    0,	/* Right Arrow */
  '+',
    0,	/* 79 - End key*/
    0,	/* Down Arrow */
    0,	/* Page Down */
    0,	/* Insert Key */
    0,	/* Delete Key */
    0,   0,   0,
    0,	/* F11 Key */
    0,	/* F12 Key */
    0,	/* All other keys are undefined */
};

void keyboard_handler(registers_t regs)
{
    uint8_t scancode = inb(0x60);

    // If the high bit of the scancode is set, it means a key was just released
    if (scancode & 0x80)
    {
        // Key released - ignore for now
    }
    else
    {
        // Key pressed - translate to ASCII and print to screen
        char c = kbdus[scancode];
        if (c != 0)
        {
            print_char(c);
        }
    }
    (void)regs;
}

void init_keyboard()
{
    // Register the keyboard handler on IRQ1 (vector 33)
    register_interrupt_handler(33, keyboard_handler);
}
