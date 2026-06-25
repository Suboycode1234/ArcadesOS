.extern isr_handler

# Common ISR stub
isr_common_stub:
    pusha               # Pushes edi, esi, ebp, esp, ebx, edx, ecx, eax

    mov %ds, %ax        # Save the data segment selector
    push %eax

    mov $0x10, %ax      # Load the kernel data segment descriptor
    mov %ax, %ds
    mov %ax, %es
    mov %ax, %fs
    mov %ax, %gs

    call isr_handler

    pop %eax            # Reload the original data segment descriptor
    mov %ax, %ds
    mov %ax, %es
    mov %ax, %fs
    mov %ax, %gs

    popa                # Pops edi, esi, ebp, esp, ebx, edx, ecx, eax
    add $8, %esp        # Cleans up the pushed error code and pushed ISR number
    iret                # pops 5 things at once: CS, EIP, EFLAGS, SS, ESP

# 32 Exception handlers
.global isr0
isr0:
    cli
    push $0
    push $0
    jmp isr_common_stub

.global isr1
isr1:
    cli
    push $0
    push $1
    jmp isr_common_stub

.global isr2
isr2:
    cli
    push $0
    push $2
    jmp isr_common_stub

.global isr3
isr3:
    cli
    push $0
    push $3
    jmp isr_common_stub

.global isr4
isr4:
    cli
    push $0
    push $4
    jmp isr_common_stub

.global isr5
isr5:
    cli
    push $0
    push $5
    jmp isr_common_stub

.global isr6
isr6:
    cli
    push $0
    push $6
    jmp isr_common_stub

.global isr7
isr7:
    cli
    push $0
    push $7
    jmp isr_common_stub

.global isr8
isr8:
    cli
    # CPU pushes error code
    push $8
    jmp isr_common_stub

.global isr9
isr9:
    cli
    push $0
    push $9
    jmp isr_common_stub

.global isr10
isr10:
    cli
    # CPU pushes error code
    push $10
    jmp isr_common_stub

.global isr11
isr11:
    cli
    # CPU pushes error code
    push $11
    jmp isr_common_stub

.global isr12
isr12:
    cli
    # CPU pushes error code
    push $12
    jmp isr_common_stub

.global isr13
isr13:
    cli
    # CPU pushes error code
    push $13
    jmp isr_common_stub

.global isr14
isr14:
    cli
    # CPU pushes error code
    push $14
    jmp isr_common_stub

.global isr15
isr15:
    cli
    push $0
    push $15
    jmp isr_common_stub

.global isr16
isr16:
    cli
    push $0
    push $16
    jmp isr_common_stub

.global isr17
isr17:
    cli
    # CPU pushes error code
    push $17
    jmp isr_common_stub

.global isr18
isr18:
    cli
    push $0
    push $18
    jmp isr_common_stub

.global isr19
isr19:
    cli
    push $0
    push $19
    jmp isr_common_stub

.global isr20
isr20:
    cli
    push $0
    push $20
    jmp isr_common_stub

.global isr21
isr21:
    cli
    push $0
    push $21
    jmp isr_common_stub

.global isr22
isr22:
    cli
    push $0
    push $22
    jmp isr_common_stub

.global isr23
isr23:
    cli
    push $0
    push $23
    jmp isr_common_stub

.global isr24
isr24:
    cli
    push $0
    push $24
    jmp isr_common_stub

.global isr25
isr25:
    cli
    push $0
    push $25
    jmp isr_common_stub

.global isr26
isr26:
    cli
    push $0
    push $26
    jmp isr_common_stub

.global isr27
isr27:
    cli
    push $0
    push $27
    jmp isr_common_stub

.global isr28
isr28:
    cli
    push $0
    push $28
    jmp isr_common_stub

.global isr29
isr29:
    cli
    push $0
    push $29
    jmp isr_common_stub

.global isr30
isr30:
    cli
    push $0
    push $30
    jmp isr_common_stub

.global isr31
isr31:
    cli
    push $0
    push $31
    jmp isr_common_stub
