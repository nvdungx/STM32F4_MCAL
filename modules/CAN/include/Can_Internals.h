/*******************************************************************************
* File:         Can_Internals.h
* Revision:     1.0.0
* Author:       Dung van Nguyen
* Date:         04.09.2019
* Description:  
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
#include "Can_PBTypes.h"
#include "Can.h"
#include "MemMap.h"

/*******************************************************************************
Macro definitions
*******************************************************************************/

/*******************************************************************************
Typedef definitions
*******************************************************************************/

/*******************************************************************************
Global functions
*******************************************************************************/
extern CONST(CanCtrlrHwRegType, CAN_APPL_CONST) CanCtrlr[2];

FUNC(boolean, CAN_CODE_SLOW) Can_HwInit(
  P2CONST(Can_ConfigType, AUTOMATIC, CAN_APPL_DATA) Config,
    VAR(uint8, AUTOMATIC) Controller);

FUNC(boolean, CAN_CODE_SLOW) Can_HwDeInit(VAR(uint8, AUTOMATIC) Controller);

#endif /*End of Can_Internals.h*/
