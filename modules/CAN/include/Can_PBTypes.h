/*******************************************************************************
* File:         Can_PBTypes.h
* Revision:
* Author:
* Date:         02.08.2019
* Description:  
*******************************************************************************/
#ifndef CAN_PBTYPES_H
#define CAN_PBTYPES_H

/* Data structure contain post-compile data:
  ptr to baudrate configuration structure
  ptr to controller HW initialized data
  ptr to HW object handle initialized data
  ptr to receive rule initialized data
  */
typedef struct Can_ControllerPBConfigType_STag
{

  uint8 ucControllerId;
} Can_ControllerPBConfigType;

/* Data structure contain post-compile data:
  general HW configuration data of CAN module
  */
typedef struct Can_GeneralPBConfigType_STag
{
  
  uint8 CanIndex;
} Can_GeneralPBConfigType;

#endif /*End of Can_PBTypes.h*/
