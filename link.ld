ENTRY(start)

SECTIONS
{
  . = 0x100000; /* Kernel load address */

  .text : {
    *(.text)
  }

  .rodata : {
    *(.rodata)
  }

  .data : {
    *(.data)
  }

  .bss : {
    *(.bss)
    *(COMMON)
  }
}
