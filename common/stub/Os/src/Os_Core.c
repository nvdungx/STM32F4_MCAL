#include "Os_Core.h"

void OSThreadStart(OsThread *me, OSThreadHandler threadHandler, void *stkSto, uint32 stkSize)
{
  uint32 *sp = (uint32 *)((((uint32)stkSto + stkSize) / 8) * 8);
  
}