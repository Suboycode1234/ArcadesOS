.code16
.global _start

_start:
    cli

    mov $msg, %si

print:
    lodsb
    cmp $0, %al
    je hang

    mov $0x0E, %ah
    int $0x10
    jmp print

hang:
    jmp hang

msg:
    .ascii "ArcadeOS BOOT OK"
    .byte 0

.org 510
.word 0xAA55