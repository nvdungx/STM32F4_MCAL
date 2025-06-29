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

typedef enum Can_HandleType_ETag
{
    CAN_HANDLE_BASIC,
    CAN_HANDLE_FULL
} Can_HandleType;

typedef enum Can_IdType_ETag
{
    CAN_ID_STANDARD,
    CAN_ID_EXTENDED,
    CAN_ID_MIXED
} Can_IdType;

typedef enum Can_ObjectType_ETag
{
    CAN_OBJ_RECEIVE,
    CAN_OBJ_TRANSMIT
} Can_ObjectType;

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

typedef enum Can_TTCtrlrOprModeType_ETag
{
    CAN_TT_EVENT_SYNC_TIME_TRIGGERED, // Event-synchronized time triggered operation
    CAN_TT_EVENT_TRIGGERED,           // Event triggered operation (normal can operation without time schedule)
    CAN_TT_TIME_TRIGGERED             // Time triggered operation
} Can_TTCtrlrOprModeType;

typedef enum Can_TTIRQProcessingType_ETag
{
    CAN_TT_IRQ_PROCESSING_INTERRUPT,
    CAN_TT_IRQ_PROCESSING_POLLING
} Can_TTIRQProcessingType;

typedef enum Can_TTTriggerType_ETag
{
    CAN_TT_RX_TRIGGER,
    CAN_TT_TX_REF_TRIGGER,
    CAN_TT_TX_REF_TRIGGER_GAP,
    CAN_TT_TX_TRIGGER_EXCLUSIVE,
    CAN_TT_TX_TRIGGER_MERGED
} Can_TTTriggerType;

typedef enum Can_ObjPayloadLenType_ETag
{
    CAN_OBJECT_PL_12, // Payload length of 12 Bytes
    CAN_OBJECT_PL_16, // Payload length of 16 Bytes
    CAN_OBJECT_PL_20, // Payload length of 20 Bytes
    CAN_OBJECT_PL_24, // Payload length of 24 Bytes
    CAN_OBJECT_PL_32, // Payload length of 32 Bytes
    CAN_OBJECT_PL_48, // Payload length of 48 Bytes
    CAN_OBJECT_PL_64, // Payload length of 64 Bytes
    CAN_OBJECT_PL_8   // Payload length of 8 Bytes
} Can_ObjPayloadLenType;

typedef float Can_MainFncPeriodType;

typedef struct CanXL_BaudrateConfigType_STag
{
    /* [ECUC_Can_00513] CanXLBaudRate*/
    uint16 u16XlBaudrate;
    uint16 u16XlBaudrateBRP;
    /* [ECUC_Can_00523] CanXLErrorSignaling */
    boolean blErrorSignaling;
    /* [ECUC_Can_00517] CanXLPropSeg */
    uint8 u8XlBaudratePropSeg;
    /* [ECUC_Can_00514] CanXLPwmL */
    uint8 u8XlPwmL;
    /* [ECUC_Can_00516] CanXLPwmO */
    uint8 u8XlPwmO;
    /* [ECUC_Can_00515] CanXLPwmS */
    uint8 u8XlPwmS;
    /* [ECUC_Can_00518] CanXLSeg1 */
    uint8 u8XlSeg1;
    /* [ECUC_Can_00519] CanXLSeg2 */
    uint8 u8XlSeg2;
    /* [ECUC_Can_00521] CanXLSspOffset */
    uint8 u8XlSspOffset;
    /* [ECUC_Can_00520] CanXLSyncJumpWidth */
    uint8 u8XlSyncJumpWidth;
    /* [ECUC_Can_00522] CanXLTrcvPwmMode */
    uint8 u8XlTrcvPwmMode;
} CanXL_BaudrateConfigType;

/* [ECUC_Can_00473] */
typedef struct Can_FdBaudrateConfigType_STag
{
    /* [ECUC_Can_00481] CanControllerFdBaudRate */
    uint16 u16FdBaudrate;
    uint16 u16FdBaudrateBRP;
    /* [ECUC_Can_00476] CanControllerPropSeg */
    uint8 u8FdBaudratePropSeg;
    /* [ECUC_Can_00477] CanControllerSeg1 */
    uint8 u8FdBaudrateSeg1;
    /* [ECUC_Can_00478] CanControllerSeg2 */
    uint8 u8FdBaudrateSeg2;
    /* [ECUC_Can_00479] CanControllerSyncJumpWidth */
    uint8 u8FdFdBaudrateSJW;
    /* [ECUC_Can_00494] CanControllerSspOffset */
    uint8 u8FdBaudrateSspOffset;
    /* [ECUC_Can_00475] CanControllerTxBitRateSwitch */
    boolean blFdBaudrateTxBRS;
} Can_FdBaudrateConfigType;

