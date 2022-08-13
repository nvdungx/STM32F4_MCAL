/*******************************************************************************
* File:         Os.h
* Revision:     1.0.0
* Author:       Dung van Nguyen
* Date:         30.08.2019
* Description:  Stub header file for Os
*******************************************************************************/

#ifndef OS_H
#define OS_H
/*******************************************************************************
Includes
*******************************************************************************/
#include "Std_Types.h"

/*******************************************************************************
Macro definitions
*******************************************************************************/

/*******************************************************************************
Typedef definitions
*******************************************************************************/
#ifndef STATUSTYPEDEFINED
#define STATUSTYPEDEFINED
typedef uint8 StatusType;
#endif
typedef uint16 CounterType;

/*! Data type to measure time. */
typedef uint32    Os_TickType;

/*! This data type represents count values in ticks. */
typedef Os_TickType TickType;


/*! This data type points to the data type TickType. */
typedef TickType* TickRefType;

StatusType GetCounterValue (CounterType CounterID, uint32 * Value);

#endif /*End of Os.h*/
