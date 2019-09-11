/*******************************************************************************
* File:         Can_Types.h
* Revision:
* Author:
* Date:         02.08.2019
* Description:  
*******************************************************************************/
#ifndef CAN_TYPES_H
#define CAN_TYPES_H

#include "EcuM.h"
#include "Can_GeneralTypes.h"

typedef enum Can_DrvStsType_ETag
{
  CAN_UNINIT,
  CAN_READY
} Can_DrvStsType;

typedef enum CanHandleType_ETag
{
  CAN_OBJ_BASIC,
  CAN_OBJ_FULL
} CanHandleType;

typedef enum CanIdType_ETag
{
  CAN_ID_STANDARD,
  CAN_ID_EXTENDED,
  CAN_ID_MIXED
} CanIdType;

typedef enum CanObjectType_ETag
{
  CAN_OBJ_RECEIVE,
  CAN_OBJ_TRANSMIT
} CanObjectType;

typedef enum Can_ModeOpType_ETag
{
  CAN_MODE_INTERRUPT,
  CAN_MODE_POLLING,
  CAN_MODE_MIXED
} Can_ModeOpType;

/* Type of CanIcomSignalOperation */
typedef enum Can_IcomSignalOperationType_ETag
{
  CAN_ICOM_SIG_OP_AND = 0u,
  CAN_ICOM_SIG_OP_EQUAL,
  CAN_ICOM_SIG_OP_GREATER,
  CAN_ICOM_SIG_OP_SMALLER,
  CAN_ICOM_SIG_OP_XOR
} Can_IcomSignalOperationType;

typedef enum Can_IcomLevelType_ETag
{
  CAN_ICOM_LEVEL_ONE,
  CAN_ICOM_LEVEL_TWO
} Can_IcomLevelType;

typedef enum CanIcomVariantType_ETag
{
  CAN_ICOM_VARIANT_NONE,
  CAN_ICOM_VARIANT_HW,
  CAN_ICOM_VARIANT_SW
} Can_IcomVariantType;

#endif /*End of Can_Types.h*/
