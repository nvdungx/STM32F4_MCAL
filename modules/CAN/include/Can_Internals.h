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
#define CAN_MSR_SLEEP_ACK ((uint32)1 << 1)
#define CAN_MSR_INIT_ACK ((uint32)1)
/*******************************************************************************
Typedef definitions
*******************************************************************************/

/*******************************************************************************
Global functions
*******************************************************************************/
extern CONST(CanCtrlrHwRegType, CAN_APPL_CONST) HwCanCtrlr[];
extern Can_DrvStsType Gen_CanDriverState;

FUNC(boolean, CAN_CODE_SLOW) Can_HwCtrlInit(P2CONST(Can_ConfigType, AUTOMATIC, CAN_APPL_DATA) ConfigPtr,
                                            VAR(uint8, AUTOMATIC) CtrlrIdx);

FUNC(boolean, CAN_CODE_SLOW) Can_HwDeInit(P2CONST(Can_ConfigType, AUTOMATIC, CAN_APPL_DATA) ConfigPtr,
                                            VAR(uint8, AUTOMATIC) CtrlrIdx);
FUNC(Std_ReturnType, CAN_CODE_SLOW) Can_WaitRegValUntilTimeout(uint32 * RegAddr, uint32 ExpectedValue, uint32 Mask);
FUNC(boolean, CAN_CODE_SLOW) Can_ConfigFilterRule(uint8 CtrlrIdx, uint8 FltBankStart, uint8 FltBankEnd,
    uint8 FltBankType, Can_HwFilterConfigType *HwFilterRule);
FUNC(Can_ControllerConfigType *, CAN_CODE_SLOW) Can_GetCtrlr(P2CONST(Can_ConfigType, AUTOMATIC, CAN_APPL_DATA) ConfigPtr,
    VAR(uint8, AUTOMATIC) CtrlrId);
FUNC(Can_BaudrateConfigType *, CAN_CODE_SLOW) Can_GetBaudrateCfg(Can_ControllerConfigType *CtrlrPtr,
    VAR(uint8, AUTOMATIC) BaudRateConfigID);
FUNC(Std_ReturnType, CAN_CODE_SLOW) Can_CheckValidSetCtrlrModeTrans(Can_ControllerStateType CurState,
                                                                    Can_ControllerStateType NextState);
FUNC(Std_ReturnType, CAN_CODE_SLOW) Can_CheckDevError(P2CONST(Can_ConfigType, AUTOMATIC, CAN_APPL_DATA) ConfigPtr,
    VAR(uint8, AUTOMATIC) Controller, VAR(uint8, AUTOMATIC) ServiceID, Can_ControllerConfigType *Lpt_Ctrlr);
#endif /*End of Can_Internals.h*/
