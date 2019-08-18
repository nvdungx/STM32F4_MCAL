/*******************************************************************************
* File:         Interrupt_VectorTable.c
* Revision:
* Author:
* Date:         02.08.2019
* Description:  interrupt vector table definition
*******************************************************************************/
#include "Interrupt_VectorTable.h"

// #ifndef __STACK_SIZE
  // #define __STACK_SIZE  0x00000400
// #endif
// static uint8_t stack[__STACK_SIZE] __attribute__ ((aligned(8), used, section(".stack")));


/* You can use __attribute__((section(..))) for functions
  or variables as an alternative to #pragma arm section. */
/* Place table in separate section */
// #pragma arm section rodata="vectortable_area"
// __attribute__((section(".vectortable_area")))
ExecFuncPtr exception_table[] __attribute__((section(".vectortable_area"))) =
{
  /* This initial stack pointer address section is define in link file */
  (ExecFuncPtr)(&_USER_STACK),
  /* Initial PC, set to entry point */
  __user_reset_init,
  NMIException,
  HardFaultException,
  MemManageException,
  BusFaultException,
  UsageFaultException,
  0, 0, 0, 0, /* Reserved */
  SVCHandler,
  DebugMonitor,
  0, /* Reserved */
  PendSVC,SysTickHandler,
  /* Configurable interrupts start here...*/
  dummy_handler,
  dummy_handler,
  dummy_handler
  /*
  …
  */
};
// #pragma arm section