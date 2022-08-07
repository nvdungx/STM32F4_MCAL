/*******************************************************************************
 * File:         Can_IOCommon.h
 * Revision:     1.0.0
 * Author:       Dung van Nguyen
 * Date:         02.08.2019
 * Description:  define base address and structure of bxCAN Hw STM32F407VG
 *******************************************************************************/

#ifndef CAN_IOCOMMON_H
#define CAN_IOCOMMON_H

#include "Std_Types.h"
/*
 * Define HW structure map
 */

#ifndef __rw
/* read/write Software can read and write to these bits */
#define __rw volatile
#endif

#ifndef __w
/* write-only Software can only write to this bit.
  Reading the bit returns the reset value */
#define __w volatile
#endif

#ifndef __r
/* read-only Software can only read these bits */
#define __r volatile const
#endif

#ifndef __rc_w1
/* read/clear Software can read as well as clear this bit by writing 1.
  Writing ‘0’ has no effect on the bit value */
#define __rc_w1 volatile
#endif

#ifndef __rc_w0
/* read/clear Software can read as well as clear this bit by writing 0.
  Writing ‘1’ has no effect on the bit value*/
#define __rc_w0 volatile
#endif

#ifndef __rc_r
/* read/clear by read Software can read this bit.
  Reading this bit automatically clears it to ‘0’. Writing ‘0’ has no effect
  on the bit value*/
#define __rc_r volatile
#endif

#ifndef __rs
/* read/set Software can read as well as set this bit.
  Writing ‘0’ has no effect on the bit value.*/
#define __rs volatile
#endif

#ifndef __rt_w
/* read-only write trigger Software can read this bit.
  Writing ‘0’ or ‘1’ triggers an event but has no effect on the bit value*/
#define __rt_w volatile
#endif

#ifndef __t
/* toggle Software can only toggle this bit by writing ‘1’. Writing ‘0’ has no effect*/
#define __t volatile
#endif

#ifndef __res
/* Reserved Reserved bit, must be kept at reset value */
#define __res const
#endif

#ifndef SET_BIT32
#define SET_BIT32(reg, x) ((uint32)reg | (uint32)(1 << x))
#endif

#ifndef CLEAR_BIT32
#define CLEAR_BIT32(reg, x) ((uint32)reg & (~(uint32)(1 << x)))
#endif

