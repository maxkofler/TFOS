;use 16 bits here
[bits 16]
[org 0x7c00]

;Kernel code starts here
KERNEL_OFFSET equ 0x1000

;boot drive is in 'dl' reguster, store it
mov [BOOT_DRIVE], dl

;Stack
mov bp, 0x9000
mov sp, bp


BOOT_DRIVE db 0

times 510 - ($-$$) db 0
dw 0xaa55