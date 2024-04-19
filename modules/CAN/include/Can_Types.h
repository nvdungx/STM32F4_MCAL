/*******************************************************************************
 * COPYRIGHT
 * -----------------------------------------------------------------------------
 * Copyright (c) 2022 by <<>>. All rights reserved.
 * -----------------------------------------------------------------------------
 * FILE DESCRIPTION
 *  File:         Can_Types.h
 *  Component:    Header
 *  Module:       CAN
 *  Generator:    N/A
 *  Description:  CAN Driver types
 * -----------------------------------------------------------------------------
 * REVISION HISTORY
 * -----------------------------------------------------------------------------
 * Version   Date        Author  Description
 * -----------------------------------------------------------------------------
 * 01.00.00  13/08/2022  Dungnv  Initial version
 *
 *******************************************************************************/

#ifndef CAN_TYPES_H
#define CAN_TYPES_H

#include "EcuM.h"
#include "Can_GeneralTypes.h"

typedef enum Can_DrvStsType_ETag
{
    CAN_UNINIT,
    CAN_READY
} Can_DrvStsType;

typedef enum CanHandleType_ETag
{
    CAN_HANDLE_BASIC,
    CAN_HANDLE_FULL
} CanHandleType;

typedef enum CanIdType_ETag
{
    CAN_ID_STANDARD,
    CAN_ID_EXTENDED,
    CAN_ID_MIXED
} CanIdType;

typedef enum CanObjectType_ETag
{
    CAN_OBJ_RECEIVE,
    CAN_OBJ_TRANSMIT
} CanObjectType;

typedef enum Can_ModeOprType_ETag
{
    CAN_MODE_OPR_INTERRUPT,
    CAN_MODE_OPR_POLLING
} Can_ModeOprType;
typedef enum Can_TrxType_ETag
{
    CAN_TRANSCEIVE_INTERRUPT,
    CAN_TRANSCEIVE_POLLING,
    CAN_TRANSCEIVE_MIXED
} Can_TrxType;

/* Type of CanIcomSignalOperation */
typedef enum Can_IcomSignalOperationType_ETag
{
    CAN_ICOM_SIG_OP_AND = 0u,
    CAN_ICOM_SIG_OP_EQUAL,
    CAN_ICOM_SIG_OP_GREATER,
    CAN_ICOM_SIG_OP_SMALLER,
    CAN_ICOM_SIG_OP_XOR
} Can_IcomSignalOperationType;

typedef enum Can_IcomLevelType_ETag
{
    CAN_ICOM_LEVEL_ONE,
    CAN_ICOM_LEVEL_TWO
} Can_IcomLevelType;

typedef enum CanIcomVariantType_ETag
{
    CAN_ICOM_VARIANT_NONE,
    CAN_ICOM_VARIANT_HW,
    CAN_ICOM_VARIANT_SW
} Can_IcomVariantType;

typedef float Can_MainFncRWPeriodType;

/* [ref]: ECUC_Can_00473 */
typedef struct Can_FdBaudrateConfigType_STag
{
    /* [ref]: ECUC_Can_00481 */
    uint16 usFdBaudrate;
    uint16 usFdBaudrateBRP;
    /* [ref]: ECUC_Can_00476 */
    uint8 ucFdBaudratePropSeg;
    /* [ref]: ECUC_Can_00477 */
    uint8 ucFdBaudrateSeg1;
    /* [ref]: ECUC_Can_00478 */
    uint8 ucFdBaudrateSeg2;
    /* [ref]: ECUC_Can_00479 */
    uint8 ucFdFdBaudrateSJW;
    /* [ref]: ECUC_Can_00494 */
    uint8 ucFdBaudrateSspOffset;
    /* [ref]: ECUC_Can_00475 */
    boolean blFdBaudrateTxBRS;
} Can_FdBaudrateConfigType;

/* [ref]: ECUC_Can_00387 */
typedef struct Can_BaudrateConfigType_STag
{
    const Can_FdBaudrateConfigType *stFdBaudrateConf;
    /* [ref]: ECUC_Can_00471 */
    uint16 usBaudrateId;
    /* [ref]: ECUC_Can_00005 */
    uint16 usBaudRate;
    uint16 usBaudrateBRP;
    /* [ref]: ECUC_Can_00073 */
    uint8 ucBaudratePropSeg;
    /* [ref]: ECUC_Can_00074 */
    uint8 ucBaudrateSeg1;
    /* [ref]: ECUC_Can_00075 */
    uint8 ucBaudrateSeg2;
    /* [ref]: ECUC_Can_00383 */
    uint8 ucBaudrateSJW;
} Can_BaudrateConfigType;

typedef uint32 Can_IcomSignalMaskType;
typedef uint32 Can_IcomSignalValueType;

typedef struct Can_IcomRxMessageSignalConfigType_STag
{
    Can_IcomSignalMaskType ulSignalMask;
    Can_IcomSignalValueType ulSignalValue;
    Can_IcomSignalOperationType enSigOpr;
} Can_IcomRxMessageSignalConfigType;

