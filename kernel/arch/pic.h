#ifndef PIC_H
#define PIC_H

#include <stdint.h>

// PIC ports
#define PIC1_CMD  0x20
#define PIC1_DATA 0x21
#define PIC2_CMD  0xA0
#define PIC2_DATA 0xA1

// Inline assembly helpers for I/O ports
static inline void outb(uint16_t port, uint8_t val)
{
    asm volatile ("outb %0, %1" : : "a"(val), "Nd"(port));
}

static inline uint8_t inb(uint16_t port)
{
    uint8_t ret;
    asm volatile ("inb %1, %0" : "=a"(ret) : "Nd"(port));
    return ret;
}

static inline void io_wait(void)
{
    // Port 0x80 is unused and safe for I/O delay
    outb(0x80, 0);
}

void pic_remap(uint8_t offset1, uint8_t offset2);

#endif
