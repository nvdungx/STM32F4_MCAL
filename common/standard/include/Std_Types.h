/*******************************************************************************
 * COPYRIGHT
 * -----------------------------------------------------------------------------
 * Copyright (c) 2022 by <<>>. All rights reserved.
 * -----------------------------------------------------------------------------
 * FILE DESCRIPTION
 *  File:         Std_Types.h
 *  Component:    <<>>
 *  Module:       <<>>
 *  Generator:    <<>>
 *  Description:  Standard AUTOSAR file(AUTOSAR_CP_SWS_StandardTypes)
 * -----------------------------------------------------------------------------
 * REVISION HISTORY
 * -----------------------------------------------------------------------------
 * Version   Date        Author  Description
 * -----------------------------------------------------------------------------
 * 01.00.00  03/01/2026  Dungnv  Initial version(R24 update)
 *
*******************************************************************************/

#ifndef STD_TYPES_H
#define STD_TYPES_H
/*******************************************************************************
Includes
*******************************************************************************/
#include "Platform_Types.h"

/*******************************************************************************
Macro definitions
*******************************************************************************/

# define STD_TYPES_VENDOR_ID               (0xF0U)
# define STD_TYPES_MODULE_ID               (197U)

# define STD_VENDOR_ID                     STD_TYPES_VENDOR_ID
# define STD_MODULE_ID                     STD_TYPES_MODULE_ID

/* AUTOSAR Software Specification Version Information */
#  define STD_AR_RELEASE_MAJOR_VERSION             (24U)
#  define STD_AR_RELEASE_MINOR_VERSION             (0U)
#  define STD_AR_RELEASE_REVISION_VERSION          (0U)

/* Component Version Information */
# define STD_TYPES_SW_MAJOR_VERSION       (1U)
# define STD_TYPES_SW_MINOR_VERSION       (0U)
# define STD_TYPES_SW_PATCH_VERSION       (0U)

#ifndef STATUSTYPEDEFINED
  #define STATUSTYPEDEFINED
  /* [SWS_Std_00006] */
  #define E_OK        ((uint8)0x00U)
  typedef uint8 StatusType; /* OSEK compliance */
#endif

/* [SWS_Std_00007] */
#define STD_LOW     0x00U  /* Physical state 0V */
#define STD_HIGH    0x01U  /* Physical state 5V or 3.3V */

/* [SWS_Std_00010] */
#define STD_OFF     0x00U
#define STD_ON      0x01U

/* [SWS_Std_00013] */
#define STD_IDLE    0x00U  /* Logical state idle   */
#define STD_ACTIVE  0x01U  /* Logical state active */

#define E_NOT_OK    ((uint8)0x01U)

/* [SWS_Std_00031] */
#define NULL_PTR    ((void *)0)
/*******************************************************************************
 Typedef definitions
*******************************************************************************/
/* [SWS_Std_00005, SWS_Std_00011] */
typedef uint8 Std_ReturnType;
/* request not accepted, a development error occurred */

/* [SWS_Std_00015] */
typedef struct Std_VersionInfoType_STag
{
  uint16 vendorID;
  uint16 moduleID;
  uint8 sw_major_version;
  uint8 sw_minor_version;
  uint8 sw_patch_version;
} Std_VersionInfoType;

/* [SWS_Std_00022] */
typedef uint8 Std_TransformerErrorCode;
/* [SWS_Std_00024, SWS_Std_00025, SWS_Std_00026] */
#define STD_TRANSFORMER_UNSPECIFIED   ((Std_TransformerClass)0x00U)
#define STD_TRANSFORMER_SERIALIZER    ((Std_TransformerClass)0x01U)
#define STD_TRANSFORMER_SAFETY        ((Std_TransformerClass)0x02U)
#define STD_TRANSFORMER_SECURITY      ((Std_TransformerClass)0x03U)
#define STD_TRANSFORMER_CUSTOM        ((Std_TransformerClass)0xFFU)

/* [SWS_Std_00023] */
typedef uint8 Std_TransformerClass;
/* [SWS_Std_00028] */
typedef uint8 Std_TransformerForwardCode;
/* [SWS_Std_00029] */
#define STD_TRANSFORMER_E_OK                      ((uint8)0x00U)
#define STD_TRANSFORMER_E_SAFETY_INVALID_REP      ((uint8)0x01U)
#define STD_TRANSFORMER_E_SAFETY_INVALID_CRC      ((uint8)0x02U)
#define STD_TRANSFORMER_E_SAFETY_INVALID_SEQ      ((uint8)0x03U)

/* [SWS_Std_00021] */
typedef struct Std_TransformerError_STag
{
  Std_TransformerErrorCode errorCode;
  Std_TransformerClass transformerClass;
} Std_TransformerError;

/* [SWS_Std_91001, SWS_Std_00017] */
typedef uint8 Std_MessageTypeType;
#define STD_MESSAGETYPE_REQUEST    ((Std_MessageTypeType)0x00U)
#define STD_MESSAGETYPE_RESPONSE   ((Std_MessageTypeType)0x01U)

/* [SWS_Std_91002, SWS_Std_00019] */
typedef uint8 Std_MessageResultType;
#define STD_MESSAGERESULT_OK       ((Std_MessageResultType)0x00U)
#define STD_MESSAGERESULT_ERROR    ((Std_MessageResultType)0x01U)

/* [SWS_Std_91003] */
typedef Std_ReturnType (*Std_ExtractProtocolHeaderFieldsType) (const uint8* buffer, uint32 bufferLength, Std_MessageTypeType* messageType, Std_MessageResultType* messageResult);



/*******************************************************************************
Global functions
*******************************************************************************/

#endif // STD_TYPES_H
