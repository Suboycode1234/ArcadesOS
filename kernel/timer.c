#include "timer.h"
#include "vga.h"

volatile int timer_ticks = 0;

void timer_handler(registers_t regs) {
    timer_ticks++;
    if (timer_ticks % 100 == 0) {
        if ((timer_ticks / 100) % 2 == 0) {
            print_line("Timer status: TICK", 5);
        } else {
            print_line("Timer status: TOCK", 5);
        }
    }
    (void)regs;
}

void init_timer() {
    register_interrupt_handler(32, timer_handler);
}
