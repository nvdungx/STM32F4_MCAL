/*******************************************************************************
 * COPYRIGHT
 * -----------------------------------------------------------------------------
 * Copyright (c) 2022 by <<>>. All rights reserved.
 * -----------------------------------------------------------------------------
 * FILE DESCRIPTION
 *  File:         Can_Internals.h
 *  Component:    Header
 *  Module:       CAN
 *  Generator:    N/A
 *  Description:
 * -----------------------------------------------------------------------------
 * REVISION HISTORY
 * -----------------------------------------------------------------------------
 * Version   Date        Author  Description
 * -----------------------------------------------------------------------------
 * 01.00.00  13/08/2022  Dungnv  Initial version
 *
*******************************************************************************/

#ifndef CAN_INTERNALS_H
#define CAN_INTERNALS_H
/*******************************************************************************
Includes
*******************************************************************************/
#include "ComStack_Types.h"
#include "Can_GeneralTypes.h"

#include "Can_IOCommon.h"
#include "Can_Types.h"
#include "Can.h"
#include "MemMap.h"

/*******************************************************************************
Macro definitions
*******************************************************************************/

/*******************************************************************************
Typedef definitions
*******************************************************************************/
#define CAN_MSR_SLEEP_ACK ((uint32)1 << 1)
/*******************************************************************************
Global functions
*******************************************************************************/
extern CONST(CanCtrlrHwRegType, CAN_APPL_CONST) HwCanCtrlr[];

FUNC(boolean, CAN_CODE_SLOW) Can_HwCtrlInit(P2CONST(Can_ConfigType, AUTOMATIC, CAN_APPL_DATA) ConfigPtr,
                                            VAR(uint8, AUTOMATIC) CtrlrIdx);

FUNC(boolean, CAN_CODE_SLOW) Can_HwDeInit(P2CONST(Can_ConfigType, AUTOMATIC, CAN_APPL_DATA) ConfigPtr,
                                            VAR(uint8, AUTOMATIC) CtrlrIdx);
FUNC(Std_ReturnType, CAN_CODE_SLOW) Can_WaitRegValUntilTimeout(uint32 * RegAddr, uint32 ExpectedValue);
FUNC(boolean, CAN_CODE_SLOW) Can_ConfigFilterRule(uint8 CtrlrIdx, uint8 FltBankStart, uint8 FltBankEnd,
    uint8 FltBankType, Can_HwFilterConfigType *HwFilterRule);
#endif /*End of Can_Internals.h*/
