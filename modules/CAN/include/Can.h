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

#define CAN_SID_GET_VERSIONINFO 0x07U
#define CAN_SID_INIT 0x00U
#define CAN_SID_DEINIT 0x10U
#define CAN_SID_SET_BAUDRATE 0x0FU
#define CAN_SID_SET_CONTROLLER_MODE 0x03U
#define CAN_SID_DISABLE_CONTROLLER_INTERRUPT 0x04U
#define CAN_SID_ENABLE_CONTROLLER_INTERRUPT 0x05U
#define CAN_SID_CHECK_WAKEUP 0x0BU
#define CAN_SID_GET_CONTROLLER_ERROR_STATE 0x11U
#define CAN_SID_GET_CONTROLLER_MODE 0x12U
#define CAN_SID_GET_CONTROLLER_RX_ERROR_COUNTER 0x30U
#define CAN_SID_GET_CONTROLLER_TX_ERROR_COUNTER 0x31U
/*******************************************************************************
Typedef definitions
*******************************************************************************/
/* [ref]: ECUC_Can_00489 */
/* Post-build configuration structure could be changed after build (i.e update
by during run time)
Pre-compile configuration structure is fixed after compilation process. */
/* [SWS_Can_00413] */
typedef struct Can_ConfigType_STag
{
    /* CanGeneral */
    Can_GeneralConfigType                   * stCanGeneral;
    /* CanConfigSet */
        /* CanControllers */
        Can_ControllerConfigType                *stCanCtrlrs;
        /* CanIcom */
        Can_IcomControllerConfigType            *stCanIcomCtrlr;
        /* CanHardwareObject */
        Can_HwObjectConfigType                  *stCanHwObjs;
    uint8                                   ucNumCanController;
} Can_ConfigType;

/*******************************************************************************
Global functions
*******************************************************************************/
#if(CAN_VERSIONINFO_API == STD_ON)
FUNC(void, CAN_CODE_SLOW) Can_GetVersionInfo(P2VAR(Std_VersionInfoType, AUTOMATIC, CAN_APPL_DATA) versioninfo);
#endif

FUNC(void, CAN_CODE_SLOW) Can_Init(P2CONST(Can_ConfigType, AUTOMATIC, CAN_APPL_DATA) Config);

FUNC(void, CAN_CODE_SLOW) Can_DeInit(void);

#if(CAN_SET_BAUDRATE_API == STD_ON)
FUNC(Std_ReturnType, CAN_CODE_SLOW) Can_SetBaudrate(VAR(uint8, AUTOMATIC) Controller,
                                                    VAR(uint16, AUTOMATIC) BaudRateConfigID);
#endif

FUNC(Std_ReturnType, CAN_CODE_SLOW) Can_SetControllerMode(VAR(uint8, AUTOMATIC) Controller,
                                                          VAR(Can_ControllerStateType, AUTOMATIC) Transition);

FUNC(void, CAN_CODE_SLOW) Can_DisableControllerInterrupts(VAR(uint8, AUTOMATIC) Controller);

FUNC(void, CAN_CODE_SLOW) Can_EnableControllerInterrupts(VAR(uint8, AUTOMATIC) Controller);

#if(CAN_WAKEUP_FUNCTIONALITY_API == STD_ON)
FUNC(Std_ReturnType, CAN_CODE_SLOW) Can_CheckWakeup(VAR(uint8, AUTOMATIC) Controller);
#endif

FUNC(Std_ReturnType, CAN_CODE_SLOW) Can_GetControllerErrorState(VAR(uint8, AUTOMATIC) ControllerId,
                                                    P2VAR(Can_ErrorStateType, AUTOMATIC, CAN_APPL_DATA) ErrorStatePtr);

FUNC(Std_ReturnType, CAN_CODE_SLOW) Can_GetControllerMode(VAR(uint8, AUTOMATIC) Controller,
                                            P2VAR(Can_ControllerStateType, AUTOMATIC, CAN_APPL_DATA) ControllerModePtr);

FUNC(Std_ReturnType, CAN_CODE_SLOW) Can_GetControllerRxErrorCounter(VAR(uint8, AUTOMATIC) ControllerId,
                                                              P2VAR(uint8, AUTOMATIC, CAN_APPL_DATA) RxErrorCounterPtr);

FUNC(Std_ReturnType, CAN_CODE_SLOW) Can_GetControllerTxErrorCounter(VAR(uint8, AUTOMATIC) ControllerId,
                                                              P2VAR(uint8, AUTOMATIC, CAN_APPL_DATA) TxErrorCounterPtr);

FUNC(Std_ReturnType, CAN_CODE_SLOW) Can_Write(VAR(Can_HwHandleType, AUTOMATIC) Hth,
                                              P2CONST(Can_PduType, AUTOMATIC, CAN_APPL_DATA) PduInfo);

#if(CAN_TX_PROCESSING_API == STD_ON)
FUNC(void, CAN_CODE_SLOW) Can_MainFunction_Write (void);
#endif

#if(CAN_RX_PROCESSING_API == STD_ON)
FUNC(void, CAN_CODE_SLOW) Can_MainFunction_Read (void);
#endif

#if(CAN_BUSOFF_PROCESSING_API == STD_ON)
FUNC(void, CAN_CODE_SLOW) Can_MainFunction_BusOff (void);
#endif

#if(CAN_WAKEUP_PROCESSING_API == STD_ON)
FUNC(void, CAN_CODE_SLOW) Can_MainFunction_Wakeup (void);
#endif

FUNC(void, CAN_CODE_SLOW) Can_MainFunction_Mode (void);

#if(CAN_PUBLIC_ICOM_SUPPORT == STD_ON)
FUNC(Std_ReturnType, CAN_CODE_SLOW) Can_SetIcomConfiguration(VAR(uint8, AUTOMATIC) Controller,
                                                            VAR(IcomConfigIdType, AUTOMATIC) ConfigurationId);
#endif

#endif /* End of Can.h */
