#ifndef PMM_H
#define PMM_H

#include <stdint.h>

// End symbol defined in linker.ld
extern uint32_t _kernel_end;

void pmm_init(uint32_t paging_start, uint32_t paging_end);
uint32_t pmm_alloc_frame();
void pmm_free_frame(uint32_t addr);

#endif
