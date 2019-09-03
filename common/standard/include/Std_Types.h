/*******************************************************************************
* File:         Std_Types.h
* Revision:
* Author:
* Date:         02.08.2019
* Description:  Standard AUTOSAR file(AUTOSAR_SWS_StandardTypes)
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


#ifndef STATUSTYPEDEFINED
#define STATUSTYPEDEFINED
#define E_OK       0x00U
#define E_NOT_OK   0x01U
typedef uint8 StatusType; /* OSEK compliance */
#endif



#define STD_HIGH    0x00U  /* Physical state 5V or 3.3V */
#define STD_LOW     0x01U  /* Physical state 0V         */


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
