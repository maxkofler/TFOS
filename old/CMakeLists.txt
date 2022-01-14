cmake_minimum_required (VERSION 3.5)

#   SETUP GCC
set (CMAKE_C_FLAGS "-m32 -ffreestanding")

#   SETUP CXX
set (CMAKE_CXX_FLAGS "-m32 -ffreestanding")

#   SETUP GAS
set (CMAKE_ASM_FLAGS "-m32 -ffreestanding")

#   SETUP NASM
set (CMAKE_ASM_NASM_OBJECT_FORMAT elf32)

project (TFOS C CXX ASM ASM_NASM)

set (OUTPUT tfos.bin)

file (GLOB_RECURSE Csources "${PROJECT_SOURCE_DIR}/src/**.c")
file (GLOB_RECURSE CXXsources "${PROJECT_SOURCE_DIR}/src/**.cpp")
file (GLOB_RECURSE ASMsources "${PROJECT_SOURCE_DIR}/src/**.S")
file (GLOB_RECURSE NASMsources "${PROJECT_SOURCE_DIR}/src/**.asm")

include_directories(include)

add_executable(${OUTPUT} ${Csources} ${CXXsources} ${ASMsources} ${NASMsources})

target_link_options(${OUTPUT}
PUBLIC
    -T ${PROJECT_SOURCE_DIR}/linker.ld
    -nostdlib
    -ffreestanding
    -nostartfiles
    -lgcc
    -fno-exceptions
    -fno-rtti
	-fPIE
	-m32
)