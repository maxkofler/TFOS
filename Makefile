CC = i686-elf-gcc
CC_FLAGS = -g -m32 -ffreestanding -nostdlib -Wall -Wextra -Ikernel/include -Ikenrel/include/libc

CXX = i686-elf-g++
CXX_FLAGS = -g -m32 -ffreestanding -nostdlib -Wall -Wextra -Ikernel/include -Ikernel//include/libc

LD = i686-elf-ld
LD_FLAGS = 

AS = i686-elf-as
AS_FLAGS =

OBJCOPY = i686-elf-objcopy

NASM_FLAGS = -Ikernel/

OUTPUT = MONNOS.bin
SYMBOLS = MONNOS.sym

C_SOURCES = $(shell find kernel/src/ -type f -name '**.c')
C_OBJECTS = $(patsubst %.c, %.c.o, ${C_SOURCES})

CXX_SOURCES = $(shell find kernel/src/ -type f -name '**.cpp')
CXX_OBJECTS = $(patsubst %.cpp, %.cpp.o, ${CXX_SOURCES})

NASM_SOURCES = $(shell find kernel/src/ -type f -name '**.asm')
NASM_OBJECTS = $(patsubst %.asm, %.asm.o, ${NASM_SOURCES})

all: builddir ${OUTPUT} clean_dev

run: all
	qemu-system-i386 -fda ${OUTPUT}

debug_run: ${SYMBOLS} all
	bash -c "qemu-system-i386 -s -S -fda ${OUTPUT}&"

show:
	@echo ${C_SOURCES} ${CXX_SOURCES} ${NASM_SOURCES}

MONNOS: builddir ${OUTPUT}

${OUTPUT}: build/boot_multiboot.o ${C_OBJECTS} ${CXX_OBJECTS} ${NASM_OBJECTS}
	@echo "LD: $@"
	@${LD} -T linker.ld ${LD_FLAGS} -o $@ -Ttext 0x1000 $^

${SYMBOLS}: ${C_OBJECTS} ${CXX_OBJECTS} ${NASM_OBJECTS}
	@echo "SYM: $^"
	@${LD} ${LD_FLAGS} -o $@ -Ttext 0x1000 $^
	@mv ${SYMBOLS} ${SYMBOLS}.elf
	@${OBJCOPY} ${SYMBOLS}.elf ${SYMBOLS}
	@rm ${SYMBOLS}.elf

build/boot_multiboot.o: builddir
	@echo "KENTRY NASM: $@"
	@nasm -felf32 kernel/boot_multiboot.asm -o build/boot_multiboot.o

builddir:
	@-mkdir build

%.c.o: %.c
	@echo "CC: $^"
	@${CC} ${CC_FLAGS} -c $^ -o $@

%.cpp.o: %.cpp
	@echo "CXX: $^"
	@${CXX} ${CXX_FLAGS} -c $^ -o $@

%.asm.o: %.asm	
	@echo "NASM: $^"
	@nasm $^ -f elf -o $@

clean: clean_dev
	@-rm -rf ${OUTPUT} ${SYMBOLS}

clean_dev:
	@-rm -rf ${C_OBJECTS} ${CXX_OBJECTS} ${NASM_OBJECTS} ${KERNEL} bootloader.bin build/