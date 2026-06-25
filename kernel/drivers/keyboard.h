#ifndef KEYBOARD_H
#define KEYBOARD_H

#include "arch/isr.h"

void init_keyboard();
void keyboard_handler(registers_t regs);

#endif
