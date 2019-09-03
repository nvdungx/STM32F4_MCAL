/*******************************************************************************
* File:         Can.h
* Revision:
* Author:
* Date:         02.08.2019
* Description:  declaration of CAN module API
*******************************************************************************/

#ifndef CAN_H
#define CAN_H
/*******************************************************************************
Includes
*******************************************************************************/
#include "ComStack_Types.h"
#include "Can_GeneralTypes.h"
#include "Can_Cfg.h"

/*******************************************************************************
Macro definitions
*******************************************************************************/

#define CAN_SID_GETVERSIONINFO    0x07U
#define CAN_SID_INIT              0x00U
#define CAN_SID_DEINIT            0x10U
#define CAN_SID_SETBAUDRATE       0x0FU

/* Temporary >> shall move to DET module instead */
#define CAN_E_PARAM_POINTER       0x01U
#define CAN_E_PARAM_HANDLE        0x02U
#define CAN_E_PARAM_DATA_LENGTH   0x03U
#define CAN_E_PARAM_CONTROLLER    0x04U
#define CAN_E_UNINIT              0x05U
#define CAN_E_TRANSITION          0x06U
#define CAN_E_PARAM_BAUDRATE      0x07U
#define CAN_E_ICOM_CONFIG_INVALID 0x08U
#define CAN_E_INIT_FAILED         0x09U

/* Temporary >> shall move to DEM module instead */
#define CAN_E_DATALOST            0x01U

#define CAN_MODULE_ID             0x80U
/*******************************************************************************
Typedef definitions
*******************************************************************************/



/*******************************************************************************
Global functions
*******************************************************************************/

FUNC(void, CAN_CODE_SLOW) Can_GetVersionInfo (
  P2VAR(Std_VersionInfoType, AUTOMATIC, CAN_APPL_DATA) versioninfo);

FUNC(void, CAN_CODE_SLOW) Can_Init (
  P2CONST(Can_ConfigType, CAN_APPL_DATA) Config);

FUNC(void, CAN_CODE_SLOW) Can_DeInit (void);

FUNC(Std_ReturnType, CAN_CODE_SLOW) Can_SetBaudrate (
  VAR(uint8, AUTOMATIC) Controller, VAR(uint16, AUTOMATIC) BaudRateConfigID);

FUNC(Std_ReturnType, CAN_CODE_SLOW) Can_SetControllerMode (
  VAR(uint8, AUTOMATIC) Controller, VAR(Can_ControllerStateType) Transition);

FUNC(void, CAN_CODE_SLOW) Can_DisableControllerInterrupts (
  VAR(uint8, AUTOMATIC) Controller);

FUNC(void, CAN_CODE_SLOW) Can_EnableControllerInterrupts (
  VAR(uint8, AUTOMATIC) Controller);

FUNC(Std_ReturnType, CAN_CODE_SLOW) Can_CheckWakeup (
  VAR(uint8, AUTOMATIC) Controller);

FUNC(Std_ReturnType, CAN_CODE_SLOW) Can_GetControllerErrorState (
  VAR(uint8, AUTOMATIC) ControllerId,
    P2VAR(Can_ErrorStateType, AUTOMATIC) ErrorStatePtr);

FUNC(Std_ReturnType, CAN_CODE_SLOW) Can_GetControllerMode (
  VAR(uint8, AUTOMATIC) Controller,
    P2VAR(Can_ControllerStateType, AUTOMATIC) ControllerModePtr);

FUNC(Std_ReturnType, CAN_CODE_SLOW) Can_GetControllerRxErrorCounter (
  VAR(uint8, AUTOMATIC) ControllerId,
    P2VAR(uint8, AUTOMATIC) RxErrorCounterPtr);

FUNC(Std_ReturnType, CAN_CODE_SLOW) Can_GetControllerTxErrorCounter (
  VAR(uint8, AUTOMATIC) ControllerId,
    P2VAR(uint8, AUTOMATIC) TxErrorCounterPtr);

FUNC(Std_ReturnType, CAN_CODE_SLOW) Can_Write (
  VAR(Can_HwHandleType, AUTOMATIC) Hth,
    P2CONST(Can_PduType, AUTOMATIC) PduInfo);

#endif /* End of Can.h */
