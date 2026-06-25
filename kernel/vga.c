#include "vga.h"

int cursor_col = 0;
int cursor_row = 12;

void clear_screen() {
    for (int i = 0; i < 80 * 25; i++) {
        VGA[i] = (0x0F << 8) | ' ';
    }
}

void print_line(const char* str, int row) {
    // Bounds check row parameter - same pattern as cursor_row fix
    if (row > 24) {
        row = 12;
    }
    for (int i = 0; str[i] != '\0'; i++) {
        VGA[(row * 80) + i] = (0x0F << 8) | str[i];
    }
}

void print_char(char c) {
    if (c == '\n') {
        cursor_row++;
        if (cursor_row > 24) {
            cursor_row = 12;
        }
        cursor_col = 0;
    } else if (c == '\b') {
        if (cursor_col > 0) {
            cursor_col--;
            VGA[(cursor_row * 80) + cursor_col] = (0x0F << 8) | ' ';
        }
    } else {
        VGA[(cursor_row * 80) + cursor_col] = (0x0F << 8) | c;
        cursor_col++;
        if (cursor_col >= 80) {
            cursor_col = 0;
            cursor_row++;
            if (cursor_row > 24) {
                cursor_row = 12;
            }
        }
    }
}
