cmake_minimum_required (VERSION 3.5)
project (TFOS)

enable_language(ASM CXX)

set (OUTPUT tfos.bin)

file (GLOB_RECURSE Csources "${PROJECT_SOURCE_DIR}/src/*.c")
file (GLOB_RECURSE CXXsources "${PROJECT_SOURCE_DIR}/src/*.cpp")

include_directories(include)

add_executable(${OUTPUT} "")

target_sources(${OUTPUT}
PRIVATE
    ${Csources}
    ${CXXsources}
    ${PROJECT_SOURCE_DIR}/src/boot.s
)

target_link_options(${OUTPUT}
PUBLIC
    -T ${PROJECT_SOURCE_DIR}/linker.ld
    -nostdlib
    -ffreestanding
    -nostartfiles
    -lgcc
    -fno-exceptions
    -fno-rtti
    -m32
)

target_compile_options(${OUTPUT}
PUBLIC
    -m32
    -ffreestanding
)