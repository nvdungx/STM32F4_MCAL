/*******************************************************************************
 * COPYRIGHT
 * -----------------------------------------------------------------------------
 * Copyright (c) 2022 by <<>>. All rights reserved.
 * -----------------------------------------------------------------------------
 * FILE DESCRIPTION
 *  File:         Can_Ram.c
 *  Component:    Source
 *  Module:       CAN
 *  Generator:    N/A
 *  Description:  declaration for global variable.
 * -----------------------------------------------------------------------------
 * REVISION HISTORY
 * -----------------------------------------------------------------------------
 * Version   Date        Author  Description
 * -----------------------------------------------------------------------------
 * 01.00.00  13/08/2022  Dungnv  Initial version
 *
*******************************************************************************/

#include "Can.h"
#include "Can_IOCommon.h"

/* Global CAN Driver configuration data structure - should be provided(pointed)
  to generated configured data array */
P2CONST(Can_ConfigType, AUTOMATIC, CAN_APPL_DATA) Glb_CanCfgPtr;

/* Constant data structure provide access to corresponding hardware registers
  of CAN Hardware controllers */
CONST(CanCtrlrHwRegType, CAN_APPL_CONST) HwCanCtrlr[CAN_HW_NUM_CTRLR_MAX] = {
    {
        .CtrlNSts = CAN1_CtrlSts,
        .TxMbx = {CAN1_TxMbx0, CAN1_TxMbx1, CAN1_TxMbx2},
        .RxMbx = {CAN1_RxMbx0, CAN1_RxMbx1},
        .Filter = CAN_ReceiveRule
    },
    {
        .CtrlNSts = CAN2_CtrlSts,
        .TxMbx = {CAN2_TxMbx0, CAN2_TxMbx1, CAN2_TxMbx2},
        .RxMbx = {CAN2_RxMbx0, CAN2_RxMbx1},
        .Filter = CAN_ReceiveRule
    }
};