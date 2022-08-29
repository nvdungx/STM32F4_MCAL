/*******************************************************************************
 * COPYRIGHT
 * -----------------------------------------------------------------------------
 * Copyright(c) 2022 by <<>>. All rights reserved.
 * -----------------------------------------------------------------------------
 * FILE DESCRIPTION
 *  File:         Os.h
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

#ifndef OS_H
#define OS_H
#ifdef __cplusplus
extern "C" {
#endif

/*******************************************************************************
Includes
*******************************************************************************/
#include "Std_Types.h"
#include "Rte_Types.h"
#include "Os_Cfg.h"
#include "Os_Memmap.h"

#include "Os_Types.h"

/*******************************************************************************
Macro definitions
*******************************************************************************/
#define OSMEMORY_IS_READABLE(AccessType)(TRUE)
#define OSMEMORY_IS_WRITEABLE(AccessType)(TRUE)
#define OSMEMORY_IS_EXECUTABLE(AccessType)(TRUE)
#define OSMEMORY_IS_STACKSPACE(AccessType)(TRUE)

/* The total number of cores */
uint16 TotalNumberOfCores;

/*******************************************************************************
Typedef definitions
*******************************************************************************/
/* OSEK */
FUNC(StatusType, OS_CODE_SLOW) ActivateTask(TaskType TaskID);
FUNC(StatusType, OS_CODE_SLOW) TerminateTask(TaskType TaskID);
FUNC(StatusType, OS_CODE_SLOW) ChainTask(TaskType TaskID);
FUNC(StatusType, OS_CODE_SLOW) Schedule(void);
FUNC(StatusType, OS_CODE_SLOW) GetTaskID(TaskRefType TaskID);
FUNC(StatusType, OS_CODE_SLOW) GetTaskState(TaskRefType TaskID, TaskStateRefType State);
FUNC(void, OS_CODE_SLOW) EnableAllInterrupts(void);
FUNC(void, OS_CODE_SLOW) DisableAllInterrupts(void);
FUNC(void, OS_CODE_SLOW) ResumeAllInterrupts(void);
FUNC(void, OS_CODE_SLOW) SuspendAllInterrupts(void);
FUNC(void, OS_CODE_SLOW) ResumeOSInterrupts(void);
FUNC(void, OS_CODE_SLOW) SuspendOSInterrupts(void);
FUNC(StatusType, OS_CODE_SLOW) GetResource(ResourceType ResID);
FUNC(StatusType, OS_CODE_SLOW) ReleaseResource(ResourceType ResID);
FUNC(StatusType, OS_CODE_SLOW) SetEvent(TaskType TaskID, EventMaskType Mask);
FUNC(StatusType, OS_CODE_SLOW) ClearEvent(EventMaskType Mask);
FUNC(StatusType, OS_CODE_SLOW) GetEvent(TaskType TaskID, EventMaskRefType Event);
FUNC(StatusType, OS_CODE_SLOW) WaitEvent(EventMaskType Mask);
FUNC(StatusType, OS_CODE_SLOW) GetAlarmBase(AlarmType AlarmID, AlarmBaseRefType Info);
FUNC(StatusType, OS_CODE_SLOW) GetAlarm(AlarmType AlarmID, TickRefType Tick);
FUNC(StatusType, OS_CODE_SLOW) SetRelAlarm(AlarmType AlarmID, TickType increment, TickType cycle);
FUNC(StatusType, OS_CODE_SLOW) SetAbsAlarm(AlarmType AlarmID, TickType start, TickType cycle);
FUNC(StatusType, OS_CODE_SLOW) CancelAlarm(AlarmType AlarmID);
FUNC(AppModeType, OS_CODE_SLOW) GetActiveApplicationMode(void);
FUNC(void, OS_CODE_SLOW) StartOS(AppModeType Mode);
FUNC(void, OS_CODE_SLOW) ShutdownOS(StatusType Error);
FUNC(void, OS_CODE_SLOW) ErrorHook(StatusType Error);
FUNC(void, OS_CODE_SLOW) PreTaskHook(void);
FUNC(void, OS_CODE_SLOW) PostTaskHook(void);
FUNC(void, OS_CODE_SLOW) StartupHook(void);
FUNC(void, OS_CODE_SLOW) ShutdownHook(StatusType Error);

