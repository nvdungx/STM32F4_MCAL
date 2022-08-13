/*******************************************************************************
 * COPYRIGHT
 * -----------------------------------------------------------------------------
 * Copyright (c) 2022 by <<>>. All rights reserved.
 * -----------------------------------------------------------------------------
 * FILE DESCRIPTION
 *  File:         Compiler_Cfg.h
 *  Component:    <<>>
 *  Module:       <<>>
 *  Generator:    <<>>
 *  Description:  Compiler configuration definition (should be generated from
*                 options of compiler configuration)
 * -----------------------------------------------------------------------------
 * REVISION HISTORY
 * -----------------------------------------------------------------------------
 * Version   Date        Author  Description
 * -----------------------------------------------------------------------------
 * 01.00.00  13/08/2022  Dungnv  Initial version
 * 
*******************************************************************************/


#ifndef __COMPILER_CFG_H__
#define __COMPILER_CFG_H__

/*******************************************************************************
*       CAN MODULE SPECIFIC COMPILER MACRO
*******************************************************************************/
// <INIT_POLICY> is the initialization policy of variables, Variables
/* [SWS_COMPILER_00003, SWS_COMPILER_00040, SWS_COMPILER_00041, SWS_COMPILER_00055, SWS_COMPILER_00054] */
/* VARIABLES */
/* To be used for all global or static variables. */
#define CAN_VAR_NO_INIT             // Used for variables that are never cleared and never initialized.
#define CAN_VAR_CLEARED             // Used for variables that are cleared to zero after every reset.
#define CAN_VAR_POWER_ON_CLEARED    // Used for variables that are cleared to zero only after power on reset.
#define CAN_VAR_INIT                // Used for variables that are initialized with values after every reset.
#define CAN_VAR_POWER_ON_INIT       // Used for variables that are initialized with values only afterpower on reset.
/* To be used for all global or static variables that have at least one of the
* following properties:
*    * accessed bitwise
*    * frequently used
*    * high number of accesses in source  code */
#define CAN_VAR_FAST_NO_INIT
#define CAN_VAR_FAST_CLEARED
#define CAN_VAR_FAST_POWER_ON_CLEARED
#define CAN_VAR_FAST_INIT
#define CAN_VAR_FAST_POWER_ON_INIT
/* To be used for all infrequently accessed global or static variables. */
#define CAN_VAR_SLOW_NO_INIT
#define CAN_VAR_SLOW_CLEARED
#define CAN_VAR_SLOW_POWER_ON_CLEARED
#define CAN_VAR_SLOW_INIT
#define CAN_VAR_SLOW_POWER_ON_INIT
/* To be used for global or static variables which are accessible from a calibration tool. */
#define CAN_INTERNAL_VAR_NO_INIT
#define CAN_INTERNAL_VAR_CLEARED
#define CAN_INTERNAL_VAR_POWER_ON_CLEARED
#define CAN_INTERNAL_VAR_INIT
#define CAN_INTERNAL_VAR_POWER_ON_INIT
/* To be used for RAM buffers of variables saved in non-volatile memory. X shall be
replaced with the number of bytes (i.e. 8,16 or 32). */
#define CAN_VAR_SAVED_ZONE8
#define CAN_VAR_SAVED_ZONE16
#define CAN_VAR_SAVED_ZONE32

/* CODE */
/* To be used for code, PERIOD is the typical period time value and unit of the ExecutableEntitys in this MemorySection. */
#define CAN_CODE
#define CAN_CODE_100US
#define CAN_CODE_400US
#define CAN_CODE_1MS
#define CAN_CODE_5MS
#define CAN_CODE_10MS
#define CAN_CODE_20MS
#define CAN_CODE_100MS
#define CAN_CODE_1S
/* To be used for callout code */
#define CAN_CALLOUT_CODE
/* To be used for code that shall go into fast code memory segments. */
#define CAN_CODE_FAST
/* To be used for code that shall go into slow code memory segments. */
#define CAN_CODE_SLOW

/* CONSTANTS */
/* To be used for global or static constants */
#define CAN_CONST
/* To be used for calibration constants. */
#define CAN_CALIB
/* To be used for module configuration constants. */
#define CAN_CONFIG_DATA
/* To be used for ROM buffers of variables saved in non-volatile memory. */
#define CAN_CONST_SAVED_RECOVERY_ZONE8
#define CAN_CONST_SAVED_RECOVERY_ZONE16
#define CAN_CONST_SAVED_RECOVERY_ZONE32

/* POINTER */
/* To be used for references on application data (expected to be in RAM or ROM) passed via API */
#define CAN_APPL_DATA
/* To be used for references on application constants (expected to be certainly in
ROM, for instance pointer of Init-function) passed via API */
#define CAN_APPL_CONST
/* To be used for pointers to registers 
(e.g. static volatile CONSTP2VAR(uint16, PWM_CONST, REGSPACE)). */
#define REGSPACE
/******************************************************************************/

/*******************************************************************************
*       ADC MODULE SPECIFIC COMPILER MACRO
*******************************************************************************/

/******************************************************************************/


#endif // __COMPILER_CFG_H__