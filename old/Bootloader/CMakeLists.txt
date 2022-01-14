cmake_minimum_required(VERSION 3.7)

set(CMAKE_VERBOSE_MAKEFILE ON)

set(project_name "hello")

set(CMAKE_NASM_LINK_EXECUTABLE "ld   -o  ")
set(CAN_USE_ASSEMBLER TRUE)

set(CMAKE_ASM_NASM_FLAGS "-f bin")
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS}")

set(CMAKE_ASM_NASM_OBJECT_FORMAT elf64)

project(${project_name} ASM_NASM)

enable_language(ASM_NASM)
file (GLOB_RECURSE SOURCE_FILES "src/**.asm")

add_executable(${project_name} ${SOURCE_FILES})
set_target_properties(${project_name} PROPERTIES LINKER_LANGUAGE NASM)