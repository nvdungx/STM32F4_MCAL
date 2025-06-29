/*******************************************************************************
 * COPYRIGHT
 * -----------------------------------------------------------------------------
 * Copyright (c) 2022 by <<>>. All rights reserved.
 * -----------------------------------------------------------------------------
 * FILE DESCRIPTION
 *  File:         Can_Internals.c
 *  Component:    Source
 *  Module:       CAN
 *  Generator:    N/A
 *  Description:  definition for internal functions.
 * -----------------------------------------------------------------------------
 * REVISION HISTORY
 * -----------------------------------------------------------------------------
 * Version   Date        Author  Description
 * -----------------------------------------------------------------------------
 * 01.00.00  13/08/2022  Dungnv  Initial version
 *
*******************************************************************************/

#include "Can_IOCommon.h"
#include "Can_Internals.h"
#include "Os.h"
#include "Det.h"


/* scale        |mode,
1:32bit, 0:16bit|1:IdentList, 0:IdentMask */
#define FLT_ATTR_EXTENDED_MASKED    0b10
#define FLT_ATTR_EXTENDED_IDENT     0b11
#define FLT_ATTR_STANDARD_MASKED    0b00
#define FLT_ATTR_STANDARD_IDENT     0b01
#define IGNORE_MODE_BIT             ((uint32)0x00000003)
#define GetExtendedRuleConfig(val)   ((((uint32)val & 0x000007FF) << 21) | (((uint32)val & 0x1FFFF800) >> 11) << 3 | (uint32)1 << 2)
#define GetStandardRuleConfig(val)   (((uint16)val & 0x07FF) << 5 | (uint16)1 << 3)

#define GetCurrentStateMask(state) ((uint8)(state == CAN_CS_STARTED) | ((uint8)(state == CAN_CS_STOPPED) << 1) | ((uint8)(state == CAN_CS_SLEEP) << 2))
#define GetTargetStateMask(state) (GetCurrentStateMask(state) << 4)

/*
 *  Service Name...... : Can_HwCtrlInit
 *  Service ID      .. : None
 *  Sync/Async........ : Synchronous
 *  Reentrancy........ : Non Reentrant
 *  Parameters (IN)... : Controller
 *  Parameters (INOUT) : None
 *  Parameters (OUT).. : None
 *  Return Value...... : boolean(true/false)
 *  Register usage     :
 *  Global variable    :
 *  Description....... : Configure CAN controller
 */
