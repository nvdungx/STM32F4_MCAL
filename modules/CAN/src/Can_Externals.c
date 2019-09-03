/*******************************************************************************
* File:         Can_Externals.c
* Revision:
* Author:
* Date:         03.09.2019
* Description:  
*******************************************************************************/

/*******************************************************************************
Includes
*******************************************************************************/
#include "Can_Externals.h"

/*
 *  Service Name...... : LPDU_CALLOUTFUNCTION_NAME
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
/* LPDU_CALLOUTFUNCTION_NAME call out function name shall
  be configured by user */
FUNC(boolean, CAN_CODE_FAST) LPDU_CALLOUTFUNCTION_NAME(
  VAR(uint8, AUTOMATIC) Hrh, VAR(Can_IdType, AUTOMATIC) CanId,
    VAR(uint8, AUTOMATIC) CanDataLength, P2CONST(uint8, AUTOMATIC) CanSduPtr)
{
  /* User defined call out routine */
}

