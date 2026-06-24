all:
	i686-elf-as boot/boot.s -o boot.o
	i686-elf-gcc -ffreestanding -m32 -c kernel/kernel.c -o kernel.o
	i686-elf-ld -T linker.ld -o kernel.elf boot.o kernel.o

run:
	qemu-system-i386 -kernel kernel.elf

clean:
	rm -f *.o *.elf