boolean Can_HwCtrlInit(const Can_ConfigType* ConfigPtr, uint8 CtrlrIdx)
{
    boolean blInitSts;
    uint8 u8FilterBankType;
    uint8 u8ObjectIdx;
    uint8 u8FilterIdx;
    uint8 u8HwId;
    Can_ControllerType *Lpt_Ctrlr;
    blInitSts = TRUE;
    Lpt_Ctrlr = &ConfigPtr->ptrCanCtrlrs[CtrlrIdx];
    u8HwId = ConfigPtr->ptrCanCtrlrs[CtrlrIdx].u8CanCtrlId;

    /* CAN controller configuration: master control, interrupt, baudrate, filter, [status?] */

    /* Request CAN hw controller exit SLEEP mode */
    HwCanCtrlr[u8HwId].CtrlNSts->u32MCReg.SLEEP = REGISTER_BIT_CLEAR;
    /* Request CAN hw controller to enter INITIALIZATION mode */
    HwCanCtrlr[u8HwId].CtrlNSts->u32MCReg.INRQ = REGISTER_BIT_SET;
    /* Poll the Master Status register for Initialization acknowledge status */
    if (E_OK != Can_WaitRegValUntilTimeout((uint32 *)&HwCanCtrlr[u8HwId].CtrlNSts->u32MSReg, CAN_MSR_INIT_ACK, CAN_MSR_INIT_ACK))
    {
        *(ConfigPtr->ptrCanCtrlrs[u8HwId].ptrCanCtrlrSts) = CAN_CS_UNINIT;
        blInitSts = FALSE;
    }
    else
    {
        /* [SWS_Can_00419, SWS_Can_00033, SWS_Can_00053] */
        /* Clear all CAN hw unit interrupt setting by default, interrupt shall be configured by SetControllerMode API */
        HwCanCtrlr[u8HwId].CtrlNSts->u32IEReg.val = REGISTER_RESET_VALUE;
        /* Clear all setting bits in Master Configuration Reg except Mode control bit */
        HwCanCtrlr[u8HwId].CtrlNSts->u32MCReg.val &= IGNORE_MODE_BIT;
        #if(CAN_SUPPORT_TTCAN == STD_ON)
        /* Enable time trigger communication mode */
        HwCanCtrlr[u8HwId].CtrlNSts->u32MCReg.TTCM = REGISTER_BIT_SET;
        /* No automatic retransmission */
        HwCanCtrlr[u8HwId].CtrlNSts->u32MCReg.NART = REGISTER_BIT_SET;
        #endif
        #if(CAN_MULTIPLEXED_TRANSMISSION == STD_ON)
        /* [SWS_Can_00277] */
        /* Priority driven by the request order (chronologically) when several mailboxes are pending at the same time */
        HwCanCtrlr[u8HwId].CtrlNSts->u32MCReg.TXFP = REGISTER_BIT_SET;
        #endif

        /* setup CAN controller default baudrate */
        HwCanCtrlr[u8HwId].CtrlNSts->u32BTReg.val = REGISTER_RESET_VALUE;
        HwCanCtrlr[u8HwId].CtrlNSts->u32BTReg.SJW = Lpt_Ctrlr->ptDefaultBaudrateCfg->u8BaudrateSJW;
        HwCanCtrlr[u8HwId].CtrlNSts->u32BTReg.TS2 = Lpt_Ctrlr->ptDefaultBaudrateCfg->u8BaudrateSeg2;
        HwCanCtrlr[u8HwId].CtrlNSts->u32BTReg.TS1 = Lpt_Ctrlr->ptDefaultBaudrateCfg->u8BaudrateSeg1;
        HwCanCtrlr[u8HwId].CtrlNSts->u32BTReg.BRP = Lpt_Ctrlr->ptDefaultBaudrateCfg->usBaudrateBRP;

        /* configure hardware object and hardware filter of CAN controller */
        /* enter initialization mode to config filter */
        HwCanCtrlr[u8HwId].Filter->u32FMReg.FINIT = REGISTER_BIT_SET;

        /* define the start bank for the CAN2 interface (Slave) in the range 0 to 27 */
        if (u8HwId == CAN_HW_CTRLR1)
        {
            HwCanCtrlr[u8HwId].Filter->u32FMReg.CAN2SB = Lpt_Ctrlr->u8FltBankStart;
        }
        else
        {
            /* empty */
        }

        for (u8ObjectIdx = 0; u8ObjectIdx < CAN_HW_OBJS_SIZE; u8ObjectIdx++)
        {
            if (ConfigPtr->stCanHwObjs[u8ObjectIdx].enObjType != CAN_OBJ_RECEIVE)
            {
                /* skip if not RECEIVE obj */
                continue;
            }
            else
            {
                /* empty */
            }
            /* 28 filter bank, 56 regs either 32 bit or 16 bit mask/identifier
            max 56*2 = 112 filter with 16bit identifiers -> 14 bytes tracking status
            1 bank, 4 bit track per FIFO, ident/mask type, scale(3bit attribute) */
            for (u8FilterIdx = 0; u8FilterIdx < ConfigPtr->stCanHwObjs[u8ObjectIdx].u8CanHwFilterSize; u8FilterIdx++)
            {
                /* bit2: standard = 0 else 1, bit1 IdentMask = 0 else 1, bit0 FIFOId(config either 0 or 1 << tool gen check) */
                u8FilterBankType = ((uint8)(ConfigPtr->stCanHwObjs[u8ObjectIdx].enObjIdType != CAN_ID_STANDARD) << 2) |
                    ((uint8)(ConfigPtr->stCanHwObjs[u8ObjectIdx].stCanHwFilters[u8FilterIdx].blMasked == FALSE) << 1) |
                    ConfigPtr->stCanHwObjs[u8ObjectIdx].u8HwRxFIFOId;
                (void)Can_ConfigFilterRule(u8HwId, Lpt_Ctrlr->u8FltBankStart, Lpt_Ctrlr->u8FltBankEnd, u8FilterBankType,
                                        &ConfigPtr->stCanHwObjs[u8ObjectIdx].stCanHwFilters[u8FilterIdx]);
            }
        }

        /* exit initialization mode to config filter */
        HwCanCtrlr[u8HwId].Filter->u32FMReg.FINIT = REGISTER_BIT_CLEAR;
        /* [SWS_Can_00259] Change software state of CAN controllers to STOPPED */
        *(ConfigPtr->ptrCanCtrlrs[u8HwId].ptrCanCtrlrSts) = CAN_CS_STOPPED;
    }
    return blInitSts;
}

