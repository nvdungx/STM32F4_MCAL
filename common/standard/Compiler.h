/*******************************************************************************
* File:         Compiler.h
* Revision:
* Author:
* Date:         02.08.2019
* Description:  Standard AUTOSAR file
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

/* Object declaration macros */
/* memclass is the memory class of the variable itself */
/* ptrclass is the memory class to where the pointer points */
/* ptrtype is the type of the object to where the pointer points */


#define FUNC(rettype, memclass)                     rettype


#define P2VAR(ptrtype, memclass, ptrclass)          ptrtype *


#define P2CONST(ptrtype, memclass, ptrclass)        const ptrtype *


#define CONSTP2VAR(ptrtype, memclass, ptrclass)     ptrtype * const


#define CONSTP2CONST(ptrtype, memclass, ptrclass)   const ptrtype * const


#define P2FUNC(rettype, ptrclass, fctname)          rettype (* fctname)


#define CONST(consttype, memclass)                  const consttype


#define VAR(vartype, memclass)                      vartype

/* To fix MISRA errors */
#define PARAM_UNUSED(param) if ((param) != 0) {}
/*******************************************************************************
Macro definitions - additional project specific macros
*******************************************************************************/
#define DI      __disable_interrupt
#define EI      __enable_interrupt
#define HALT    __halt
#define NOP     __no_operation
#define STOP    __stop

#endif // COMPILER_H
