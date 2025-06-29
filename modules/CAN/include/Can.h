/*******************************************************************************
 * COPYRIGHT
 * -----------------------------------------------------------------------------
 * Copyright (c) 2022 by <<>>. All rights reserved.
 * -----------------------------------------------------------------------------
 * FILE DESCRIPTION
 *  File:         Can.h
 *  Component:    Header
 *  Module:       CAN
 *  Generator:    N/A
 *  Description:  declaration of CAN module API
 * -----------------------------------------------------------------------------
 * REVISION HISTORY
 * -----------------------------------------------------------------------------
 * Version   Date        Author  Description
 * -----------------------------------------------------------------------------
 * 01.00.00  13/08/2022  Dungnv  Initial version
 *
 *******************************************************************************/

/* [SWS_Can_00386] */
#ifndef CAN_H
#define CAN_H
/*******************************************************************************
Includes
*******************************************************************************/
#include "ComStack_Types.h"
/* [SWS_Can_00436] */
#include "Can_GeneralTypes.h"
#include "Can_Types.h"
#include "MemMap.h"
#include "Can_Cfg.h"

/*******************************************************************************
Macro definitions
*******************************************************************************/
#define CAN_SID_GET_VERSIONINFO                     0x07U
#define CAN_SID_INIT                                0x00U
#define CAN_SID_DEINIT                              0x10U
#define CAN_SID_SET_BAUDRATE                        0x0FU
#define CAN_SID_SET_CONTROLLER_MODE                 0x03U
#define CAN_SID_DISABLE_CONTROLLER_INTERRUPT        0x04U
#define CAN_SID_ENABLE_CONTROLLER_INTERRUPT         0x05U
#define CAN_SID_CHECK_WAKEUP                        0x0BU
#define CAN_SID_GET_CONTROLLER_ERROR_STATE          0x11U
#define CAN_SID_GET_CONTROLLER_MODE                 0x12U
#define CAN_SID_GET_CONTROLLER_RX_ERROR_COUNTER     0x30U
#define CAN_SID_GET_CONTROLLER_TX_ERROR_COUNTER     0x31U
#define CAN_SID_GET_TIMESTAMP                       0x32U
#define CAN_SID_ENABLE_EGRESS_TIMESTAMP             0x33U
#define CAN_SID_GET_EGRESS_TIMESTAMP                0x34U
#define CAN_SID_GET_INGRESS_TIMESTAMP               0x35U
#define CAN_SID_MAINFUNCTION_WRITE                  0x01U
#define CAN_SID_MAINFUNCTION_READ                   0x08U
#define CAN_SID_MAINFUNCTION_BUSOFF                 0x09U
#define CAN_SID_MAINFUNCTION_WAKEUP                 0x0AU
#define CAN_SID_MAINFUNCTION_MODE                   0x0CU

/*******************************************************************************
Typedef definitions
*******************************************************************************/

/*******************************************************************************
Global functions
*******************************************************************************/
#if(CAN_VERSIONINFO_API == STD_ON)
void Can_GetVersionInfo(Std_VersionInfoType* versioninfo);
#endif

void Can_Init(const Can_ConfigType* Config);

void Can_DeInit(void);

#if(CAN_SET_BAUDRATE_API == STD_ON)
Std_ReturnType Can_SetBaudrate(uint8 Controller, uint16 BaudRateConfigID);
#endif

Std_ReturnType Can_SetControllerMode(uint8 Controller, Can_ControllerStateType Transition);

void Can_DisableControllerInterrupts(uint8 Controller);

void Can_EnableControllerInterrupts(uint8 Controller);

#if(CAN_WAKEUP_FUNCTIONALITY_API == STD_ON)
Std_ReturnType Can_CheckWakeup(uint8 Controller);
#endif

Std_ReturnType Can_GetControllerErrorState(uint8 ControllerId, Can_ErrorStateType* ErrorStatePtr);

Std_ReturnType Can_GetControllerMode(uint8 Controller, Can_ControllerStateType* ControllerModePtr);

Std_ReturnType Can_GetControllerRxErrorCounter(uint8 ControllerId, uint8* RxErrorCounterPtr);

Std_ReturnType Can_GetControllerTxErrorCounter(uint8 ControllerId, uint8* TxErrorCounterPtr);

Std_ReturnType Can_GetCurrentTime(uint8 ControllerId, Can_TimeStampType* TimeStampPtr);

void Can_EnableEgressTimeStamp(Can_HwHandleType Hth);

Std_ReturnType Can_GetEgressTimeStamp(PduIdType TxPduId, Can_HwHandleType Hth, Can_TimeStampType* TimeStampPtr);

Std_ReturnType Can_GetIngressTimeStamp(Can_HwHandleType Hrh, Can_TimeStampType* TimeStampPtr);

Std_ReturnType Can_Write(Can_HwHandleType Hth, const Can_PduType* PduInfo);

#if(CAN_TX_PROCESSING_API == STD_ON)
void Can_MainFunction_Write(void);
#endif

#if(CAN_RX_PROCESSING_API == STD_ON)
void Can_MainFunction_Read(void);
#endif

#if(CAN_BUSOFF_PROCESSING_API == STD_ON)
void Can_MainFunction_BusOff(void);
#endif

#if(CAN_WAKEUP_PROCESSING_API == STD_ON)
void Can_MainFunction_Wakeup(void);
#endif

void Can_MainFunction_Mode(void);

#endif /* End of Can.h */
