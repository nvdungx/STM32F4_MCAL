Core AUTOSAR operating system assumes free access to hardware resources:
 interrupt control registers
 processor status words
 stack pointer(s)

 Memory Protection: A hardware memory protection unit is required. All memory
accesses that have the consequence of writing (e.g. reads that have the side
effect of writing to a memory location) shall be treated as writes.

 Time Protection: Timer Hardware for monitoring execution times and arrival rates.

 »Privileged« and »non-privileged« modes on the MCU: to protect the OS against
internal corruption caused by writes to OS controlled registers. 

 Local/Global Time Synchronization: A global time source is needed.

In general hardware failures in the processor are not detected by the operating
system. In the event of hardware failure, correct operation of the OS cannot be
guaranteed.

OSEK OS is an event-triggered operating system. This provides high flexibility in the
design and maintenance of AUTOSAR based systems

fixed priority-based scheduling facilities for handling interrupts only interrupts with higher priority than tasks
some protection against incorrect use of OS services a startup interface through StartOS() and the StartupHook() a shutdown interface through ShutdownOS() and the ShutdownHook()

configurable selection of Trusted Functions, Tasks, ISRs, Alarms,
Schedule tables, Counters, hooks (for startup, error and shutdown).

OSEK core services:
- Task management, scheduler
- ISR management
- Resource management
- Counters
- Alarms
- Events
- Communication
- Error handling, hook routines

Task provides frame(data storage) for executing functions, execution can be concurrently or asynchronously
OSEK has 2 kind of task:
- Basic: no waiting state, can only be synchronized at start or end of task
- Extended: can call WaitEvent(), event synchronize inside the task

Task can not be killed and only terminate by itself.
Ready, Running, Suspended, Waiting(Extended)
Task activation: OS at startup, other task, ISR, alarm, sending message.
Task termination itself by calling: TerminateTask, ChainTask


Cooperative(non-preemptive)/Preemptive scheduling
Static/Dynamic scheduling
OSEK use priority-based dynamic scheduling
Nested interrupt is allowed, ISRs have highest priority
2 category: with os call, without os call

Resource management:
Two tasks/ISRs cannot “own” the same resource at the same time
Tasks accessing resources never enter a Wait state
Resource with ceiling priority higher than all tasks