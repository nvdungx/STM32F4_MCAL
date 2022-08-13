/*******************************************************************************
* File:         Det.h
* Revision:     1.0.0
* Author:       Dung van Nguyen
* Date:         04.09.2019
* Description:  Default Error Tracer stub file.
*******************************************************************************/

#ifndef DET_H
#define DET_H
/*******************************************************************************
Includes
*******************************************************************************/
#include "Std_Types.h"

/*******************************************************************************
Macro definitions
*******************************************************************************/
#define CAN_E_PARAM_POINTER       0x01U
#define CAN_E_PARAM_HANDLE        0x02U
#define CAN_E_PARAM_DATA_LENGTH   0x03U
#define CAN_E_PARAM_CONTROLLER    0x04U
#define CAN_E_UNINIT              0x05U
#define CAN_E_TRANSITION          0x06U
#define CAN_E_PARAM_BAUDRATE      0x07U
#define CAN_E_ICOM_CONFIG_INVALID 0x08U
#define CAN_E_INIT_FAILED         0x09U

/*******************************************************************************
Typedef definitions
*******************************************************************************/
Std_ReturnType Det_ReportError(uint8 module_id, uint8 module_instance, uint8 service_id, uint8 det_error);
Std_ReturnType Det_ReportRuntimeError(void);

#endif /*End of Det.h*/
