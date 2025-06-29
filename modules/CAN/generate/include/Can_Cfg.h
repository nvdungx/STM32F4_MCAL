/*******************************************************************************
 * COPYRIGHT
 * -----------------------------------------------------------------------------
 * Copyright (c) 2022 by <<>>. All rights reserved.
 * -----------------------------------------------------------------------------
 * FILE DESCRIPTION
 *  File:         Can_Cfg.h
 *  Component:    Header
 *  Module:       CAN
 *  Generator:    CAN Module Configuration Generator
 *  Description:  CAN Driver pre-compile configuration header file
 * -----------------------------------------------------------------------------
 * REVISION HISTORY
 * -----------------------------------------------------------------------------
 * Version   Date        Author  Description
 * -----------------------------------------------------------------------------
 * 01.00.00  13/03/2026  Dungnv  Initial version
 *
 *******************************************************************************/

#ifndef CAN_CFG_H
#define CAN_CFG_H
/*******************************************************************************
Includes
*******************************************************************************/


/*******************************************************************************
Macro definitions
*******************************************************************************/
#define CAN_MODULE_ID             0x80U
#define CAN_VENDOR_ID             0x00U
#define SW_MINOR_VERSION          0x01U
#define SW_MAJOR_VERSION          0x00U
#define SW_PATCH_VERSION          0x00U
#define NUMBER_CAN_CONTROLLER     0x02U

/* [ECUC_Can_00497] CanGeneral - Pre-compile time variant parameters */
/* [ECUC_Can_00064] CanDevErrorDetect */
#define CAN_DEV_ERROR_DETECT_API            STD_ON
/* [ECUC_Can_00496] CanEnableSecurityEventReporting */
#define CAN_SEC_EVENT_REPORT                STD_ON
/* [ECUC_Can_00498] CanGlobalTimeSupport */
#define CAN_GLOBAL_TIME_SUPPORT             STD_ON
/* [ECUC_Can_00320] CanIndex */
#define CAN_INSTANCE_ID                     (uint8)0x00U
/* [ECUC_Can_00434] CanLPduReceiveCalloutFunction */
#define CAN_LPDU_CALLOUT_FUNCTION_NAME      CanLPduReceiveCalloutFunction
/* [ECUC_Can_00355] CanMainFunctionBusoffPeriod */
#define CAN_MAINFUNCTION_BUSOFF_PERIOD      (float32)0.1f
/* [ECUC_Can_00376] CanMainFunctionModePeriod */
#define CAN_MAINFUNCTION_MODE_PERIOD        (float32)0.1f
/* [ECUC_Can_00357] CanMainFunctionWakeupPeriod */
#define CAN_MAINFUNCTION_WAKEUP_PERIOD      (float32)0.1f
/* [ECUC_Can_00095] CanMultiplexedTransmission */
#define CAN_MULTIPLEXED_TRANSMISSION        STD_ON
/* [ECUC_Can_00482] CanSetBaudrateApi */
#define CAN_SET_BAUDRATE_API                STD_ON
/* [ECUC_Can_00113] CanTimeoutDuration */
#define CAN_TIMEOUT_DURATION                (float32)0.1f
/* [ECUC_Can_00106] CanVersionInfoApi */
#define CAN_VERSIONINFO_API                 STD_ON
/* [ECUC_Can_00431] CanOsCounterRef */
#define CAN_OS_COUNTER                      0 // name of OsCounter ref
/* [ECUC_Can_00491] CanEcucPartitionRef */
#define CAN_ECUC_PART_REF                   EcucPartition_Core0QM
/* [ECUC_Can_00430] CanSupportTTCANRef */
#define CAN_SUPPORT_TTCAN                   STD_OFF
/* [ECUC_Can_00437] CanMainFunctionRWPeriods */
#define CAN_MAINFUNCTION_RW_PERIOD          (float32)0.1f
/* [ECUC_Can_00525, ECUC_Can_00524] CanXLEthGlobalTimeSupport - CANXL driver */
#define CANXL_ETH_GLOBALTIME_SUPPORT        STD_OFF

/* [ECUC_Can_00354] CanController - pre-compile time variant parameters */
/* [ECUC_Can_00314] CanBusoffProcessing */
#define CAN_BUSOFF_PROCESSING_API           STD_ON
/* [ECUC_Can_00316] */
#define CAN_CONTROLLER0_ID                  (uint8)0x00U
#define CAN_CONTROLLER1_ID                  (uint8)0x01U
/* [ECUC_Can_00317] CanRxProcessing */
#define CAN_RX_PROCESSING_API               STD_ON
/* [ECUC_Can_00318] CanTxProcessing */
#define CAN_TX_PROCESSING_API               STD_ON
/* [ECUC_Can_00319] CanWakeupProcessing */
#define CAN_WAKEUP_PROCESSING_API           STD_ON
/* [ECUC_Can_00330] CanWakeupSupport */
#define CAN_WAKEUP_SUPPORT                  STD_ON
/* [ECUC_Can_00313] CanCpuClockRef - not used #define CAN_CPU_CLK_REF McuClockReferencePoint */
/* [ECUC_Can_00359] CanWakeupSourceRef - not used #define CAN_WAKEUP_SOURCE_REF 0*/

/* [ECUC_Can_00435] */
#define CAN_DEFAULT_BAUDRATE_IDX            (uint8)0x00

#define CAN_CONTROLLER_NUM             ((uint8)2)

/* [ECUC_Can_00387] */
#define CAN_MAX_BAUD_CONFIG_NUM            ((uint8)2)

/* CanHardwareObject - pre-compile time variant parameters */
/* [ECUC_Can_00326] */
#define CAN_HWOBJ_RX_HRH0_0 ((uint8)0)
#define CAN_HWOBJ_RX_HRH1_1 ((uint8)1)
#define CAN_HWOBJ_RX_HRH0_2 ((uint8)2)
#define CAN_HWOBJ_RX_HRH1_3 ((uint8)3)

/* CanMainFunctionRWPeriods */
/* [ECUC_Can_00437] */
/* [ECUC_Can_00484] */
#define CAN_MAINFUNCTION_READWRITE_PERIOD      (float32)0

#define CAN_HW_OBJS_SIZE ((uint8)2)



















#endif /*End of Can_Cfg.h*/
