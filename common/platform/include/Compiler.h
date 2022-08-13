/*******************************************************************************
 * COPYRIGHT
 * -----------------------------------------------------------------------------
 * Copyright (c) 2022 by <<>>. All rights reserved.
 * -----------------------------------------------------------------------------
 * FILE DESCRIPTION
 *  File:         Compiler.h
 *  Component:    <<>>
 *  Module:       <<>>
 *  Generator:    <<>>
 *  Description:  Standard AUTOSAR file(AUTOSAR_SWS_CompilerAbstraction)
 * -----------------------------------------------------------------------------
 * REVISION HISTORY
 * -----------------------------------------------------------------------------
 * Version   Date        Author  Description
 * -----------------------------------------------------------------------------
 * 01.00.00  13/08/2022  Dungnv  Initial version
 * 
*******************************************************************************/

/* [SWS_COMPILER_00004, SWS_COMPILER_00047, SWS_COMPILER_00050] */
#ifndef COMPILER_H
#define COMPILER_H
/*******************************************************************************
Includes
*******************************************************************************/
/* [SWS_COMPILER_00048] */
#include "Compiler_Cfg.h"

#define COMPILER_VENDOR_ID    (0xF0U)
#define COMPILER_MODULE_ID    (198U)

/* AUTOSAR Software Specification Release Version Information */
#define COMPILER_AR_RELEASE_MAJOR_VERSION       (4U)
#define COMPILER_AR_RELEASE_MINOR_VERSION       (4U)
#define COMPILER_AR_RELEASE_REVISION_VERSION    (0U)

/* Component Version Information */
#define COMPILER_SW_MAJOR_VERSION       (1U)
#define COMPILER_SW_MINOR_VERSION       (0U)
#define COMPILER_SW_PATCH_VERSION       (0U)

/*******************************************************************************
Macro definitions - according AUTOSAR
*******************************************************************************/
/* [SWS_COMPILER_00010] */
#define _GREENHILLS_C_STM32_
#define _ADS_C_STM32_
/* [SWS_COMPILER_00030] */

/* [SWS_COMPILER_00053, SWS_COMPILER_00005, SWS_COMPILER_00036, SWS_COMPILER_00046] */
#define AUTOMATIC    /* Memory class for automatic variables */

/* [SWS_COMPILER_00059] */
#define TYPEDEF      /* Memory class for typedef */


#define STATIC    static

/* [SWS_COMPILER_00051] */
#define NULL_PTR  ((void *)0)

/* [SWS_COMPILER_00057] */
#define INLINE    inline /* The compiler abstraction shall provide the INLINE define for abstraction of the keyword inline. */

/* [SWS_COMPILER_00060] */
#define LOCAL_INLINE  static inline


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
/* [SWS_COMPILER_00035, SWS_COMPILER_00001] */
#define FUNC(rettype, memclass) rettype memclass
/* [SWS_COMPILER_00058, SWS_COMPILER_00061, SWS_COMPILER_00062] */
#define FUNC_P2CONST(rettype, ptrclass, memclass)\
  const ptrclass rettype * memclass
/* [SWS_COMPILER_00063, SWS_COMPILER_00064] */
#define FUNC_P2VAR(rettype, ptrclass, memclass) ptrclass rettype * memclass
/* [SWS_COMPILER_00006] */
#define P2VAR(ptrtype, ptrclass, memclass)  ptrclass ptrtype * memclass
/* [SWS_COMPILER_00013] */
#define P2CONST(ptrtype,ptrclass, memclass) const ptrclass ptrtype * memclass
/* [SWS_COMPILER_00031] */
#define CONSTP2VAR(ptrtype, ptrclass, memclass)\
  ptrclass ptrtype * const memclass
/* [SWS_COMPILER_00032] */
#define CONSTP2CONST(ptrtype, ptrclass, memclass)\
  const ptrclass ptrtype * const memclass
/* [SWS_COMPILER_00039] */
#define P2FUNC(rettype, ptrclass, fctname)  ptrclass rettype (* fctname)
/* [SWS_COMPILER_00065] */
#define CONSTP2FUNC(rettype, ptrclass, fctname)\
  ptrclass rettype (* const fctname)
/* [SWS_COMPILER_00023] */
#define CONST(consttype, memclass)  memclass const consttype
/* [SWS_COMPILER_00026] */
#define VAR(vartype, memclass)  memclass vartype

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