/* [ECUC_Can_00387] */
typedef struct Can_BaudrateConfigType_STag
{
    /* [ECUC_Can_00473] CanControllerFdBaudrateConfig - not supported */
    // const Can_FdBaudrateConfigType *stFdBaudrateConf;
    /* [ECUC_Can_00512] CanXLBaudrateConfig - not supported */
    // const CanXL_BaudrateConfigType *stXlBaudrateConf;
    /* [ECUC_Can_00471] CanControllerBaudRateConfigID */
    uint16 u16BaudrateId;
    /* [ECUC_Can_00005] CanControllerBaudRate*/
    uint16 u16Baudrate;
    uint16 u16BaudrateBRP;
    /* [ECUC_Can_00073] CanControllerPropSeg */
    uint8 u8BaudratePropSeg;
    /* [ECUC_Can_00074] CanControllerSeg1 */
    uint8 u8BaudrateSeg1;
    /* [ECUC_Can_00075] CanControllerSeg2 */
    uint8 u8BaudrateSeg2;
    /* [ECUC_Can_00383] CanControllerSyncJumpWidth */
    uint8 u8BaudrateSJW;
} Can_BaudrateConfigType;

/* [ECUC_Can_00468] */
typedef struct Can_HwFilterType_STag
{
    /* [ECUC_Can_00469] CanHwFilterCode */
    uint32 u32HwFilterCode;
    /* [ECUC_Can_00470] CanHwFilterMask */
    uint32 u32HwFilterMask;
    boolean blMasked;
} Can_HwFilterType;

typedef struct Can_PnFrameDataMaskSpecType_STag
{
    /* [ECUC_Can_00536] CanPnFrameDataMask */
    uint8 u8PnFrameDataMask;
    /* [ECUC_Can_00537] CanPnFrameDataMaskIndex */
    uint8 u8PnFrameDataMaskIdx;
} Can_PnFrameDataMaskSpecType;

typedef struct Can_PnNetworkType_STag
{
    /* [ECUC_Can_00532] CanPnFrameCanId */
    uint32 u32PnFrameCanId;
    /* [ECUC_Can_00533] CanPnFrameCanIdMask */
    uint32 u32PnFrameCanIdMask;
    /* [ECUC_Can_00535] CanPnFrameDlc */
    uint8 u8PnFrameDlc;
    /* [ECUC_Can_00534] CanPnFrameDataMaskSpec */
    const Can_PnFrameDataMaskSpecType arrPnFrameDataMaskSpec[8];
    /* [ECUC_Can_00531] CanPnEnabled */
    boolean blPnEnable;
} Can_PnNetworkType;

typedef struct Can_TTControllerType_STag
{
    /* [ECUC_Can_00141] CanTTControllerNTUConfig */
    float32 f32TTCtrlrNTUConfig;
    /* [ECUC_Can_00132] CanTTControllerSyncDeviation */
    float32 f32TTCtrlrSyncDeviation;
    /* [ECUC_Can_00127] CanTTControllerOperationMode */
    Can_TTCtrlrOprModeType enTTCtrlrOprMode;
    /* [ECUC_Can_00142] CanTTIRQProcessing */
    Can_TTIRQProcessingType enTTCtrlrIRQProcessing;
    /* [ECUC_Can_00140] CanTTControllerInterruptEnable */
    uint16 u16TTCtrlrInterruptEnable;
    /* [ECUC_Can_00158] CanTTControllerWatchTriggerGapTimeMark */
    uint16 u16TTCtrlrWatchTriggerGapTimeMark;
    /* [ECUC_Can_00159] CanTTControllerWatchTriggerTimeMark */
    uint16 u16TTCtrlrWatchTriggerTimeMark;
    /* [ECUC_Can_00139] CanTTControllerApplWatchdogLimit */
    uint8 u8TTCtrlrApplWdgLimit;
    /* [ECUC_Can_00138] CanTTControllerCycleCountMax */
    uint8 u8TTCtrlrCycleCntMax;
    /* [ECUC_Can_00136] CanTTControllerExpectedTxTrigger */
    uint8 u8TTCtrlrExpectedTxTrigger;
    /* [ECUC_Can_00128] CanTTControllerInitialRefOffset */
    uint8 u8TTCtrlrInitialRefOffset;
    /* [ECUC_Can_00130] CanTTControllerTimeMasterPriority */
    uint8 u8TTCtrlrTimeMasterPrio;
    /* [ECUC_Can_00137] CanTTControllerTxEnableWindowLength */
    uint8 u8TTCtrlrTxEnableWindowLen;
    /* [ECUC_Can_00135] CanTTControllerExternalClockSynchronisation */
    boolean blTTCtrlrExternalClockSync;
    /* [ECUC_Can_00134] CanTTControllerGlobalTimeFiltering */
    boolean blTTCtrlrGlbTimeFiltering;
    /* [ECUC_Can_00131] CanTTControllerLevel2 */
    boolean blTTCtrlrLevel2;
    /* [ECUC_Can_00129] CanTTControllerTimeMaster */
    boolean blTTCtrlrTimeMaster;
    /* [ECUC_Can_00133] CanTTControllerTURRestore */
    boolean blTTCtrlrTURRestore;
    /* [ECUC_Can_00493] CanTTControllerEcucPartitionRef - not used */
} Can_TTControllerType;

