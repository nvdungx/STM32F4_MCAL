# AUTOSAR MCAL CAN Driver
The Can module is part of the lowest layer, performs the hardware access and offers  
a hardware independent API to the upper layer.
The Can module provides services:
- initiating transmissions
- call the callbacks of CANIf(only upper layer module has access to CAN module) for notifying events
- control the behavior and state of CAN controllers

# Acronym
CAN Controller: a CAN controller serves exactly 1 **physical channel(physical interface to access CAN Network)**.  
CAN HW Unit: contain 1 or multiple CAN Controllers of same types and 1 or multiple CAN RAM areas. CAN HW Unit could be on-chip or external, and represent by 1 CAN driver.  
L-PDU: Data Link Protocol Data Unit = Identifier, Data Length, Data(SDU).  
L-SDU: Data Link Service Data Unit, data being transport in PDU.  
DLC: Data Length Code.  
CAN HW Object: a L-PDU buffer inside CAN RAM.  
Hardware Receive Handle(HRH): define and provide(indexes for sw filter/operation) by CAN Driver, represent 1 HW Object.  
Hardware Transmit Handle(HTH): define and provide by CAN Driver, represent 1 or multiple Hw Objects(hardware transmit buffer pool).  
Inner Priority Inversion: transmission of high priority msg is blocked by lower priority which is already available on the hardware transmit object, and is waiting to be transmitted until bus is available. This occur when system use only 1 hardware transmit object.  
Outer Priority Inversion: The problem of outer priority inversion may occur in some CAN implementations. Let us assume that a CAN node wishes to transmit a package of consecutive messages with high priority, which are stored in different message buffers. If the interframe space between these messages on the CAN network is longer than the minimum space defined by the CAN standard, a second node is able to start the transmission of a lower priority message. The minimum interframe space is determined by the Intermission field, which consists of 3 recessive bits  
ICOM: Intelligent Communication Controller  
SPAL: Standard Peripheral Abstraction Layer  

# CAN Driver shall provide functionalities of STM32F407VG MCU and follow requirement AUTOSAR_SWS_CANDriver_4.4.0, AUTOSAR_SWS_BSWGeneral_4.4.0
Reference inputs: LayeredSoftwareArchitecture, SPALGeneral, CANInterface, DET, ECUStateManager, MCU, OS, MemoryMapping, SPIHandler, BSWScheduler, BswDescriptionTemplate, BswModuleList, ISO11898, ISO/IEC 7498-1, CiA601-2

Functional Requirements:  
- Configuration (which elements of the module need to be configurable)  
- Initialization  
- Normal Operation  
- Shutdown Operation  
- Fault Operation  
- ...
Non-Functional Requirements:  
- Timing Requirements  
- Resource Usage  
- Usability  
- Output for other WPs (e.g. Description Templates, Tooling,...)  
- ...

The Basic Extended CAN peripheral, named bxCAN, interfaces the CAN network. It
supports the CAN protocols version 2.0A and B
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

