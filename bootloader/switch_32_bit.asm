
;Routine to switch to 32-bit protected mode
[bits 16]
switch_32_bit:
	cli						;Disable interrupts
	lgdt [gdt_descriptor]	;Load GDT
	mov eax, cr0
	or eax, 0x1				;Enable protected mode
	mov cr0, eax
	jmp CODE_SEG:init_32	;Far jump

[bits 32]
init_32:
	mov ax, DATA_SEG		;Update segment registers
	mov ds, ax
	mov ss, ax
	mov es, ax
	mov fs, ax
	mov gs, ax

	mov ebp, 0x90000		;Stack
	mov esp, ebp

	call ENTRY_32BIT