typedef struct Can_XLEthEgressFifoType_STag
{
    /* [ECUC_Can_00503] CanXLEthEgressFifoCanXLPriority */
    uint16 u16XLEthEgressFifoCanXLPrio;
    /* [ECUC_Can_00504] CanXLEthEgressFifoCanXLQueue */
    uint8 u8XLEthEgressFifoCanXLQueue;
    /* [ECUC_Can_00505] CanXLEthEgressFifoIdx */
    uint8 u8XLEthEgressFifoIdx;
} Can_XLEthEgressFifoType;

typedef struct Can_XLEthIngressFifoType_STag
{
    /* [ECUC_Can_00509] CanXLEthIngressFifoCanXLQueue */
    uint8 u8XLEthIngressFifoCanXLQueue;
    /* [ECUC_Can_00508] CanXLEthIngressFifoIdx */
    uint8 u8XLEthIngressFifoIdx;
    /* [ECUC_Can_00510] CanXLEthIngressFifoVcid */
    const uint8 *ptrXLEthIngressFifoVcid;
} Can_XLEthIngressFifoType;

typedef struct Can_XLControllerType_STag
{
    /* [ECUC_Can_00502] CanXLEthEgressFifo */
    const Can_XLEthEgressFifoType *ptrXLEthEgressFifoCfgs;
    /* [ECUC_Can_00507] CanXLEthIngressFifo */
    const Can_XLEthIngressFifoType *ptrXLEthIngressFifoCfgs;
    /* [ECUC_Can_00500] CanXLCtrlEthDefaultPriority */
    uint16 u16XLCtrlEthDefaultPrio;
    /* [ECUC_Can_00501] CanXLEthDefaultQueue */
    uint8 u8XLEthDefaultQueue;
    /* [ECUC_Can_00506] CanXLEthPhysAddress */
    const char cXLEthPhysAddress[17];
    /* [ECUC_Can_00511] CanXLEthEcucPartitionRef - not used */
} Can_XLControllerType;

typedef struct Can_TTHwObjectTriggerType_STag
{
    /* [ECUC_Can_00145] CanTTHardwareObjectTriggerType */
    Can_TTTriggerType enTTHwObjTriggerType;
    /* [ECUC_Can_00146] CanTTHardwareObjectTimeMark */
    uint16 u16TTHwObjTimeMark;
    /* [ECUC_Can_00147] CanTTHardwareObjectBaseCycle */
    uint8 u8TTHwObjBaseCycle;
    /* [ECUC_Can_00148] ] CanTTHardwareObjectCycleRepetition */
    uint8 u8TTHwObjCycleRepetition;
    /* [ECUC_Can_00155] CanTTHardwareObjectTriggerId */
    uint8 u8TTHwObjTriggerId;
} Can_TTHwObjectTriggerType;

