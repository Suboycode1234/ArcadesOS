.global _start
.global gdt_flush

.extern kmain

.section .text

_start:
    cli
    mov $stack_top, %esp
    call kmain

.hang:
    jmp .hang

gdt_flush:
    mov 4(%esp), %eax
    lgdt (%eax)
    mov $0x10, %ax
    mov %ax, %ds
    mov %ax, %es
    mov %ax, %fs
    mov %ax, %gs
    mov %ax, %ss
    ljmp $0x08, $1f
1:
    ret

.section .bss
.align 16

stack_bottom:
    .skip 16384
stack_top: