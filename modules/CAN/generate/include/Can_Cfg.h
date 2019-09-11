/*******************************************************************************
* File:         Can_Cfg.h
* Revision:
* Author:
* Date:         11.09.2019
* Description:  
*******************************************************************************/

#ifndef CAN_CFG_H
#define CAN_CFG_H
/*******************************************************************************
Includes
*******************************************************************************/


/*******************************************************************************
Macro definitions
*******************************************************************************/
/* [ref]: ECUC_Can_00328 */
/* CanGeneral - Pre-compile time variant parameters */
/* [ref]: ECUC_Can_00064 */
#define DEV_ERROR_DETECT_API                STD_ON
/* [ref]: ECUC_Can_00320 */
#define CAN_INSTANCE_ID                     (uint8)0x00
/* [ref]: ECUC_Can_00434 */
#define LPDU_CALLOUTFUNCTION_NAME           CanLPduReceiveCalloutFunction
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
#define CAN_SETBAUDRATE_API                 STD_ON
/* [ref]: ECUC_Can_00113 */
#define CAN_TIMEOUT_DURATION                (float32)1E-6
/* [ref]: ECUC_Can_00106 */
#define CAN_VERSIONINFO_API                 STD_ON
/* [ref]: ECUC_Can_00431 */
#define CAN_OS_COUNTER                     OS_COUNTER0 // name of OsCounter ref

/* CanIcomGeneral - precompile data could be fixed constant in Can_Cfg.c */
/* [ref]: ECUC_Can_00445 */
#define CAN_ICOM_LEVEL                     CAN_ICOM_LEVEL_ONE
/* [ref]: ECUC_Can_00446 */
#define CAN_ICOM_VARIANT                   CAN_ICOM_VARIANT_SW

/* [ref]: ECUC_Can_00354 */
/* CanController - pre-compile time variant parameters */
/*[ref]: ECUC_Can_00314 */
#define CAN_BUSOFF_PROCESING_API           STD_ON
/* [ref]: ECUC_Can_00316 */
#define CAN_CONTROLLER0                    (uint8)0x00
#define CAN_CONTROLLER1                    (uint8)0x01
/*[ref]: ECUC_Can_00317 */
#define CAN_RX_PROCESING_API               STD_ON
/*[ref]: ECUC_Can_00318 */
#define CAN_TX_PROCESING_API               STD_ON
/*[ref]: ECUC_Can_00319 */
#define CAN_WAKEUP_PROCESING_API           STD_ON
/*[ref]: ECUC_Can_00466 */
#define CAN_WAKEUP_FUNCTIONALITY_API       STD_ON
/* [ref]: ECUC_Can_00330 */
#define CAN_WAKEUP_SUPPORT                 STD_ON




























#endif /*End of Can_Cfg.h*/
