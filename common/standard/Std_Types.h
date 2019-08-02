/*******************************************************************************
* File:         Std_Types.h
* Revision:
* Author:
* Date:         02.08.2019
* Description:  Standard AUTOSAR file
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


#define E_OK        0
#define E_NOT_OK    1


#define STD_HIGH    1  /* Physical state 5V or 3.3V */
#define STD_LOW     0  /* Physical state 0V         */


#define STD_ON      1
#define STD_OFF     0


#define STD_ACTIVE  1  /* Logical state active */
#define STD_IDLE    0  /* Logical state idle   */

/*******************************************************************************
Typedef definitions
*******************************************************************************/

typedef uint8 Std_ReturnType;

typedef struct
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
