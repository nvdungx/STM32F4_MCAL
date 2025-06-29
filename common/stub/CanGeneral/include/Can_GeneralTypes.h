/*******************************************************************************
 * COPYRIGHT
 * -----------------------------------------------------------------------------
 * Copyright (c) 2022 by <<>>. All rights reserved.
 * -----------------------------------------------------------------------------
 * FILE DESCRIPTION
 *  File:         Can_GeneralTypes.h
 *  Component:    <<>>
 *  Module:       <<>>
 *  Generator:    <<>>
 *  Description:  General type definitions shared among the AUTOSAR CAN modules
 *               Can, CanIf and CanTrcv.
 * -----------------------------------------------------------------------------
 * REVISION HISTORY
 * -----------------------------------------------------------------------------
 * Version   Date        Author  Description
 * -----------------------------------------------------------------------------
 * 01.00.00  03/01/2026  Dungnv  Initial version(R24 update)
 *
*******************************************************************************/

#ifndef CAN_GENERALTYPES_H
#define CAN_GENERALTYPES_H
/* [SWS_Can_00222, SWS_Can_00436] */
/*******************************************************************************
Includes
*******************************************************************************/
#include "ComStack_Types.h"

/*******************************************************************************
Macro definitions
*******************************************************************************/
/* transmit request could not be processed because no transmit object was available
 Overlayed return value of Std_ReturnType for CAN driver API Can_Write() */
/* [SWS_Can_00039] */
#define CAN_BUSY ((Std_ReturnType)0x02U)

/*******************************************************************************
Typedef definitions
*******************************************************************************/
/* Standard32Bit -- 0..0x400007FF
*  Extended32Bit -- 0..0xDFFFFFFF
*  Represents the Identifier of an L-PDU. The two most significant bits specify
*  the frame type:
*  00 CAN message with Standard CAN ID
*  01 CAN FD frame with Standard CAN ID
*  10 CAN message with Extended CAN ID
*  11 CAN FD frame with Extended CAN ID
*/
/* [SWS_Can_00416] */
typedef uint32 Can_IdType;

/* Represents the hardware object handles of a CAN hardware unit. For CAN
hardware units with more than 255 HW objects use extended range. */
/* [SWS_Can_00429] */
typedef uint16 Can_HwHandleType;

/* States that are used by the several ControllerMode functions */
/* [SWS_Can_91013] */
typedef enum Can_ControllerStateType_ETag
{
  /* CAN controller state UNINIT. */
  CAN_CS_UNINIT     = 0x00U,
  /* CAN controller state STARTED. */
  CAN_CS_STARTED    = 0x01U,
  /* CAN controller state STOPPED. */
  CAN_CS_STOPPED    = 0x02U,
  /* CAN controller state SLEEP. */
  CAN_CS_SLEEP      = 0x03U
} Can_ControllerStateType;

/* Error states of a CAN controller */
/* [SWS_Can_91003] */
typedef enum Can_ErrorStateType_ETag
{
  /* The CAN controller takes fully part in communication. */
  CAN_ERRORSTATE_ACTIVE  = 0x00U,
  /* The CAN controller takes part in communication, but does not send active error frames. */
  CAN_ERRORSTATE_PASSIVE = 0x01U,
  /* The CAN controller does not take part in communication */
  CAN_ERRORSTATE_BUSOFF  = 0x02U
} Can_ErrorStateType;

/* This type defines a data structure which clearly provides an Hardware Object
Handle including its corresponding CAN Controller and therefore CanDrv as well
as the specific CanId. */
/* [SWS_CAN_00496] */
typedef struct Can_HwType_STag
{
  Can_IdType        CanId; /* Standard/Extended CAN ID of CAN LPDU */
  Can_HwHandleType  Hoh; /* ID of the corresponding Hardware Object Range */
  uint8             ControllerId;/* ControllerId provided by CanIf clearly identify the corresponding controller */
} Can_HwType;

/* This type unites PduId (swPduHandle), SduLength (length), SduData (sdu), and CanId (id) for any CAN L-SDU. */
/* [SWS_Can_00415] */
typedef struct Can_PduType_STag
{
  Can_IdType        id;
  PduIdType         swPduHandle;
  uint8             length;
  uint8             *sdu;
} Can_PduType;

/* The enumeration represents a superset of CAN Error Types which typical CAN HW is able to report.
 That means not all CAN HW will be able to support the complete set */
/* [SWS_Can_91021] */
typedef enum Can_ErrorType_ETag
{
  /* A 0 was transmitted and a 1 was read back */
  CAN_ERROR_BIT_MONITORING1 = 0x01U,
  /* A 1 was transmitted and a 0 was read back */
  CAN_ERROR_BIT_MONITORING0 = 0x02U,
  /*  The HW reports a CAN bit error but cannot report distinguish between BIT_MONITORING1 and BIT_MONITORING0 */
  CAN_ERROR_BIT = 0x03U,
  /* Acknowledgement check failed */
  CAN_ERROR_CHECK_ACK_FAILED = 0x04U,
  /* Acknowledgement delimiter check failed */
  CAN_ERROR_ACK_DELIMITER = 0x05U,
  /* The sender lost in arbitration */
  CAN_ERROR_ARBITRATION_LOST = 0x06U,
  /* CAN overload detected via an overload frame. Indicates that the receive buffers of a receiver are full. */
  CAN_ERROR_OVERLOAD = 0x07U,
  /* Violations of the fixed frame format */
  CAN_ERROR_CHECK_FORM_FAILED = 0x08U,
  /* Stuffing bits not as expected */
  CAN_ERROR_CHECK_STUFFING_FAILED = 0x09U,
  /* CRC failed */
  CAN_ERROR_CHECK_CRC_FAILED = 0x0AU,
  /* Bus lock (Bus is stuck to dominant level) */
  CAN_ERROR_BUS_LOCK = 0x0BU,
} Can_ErrorType;

/* Variables of this type are used to express time stamps based on relative time */
/* [SWS_CAN_91029] */
typedef struct Can_TimeStampType_STag
{
  uint32 nanoseconds;
  uint32 seconds;
} Can_TimeStampType;

#endif /*End of Can_GeneralTypes.h*/
