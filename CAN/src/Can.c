/*******************************************************************************
* File:         Can.c
* Revision:
* Author:
* Date:         02.08.2019
* Description:  definition of CAN module API
*******************************************************************************/

#include "Dem.h"
#include "Det.h"
#include "MemMap.h"
#include "SchM_Can.h"
#include "EcuM_Cbk.h"
#include "Os.h"
#include "CanIf_Cbk.h"
#include "Can.h"

Can_DrvStsType Can_DriverSts = CAN_UNINIT;

/*
 *  Service Name...... : Can_GetVersionInfo
 *  Service ID      .. : 0x07
 *  Sync/Async........ : Synchronous
 *  Reentrancy........ : Reentrant
 *  Parameters (IN)... : None
 *  Parameters (INOUT) : versioninfo
 *  Parameters (OUT).. : None
 *  Return Value...... : None
 *  Register usage     : 
 *  Global variable    : 
 *  Description....... : This function return the version information of module.
 */
FUNC(void, CAN_CODE_SLOW) Can_GetVersionInfo (
  P2VAR(Std_VersionInfoType, AUTOMATIC, CAN_APPL_DATA) versioninfo)
{
  if (versioninfo == NULL_PTR)
  {
    #ifdef DEV_ERROR_DETECT_API
    (void)Det_ReportError(CAN_MODULE_ID, CAN_INSTANCE_ID,
      CAN_SID_GETVERSIONINFO, CAN_E_PARAM_POINTER);
    #endif
  }
  else
  {
    versioninfo->vendorID = CAN_VENDOR_ID;
    versioninfo->moduleID =  ;
    versioninfo->sw_major_version = SW_MAJOR_VERSION;
    versioninfo->sw_minor_version = SW_MINOR_VERSION;
    versioninfo->sw_patch_version = SW_PATCH_VERSION;
  }
}

/*
 *  Service Name...... : Can_Init
 *  Service ID      .. : 0x00
 *  Sync/Async........ : Synchronous
 *  Reentrancy........ : Non Reentrant
 *  Parameters (IN)... : Config
 *  Parameters (INOUT) : None
 *  Parameters (OUT).. : None
 *  Return Value...... : None
 *  Register usage     : 
 *  Global variable    : 
 *  Description....... : This function initializes the module.
 */
FUNC(void, CAN_CODE_SLOW) Can_Init (
  P2CONST(Can_ConfigType, CAN_APPL_DATA) Config)
{
  
}

/*
 *  Service Name...... : Can_DeInit
 *  Service ID      .. : 0x10
 *  Sync/Async........ : Synchronous
 *  Reentrancy........ : Non Reentrant
 *  Parameters (IN)... : None
 *  Parameters (INOUT) : None
 *  Parameters (OUT).. : None
 *  Return Value...... : None
 *  Register usage     : 
 *  Global variable    : 
 *  Description....... : This function de-initializes the module.
 */
FUNC(void, CAN_CODE_SLOW) Can_DeInit (void)
{
  uint8 Luc_Count;
  boolean Lbl_DeInitSts;
  #ifdef DEV_ERROR_DETECT_API
  Std_ReturnType Luc_StdResult;

  Luc_StdResult = E_OK;
  /* Check if driver is initialized - Driver not in state CAN_READY */
  if (CAN_READY != Can_DriverSts)
  {
    (void)Det_ReportError(CAN_MODULE_ID, CAN_INSTANCE_ID,
      CAN_SID_DEINIT, CAN_E_TRANSITION);
    Luc_StdResult = E_NOT_OK;
  }
  /* Check all CAN Controllers is not in START mode */
  else
  {
    /* access configuration structure, loop through all controller and check
    the current sw status of each controller */
    for (Luc_Count = 0; Luc_Count < NUMBER_CAN_CONTROLLER; Luc_Count++)
    {
      
    }
    if (E_OK == Luc_StdResult)
    {
    (void)Det_ReportError(CAN_MODULE_ID, CAN_INSTANCE_ID,
      CAN_SID_DEINIT, CAN_E_TRANSITION);
    Luc_StdResult = E_NOT_OK;
    }
  }
  #endif

  #ifdef DEV_ERROR_DETECT_API
  if (E_OK == Luc_StdResult)
  {
  #endif
    Lbl_DeInitSts = TRUE;
    for (Luc_Count = 0; Luc_Count < NUMBER_CAN_CONTROLLER; Luc_Count++)
    {
      Lbl_DeInitSts &= Can_HwDeInit(Luc_Count);
    }
    if (TRUE == Lbl_DeInitSts)
    {
      /* There are no fail during deinit process */
      Can_DriverSts = CAN_UNINIT;
    }
    else
    {
      /* There is fail during deinit controllers process */
    }
  #ifdef DEV_ERROR_DETECT_API
  }
  else
  {
    /* No action required */
  }
  #endif
}

