#include "gdt.h"

gdt_entry_t gdt_entries[3];
gdt_ptr_t   gdt_ptr;

// Set the value of one GDT entry
static void gdt_set_gate(int32_t num, uint32_t base, uint32_t limit, uint8_t access, uint8_t gran)
{
    gdt_entries[num].base_low    = (base & 0xFFFF);
    gdt_entries[num].base_middle = (base >> 16) & 0xFF;
    gdt_entries[num].base_high   = (base >> 24) & 0xFF;

    gdt_entries[num].limit_low   = (limit & 0xFFFF);
    gdt_entries[num].granularity = (limit >> 16) & 0x0F;

    gdt_entries[num].granularity |= gran & 0xF0;
    gdt_entries[num].access      = access;
}

void init_gdt()
{
    gdt_ptr.limit = (sizeof(gdt_entry_t) * 3) - 1;
    gdt_ptr.base  = (uint32_t)&gdt_entries;

    // Null descriptor
    gdt_set_gate(0, 0, 0, 0, 0);
    // Code segment: base 0, limit 0xFFFFF, 4KB granularity, 32-bit opcodes, Ring 0
    // Access: 0x9A (10011010b) -> Present, Ring 0, Code, Executable, Readable
    // Granularity: 0xCF (11001111b) -> 4KB granularity, 32-bit protected mode
    gdt_set_gate(1, 0, 0xFFFFF, 0x9A, 0xCF);
    // Data segment: base 0, limit 0xFFFFF, 4KB granularity, 32-bit opcodes, Ring 0
    // Access: 0x92 (10010010b) -> Present, Ring 0, Data, Writable
    gdt_set_gate(2, 0, 0xFFFFF, 0x92, 0xCF);

    gdt_flush((uint32_t)&gdt_ptr);
}
