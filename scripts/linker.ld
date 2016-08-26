ENTRY(_start)
SECTIONS
{
	. = 0x100000;

	.text :
	{
		*(.multiboot)
		*(.text)
		. = ALIGN(4096);
	}
	.data :
	{
		*(.data)
		*(.rodata)
		. = ALIGN(4096);
	}
	.stab :
	{
		*(.stab)
		. = ALIGN(4096);
	}
	.stabstr :
	{
		*(.stabstr)
		. = ALIGN(4096);
	}
	.bss :
	{
		*(.bss)
		. = ALIGN(4096);
	}

	STACK_TOP = .;
	. = ALIGN(32768);
	KERNEL_CODE_END = .;

	/DISCARD/ : { *(.comment) *(.eh_frame) }
}
