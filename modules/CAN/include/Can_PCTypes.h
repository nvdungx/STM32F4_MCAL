/*******************************************************************************
* File:         Can_PCTypes.h
* Revision:
* Author:
* Date:         02.08.2019
* Description:  
*******************************************************************************/
#ifndef CAN_PCTYPES_H
#define CAN_PCTYPES_H

/* Data structure contain pre-compile data:
  ref to EcuM wakeup API
  ref to ICOM configuration data
  interrupt enable/disable status
  controller sw status
  controller tx/rx error status
  */
typedef struct Can_ControllerPCConfigType_STag
{

  uint8 ucControllerId;
} Can_ControllerPCConfigType;

#endif /*End of Can_PCTypes.h*/
