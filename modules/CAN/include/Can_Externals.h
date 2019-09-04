/*******************************************************************************
* File:         Can_Externals.h
* Revision:
* Author:
* Date:         02.09.2019
* Description:  
*******************************************************************************/

#ifndef CAN_EXTERNALS_H
#define CAN_EXTERNALS_H
/*******************************************************************************
Includes
*******************************************************************************/
#include "Can.h"

/*******************************************************************************
Macro definitions
*******************************************************************************/


/*******************************************************************************
Typedef definitions
*******************************************************************************/

/*******************************************************************************
Global functions
*******************************************************************************/

/* LPDU_CALLOUTFUNCTION_NAME call out function name shall
  be configured by user */
FUNC(boolean, CAN_CODE_FAST) LPDU_CALLOUTFUNCTION_NAME(
  VAR(uint8, AUTOMATIC) Hrh, VAR(Can_IdType, AUTOMATIC) CanId,
    VAR(uint8, AUTOMATIC) CanDataLength,
      P2CONST(uint8, AUTOMATIC, CAN_APPL_DATA) CanSduPtr);

#endif /*End of Can_Externals.h*/
