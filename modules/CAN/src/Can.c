/*******************************************************************************
 * COPYRIGHT
 * -----------------------------------------------------------------------------
 * Copyright (c) 2022 by <<>>. All rights reserved.
 * -----------------------------------------------------------------------------
 * FILE DESCRIPTION
 *  File:         Can.c
 *  Component:    Source
 *  Module:       CAN
 *  Generator:    N/A
 *  Description:  definition of CAN module API
 * -----------------------------------------------------------------------------
 * REVISION HISTORY
 * -----------------------------------------------------------------------------
 * Version   Date        Author  Description
 * -----------------------------------------------------------------------------
 * 01.00.00  13/08/2022  Dungnv  Initial version
 *
*******************************************************************************/

/*******************************************************************************
Includes
*******************************************************************************/
/* [SWS_Can_00058], [SWS_Can_00079] */
#include "Dem.h"
#include "Det.h"
#include "MemMap.h"
#include "SchM_Can.h"
#include "EcuM_Cbk.h"
#include "Os.h"
#include "CanIf_Cbk.h"
#include "Can.h"

#include "Can_Internals.h"

extern P2CONST(Can_ConfigType, AUTOMATIC, CAN_APPL_DATA) Glb_CanCfgPtr;
/* [SWS_Can_00103] */
/* Internal CAN Driver state machine */
Can_DrvStsType Gen_CanDriverState = CAN_UNINIT;

#define GetControllerState(index) (*Glb_CanCfgPtr->stCanCtrlrs[index].ptCanCtrlSts)

#if(CAN_VERSIONINFO_API == STD_ON)
/*
 *  Service Name...... : Can_GetVersionInfo
 *  Service ID ....... : 0x07
 *  Sync/Async........ : Synchronous
 *  Reentrancy........ : Reentrant
 *  Parameters (IN)... : None
 *  Parameters (INOUT) : versioninfo
 *  Parameters (OUT).. : None
 *  Return Value...... : None
 *  Register usage ... :
 *  Global variable .. :
 *  Description....... : This function return the version information of module.
 */
