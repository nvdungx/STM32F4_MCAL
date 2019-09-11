/*******************************************************************************
* File:         Can_PCTypes.h
* Revision:
* Author:
* Date:         02.08.2019
* Description:  
*******************************************************************************/
#ifndef CAN_PCTYPES_H
#define CAN_PCTYPES_H

#include "Can_Types.h"


/* [ref]: ECUC_Can_00444 */
typedef struct Can_IcomGeneralPCConfigType_STag
{
  Can_IcomLevelType   enCanIcomLevel;
  Can_IcomVariantType enCanIcomVariant;
} Can_IcomGeneralPCConfigType;

/* Data structure contain pre-compile data:
  ref to EcuM wakeup API
  ref to ICOM configuration data
  tx/rx/busoff processing option
  interrupt enable/disable status
  controller sw status
  controller tx/rx error status
  */
/* [ref]: ECUC_Can_00354 */
typedef struct Can_ControllerPCConfigType_STag
{
  EcuM_WakeupSourceType     enCanWakeupRef;
  Can_ModeOpType            enCanWakeupModeOp;
  Can_ModeOpType            enCanBusoffModeOp;
  Can_ModeOpType            enCanRxModeOp;
  Can_ModeOpType            enCanTxModeOp;
  Can_ControllerStateType * ptCanControllerSts;
  uint8                     ucCanControllerId;
} Can_ControllerPCConfigType;

/* Data structure contain pre-compile data:
  general configuration data of CAN module
  */
/* [ref]: ECUC_Can_00328 */
typedef struct Can_GeneralPCConfigType_STag
{
  Can_IcomGeneralPCConfigType * stCanIcomGeneral;
  uint8                         ucCanIndex;
  uint8                         ucCanMultiplexedTx;
  uint8                         ucCanIcomEnable;
} Can_GeneralPCConfigType;

#endif /*End of Can_PCTypes.h*/
