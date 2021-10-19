/*******************************************************************************
* File:         Can_GeneralTypes.h
* Revision:     1.0.0
* Author:       Dung van Nguyen
* Date:         10.17.2021
* Description:  General type definitions shared among the AUTOSAR CAN modules
*               Can, CanIf and CanTrcv.
*******************************************************************************/

#ifndef CAN_GENERALTYPES_H
#define CAN_GENERALTYPES_H
/* [SWS_Can_00222] */
/*******************************************************************************
Includes
*******************************************************************************/
#include "ComStack_Types.h"

/*******************************************************************************
Macro definitions
*******************************************************************************/
/* transmit request could not be processed because no
  transmit object was available */
/* [SWS_Can_00039] */
#define CAN_BUSY 0x02U

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
typedef uint8 Can_HwHandleType;

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
  /* The CAN controller takes part in communication,
    but does not send active error frames. */
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
  /* Standard/Extended CAN ID of CAN LPDU */
  Can_IdType        CanId;
  /* ID of the corresponding Hardware Object Range */
  Can_HwHandleType  Hoh;
  /* ControllerId provided by CanIf clearly identify
    the corresponding controller */
  uint8             ControllerId;
} Can_HwType;

/* This type unites PduId (swPduHandle), SduLength (length), SduData (sdu), and
CanId (id) for any CAN L-SDU. */
/* [SWS_Can_00415] */
typedef struct Can_PduType_STag
{
  Can_IdType        id;
  PduIdType         swPduHandle;
  uint8             length;
  uint8             *sdu;
} Can_PduType;

#endif /*End of Can_GeneralTypes.h*/
