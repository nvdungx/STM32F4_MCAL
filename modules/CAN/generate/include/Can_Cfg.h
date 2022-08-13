/*******************************************************************************
* File:         Can_Cfg.h
* Revision:     1.0.0
* Author:       Dung van Nguyen
* Date:         11.09.2019
* Description:  Pre-compile time configuration
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

/* [ref]: ECUC_Can_00328 */
/* CanGeneral - Pre-compile time variant parameters */
/* [ref]: ECUC_Can_00064 */
#define CAN_DEV_ERROR_DETECT_API            STD_ON
/* [ref]: ECUC_Can_00320 */
#define CAN_INSTANCE_ID                     (uint8)0x00
/* [ref]: ECUC_Can_00434 */
#define CAN_LPDU_CALLOUT_FUNCTION_NAME      CanLPduReceiveCalloutFunction
/* [ref]: ECUC_Can_00355 */
#define CAN_MAINFUNCTION_BUSOFF_PERIOD      (float32)0
/* [ref]: ECUC_Can_00376 */
#define CAN_MAINFUNCTION_MODE_PERIOD        (float32)0
/* [ref]: ECUC_Can_00357 */
#define CAN_MAINFUNCTION_WAKEUP_PERIOD      (float32)0
/* [ref]: ECUC_Can_00095 */
#define CAN_MULTIPLEXED_TRANSMISSION        STD_ON
/* [ref]: ECUC_Can_00483 */
#define CAN_PUBLIC_ICOM_SUPPORT             STD_ON
/* [ref]: ECUC_Can_00482 */
#define CAN_SET_BAUDRATE_API                STD_ON
/* [ref]: ECUC_Can_00113 */
#define CAN_TIMEOUT_DURATION                (float32)1E-6
/* [ref]: ECUC_Can_00106 */
#define CAN_VERSIONINFO_API                 STD_ON
/* [ref]: ECUC_Can_00431 */
#define CAN_OS_COUNTER                      0 // name of OsCounter ref
#define CAN_ECUC_PART_REF                   EcucPartition
/* [ref]: ECUC_Can_00430 */
#define CAN_SUPPORT_TTCAN                   STD_OFF

/* CanIcomGeneral - precompile data could be fixed constant in Can_Cfg.c */
/* [ref]: ECUC_Can_00445 */
#define CAN_ICOM_LEVEL                     CAN_ICOM_LEVEL_ONE
/* [ref]: ECUC_Can_00446 */
#define CAN_ICOM_VARIANT                   CAN_ICOM_VARIANT_SW

/* [ref]: ECUC_Can_00354 */
/* CanController - pre-compile time variant parameters */
/*[ref]: ECUC_Can_00314 */
#define CAN_BUSOFF_PROCESSING_API          STD_ON
/* [ref]: ECUC_Can_00316 */
#define CAN_CONTROLLER0_ID                    (uint8)0x00
#define CAN_CONTROLLER1_ID                    (uint8)0x01
/*[ref]: ECUC_Can_00317 */
#define CAN_RX_PROCESSING_API               STD_ON
/*[ref]: ECUC_Can_00318 */
#define CAN_TX_PROCESSING_API               STD_ON
/*[ref]: ECUC_Can_00319 */
#define CAN_WAKEUP_PROCESSING_API           STD_ON
/*[ref]: ECUC_Can_00466 */
#define CAN_WAKEUP_FUNCTIONALITY_API       STD_ON
/* [ref]: ECUC_Can_00330 */
#define CAN_WAKEUP_SUPPORT                 STD_ON
/* [ref]: ECUC_Can_00492 */
#define CAN_CTRL_ECUC_PARTITION_REF         (uint8)0x00
/* [ref]: ECUC_Can_00313 */
#define CAN_CPU_CLK_REF                     McuClockReferencePoint
/* [ref]: ECUC_Can_00359 */
#define CAN_WAKEUP_SOURCE_REF               0
/* [ref]: ECUC_Can_00435 */
#define CAN_DEFAULT_BAUDRATE_IDX            (uint8)0x00

#define CAN_CONTROLLER_NUM             ((uint8)2)

/* [ref]: ECUC_Can_00387 */
#define CAN_MAX_BAUD_CONFIG_NUM            ((uint8)2)

/* CanHardwareObject - pre-compile time variant parameters */
/* [ref]: ECUC_Can_00326 */
#define CAN_HWOBJ_RX_HRH0_0 ((uint8)0)
#define CAN_HWOBJ_RX_HRH1_1 ((uint8)1)
#define CAN_HWOBJ_RX_HRH0_2 ((uint8)2)
#define CAN_HWOBJ_RX_HRH1_3 ((uint8)3)

/* CanMainFunctionRWPeriods */
/* [ref]: ECUC_Can_00437 */
/* [ref]: ECUC_Can_00484 */
#define CAN_MAINFUNCTION_READWRITE_PERIOD      (float32)0

#define CAN_HW_OBJS_SIZE ((uint8)2)



















#endif /*End of Can_Cfg.h*/
