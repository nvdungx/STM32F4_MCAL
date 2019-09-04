/*******************************************************************************
* File:         Compiler.h
* Revision:
* Author:
* Date:         02.08.2019
* Description:  Standard AUTOSAR file(AUTOSAR_SWS_CompilerAbstraction)
*******************************************************************************/

#ifndef COMPILER_H
#define COMPILER_H

/*******************************************************************************
Macro definitions - according AUTOSAR
*******************************************************************************/


#define AUTOMATIC    /* Memory class for automatic variables */


#define TYPEDEF      /* Memory class for typedef */


#define STATIC    static


#define NULL_PTR  ((void *)0)


#define INLINE    inline

#define LOCAL_INLINE  satic inline


/* Object declaration macros */
/* memclass is the memory class of the variable itself */
/* ptrclass is the memory class to where the pointer points */
/* ptrtype is the type of the object to where the pointer points */
/* #define <PREFIX>_CODE_SLOW @far
   #define <PREFIX>_CODE_FAST @near
   FUNC(void, CAN_CODE_SLOW) Can_Init(void);
   #define SPI_APPL_DATA @far
   #define SPI_VAR_FAST @near
 */
#define FUNC(rettype, memclass)                     rettype memclass

#define FUNC_P2CONST(rettype, ptrclass, memclass)\
  const ptrclass rettype * memclass

#define FUNC_P2VAR(rettype, ptrclass, memclass)      ptrclass rettype * memclass

#define P2VAR(ptrtype, ptrclass, memclass)           ptrclass ptrtype * memclass

#define P2CONST(ptrtype,ptrclass, memclass)   const ptrclass ptrtype * memclass

#define CONSTP2VAR(ptrtype, ptrclass, memclass)\
  ptrclass ptrtype * const memclass

#define CONSTP2CONST(ptrtype, ptrclass, memclass)\
  const ptrclass ptrtype * const memclass

#define P2FUNC(rettype, ptrclass, fctname)          ptrclass rettype (* fctname)

#define CONSTP2FUNC(rettype, ptrclass, fctname)\
  ptrclass rettype (* const fctname)

#define CONST(consttype, memclass)                  memclass const consttype

#define VAR(vartype, memclass)                      memclass vartype

/* To fix MISRA errors */
#define PARAM_UNUSED(param) if ((param) != 0) {}
/*******************************************************************************
Macro definitions - additional project specific macros
*******************************************************************************/
#define DI      __disable_interrupt
#define EI      __enable_interrupt
#define HALT    __halt
#define NOP     __asm("nop")
#define STOP    __stop
#define WFI     __asm("wfi")
#define WFE     __asm("wfe")

#endif // COMPILER_H
