.global _start
.global gdt_flush
.global idt_flush

.extern kmain

.section .text

_start:
    cli
    mov $stack_top, %esp
    call kmain

.hang:
    jmp .hang

# ASM helper to load GDT pointer and flush segments
gdt_flush:
    mov 4(%esp), %eax   # Load the pointer to gdt_ptr from the stack
    lgdt (%eax)          # Load GDT
    mov $0x10, %ax      # Load 0x10 (Data segment selector) into all data registers
    mov %ax, %ds
    mov %ax, %es
    mov %ax, %fs
    mov %ax, %gs
    mov %ax, %ss
    ljmp $0x08, $1f     # Far jump to 0x08 (Code segment selector) to flush cache
1:
    ret                  # Return to caller

# ASM helper to load IDT pointer
idt_flush:
    mov 4(%esp), %eax   # Load the pointer to idt_ptr from the stack
    lidt (%eax)          # Load IDT
    ret

.section .bss
.align 16

stack_bottom:
    .skip 16384
stack_top: