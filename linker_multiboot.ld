ENTRY(_start)

SECTIONS{
	/*Kernels are normally loaded ad 1 MiB*/
	. = 1M;

	/*Put the multiboot header and then the .text section*/
	.text BLOCK(4K) : ALIGN(4K){
		*(.multiboot_header)
		*(.text)
	}

	/*Read only data*/
	.rodata BLOCK(4K) : ALIGN(4K){
		*(.rodata)
	}

	/*Read - write data (initialiazed)*/
	.data BLOCK(4K) : ALIGN(4K){
		*(.data)
	}
	
	/*Read - write data (uninitialiazed)*/
	.data BLOCK(4K) : ALIGN(4K){
		*(COMMON)
		*(.bss)
	}
}