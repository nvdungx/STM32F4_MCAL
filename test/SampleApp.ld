/*******************************************************************************
* File:         SampleApp.ld
* Revision:
* Author:
* Date:         02.08.2019
* Description:  ARM linker script
*******************************************************************************/

OUTPUT_FORMAT("elf32-littlearm","elf32-bigarm","elf32-littlearm")
OUTPUT_ARCH(arm)

MEMORY
{
  /* Flash section store RO data, code, executable */
  FLASH (rx)  : ORIGIN = 0x00000000, LENGTH = 0x20000
  /* SRAM store RW data(global var, bss, executable code) */
  SRAM  (rwx) : ORIGIN = 0x20000000, LENGTH = 0xFFFF
  /* Stack section*/
  STACK (rw)  : ORIGIN = 0x20010000, LENGTH = 0xFFFF
}
/* Linker script to place sections and symbol values. Should be used together
 * with other linker script that defines memory regions FLASH and RAM.
 * It references following symbols, which must be defined in code:
 *   __user_reset_init : Entry of reset handler
 *
 * It defines following symbols, which code can use without definition:
 *   __data_flash_end__
 *   __data_ram_begin__
 *   __data_ram_end__
 *   __bss_begin__
 *   __bss_end__
 */


ENTRY(__user_reset_init)
SECTIONS
{
  .text :
  {
    /* Keep vector table in start address */
    /* When link-time garbage collection is in use (‘--gc-sections’),
    it is often useful to mark sections that should not be eliminated */
    KEEP(*(.vectortable_area))
    /* follow by code .text from any file "*" */
    *(.text*)
    /* data used to init global variable and const value */
    *(.rodata*)
  } >FLASH

  __data_flash_end__ = .;

  .data_ram : AT (__data_flash_end__)
  {
    __data_ram_begin__ = .;
    *(.data*)
    __data_ram_end__ = .;
  } >SRAM

  .bss :
  {
    . = ALIGN(4);
    __bss_begin__ = .;
    *(.bss*)
    *(COMMON)
    . = ALIGN(4);
    __bss_end__ = .;
  } >SRAM

  .stack :
  {
    __StackLimit = .;
    KEEP(*(.stack*))
    __StackTop = .;
  } >STACK

  /* Check if data exceeds RAM limit */
  /* ASSERT((SIZEOF(.bss)+ SIZEOF(.data_ram)) > 65535, "region RAM overflowed data") */

  /* Check if stack exceeds limit */
  /* ASSERT(__StackTop > 0x2001FFFF, "region RAM overflowed with stack") */
}
