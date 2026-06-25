#include "kmalloc.h"
#include "vga.h"
#include <stdint.h>

#define HEAP_SIZE 1048576 // 1MB static heap

static uint8_t heap[HEAP_SIZE];
static size_t heap_offset = 0;

void* kmalloc(size_t size)
{
    // Round size up to a multiple of 4 to guarantee 4-byte alignment
    size = (size + 3) & ~3;

    // Check for Out Of Memory condition
    if (heap_offset + size > HEAP_SIZE)
    {
        // Out of memory: Print panic message and halt
        clear_screen();
        print_line("KERNEL PANIC: Out of memory", 10);
        print_line("System halted.", 11);
        while (1)
        {
            asm("hlt");
        }
    }

    void* ptr = &heap[heap_offset];
    heap_offset += size;
    return ptr;
}
