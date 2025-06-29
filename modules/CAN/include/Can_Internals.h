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
extern const CanCtrlrHwRegType HwCanCtrlr[];
extern Can_DrvStsType g_enCanDriverState;

boolean Can_HwCtrlInit(const Can_ConfigType* ConfigPtr, uint8 CtrlrIdx);
boolean Can_HwDeInit(const Can_ConfigType* ConfigPtr, uint8 CtrlrIdx);
Std_ReturnType Can_WaitRegValUntilTimeout(uint32 * RegAddr, uint32 ExpectedValue, uint32 Mask);
boolean Can_ConfigFilterRule(uint8 CtrlrIdx, uint8 FltBankStart, uint8 FltBankEnd, uint8 FltBankType, Can_HwFilterType *HwFilterRule);
Can_ControllerType* Can_GetCtrlr(const Can_ConfigType* ConfigPtr, uint8 CtrlrId);
Can_BaudrateConfigType* Can_GetBaudrateCfg(Can_ControllerType *CtrlrPtr, uint8 BaudRateConfigID);
Std_ReturnType Can_CheckValidSetCtrlrModeTrans(Can_ControllerStateType CurState, Can_ControllerStateType NextState);
Std_ReturnType Can_CheckDevError(const Can_ConfigType* ConfigPtr, uint8 Controller, uint8 ServiceID, Can_ControllerType *Lpt_Ctrlr);

#endif /*End of Can_Internals.h*/
