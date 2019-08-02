/*******************************************************************************
* The startup code must be linked at the start of ROM which is NOT necessarily
* address zero
*/

  .text
  .code 32

  .global _start
  .func   _start

_start:
  /* Vector table
  * Note: used only very briefly until RAM is remapped to address zero
  */
  B       _reset
