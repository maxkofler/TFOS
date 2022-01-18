
CC = x86_64-elf-gcc
CC_FLAGS = -g -m32 -ffreestanding -nostdlib -Wall -Wextra -Ikernel/include -Ikenrel/include/libc
CXX = x86_64-elf-g++
CXX_FLAGS = -g -m32 -ffreestanding -nostdlib -Wall -Wextra -Ikernel/include -Ikernel//include/libc
LD = x86_64-elf-ld
LD_FLAGS = 
OBJCOPY = x86_64-elf-objcopy

OUTPUT = TFOS.bin
SYMBOLS = TFOS.sym
KERNEL = kernel.bin

C_SOURCES = $(shell find kernel/src/ -type f -name '**.c')
C_OBJECTS = $(patsubst %.c, %.c.o, ${C_SOURCES})

CXX_SOURCES = $(shell find kernel/src/ -type f -name '**.cpp')
CXX_OBJECTS = $(patsubst %.cpp, %.cpp.o, ${CXX_SOURCES})

NASM_SOURCES = $(shell find kernel/src/ -type f -name '**.asm')
NASM_OBJECTS = $(patsubst %.asm, %.asm.o, ${NASM_SOURCES})

all: builddir ${OUTPUT} clean_dev

run: all
	qemu-system-i386 -fda TFOS.bin

debug_run: ${SYMBOLS} all 
	bash -c "qemu-system-i386 -s -S -fda TFOS.bin& < /dev/null"

show:
	@echo $(C_SOURCES) ${CXX_SOURCES}

TFOS: builddir ${OUTPUT}

${OUTPUT}: bootloader.bin ${KERNEL}
	cat $^ > $@

${KERNEL}: build/kernel_entry.o ${C_OBJECTS} ${CXX_OBJECTS} ${NASM_OBJECTS}
	@echo "LD: $^"
	@${LD} -m elf_i386 ${LD_FLAGS} -o $@ -Ttext 0x1000 $^ --oformat binary

${SYMBOLS}: ${C_OBJECTS} ${CXX_OBJECTS} ${NASM_OBJECTS}
	@echo "SYM: $^"
	@${LD} -m elf_i386 ${LD_FLAGS} -o $@ -Ttext 0x1000 $^ --oformat elf32-i386
	@mv ${SYMBOLS} ${SYMBOLS}.elf
	@${OBJCOPY} ${SYMBOLS}.elf ${SYMBOLS}
	@rm ${SYMBOLS}.elf

build/kernel_entry.o: kernel/kernel_entry.asm
	nasm $< -f elf -o $@

%.c.o: %.c
	@echo "CC: $^"
	@${CC} ${CC_FLAGS} -c $^ -o $@

%.cpp.o: %.cpp
	@echo "CXX: $^"
	@${CXX} ${CXX_FLAGS} -c $^ -o $@

%.asm.o: %.asm	
	@echo "NASM: $^"
	@nasm $^ -f elf -o $@

bootloader.bin: bootloader/mbr.asm
	nasm $< -f bin -o $@

builddir:
	@-mkdir build/

clean: clean_dev
	@-rm -rf ${OUTPUT}

clean_dev:
	@-rm -rf ${C_OBJECTS} ${CXX_OBJECTS} ${NASM_OBJECTS} ${KERNEL} bootloader.bin build/