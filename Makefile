all: builddir tfos.bin

builddir:
	-mkdir build

C_SRC = $(shell find src/ -type f -name '*.c')
CPP_SRC = $(shell find src/ -type f -name '*.cpp')
GAS_SRC = $(shell find src/ -type f -name '*.S')
NASM_SRC = $(shell find src/ -type f -name '*.asm')

INCLUDE = -Iinclude/

C_FLAGS = -Wall -ffreestanding -m32
CPP_FLAGS = -Wall -ffreestanding -m32
GAS_FLAGS = -Wall -ffreestanding -m32

LD_FLAGS = -nostdlib -ffreestanding -nostartfiles -lgcc -fno-exceptions -fno-rtti -m32

C_OBJ = $(C_SRC:.c=.c.o)
CPP_OBJ = $(CPP_SRC:.cpp=.cpp.o)
GAS_OBJ = $(GAS_SRC:.S=.S.o)
NASM_OBJ = $(NASM_SRC:.asm=.asm.o)


%.c.o: %.c builddir
	gcc $(C_FLAGS) $(INCLUDE) -c $< -o $@

%.cpp.o: %.cpp builddir
	g++ $(CPP_FLAGS) $(INCLUDE) -c $< -o $@

%.S.o: %.S builddir
	gcc $(GAS_FLAGS) $(INCLUDE) -c $< -o $@

%.asm.o: %.asm builddir
	nasm $< -o $@

clean:
	rm -f $(C_OBJ) $(CPP_OBJ) $(GAS_OBJ) $(NASM_OBJ)

tfos.bin: $(C_OBJ) $(CPP_OBJ) $(GAS_OBJ) $(NASM_OBJ)
	gcc -T linker.ld $(LD_FLAGS) -o build/tfos.bin $^ $(CFLAGS)