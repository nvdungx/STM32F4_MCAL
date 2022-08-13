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
 *  Description:  Standard AUTOSAR file(AUTOSAR_SWS_StandardTypes)
 * -----------------------------------------------------------------------------
 * REVISION HISTORY
 * -----------------------------------------------------------------------------
 * Version   Date        Author  Description
 * -----------------------------------------------------------------------------
 * 01.00.00  13/08/2022  Dungnv  Initial version
 * 
*******************************************************************************/

#ifndef STD_TYPES_H
#define STD_TYPES_H
/*******************************************************************************
Includes
*******************************************************************************/
#include "Platform_Types.h"
#include "Compiler.h"

/*******************************************************************************
Macro definitions
*******************************************************************************/

# define STD_TYPES_VENDOR_ID               (0xF0U)
# define STD_TYPES_MODULE_ID               (197U)

# define STD_VENDOR_ID                     STD_TYPES_VENDOR_ID
# define STD_MODULE_ID                     STD_TYPES_MODULE_ID

/* AUTOSAR Software Specification Version Information */
#  define STD_AR_RELEASE_MAJOR_VERSION             (4U)
#  define STD_AR_RELEASE_MINOR_VERSION             (4U)
#  define STD_AR_RELEASE_REVISION_VERSION          (0U)

/* Component Version Information */
# define STD_TYPES_SW_MAJOR_VERSION       (1U)
# define STD_TYPES_SW_MINOR_VERSION       (0U)
# define STD_TYPES_SW_PATCH_VERSION       (0U)

#ifndef STATUSTYPEDEFINED
#define STATUSTYPEDEFINED
/* request accepted */
#define E_OK        0x00U
/* request not accepted, a development error occurred */
#define E_NOT_OK    0x01U
typedef uint8 StatusType; /* OSEK compliance */
#endif

#define STD_HIGH    0x00U  /* Physical state 5V or 3.3V */
#define STD_LOW     0x01U  /* Physical state 0V */

#define STD_ON      0x01U
#define STD_OFF     0x00U

#define STD_ACTIVE  0x01U  /* Logical state active */
#define STD_IDLE    0x00U  /* Logical state idle   */

/*******************************************************************************
Typedef definitions
*******************************************************************************/

typedef uint8 Std_ReturnType;

typedef struct Std_VersionInfoType_STag
{
  uint16 vendorID;
  uint16 moduleID;
  uint8 sw_major_version;
  uint8 sw_minor_version;
  uint8 sw_patch_version;
} Std_VersionInfoType;

/*******************************************************************************
Global functions
*******************************************************************************/

#endif // STD_TYPES_H