/*
 *  Service Name...... : Can_HwDeInit
 *  Service ID      .. : None
 *  Sync/Async........ : Synchronous
 *  Reentrancy........ : Non Reentrant
 *  Parameters (IN)... : Controller
 *  Parameters (INOUT) : None
 *  Parameters (OUT).. : None
 *  Return Value...... : boolean(true/false)
 *  Register usage     :
 *  Global variable    :
 *  Description....... : deinitialize static variables, including flags,
 *    Common setting for the complete CAN HW unit
 *    CAN controller specific settings for each CAN controller.
 */
boolean Can_HwDeInit(const Can_ConfigType* ConfigPtr, uint8 CtrlrIdx)
{
    boolean Lbl_DeInitSts;
    uint8 Luc_Count;
    uint8 u8HwId;
    u8HwId = ConfigPtr->ptrCanCtrlrs[CtrlrIdx].u8Id;
    /* change to initialization mode and clear out register setting */
    HwCanCtrlr[u8HwId].CtrlNSts->u32MCReg.SLEEP = REGISTER_BIT_CLEAR;
    HwCanCtrlr[u8HwId].CtrlNSts->u32MCReg.INRQ = REGISTER_BIT_SET;
    if (E_OK != Can_WaitRegValUntilTimeout((uint32 *)&HwCanCtrlr[u8HwId].CtrlNSts->u32MSReg, CAN_MSR_INIT_ACK, CAN_MSR_INIT_ACK))
    {
        Lbl_DeInitSts = FALSE;
    }
    else
    {
        /* [SWS_Can_00053], [SWS_Can_00407] */
        HwCanCtrlr[u8HwId].CtrlNSts->u32IEReg.val = REGISTER_RESET_VALUE;
        /* clear baudrate */
        HwCanCtrlr[u8HwId].CtrlNSts->u32BTReg.val = REGISTER_RESET_VALUE;
        HwCanCtrlr[u8HwId].Filter->u32FMReg.val = REGISTER_RESET_VALUE;
        HwCanCtrlr[u8HwId].Filter->u32FMReg.FINIT = REGISTER_BIT_SET;
        for (Luc_Count = 0; Luc_Count < CAN_HW_FILTER_BANK_MAX; Luc_Count++)
        {
            HwCanCtrlr[u8HwId].Filter->u32FM1Reg = REGISTER_RESET_VALUE;
            HwCanCtrlr[u8HwId].Filter->u32FS1Reg = REGISTER_RESET_VALUE;
            HwCanCtrlr[u8HwId].Filter->u32FFA1Reg = REGISTER_RESET_VALUE;
            HwCanCtrlr[u8HwId].Filter->u32FReg[Luc_Count][FILTER_BANK_ID] = REGISTER_RESET_VALUE;
            HwCanCtrlr[u8HwId].Filter->u32FReg[Luc_Count][FILTER_BANK_MASK] = REGISTER_RESET_VALUE;
            HwCanCtrlr[u8HwId].Filter->u32FA1Reg = REGISTER_RESET_VALUE;
        }
        HwCanCtrlr[u8HwId].Filter->u32FMReg.FINIT = REGISTER_BIT_CLEAR;

        HwCanCtrlr[u8HwId].CtrlNSts->u32MCReg.val = REGISTER_RESET_VALUE;
        /* Request CAN hw controller into sleep mode by default */
        HwCanCtrlr[u8HwId].CtrlNSts->u32MCReg.INRQ = REGISTER_BIT_CLEAR;
        HwCanCtrlr[u8HwId].CtrlNSts->u32MCReg.SLEEP = REGISTER_BIT_SET;
        if (E_OK != Can_WaitRegValUntilTimeout((uint32 *)&HwCanCtrlr[u8HwId].CtrlNSts->u32MSReg, CAN_MSR_SLEEP_ACK, CAN_MSR_SLEEP_ACK))
        {
            Lbl_DeInitSts = FALSE;
        }
        else
        {
            Lbl_DeInitSts = TRUE;
            *(ConfigPtr->ptrCanCtrlrs[CtrlrIdx].ptrCanCtrlrSts) = CAN_CS_UNINIT;
        }
    }
    return Lbl_DeInitSts;
}

