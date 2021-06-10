all:
	make build
	make iso

build:
	-mkdir build
	gcc -c src/kernel/kernel.c -o build/kernel.o -ffreestanding -m32 -Wall -Wextra
	gcc -c boot.s -o build/boot.o -m32
	gcc -T linker.ld -o build/tfos.bin -ffreestanding -nostdlib build/boot.o build/kernel.o -static -m32

iso:
	make test
	-mkdir -p iso/boot/grub
	cp build/tfos.bin iso/boot/tfos.bin
	cp grub.cfg iso/boot/grub/grub.cfg
	grub-mkrescue -o tfos.iso iso

test:
	sh multibootTest.sh

boot:
	make clean
	make all
	qemu-system-x86_64 -cpu pentium2 -cdrom tfos.iso

clean:
	rm -rf build iso *.iso