/*
 *  Service Name...... : Can_SetBaudrate
 *  Service ID      .. : 0x0F
 *  Sync/Async........ : Synchronous
 *  Reentrancy........ : Non Reentrant (for same Controller),
 *                       Reentrant (for different Controller)
 *  Parameters (IN)... : Controller, BaudRateConfigID
 *  Parameters (INOUT) : None
 *  Parameters (OUT).. : None
 *  Return Value...... : Std_ReturnType(E_OK/E_NOT_OK)
 *  Register usage     : 
 *  Global variable    : 
 *  Description....... : This service shall set the baud rate configuration of
 *                       the CAN controller. Depending on necessary baud rate
 *                       modifications the controller might have to reset.
 */
FUNC(Std_ReturnType, CAN_CODE_SLOW) Can_SetBaudrate (
  VAR(uint8, AUTOMATIC) Controller,
  VAR(uint16, AUTOMATIC) BaudRateConfigID)
{

  Std_ReturnType Luc_StdResult;

  Luc_StdResult = E_OK;
  #ifdef DEV_ERROR_DETECT_API
  /* Check if driver is initialized - Driver not in state CAN_READY */
  if (CAN_READY != Can_DriverSts)
  {
    (void)Det_ReportError(CAN_MODULE_ID, CAN_INSTANCE_ID,
      CAN_SID_SETBAUDRATE, CAN_E_UNINIT);
    Luc_StdResult = E_NOT_OK;
  }
  /* Check if requested Controller value is valid */
  else if (CAN_LAST_CONTROLLERID < Controller)
  {
    (void)Det_ReportError(CAN_MODULE_ID, CAN_INSTANCE_ID,
      CAN_SID_SETBAUDRATE, CAN_E_PARAM_CONTROLLER);
    Luc_StdResult = E_NOT_OK;
  }
  /* Check if requested BaudRateConfigID value is valid */
  else if (CAN_MAX_BDCONFIG_ID < BaudRateConfigID)
  {
    (void)Det_ReportError(CAN_MODULE_ID, CAN_INSTANCE_ID,
      CAN_SID_SETBAUDRATE, CAN_E_PARAM_BAUDRATE);
    Luc_StdResult = E_NOT_OK;
  }
  else
  {
    /* No action required */
  }
  #endif

  #ifdef DEV_ERROR_DETECT_API
  if (E_OK == Luc_StdResult)
  {
  #endif
    /* Check whether Controller mode is in STOP_MODE if required */
  
    /* Get the configuration data from input controller and BaudRateConfigID */
  
    /* Configure the HW of requested Controller */
  
  #ifdef DEV_ERROR_DETECT_API
  }
  else
  {
    /* No action required */
  }
  #endif
  return Luc_StdResult;
}

/*
 *  Service Name...... : Can_SetControllerMode
 *  Service ID      .. : 0x03
 *  Sync/Async........ : Asynchronous
 *  Reentrancy........ : Non Reentrant
 *  Parameters (IN)... : Controller, Transition
 *  Parameters (INOUT) : None
 *  Parameters (OUT).. : None
 *  Return Value...... : Std_ReturnType(E_OK/E_NOT_OK)
 *  Register usage     : 
 *  Global variable    : 
 *  Description....... : This function performs software triggered state
 *                       transitions of the CAN controller State machine.
 */
FUNC(Std_ReturnType, CAN_CODE_SLOW) Can_SetControllerMode (
  VAR(uint8, AUTOMATIC) Controller,
  VAR(Can_ControllerStateType) Transition)
{

}

/*
 *  Service Name...... : Can_DisableControllerInterrupts
 *  Service ID      .. : 0x04
 *  Sync/Async........ : Synchronous
 *  Reentrancy........ : Reentrant
 *  Parameters (IN)... : Controller
 *  Parameters (INOUT) : None
 *  Parameters (OUT).. : None
 *  Return Value...... : None
 *  Register usage     : 
 *  Global variable    : 
 *  Description....... : This function disables all interrupts for this
 *                       CAN controller.
 */
FUNC(void, CAN_CODE_SLOW) Can_DisableControllerInterrupts (
  VAR(uint8, AUTOMATIC) Controller)
{

}

/*
 *  Service Name...... : Can_EnableControllerInterrupts
 *  Service ID      .. : 0x05
 *  Sync/Async........ : Synchronous
 *  Reentrancy........ : Reentrant
 *  Parameters (IN)... : Controller
 *  Parameters (INOUT) : None
 *  Parameters (OUT).. : None
 *  Return Value...... : None
 *  Register usage     : 
 *  Global variable    : 
 *  Description....... : This function enables all allowed interrupts for this
 *                       CAN controller.
 */
