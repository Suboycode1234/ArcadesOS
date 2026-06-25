#include "pmm.h"
#include "vga.h"

#define PMM_BITMAP_SIZE 128
static uint8_t pmm_bitmap[PMM_BITMAP_SIZE];

void pmm_free_frame(uint32_t addr)
{
    uint32_t frame = addr / 4096;
    uint32_t byte = frame / 8;
    uint32_t bit = frame % 8;

    if (byte < PMM_BITMAP_SIZE)
    {
        pmm_bitmap[byte] &= ~(1 << bit);
    }
}

void pmm_init(uint32_t paging_start, uint32_t paging_end)
{
    // 1. Mark all frames as used by default (0xFF)
    for (int i = 0; i < PMM_BITMAP_SIZE; i++)
    {
        pmm_bitmap[i] = 0xFF;
    }

    // 2. Walk the 4MB physical address range and free unused frames
    // Keep lower 1MB (0x0 to 0x100000) reserved.
    uint32_t kernel_start = 0x100000;
    
    // Round _kernel_end UP to the nearest 4096-byte page boundary
    uint32_t kernel_end = (((uint32_t)&_kernel_end) + 4095) & ~4095;

    for (uint32_t addr = 0x100000; addr < 0x400000; addr += 4096)
    {
        // Skip if inside kernel image
        if (addr >= kernel_start && addr < kernel_end)
        {
            continue;
        }

        // Skip if inside page directory / tables range
        if (addr >= paging_start && addr < paging_end)
        {
            continue;
        }

        // Free the frame
        pmm_free_frame(addr);
    }
}

uint32_t pmm_alloc_frame()
{
    for (int i = 0; i < PMM_BITMAP_SIZE; i++)
    {
        if (pmm_bitmap[i] != 0xFF)
        {
            for (int bit = 0; bit < 8; bit++)
            {
                if (!(pmm_bitmap[i] & (1 << bit)))
                {
                    pmm_bitmap[i] |= (1 << bit);
                    return (i * 8 + bit) * 4096;
                }
            }
        }
    }
    return 0; // Out of memory
}
