;Null segment
gdt_start:
	dq 0x0

;Flat memory map, data and code is the same

;Code segment descriptor
gtd_code_seg:
	dw 0xffff		;Segment length (bits 0-15)
	dw 0x0			;Segment base (bits 0-15)
	db 0x0			;Segment base (bits 16-23)
	db 10011010b	;Flags
	db 11001111b	;Flags + segment length (bits 16-19)
	db 0x0			;Segment base (24-31)

;Data segment descriptor
gtd_data_seg:
	dw 0xffff		;Segment length (bits 0-15)
	dw 0x0			;Segment base (bits 0-15)
	db 0x0			;Segment base (bits 16-23)
	db 10010010b	;Flags
	db 11001111b	;Flags + segment length (bits 16-19)
	db 0x0			;Segment base (24-31)

gdt_end:

;Calculate GDT descriptor
gdt_descriptor:
	dw gdt_end-gdt_start-1	;Size of GDT
	dd gdt_start			;Location of GDT

CODE_SEG equ gtd_code_seg - gdt_start
DATA_SEG equ gtd_data_seg - gdt_start