// ArcadeOS Kernel (Multiboot Compatible)
#include <stdint.h>
#include "arch/gdt.h"
#include "arch/idt.h"
#include "arch/isr.h"
#include "arch/pic.h"
#include "drivers/keyboard.h"

__attribute__((section(".multiboot")))
unsigned long multiboot_header[] =
{
    0x1BADB002,
    0x00000000,
    0xE4524FFE
};

#define VGA ((uint16_t*)0xB8000)

void clear_screen() {
    for (int i = 0; i < 80 * 25; i++) {
        VGA[i] = (0x0F << 8) | ' ';
    }
}

void print_line(const char* str, int row) {
    for (int i = 0; str[i] != '\0'; i++) {
        VGA[(row * 80) + i] = (0x0F << 8) | str[i];
    }
}

// Typing cursor state
int cursor_col = 0;
int cursor_row = 12; // Start keyboard inputs printing on line 12

void print_char(char c) {
    if (c == '\n') {
        cursor_row++;
        if (cursor_row > 24) {
            cursor_row = 12;
        }
        cursor_col = 0;
    } else if (c == '\b') {
        if (cursor_col > 0) {
            cursor_col--;
            VGA[(cursor_row * 80) + cursor_col] = (0x0F << 8) | ' ';
        }
    } else {
        VGA[(cursor_row * 80) + cursor_col] = (0x0F << 8) | c;
        cursor_col++;
        if (cursor_col >= 80) {
            cursor_col = 0;
            cursor_row++;
            if (cursor_row > 24) {
                cursor_row = 12;
            }
        }
    }
}

volatile int timer_ticks = 0;
void timer_handler(registers_t regs) {
    timer_ticks++;
    if (timer_ticks % 100 == 0) { // Slower TICK/TOCK output to prevent filling logs too fast
        if ((timer_ticks / 100) % 2 == 0) {
            print_line("Timer status: TICK", 5);
        } else {
            print_line("Timer status: TOCK", 5);
        }
    }
    (void)regs;
}

void kmain(void) {
    // Initialize GDT
    init_gdt();

    // Initialize IDT
    init_idt();

    // Initialize ISR Exception & IRQ gates
    init_isr();

    // Initialize Keyboard driver (registers IRQ1 handler)
    init_keyboard();

    // Remap PIC: Master offset 32, Slave offset 40
    pic_remap(32, 40);

    // Mask all interrupts by default on both PICs
    outb(PIC1_DATA, 0xFF);
    outb(PIC2_DATA, 0xFF);

    clear_screen();

    print_line("=== ARCADE OS ===", 0);
    print_line("GDT Loaded Successfully!", 1);
    print_line("IDT Loaded Successfully!", 2);
    print_line("ISR Exceptions Wired Successfully!", 3);
    print_line("PIC Remapped (IRQ0-15 -> Vectors 32-47)!", 4);

    // Register our timer interrupt handler on IRQ0 (vector 32)
    register_interrupt_handler(32, timer_handler);

    // Unmask IRQ0 (Timer) and IRQ1 (Keyboard) on the Master PIC, keep others masked
    // 0xFC = 11111100b -> Unmasks IRQ0 (bit 0) and IRQ1 (bit 1)
    outb(PIC1_DATA, 0xFC);
    outb(PIC2_DATA, 0xFF);

    // Enable hardware interrupts
    asm volatile ("sti");

    print_line("1. START GAME", 7);
    print_line("2. SETTINGS", 8);
    print_line("3. EXIT", 9);
    print_line("Type below to verify Keyboard IRQ1:", 11);

    while (1) {
        asm("hlt");
    }
}