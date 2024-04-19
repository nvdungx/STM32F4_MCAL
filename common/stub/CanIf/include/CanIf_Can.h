#ifndef __CANIF_CAN_H__
#define __CANIF_CAN_H__

void CanIf_ControllerBusOff(void);
void CanIf_ControllerModeIndication(void);
void CanIf_RxIndication(void);
void CanIf_TxConfirmation(void);
void CanIf_CurrentIcomConfiguration(void);

#endif // __CANIF_CAN_H__