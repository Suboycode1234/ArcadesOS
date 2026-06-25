#include "isr.h"
#include "idt.h"

// Declare external assembly stubs
extern void isr0();
extern void isr1();
extern void isr2();
extern void isr3();
extern void isr4();
extern void isr5();
extern void isr6();
extern void isr7();
extern void isr8();
extern void isr9();
extern void isr10();
extern void isr11();
extern void isr12();
extern void isr13();
extern void isr14();
extern void isr15();
extern void isr16();
extern void isr17();
extern void isr18();
extern void isr19();
extern void isr20();
extern void isr21();
extern void isr22();
extern void isr23();
extern void isr24();
extern void isr25();
extern void isr26();
extern void isr27();
extern void isr28();
extern void isr29();
extern void isr30();
extern void isr31();

// VGA print function defined in kernel.c
extern void print_line(const char* str, int row);

const char *exception_messages[] = {
    "EXCEPTION 0: Division By Zero",
    "EXCEPTION 1: Debug Exception",
    "EXCEPTION 2: Non Maskable Interrupt",
    "EXCEPTION 3: Breakpoint Exception",
    "EXCEPTION 4: Into Detected Overflow",
    "EXCEPTION 5: Out of Bounds Exception",
    "EXCEPTION 6: Invalid Opcode Exception",
    "EXCEPTION 7: No Coprocessor Exception",
    "EXCEPTION 8: Double Fault Exception",
    "EXCEPTION 9: Coprocessor Segment Overrun",
    "EXCEPTION 10: Bad TSS Exception",
    "EXCEPTION 11: Segment Not Present Exception",
    "EXCEPTION 12: Stack Fault Exception",
    "EXCEPTION 13: General Protection Fault",
    "EXCEPTION 14: Page Fault Exception",
    "EXCEPTION 15: Unknown Interrupt Exception",
    "EXCEPTION 16: Coprocessor Fault Exception",
    "EXCEPTION 17: Alignment Check Exception",
    "EXCEPTION 18: Machine Check Exception",
    "EXCEPTION 19: Reserved Exception",
    "EXCEPTION 20: Reserved Exception",
    "EXCEPTION 21: Reserved Exception",
    "EXCEPTION 22: Reserved Exception",
    "EXCEPTION 23: Reserved Exception",
    "EXCEPTION 24: Reserved Exception",
    "EXCEPTION 25: Reserved Exception",
    "EXCEPTION 26: Reserved Exception",
    "EXCEPTION 27: Reserved Exception",
    "EXCEPTION 28: Reserved Exception",
    "EXCEPTION 29: Reserved Exception",
    "EXCEPTION 30: Reserved Exception",
    "EXCEPTION 31: Reserved Exception"
};

void init_isr()
{
    // Wire all 32 stubs into the IDT (selector 0x08, flags 0x8E for interrupt gate)
    idt_set_gate(0, (uint32_t)isr0, 0x08, 0x8E);
    idt_set_gate(1, (uint32_t)isr1, 0x08, 0x8E);
    idt_set_gate(2, (uint32_t)isr2, 0x08, 0x8E);
    idt_set_gate(3, (uint32_t)isr3, 0x08, 0x8E);
    idt_set_gate(4, (uint32_t)isr4, 0x08, 0x8E);
    idt_set_gate(5, (uint32_t)isr5, 0x08, 0x8E);
    idt_set_gate(6, (uint32_t)isr6, 0x08, 0x8E);
    idt_set_gate(7, (uint32_t)isr7, 0x08, 0x8E);
    idt_set_gate(8, (uint32_t)isr8, 0x08, 0x8E);
    idt_set_gate(9, (uint32_t)isr9, 0x08, 0x8E);
    idt_set_gate(10, (uint32_t)isr10, 0x08, 0x8E);
    idt_set_gate(11, (uint32_t)isr11, 0x08, 0x8E);
    idt_set_gate(12, (uint32_t)isr12, 0x08, 0x8E);
    idt_set_gate(13, (uint32_t)isr13, 0x08, 0x8E);
    idt_set_gate(14, (uint32_t)isr14, 0x08, 0x8E);
    idt_set_gate(15, (uint32_t)isr15, 0x08, 0x8E);
    idt_set_gate(16, (uint32_t)isr16, 0x08, 0x8E);
    idt_set_gate(17, (uint32_t)isr17, 0x08, 0x8E);
    idt_set_gate(18, (uint32_t)isr18, 0x08, 0x8E);
    idt_set_gate(19, (uint32_t)isr19, 0x08, 0x8E);
    idt_set_gate(20, (uint32_t)isr20, 0x08, 0x8E);
    idt_set_gate(21, (uint32_t)isr21, 0x08, 0x8E);
    idt_set_gate(22, (uint32_t)isr22, 0x08, 0x8E);
    idt_set_gate(23, (uint32_t)isr23, 0x08, 0x8E);
    idt_set_gate(24, (uint32_t)isr24, 0x08, 0x8E);
    idt_set_gate(25, (uint32_t)isr25, 0x08, 0x8E);
    idt_set_gate(26, (uint32_t)isr26, 0x08, 0x8E);
    idt_set_gate(27, (uint32_t)isr27, 0x08, 0x8E);
    idt_set_gate(28, (uint32_t)isr28, 0x08, 0x8E);
    idt_set_gate(29, (uint32_t)isr29, 0x08, 0x8E);
    idt_set_gate(30, (uint32_t)isr30, 0x08, 0x8E);
    idt_set_gate(31, (uint32_t)isr31, 0x08, 0x8E);
}

void isr_handler(registers_t regs)
{
    if (regs.int_no < 32)
    {
        print_line("=== CPU EXCEPTION DETECTED ===", 10);
        print_line(exception_messages[regs.int_no], 11);
        print_line("System Halted cleanly.", 12);
        while (1)
        {
            asm("hlt");
        }
    }
}
