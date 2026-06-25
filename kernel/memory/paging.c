#include "paging.h"
#include "pmm.h"

// Page directory (1024 entries, 4KB page-aligned)
static uint32_t page_directory[1024] __attribute__((aligned(4096)));

// First page table (1024 entries, 4KB page-aligned, maps 0MB-4MB)
static uint32_t page_table[1024] __attribute__((aligned(4096)));

// Print helpers defined in main.c
extern void print_line(const char* str, int row);
extern void print_hex(uint32_t val, int row);

void init_paging()
{
    // 1. Initialize the first page table (identity map first 4MB)
    for (int i = 0; i < 1024; i++)
    {
        // Attribute: Present (0x01) + Read/Write (0x02) = 0x03
        page_table[i] = (i * 4096) | 0x03;
    }

    // 2. Initialize the page directory
    // Entry 0 points to our first page table (Attribute: Present + Read/Write = 0x03)
    page_directory[0] = ((uint32_t)page_table) | 0x03;

    // Remaining entries (1 to 1023) are set to 0 (not present)
    for (int i = 1; i < 1024; i++)
    {
        page_directory[i] = 0;
    }

    // 3. Calculate paging structures range for PMM exclusion
    uint32_t paging_start = (uint32_t)page_directory < (uint32_t)page_table ? (uint32_t)page_directory : (uint32_t)page_table;
    uint32_t paging_end = (uint32_t)page_directory < (uint32_t)page_table ? (uint32_t)page_table + 4096 : (uint32_t)page_directory + 4096;

    // 4. Initialize PMM with paging structures range excluded for production
    pmm_init(paging_start, paging_end);

    // 5. Load page directory and enable paging
    load_page_directory(page_directory);
    enable_paging();
}


