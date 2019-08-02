/*******************************************************************************
* File:         Interrupt_VectorTable.c
* Revision:
* Author:
* Date:         02.08.2019
* Description:  interrupt vector table definition
*******************************************************************************/


typedef void(* const ExecFuncPtr)(void) __irq;
/* Place table in separate section */
#pragma arm section rodata="exceptions_area"
ExecFuncPtr exception_table[] = {
  /* This initial stack pointer address section is define in link file */
  (ExecFuncPtr)&Image$$ARM_LIB_STACKHEAP$$ZI$$Limit,
  /* Initial PC, set to entry point */
  (ExecFuncPtr)__main,
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
  InterruptHandler0,
  InterruptHandler1,
  InterruptHandler2
  /*
  …
  */
};
#pragma arm section