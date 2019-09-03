/*******************************************************************************
* File:         Can_Types.h
* Revision:
* Author:
* Date:         02.08.2019
* Description:  
*******************************************************************************/
#ifndef CAN_TYPES_H
#define CAN_TYPES_H

typedef enum Can_DrvStsType_ETag
{
  CAN_UNINIT,
  CAN_READY
} Can_DrvStsType;

typedef enum Can_ReturnType_ETag
{
  CAN_OK       = 0x00,
  CAN_NOT_OK   = 0x01,
  CAN_BUSY     = 0x02
} Can_ReturnType;

typedef struct Can_ConfigType_STag
{
  
} Can_ConfigType

#endif /*End of Can_Types.h*/
