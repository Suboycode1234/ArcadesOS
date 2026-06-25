#ifndef TIMER_H
#define TIMER_H

#include "arch/isr.h"

void init_timer();
void timer_handler(registers_t regs);

#endif
