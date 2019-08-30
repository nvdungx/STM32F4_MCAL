#include "Interrupt.h"

void NMIException(void)
{
  WFI;
}
void HardFaultException(void)
{
  WFI;
}
void MemManageException(void)
{
  WFI;
}
void BusFaultException(void)
{
  WFI;
}
void UsageFaultException(void)
{
  WFI;
}
void SVCHandler(void)
{
  WFI;
}
void DebugMonitor(void)
{
  WFI;
}
void PendSVC(void)
{
  WFI;
}
void SysTickHandler(void)
{
  WFI;
}
void dummy_handler(void)
{
  WFI;
}