/* Master Control and Status registers */
typedef struct Can_CtrlSts_STag
{
  /* Master control register */
  union
  {
    __rw uint32 val;
    struct
    {
      /* Initialization request */
      __rw uint32 INRQ : 1;
      /* Sleep mode request */
      __rw uint32 SLEEP : 1;
      /* Transmit FIFO priority */
      __rw uint32 TXFP : 1;
      /* Receive FIFO locked mode */
      __rw uint32 RFLM : 1;
      /*  No automatic retransmission */
      __rw uint32 NART : 1;
      /* Automatic wakeup mode */
      __rw uint32 AWUM : 1;
      /* Automatic bus-off management */
      __rw uint32 ABOM : 1;
      /* Time triggered communication mode */
      __rw uint32 TTCM : 1;
      __res uint32 Reserved : 7;
      /* bxCAN software master reset */
      __rs uint32 RESET : 1;
      /* Debug freeze */
      __rw uint32 DBF : 1;
    };
  } ulMCReg;

  /* Master status register */
  union
  {
    __rw uint32 val;
    struct
    {
      /* Initialization acknowledge */
      __r uint32 INAK : 1;
      /* Sleep acknowledge */
      __r uint32 SLAK : 1;
      /* Error interrupt */
      __rc_w1 uint32 ERRI : 1;
      /* Wakeup interrupt */
      __rc_w1 uint32 WKUI : 1;
      /*  Sleep acknowledge interrupt*/
      __rc_w1 uint32 SLAKI : 1;
      __res uint32 Reserved : 3;
      /* Transmit mode */
      __r uint32 TXM : 1;
      /* Receive mode */
      __r uint32 RXM : 1;
      /* Last sample point */
      __r uint32 SAMP : 1;
      /* CAN Rx signal */
      __r uint32 RX : 1;
    };
  } ulMSReg;

  /* Transmit mailbox status register */
  union
  {
    __rw uint32 val;
    struct
    {
      /* Request completed mailbox 0 */
      __rc_w1 uint32 RQCP0 : 1;
      /* Transmission OK of mailbox 0 */
      __rc_w1 uint32 TXOK0 : 1;
      /* Arbitration lost for mailbox 0 */
      __rc_w1 uint32 ALST0 : 1;
      /* Transmission error of mailbox 0 */
      __rc_w1 uint32 TERR0 : 1;
      __res uint32 Reserved0 : 3;
      /* Abort request for mailbox 0 */
      __rs uint32 ABRQ0 : 1;
      /* Request completed mailbox 1 */
      __rc_w1 uint32 RQCP1 : 1;
      /* Transmission OK of mailbox 1 */
      __rc_w1 uint32 TXOK1 : 1;
      /* Arbitration lost for mailbox 1 */
      __rc_w1 uint32 ALST1 : 1;
      /* Transmission error of mailbox 1 */
      __rc_w1 uint32 TERR1 : 1;
      __res uint32 Reserved1 : 3;
      /* Abort request for mailbox 1 */
      __rs uint32 ABRQ1 : 1;
      /* Request completed mailbox 2 */
      __rc_w1 uint32 RQCP2 : 1;
      /* Transmission OK of mailbox 2 */
      __rc_w1 uint32 TXOK2 : 1;
      /* Arbitration lost for mailbox 2 */
      __rc_w1 uint32 ALST2 : 1;
      /* Transmission error of mailbox 2 */
      __rc_w1 uint32 TERR2 : 1;
      __res uint32 Reserved2 : 3;
      /* Abort request for mailbox 2 */
      __rs uint32 ABRQ2 : 1;
      /* Mailbox code */
      __r uint32 CODE : 2;
      /* Transmit mailbox 0 empty */
      __r uint32 TME0 : 1;
      /* Transmit mailbox 1 empty */
      __r uint32 TME1 : 1;
      /* Transmit mailbox 2 empty */
      __r uint32 TME2 : 1;
      /* Lowest priority flag for mailbox 0 */
      __r uint32 LOW0 : 1;
      /* Lowest priority flag for mailbox 1 */
      __r uint32 LOW1 : 1;
      /* Lowest priority flag for mailbox 2 */
      __r uint32 LOW2 : 1;
    };
  } ulTSReg;

  /* Receive FIFO0 status register */
  union
  {
    __rw uint32 val;
    struct
    {
      /* FIFO 0 message pending */
      __r uint32 FMP0 : 2;
      __res uint32 Reserved : 1;
      /* FIFO 0 full */
      __rc_w1 uint32 FULL0 : 1;
      /* FIFO 0 overrun */
      __rc_w1 uint32 FOVR0 : 1;
      /* Release FIFO 0 output mailbox */
      __rs uint32 RFOM0 : 1;
    };
  } ulRF0Reg;

  /* Receive FIFO1 status register */
  union
  {
    __rw uint32 val;
    struct
    {
      /* FIFO 1 message pending */
      __r uint32 FMP1 : 2;
      __res uint32 Reserved : 1;
      /* FIFO 1 full */
      __rc_w1 uint32 FULL1 : 1;
      /* FIFO 1 overrun */
      __rc_w1 uint32 FOVR1 : 1;
      /* Release FIFO 1 output mailbox */
      __rs uint32 RFOM1 : 1;
    };
  } ulRF1Reg;

  /* Interrupt enable register */
  union
  {
    __rw uint32 val;
    struct
    {
      /* Transmit mailbox empty interrupt enable */
      __rw uint32 TMEIE : 1;
      /* FIFO message pending interrupt enable */
      __rw uint32 FMPIE0 : 1
          /* FIFO full interrupt enable */;
      __rw uint32 FFIE0 : 1;
      /* FIFO overrun interrupt enable */
      __rw uint32 FOVIE0 : 1;
      /* FIFO message pending interrupt enable */
      __rw uint32 FMPIE1 : 1
          /* FIFO full interrupt enable */;
      __rw uint32 FFIE1 : 1;
      /* FIFO overrun interrupt enable */
      __rw uint32 FOVIE1 : 1;
      __res uint32 Reserved0 : 1;
      /* Error warning interrupt enable */
      __rw uint32 EWGIE : 1;
      /* Error passive interrupt enable */
      __rw uint32 EPVIE : 1;
      /* Bus-off interrupt enable */
      __rw uint32 BOFIE : 1;
      /* Last error code interrupt enable */
      __rw uint32 LECIE : 1;
      __res uint32 Reserved1 : 3;
      /* Error interrupt enable */
      __rw uint32 ERRIE : 1;
      /* Wakeup interrupt enable */
      __rw uint32 WKUIE : 1;
      /*  Sleep interrupt enable */
      __rw uint32 SLKIE : 1;
    };
  } ulIEReg;

  /* Error status register */
  union
  {
    __rw uint32 val;
    struct
    {
      /* Error warning flag */
      __r uint32 EWGF : 1;
      /* Error passive flag */
      __r uint32 EPVF : 1;
      /* Bus-off flag */
      __r uint32 BOFF : 1;
      __res uint32 Reserved0 : 1;
      /* Last error code */
      __rw uint32 LEC : 3;
      __res uint32 Reserved1 : 9;
      /* Least significant byte of the 9-bit transmit error counter */
      __r uint32 TEC : 8;
      /* Receive error counter */
      __r uint32 REC : 8;
    };
  } ulESReg;

  /* Bit timing register, configure baudrate */
  union
  {
    __rw uint32 val;
    struct
    {
      /* Baud rate prescaler */
      __rw uint32 BRP : 10;
      __res uint32 Reserved0 : 6;
      /* Time segment 1 */
      __rw uint32 TS1 : 4;
      /* Time segment 2 */
      __rw uint32 TS2 : 3;
      __res uint32 Reserved1 : 1;
      /* Resynchronization jump width */
      __rw uint32 SJW : 2;
      __res uint32 Reserved2 : 4;
      /* Loop back mode (debug) */
      __rw uint32 LBKM : 1;
      /* Silent mode (debug) */
      __rw uint32 SILM : 1;
    };
  } ulBTReg;
} Can_CtrlSts;

