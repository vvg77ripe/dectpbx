
MEMORY
{
	flash 		: org = 0x00000000, len = 0x00080000
	vector_ram	: org = 0x00000000, len = 0x00000400
	sram		: org = 0x10000000, len = 0x00010000
	ipsbar		: org = 0x40000000, len = 0x40000000
}

SECTIONS
{
	.start : {
		./obj/start.o (.text)
		__RAMTEXT_LOAD = .;
	} > flash

	.ramtext : {
		__RAMTEXT_START = .;
		./obj/flash.o (.text)
	} > sram AT> flash

	.text : {
		*(.text)
	} > flash

	.data : {
		*(.rodata)
		*(.data)
		__ROMFS_START = .;
	} > flash

	.bss : {
		__BSS_START = .;
		*(.bss)
		*(COMMON)
		__BSS_END = .;
		__SP_END = .;
		. = . + 4096;
		__SP_INIT = .;
	} > sram

	.ipsbar : {
		__IPSBAR = .;
	} > ipsbar
}

__RAMTEXT_SIZE = SIZEOF(.ramtext);
