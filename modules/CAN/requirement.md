# **5.2 Driver Services**
OK: [SWS_Can_00237] ⌈ The Can module shall not transmit messages triggered by
remote transmission requests.⌋  
OK: [SWS_Can_00236] ⌈ The Can module shall initialize the CAN HW to ignore any
remote transmission requests.⌋  
OK: [SWS_Can_00238] ⌈ If the CAN controller is on-chip, the Can module shall not use
any service of other drivers.⌋  
OK: [SWS_Can_00239] ⌈ The function Can_Init shall initialize all on-chip hardware
resources that are used by the CAN controller. The only exception to this is the digital
I/O pin configuration (of pins used by CAN), which is done by the port driver.⌋  
OK: [SWS_Can_00240] ⌈ The Mcu module (SPAL see [8]) shall configure register
settings that are ‘shared’ with other modules.⌋  
NA: [SWS_Can_00242] ⌈ If an off-chip CAN controller is used3, the Can module shall use
services of other MCAL drivers (e.g. SPI).⌋  
NA: [SWS_Can_00244] ⌈ The Can module shall use the synchronous APIs of the
underlying MCAL drivers and shall not provide callback functions that can be called
by the MCAL drivers.⌋  

# **5.3 System Services**
OK: [SWS_Can_00280] ⌈ In special hardware cases, the Can module shall poll for events of the hardware.⌋  
OK: [SWS_Can_00281] ⌈ The Can module shall use the OsCounter provided by the
system service for timeout detection in case the hardware does not react in the
expected time (hardware malfunction) to prevent endless loops.⌋ (using OsCounter for timeout in case of hw status checking, timeout has to be smaller than CAN main function trigger period)  

# **5.4 Can module Users**
OK: [SWS_Can_00058] ⌈ The Can module interacts among other modules (eg. Default
Error Tracer (DET), Ecu State Manager (ECUM)) with the CanIf module in a direct
way. This document never specifies the actual origin of a request or the actual
destination of a notification. The driver only sees the CanIf module as origin and
destination.⌋  

# **5.5 File structure**
OK: [SWS_Can_00436] ⌈ Can_GeneralTypes.h shall contain all types and constants that
are shared among the AUTOSAR CAN modules Can, CanIf and CanTrcv.⌋ (common/stub/CanGeneral/include/Can_GeneralTypes.h)  

# **7 Functional specification**
OK: [SWS_Can_00033] ⌈ The Can module shall implement the interrupt service routines
for all CAN Hardware Unit interrupts that are needed. ⌋  
OK: [SWS_Can_00419] ⌈ The Can module shall disable all unused interrupts in the CAN Controller.⌋  
OK: [SWS_Can_00420] ⌈ The Can module shall *reset the interrupt flag at the end* of the ISR (if not done automatically by hardware). ⌋  
OK: [SWS_Can_00079] ⌈ The Can module shall fulfill all design and implementation guidelines described in [2].⌋ 

# **7.1 Driver scope**
NA: [SWS_Can_00077] ⌈ For CAN Hardware Units of different type, different Can modules shall be implemented. ⌋  
NA: [SWS_Can_00284] ⌈ In case several CAN Hardware Units (of same or different
vendor) are implemented in one ECU the function names, and global variables of the
Can modules shall be implemented such that no two functions with the same name
are generated.⌋  
NA: [SWS_Can_00385] ⌈ The naming conventions shall be used only in that case, if
multiple different CAN controller types on one ECU have to be supported. ⌋  
OK: [SWS_Can_00386] ⌈ If only one controller type is used, the original naming
conventions without any &lt;driver abbreviation&gt; extensions are sufficient.⌋  

# **7.2 Driver State Machine**
OK: [SWS_Can_00103] ⌈ After power-up/reset, the Can module shall be in the state CAN_UNINIT. ⌋  
OK: [SWS_Can_00246] ⌈ The function Can_Init shall change the module state to
CAN_READY, after initializing all controllers inside the HW Unit.⌋  
OK: [SWS_Can_00245] ⌈ The function Can_Init shall initialize all CAN controllers
according to their configuration.⌋  
OK: [SWS_Can_ 91009] ⌈ The function Can_DeInit shall change the module state to
CAN_UNINIT before de-initializing all controllers inside the HW unit⌋  

# **7.3 CAN Controller State Machine**
CAN Controller HW has its own complex state machine, but for simplification CAN Controller SW shall
has 4 basic states: UNINIT, STOPPED, STARTED, SLEEP.  
Service that change internal register settings to effects CAN module state: Can_Init, Can_SetBaudrate, Can_SetControllerMode.  
External event that effects to CAN Controller state: Bus-off, HW wakeup event. These event shall be detected by interrupt or polling status bit
with Can_MainFunction_BusOff, Can_MainFunction_Wakeup, then it notifies the CANIf module with corresponding callback function (the software state is then changed inside
the callback function).  

# **7.3.1 CAN Controller State Description**
- **UNINIT**: The CAN controller is not initialized. All registers belonging to the CAN module are in reset state, CAN interrupts are disabled.  
- **STOPPED**: In this state the CAN Controller is initialized but does not participate on the bus.  
- **STARTED**: The controller is in a normal operation mode with complete functionality, which means it participates in the network.  
- **SLEEP**: The hardware settings only differ from state STOPPED for CAN hardware that support a sleep mode (wake-up over CAN bus directly supported by CAN hardware).  

NG: [SWS_Can_00257] ⌈ When the CAN hardware supports sleep mode and is triggered
to transition into SLEEP state, the Can module shall set the controller to the SLEEP
state from which the hardware can be woken over CAN Bus.⌋  
NG: [SWS_Can_00258] ⌈ When the CAN hardware does not support sleep mode and is
triggered to transition into SLEEP state, the Can module shall emulate a logical
SLEEP state from which it returns only, when it is triggered by software to transition
into STOPPED state.⌋  
NG: [SWS_Can_00404] ⌈ The CAN hardware shall remain in state STOPPED, while the
logical SLEEP state is active.⌋  

# **7.3.2 CAN Controller State Transitions**
