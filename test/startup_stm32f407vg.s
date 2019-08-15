/*******************************************************************************
* The startup code must be linked at the start of ROM which is NOT necessarily
* address zero
*/
  .syntax  unified
  .arch  armv7e-m
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
 *    _BSS_BEGIN: start of the BSS section.
 *    _BSS_END: end of the BSS section.
 *
 *  Both addresses must be aligned to 4 bytes boundary.
 */
    ldr r1, =_BSS_BEGIN
    ldr r2, =_BSS_END

    movs r0, 0
.L_loop3:
    cmp r1, r2
    itt lt
    strlt r0, [r1], #4
    blt .L_loop3

/*  Single section scheme.
 *
 *  The ranges of copy from/to are specified by following symbols
 *    _DATA_FLASH_BEGIN: LMA of start of the section to copy from. Usually end of text
 *    _DATA_RAM_BEGIN: VMA of start of the section to copy to
 *    __data_end__: VMA of end of the section to copy to
 *
 *  All addresses must be aligned to 4 bytes boundary.
 */
    ldr r1, =_DATA_FLASH_BEGIN
    ldr r2, =_DATA_RAM_BEGIN
    ldr r3, =_DATA_RAM_END

.L_loop1:
    cmp r2, r3
    ittt lt
    ldrlt r0, [r1], #4
    strlt r0, [r2], #4
    blt .L_loop1

/* Call system initialize function then call user main */
//    bl System_Init
    bl main
    wfi
    b .