/* Transmit mailbox register */
typedef struct Can_TxMbx_STag
{
  /* ID field value, ID type, frame type, TxRequest - TIxR */
  union
  {
    __rw uint32 val;
    struct
    {
      /* Transmit mailbox request */
      __rw uint32 TXRQ : 1;
      /* Remote transmission request */
      __rw uint32 RTR : 1;
      /* Identifier extension */
      __rw uint32 IDE : 1;
      /* 18 LSB Extended identifier */
      __rw uint32 EXID_LSB : 18;
      /* Standard identifier or 11 MSB extended identifier */
      __rw uint32 STID : 11;
    };
  } ulTXIDRQReg;

  /* DLC, TimeStamp - TDTxR */
  union
  {
    __rw uint32 val;
    struct
    {
      /*  Data length code */
      __rw uint32 DLC : 4;
      __res uint32 Reserved0 : 4;
      /* Transmit global time */
      __rw uint32 TGT : 1;
      __res uint32 Reserved1 : 7;
      /* Message time stamp */
      __rw uint32 TIME : 16;
    };
  } ulTXDLCTSReg;

  /* Data low - TDLxR */
  union
  {
    __rw uint32 val;
    __rw uint8 DATA[4];
  } ulTXDATALReg;

  /* Data high - TDHxR */
  union
  {
    __rw uint32 val;
    __rw uint8 DATA[4];
  } ulTXDATAHReg;

} Can_TxMbx;

