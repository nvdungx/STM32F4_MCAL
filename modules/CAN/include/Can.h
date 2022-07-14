/*******************************************************************************
* File:         Can.h
* Revision:     1.0.0
* Author:       Dung van Nguyen
* Date:         02.08.2019
* Description:  declaration of CAN module API
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
#include "Can_PBTypes.h"
#include "Can_PCTypes.h"
#include "MemMap.h"
#include "Can_Cfg.h"

/*******************************************************************************
Macro definitions
*******************************************************************************/

#define CAN_SID_GETVERSIONINFO    0x07U
#define CAN_SID_INIT              0x00U
#define CAN_SID_DEINIT            0x10U
#define CAN_SID_SETBAUDRATE       0x0FU

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
  const Can_ControllerPCConfigType     * const stCanPCController;
  const Can_ControllerPBConfigType           * stCanPBController;
  const Can_GeneralPCConfigType        * const stCanPCGeneral;
  const Can_IcomControllerPBConfigType       * stCanIcomPBController;
  const Can_HwObjectPBConfigType             * stCanHwObj;
  const Can_HwFilterPBConfigType             * stCanHwFilter;
  uint8 ucNumCanController;
} Can_ConfigType;

/*******************************************************************************
Global functions
*******************************************************************************/

FUNC(void, CAN_CODE_SLOW) Can_GetVersionInfo (
  P2VAR(Std_VersionInfoType, AUTOMATIC, CAN_APPL_DATA) versioninfo);

FUNC(void, CAN_CODE_SLOW) Can_Init (
  P2CONST(Can_ConfigType, AUTOMATIC, CAN_APPL_DATA) Config);

FUNC(void, CAN_CODE_SLOW) Can_DeInit (void);

FUNC(Std_ReturnType, CAN_CODE_SLOW) Can_SetBaudrate (
  VAR(uint8, AUTOMATIC) Controller, VAR(uint16, AUTOMATIC) BaudRateConfigID);

FUNC(Std_ReturnType, CAN_CODE_SLOW) Can_SetControllerMode (
  VAR(uint8, AUTOMATIC) Controller,
    VAR(Can_ControllerStateType, AUTOMATIC) Transition);

FUNC(void, CAN_CODE_SLOW) Can_DisableControllerInterrupts (
  VAR(uint8, AUTOMATIC) Controller);

FUNC(void, CAN_CODE_SLOW) Can_EnableControllerInterrupts (
  VAR(uint8, AUTOMATIC) Controller);

FUNC(Std_ReturnType, CAN_CODE_SLOW) Can_CheckWakeup (
  VAR(uint8, AUTOMATIC) Controller);

FUNC(Std_ReturnType, CAN_CODE_SLOW) Can_GetControllerErrorState (
  VAR(uint8, AUTOMATIC) ControllerId,
    P2VAR(Can_ErrorStateType, AUTOMATIC, CAN_APPL_DATA) ErrorStatePtr);

FUNC(Std_ReturnType, CAN_CODE_SLOW) Can_GetControllerMode (
  VAR(uint8, AUTOMATIC) Controller,
    P2VAR(Can_ControllerStateType, AUTOMATIC, CAN_APPL_DATA) ControllerModePtr);

FUNC(Std_ReturnType, CAN_CODE_SLOW) Can_GetControllerRxErrorCounter (
  VAR(uint8, AUTOMATIC) ControllerId,
    P2VAR(uint8, AUTOMATIC, CAN_APPL_DATA) RxErrorCounterPtr);

FUNC(Std_ReturnType, CAN_CODE_SLOW) Can_GetControllerTxErrorCounter (
  VAR(uint8, AUTOMATIC) ControllerId,
    P2VAR(uint8, AUTOMATIC, CAN_APPL_DATA) TxErrorCounterPtr);

FUNC(Std_ReturnType, CAN_CODE_SLOW) Can_Write (
  VAR(Can_HwHandleType, AUTOMATIC) Hth,
    P2CONST(Can_PduType, AUTOMATIC, CAN_APPL_DATA) PduInfo);

FUNC(Std_ReturnType, CAN_CODE_SLOW) Can_SetIcomConfiguration (
  VAR(uint8, AUTOMATIC) Controller,
    VAR(IcomConfigIdType, AUTOMATIC) ConfigurationId);

#endif /* End of Can.h */
