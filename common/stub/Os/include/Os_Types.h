/*******************************************************************************
 * COPYRIGHT
 * -----------------------------------------------------------------------------
 * Copyright (c) 2022 by <<>>. All rights reserved.
 * -----------------------------------------------------------------------------
 * FILE DESCRIPTION
 *  File:         Rte_Types.h
 *  Component:    <<>>
 *  Module:       <<>>
 *  Generator:    <<>>
 *  Description:  Stub header file for Os
 * -----------------------------------------------------------------------------
 * REVISION HISTORY
 * -----------------------------------------------------------------------------
 * Version   Date        Author  Description
 * -----------------------------------------------------------------------------
 * 01.00.00  13/08/2022  Dungnv  Initial version
 * 
*******************************************************************************/

#ifndef OS_TYPES_H
#define OS_TYPES_H
#ifdef __cplusplus
extern "C" {
#endif

/*******************************************************************************
Includes
*******************************************************************************/
#include "Std_Types.h"

/*******************************************************************************
Macro definitions
*******************************************************************************/
#define INVALID_OSAPPLICATION ((uint32)0xFFFFFFFF)
#define INVALID_ISR           ((uint32)0xFFFFFFFF)

#define E_OS_SERVICEID    ((StatusType)0x02U)
#define E_OS_ID           ((StatusType)0x03U)
#define E_OS_VALUE        ((StatusType)0x04U)
#define E_OS_STATE        ((StatusType)0x05U)

/*******************************************************************************
Typedef definitions
*******************************************************************************/
#ifndef STATUSTYPEDEFINED
#define STATUSTYPEDEFINED
typedef uint8 StatusType;
#endif
/* SWS_Os_00794 */
typedef uint64 TimeInMicrosecondsType;
/* SWS_Os_00786 */
typedef uint32 CounterType;

typedef uint32 TickType;
typedef P2VAR(TickType, AUTOMATIC, OS_VAR_NOINIT_FAST) TickRefType;

/* This data type identifies the OS-Application. */
/* SWS_Os_00772 */
typedef uint32 ApplicationType;

/* This data type identifies a trusted function */
typedef uint32 TrustedFunctionIndexType;

/* This data type points to a structure which holds the arguments for a call to a trusted function */
typedef TrustedFunctionIndexType * TrustedFunctionParameterRefType;

/* This type holds information how a specific memory region can be accessed. */
typedef uint32 AccessType;

typedef uint32 TaskType;
typedef P2VAR(TaskType, AUTOMATIC, OS_VAR_NOINIT_FAST) TaskRefType;

typedef uint32 ResourceType;

typedef uint32 EventMaskType;
typedef EventMaskType * EventMaskRefType;

typedef uint32 AlarmType;
/* AppMode of the core shall be inherited from another core. */
/* SWS_Os_91007 */
typedef enum AppModeType_ETag
{
  
} AppModeType;

typedef uint32 ISRType;

typedef uint32 PhysicalTimeType;

#define INVALID_SPINLOCK ((uint16)0)
typedef uint16 SpinlockIdType;

typedef uint16 AreaIdType;

/* This data type is a pointer which is able to point to any location in the MCU address space */
typedef void * MemoryStartAddressType;

/* This data type identifies the state of an OS-Application. */
/* SWS_Os_00773 */
typedef enum ApplicationStateType_ETag
{
  APPLICATION_ACCESSIBLE = 1,
  APPLICATION_RESTARTING,
  APPLICATION_TERMINATED
} ApplicationStateType;

/* This data type points to location where a ApplicationStateType can be stored. */
/* SWS_Os_00774 */
typedef P2VAR(ApplicationStateType, AUTOMATIC, OS_VAR_NOINIT_FAST) ApplicationStateRefType;

typedef struct AlarmBaseType_STag
{
  TickType maxallowedvalue;
  TickType ticksperbase;
  TickType mincycle;
} AlarmBaseType;
typedef P2VAR(AlarmBaseType, AUTOMATIC, OS_VAR_NOINIT_FAST) AlarmBaseRefType;

typedef enum TaskStateType_ETag
{
  RUNNING = 1,
  READY,
  WAITING,
  SUSPENDED
} TaskStateType;
typedef P2VAR(TaskStateType, AUTOMATIC, OS_VAR_NOINIT_FAST) TaskStateRefType;

/* This data type identifies if an OS-Application has access to an object. */
typedef enum ObjectAccessType_ETag
{
  ACCESS = 1,
  NO_ACCESS
} ObjectAccessType;

/* This data type identifies an object. */
typedef enum ObjectTypeType_ETag
{
  OBJECT_TASK = 1,
  OBJECT_ISR,
  OBJECT_ALARM,
  OBJECT_RESOURCE,
  OBJECT_COUNTER,
  OBJECT_SCHEDULETABLE
} ObjectTypeType;

/* This data type holds the size (in bytes) of a memory region. */
typedef enum MemorySizeType_ETag
{
  MEM_SIZE_1BYTES,
  MEM_SIZE_2BYTES,
  MEM_SIZE_4BYTES
} MemorySizeType;

typedef struct ScheduleTableType_STag
{
  boolean repeatFlag;
} ScheduleTableType;

typedef enum ScheduleTableStatusType_ETag
{
  SCHEDULETABLE_STOPPED = 1,
  SCHEDULETABLE_NEXT,
  SCHEDULETABLE_WAITING,
  SCHEDULETABLE_RUNNING,
  SCHEDULETABLE_RUNNING_AND_SYNCHRONOUS
} ScheduleTableStatusType;
typedef P2VAR(ScheduleTableStatusType, AUTOMATIC, OS_VAR_NOINIT_FAST) ScheduleTableStatusRefType;

typedef enum ProtectionReturnType_ETag
{
  PRO_IGNORE = 1,
  PRO_TERMINATETASKISR,
  PRO_TERMINATEAPPL,
  PRO_TERMINATEAPPL_RESTART,
  PRO_SHUTDOWN
} ProtectionReturnType;

/* This data type defines the use of a Restart Task after terminating an OS-Application */
typedef enum RestartType_ETag
{
  RESTART = 1,
  NO_RESTART
} RestartType;

typedef enum CoreIdType_ETag
{
  OS_CORE_ID_MASTER = 1,
  OS_CORE_ID_0,
  OS_CORE_ID_1,
  OS_CORE_ID_2,
  OS_CORE_ID_3
} CoreIdType;

typedef enum TryToGetSpinlockType_ETag
{
  TRYTOGETSPINLOCK_SUCCESS = 1,
  TRYTOGETSPINLOCK_NOSUCCESS
} TryToGetSpinlockType;

typedef enum IdleModeType_ETag
{
  IDLE_NO_HALT
} IdleModeType;

#ifdef __cplusplus
}
#endif
#endif /*End of Os_Types.h*/
