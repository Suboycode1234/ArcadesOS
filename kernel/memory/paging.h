#ifndef PAGING_H
#define PAGING_H

#include <stdint.h>
#include "arch/isr.h"

void init_paging();

void load_page_directory(uint32_t* page_dir);
void enable_paging();

void page_fault_handler(registers_t* regs);

#endif
