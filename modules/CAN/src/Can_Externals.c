/*******************************************************************************
 * COPYRIGHT
 * -----------------------------------------------------------------------------
 * Copyright (c) 2022 by <<>>. All rights reserved.
 * -----------------------------------------------------------------------------
 * FILE DESCRIPTION
 *  File:         Can_Externals.c
 *  Component:    Source
 *  Module:       CAN
 *  Generator:    N/A
 *  Description:  definition for external callout and callback functions.
 * -----------------------------------------------------------------------------
 * REVISION HISTORY
 * -----------------------------------------------------------------------------
 * Version   Date        Author  Description
 * -----------------------------------------------------------------------------
 * 01.00.00  13/08/2022  Dungnv  Initial version
 * 
*******************************************************************************/

/*******************************************************************************
Includes
*******************************************************************************/
#include "Can_Externals.h"

/*
 *  Service Name...... : CAN_LPDU_CALLOUT_FUNCTION_NAME
 *  Service ID      .. : 0x20
 *  Sync/Async........ : Asynchronous
 *  Reentrancy........ : Non Reentrant
 *  Parameters (IN)... : Hrh, CanId, CanDataLength, CanSduPtr
 *  Parameters (INOUT) : None
 *  Parameters (OUT).. : None
 *  Return Value...... : boolean(true/false)
 *  Register usage     : 
 *  Global variable    : 
 *  Description....... : This function handle L-PDU callouts on every reception
 *                       of a L-PDU.
 */
/* CAN_LPDU_CALLOUT_FUNCTION_NAME call out function name shall
  be configured by user */
#ifdef CAN_LPDU_CALLOUT_FUNCTION_NAME
FUNC(boolean, CAN_CODE_FAST) CAN_LPDU_CALLOUT_FUNCTION_NAME(VAR(uint8, AUTOMATIC) Hrh, VAR(Can_IdType, AUTOMATIC) CanId,
    VAR(uint8, AUTOMATIC) CanDataLength, P2CONST(uint8, AUTOMATIC, CAN_APPL_DATA) CanSduPtr)
{
    /* User defined call out routine */
}
#endif