FUNC(void, CAN_CODE_SLOW) Can_EnableControllerInterrupts (
  VAR(uint8, AUTOMATIC) Controller)
{

}

/*
 *  Service Name...... : Can_CheckWakeup
 *  Service ID      .. : 0x0B
 *  Sync/Async........ : Synchronous
 *  Reentrancy........ : Non Reentrant
 *  Parameters (IN)... : Controller
 *  Parameters (INOUT) : None
 *  Parameters (OUT).. : None
 *  Return Value...... : Std_ReturnType(E_OK/E_NOT_OK)
 *  Register usage     : 
 *  Global variable    : 
 *  Description....... : This function checks if a wakeup has occurred for
 *                       the given controller.
 */
FUNC(Std_ReturnType, CAN_CODE_SLOW) Can_CheckWakeup (
  VAR(uint8, AUTOMATIC) Controller)
{

}

/*
 *  Service Name...... : Can_GetControllerErrorState
 *  Service ID      .. : 0x11
 *  Sync/Async........ : Synchronous
 *  Reentrancy........ : Non Reentrant (for the same ControllerId)
 *  Parameters (IN)... : ControllerId
 *  Parameters (INOUT) : None
 *  Parameters (OUT).. : ErrorStatePtr
 *  Return Value...... : Std_ReturnType(E_OK/E_NOT_OK)
 *  Register usage     : 
 *  Global variable    : 
 *  Description....... : This service obtains the error state of
 *                       the CAN controller.
 */
FUNC(Std_ReturnType, CAN_CODE_SLOW) Can_GetControllerErrorState (
  VAR(uint8, AUTOMATIC) ControllerId,
  P2VAR(Can_ErrorStateType, AUTOMATIC) ErrorStatePtr)
{

}

/*
 *  Service Name...... : Can_GetControllerMode
 *  Service ID      .. : 0x12
 *  Sync/Async........ : Synchronous
 *  Reentrancy........ : Non Reentrant
 *  Parameters (IN)... : Controller
 *  Parameters (INOUT) : None
 *  Parameters (OUT).. : ControllerModePtr
 *  Return Value...... : Std_ReturnType(E_OK/E_NOT_OK)
 *  Register usage     : 
 *  Global variable    : 
 *  Description....... : This service reports about the current status of
 *                       the requested CAN controller
 */
FUNC(Std_ReturnType, CAN_CODE_SLOW) Can_GetControllerMode (
  VAR(uint8, AUTOMATIC) Controller,
  P2VAR(Can_ControllerStateType, AUTOMATIC) ControllerModePtr)
{

}

/*
 *  Service Name...... : Can_GetControllerRxErrorCounter
 *  Service ID      .. : 0x30
 *  Sync/Async........ : Synchronous
 *  Reentrancy........ : Non Reentrant (for the same ControllerId)
 *  Parameters (IN)... : ControllerId
 *  Parameters (INOUT) : None
 *  Parameters (OUT).. : RxErrorCounterPtr
 *  Return Value...... : Std_ReturnType(E_OK/E_NOT_OK)
 *  Register usage     : 
 *  Global variable    : 
 *  Description....... : Returns the Rx error counter for a CAN controller.
 */
FUNC(Std_ReturnType, CAN_CODE_SLOW) Can_GetControllerRxErrorCounter (
  VAR(uint8, AUTOMATIC) ControllerId,
  P2VAR(uint8, AUTOMATIC) RxErrorCounterPtr)
{

}

/*
 *  Service Name...... : Can_GetControllerTxErrorCounter
 *  Service ID      .. : 0x31
 *  Sync/Async........ : Synchronous
 *  Reentrancy........ : Non Reentrant (for the same ControllerId)
 *  Parameters (IN)... : ControllerId
 *  Parameters (INOUT) : None
 *  Parameters (OUT).. : TxErrorCounterPtr
 *  Return Value...... : Std_ReturnType(E_OK/E_NOT_OK)
 *  Register usage     : 
 *  Global variable    : 
 *  Description....... : Returns the Tx error counter for a CAN controller.
 */
FUNC(Std_ReturnType, CAN_CODE_SLOW) Can_GetControllerTxErrorCounter (
  VAR(uint8, AUTOMATIC) ControllerId,
  P2VAR(uint8, AUTOMATIC) TxErrorCounterPtr)
{

}