/* AUTOSAR */
FUNC(ApplicationType, OS_CODE_SLOW) GetApplicationID(void);
FUNC(ApplicationType, OS_CODE_SLOW) GetCurrentApplicationID(void);
FUNC(ISRType, OS_CODE_SLOW) GetISRID(void);

FUNC(StatusType, OS_CODE_SLOW) CallTrustedFunction(TrustedFunctionIndexType FunctionIndex, TrustedFunctionParameterRefType FunctionParams);
FUNC(AccessType, OS_CODE_SLOW) CheckISRMemoryAccess(ISRType ISRID, MemoryStartAddressType Address, MemorySizeType Size);

FUNC(AccessType, OS_CODE_SLOW) CheckTaskMemoryAccess(TaskType TaskID, MemoryStartAddressType Address, MemorySizeType Size);
FUNC(ObjectAccessType, OS_CODE_SLOW) CheckObjectAccess(ApplicationType ApplID, ObjectTypeType ObjectType, P2VAR(void, AUTOMATIC, OS_APPL_DATA) Obj);
FUNC(ApplicationType, OS_CODE_SLOW) CheckObjectOwnership(ObjectTypeType ObjectType, P2VAR(void, AUTOMATIC, OS_APPL_DATA) Obj);

FUNC(StatusType, OS_CODE_SLOW) StartScheduleTableAbs(ScheduleTableType ScheduleTableID, TickType Start);
FUNC(StatusType, OS_CODE_SLOW) StartScheduleTableRel(ScheduleTableType ScheduleTableID, TickType Offset);
FUNC(StatusType, OS_CODE_SLOW) StopScheduleTable(ScheduleTableType ScheduleTableID);
FUNC(StatusType, OS_CODE_SLOW) NextScheduleTable(ScheduleTableType ScheduleTableID_From, ScheduleTableType ScheduleTableID_To);
FUNC(StatusType, OS_CODE_SLOW) StartScheduleTableSynchron(ScheduleTableType ScheduleTableID);
FUNC(StatusType, OS_CODE_SLOW) SyncScheduleTable(ScheduleTableType ScheduleTableID, TickType Value);
FUNC(StatusType, OS_CODE_SLOW) SetScheduleTableAsync(ScheduleTableType ScheduleTableID);
FUNC(StatusType, OS_CODE_SLOW) GetScheduleTableStatus(ScheduleTableType ScheduleTableID, ScheduleTableStatusRefType ScheduleStatus);

FUNC(StatusType, OS_CODE_SLOW) IncrementCounter(CounterType CounterID);
FUNC(StatusType, OS_CODE_SLOW) GetCounterValue(CounterType CounterID, TickRefType Value);
FUNC(StatusType, OS_CODE_SLOW) GetElapsedValue(CounterType CounterID, TickRefType Value, TickRefType ElapsedValue);

