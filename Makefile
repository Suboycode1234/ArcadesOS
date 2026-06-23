all:
	i686-elf-gcc -ffreestanding -m32 -c kernel/kernel.c -o kernel.o
	i686-elf-ld -T linker.ld -o kernel.elf kernel.o
	i686-elf-objcopy -O binary kernel.elf kernel.bin

	i686-elf-as boot/boot.s -o boot.o
	i686-elf-ld -Ttext 0x7C00 --oformat binary boot.o -o boot.bin

	dd if=/dev/zero of=arcadeos.img bs=512 count=2880
	dd if=boot.bin of=arcadeos.img conv=notrunc
	dd if=kernel.bin of=arcadeos.img bs=512 seek=1 conv=notrunc

run:
	"/c/Program Files/qemu/qemu-system-i386.exe" -drive format=raw,file=arcadeos.img

clean:
	rm -f *.o *.bin *.elf *.img