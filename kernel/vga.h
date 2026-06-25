#ifndef VGA_H
#define VGA_H

#include <stdint.h>

#define VGA ((uint16_t*)0xB8000)

extern int cursor_col;
extern int cursor_row;

void clear_screen();
void print_line(const char* str, int row);
void print_char(char c);

#endif
