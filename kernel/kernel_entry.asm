[bits 32]
[extern kernel_main]

;A kernel "magic number" for idetifying the kernel start
dw 0xf0f0

;Create the _start symbol for the kernel to make the linker happy
global _start
_start:


call kernel_main
jmp $