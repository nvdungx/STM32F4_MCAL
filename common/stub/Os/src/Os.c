/*******************************************************************************
 * COPYRIGHT
 * -----------------------------------------------------------------------------
 * Copyright (c) 2022 by <<>>. All rights reserved.
 * -----------------------------------------------------------------------------
 * FILE DESCRIPTION
 *  File:         Os.c
 *  Component:    <<>>
 *  Module:       <<>>
 *  Generator:    <<>>
 *  Description:  Stub source file for Os
 * -----------------------------------------------------------------------------
 * REVISION HISTORY
 * -----------------------------------------------------------------------------
 * Version   Date        Author  Description
 * -----------------------------------------------------------------------------
 * 01.00.00  13/08/2022  Dungnv  Initial version
 * 
*******************************************************************************/

#include "Os_LCfg.h"
#include "Os.h"
uint16 TotalNumberOfCores = 1;

FUNC(StatusType, OS_CODE_SLOW) ActivateTask(VAR(TaskType, AUTOMATIC) TaskID)
{

}

FUNC(StatusType, OS_CODE_SLOW) TerminateTask(VAR(TaskType, AUTOMATIC) TaskID)
{

}

FUNC(StatusType, OS_CODE_SLOW) ChainTask(VAR(TaskType, AUTOMATIC) TaskID)
{

}

FUNC(StatusType, OS_CODE_SLOW) Schedule(void)
{

}

FUNC(StatusType, OS_CODE_SLOW) GetTaskID(VAR(TaskRefType, AUTOMATIC) TaskID)
{

}

FUNC(StatusType, OS_CODE_SLOW) GetTaskState(VAR(TaskRefType, AUTOMATIC) TaskID, VAR(TaskStateRefType, AUTOMATIC) State)
{

}

FUNC(void, OS_CODE_SLOW) StartOS(VAR(AppModeType, AUTOMATIC) Mode)
{

}

FUNC(void, OS_CODE_SLOW) ShutdownOS(VAR(StatusType, AUTOMATIC) Error)
{

}
