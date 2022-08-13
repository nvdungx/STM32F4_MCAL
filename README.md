# stm32 AUTOSAR MCAL  
# target is to create AUTOSAR MCAL(4.4.0) and sample bare metal embedded project  
# directory structure  
**common**: startup code, interrupt table, memory mapping, platform, standard abstraction and stub code  
**modules**: mcal modules for stm32f407vg mcu  
**ref**: reference source  
**sample**: sample application  
**script**: script file for project  
**test**: test folder  

make clean;make all;arm-none-eabi-objdump -DleF project.elf > debuginfo_2.txt  