typedef uint32 Can_IcomMessageIdType;
typedef uint32 Can_IcomMessageIdMaskType;
typedef uint16 Can_IcomCounterValueType;
typedef float Can_IcomMissingMessageTimerValueType;
typedef boolean Can_IcomPayloadLengthErrorType;
typedef struct Can_IcomRxMessageType_STag
{
    Can_IcomRxMessageSignalConfigType *stRxMsgSignals;
    Can_IcomMessageIdType ulMsgId;
    Can_IcomMessageIdMaskType ulMsgIdMask;
    Can_IcomCounterValueType usCounter;
    Can_IcomMissingMessageTimerValueType flTmValue;
    Can_IcomPayloadLengthErrorType blPayloadLenErr;
} Can_IcomRxMessageType;

typedef struct Can_IcomWakeupCauseType_STag
{
    Can_IcomRxMessageType *stIcomRxMessage;
} Can_IcomWakeupCauseType;

/* [ref]: ECUC_Can_00440, ECUC_Can_00459 */
typedef struct Can_IcomControllerConfigType_STag
{
    Can_IcomWakeupCauseType *stCanIcomWakeupCauses;
    /* [ref]: ECUC_Can_00441 */
    uint8 ucCanIcomCfgId;
    /* [ref]: ECUC_Can_00442 */
    boolean blCanIcomWakeOnBusoff;
} Can_IcomControllerConfigType;

/* [ref]: ECUC_Can_00468 */
typedef struct Can_HwFilterConfigType_STag
{
    /* [ref]: ECUC_Can_00469 */
    uint32 ulHwFilterCode;
    /* [ref]: ECUC_Can_00470 */
    uint32 ulHwFilterMask;
    boolean blMasked;
} Can_HwFilterConfigType;

typedef struct Can_ControllerConfigType_STag Can_ControllerConfigType;
/* [ref]: ECUC_Can_00324 */
typedef struct Can_HwObjectConfigType_STag
{
    /* [ref]: ECUC_Can_00438 */
    Can_MainFncRWPeriodType *ptrRWPeriodRef;
    Can_HwFilterConfigType *stCanHwFilters;
    /* [ref]: ECUC_Can_00322 */
    Can_ControllerConfigType *ptCtrlrRef;
    /* [ref]: ECUC_Can_00323 */
    CanHandleType enObjHandleType;
    /* [ref]: ECUC_Can_00327 */
    CanObjectType enObjType;
    /* [ref]: ECUC_Can_00065 */
    CanIdType enObjIdType;
    /* [ref]: ECUC_Can_00326 */
    uint16 usObjId;
    /* [ref]: ECUC_Can_00467 */
    uint16 usObjCount;
    /* [ref]: ECUC_Can_00485 */
    uint8 ucObjFdPaddingVal;
    uint8 ucCanHwFilterSize;
    uint8 ucHwRxFIFOId;
    /* [ref]: ECUC_Can_00490 */
    boolean blObjPolling;
    /* [ref]: ECUC_Can_00327 */
    boolean blObjTriggerTx;
} Can_HwObjectConfigType;

/* [ref]: ECUC_Can_00444 */
typedef struct Can_IcomGeneralConfigType_STag
{
    Can_IcomLevelType enCanIcomLevel;
    Can_IcomVariantType enCanIcomVariant;
} Can_IcomGeneralConfigType;

/* Data structure contain pre-compile data:
  ref to EcuM wakeup API
  ref to ICOM configuration data
  tx/rx/busoff processing option
  interrupt enable/disable status
  controller sw status
  controller tx/rx error status
  */
/* [ref]: ECUC_Can_00354 */
typedef struct Can_ControllerConfigType_STag
{
    /* [ref]: ECUC_Can_00382 */
    uint32 ulHwBaseAddr;
    Can_ControllerStateType *ptCanCtrlSts;
    Can_BaudrateConfigType *stBaudrateCfgs;
    /* [ref]: ECUC_Can_00435 */
    Can_BaudrateConfigType *ptDefaultBaudrateCfg;
    /* [ref]: ECUC_Can_00359 */
    EcuM_WakeupSourceType enCanWakeupRef;
    Can_ModeOprType enCanWakeupModeOp;
    /*[ref]: ECUC_Can_00314 */
    Can_ModeOprType enCanBusoffModeOp;
    /*[ref]: ECUC_Can_00317 */
    Can_TrxType enCanRxModeOp;
    /*[ref]: ECUC_Can_00318 */
    Can_TrxType enCanTxModeOp;
    /* [ref]: ECUC_Can_00316, this should be can hardware controller id */
    uint8 ucId;
    /* [ref]: ECUC_Can_00492 */
    uint8 ucCanCtrlEcucPartRef;
    uint8 ucBaudrateCfgSize;
    uint8 ucFltBankStart;
    uint8 ucFltBankEnd;
    /* [ref]: ECUC_Can_00315 */
    boolean blActive;
} Can_ControllerConfigType;

/* Data structure contain pre-compile data:
  general configuration data of CAN module
  */
/* [ref]: ECUC_Can_00328 */
typedef struct Can_GeneralConfigType_STag
{
    Can_IcomGeneralConfigType *stCanIcomGeneral;
    Can_MainFncRWPeriodType *flRWPeriodArr;
    uint8 ucCanIndex;
    boolean ucCanMultiplexedTx;
    boolean ucCanIcomEnable;
} Can_GeneralConfigType;

#endif /*End of Can_Types.h*/
