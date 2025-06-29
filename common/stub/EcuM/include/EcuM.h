/*******************************************************************************
* File:         EcuM.h
* Revision:     1.0.0
* Author:       Dung van Nguyen
* Date:         30.08.2019
* Description:  Stub Ecu Manage header
*******************************************************************************/

#ifndef ECUM_H
#define ECUM_H
/*******************************************************************************
Includes
*******************************************************************************/
#include "Std_Types.h"
/*******************************************************************************
Macro definitions
*******************************************************************************/
#define ECUM_WKSOURCE_POWER             ((uint32)1)
#define ECUM_WKSOURCE_RESET             ((uint32)1 << 1)
#define ECUM_WKSOURCE_INTERNAL_RESET    ((uint32)1 << 2)
#define ECUM_WKSOURCE_INTERNAL_WDG      ((uint32)1 << 3)
#define ECUM_WKSOURCE_EXTERNAL_WDG      ((uint32)1 << 4)
/*******************************************************************************
Typedef definitions
*******************************************************************************/
typedef uint32 EcuM_WakeupSourceType;

void EcuM_SetWakeupEvent(EcuM_WakeupSourceType sources);

#endif /*End of EcuM.h*/
