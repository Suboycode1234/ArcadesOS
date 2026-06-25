// ArcadeOS Kernel (Multiboot Compatible)
#include <stdint.h>
#include "arch/gdt.h"
#include "arch/idt.h"

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

void kmain(void) {
    // Initialize GDT
    init_gdt();

    // Initialize IDT
    init_idt();

    clear_screen();

    print_line("=== ARCADE OS ===", 0);
    print_line("GDT Loaded Successfully!", 1);
    print_line("IDT Loaded Successfully!", 2);
    print_line("1. START GAME", 4);
    print_line("2. SETTINGS", 5);
    print_line("3. EXIT", 6);

    while (1) {
        asm("hlt");
    }
}