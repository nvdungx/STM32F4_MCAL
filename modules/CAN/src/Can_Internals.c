/*******************************************************************************
* File:         Can_Internals.c
* Revision:     1.0.0
* Author:       Dung van Nguyen
* Date:         04.09.2019
* Description:  definition for internal functions.
*******************************************************************************/

#include "Can_Internals.h"

/*
 *  Service Name...... : Can_DeInit
 *  Service ID      .. : None
 *  Sync/Async........ : Asynchronous
 *  Reentrancy........ : Non Reentrant
 *  Parameters (IN)... : Controller
 *  Parameters (INOUT) : None
 *  Parameters (OUT).. : None
 *  Return Value...... : boolean(true/false)
 *  Register usage     : 
 *  Global variable    : 
 *  Description....... : 
 */
FUNC(boolean, CAN_CODE_SLOW) Can_HwInit(VAR(uint8, AUTOMATIC) Controller)
{
  boolean Lbl_InitSts;
  
  
  return Lbl_InitSts;
}

/*
 *  Service Name...... : Can_HwDeInit
 *  Service ID      .. : None
 *  Sync/Async........ : Asynchronous
 *  Reentrancy........ : Non Reentrant
 *  Parameters (IN)... : Controller
 *  Parameters (INOUT) : None
 *  Parameters (OUT).. : None
 *  Return Value...... : boolean(true/false)
 *  Register usage     : 
 *  Global variable    : 
 *  Description....... : initialize static variables, including flags,
 *    Common setting for the complete CAN HW unit
 *    CAN controller specific settings for each CAN controller.
 */
FUNC(boolean, CAN_CODE_SLOW) Can_HwDeInit(VAR(uint8, AUTOMATIC) Controller)
{
  boolean Lbl_DeInitSts;
  /* [SWS_Can_00053], [SWS_Can_00407] */
  
  return Lbl_DeInitSts;
}














