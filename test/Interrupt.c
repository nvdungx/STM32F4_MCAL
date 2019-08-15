#include "Interrupt.h"

void NMIException(void)
{
  __asm("wfi");
}
void HardFaultException(void)
{
  __asm("wfi");
}
void MemManageException(void)
{
  __asm("wfi");
}
void BusFaultException(void)
{
  __asm("wfi");
}
void UsageFaultException(void)
{
  __asm("wfi");
}
void SVCHandler(void)
{
  __asm("wfi");
}
void DebugMonitor(void)
{
  __asm("wfi");
}
void PendSVC(void)
{
  __asm("wfi");
}
void SysTickHandler(void)
{
  __asm("wfi");
}
void dummy_handler(void)
{
  static unsigned char dummy_var = 0;
  dummy_var++;
  if(dummy_var == 100)
  {
    dummy_var = 0;
  }
}