/*
 *  Service Name...... : Can_ConfigFilterRule
 *  Service ID      .. : None
 *  Sync/Async........ : Synchronous
 *  Reentrancy........ : Non Reentrant
 *  Parameters (IN)... : Idx, FltBankStart, FltBankEnd, u8FilterBankType, HwFilterRule
 *  Parameters (INOUT) : None
 *  Parameters (OUT).. : None
 *  Return Value...... : boolean(TRUE/FALSE)
 *  Register usage     :
 *  Global variable    :
 *  Description....... : fill in filter rule to available CAN hardware filter bank.
 * Configuration tool: shall generate HwFilterRule to fill out the most of hw bank according to
 * "Figure 299. Filter bank scale configuration - register organization"
 */
boolean Can_ConfigFilterRule(uint8 Idx, uint8 FltBankStart, uint8 FltBankEnd, uint8 u8FilterBankType, Can_HwFilterType *HwFilterRule)
{
    uint8 Luc_Count;
    boolean Lbl_Success;
    /* if init(i.e != 0 then bank has attributes, check and find available) */
    /* 1 bit = 16 byte data */
    static uint8 Lar_FltBankCfgSts[CAN_HW_FILTER_BANK_MAX] = {0b0000};
    /* filter bank only have 1 attributes */
    static uint8 Lar_FltBankAttr[CAN_HW_FILTER_BANK_MAX] = {0b000};

    Lbl_Success = FALSE;
    /* One 32-bit filter for the STDID[10:0], EXTID[17:0], IDE and RTR bits.
        Two 16-bit filters for the STDID[10:0], RTR, IDE and EXTID[17:15] bits */
    /* filter scale: 11bit or 29bit
        |STID[10:3] | STID[2:0] EXID[17:13] | EXID[12:5] | EXID[4:0] IDE RTR 0|*/
    for (Luc_Count = FltBankStart; (Luc_Count <= FltBankEnd) && (Lbl_Success == FALSE); Luc_Count++)
    {
        // if bank status is not yet configured then load filter rule to it
        if (Lar_FltBankCfgSts[Luc_Count] == 0)
        {
            /* filter scale: 11bit or 29bit */
            CLEAR_BIT32(HwCanCtrlr[Idx].Filter->u32FS1Reg, Luc_Count);
            HwCanCtrlr[Idx].Filter->u32FS1Reg |= ((u8FilterBankType >> 2) & 0x01) << Luc_Count;

            /* filter FIFO assignment */
            CLEAR_BIT32(HwCanCtrlr[Idx].Filter->u32FFA1Reg, Luc_Count);
            HwCanCtrlr[Idx].Filter->u32FFA1Reg |= (u8FilterBankType & 0x01) << Luc_Count;

            /* set filter mode: CLEAR Identifier Mask or SET Identifier List */
            CLEAR_BIT32(HwCanCtrlr[Idx].Filter->u32FM1Reg, Luc_Count);
            HwCanCtrlr[Idx].Filter->u32FM1Reg |= ((u8FilterBankType >> 1) & 0x01) << Luc_Count;

            switch ((u8FilterBankType >> 1) & 0x03)
            {
            case FLT_ATTR_EXTENDED_MASKED:
                HwCanCtrlr[Idx].Filter->u32FReg[Luc_Count][FILTER_BANK_ID] = GetExtendedRuleConfig(HwFilterRule->u32HwFilterCode);
                HwCanCtrlr[Idx].Filter->u32FReg[Luc_Count][FILTER_BANK_MASK] = GetExtendedRuleConfig(HwFilterRule->u32HwFilterMask);
                Lar_FltBankCfgSts[Luc_Count] |= 0b1111;
                break;
            case FLT_ATTR_EXTENDED_IDENT:
                HwCanCtrlr[Idx].Filter->u32FReg[Luc_Count][FILTER_BANK_ID] = GetExtendedRuleConfig(HwFilterRule->u32HwFilterCode);
                /* clear unused */
                HwCanCtrlr[Idx].Filter->u32FReg[Luc_Count][FILTER_BANK_MASK] = REGISTER_RESET_VALUE;
                Lar_FltBankCfgSts[Luc_Count] |= 0b0011;
                break;
            case FLT_ATTR_STANDARD_MASKED:
                HwCanCtrlr[Idx].Filter->u32FReg[Luc_Count][FILTER_BANK_ID] = (uint16)GetStandardRuleConfig(HwFilterRule->u32HwFilterCode);
                HwCanCtrlr[Idx].Filter->u32FReg[Luc_Count][FILTER_BANK_ID] |= (uint16)GetStandardRuleConfig(HwFilterRule->u32HwFilterMask) << 16;
                /* clear unused */
                HwCanCtrlr[Idx].Filter->u32FReg[Luc_Count][FILTER_BANK_MASK] = REGISTER_RESET_VALUE;
                Lar_FltBankCfgSts[Luc_Count] |= 0b0011;
                break;
            case FLT_ATTR_STANDARD_IDENT:
                HwCanCtrlr[Idx].Filter->u32FReg[Luc_Count][FILTER_BANK_ID] = (uint16)GetStandardRuleConfig(HwFilterRule->u32HwFilterCode);
                HwCanCtrlr[Idx].Filter->u32FReg[Luc_Count][FILTER_BANK_ID] = (uint16)0x0000 << 16;
                HwCanCtrlr[Idx].Filter->u32FReg[Luc_Count][FILTER_BANK_MASK] = REGISTER_RESET_VALUE;
                Lar_FltBankCfgSts[Luc_Count] |= 0b0001;
                break;
            default:
                break;
            }

            /* activate filter */
            SET_BIT32(HwCanCtrlr[Idx].Filter->u32FA1Reg, Luc_Count);

            /* store attribute for this bank */
            Lar_FltBankAttr[Luc_Count] = u8FilterBankType;
            Lbl_Success = TRUE;
        }
        else
        {
            // check if current rule u8FilterBankType match
            if (Lar_FltBankAttr[Luc_Count] == u8FilterBankType)
            {
                switch ((u8FilterBankType >> 1) & 0b11)
                {
                case FLT_ATTR_EXTENDED_MASKED:
                    /* should not fall into this since this should get a bank fill completely */
                    break;
                case FLT_ATTR_EXTENDED_IDENT:
                    /* 1st reg bank ident should be filled with extended ident*/
                    HwCanCtrlr[Idx].Filter->u32FReg[Luc_Count][FILTER_BANK_MASK] = GetExtendedRuleConfig(HwFilterRule->u32HwFilterCode);
                    Lar_FltBankCfgSts[Luc_Count] |= 0b1100;
                    break;
                case FLT_ATTR_STANDARD_MASKED:
                    /* 1st reg bank ident should be filled with standard ident and mask */
                    HwCanCtrlr[Idx].Filter->u32FReg[Luc_Count][FILTER_BANK_MASK] = (uint16)GetStandardRuleConfig(HwFilterRule->u32HwFilterCode);
                    HwCanCtrlr[Idx].Filter->u32FReg[Luc_Count][FILTER_BANK_MASK] |= (uint16)GetStandardRuleConfig(HwFilterRule->u32HwFilterMask) << 16;
                    Lar_FltBankCfgSts[Luc_Count] |= 0b1100;
                    break;
                case FLT_ATTR_STANDARD_IDENT:
                    /* 1st 2 byte of Ident reg should be fill with standard ident, check for next available slot */
                    if ((Lar_FltBankCfgSts[Luc_Count] & 0b0010) == 0)
                    {
                        HwCanCtrlr[Idx].Filter->u32FReg[Luc_Count][FILTER_BANK_ID] |= (uint16)GetStandardRuleConfig(HwFilterRule->u32HwFilterCode) << 16;
                        Lar_FltBankCfgSts[Luc_Count] |= 0b0010;
                    }
                    else if ((Lar_FltBankCfgSts[Luc_Count] & 0b0100) == 0)
                    {
                        HwCanCtrlr[Idx].Filter->u32FReg[Luc_Count][FILTER_BANK_MASK] = (uint16)GetStandardRuleConfig(HwFilterRule->u32HwFilterCode);
                        Lar_FltBankCfgSts[Luc_Count] |= 0b0100;
                    }
                    else if ((Lar_FltBankCfgSts[Luc_Count] & 0b1000) == 0)
                    {
                        HwCanCtrlr[Idx].Filter->u32FReg[Luc_Count][FILTER_BANK_MASK] |= (uint32)GetStandardRuleConfig(HwFilterRule->u32HwFilterCode) << 16;
                        Lar_FltBankCfgSts[Luc_Count] |= 0b1000;
                    }
                    else
                    {
                        /* should not fall into this */
                    }
                    break;
                default:
                    break;
                }
                /* no need to set bank attribute or active filter since it's done by first bank setup */
                Lbl_Success = TRUE;
            }
            else
            {
                /* skip, look for next available bank or bank with same attribute */
            }
        }
    }
}

