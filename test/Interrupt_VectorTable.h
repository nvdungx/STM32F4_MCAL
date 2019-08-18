#ifndef _INTERRUPT_VECTORTABLE_H_
#define _INTERRUPT_VECTORTABLE_H_

typedef void(* const ExecFuncPtr)(void);

extern void NMIException(void);
extern void HardFaultException(void);
extern void MemManageException(void);
extern void BusFaultException(void);
extern void UsageFaultException(void);
extern void SVCHandler(void);
extern void DebugMonitor(void);
extern void PendSVC(void);
extern void SysTickHandler(void);
extern void dummy_handler(void);

extern ExecFuncPtr exception_table[];

extern unsigned int const __StackTop;
extern void __user_reset_init(void);

#endif
