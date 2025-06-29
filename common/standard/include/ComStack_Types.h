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
 *  Description:  Communication Stack Types AUTOSAR file(AUTOSAR_CP_SWS_CommunicationStackTypes)
 * -----------------------------------------------------------------------------
 * REVISION HISTORY
 * -----------------------------------------------------------------------------
 * Version   Date        Author  Description
 * -----------------------------------------------------------------------------
 * 01.00.00  03/01/2026  Dungnv  Initial version(R24 update)
 *
*******************************************************************************/


#ifndef COMSTACK_TYPES_H
#define COMSTACK_TYPES_H
/*******************************************************************************
Includes
*******************************************************************************/
/* [SWS_Comtype_00004, SWS_Comtype_00015] */
#include "Std_Types.h"
//#include "ComStack_Cfg.h"

/*******************************************************************************
Macro definitions
*******************************************************************************/

/*******************************************************************************
Typedef definitions
*******************************************************************************/
/* [SWS_COMTYPE_00005, SWS_Comtype_00030, SWS_Comtype_00006, SWS_Comtype_00007 SWS_Comtype_00014] */
typedef uint16 PduIdType;

/* [SWS_COMTYPE_00008, SWS_Comtype_00010, SWS_Comtype_00017] */
typedef uint32 PduLengthType;

/* Variables of this type shall be used to store the basic information about a PDU of any type, namely a pointer
variable pointing to its SDU (payload), a pointer to Meta Data of the PDU, and the corresponding length of the SDU in bytes */
/* [SWS_COMTYPE_00011] */
typedef struct PduInfoType_STag
{
  PduLengthType SduLength;
  uint8 *SduDataPtr;
  uint8 *MetaDataPtr;
} PduInfoType;

/* Used to store the identifier of a partial network cluster */
/* [SWS_COMTYPE_00036] */
typedef uint16 PNCHandleType;

/* Specify the parameter to which the value has to be changed (BS or STmin) */
/* [SWS_COMTYPE_00031] */
typedef enum TPParameterType_ETag
{
  /* separation time */
  TP_STMIN      = 0x00,
  /* block size */
  TP_BS         = 0x01,
  /* bandwidth control */
  TP_BC         = 0x02
} TPParameterType;

/* Variables of this type shall be used to store the result of a buffer request */
/* [SWS_COMTYPE_00012] */
typedef enum BufReq_ReturnType_ETag
{
  BUFREQ_OK       = 0x00,
  BUFREQ_E_NOT_OK = 0x01,
  BUFREQ_E_BUSY   = 0x02,
  BUFREQ_E_OVFL   = 0x03
} BufReq_ReturnType;

/* Variables of this type shall be used to store the state of TP buffer. */
/* [SWS_COMTYPE_00027] */
typedef enum TpDataStateType_ETag
{
  TP_DATACONF     = 0x00,
  TP_DATARETRY    = 0x01,
  TP_CONFPENDING  = 0x02
} TpDataStateType;

/* Variables of this type shall be used to store the information about Tp buffer
handling. */
typedef struct RetryInfoType_STag
{
  PduLengthType TxTpDataCnt;
  TpDataStateType TpDataState;
} RetryInfoType;

/* Variables of the type NetworkHandleType shall be used to store the identifier of a communication channel. */
/* [SWS_COMTYPE_00038] */
typedef uint8 NetworkHandleType;

/* Used for the handle Ids of Com and LdCom user callbacks */
/* [SWS_COMTYPE_91001] */
typedef uint16 CbkHandleIdType;

/* Variables of this type are used for expressing time stamps including relative time and absolute calendar time.
  The absolute time starts at 1970-01-01. */
/* [SWS_COMTYPE_91003] */
typedef struct TimeStampType_STag
{
  uint32 nanoseconds;
  uint32 seconds;
  uint16 secondsHi;
} TimeStampType;

/* [SWS_COMTYPE_91004] */
typedef enum TimeStampQualType_ETag
{
  VALID     = 0x00U,
  INVALID   = 0x01U,
  UNCERTAIN = 0x02U
} TimeStampQualType;

/* The Time Tuple represents the clock values of two related HW clocks
• the value of the clock used for timestamping of frames
• and the corresponding value of the adjustable HW clock, derived by cross-timestamping */
/* [SWS_COMTYPE_91002] */
typedef struct TimeTupleType_STag
{
  /* Value of the clock, which is used of ingress/egress timestamping */
  TimeStampType timestampClockValue;
  /* Value of the adjustable HW clock */
  TimeStampType disciplinedClockValue;
  /* Status of time tuple */
  TimeStampQualType timeQuality;
} TimeTupleType;

typedef struct ListElemStructType_Stag ListElemStructType;
/* This type defines one element of a single linked list. Each element represents on part of an
associated data block. The data block could form for example an Ethernet frame. */
/* [SWS_COMTYPE_91005] */
typedef struct ListElemStructType_Stag
{
  uint16 DataLength;                  /* Represents length of data */
  uint8* DataPtr;                     /* Pointer to data */
  ListElemStructType* next;           /* Pointer to next element (NULL_PTR for tail) */
} ListElemStructType;

/*******************************************************************************
 Global functions
 *******************************************************************************/

#endif // COMSTACK_TYPES_H
