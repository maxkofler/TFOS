;Routine for loading data from disk
;	'bx'	Location to load to
;	'dh'	Amount of sectors to load
;	'dl'	Boot disk to load from
disk_load:
	pusha
	push dx

	mov ah, 0x02				;BIOS call for reading
	mov al, dh					;Amount of sectors to load supplied
	mov cl, 0x02				;Read from sector 2 starting (1 is boot sector)
	mov ch, 0x00				;Read from cylinder 0
	mov dh, 0x00				;Use head 0

	;dl		->		Drive number
	;ex:bx	->		The location to load to

	int 0x13					;Call BIOS interrupt
	jc disk_error				;Carry jump on disk error

	pop dx						;????
	cmp al, dh					;'al' holds sectors actually read, compare to 'dh'
	jne sectors_error			;Error out if load was not complete

	popa
	ret

disk_error:
	jmp disk_error

sectors_error:
	jmp sectors_error