typedef struct Can_ControllerType_STag Can_ControllerType;
/* [ECUC_Can_00324] */
typedef struct Can_HwObjectType_STag
{
    /* [ECUC_Can_00438] CanMainFunctionRWPeriodRef */
    Can_MainFncPeriodType *ptrRWPeriodRef;
    /* [ECUC_Can_00322] CanControllerRef */
    Can_ControllerType *ptrCtrlrRef;
    /* [ECUC_Can_00468] CanHwFilter */
    Can_HwFilterType *ptrCanHwFilters;
    /* [ECUC_Can_00002] CanTTHardwareObjectTrigger */
    Can_TTHwObjectTriggerType *ptrTTHwObjTrigger;
    /* [ECUC_Can_00323] CanHandleType */
    Can_HandleType enObjHandleType;
    /* [ECUC_Can_00495] CanObjectPayloadLength */
    Can_ObjPayloadLenType enObjPayloadLen;
    /* [ECUC_Can_00327] CanObjectType */
    Can_ObjectType enObjType;
    /* [ECUC_Can_00065] CanIdType */
    Can_IdType enIdType;
    /* [ECUC_Can_00326] CanObjectId */
    uint16 u16ObjId;
    /* [ECUC_Can_00467] CanHwObjectCount */
    uint16 u16ObjCount;
    /* [ECUC_Can_00485] CanFdPaddingValue */
    uint8 u8ObjFdPaddingVal;
    uint8 u8HwRxFIFOId;
    /* [ECUC_Can_00490] CanHardwareObjectUsesPolling */
    boolean blObjPolling;
    /* [ECUC_Can_00486] CanTriggerTransmitEnable */
    boolean blTriggerTxEn;
    uint8 u8HwFilterSize;
    uint8 u8TTHwObjTriggerSize;
} Can_HwObjectType;

typedef struct Can_XLHwFilterType_STag
{
    /* hardware specific - vendor define */
    uint32 u32XLHwFilterCode;
    uint32 u32XLHwFilterMask;
    boolean blMasked;
} Can_XLHwFilterType;

/* [ECUC_Can_00526] */
typedef struct CanXL_HwObjectType_STag
{
    /* [ECUC_Can_00528] CanXLHwFilter */
    const Can_XLHwFilterType *ptrXLHwFilters;
    /* [ECUC_Can_00438] CanMainFunctionRWPeriodRef */
    const Can_MainFncPeriodType *ptrRWPeriodRef;
    /* [ECUC_Can_00322] CanControllerRef */
    const Can_ControllerType *ptrCtrlrRef;
    /* [ECUC_Can_00327] CanObjectType */
    Can_ObjectType enObjType;
    /* [ECUC_Can_00527] CanXLObjectId */
    uint16 u16ObjId;
} CanXL_HwObjectType;

/* [ECUC_Can_00354] CanController */
typedef struct Can_ControllerType_STag
{
    Can_ControllerStateType *ptrCanCtrlrSts;
    /* [ECUC_Can_00387] CanControllerBaudrateConfig */
    const Can_BaudrateConfigType *ptrBaudrateCfgs;
    /* [ECUC_Can_00530] CanPartialNetwork */
    const Can_PnNetworkType *ptrCanPnCfgs;
    /* [ECUC_Can_00001] CanTTController */
    const Can_TTControllerType *ptrTTCtrlrCfgs;
    /* [ECUC_Can_00499] CanXLController - not supported */
    // const Can_XLControllerType *ptrXLCtrlrCfgs;
    /* [ECUC_Can_00382] CanControllerBaseAddress - not used */
    /* [ECUC_Can_00359] CanWakeupSourceRef - not used EcuM_WakeupSourceType enCanWakeupRef */
    /*[ECUC_Can_00314] CanBusoffProcessing */
    Can_ModeOprType enCanBusoffModeOp;
    /*[ECUC_Can_00317] CanRxProcessing */
    Can_TrxType enCanRxModeOp;
    /*[ECUC_Can_00318] CanTxProcessing */
    Can_TrxType enCanTxModeOp;
    /* [ECUC_Can_00330] CanWakeupProcessing */
    Can_ModeOprType enCanWakeupModeOp;
    /* [ECUC_Can_00435] CanControllerDefaultBaudrate */
    uint8 u8DefaultBdCfgIdx;
    /* [ECUC_Can_00492] CanControllerEcucPartitionRef - not used */
    uint8 u8BdCfgSize;
    uint8 u8FltBankStart;
    uint8 u8FltBankEnd;
    /* [ECUC_Can_00316] CanControllerId */
    uint8 u8CanCtrlId;
    /* [ECUC_Can_00315] CanControllerActivation - not used */
    /* [ECUC_Can_00529] CanHwPnSupport */
    boolean blCanHwPnSupport;
} Can_ControllerType;

/* [SWS_Can_00413, ECUC_Can_00343] */
/* CanConfigSet[1] */
typedef struct Can_ConfigType_STag
{
    /* [ECUC_Can_00354] CanControllers[1:*] */
    Can_ControllerType *ptrCanCtrlrs;
    /* [ECUC_Can_00324] CanHardwareObject[0:*] */
    Can_HwObjectType *ptrCanHwObjs;
    /* [ECUC_Can_00526] CanXLHardwareObject[0:*] */
    // CanXL_HwObjectType     *ptrCanXLHwObjs; not supported
    uint8 u8NumCanCtrlr;
} Can_ConfigType;

#endif /*End of Can_Types.h*/
