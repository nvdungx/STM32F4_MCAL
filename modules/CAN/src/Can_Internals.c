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

#define FLT_ATTR_EXTENDED_MASKED    0x01
#define FLT_ATTR_EXTENDED_IDENT     0x00
#define FLT_ATTR_STANDARD_MASKED    0x03
#define FLT_ATTR_STANDARD_IDENT     0x02
#define GetExtendedRuleConfig(val)   ((((uint32)val & 0x000007FF) << 21) | (((uint32)val & 0x1FFFF800) >> 11) << 3 | (uint32)1 << 2)
#define GetStandardRuleConfig(val)   (((uint16)val & 0x07FF) << 5 | (uint16)1 << 3)

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
FUNC(boolean, CAN_CODE_SLOW) Can_HwCtrlInit(P2CONST(Can_ConfigType, AUTOMATIC, CAN_APPL_DATA) ConfigPtr,
    VAR(uint8, AUTOMATIC) CtrlrIdx)
{
    boolean Lbl_InitSts;
    uint8 FltBankType;
    uint8 Luc_ObjIdx;
    uint8 Luc_FltIdx;
    Can_ControllerConfigType *Lpt_Ctrlr;
    Lbl_InitSts = TRUE;
    Lpt_Ctrlr = &ConfigPtr->stCanCtrlrs[CtrlrIdx];

    /* [SWS_Can_00419, SWS_Can_00033, SWS_Can_00053] */
    /* Clear all CAN hw unit interrupt setting by default, interrupt shall be configured by SetControllerMode API */
    HwCanCtrlr[CtrlrIdx].CtrlNSts->ulIEReg.val = REGISTER_RESET_VALUE;

    HwCanCtrlr[CtrlrIdx].CtrlNSts->ulMCReg.val = REGISTER_RESET_VALUE;
    /* Request CAN hw controller into sleep mode by default */
    HwCanCtrlr[CtrlrIdx].CtrlNSts->ulMCReg.SLEEP = REGISTER_BIT_SET;
    #if(CAN_SUPPORT_TTCAN == STD_ON)
    /* Enable time trigger communication mode */
    HwCanCtrlr[CtrlrIdx].CtrlNSts->ulMCReg.TTCM = REGISTER_BIT_SET;
    /* No automatic retransmission */
    HwCanCtrlr[CtrlrIdx].CtrlNSts->ulMCReg.NART = REGISTER_BIT_SET;
    #endif
    #if(CAN_MULTIPLEXED_TRANSMISSION == STD_ON)
    /* Priority driven by the request order (chronologically) when several mailboxes are pending at the same time */
    HwCanCtrlr[CtrlrIdx].CtrlNSts->ulMCReg.TXFP = REGISTER_BIT_SET;
    #endif

    /* setup CAN controller default baudrate */
    HwCanCtrlr[CtrlrIdx].CtrlNSts->ulBTReg.val = REGISTER_RESET_VALUE;
    HwCanCtrlr[CtrlrIdx].CtrlNSts->ulBTReg.SJW = Lpt_Ctrlr->ptDefaultBaudrateCfg->ucBaudrateSJW;
    HwCanCtrlr[CtrlrIdx].CtrlNSts->ulBTReg.TS2 = Lpt_Ctrlr->ptDefaultBaudrateCfg->ucBaudrateSeg2;
    HwCanCtrlr[CtrlrIdx].CtrlNSts->ulBTReg.TS1 = Lpt_Ctrlr->ptDefaultBaudrateCfg->ucBaudrateSeg1;
    HwCanCtrlr[CtrlrIdx].CtrlNSts->ulBTReg.BRP = Lpt_Ctrlr->ptDefaultBaudrateCfg->usBaudrateBRP;

    /* configure hardware object and hardware filter of CAN controller */
    /* enter initialization mode to config filter */
    HwCanCtrlr[CtrlrIdx].Filter->ulFMReg.FINIT = REGISTER_BIT_SET;

    /* define the start bank for the CAN2 interface (Slave) in the range 0 to 27 */
    if (CtrlrIdx == CAN_HW_CTRLR1)
    {
        HwCanCtrlr[CtrlrIdx].Filter->ulFMReg.CAN2SB = Lpt_Ctrlr->ucFltBankStart;
    }
    else
    {
        /* empty */
    }

    for (Luc_ObjIdx = 0; Luc_ObjIdx < CAN_HW_OBJS_SIZE; Luc_ObjIdx++)
    {
        if (ConfigPtr->stCanHwObjs[Luc_ObjIdx].enObjType != CAN_OBJ_RECEIVE)
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
        1 bank, 4 bit track per FIFO, ident/mask type, scale(3bit attribute)
         */
        for (Luc_FltIdx = 0; Luc_FltIdx < ConfigPtr->stCanHwObjs[Luc_ObjIdx].ucCanHwFilterSize; Luc_FltIdx++)
        {
            FltBankType = ((uint8)(ConfigPtr->stCanHwObjs[Luc_ObjIdx].enObjIdType == CAN_ID_STANDARD) << 2) |
                                ((uint8)ConfigPtr->stCanHwObjs[Luc_ObjIdx].stCanHwFilters[Luc_FltIdx].blMasked << 1) |
                                ConfigPtr->stCanHwObjs[Luc_ObjIdx].ucHwRxFIFOId;
            Can_ConfigFilterRule(CtrlrIdx, Lpt_Ctrlr->ucFltBankStart, Lpt_Ctrlr->ucFltBankEnd, FltBankType,
                                    &ConfigPtr->stCanHwObjs[Luc_ObjIdx].stCanHwFilters[Luc_FltIdx]);
        }
    }

    /* exit initialization mode to config filter */
    HwCanCtrlr[CtrlrIdx].Filter->ulFMReg.FINIT = REGISTER_BIT_CLEAR;

    if (E_OK != Can_WaitRegValUntilTimeout((uint32 *)&HwCanCtrlr[CtrlrIdx].CtrlNSts->ulMSReg, CAN_MSR_SLEEP_ACK))
    {
        Lbl_InitSts = FALSE;
        *(ConfigPtr->stCanCtrlrs[CtrlrIdx].ptCanCtrlSts) = CAN_CS_UNINIT;
    }
    else
    {
        /* Change software state of CAN controllers to STOPPED */
        *(ConfigPtr->stCanCtrlrs[CtrlrIdx].ptCanCtrlSts) = CAN_CS_STOPPED;
    }

    return Lbl_InitSts;
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
FUNC(boolean, CAN_CODE_SLOW) Can_HwDeInit(P2CONST(Can_ConfigType, AUTOMATIC, CAN_APPL_DATA) ConfigPtr,
    VAR(uint8, AUTOMATIC) CtrlrIdx)
{
    boolean Lbl_DeInitSts;
    uint8 Luc_Count;
    /* [SWS_Can_00053], [SWS_Can_00407] */
    HwCanCtrlr[CtrlrIdx].CtrlNSts->ulIEReg.val = REGISTER_RESET_VALUE;
    HwCanCtrlr[CtrlrIdx].CtrlNSts->ulMCReg.val = REGISTER_RESET_VALUE;
    /* Request CAN hw controller into sleep mode by default */
    HwCanCtrlr[CtrlrIdx].CtrlNSts->ulMCReg.SLEEP = REGISTER_BIT_SET;
    /* clear baudrate */
    HwCanCtrlr[CtrlrIdx].CtrlNSts->ulBTReg.val = REGISTER_RESET_VALUE;
    HwCanCtrlr[CtrlrIdx].Filter->ulFMReg.val = REGISTER_RESET_VALUE;
    HwCanCtrlr[CtrlrIdx].Filter->ulFMReg.FINIT = REGISTER_BIT_SET;
    for (Luc_Count = 0; Luc_Count < CAN_HW_FILTER_BANK_MAX; Luc_Count++)
    {
        HwCanCtrlr[CtrlrIdx].Filter->ulFM1Reg = REGISTER_RESET_VALUE;
        HwCanCtrlr[CtrlrIdx].Filter->ulFS1Reg = REGISTER_RESET_VALUE;
        HwCanCtrlr[CtrlrIdx].Filter->ulFFA1Reg = REGISTER_RESET_VALUE;
        HwCanCtrlr[CtrlrIdx].Filter->ulFReg[Luc_Count][FILTER_BANK_ID] = REGISTER_RESET_VALUE;
        HwCanCtrlr[CtrlrIdx].Filter->ulFReg[Luc_Count][FILTER_BANK_MASK] = REGISTER_RESET_VALUE;
        HwCanCtrlr[CtrlrIdx].Filter->ulFA1Reg = REGISTER_RESET_VALUE;
    }
    HwCanCtrlr[CtrlrIdx].Filter->ulFMReg.FINIT = REGISTER_BIT_CLEAR;


    if (E_OK != Can_WaitRegValUntilTimeout((uint32 *)&HwCanCtrlr[CtrlrIdx].CtrlNSts->ulMSReg, CAN_MSR_SLEEP_ACK))
    {
        Lbl_DeInitSts = FALSE;
    }
    else
    {
        Lbl_DeInitSts = TRUE;
        *(ConfigPtr->stCanCtrlrs[CtrlrIdx].ptCanCtrlSts) = CAN_CS_UNINIT;
    }

    return Lbl_DeInitSts;
}

/*
 *  Service Name...... : Can_ConfigFilterRule
 *  Service ID      .. : None
 *  Sync/Async........ : Synchronous
 *  Reentrancy........ : Non Reentrant
 *  Parameters (IN)... : CtrlrIdx, FltBankStart, FltBankEnd, FltBankType, HwFilterRule
 *  Parameters (INOUT) : None
 *  Parameters (OUT).. : None
 *  Return Value...... : boolean(TRUE/FALSE)
 *  Register usage     :
 *  Global variable    :
 *  Description....... : fill in filter rule to available CAN hardware filter bank.
 */
FUNC(boolean, CAN_CODE_SLOW) Can_ConfigFilterRule(uint8 CtrlrIdx, uint8 FltBankStart, uint8 FltBankEnd,
    uint8 FltBankType, Can_HwFilterConfigType *HwFilterRule)
{
    uint8 Luc_Count;
    boolean Lbl_Success;
    /* if init(i.e != 0 then bank has attributes, check and find available) */
    /* 1 bit = 16 byte data */
    static uint8 Lar_FltBankCfgSts[CAN_HW_FILTER_BANK_MAX] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
    /* filter bank only have 1 attributes */
    static uint8 Lar_FltBankAttr[CAN_HW_FILTER_BANK_MAX] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

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
            CLEAR_BIT32(HwCanCtrlr[CtrlrIdx].Filter->ulFS1Reg, Luc_Count);
            HwCanCtrlr[CtrlrIdx].Filter->ulFS1Reg |= ((FltBankType >> 2) & 0x01) << Luc_Count;

            /* filter FIFO assignment */
            CLEAR_BIT32(HwCanCtrlr[CtrlrIdx].Filter->ulFFA1Reg, Luc_Count);
            HwCanCtrlr[CtrlrIdx].Filter->ulFFA1Reg |= (FltBankType & 0x01) << Luc_Count;

            /* set filter mode: CLEAR Identifier Mask or SET Identifier List */
            CLEAR_BIT32(HwCanCtrlr[CtrlrIdx].Filter->ulFM1Reg, Luc_Count);
            HwCanCtrlr[CtrlrIdx].Filter->ulFM1Reg |= ((FltBankType >> 1) & 0x01) << Luc_Count;

            switch ((FltBankType >> 1) & 0x03)
            {
            case FLT_ATTR_EXTENDED_MASKED:
                HwCanCtrlr[CtrlrIdx].Filter->ulFReg[Luc_Count][FILTER_BANK_ID] = GetExtendedRuleConfig(HwFilterRule->ulHwFilterCode);
                HwCanCtrlr[CtrlrIdx].Filter->ulFReg[Luc_Count][FILTER_BANK_MASK] = GetExtendedRuleConfig(HwFilterRule->ulHwFilterMask);
                Lar_FltBankCfgSts[Luc_Count] |= 0b00001111;
                break;
            case FLT_ATTR_EXTENDED_IDENT:
                HwCanCtrlr[CtrlrIdx].Filter->ulFReg[Luc_Count][FILTER_BANK_ID] = GetExtendedRuleConfig(HwFilterRule->ulHwFilterCode);
                Lar_FltBankCfgSts[Luc_Count] |= 0b00000011;
                break;
            case FLT_ATTR_STANDARD_MASKED:
                HwCanCtrlr[CtrlrIdx].Filter->ulFReg[Luc_Count][FILTER_BANK_ID] = (uint32)GetStandardRuleConfig(HwFilterRule->ulHwFilterCode);
                HwCanCtrlr[CtrlrIdx].Filter->ulFReg[Luc_Count][FILTER_BANK_ID] |= (uint32)GetStandardRuleConfig(HwFilterRule->ulHwFilterMask) << 16;
                Lar_FltBankCfgSts[Luc_Count] |= 0b00000011;
                break;
            case FLT_ATTR_STANDARD_IDENT:
                HwCanCtrlr[CtrlrIdx].Filter->ulFReg[Luc_Count][FILTER_BANK_ID] = (uint32)GetStandardRuleConfig(HwFilterRule->ulHwFilterCode);
                Lar_FltBankCfgSts[Luc_Count] |= 0b00000001;
                break;
            default:
                break;
            }

            /* activate filter */
            SET_BIT32(HwCanCtrlr[CtrlrIdx].Filter->ulFA1Reg, Luc_Count);

            /* store attribute for this bank */
            Lar_FltBankAttr[Luc_Count] = FltBankType;
            Lbl_Success = TRUE;
        }
        else
        {
            // check if current rule FltBankType match
            if (Lar_FltBankAttr[Luc_Count] == FltBankType)
            {
                switch ((FltBankType >> 1) & 0x03)
                {
                case FLT_ATTR_EXTENDED_MASKED:
                    /* should not fall into this since this should get a bank fill completely */
                    break;
                case FLT_ATTR_EXTENDED_IDENT:
                    /* 1st reg bank ident should be filled with extended ident*/
                    HwCanCtrlr[CtrlrIdx].Filter->ulFReg[Luc_Count][FILTER_BANK_MASK] = GetExtendedRuleConfig(HwFilterRule->ulHwFilterCode);
                    Lar_FltBankCfgSts[Luc_Count] |= 0b00001100;
                    break;
                case FLT_ATTR_STANDARD_MASKED:
                    /* 1st reg bank ident should be filled with standard ident and mask */
                    HwCanCtrlr[CtrlrIdx].Filter->ulFReg[Luc_Count][FILTER_BANK_MASK] = (uint32)GetStandardRuleConfig(HwFilterRule->ulHwFilterCode);
                    HwCanCtrlr[CtrlrIdx].Filter->ulFReg[Luc_Count][FILTER_BANK_MASK] |= (uint32)GetStandardRuleConfig(HwFilterRule->ulHwFilterMask) << 16;
                    Lar_FltBankCfgSts[Luc_Count] |= 0b00001100;
                    break;
                case FLT_ATTR_STANDARD_IDENT:
                    /* 1st 2 byte of Ident reg should be fill with standard ident  */
                    if ((Lar_FltBankCfgSts[Luc_Count] & 0b00000010) == 0)
                    {
                        HwCanCtrlr[CtrlrIdx].Filter->ulFReg[Luc_Count][FILTER_BANK_ID] |= (uint32)GetStandardRuleConfig(HwFilterRule->ulHwFilterCode) << 16;
                        Lar_FltBankCfgSts[Luc_Count] |= 0b00000010;
                    }
                    else if ((Lar_FltBankCfgSts[Luc_Count] & 0b00000100) == 0)
                    {
                        HwCanCtrlr[CtrlrIdx].Filter->ulFReg[Luc_Count][FILTER_BANK_MASK] = (uint32)GetStandardRuleConfig(HwFilterRule->ulHwFilterCode);
                        Lar_FltBankCfgSts[Luc_Count] |= 0b00000100;
                    }
                    else if ((Lar_FltBankCfgSts[Luc_Count] & 0b00001000) == 0)
                    {
                        HwCanCtrlr[CtrlrIdx].Filter->ulFReg[Luc_Count][FILTER_BANK_MASK] |= (uint32)GetStandardRuleConfig(HwFilterRule->ulHwFilterCode) << 16;
                        Lar_FltBankCfgSts[Luc_Count] |= 0b00001000;
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
FUNC(Std_ReturnType, CAN_CODE_SLOW) Can_WaitRegValUntilTimeout(uint32 * RegAddr, uint32 ExpectedValue)
{
    TickType Lul_PreOsTick;
    TickType Lul_CurOsTick;
    Std_ReturnType Luc_ReturnVal;
    Luc_ReturnVal = E_NOT_OK;
    GetCounterValue(CAN_OS_COUNTER, &Lul_PreOsTick);
    do
    {
        GetCounterValue(CAN_OS_COUNTER, &Lul_CurOsTick);
        if (((*(volatile uint32 *)RegAddr) & ExpectedValue) == ExpectedValue)
        {
            Luc_ReturnVal = E_OK;
            break;
        }
    } while ((Lul_CurOsTick - Lul_PreOsTick) < CAN_TIMEOUT_DURATION);
    return Luc_ReturnVal;
}













