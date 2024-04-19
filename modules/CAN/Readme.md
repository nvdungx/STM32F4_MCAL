# AUTOSAR MCAL CAN Driver
CAN hardware unit:
- 2 CAN controller.
- support 2.0A, 2.0B(11 bit or 29 bit arbitration identifier)
- CAN1: Master bxCAN, CAN2: Slave bxCAN, 512-byte SRAM memory
- Bit rates up to 1 Mbit/s
- Support TTCAN
1. Transmission:
  - 3 tx mailbox
  - configurable priority
  - timestamp
2. Reception:
  - 2 rx FIFO with 3 stages
  - 28 filter bank shared between 2 CAN
  - identifier list
  - configurable FIFO overrun
  - timestamp
3. TTCAN:
  - Enable/Disable automatic retransmission mode
  - 16-bit free running timer
  - Time Stamp sent in last two data bytes
4. Management:
  - Maskable interrupts
  - Software-efficient mailbox mapping

bxCAN has three main operating modes: initialization, normal and Sleep<br/>

map software state to bxCAN hw state<br/>
CAN_UNINIT:<br/>
  CAN_CS_UNINIT, Sleep<br/>
CAN_INIT:<br/>
  CAN_CS_START, normal<br/>
  CAN_CS_STOPPED, initialization<br/>
  CAN_CS_SLEEP, Sleep<br/>