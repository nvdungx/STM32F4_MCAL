/*******************************************************************************
 * COPYRIGHT
 * -----------------------------------------------------------------------------
 * Copyright (c) 2022 by <<DungNV>>. All rights reserved.
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
 * 01.00.00  03/01/2026  Dungnv  Initial version(R24 update)
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

extern const Can_ConfigType* g_CanCfgPtr;

#define INT_MASK_BUSOFF      ((uint32)1 << 10)
#define INT_MASK_WAKEUP      ((uint32)1 << 16)
#define INT_MASK_RX          (((uint32)1 << 4) | ((uint32)1 << 1))
#define INT_MASK_TX          ((uint32)1)
#define INT_NESTED_SET_MAX 255
#define INT_NESTED_SET_MIN 0

/* [SWS_Can_00103] */
/* Internal CAN Driver state machine */
Can_DrvStsType g_enCanDriverState = CAN_UNINIT;

static uint8 m_u8InterruptSetCounter = 0;
static uint32 m_u32InterruptSetting = 0;

#define GetControllerState(index) (*g_CanCfgPtr->ptrCanCtrlrs[index].ptrCanCtrlrSts)

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
void Can_GetVersionInfo(Std_VersionInfoType* versioninfo)
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
void Can_Init(const Can_ConfigType* Config)
{
    uint8 u8Count;
    boolean blInitSts;
    Std_ReturnType u8StdResult;

    u8StdResult = E_OK;

    /* Verify no null ptr passed as parameter */
    if (NULL_PTR == Config)
    {
        #if(CAN_DEV_ERROR_DETECT_API == STD_ON)
        (void)Det_ReportError(CAN_MODULE_ID, CAN_INSTANCE_ID, CAN_SID_INIT, CAN_E_PARAM_POINTER);
        #endif
        u8StdResult = E_NOT_OK;
    }
    else
    {
        /* store the configuration structure pointer to internal global ptr */
        g_CanCfgPtr = Config;

        /* Check whether or not CAN Driver is in state CAN_UNINIT */
        if (CAN_UNINIT != g_enCanDriverState)
        {
            #if(CAN_DEV_ERROR_DETECT_API == STD_ON)
            /* [SWS_Can_00174], [SWS_Can_00259] */
            (void)Det_ReportError(CAN_MODULE_ID, CAN_INSTANCE_ID, CAN_SID_INIT, CAN_E_TRANSITION);
            #endif
            u8StdResult = E_NOT_OK;
        }
        /* Check whether or not CAN Controllers is in UNINIT mode */
        else
        {
            /* access configuration structure, loop through all controller
                and check the current sw status of each controller */
            /*  [SWS_Can_00408, SWS_Can_00259] */
            for (u8Count = 0; (u8Count < g_CanCfgPtr->u8NumCanCtrlr) && (E_OK == u8StdResult); u8Count++)
            {
                /* Check sw status of controller */
                if (CAN_CS_UNINIT != GetControllerState(u8Count))
                {
                    #if(CAN_DEV_ERROR_DETECT_API == STD_ON)
                    /* if CAN controller status != CAN_CS_UNINIT then return NG */
                    (void)Det_ReportError(CAN_MODULE_ID, CAN_INSTANCE_ID, CAN_SID_INIT, CAN_E_TRANSITION);
                    #endif
                    u8StdResult = E_NOT_OK;
                }
            }
        }
    }

    if (E_OK == u8StdResult)
    {
        blInitSts = TRUE;
        /* 1. module global variables: N/A */
        /* 2. general initialization of CAN hardware module: N/A */
        /* 3. specific initialization of CAN controllers */
        for (u8Count = 0; u8Count < g_CanCfgPtr->u8NumCanCtrlr; u8Count++)
        {
            /* [SWS_Can_00237, SWS_Can_00236, SWS_Can_00238, SWS_Can_00239, SWS_Can_00245, SWS_Can_00250] */
            blInitSts &= Can_HwCtrlInit(Config, u8Count);
        }
        if (TRUE == blInitSts)
        {
            /* [SWS_Can_00246] */
            /* There are no fail during initialized process */
            g_enCanDriverState = CAN_READY;
        }
        else
        {
            /* There is fail during initialized controllers process, CanDriverState remain in UNINIT state */
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
void Can_DeInit(void)
{
    uint8 u8Count;
    boolean Lbl_DeInitSts;
    Std_ReturnType u8StdResult;

    u8StdResult = E_OK;
    /* Check if driver is initialized - Driver not in state CAN_READY */
    if (CAN_READY != g_enCanDriverState)
    {
        #if(CAN_DEV_ERROR_DETECT_API == STD_ON)
        /* [SWS_Can_91011], [SWS_Can_91010]*/
        (void)Det_ReportError(CAN_MODULE_ID, CAN_INSTANCE_ID, CAN_SID_DEINIT, CAN_E_TRANSITION);
        #endif
        u8StdResult = E_NOT_OK;
    }
    /* Check all CAN Controllers is not in START mode */
    else
    {
        /* access configuration structure, loop through all controller and check
        the current sw status of each controller */
        /* [SWS_Can_91012], [SWS_Can_91010]*/
        for (u8Count = 0; (u8Count < g_CanCfgPtr->u8NumCanCtrlr) && (E_OK == u8StdResult); u8Count++)
        {
            /* Check sw status of controller, no controllers in STARTED state before deinit */
            if (CAN_CS_STARTED == *(g_CanCfgPtr->ptrCanCtrlrs[u8Count].ptrCanCtrlrSts))
            {
                /* if CAN controller status == CAN_CS_STARTED then return NG */
                #if(CAN_DEV_ERROR_DETECT_API == STD_ON)
                (void)Det_ReportError(CAN_MODULE_ID, CAN_INSTANCE_ID, CAN_SID_DEINIT, CAN_E_TRANSITION);
                #endif
                u8StdResult = E_NOT_OK;
            }
        }
    }

    if (E_OK == u8StdResult)
    {
        Lbl_DeInitSts = TRUE;
        /* [SWS_Can_00103, SWS_Can_91009] */
        /* Change state to UNINIT before perform actual deinit operation in CAN */
        g_enCanDriverState = CAN_UNINIT;
        /* 1. deinit static variables, including flags: N/A */
        /* 2. general de-initialization of CAN hardware module: N/A */
        /* 3. specific de-initialization of CAN controllers */
        for (u8Count = 0; u8Count < g_CanCfgPtr->u8NumCanCtrlr; u8Count++)
        {
            Lbl_DeInitSts &= Can_HwDeInit(g_CanCfgPtr, u8Count);
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
Std_ReturnType Can_SetBaudrate(uint8 Controller, uint16 BaudRateConfigID)
{
    uint8 Luc_HwId;
    Std_ReturnType u8StdResult;
    Can_ControllerType *Lpt_Ctrlr;
    Can_BaudrateConfigType *Lpt_Baudrate;

    u8StdResult = E_OK;
    if (E_OK == Can_CheckDevError(g_CanCfgPtr, Controller, CAN_SID_SET_BAUDRATE, Lpt_Ctrlr))
    {
        Lpt_Baudrate = Can_GetBaudrateCfg(Lpt_Ctrlr, BaudRateConfigID);
        if (NULL_PTR == Lpt_Baudrate)
        {
            /* [SWS_Can_00493] */
            #if(CAN_DEV_ERROR_DETECT_API == STD_ON)
            (void)Det_ReportError(CAN_MODULE_ID, CAN_INSTANCE_ID, CAN_SID_SET_BAUDRATE, CAN_E_PARAM_BAUDRATE);
            #endif
            u8StdResult = E_NOT_OK;
        }
        else
        {
            /* [SWS_Can_00500, SWS_Can_00256, SWS_Can_00062, SWS_Can_00260] */
            /* required CAN controller to be in stop state before change baudrate */
            if (*Lpt_Ctrlr->ptrCanCtrlrSts != CAN_CS_STOPPED)
            {
                u8StdResult = E_NOT_OK;
            }
            else
            {
                /* empty */
            }
        }
    }
    else
    {
        u8StdResult = E_NOT_OK;
    }
    /* Check if requested BaudRateConfigID value is valid */
    if (E_OK == u8StdResult)
    {
        Luc_HwId = Lpt_Ctrlr->u8Id;
        /* Check whether Controller mode is in STOP_MODE(initialization) */
        if ((HwCanCtrlr[Luc_HwId].CtrlNSts->u32MSReg.INAK) != REGISTER_BIT_SET)
        {
            u8StdResult = E_NOT_OK;
        }
        else
        {
            /* [SWS_Can_00422] Configure the HW of requested Controller */
            HwCanCtrlr[Luc_HwId].CtrlNSts->u32BTReg.val = REGISTER_RESET_VALUE;
            HwCanCtrlr[Luc_HwId].CtrlNSts->u32BTReg.SJW = Lpt_Baudrate->u8BaudrateSJW;
            HwCanCtrlr[Luc_HwId].CtrlNSts->u32BTReg.TS2 = Lpt_Baudrate->u8BaudrateSeg2;
            HwCanCtrlr[Luc_HwId].CtrlNSts->u32BTReg.TS1 = Lpt_Baudrate->u8BaudrateSeg1;
            HwCanCtrlr[Luc_HwId].CtrlNSts->u32BTReg.BRP = Lpt_Baudrate->usBaudrateBRP;
        }
    }
    else
    {
        /* empty */
    }
    return u8StdResult;
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
Std_ReturnType Can_SetControllerMode(uint8 Controller, Can_ControllerStateType Transition)
{
    /* [SWS_Can_00230] */
    Std_ReturnType u8StdResult;
    uint8 u8Count;
    Can_ControllerType *Lpt_Ctrlr;

    u8StdResult = E_OK;
    if (E_OK == Can_CheckDevError(g_CanCfgPtr, Controller, CAN_SID_SET_CONTROLLER_MODE, Lpt_Ctrlr))
    {
        /* check invalid transition request */
        /* [SWS_Can_00200] */
        if (E_NOT_OK == Can_CheckValidSetCtrlrModeTrans(*Lpt_Ctrlr->ptrCanCtrlrSts, Transition))
        {
            #if(CAN_DEV_ERROR_DETECT_API == STD_ON)
            (void)Det_ReportError(CAN_MODULE_ID, CAN_INSTANCE_ID, CAN_SID_SET_CONTROLLER_MODE, CAN_E_TRANSITION);
            #endif
            u8StdResult = E_NOT_OK;
        }
        else
        {
            /* empty */
        }
    }
    else
    {
        u8StdResult = E_NOT_OK;
    }

    /* Check if requested BaudRateConfigID value is valid */
    if ((E_OK == u8StdResult) && (*Lpt_Ctrlr->ptrCanCtrlrSts != Transition))
    {
        /* [SWS_Can_00384, SWS_Can_00017] re-init controller same as Can_SetBaudrate and Can_Init when CAN_CS_STARTED
            there is no setting change done by other operation, so no re-init operation require */
        switch (Transition)
        {
        case CAN_CS_STARTED:
            /* [SWS_Can_00384, SWS_Can_00261] */
            /* clear init to transit to hw normal state */
            HwCanCtrlr[Lpt_Ctrlr->u8Id].CtrlNSts->u32MCReg.SLEEP = REGISTER_BIT_CLEAR;
            HwCanCtrlr[Lpt_Ctrlr->u8Id].CtrlNSts->u32MCReg.INRQ = REGISTER_BIT_CLEAR;
            /* [SWS_Can_00196, SWS_Can_00425], enable/disable interrupt setting */
            if (m_u8InterruptSetCounter == INT_NESTED_SET_MIN)
            {
                /* enable interrupt required for current state */
                m_u32InterruptSetting = INT_MASK_BUSOFF * (uint32)(Lpt_Ctrlr->enCanBusoffModeOp == CAN_MODE_OPR_INTERRUPT);
                m_u32InterruptSetting |= INT_MASK_WAKEUP * (uint32)REGISTER_BIT_CLEAR;
                m_u32InterruptSetting |= INT_MASK_RX * (uint32)(Lpt_Ctrlr->enCanRxModeOp != CAN_TRANSCEIVE_POLLING);
                m_u32InterruptSetting |= INT_MASK_TX * (uint32)(Lpt_Ctrlr->enCanTxModeOp != CAN_TRANSCEIVE_POLLING);
                HwCanCtrlr[Lpt_Ctrlr->u8Id].CtrlNSts->u32IEReg.val = m_u32InterruptSetting;
            }
            else
            {
                /* disable interrupt */
            }
            /* [SWS_Can_00398, SWS_Can_00372, SWS_Can_00262] wait for mode change */
            u8StdResult = Can_WaitRegValUntilTimeout((uint32 *)&HwCanCtrlr[Lpt_Ctrlr->u8Id].CtrlNSts->u32MSReg, REGISTER_RESET_VALUE ,CAN_MSR_INIT_ACK);
            break;
        case CAN_CS_STOPPED:
            /* [SWS_Can_00197, SWS_Can_00426], disable all interrupt */
            m_u32InterruptSetting = REGISTER_RESET_VALUE;
            HwCanCtrlr[Lpt_Ctrlr->u8Id].CtrlNSts->u32IEReg.val = m_u32InterruptSetting;

            /* [SWS_Can_00282] abort all transmission, clear all hardware and software FIFOs */
            HwCanCtrlr[Lpt_Ctrlr->u8Id].CtrlNSts->u32TSReg.ABRQ0 = REGISTER_BIT_SET;
            HwCanCtrlr[Lpt_Ctrlr->u8Id].CtrlNSts->u32TSReg.ABRQ1 = REGISTER_BIT_SET;
            HwCanCtrlr[Lpt_Ctrlr->u8Id].CtrlNSts->u32TSReg.ABRQ2 = REGISTER_BIT_SET;

            /* [SWS_Can_00282] cancel all pending receive, release all hardware and software mailboxs */
            for (u8Count = 0; (u8Count < HwCanCtrlr[Lpt_Ctrlr->u8Id].CtrlNSts->u32RF0Reg.FMP0) ||
                (HwCanCtrlr[Lpt_Ctrlr->u8Id].CtrlNSts->u32RF0Reg.RFOM0 == REGISTER_BIT_SET); u8Count++)
            {
                HwCanCtrlr[Lpt_Ctrlr->u8Id].CtrlNSts->u32RF0Reg.RFOM0 = REGISTER_BIT_SET;
            }
            for (u8Count = 0; (u8Count < HwCanCtrlr[Lpt_Ctrlr->u8Id].CtrlNSts->u32RF1Reg.FMP1) ||
                (HwCanCtrlr[Lpt_Ctrlr->u8Id].CtrlNSts->u32RF1Reg.RFOM1 == REGISTER_BIT_SET); u8Count++)
            {
                HwCanCtrlr[Lpt_Ctrlr->u8Id].CtrlNSts->u32RF1Reg.RFOM1 = REGISTER_BIT_SET;
            }

            /* [SWS_Can_00263] back to hw init state */
            HwCanCtrlr[Lpt_Ctrlr->u8Id].CtrlNSts->u32MCReg.SLEEP = REGISTER_BIT_CLEAR;
            HwCanCtrlr[Lpt_Ctrlr->u8Id].CtrlNSts->u32MCReg.INRQ = REGISTER_BIT_SET;
            /* [SWS_Can_00372, SWS_Can_00264, SWS_Can_00268] */
            u8StdResult = Can_WaitRegValUntilTimeout((uint32 *)&HwCanCtrlr[Lpt_Ctrlr->u8Id].CtrlNSts->u32MSReg, CAN_MSR_INIT_ACK ,CAN_MSR_INIT_ACK);
            break;
        case CAN_CS_SLEEP:
            /* [SWS_Can_00294] */
            /* [SWS_Can_00257, SWS_Can_00265] to hw sleep state */
            HwCanCtrlr[Lpt_Ctrlr->u8Id].CtrlNSts->u32MCReg.AWUM = REGISTER_BIT_SET;
            HwCanCtrlr[Lpt_Ctrlr->u8Id].CtrlNSts->u32MCReg.INRQ = REGISTER_BIT_CLEAR;
            HwCanCtrlr[Lpt_Ctrlr->u8Id].CtrlNSts->u32MCReg.SLEEP = REGISTER_BIT_SET;
            if (m_u8InterruptSetCounter == INT_NESTED_SET_MIN)
            {
                m_u32InterruptSetting = INT_MASK_WAKEUP * (uint32)(Lpt_Ctrlr->enCanWakeupModeOp == CAN_MODE_OPR_INTERRUPT);
                HwCanCtrlr[Lpt_Ctrlr->u8Id].CtrlNSts->u32IEReg.val = m_u32InterruptSetting;
            }
            else
            {
                /* empty */
            }
            /* [SWS_Can_00372, SWS_Can_00266] */
            u8StdResult = Can_WaitRegValUntilTimeout((uint32 *)&HwCanCtrlr[Lpt_Ctrlr->u8Id].CtrlNSts->u32MSReg, CAN_MSR_SLEEP_ACK ,CAN_MSR_SLEEP_ACK);
            break;
        default:
            /* empty */
            break;
        }
        if (u8StdResult == E_OK)
        {
            /* [SWS_Can_00017] */
            *Lpt_Ctrlr->ptrCanCtrlrSts = Transition;
        }
        else
        {
            /* empty */
        }
    }
    else
    {
        /* No action required */
    }
    return u8StdResult;
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
void Can_DisableControllerInterrupts(uint8 Controller)
{
    /* [SWS_Can_00231] */
    Std_ReturnType u8StdResult;
    Can_ControllerType *Lpt_Ctrlr;

    u8StdResult = E_OK;
    /* [SWS_Can_00049] */
    if (E_OK == Can_CheckDevError(g_CanCfgPtr, Controller, CAN_SID_DISABLE_CONTROLLER_INTERRUPT, Lpt_Ctrlr))
    {
        /* [SWS_Can_00202] */
        if (m_u8InterruptSetCounter != INT_NESTED_SET_MAX)
        {
            m_u8InterruptSetCounter++;
        }
        else
        {
            /* empty */
        }
        /* [SWS_Can_00204] */
        HwCanCtrlr[Lpt_Ctrlr->u8Id].CtrlNSts->u32IEReg.val = REGISTER_RESET_VALUE;
    }
    else
    {
        /* empty */
    }
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
void Can_EnableControllerInterrupts(uint8 Controller)
{
    /* [SWS_Can_00232] */
    Can_ControllerType *Lpt_Ctrlr;

    if (E_OK == Can_CheckDevError(g_CanCfgPtr, Controller, CAN_SID_ENABLE_CONTROLLER_INTERRUPT, Lpt_Ctrlr))
    {
        /* [SWS_Can_00208] */
        if (m_u8InterruptSetCounter != INT_NESTED_SET_MIN)
        {
            m_u8InterruptSetCounter--;
        }
        else
        {
            /* [SWS_Can_00050] */
            HwCanCtrlr[Lpt_Ctrlr->u8Id].CtrlNSts->u32IEReg.val = m_u32InterruptSetting;
        }
    }
    else
    {
        /* empty */
    }
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
Std_ReturnType Can_CheckWakeup(uint8 Controller)
{
    /* [SWS_Can_00360] */
    Std_ReturnType u8StdResult;
    Can_ControllerType *Lpt_Ctrlr;

    u8StdResult = E_OK;
    if (E_OK == Can_CheckDevError(g_CanCfgPtr, Controller, CAN_SID_CHECK_WAKEUP, Lpt_Ctrlr))
    {

    }
    else
    {
        u8StdResult = E_NOT_OK;
    }
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
Std_ReturnType Can_GetControllerErrorState(uint8 ControllerId, Can_ErrorStateType* ErrorStatePtr)
{
    Std_ReturnType u8StdResult;
    Can_ControllerType *Lpt_Ctrlr;

    u8StdResult = E_OK;
    if (E_OK == Can_CheckDevError(g_CanCfgPtr, ControllerId, CAN_SID_GET_CONTROLLER_ERROR_STATE, Lpt_Ctrlr))
    {

    }
    else
    {
        u8StdResult = E_NOT_OK;
    }
    if (E_OK == u8StdResult)
    {

    }
    else
    {
        /* empty */
    }
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
Std_ReturnType Can_GetControllerMode(uint8 Controller, Can_ControllerStateType* ControllerModePtr)
{
    Std_ReturnType u8StdResult;
    Can_ControllerType *Lpt_Ctrlr;

    u8StdResult = E_OK;
    if (E_OK == Can_CheckDevError(g_CanCfgPtr, Controller, CAN_SID_GET_CONTROLLER_MODE, Lpt_Ctrlr))
    {

    }
    else
    {
        u8StdResult = E_NOT_OK;
    }
    if (E_OK == u8StdResult)
    {

    }
    else
    {
        /* empty */
    }
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
Std_ReturnType Can_GetControllerRxErrorCounter(uint8 ControllerId, uint8* RxErrorCounterPtr)
{
    Std_ReturnType u8StdResult;
    Can_ControllerType *Lpt_Ctrlr;

    u8StdResult = E_OK;
    if (E_OK == Can_CheckDevError(g_CanCfgPtr, ControllerId, CAN_SID_GET_CONTROLLER_RX_ERROR_COUNTER, Lpt_Ctrlr))
    {

    }
    else
    {
        u8StdResult = E_NOT_OK;
    }
    if (E_OK == u8StdResult)
    {

    }
    else
    {
        /* empty */
    }
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
Std_ReturnType Can_GetControllerTxErrorCounter(uint8 ControllerId,
                                                    uint8* TxErrorCounterPtr)
{
    Std_ReturnType u8StdResult;
    Can_ControllerType *Lpt_Ctrlr;

    u8StdResult = E_OK;
    if (E_OK == Can_CheckDevError(g_CanCfgPtr, ControllerId, CAN_SID_GET_CONTROLLER_TX_ERROR_COUNTER, Lpt_Ctrlr))
    {

    }
    else
    {
        u8StdResult = E_NOT_OK;
    }
    if (E_OK == u8StdResult)
    {

    }
    else
    {
        /* empty */
    }
}

/*
 *  Service Name...... : Can_GetCurrentTime
 *  Service ID      .. : 0x32
 *  Sync/Async........ : Synchronous
 *  Reentrancy........ : Non Reentrant (for the same ControllerId)
 *  Parameters (IN)... : ControllerId
 *  Parameters (INOUT) : None
 *  Parameters (OUT).. : TimeStampPtr
 *  Return Value...... : Std_ReturnType(E_OK/E_NOT_OK)
 *  Register usage     :
 *  Global variable    :
 *  Description....... : Returns a time value out of the HW registers according to the capability of the HW
 */
Std_ReturnType Can_GetCurrentTime(uint8 ControllerId, Can_TimeStampType* TimeStampPtr)
{
    Std_ReturnType u8StdResult;
    Can_ControllerType *Lpt_Ctrlr;

    u8StdResult = E_OK;
    if (E_OK == Can_CheckDevError(g_CanCfgPtr, ControllerId, CAN_SID_GET_TIMESTAMP, Lpt_Ctrlr))
    {
        /* [SWS_Can_00493] */
        if (NULL_PTR == TimeStampPtr)
        {
            #if(CAN_DEV_ERROR_DETECT_API == STD_ON)
            (void)Det_ReportError(CAN_MODULE_ID, CAN_INSTANCE_ID, CAN_SID_GET_TIMESTAMP,  CAN_E_PARAM_POINTER);
            #endif
            u8StdResult = E_NOT_OK;
        }
        else
        {
            /* empty */
        }
    }
    else
    {
        u8StdResult = E_NOT_OK;
    }
    if (E_OK == u8StdResult)
    {

    }
    else
    {
        /* empty */
    }
}

/*
 *  Service Name...... : Can_EnableEgressTimeStamp
 *  Service ID      .. : 0x33
 *  Sync/Async........ : Synchronous
 *  Reentrancy........ : Non Reentrant (for same Hth)
 *  Parameters (IN)... : Hth
 *  Parameters (INOUT) : None
 *  Parameters (OUT).. : None
 *  Return Value...... : None
 *  Register usage     :
 *  Global variable    :
 *  Description....... : Activates egress time stamping on a dedicated HTH.
 */
void Can_EnableEgressTimeStamp(Can_HwHandleType Hth)
{

}

/*
 *  Service Name...... : Can_GetEgressTimeStamp
 *  Service ID      .. : 0x34
 *  Sync/Async........ : Synchronous
 *  Reentrancy........ : Non Reentrant (for same TxPduId)
 *  Parameters (IN)... : TxPduId, Hth
 *  Parameters (INOUT) : TimeStampPtr
 *  Parameters (OUT).. : None
 *  Return Value...... : Std_ReturnType(E_OK/E_NOT_OK)
 *  Register usage     :
 *  Global variable    :
 *  Description....... : Reads back the egress time stamp on a dedicated message object.
 *                       It needs to be called within the TxConfirmation() function.
 */
Std_ReturnType Can_GetEgressTimeStamp(PduIdType TxPduId, Can_HwHandleType Hth, Can_TimeStampType* TimeStampPtr)
{

}

/*
 *  Service Name...... : Can_GetIngressTimeStamp
 *  Service ID      .. : 0x35
 *  Sync/Async........ : Synchronous
 *  Reentrancy........ : Non Reentrant (for same Hrh)
 *  Parameters (IN)... : Hrh
 *  Parameters (INOUT) : TimeStampPtr
 *  Parameters (OUT).. : None
 *  Return Value...... : Std_ReturnType(E_OK/E_NOT_OK)
 *  Register usage     :
 *  Global variable    :
 *  Description....... : Reads back the ingress time stamp on a dedicated message object.
 *                       It needs to be called within the RxIndication() function.
 */
Std_ReturnType Can_GetIngressTimeStamp(Can_HwHandleType Hrh, Can_TimeStampType* TimeStampPtr)
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
Std_ReturnType Can_Write(Can_HwHandleType Hth, const Can_PduType* PduInfo)
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
void Can_MainFunction_Write(void)
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
void Can_MainFunction_Read(void)
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
void Can_MainFunction_BusOff(void)
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
void Can_MainFunction_Wakeup(void)
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
void Can_MainFunction_Mode(void)
{
  /* [SWS_Can_00280] */
}
