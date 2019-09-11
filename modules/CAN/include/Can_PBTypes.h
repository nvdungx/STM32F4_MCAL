/*******************************************************************************
* File:         Can_PBTypes.h
* Revision:
* Author:
* Date:         02.08.2019
* Description:  
*******************************************************************************/
#ifndef CAN_PBTYPES_H
#define CAN_PBTYPES_H

#include "Can_Types.h"

typedef struct Can_FdBaudrateConfigType_STag
{
  uint16 usFdBaudrateBRP;
  uint8  ucFdBaudratePropSeg;
  uint8  ucFdBaudrateSeg1;
  uint8  ucFdBaudrateSeg2;
  uint8  ucFdFdBaudrateSJW;
  uint8  ucFdBaudrateSspOffset;
  uint8  ucFdBaudrateTxBRS;
} Can_FdBaudrateConfigType;

typedef struct Can_BaudrateConfigType_STag
{
  const  Can_FdBaudrateConfigType * stCan_FdBaudrateConf;
  uint16                            usBaudrateId;
  uint16                            usBaudrateBRP;
  uint8                             ucBaudratePropSeg;
  uint8                             ucBaudrateSeg1;
  uint8                             ucBaudrateSeg2;
  uint8                             ucBaudrateSJW;
} Can_BaudrateConfigType;

/* Data structure contain post-compile data:
  ptr to baudrate configuration structure
  ptr to controller HW initialized data
  ptr to HW object handle initialized data
  ptr to receive rule initialized data
  */
typedef struct Can_ControllerPBConfigType_STag
{
  const Can_BaudrateConfigType *stCan_BaudrateConf;
  uint8                         ucCanControllerDefaultBaudrate;
  uint8                         ucCanControllerId;
} Can_ControllerPBConfigType;

typedef struct Can_IcomControllerPBConfigType_STag
{
  
} Can_IcomControllerPBConfigType;

typedef struct Can_HwObjectPBConfigType_STag
{
  uint16          usObjId;
  uint16          usObjCount;
  CanHandleType   enObjHandleType;
  CanIdType       enObjIdType;
  CanObjectType   enObjType;
  uint8           ucObjFdPaddingVal;
  uint8           ucCanControllerRef;
  boolean         blObjPolling;
  boolean         blObjTrigerTx;
} Can_HwObjectPBConfigType;

typedef struct Can_HwFilterPBConfigType_STag
{
  
} Can_HwFilterPBConfigType;



#endif /*End of Can_PBTypes.h*/
