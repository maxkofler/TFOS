ENTRY(_start)

SECTIONS
{
  . = 1000;
  .text : { *(.text) }
  .data : { *(.data) }
  .bss : { *(.bss) }
}