/*******************************************************************************
 * COPYRIGHT
 * -----------------------------------------------------------------------------
 * Copyright (c) 2022 by <<>>. All rights reserved.
 * -----------------------------------------------------------------------------
 * FILE DESCRIPTION
 *  File:         Can_Externals.h
 *  Component:    Header
 *  Module:       CAN
 *  Generator:    N/A
 *  Description:  
 * -----------------------------------------------------------------------------
 * REVISION HISTORY
 * -----------------------------------------------------------------------------
 * Version   Date        Author  Description
 * -----------------------------------------------------------------------------
 * 01.00.00  13/08/2022  Dungnv  Initial version
 * 
*******************************************************************************/

#ifndef CAN_EXTERNALS_H
#define CAN_EXTERNALS_H
/*******************************************************************************
Includes
*******************************************************************************/
#include "Can_GeneralTypes.h"

/*******************************************************************************
Macro definitions
*******************************************************************************/


/*******************************************************************************
Typedef definitions
*******************************************************************************/

/*******************************************************************************
Global functions
*******************************************************************************/

/* CAN_LPDU_CALLOUT_FUNCTION_NAME call out function name shall
  be configured by user */
#ifdef CAN_LPDU_CALLOUT_FUNCTION_NAME
FUNC(boolean, CAN_CODE_FAST) CAN_LPDU_CALLOUT_FUNCTION_NAME(VAR(uint8, AUTOMATIC) Hrh, VAR(Can_IdType, AUTOMATIC) CanId,
    VAR(uint8, AUTOMATIC) CanDataLength, P2CONST(uint8, AUTOMATIC, CAN_APPL_DATA) CanSduPtr);
#endif

#endif /*End of Can_Externals.h*/
