// ArcadeOS Kernel (Multiboot Compatible)
#include <stdint.h>
#include "arch/gdt.h"
#include "arch/idt.h"
#include "arch/isr.h"
#include "arch/pic.h"
#include "vga.h"
#include "timer.h"
#include "shell.h"
#include "drivers/keyboard.h"
#include "memory/pmm.h"
#include "memory/paging.h"

void print_hex(uint32_t val, int row) {
    char buf[11];
    buf[0] = '0';
    buf[1] = 'x';
    const char* hexchars = "0123456789ABCDEF";
    for (int i = 0; i < 8; i++) {
        buf[2 + i] = hexchars[(val >> (28 - i * 4)) & 0x0F];
    }
    buf[10] = '\0';
    print_line(buf, row);
}

__attribute__((section(".multiboot")))
unsigned long multiboot_header[] =
{
    0x1BADB002,
    0x00000000,
    0xE4524FFE
};

void kmain(void) {
    // Initialize GDT
    init_gdt();

    // Initialize IDT
    init_idt();

    // Initialize ISR Exception & IRQ gates
    init_isr();

    // Initialize Keyboard driver
    init_keyboard();

    // Initialize Timer driver
    init_timer();

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

    // Unmask IRQ0 (Timer) and IRQ1 (Keyboard) on Master PIC
    // 0xFC = 11111100b -> Unmasks IRQ0 (bit 0) and IRQ1 (bit 1)
    outb(PIC1_DATA, 0xFC);
    outb(PIC2_DATA, 0xFF);

    // Enable hardware interrupts
    asm volatile ("sti");

    print_line("1. START GAME", 7);
    print_line("2. SETTINGS", 8);
    print_line("3. EXIT", 9);
    print_line("Type below to verify Keyboard IRQ1:", 11);

    // Initialize paging (which runs pmm_init with exclusions)
    init_paging();

    // Initialize shell and display prompt
    init_shell();

    while (1) {
        asm("hlt");
    }
}
