all:
	i686-elf-as boot/boot.s -o boot.o
	i686-elf-gcc -ffreestanding -m32 -Ikernel -c kernel/kernel.c -o kernel.o
	i686-elf-gcc -ffreestanding -m32 -Ikernel -c kernel/arch/gdt.c -o gdt.o
	i686-elf-gcc -ffreestanding -m32 -Ikernel -c kernel/arch/idt.c -o idt.o
	i686-elf-ld -T linker.ld -o kernel.elf boot.o kernel.o gdt.o idt.o

run:
	"/c/Program Files/qemu/qemu-system-i386.exe" -kernel kernel.elf

clean:
	rm -f *.o *.elf