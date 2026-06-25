#include "pic.h"

void pic_remap(uint8_t offset1, uint8_t offset2)
{
    uint8_t a1, a2;

    // Save masks
    a1 = inb(PIC1_DATA);
    a2 = inb(PIC2_DATA);

    // Start initialization sequence in cascade mode (ICW1)
    outb(PIC1_CMD, 0x11);
    io_wait();
    outb(PIC2_CMD, 0x11);
    io_wait();

    // Vector offset (ICW2)
    outb(PIC1_DATA, offset1);
    io_wait();
    outb(PIC2_DATA, offset2);
    io_wait();

    // Tell Master PIC that there is a slave PIC at IRQ2 (00000100b = 0x04) (ICW3)
    outb(PIC1_DATA, 0x04);
    io_wait();
    // Tell Slave PIC its cascade identity (00000010b = 0x02) (ICW3)
    outb(PIC2_DATA, 0x02);
    io_wait();

    // Set environment mode to 8086/88 (ICW4)
    outb(PIC1_DATA, 0x01);
    io_wait();
    outb(PIC2_DATA, 0x01);
    io_wait();

    // Restore masks
    outb(PIC1_DATA, a1);
    outb(PIC2_DATA, a2);
}
