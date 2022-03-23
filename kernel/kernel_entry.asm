[bits 32]
[extern kernel_main]

;Create the _start symbol for the kernel to make the linker happy
global _start
_start:


call kernel_main
jmp $