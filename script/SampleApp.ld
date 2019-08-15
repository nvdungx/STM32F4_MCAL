/*******************************************************************************
* File:         SampleApp.ld
* Revision:
* Author:
* Date:         02.08.2019
* Description:  ARM linker script
*******************************************************************************/

OUTPUT_FORMAT("elf32-littlearm","elf32-bigarm","elf32-littlearm")
OUTPUT_ARCH(arm)
ENTRY(__user_reset_init)

MEMORY
{
  /* Flash section store RO data, code, executable */
  FLASH (rx)  : ORIGIN = 0x08000000,        LENGTH = 0x20000
  /* SRAM store RW data(global var, bss, executable code) */
  SRAM  (rwx) : ORIGIN = 0x20000000, LENGTH = 0xFFFF
  /* Stack section, grow down ward*/
  STACK (rw)  : ORIGIN = 0x2000FFFF, LENGTH = 0K
}

SECTIONS
{
  .text :
  {
    . = ALIGN(4);
    /* Keep vector table in start address */
    /* When link-time garbage collection is in use (‘--gc-sections’),
    it is often useful to mark sections that should not be eliminated */
    KEEP(*(.vectortable_area))
    /* follow by code .text from any file "*" */
    *(.text)
  } >FLASH

  .rodata :
  {
    /* data used to init global variable and const value */
    *(.rodata.*)
  } >FLASH

  .data_flash :
  {
    . = ALIGN(4);
    _DATA_FLASH_BEGIN = .;
    *(.data.*)
    . = ALIGN(4);
    _DATA_FLASH_END = .;
  } >FLASH

  .data_ram :
  {
    . = ALIGN(4);
    _DATA_RAM_BEGIN = .;
    *(.data.*)
    . = ALIGN(4);
    _DATA_RAM_END = _DATA_RAM_BEGIN + SIZEOF(.data_flash);
  } >SRAM

  .bss :
  {
    . = ALIGN(4);
    _BSS_BEGIN = _DATA_RAM_END;
    *(.bss.*)
    . = ALIGN(4);
    _BSS_END = .;
  } >SRAM

  .stack :
  {
    _USER_STACK = .;
  } >STACK
}
