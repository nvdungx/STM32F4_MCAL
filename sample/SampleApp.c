#include "SampleApp.h"
#include "Can.h"
#include "Can_PBCfg.h"
#include "Can_Cfg.h"

typedef struct List_STag
{
  struct List_STag *_pre;
  void *data_ptr;
  struct List_STag *_next;
} List;

uint8 arr[4] = {1, 2, 3, 4};
List mylist =
{
  NULL_PTR,
  arr,
  NULL_PTR
};
Std_ReturnType add_list(List* ele);
#define RCC_CR (*(volatile uint32 *)0x40023800)
#define RCC_PLLCFGR (*(volatile uint32 *)0x40023804)
#define RCC_CFGR (*(volatile uint32 *)0x40023808)
#define RCC_APB1ENR (*(volatile uint32 *)0x40023840)

int main(void)
{
  // config clock

  // enable CAN module
  RCC_APB1ENR |= (3 << 25);
  Can_Init(&CanConfig);

  while(1)
  {

  }
  return 0;
}

Std_ReturnType add_list(List* ele)
{
  mylist._next = ele;
  ele->_pre = &mylist;
  return E_OK;
}

void System_Init(void)
{
  arr[0] = 0xFF;
}
