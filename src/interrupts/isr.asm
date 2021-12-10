

SECTION .TEXT
	global isr0
	extern isr_handler

;Division by zero
isr0:
	push byte 0
	push byte 0
	jmp isr_common_stub

isr_common_stub:
	;Push all the general purpose registers
	pusha

	;Push data segment selector
	mov ax, ds
	push eax

	;Use the kernel data segment TODO: ???
	mov ax, 0x10
	mov ds, ax
	mov es, ax
	mov fs, ax
	mov gs, ax

	;Create the stack for C
	push esp

	;Call c function
	call isr_handler

	;Pop stack pointer
	pop eax

	;Restore segment pointers
	pop eax
	mov ds, ax
	mov es, ax
	mov fs, ax
	mov gs, ax

	;Restore registers
	popa

	;Remove int_no and err_code from stack
	add esp, 8

	;pop cs, eip, eflags, ss and esp
	iret	