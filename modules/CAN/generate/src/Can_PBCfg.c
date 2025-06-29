#include "Can.h"
#include "Can_PBCfg.h"

Can_IcomGeneralConfigType CanIcomGeneral = {.enCanIcomLevel = CAN_ICOM_LEVEL_ONE, .enCanIcomVariant = CAN_ICOM_VARIANT_SW};
Can_MainFncRWPeriodType MainFncRWPeriod[] = {CAN_MAINFUNCTION_READWRITE_PERIOD, CAN_MAINFUNCTION_READWRITE_PERIOD};
Can_GeneralConfigType CanGeneral =
{
    .stCanIcomGeneral = &CanIcomGeneral,
    .flRWPeriodArr = MainFncRWPeriod,
    .u8CanIcomEnable = TRUE,
    .u8CanMultiplexedTx = TRUE,
    .u8CanIndex = CAN_INSTANCE_ID
};
Can_ControllerStateType CanControllerStates[] = {CAN_CS_UNINIT, CAN_CS_UNINIT};
Can_BaudrateConfigType CanBaudrateConfig[] =
{
    [0] = {
        .stFdBaudrateConf = NULL_PTR,
        .u8BaudratePropSeg = 1,
        .u8BaudrateSeg1 = 2,
        .u8BaudrateSeg2 = 3,
        .u8BaudrateSJW = 4,
        .usBaudRate = 500,
        .usBaudrateBRP = 5,
        .usBaudrateId = 0,
    },
    [2] = {
        .stFdBaudrateConf = NULL_PTR,
        .u8BaudratePropSeg = 1,
        .u8BaudrateSeg1 = 2,
        .u8BaudrateSeg2 = 3,
        .u8BaudrateSJW = 4,
        .usBaudRate = 500,
        .usBaudrateBRP = 5,
        .usBaudrateId = 1,
    }
};
Can_ControllerType CanControllers[] =
{
    [0] = {
        .blActive = TRUE,
        .enCanBusoffModeOp = CAN_MODE_OPR_INTERRUPT,
        .enCanRxModeOp = CAN_TRANSCEIVE_INTERRUPT,
        .enCanTxModeOp = CAN_TRANSCEIVE_INTERRUPT,
        .enCanWakeupModeOp = CAN_MODE_OPR_INTERRUPT,
        .enCanWakeupRef = CAN_WAKEUP_SOURCE_REF,
        .ptrCanCtrlrSts = &CanControllerStates[0],
        .ptDefaultBaudrateCfg = &CanBaudrateConfig[0],
        .stBaudrateCfgs = CanBaudrateConfig,
        .u8BaudrateCfgSize = 2,
        .u8CanCtrlEcucPartRef = 0,
        .u8FltBankStart = 0,
        .u8FltBankEnd = 14,
        .u8Id = 0,
        .u32HwBaseAddr = 0x40006400UL
    },
    [1] = {
        .blActive = TRUE,
        .enCanBusoffModeOp = CAN_MODE_OPR_INTERRUPT,
        .enCanRxModeOp = CAN_TRANSCEIVE_INTERRUPT,
        .enCanTxModeOp = CAN_TRANSCEIVE_INTERRUPT,
        .enCanWakeupModeOp = CAN_MODE_OPR_INTERRUPT,
        .enCanWakeupRef = CAN_WAKEUP_SOURCE_REF,
        .ptrCanCtrlrSts = &CanControllerStates[0],
        .ptDefaultBaudrateCfg = &CanBaudrateConfig[0],
        .stBaudrateCfgs = CanBaudrateConfig,
        .u8BaudrateCfgSize = 2,
        .u8CanCtrlEcucPartRef = 0,
        .u8FltBankStart = 15,
        .u8FltBankEnd = 27,
        .u8Id = 1,
        .u32HwBaseAddr = 0x40006800UL
    }
};
Can_HwFilterConfigType CanHwFilterConfig[] =
{
    [0] = {
        .u32HwFilterCode = 0xCCCC,
        .u32HwFilterMask = 0xCCCC,
        .blMasked = FALSE
    },
    [1] = {
        .u32HwFilterCode = 0xAAAA,
        .u32HwFilterMask = 0xAA00,
        .blMasked = TRUE
    }
};
Can_HwObjectType CanHwObjects[] =
{
    [0] = {
        .blObjPolling = TRUE,
        .blObjTriggerTx = TRUE,
        .enObjHandleType = CAN_HANDLE_BASIC,
        .enObjIdType = CAN_ID_EXTENDED,
        .enObjType = CAN_OBJ_RECEIVE,
        .ptCtrlrRef = &CanControllers[0],
        .ptrRWPeriodRef = &MainFncRWPeriod[0],
        .stCanHwFilters = CanHwFilterConfig,
        .u8CanHwFilterSize = 2,
        .u8HwRxFIFOId = 0,
        .u8ObjFdPaddingVal = 0xCC,
        .usObjCount = 1,
        .usObjId = 0
    },
    [1] = {
        .blObjPolling = TRUE,
        .blObjTriggerTx = TRUE,
        .enObjHandleType = CAN_HANDLE_BASIC,
        .enObjIdType = CAN_ID_EXTENDED,
        .enObjType = CAN_OBJ_RECEIVE,
        .ptCtrlrRef = &CanControllers[1],
        .ptrRWPeriodRef = &MainFncRWPeriod[1],
        .stCanHwFilters = CanHwFilterConfig,
        .u8CanHwFilterSize = 0,
        .u8HwRxFIFOId = 1,
        .u8ObjFdPaddingVal = 0x00,
        .usObjCount = 0,
        .usObjId = 1
    }
};
Can_IcomRxMessageSignalConfigType CanIcomRxMessageSignals_001[] =
{
    [0] = {
        .enSigOpr = CAN_ICOM_SIG_OP_AND,
        .u32SignalMask = 0xFF,
        .u32SignalValue = 0xFF,
    },
    [1] = {
        .enSigOpr = CAN_ICOM_SIG_OP_EQUAL,
        .u32SignalMask = 0xFF,
        .u32SignalValue = 0xFF,
    }
};
Can_IcomRxMessageSignalConfigType CanIcomRxMessageSignals_002[] =
{
    [0] = {
        .enSigOpr = CAN_ICOM_SIG_OP_AND,
        .u32SignalMask = 0xFF,
        .u32SignalValue = 0xFF,
    },
    [1] = {
        .enSigOpr = CAN_ICOM_SIG_OP_EQUAL,
        .u32SignalMask = 0xFF,
        .u32SignalValue = 0xFF,
    }
};
Can_IcomRxMessageType CanIcomRxMessages[] =
{
    [0] = {
        .blPayloadLenErr = TRUE,
        .flTmValue = 0.1,
        .u32MsgId = 0xF001,
        .u32MsgIdMask = 0xFFFF,
        .usCounter = 0x1,
        .stRxMsgSignals = CanIcomRxMessageSignals_001,
    },
    [1] = {
        .blPayloadLenErr = TRUE,
        .flTmValue = 0.1,
        .u32MsgId = 0xF001,
        .u32MsgIdMask = 0xFFFF,
        .usCounter = 0x1,
        .stRxMsgSignals = CanIcomRxMessageSignals_002,
    }
};
Can_IcomWakeupCauseType CanIcomWakeupCauses = {
    .stIcomRxMessage = CanIcomRxMessages
};
Can_IcomControllerConfigType CanIcomController =
{
    .u8CanIcomCfgId = 0x0FF,
    .blCanIcomWakeOnBusoff = TRUE,
    .stCanIcomWakeupCauses = &CanIcomWakeupCauses
};
const Can_ConfigType CanConfig =
{
    .stCanGeneral = &CanGeneral,
    .ptrCanCtrlrs = CanControllers,
    .stCanIcomCtrlr = &CanIcomController,
    .stCanHwObjs = CanHwObjects,
    .u8NumCanCtrlr = CAN_CONTROLLER_NUM
};
