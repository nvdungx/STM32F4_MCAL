/*******************************************************************************
* The startup code must be linked at the start of ROM which is NOT necessarily
* address zero
*/
  .syntax unified
  .arch armv7-m

  .section .stack
  .align  3
#ifdef __STACK_SIZE
  .equ  Stack_Size, __STACK_SIZE
#else
  .equ  Stack_Size, 0x00000400
#endif
  .globl  __StackTop
  .globl  __StackLimit
__StackLimit:
  .space  Stack_Size
  .size  __StackLimit, . - __StackLimit
__StackTop:
  .size  __StackTop, . - __StackTop

  .text
  .thumb
  .thumb_func
  .align 2
  .global __user_reset_init
  .func   __user_reset_init
  .type   __user_reset_init, %function
__user_reset_init:
/*  Single BSS section scheme.
 *
 *  The BSS section is specified by following symbols
 *    __bss_begin__: start of the BSS section.
 *    __bss_end__: end of the BSS section.
 *
 *  Both addresses must be aligned to 4 bytes boundary.
 */
    ldr r1, =__bss_begin__
    ldr r2, =__bss_end__

    movs r0, 0
.L_loop3:
    cmp r1, r2
    itt lt
    strlt r0, [r1], #4
    blt .L_loop3

/*  Single section scheme.
 *
 *  The ranges of copy from/to are specified by following symbols
 *    __data_flash_end__: LMA of start of the section to copy from. Usually end of text
 *    __data_ram_begin__: VMA of start of the section to copy to
 *    __data_ram_end__: VMA of end of the section to copy to
 *
 *  All addresses must be aligned to 4 bytes boundary.
 */
    ldr r1, =__data_flash_end__
    ldr r2, =__data_ram_begin__
    ldr r3, =__data_ram_end__

.L_loop1:
    cmp r2, r3
    ittt lt
    ldrlt r0, [r1], #4
    strlt r0, [r2], #4
    blt .L_loop1

/* Call system initialize function then call user main */
    bl System_Init
    bl main
    // ldr r12, =main
    // mov lr, pc
    // bx r12
    wfi
    b .
