/*******************************************************************************
 * COPYRIGHT
 * -----------------------------------------------------------------------------
 * Copyright (c) 2022 by <<>>. All rights reserved.
 * -----------------------------------------------------------------------------
 * FILE DESCRIPTION
 *  File:         ComStack_Types.h
 *  Component:    <<>>
 *  Module:       <<>>
 *  Generator:    <<>>
 *  Description:  Communication Stack Types AUTOSAR file
 * -----------------------------------------------------------------------------
 * REVISION HISTORY
 * -----------------------------------------------------------------------------
 * Version   Date        Author  Description
 * -----------------------------------------------------------------------------
 * 01.00.00  13/08/2022  Dungnv  Initial version
 * 
*******************************************************************************/


#ifndef COMSTACK_TYPES_H
#define COMSTACK_TYPES_H
/*******************************************************************************
Includes
*******************************************************************************/
#include "Std_Types.h"
//#include "ComStack_Cfg.h"

/*******************************************************************************
Macro definitions
*******************************************************************************/

/*******************************************************************************
Typedef definitions
*******************************************************************************/
/* [SWS_COMTYPE_00005] */
typedef uint16 PduIdType;

/* [SWS_COMTYPE_00008] */
typedef uint16 PduLengthType;

/* [SWS_COMTYPE_00038] */
typedef uint8 NetworkHandleType;

/* [SWS_COMTYPE_00039]  */
typedef uint8 IcomConfigIdType;

/* IcomSwitch_ErrorType defines the errors which can occur when activating or
deactivating Pretended Networking. */
/* [SWS_COMTYPE_00040]  */
typedef enum IcomSwitch_ErrorType_ETag
{
  /*  The activation of Pretended Networking was successful. */
  ICOM_SWITCH_E_OK      = 0x00U,
  /*  The activation of Pretended Networking was not successful. */
  ICOM_SWITCH_E_FAILED  = 0x01U
} IcomSwitch_ErrorType;

/* Variables of this type shall be used to store the basic information about
 a PDU of any type, namely a pointer variable pointing to its SDU (payload),
 a pointer to Meta Data of the PDU, and the corresponding length
 of the SDU in bytes */
typedef struct PduInfoType_STag
{
  PduLengthType SduLength;
  uint8 *SduDataPtr;
  uint8 *MetaDataPtr;
} PduInfoType;

/* Variables of this type shall be used to store the result
  of a buffer request */
typedef enum BufReq_ReturnType_ETag
{
  BUFREQ_OK = 0x00,
  BUFREQ_E_NOT_OK = 0x01,
  BUFREQ_E_BUSY = 0x02,
  BUFREQ_E_OVFL = 0x03
} BufReq_ReturnType;

/* Variables of this type shall be used to store the state of TP buffer. */
typedef enum TpDataStateType_ETag
{
  TP_DATACONF = 0x00,
  TP_DATARETRY = 0x01,
  TP_CONFPENDING = 0x02
} TpDataStateType;

/* Variables of this type shall be used to store the information about Tp buffer
handling. */
typedef struct RetryInfoType_STag
{
  TpDataStateType TpDataState;
  PduLengthType TxTpDataCnt;
} RetryInfoType;

/*******************************************************************************
Global functions
*******************************************************************************/

#endif // COMSTACK_TYPES_H
