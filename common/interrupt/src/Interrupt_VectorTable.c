/*******************************************************************************
* File:         Interrupt_VectorTable.c
* Revision:
* Author:
* Date:         02.08.2019
* Description:  interrupt vector table definition
*******************************************************************************/
#include "Interrupt_VectorTable.h"

/* can use __attribute__((section(..))) for functions
  or variables as an alternative to #pragma arm section. */
/* Place table in separate section */
// #pragma arm section rodata="vectortable_area"
// __attribute__((section(".vectortable_area")))
ExecFuncPtr exception_table[] __attribute__((section(".vectortable_area"))) =
{
  /* This initial stack pointer address section is define in link file */
  (ExecFuncPtr)(&_USER_STACK),
  /* Initial PC, set to entry point */
  __user_reset_init,
  NMIException,
  HardFaultException,
  MemManageException,
  BusFaultException,
  UsageFaultException,
  dummy_handler, /* Reserved */
  dummy_handler, /* Reserved */
  dummy_handler, /* Reserved */
  dummy_handler, /* Reserved */
  SVCHandler,
  DebugMonitor,
  dummy_handler, /* Reserved */
  PendSVC,
  SysTickHandler,
  #ifdef PVD
  PVD_Interrupt,
  #endif
  #ifdef AMP_STAMP
  AMP_STAMP_Interrupt,
  #endif
  #ifdef RTC_WKUP
  RTC_WKUP_Interrupt,
  #endif
  #ifdef FLASH
  FLASH_Interrupt,
  #endif
  #ifdef RCC
  RCC_Interrupt,
  #endif
  #ifdef EXTI0
  EXTI0_Interrupt,
  #endif
  #ifdef EXTI1
  EXTI1_Interrupt,
  #endif
  #ifdef EXTI2
  EXTI2_Interrupt,
  #endif
  #ifdef EXTI3
  EXTI3_Interrupt,
  #endif
  #ifdef EXTI4
  EXTI4_Interrupt,
  #endif
  #ifdef DMA1_Stream0
  DMA1_Stream0_Interrupt,
  #endif
  #ifdef DMA1_Stream1
  DMA1_Stream1_Interrupt,
  #endif
  #ifdef DMA1_Stream2
  DMA1_Stream2_Interrupt,
  #endif
  #ifdef DMA1_Stream3
  DMA1_Stream3_Interrupt,
  #endif
  #ifdef DMA1_Stream4
  DMA1_Stream4_Interrupt,
  #endif
  #ifdef DMA1_Stream5
  DMA1_Stream5_Interrupt,
  #endif
  #ifdef DMA1_Stream6
  DMA1_Stream6_Interrupt,
  #endif
  #ifdef ADC
  ADC_Interrupt,
  #endif
  #ifdef CAN1_TX
  CAN1_TX_Interrupt,
  #endif
  #ifdef CAN1_RX0
  CAN1_RX0_Interrupt,
  #endif
  #ifdef CAN1_RX1
  CAN1_RX1_Interrupt,
  #endif
  #ifdef CAN1_SCE
  CAN1_SCE_Interrupt,
  #endif
  #ifdef EXTI9_5
  EXTI9_5_Interrupt,
  #endif
  #ifdef TIM1_BRK_TIM9
  TIM1_BRK_TIM9_Interrupt,
  #endif
  #ifdef TIM1_UP_TIM10
  TIM1_UP_TIM10_Interrupt,
  #endif
  #ifdef TIM1_TRG_COM_TIM11
  TIM1_TRG_COM_TIM11_Interrupt,
  #endif
  #ifdef TIM1_CC
  TIM1_CC_Interrupt,
  #endif
  #ifdef TIM2
  TIM2_Interrupt,
  #endif
  #ifdef TIM3
  TIM3_Interrupt,
  #endif
  #ifdef TIM4
  TIM4_Interrupt,
  #endif
  #ifdef I2C1_EV
  I2C1_EV_Interrupt,
  #endif
  #ifdef I2C1_ER
  I2C1_ER_Interrupt,
  #endif
  #ifdef I2C2_EV
  I2C2_EV_Interrupt,
  #endif
  #ifdef I2C2_ER
  I2C2_ER_Interrupt,
  #endif
  #ifdef SPI1
  SPI1_Interrupt,
  #endif
  #ifdef SPI2
  SPI2_Interrupt,
  #endif
  #ifdef USART1
  USART1_Interrupt,
  #endif
  #ifdef USART2
  USART2_Interrupt,
  #endif
  #ifdef USART3
  USART3_Interrupt,
  #endif
  #ifdef EXTI15_10
  EXTI15_10_Interrupt,
  #endif
  #ifdef RTC_Alarm
  RTC_Alarm_Interrupt,
  #endif
  #ifdef OTG_FS_WKUP
  OTG_FS_WKUP_Interrupt,
  #endif
  #ifdef TIM8_BRK_TIM12
  TIM8_BRK_TIM12_Interrupt,
  #endif
  #ifdef TIM8_UP_TIM13
  TIM8_UP_TIM13_Interrupt,
  #endif
  #ifdef TIM8_TRG_COM_TIM14
  TIM8_TRG_COM_TIM14_Interrupt,
  #endif
  #ifdef TIM8_CC
  TIM8_CC_Interrupt,
  #endif
  #ifdef DMA1_Stream7
  DMA1_Stream7_Interrupt,
  #endif
  #ifdef FSMC
  FSMC_Interrupt,
  #endif
  #ifdef SDIO
  SDIO_Interrupt,
  #endif
  #ifdef TIM5
  TIM5_Interrupt,
  #endif
  #ifdef SPI3
  SPI3_Interrupt,
  #endif
  #ifdef UART4
  UART4_Interrupt,
  #endif
  #ifdef UART5
  UART5_Interrupt,
  #endif
  #ifdef TIM6_DAC
  TIM6_DAC_Interrupt,
  #endif
  #ifdef TIM7
  TIM7_Interrupt,
  #endif
  #ifdef DMA2_Stream0
  DMA2_Stream0_Interrupt,
  #endif
  #ifdef DMA2_Stream1
  DMA2_Stream1_Interrupt,
  #endif
  #ifdef DMA2_Stream2
  DMA2_Stream2_Interrupt,
  #endif
  #ifdef DMA2_Stream3
  DMA2_Stream3_Interrupt,
  #endif
  #ifdef DMA2_Stream4
  DMA2_Stream4_Interrupt,
  #endif
  #ifdef ETH
  ETH_Interrupt,
  #endif
  #ifdef ETH_WKUP
  ETH_WKUP_Interrupt,
  #endif
  #ifdef CAN2_TX
  CAN2_TX_Interrupt,
  #endif
  #ifdef CAN2_RX0
  CAN2_RX0_Interrupt,
  #endif
  #ifdef CAN2_RX1
  CAN2_RX1_Interrupt,
  #endif
  #ifdef CAN2_SCE
  CAN2_SCE_Interrupt,
  #endif
  #ifdef OTG_FS
  OTG_FS_Interrupt,
  #endif
  #ifdef DMA2_Stream5
  DMA2_Stream5_Interrupt,
  #endif
  #ifdef DMA2_Stream6
  DMA2_Stream6_Interrupt,
  #endif
  #ifdef DMA2_Stream7
  DMA2_Stream7_Interrupt,
  #endif
  #ifdef USART6
  USART6_Interrupt,
  #endif
  #ifdef I2C3_EV
  I2C3_EV_Interrupt,
  #endif
  #ifdef I2C3_ER
  I2C3_ER_Interrupt,
  #endif
  #ifdef OTG_HS_EP1_OUT
  OTG_HS_EP1_OUT_Interrupt,
  #endif
  #ifdef OTG_HS_EP1_IN
  OTG_HS_EP1_IN_Interrupt,
  #endif
  #ifdef OTG_HS_WKUP
  OTG_HS_WKUP_Interrupt,
  #endif
  #ifdef OTG_HS
  OTG_HS_Interrupt,
  #endif
  #ifdef DCMI
  DCMI_Interrupt,
  #endif
  #ifdef CRYP
  CRYP_Interrupt,
  #endif
  #ifdef HASH_RNG
  HASH_RNG_Interrupt,
  #endif
  #ifdef FPU
  FPU_Interrupt
  #endif
};
// #pragma arm section
