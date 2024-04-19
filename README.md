# stm32 AUTOSAR MCAL<br/>
# target is to create AUTOSAR MCAL(4.4.0) and sample bare metal embedded project<br/>
# directory structure<br/>
**common**: startup code, interrupt table, memory mapping, platform, standard abstraction and stub code<br/>
**modules**: mcal modules for stm32f407vg mcu<br/>
**ref**: reference source<br/>
**sample**: sample application<br/>
**script**: script file for project<br/>
**test**: test folder<br/>

make clean;make all;arm-none-eabi-objdump -DleF project.elf > debuginfo_2.txt<br/>
https://wiki.segger.com/J-Link_Commander<br/>