
OUTPUT_FORMAT("elf32-littleriscv", "elf32-littleriscv", "elf32-littleriscv")

OUTPUT_ARCH(riscv)

MEMORY
{
  mem   (rwx)	: ORIGIN = 0x00000000, LENGTH = 0x00100000
  heap	(rw)	: ORIGIN = 0x00100000, LENGTH = 0x00200000-0x00100000
  sdram	(rw)	: ORIGIN = 0x40000000, LENGTH = 0x03FFFFFF0
  stack	(rw)	: ORIGIN = 0x03000000, LENGTH = 0x01000000
}

__top_mem				=	ORIGIN(mem) + LENGTH(mem);
__heap_start			=	ORIGIN(heap);
__heap_end				=	ORIGIN(heap) + LENGTH(heap);
__sdram_start			=	ORIGIN(sdram);
__sdram_end				=	ORIGIN(sdram) + LENGTH(sdram);

ENTRY(_start)

SECTIONS
{
	
	.text : ALIGN(4)
	{
		. = 0x0010;
		_start = .;
		. = ALIGN(4);
		*(.init*)
		. = ALIGN(4);
		*(.text.entry)
		. = ALIGN(4);
		*(.text*)
		. = ALIGN(4);
	} > mem

	.rodata : ALIGN(4)
	{
		*(.rodata)
		. = ALIGN(4);
		*(.rodata.*)
		. = ALIGN(4);
	} > mem

	. = ALIGN(4);
	_etext = .;
	. = ALIGN(4);

	.data : ALIGN(4)
	{
		*(.data)
		. = ALIGN(4);
		*(.data.*)
		. = ALIGN(4);
		*(.sdata)
		. = ALIGN(4);
		*(.sdata.*)
		. = ALIGN(4);
	} > mem

	.bss : ALIGN(4)
	{
		_bss = .;
		*(.bss*)
		. = ALIGN(4);
		*(COMMON)
		. = ALIGN(4);
		_ebss = .;
		. = ALIGN(4);
		*(.sbss*)
		. = ALIGN(4);
		_end = .;
	} > mem

	.heap : ALIGN(4)
	{
		__malloc_start = .;

	} > heap

	.sdram : ALIGN(4)
	{

	} > sdram

	_stack_base = 0x03FFFFF0;
}