/*
 *  Service Name...... : Can_Write
 *  Service ID      .. : 0x06
 *  Sync/Async........ : Synchronous
 *  Reentrancy........ : Reentrant (thread-safe)
 *  Parameters (IN)... : Hth, PduInfo
 *  Parameters (INOUT) : None
 *  Parameters (OUT).. : None
 *  Return Value...... : Std_ReturnType(E_OK/E_NOT_OK/CAN_BUSY)
 *  Register usage     : 
 *  Global variable    : 
 *  Description....... : This function is called by CanIf to pass a
 *                       CAN message to CanDrv for transmission.
 */
FUNC(Std_ReturnType, CAN_CODE_SLOW) Can_Write (
  VAR(Can_HwHandleType, AUTOMATIC) Hth,
  P2CONST(Can_PduType, AUTOMATIC) PduInfo)
{

}

/*
 *  Service Name...... : Can_MainFunction_Write
 *  Service ID      .. : 0x01
 *  Sync/Async........ : Synchronous
 *  Reentrancy........ : Reentrant
 *  Parameters (IN)... : None
 *  Parameters (INOUT) : None
 *  Parameters (OUT).. : None
 *  Return Value...... : None
 *  Register usage     : 
 *  Global variable    : 
 *  Description....... : This function performs the polling of TX confirmation
 *                       when CAN_TX_PROCESSING is set to POLLING
 */
FUNC(void, CAN_CODE_SLOW) Can_MainFunction_Write (void)
{

}

/*
 *  Service Name...... : Can_MainFunction_Read
 *  Service ID      .. : 0x08
 *  Sync/Async........ : Synchronous
 *  Reentrancy........ : Reentrant
 *  Parameters (IN)... : None
 *  Parameters (INOUT) : None
 *  Parameters (OUT).. : None
 *  Return Value...... : None
 *  Register usage     : 
 *  Global variable    : 
 *  Description....... : This function performs the polling of RX indications
 *                       when CAN_RX_PROCESSING is set to POLLING
 */
FUNC(void, CAN_CODE_SLOW) Can_MainFunction_Read (void)
{

}

/*
 *  Service Name...... : Can_MainFunction_BusOff
 *  Service ID      .. : 0x09
 *  Sync/Async........ : Synchronous
 *  Reentrancy........ : Reentrant
 *  Parameters (IN)... : None
 *  Parameters (INOUT) : None
 *  Parameters (OUT).. : None
 *  Return Value...... : None
 *  Register usage     : 
 *  Global variable    : 
 *  Description....... : This function performs the polling of bus-off events
 *                       that are configured statically as 'to be polled'.
 */
FUNC(void, CAN_CODE_SLOW) Can_MainFunction_BusOff (void)
{

}

/*
 *  Service Name...... : Can_MainFunction_Wakeup
 *  Service ID      .. : 0x0A
 *  Sync/Async........ : Synchronous
 *  Reentrancy........ : Reentrant
 *  Parameters (IN)... : None
 *  Parameters (INOUT) : None
 *  Parameters (OUT).. : None
 *  Return Value...... : None
 *  Register usage     : 
 *  Global variable    : 
 *  Description....... : This function performs the polling of wake-up events
 *                       that are configured statically as 'to be polled'.
 */
FUNC(void, CAN_CODE_SLOW) Can_MainFunction_Wakeup (void)
{

}

/*
 *  Service Name...... : Can_MainFunction_Mode
 *  Service ID      .. : 0x0C
 *  Sync/Async........ : Synchronous
 *  Reentrancy........ : Reentrant
 *  Parameters (IN)... : None
 *  Parameters (INOUT) : None
 *  Parameters (OUT).. : None
 *  Return Value...... : None
 *  Register usage     : 
 *  Global variable    : 
 *  Description....... : This function performs the polling of
 *                       CAN controller mode transitions
 */
FUNC(void, CAN_CODE_SLOW) Can_MainFunction_Mode (void)
{

}

/*
 *  Service Name...... : Can_SetIcomConfiguration
 *  Service ID      .. : 0x21
 *  Sync/Async........ : Asynchronous
 *  Reentrancy........ : Reentrant (for different controller Ids)
 *  Parameters (IN)... : Controller, ConfigurationId
 *  Parameters (INOUT) : None
 *  Parameters (OUT).. : None
 *  Return Value...... : None
 *  Register usage     : 
 *  Global variable    : 
 *  Description....... : This service shall change the Icom Configuration
 *                       of a CAN controller to the requested one.
 */
FUNC(Std_ReturnType, CAN_CODE_SLOW) Can_SetIcomConfiguration (
  VAR(uint8, AUTOMATIC) Controller,
  VAR(IcomConfigIdType, AUTOMATIC) ConfigurationId)
{

}
