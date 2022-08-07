/*******************************************************************************
* File:         Can_Ram.c
* Revision:     1.0.0
* Author:       Dung van Nguyen
* Date:         05.23.2021
* Description:  declaration for global variable.
*******************************************************************************/

#include "Can.h"
#include "Can_IOCommon.h"

P2CONST(Can_ConfigType, AUTOMATIC, CAN_APPL_DATA) Gst_CanConfig;

CONST(CanCtrlrHwRegType, CAN_APPL_CONST) CanCtrlr[2] = {
  {
    .CtrlSts = CAN1_CtrlSts,
    .TxMbx = {CAN1_TxMbx0, CAN1_TxMbx1, CAN1_TxMbx2},
    .RxMbx = {CAN1_RxMbx0, CAN1_RxMbx1},
    .Filter = CAN_ReceiveRule
  },
  {
    .CtrlSts = CAN2_CtrlSts,
    .TxMbx = {CAN2_TxMbx0, CAN2_TxMbx1, CAN2_TxMbx2},
    .RxMbx = {CAN2_RxMbx0, CAN2_RxMbx1},
    .Filter = CAN_ReceiveRule
  }
};