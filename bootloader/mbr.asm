;use 16 bits here
[bits 16]
[org 0x7c00]

jmp bootloader_entry

;DO NOT WRITE ANYTHING ABOVE THAT MOVES THIS NUMBER
global _kernel_len
_kernel_len:
db KERNEL_LEN

_kernel_source:
	KERNEL_LOAD_SOURCE db 0

;Kernel code starts here
KERNEL_OFFSET equ 0x1000



%include "bootloader/kernel_len.asm"

bootloader_entry:
;Boot drive is in 'dl' reguster, store it
mov [BOOT_DRIVE], dl

;Stack
mov bp, 0x9000
mov sp, bp

;Check if the kernel is already loaded from a chainload
mov ax, [0x9c00]
cmp ax, 0xf0f0
;TODO: check if the chainload detection works
je _kernel_chainloaded

;If there was no chainload, load the kernel
mov dl, [BOOT_DRIVE]
mov [_kernel_source], dl
call load_kernel
jmp _continue

_kernel_chainloaded:
	mov byte [_kernel_source], 0xff

_continue:

;Load kernel into memory
call set_video
call switch_32_bit

jmp $

%include "bootloader/disk_load.asm"
%include "bootloader/gdt.asm"
%include "bootloader/switch_32_bit.asm"

;Loads the kernel into memory
[bits 16]
load_kernel:
	mov bx, KERNEL_OFFSET		;Load the kernel offset
	mov dh, KERNEL_LEN			;Load the kernel lenght
	mov dl, [BOOT_DRIVE]		;Set the boot disk
	call disk_load				;Call the subfunction to call the BIOS
	ret

[bits 16]
set_video:

	mov ah, 0					;BIOS set video mode
	mov al, 0x11				;640x480 16col
	int 0x10					;BIOS interrupt
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