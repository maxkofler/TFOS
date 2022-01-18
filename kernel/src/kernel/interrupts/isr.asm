SECTION .TEXT
	global isr0
	global isr1
	global isr2
	global isr3
	global isr4
	global isr5
	global isr6
	global isr7
	global isr8
	global isr9
	global isr10
	global isr11
	global isr12
	global isr13
	global isr14
	global isr15
	global isr16
	global isr17
	global isr18
	global isr19
	global isr20
	global isr21
	global isr22
	global isr23
	global isr24
	global isr25
	global isr26
	global isr27
	global isr28
	global isr29
	global isr30
	global isr31

	global irq0
	global irq1
	global irq2
	global irq3
	global irq4
	global irq5
	global irq6
	global irq7

	global irq8
	global irq9
	global irq10
	global irq11
	global irq12
	global irq13
	global irq14
	global irq15

	extern isr_handler
	extern irq_handler

;0 Divide error
isr0:
	push byte 0
	push byte 0
	jmp isr_common_stub

;1 Debug exceptions
isr1:
	push byte 0
	push byte 1
	jmp isr_common_stub

;2 Nonmaskable interrupt
isr2:
	push byte 0
	push byte 2
	jmp isr_common_stub

;3 Breakpoint (one-byte INT 3 instruction)
isr3:
	push byte 0
	push byte 3
	jmp isr_common_stub

;4 Overflow (INTO instruction)
isr4:
	push byte 0
	push byte 4
	jmp isr_common_stub

;5 Bounds check (BOUND instruction)
isr5:
	push byte 0
	push byte 5
	jmp isr_common_stub

;6 Invalid opcode
isr6:
	push byte 0
	push byte 6
	jmp isr_common_stub

;7 Coprocessor not available
isr7:
	push byte 0
	push byte 7
	jmp isr_common_stub

;8 Double fault
isr8:
	;pushed by cpu automatically (always 0)
	push byte 8
	jmp isr_common_stub

;9 (reserved)
isr9:
	push byte 0
	push byte 9
	jmp isr_common_stub

;10 Invalid TSS
isr10:
	;pushed by cpu automatically
	push byte 10
	jmp isr_common_stub

;11 Segment not present
isr11:
	push byte 0
	push byte 11
	jmp isr_common_stub

;12 Stack exception
isr12:
	;pushed by cpu automatically
	push byte 12
	jmp isr_common_stub

;13 General protection
isr13:
	;pushed by cpu automatically
	push byte 13
	jmp isr_common_stub

;14 Page fault
isr14:
	;pushed by cpu automatically
	push byte 14
	jmp isr_common_stub

;15 (reserved)
isr15:
	push byte 0
	push byte 15
	jmp isr_common_stub

;16 Coprecessor error
isr16:
	push byte 0
	push byte 16
	jmp isr_common_stub

;17
isr17:
	push byte 0
	push byte 17
	jmp isr_common_stub

;18
isr18:
	push byte 0
	push byte 18
	jmp isr_common_stub

;19
isr19:
	push byte 0
	push byte 19
	jmp isr_common_stub

;20
isr20:
	push byte 0
	push byte 20
	jmp isr_common_stub
	
;21
isr21:
	push byte 0
	push byte 21
	jmp isr_common_stub

;22
isr22:
	push byte 0
	push byte 22
	jmp isr_common_stub

;23
isr23:
	push byte 0
	push byte 23
	jmp isr_common_stub

;24
isr24:
	push byte 0
	push byte 24
	jmp isr_common_stub

;25
isr25:
	push byte 0
	push byte 25
	jmp isr_common_stub

;26
isr26:
	push byte 0
	push byte 26
	jmp isr_common_stub

;27
isr27:
	push byte 0
	push byte 27
	jmp isr_common_stub

;28
isr28:
	push byte 0
	push byte 28
	jmp isr_common_stub

;29
isr29:
	push byte 0
	push byte 29
	jmp isr_common_stub

;30
isr30:
	push byte 0
	push byte 30
	jmp isr_common_stub

;31
isr31:
	push byte 0
	push byte 31
	jmp isr_common_stub

;	IRQs from PICs
;	Primary PIC
;32
irq0:
	push byte 0
	push byte 32
	jmp irq_common_stub

;
irq1:
	push byte 1
	push byte 33
	jmp irq_common_stub

;
irq2:
	push byte 2
	push byte 34
	jmp irq_common_stub

;
irq3:
	push byte 3
	push byte 35
	jmp irq_common_stub

;
irq4:
	push byte 4
	push byte 36
	jmp irq_common_stub

;
irq5:
	push byte 5
	push byte 37
	jmp irq_common_stub

;
irq6:
	push byte 6
	push byte 38
	jmp irq_common_stub

;
irq7:
	push byte 7
	push byte 39
	jmp irq_common_stub

;	Secondary PIC
;
irq8:
	push byte 8
	push byte 40
	jmp irq_common_stub

;
irq9:
	push byte 9
	push byte 41
	jmp irq_common_stub

;
irq10:
	push byte 10
	push byte 42
	jmp irq_common_stub

;
irq11:
	push byte 11
	push byte 43
	jmp irq_common_stub

;
irq12:
	push byte 12
	push byte 44
	jmp irq_common_stub

;
irq13:
	push byte 13
	push byte 45
	jmp irq_common_stub

;
irq14:
	push byte 14
	push byte 46
	jmp irq_common_stub

;
irq15:
	push byte 15
	push byte 47
	jmp irq_common_stub

irq_common_stub:
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
	call irq_handler

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