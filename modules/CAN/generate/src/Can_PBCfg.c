#include "Can.h"
#include "Can_PBCfg.h"

Can_IcomGeneralConfigType CanIcomGeneral = {.enCanIcomLevel = CAN_ICOM_LEVEL_ONE, .enCanIcomVariant = CAN_ICOM_VARIANT_SW};
Can_MainFncRWPeriodType MainFncRWPeriod[] = {CAN_MAINFUNCTION_READWRITE_PERIOD, CAN_MAINFUNCTION_READWRITE_PERIOD};
Can_GeneralConfigType CanGeneral =
{
    .stCanIcomGeneral = &CanIcomGeneral,
    .flRWPeriodArr = MainFncRWPeriod,
    .ucCanIcomEnable = TRUE,
    .ucCanMultiplexedTx = TRUE,
    .ucCanIndex = CAN_INSTANCE_ID
};
Can_ControllerStateType CanControllerStates[] = {CAN_CS_UNINIT, CAN_CS_UNINIT};
Can_BaudrateConfigType CanBaudrateConfig[] =
{
    [0] = {
        .stFdBaudrateConf = NULL_PTR,
        .ucBaudratePropSeg = 1,
        .ucBaudrateSeg1 = 2,
        .ucBaudrateSeg2 = 3,
        .ucBaudrateSJW = 4,
        .usBaudRate = 500,
        .usBaudrateBRP = 5,
        .usBaudrateId = 0,
    },
    [2] = {
        .stFdBaudrateConf = NULL_PTR,
        .ucBaudratePropSeg = 1,
        .ucBaudrateSeg1 = 2,
        .ucBaudrateSeg2 = 3,
        .ucBaudrateSJW = 4,
        .usBaudRate = 500,
        .usBaudrateBRP = 5,
        .usBaudrateId = 1,
    }
};
Can_ControllerConfigType CanControllers[] =
{
    [0] = {
        .blActive = TRUE,
        .enCanBusoffModeOp = CAN_MODE_OPR_INTERRUPT,
        .enCanRxModeOp = CAN_TRANSCEIVE_INTERRUPT,
        .enCanTxModeOp = CAN_TRANSCEIVE_INTERRUPT,
        .enCanWakeupModeOp = CAN_MODE_OPR_INTERRUPT,
        .enCanWakeupRef = CAN_WAKEUP_SOURCE_REF,
        .ptCanCtrlSts = &CanControllerStates[0],
        .ptDefaultBaudrateCfg = &CanBaudrateConfig[0],
        .stBaudrateCfgs = CanBaudrateConfig,
        .ucBaudrateCfgSize = 2,
        .ucCanCtrlEcucPartRef = 0,
        .ucFltBankStart = 0,
        .ucFltBankEnd = 14,
        .ucId = 0,
        .ulHwBaseAddr = 0x40006400UL
    },
    [1] = {
        .blActive = TRUE,
        .enCanBusoffModeOp = CAN_MODE_OPR_INTERRUPT,
        .enCanRxModeOp = CAN_TRANSCEIVE_INTERRUPT,
        .enCanTxModeOp = CAN_TRANSCEIVE_INTERRUPT,
        .enCanWakeupModeOp = CAN_MODE_OPR_INTERRUPT,
        .enCanWakeupRef = CAN_WAKEUP_SOURCE_REF,
        .ptCanCtrlSts = &CanControllerStates[0],
        .ptDefaultBaudrateCfg = &CanBaudrateConfig[0],
        .stBaudrateCfgs = CanBaudrateConfig,
        .ucBaudrateCfgSize = 2,
        .ucCanCtrlEcucPartRef = 0,
        .ucFltBankStart = 15,
        .ucFltBankEnd = 27,
        .ucId = 1,
        .ulHwBaseAddr = 0x40006800UL
    }
};
Can_HwFilterConfigType CanHwFilterConfig[] =
{
    [0] = {
        .ulHwFilterCode = 0xCCCC,
        .ulHwFilterMask = 0xCCCC,
        .blMasked = FALSE
    },
    [1] = {
        .ulHwFilterCode = 0xAAAA,
        .ulHwFilterMask = 0xAA00,
        .blMasked = TRUE
    }
};
Can_HwObjectConfigType CanHwObjects[] =
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
        .ucCanHwFilterSize = 2,
        .ucHwRxFIFOId = 0,
        .ucObjFdPaddingVal = 0xCC,
        .usObjCount = 1,
        .usObjId = 0
    },
    [1] = {
        .blObjPolling = TRUE,
        .blObjTriggerTx = TRUE,
        .enObjHandleType = CAN_HANDLE_BASIC,
        .enObjIdType = CAN_ID_EXTENDED,
        .enObjType = CAN_OBJ_TRANSMIT,
        .ptCtrlrRef = &CanControllers[1],
        .ptrRWPeriodRef = &MainFncRWPeriod[1],
        .stCanHwFilters = NULL_PTR,
        .ucCanHwFilterSize = 0,
        .ucHwRxFIFOId = 0,
        .ucObjFdPaddingVal = 0x00,
        .usObjCount = 0,
        .usObjId = 1
    }
};
Can_IcomRxMessageSignalConfigType CanIcomRxMessageSignals_001[] =
{
    [0] = {
        .enSigOpr = CAN_ICOM_SIG_OP_AND,
        .ulSignalMask = 0xFF,
        .ulSignalValue = 0xFF,
    },
    [1] = {
        .enSigOpr = CAN_ICOM_SIG_OP_EQUAL,
        .ulSignalMask = 0xFF,
        .ulSignalValue = 0xFF,
    }
};
Can_IcomRxMessageSignalConfigType CanIcomRxMessageSignals_002[] =
{
    [0] = {
        .enSigOpr = CAN_ICOM_SIG_OP_AND,
        .ulSignalMask = 0xFF,
        .ulSignalValue = 0xFF,
    },
    [1] = {
        .enSigOpr = CAN_ICOM_SIG_OP_EQUAL,
        .ulSignalMask = 0xFF,
        .ulSignalValue = 0xFF,
    }
};
Can_IcomRxMessageType CanIcomRxMessages[] =
{
    [0] = {
        .blPayloadLenErr = TRUE,
        .flTmValue = 0.1,
        .ulMsgId = 0xF001,
        .ulMsgIdMask = 0xFFFF,
        .usCounter = 0x1,
        .stRxMsgSignals = CanIcomRxMessageSignals_001,
    },
    [1] = {
        .blPayloadLenErr = TRUE,
        .flTmValue = 0.1,
        .ulMsgId = 0xF001,
        .ulMsgIdMask = 0xFFFF,
        .usCounter = 0x1,
        .stRxMsgSignals = CanIcomRxMessageSignals_002,
    }
};
Can_IcomWakeupCauseType CanIcomWakeupCauses = {
    .stIcomRxMessage = CanIcomRxMessages
};
Can_IcomControllerConfigType CanIcomController =
{
    .ucCanIcomCfgId = 0x0FF,
    .blCanIcomWakeOnBusoff = TRUE,
    .stCanIcomWakeupCauses = &CanIcomWakeupCauses
};
const Can_ConfigType CanConfig =
{
    .stCanGeneral = &CanGeneral,
    .stCanCtrlrs = CanControllers,
    .stCanIcomCtrlr = &CanIcomController,
    .stCanHwObjs = CanHwObjects,
    .ucNumCanController = CAN_CONTROLLER_NUM
};