/*
 *  Service Name...... : Can_WaitRegValUntilTimeout
 *  Service ID      .. : None
 *  Sync/Async........ : Synchronous
 *  Reentrancy........ : Reentrant
 *  Parameters (IN)... : RegAddr, ExpectedValue
 *  Parameters (INOUT) : None
 *  Parameters (OUT).. : None
 *  Return Value...... : Std_ReturnType(E_OK/E_NOT_OK)
 *  Register usage     :
 *  Global variable    :
 *  Description....... : wait until input register match expected value or timeout occur.
 */
Std_ReturnType Can_WaitRegValUntilTimeout(uint32* RegAddr, uint32 ExpectedValue, uint32 Mask)
{
    TickType Lul_PreOsTick = 0;
    TickType Lul_CurOsTick = 0;
    Std_ReturnType Luc_ReturnVal;
    Luc_ReturnVal = E_NOT_OK;
    GetCounterValue(CAN_OS_COUNTER, &Lul_PreOsTick);
    do
    {
        GetCounterValue(CAN_OS_COUNTER, &Lul_CurOsTick);
        /* [SWS_Can_00281] */
        if (((*(volatile uint32 *)RegAddr) & Mask) == ExpectedValue)
        {
            Luc_ReturnVal = E_OK;
            break;
        }
    } while ((Lul_CurOsTick - Lul_PreOsTick) < (uint32)(CAN_TIMEOUT_DURATION*1E6));
    return Luc_ReturnVal;
}

