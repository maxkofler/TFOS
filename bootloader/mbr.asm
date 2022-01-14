;use 16 bits here
[bits 16]
[org 0x7c00]

;Kernel code starts here
KERNEL_OFFSET equ 0x1000

;Boot drive is in 'dl' reguster, store it
mov [BOOT_DRIVE], dl

;Stack
mov bp, 0x9000
mov sp, bp

;Load kernel into memory
call load_kernel
call switch_32_bit

jmp $

%include "bootloader/disk_load.asm"
%include "bootloader/gdt.asm"
%include "bootloader/switch_32_bit.asm"

;Loads the kernel into memory
[bits 16]
load_kernel:
	mov bx, KERNEL_OFFSET		;Load the kernel offset
	mov dh, 2					;Load 2 sectors				TODO: kernel could be larger!
	mov dl, [BOOT_DRIVE]		;Set the boot disk
	call disk_load				;Now load from disk
	ret

[bits 32]
ENTRY_32BIT:
	call KERNEL_OFFSET			;Jump to the kernel
	jmp $						;Loop in case the kernel should return (normally never)


;Variable for storing boot drive
BOOT_DRIVE db 0

;Fill empty space
times 510 - ($-$$) db 0
dw 0xaa55						;Magic number for bootloader