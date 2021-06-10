cmake_minimum_required (VERSION 3.5)
project (TFOS)

enable_language(ASM)

set (OUTPUT tfos.bin)

file (GLOB_RECURSE sources "${PROJECT_SOURCE_DIR}/src/*.c")

add_executable(${OUTPUT} "")

include_directories(include)

target_sources(${OUTPUT}
PRIVATE
    ${sources}
    ${PROJECT_SOURCE_DIR}/src/boot.s
)

target_link_options(${OUTPUT}
PUBLIC
    -T ${PROJECT_SOURCE_DIR}/linker.ld
    -nostdlib
    -ffreestanding
    -nostartfiles
    -m32
)

target_compile_options(${OUTPUT}
PUBLIC
    -m32
    -ffreestanding
)