FUNC(StatusType, OS_CODE_SLOW) TerminateApplication(ApplicationType Application, RestartType RestartOption);
FUNC(StatusType, OS_CODE_SLOW) AllowAccess(void);
FUNC(StatusType, OS_CODE_SLOW) GetApplicationState(ApplicationType Application, ApplicationStateRefType Value);
FUNC(uint32, OS_CODE_SLOW) GetNumberOfActivatedCores(void);
FUNC(CoreIdType, OS_CODE_SLOW) GetCoreID(void);
FUNC(void, OS_CODE_SLOW) StartCore(CoreIdType CoreID, P2VAR(StatusType, AUTOMATIC, OS_APPL_DATA) Status);
FUNC(void, OS_CODE_SLOW) StartNonAutosarCore(CoreIdType CoreID, P2VAR(StatusType, AUTOMATIC, OS_APPL_DATA) Status);
FUNC(StatusType, OS_CODE_SLOW) GetSpinlock(SpinlockIdType SpinlockId);
FUNC(StatusType, OS_CODE_SLOW) ReleaseSpinlock(SpinlockIdType SpinlockId);
FUNC(StatusType, OS_CODE_SLOW) TryToGetSpinlock(SpinlockIdType SpinlockId, P2VAR(TryToGetSpinlockType, AUTOMATIC, OS_APPL_DATA) Success);
FUNC(void, OS_CODE_SLOW) ShutdownAllCores(StatusType Error);
FUNC(StatusType, OS_CODE_SLOW) ControlIdle(CoreIdType CoreID, IdleModeType IdleMode);

FUNC(StatusType, OS_CODE_SLOW) ReadPeripheral8(AreaIdType Area, P2CONST(uint8, AUTOMATIC, OS_APPL_DATA) Address, P2VAR(uint8, AUTOMATIC, OS_APPL_DATA) ReadValue);
FUNC(StatusType, OS_CODE_SLOW) ReadPeripheral16(AreaIdType Area, P2CONST(uint16, AUTOMATIC, OS_APPL_DATA) Address, P2VAR(uint16, AUTOMATIC, OS_APPL_DATA) ReadValue);
FUNC(StatusType, OS_CODE_SLOW) ReadPeripheral32(AreaIdType Area, P2CONST(uint32, AUTOMATIC, OS_APPL_DATA) Address, P2VAR(uint32, AUTOMATIC, OS_APPL_DATA) ReadValue);
FUNC(StatusType, OS_CODE_SLOW) WritePeripheral8(AreaIdType Area, P2CONST(uint8, AUTOMATIC, OS_APPL_DATA) Address, uint8 WriteValue);
FUNC(StatusType, OS_CODE_SLOW) WritePeripheral16(AreaIdType Area, P2CONST(uint16, AUTOMATIC, OS_APPL_DATA) Address, uint16 WriteValue);
FUNC(StatusType, OS_CODE_SLOW) WritePeripheral32(AreaIdType Area, P2CONST(uint32, AUTOMATIC, OS_APPL_DATA) Address, uint32 WriteValue);
FUNC(StatusType, OS_CODE_SLOW) ModifyPeripheral8(AreaIdType Area, P2VAR(uint8, AUTOMATIC, OS_APPL_DATA) Address, uint8 Clearmask, uint8 Setmask);
FUNC(StatusType, OS_CODE_SLOW) ModifyPeripheral16(AreaIdType Area, P2VAR(uint8, AUTOMATIC, OS_APPL_DATA) Address, uint8 Clearmask, uint8 Setmask);
FUNC(StatusType, OS_CODE_SLOW) ModifyPeripheral32(AreaIdType Area, P2VAR(uint8, AUTOMATIC, OS_APPL_DATA) Address, uint8 Clearmask, uint8 Setmask);

FUNC(StatusType, OS_CODE_SLOW) EnableInterruptSource(ISRType ISRID, boolean ClearPending);
FUNC(StatusType, OS_CODE_SLOW) DisableInterruptSource(ISRType ISRID);
FUNC(StatusType, OS_CODE_SLOW) ClearPendingInterrupt(ISRType ISRID);
FUNC(StatusType, OS_CODE_SLOW) ClearPendingInterrupt(ISRType ISRID);
FUNC(void, OS_CODE_SLOW) ActivateTaskAsyn(TaskType id);
FUNC(void, OS_CODE_SLOW) SetEventAsyn(TaskType id, EventMaskType m);

#ifdef __cplusplus
}
#endif
#endif /*End of Os.h*/
