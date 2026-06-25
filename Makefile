all:
	i686-elf-as boot/boot.s -o boot.o
	i686-elf-gcc -ffreestanding -m32 -Ikernel -c kernel/main.c -o main.o
	i686-elf-gcc -ffreestanding -m32 -Ikernel -c kernel/vga.c -o vga.o
	i686-elf-gcc -ffreestanding -m32 -Ikernel -c kernel/timer.c -o timer.o
	i686-elf-gcc -ffreestanding -m32 -Ikernel -c kernel/shell.c -o shell.o
	i686-elf-gcc -ffreestanding -m32 -Ikernel -c kernel/memory/kmalloc.c -o kmalloc.o
	i686-elf-gcc -ffreestanding -m32 -Ikernel -c kernel/memory/pmm.c -o pmm.o
	i686-elf-gcc -ffreestanding -m32 -Ikernel -c kernel/arch/gdt.c -o gdt.o
	i686-elf-gcc -ffreestanding -m32 -Ikernel -c kernel/arch/idt.c -o idt.o
	i686-elf-gcc -ffreestanding -m32 -Ikernel -c kernel/arch/isr.c -o isr_c.o
	i686-elf-as kernel/arch/isr.s -o isr_s.o
	i686-elf-gcc -ffreestanding -m32 -Ikernel -c kernel/arch/pic.c -o pic.o
	i686-elf-gcc -ffreestanding -m32 -Ikernel -c kernel/drivers/keyboard.c -o keyboard.o
	i686-elf-ld -T linker.ld -o kernel.elf boot.o main.o vga.o timer.o shell.o kmalloc.o pmm.o gdt.o idt.o isr_c.o isr_s.o pic.o keyboard.o

run:
	"/c/Program Files/qemu/qemu-system-i386.exe" -kernel kernel.elf

clean:
	rm -f *.o *.elf