/* Receive FIFO mailbox register */
typedef struct Can_RxMbx_STag
{
  /* ID field value, ID type, frame type - RIxR */
  union
  {
    __r uint32 val;
    struct
    {
      __res uint32 Reserved : 1;
      /* Remote transmission request */
      __r uint32 RTR : 1;
      /* Identifier extension */
      __r uint32 IDE : 1;
      /* 18 LSB Extended identifier */
      __r uint32 EXID_LSB : 18;
      /* Standard identifier or 11 MSB extended identifier */
      __r uint32 STID : 11;
    };
  } ulRXIDReg;

  /* DLC, Filter match index, TimeStamp - RDTxR */
  union
  {
    __r uint32 val;
    struct
    {
      /*  Data length code */
      __r uint32 DLC : 4;
      __res uint32 Reserved0 : 4;
      /* Filter match index */
      __r uint32 FMI : 8;
      /* Message time stamp */
      __r uint32 TIME : 16;
    };
  } ulRXDLCTSReg;

  /* Receive Data low - RDLxR */
  union
  {
    __r uint32 val;
    __r uint8 DATA[4];
  } ulRXDATALReg;

  /* Receive Data high - RDHxR */
  union
  {
    __r uint32 val;
    __r uint8 DATA[4];
  } ulRXDATAHReg;
} Can_RxMbx;

/* Receive rule register */
typedef struct Can_Filter_STag
{
  /* filter master register */
  union
  {
    __rw uint32 val;
    struct
    {
      /* Filter init mode */
      __rw uint32 FINIT : 1;
      __res uint32 Reserved : 7;
      /*  CAN2 start bank */
      __rw uint32 CAN2SB : 6;
    };
  } ulFMReg;

  /* filter mode register */
  __rw uint32 ulFM1Reg;

  /* dummy address value */
  __res uint32 dummy0;

  /* filter scale register */
  __rw uint32 ulFS1Reg;

  /* dummy address value */
  __res uint32 dummy1;

  /* filter FIFO assignment register */
  __rw uint32 ulFFA1Reg;

  /* dummy address value */
  __res uint32 dummy2;

  /* filter activation register */
  __rw uint32 ulFA1Reg;

  /* dummy address value */
  __res uint32 dummy3[8];

  /* Filter bank i register x */
  __rw uint32 ulFReg[28][2];
} Can_Filter;

/*
 * Define address of HW
 */
/* Table 1. STM32F40x and STM32F41x register boundary addresses */
/* 0x4000 6400 - 0x4000 67FF */
#define CAN1_BASEADDR 0x40006400UL
/* 0x4000 6800 - 0x4000 6BFF */
#define CAN2_BASEADDR 0x40006800UL

#define CAN1_CtrlSts ((volatile Can_CtrlSts *)(CAN1_BASEADDR + 0UL))
#define CAN2_CtrlSts ((volatile Can_CtrlSts *)(CAN2_BASEADDR + 0UL))

#define CAN1_TxMbx0 ((volatile Can_TxMbx *)(CAN1_BASEADDR + 0x180UL))
#define CAN1_TxMbx1 ((volatile Can_TxMbx *)(CAN1_BASEADDR + 0x190UL))
#define CAN1_TxMbx2 ((volatile Can_TxMbx *)(CAN1_BASEADDR + 0x1A0UL))
#define CAN2_TxMbx0 ((volatile Can_TxMbx *)(CAN2_BASEADDR + 0x180UL))
#define CAN2_TxMbx1 ((volatile Can_TxMbx *)(CAN2_BASEADDR + 0x190UL))
#define CAN2_TxMbx2 ((volatile Can_TxMbx *)(CAN2_BASEADDR + 0x1A0UL))

#define CAN1_RxMbx0 ((volatile Can_RxMbx *)(CAN1_BASEADDR + 0x1B0UL))
#define CAN1_RxMbx1 ((volatile Can_RxMbx *)(CAN1_BASEADDR + 0x1C0UL))
#define CAN2_RxMbx0 ((volatile Can_RxMbx *)(CAN2_BASEADDR + 0x1B0UL))
#define CAN2_RxMbx1 ((volatile Can_RxMbx *)(CAN2_BASEADDR + 0x1C0UL))

/* 28 filter banks shared between CAN1 and CAN2 */
#define CAN_ReceiveRule ((volatile Can_Filter *)(CAN1_BASEADDR + 0x200UL))

/* data structure to access CAN controller register */
typedef struct CanCtrlrHwRegType_STag
{
  volatile Can_CtrlSts * const CtrlSts;
  volatile Can_TxMbx * const TxMbx[3];
  volatile Can_RxMbx * const RxMbx[2];
  volatile Can_Filter * const Filter;
} CanCtrlrHwRegType;

#endif /*End of Can_IOCommon.h*/