/* [SWS_Can_00224] */
FUNC(void, CAN_CODE_SLOW) Can_GetVersionInfo (P2VAR(Std_VersionInfoType, AUTOMATIC, CAN_APPL_DATA) versioninfo)
{
    if (versioninfo == NULL_PTR)
    {
        /* [SWS_Can_00177] */
        #if(CAN_DEV_ERROR_DETECT_API == STD_ON)
        (void)Det_ReportError(CAN_MODULE_ID, CAN_INSTANCE_ID, CAN_SID_GET_VERSIONINFO, CAN_E_PARAM_POINTER);
        #endif
    }
    else
    {
        versioninfo->vendorID = CAN_VENDOR_ID;
        versioninfo->moduleID = CAN_MODULE_ID;
        versioninfo->sw_major_version = SW_MAJOR_VERSION;
        versioninfo->sw_minor_version = SW_MINOR_VERSION;
        versioninfo->sw_patch_version = SW_PATCH_VERSION;
    }
}
#endif

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
/* [SWS_Can_00223] */
FUNC(void, CAN_CODE_SLOW) Can_Init (P2CONST(Can_ConfigType, AUTOMATIC, CAN_APPL_DATA) Config)
{
    uint8 Luc_Count;
    boolean Lbl_InitSts;
    Std_ReturnType Luc_StdResult;

    Luc_StdResult = E_OK;

    /* Verify no null ptr passed as parameter */
    if (NULL_PTR == Config)
    {
        #if(CAN_DEV_ERROR_DETECT_API == STD_ON)
        (void)Det_ReportError(CAN_MODULE_ID, CAN_INSTANCE_ID, CAN_SID_INIT, CAN_E_PARAM_POINTER);
        #endif
        Luc_StdResult = E_NOT_OK;
    }
    else
    {
        /* store the configuration structure pointer to internal global ptr */
        Glb_CanCfgPtr = Config;

        /* Check whether or not CAN Driver is in state CAN_UNINIT */
        if (CAN_UNINIT != Gen_CanDriverState)
        {
            #if(CAN_DEV_ERROR_DETECT_API == STD_ON)
            /* [SWS_Can_00174], [SWS_Can_00259] */
            (void)Det_ReportError(CAN_MODULE_ID, CAN_INSTANCE_ID, CAN_SID_INIT, CAN_E_TRANSITION);
            #endif
            Luc_StdResult = E_NOT_OK;
        }
        /* Check whether or not CAN Controllers is in UNINIT mode */
        else
        {
            /* access configuration structure, loop through all controller
                and check the current sw status of each controller */
            /*  [SWS_Can_00408], [SWS_Can_00259] */
            for (Luc_Count = 0; (Luc_Count < Glb_CanCfgPtr->ucNumCanController) && (E_OK == Luc_StdResult); Luc_Count++)
            {
                /* Check sw status of controller */
                if (CAN_CS_UNINIT != GetControllerState(Luc_Count))
                {
                    #if(CAN_DEV_ERROR_DETECT_API == STD_ON)
                    /* if CAN controller status != CAN_CS_UNINIT then return NG */
                    (void)Det_ReportError(CAN_MODULE_ID, CAN_INSTANCE_ID, CAN_SID_INIT, CAN_E_TRANSITION);
                    #endif
                    Luc_StdResult = E_NOT_OK;
                }
            }
        }
    }

    if (E_OK == Luc_StdResult)
    {
        Lbl_InitSts = TRUE;
        /* static variables, including flags */
        /* general initialization of CAN hardware module: N/A */
        /* specific initialization of CAN controllers */
        for (Luc_Count = 0; Luc_Count < Glb_CanCfgPtr->ucNumCanController; Luc_Count++)
        {
            /* [SWS_Can_00237], [SWS_Can_00236], [SWS_Can_00238], [SWS_Can_00239], [SWS_Can_00245], [SWS_Can_00250] */
            Lbl_InitSts &= Can_HwCtrlInit(Config, Luc_Count);
        }
        if (TRUE == Lbl_InitSts)
        {
            /* [SWS_Can_00246] */
            /* There are no fail during initialized process */
            Gen_CanDriverState = CAN_READY;
        }
        else
        {
            /* There is fail during initialized controllers process */
        }
    }
    else
    {
        /* No action required */
    }
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
/* [SWS_Can_91002] */
FUNC(void, CAN_CODE_SLOW) Can_DeInit (void)
{
    uint8 Luc_Count;
    boolean Lbl_DeInitSts;
    Std_ReturnType Luc_StdResult;

    Luc_StdResult = E_OK;
    /* Check if driver is initialized - Driver not in state CAN_READY */
    if (CAN_READY != Gen_CanDriverState)
    {
        #if(CAN_DEV_ERROR_DETECT_API == STD_ON)
        /* [SWS_Can_91011], [SWS_Can_91010]*/
        (void)Det_ReportError(CAN_MODULE_ID, CAN_INSTANCE_ID, CAN_SID_DEINIT, CAN_E_TRANSITION);
        #endif
        Luc_StdResult = E_NOT_OK;
    }
    /* Check all CAN Controllers is not in START mode */
    else
    {
        /* access configuration structure, loop through all controller and check
        the current sw status of each controller */
        /* [SWS_Can_91012], [SWS_Can_91010]*/
        for (Luc_Count = 0; (Luc_Count < Glb_CanCfgPtr->ucNumCanController) && (E_OK == Luc_StdResult); Luc_Count++)
        {
            /* Check sw status of controller, no controllers in STARTED state before deinit */
            if (CAN_CS_STARTED == *(Glb_CanCfgPtr->stCanCtrlrs[Luc_Count].ptCanCtrlSts))
            {
                /* if CAN controller status == CAN_CS_STARTED then return NG */
                #if(CAN_DEV_ERROR_DETECT_API == STD_ON)
                (void)Det_ReportError(CAN_MODULE_ID, CAN_INSTANCE_ID, CAN_SID_DEINIT, CAN_E_TRANSITION);
                #endif
                Luc_StdResult = E_NOT_OK;
            }
        }
    }

    if (E_OK == Luc_StdResult)
    {
        Lbl_DeInitSts = TRUE;
        /* [SWS_Can_00103], [SWS_Can_91009] */
        /* Change state to UNINIT before perform actual deinit operation in CAN */
        Gen_CanDriverState = CAN_UNINIT;
        /* deinit static variables, including flags */
        /* general de-initialization of CAN hardware module: N/A */
        /* specific de-initialization of CAN controllers */
        for (Luc_Count = 0; Luc_Count < Glb_CanCfgPtr->ucNumCanController; Luc_Count++)
        {
            Lbl_DeInitSts &= Can_HwDeInit(Glb_CanCfgPtr, Luc_Count);
        }
    }
    else
    {
        /* No action required */
    }
}

#if(CAN_SET_BAUDRATE_API == STD_ON)
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
/* [SWS_CAN_00491]  */
FUNC(Std_ReturnType, CAN_CODE_SLOW) Can_SetBaudrate (VAR(uint8, AUTOMATIC) Controller,
                                                    VAR(uint16, AUTOMATIC) BaudRateConfigID)
{

    Std_ReturnType Luc_StdResult;

    Luc_StdResult = E_OK;
    // /* Check if driver is initialized - Driver not in state CAN_READY */
    // if (CAN_READY != Gen_CanDriverState)
    // {
    //     #if(CAN_DEV_ERROR_DETECT_API == STD_ON)
    //     /* [SWS_Can_00492] */
    //     (void)Det_ReportError(CAN_MODULE_ID, CAN_INSTANCE_ID, CAN_SID_SET_BAUDRATE, CAN_E_UNINIT);
    //     #endif
    //     Luc_StdResult = E_NOT_OK;
    // }
    // /* Check if requested Controller value is valid */
    // else if (CAN_LAST_CONTROLLER_ID < Controller)
    // {
    //     /* [SWS_Can_00494]  */
    //     (void)Det_ReportError(CAN_MODULE_ID, CAN_INSTANCE_ID, CAN_SID_SET_BAUDRATE, CAN_E_PARAM_CONTROLLER);
    //     Luc_StdResult = E_NOT_OK;
    // }
    // /* Check if requested BaudRateConfigID value is valid */
    // else if (CAN_MAX_BAUD_CONFIG_ID < BaudRateConfigID)
    // {
    //     /* [SWS_Can_00493] */
    //     (void)Det_ReportError(CAN_MODULE_ID, CAN_INSTANCE_ID,
    //     CAN_SID_SET_BAUDRATE, CAN_E_PARAM_BAUDRATE);
    //     Luc_StdResult = E_NOT_OK;
    // }
    // else
    // {
    //     /* [SWS_Can_00500]?? */
    //     /* No action required */
    // }
    // #endif

    #if(CAN_DEV_ERROR_DETECT_API == STD_ON)
    if (E_OK == Luc_StdResult)
    {
    #endif
        /* Check whether Controller mode is in STOP_MODE if required */

        /* Get the configuration data from input controller and BaudRateConfigID */

        /* Configure the HW of requested Controller */

    #if(CAN_DEV_ERROR_DETECT_API == STD_ON)
    }
    else
    {
        /* No action required */
    }
    #endif
    return Luc_StdResult;
}
#endif

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
FUNC(Std_ReturnType, CAN_CODE_SLOW) Can_SetControllerMode (VAR(uint8, AUTOMATIC) Controller,
    VAR(Can_ControllerStateType, AUTOMATIC) Transition)
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
FUNC(void, CAN_CODE_SLOW) Can_DisableControllerInterrupts (VAR(uint8, AUTOMATIC) Controller)
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
FUNC(void, CAN_CODE_SLOW) Can_EnableControllerInterrupts (VAR(uint8, AUTOMATIC) Controller)
{

}

#if(CAN_WAKEUP_FUNCTIONALITY_API == STD_ON)
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
FUNC(Std_ReturnType, CAN_CODE_SLOW) Can_CheckWakeup (VAR(uint8, AUTOMATIC) Controller)
{

}
#endif

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
FUNC(Std_ReturnType, CAN_CODE_SLOW) Can_GetControllerErrorState (VAR(uint8, AUTOMATIC) ControllerId,
    P2VAR(Can_ErrorStateType, AUTOMATIC, CAN_APPL_DATA) ErrorStatePtr)
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
FUNC(Std_ReturnType, CAN_CODE_SLOW) Can_GetControllerMode (VAR(uint8, AUTOMATIC) Controller,
    P2VAR(Can_ControllerStateType, AUTOMATIC, CAN_APPL_DATA) ControllerModePtr)
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
FUNC(Std_ReturnType, CAN_CODE_SLOW) Can_GetControllerRxErrorCounter (VAR(uint8, AUTOMATIC) ControllerId,
    P2VAR(uint8, AUTOMATIC, CAN_APPL_DATA) RxErrorCounterPtr)
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
FUNC(Std_ReturnType, CAN_CODE_SLOW) Can_GetControllerTxErrorCounter (VAR(uint8, AUTOMATIC) ControllerId,
    P2VAR(uint8, AUTOMATIC, CAN_APPL_DATA) TxErrorCounterPtr)
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
FUNC(Std_ReturnType, CAN_CODE_SLOW) Can_Write (VAR(Can_HwHandleType, AUTOMATIC) Hth,
    P2CONST(Can_PduType, AUTOMATIC, CAN_APPL_DATA) PduInfo)
{

}

#if(CAN_TX_PROCESSING_API == STD_ON)
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
  /* [SWS_Can_00280] */
}
#endif

#if(CAN_RX_PROCESSING_API == STD_ON)
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
  /* [SWS_Can_00280] */
}
#endif

#if(CAN_BUSOFF_PROCESSING_API == STD_ON)
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
  /* [SWS_Can_00280] */
}
#endif

#if(CAN_WAKEUP_PROCESSING_API == STD_ON)
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
  /* [SWS_Can_00280] */
}
#endif

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
  /* [SWS_Can_00280] */
}

#if(CAN_PUBLIC_ICOM_SUPPORT == STD_ON)
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
FUNC(Std_ReturnType, CAN_CODE_SLOW) Can_SetIcomConfiguration (VAR(uint8, AUTOMATIC) Controller,
    VAR(IcomConfigIdType, AUTOMATIC) ConfigurationId)
{

}
#endif