Can_ControllerType* Can_GetCtrlr(const Can_ConfigType* ConfigPtr,
    uint8 CtrlrId)
{
    uint8 Luc_Idx;
    Can_ControllerType *CtrlrPtr;
    CtrlrPtr = NULL_PTR;
    for (Luc_Idx = 0; Luc_Idx < ConfigPtr->u8NumCanCtrlr; Luc_Idx++)
    {
        if (ConfigPtr->ptrCanCtrlrs[Luc_Idx].u8Id == CtrlrId)
        {
            CtrlrPtr = &ConfigPtr->ptrCanCtrlrs[Luc_Idx];
            break;
        }
        else
        {
            /* next */
        }
    }
    return CtrlrPtr;
}

Can_BaudrateConfigType* Can_GetBaudrateCfg(Can_ControllerType *CtrlrPtr, uint8 BaudRateConfigID)
{
    uint8 Luc_Idx;
    Can_BaudrateConfigType *Lpt_BaudratePtr;
    Lpt_BaudratePtr = NULL_PTR;
    for (Luc_Idx = 0; Luc_Idx < CtrlrPtr->u8BaudrateCfgSize; Luc_Idx++)
    {
        if (CtrlrPtr->stBaudrateCfgs[Luc_Idx].usBaudrateId == BaudRateConfigID)
        {
            Lpt_BaudratePtr = &CtrlrPtr->stBaudrateCfgs[Luc_Idx];
            break;
        }
        else
        {
            /* next */
        }
    }
    return Lpt_BaudratePtr;
}

