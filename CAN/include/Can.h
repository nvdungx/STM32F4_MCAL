/*******************************************************************************
* File:         Can.h
* Revision:
* Author:
* Date:         02.08.2019
* Description:  declaration of CAN module API
*******************************************************************************/

#ifndef CAN_H
#define CAN_H
/*******************************************************************************
Includes
*******************************************************************************/
#include "ComStack_Types.h"
#include "Can_GeneralTypes.h"
#include "Can_Cfg.h"

/*******************************************************************************
Macro definitions
*******************************************************************************/

#define CAN_SID_GETVERSIONINFO    0x07U
#define CAN_SID_INIT              0x00U
#define CAN_SID_DEINIT            0x10U
#define CAN_SID_SETBAUDRATE       0x0FU

/* Temporary >> shall move to DET module instead */
#define CAN_E_PARAM_POINTER       0x01U
#define CAN_E_PARAM_HANDLE        0x02U
#define CAN_E_PARAM_DATA_LENGTH   0x03U
#define CAN_E_PARAM_CONTROLLER    0x04U
#define CAN_E_UNINIT              0x05U
#define CAN_E_TRANSITION          0x06U
#define CAN_E_PARAM_BAUDRATE      0x07U
#define CAN_E_ICOM_CONFIG_INVALID 0x08U
#define CAN_E_INIT_FAILED         0x09U

/* Temporary >> shall move to DEM module instead */
#define CAN_E_DATALOST            0x01U

/*******************************************************************************
Typedef definitions
*******************************************************************************/




/*******************************************************************************
Global functions
*******************************************************************************/

#endif // CAN_H
