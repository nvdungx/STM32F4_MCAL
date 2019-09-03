#ifndef _INTERRUPT_H_
#define _INTERRUPT_H_

#include "Compiler.h"
#include "Interrupt_VectorTable.h"

void NMIException(void);
void HardFaultException(void);
void MemManageException(void);
void BusFaultException(void);
void UsageFaultException(void);
void SVCHandler(void);
void DebugMonitor(void);
void PendSVC(void);
void SysTickHandler(void);
void dummy_handler(void);

#endif