Std_ReturnType Can_CheckValidSetCtrlrModeTrans(Can_ControllerStateType CurState, Can_ControllerStateType NextState)
{
    /* [SWS_Can_00409] */
    static uint8 Lar_ValidTransition[] = {
        GetCurrentStateMask(CAN_CS_STARTED) | GetTargetStateMask(CAN_CS_STARTED),
        GetCurrentStateMask(CAN_CS_STARTED) | GetTargetStateMask(CAN_CS_STOPPED),
        GetCurrentStateMask(CAN_CS_STOPPED) | GetTargetStateMask(CAN_CS_STOPPED),
        GetCurrentStateMask(CAN_CS_STOPPED) | GetTargetStateMask(CAN_CS_STARTED),
        GetCurrentStateMask(CAN_CS_STARTED) | GetTargetStateMask(CAN_CS_SLEEP),
        GetCurrentStateMask(CAN_CS_SLEEP)   | GetTargetStateMask(CAN_CS_SLEEP),
        GetCurrentStateMask(CAN_CS_SLEEP)   | GetTargetStateMask(CAN_CS_STARTED)
    };
    /* valid state: STARTED, STOP, SLEEP -> 3 value, 3 bit
        2 state -> 6 bit */
    uint8 Transition = GetCurrentStateMask(CurState) | GetTargetStateMask(NextState);
    for (uint8 i = 0; i < sizeof(Lar_ValidTransition); i++)
    {
        if (Transition == Lar_ValidTransition[i])
        {
            return E_OK;
        }
    }
    return E_NOT_OK;
}

Std_ReturnType Can_CheckDevError(const Can_ConfigType* ConfigPtr, uint8 Controller, uint8 ServiceID, Can_ControllerType *Lpt_Ctrlr)
{
    Std_ReturnType Luc_StdResult;

    Luc_StdResult = E_OK;
    Lpt_Ctrlr = Can_GetCtrlr(ConfigPtr, Controller);
    /* Check if driver is initialized - Driver not in state CAN_READY */
    if (CAN_UNINIT == g_enCanDriverState)
    {
        #if(CAN_DEV_ERROR_DETECT_API == STD_ON)
        /* [SWS_Can_00492, SWS_Can_00198, SWS_Can_00209, SWS_Can_00362, SWS_Can_91005, SWS_Can_91016, SWS_Can_00512, SWS_Can_00517] */
        (void)Det_ReportError(CAN_MODULE_ID, CAN_INSTANCE_ID, ServiceID, CAN_E_UNINIT);
        #endif
        Luc_StdResult = E_NOT_OK;
    }
    /* Check if requested Controller value is valid */
    else if (NULL_PTR == Lpt_Ctrlr)
    {
        /* [SWS_Can_00494, SWS_Can_00199, SWS_Can_00210, SWS_Can_00363, SWS_Can_91006, SWS_Can_91017, SWS_Can_00513, SWS_Can_00518] */
        #if(CAN_DEV_ERROR_DETECT_API == STD_ON)
        (void)Det_ReportError(CAN_MODULE_ID, CAN_INSTANCE_ID, ServiceID, CAN_E_PARAM_CONTROLLER);
        #endif
        Luc_StdResult = E_NOT_OK;
    }
    else
    {
        /* empty */
    }
    return Luc_StdResult;
}




