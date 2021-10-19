# stm32 AUTOSAR MCAL  
# target is to create AUTOSAR MCAL and sample bare metal embedded project  
# directory structure  
**common**: startup code, interrupt table, memory mapping, platform, standard abstraction and stub code  
**modules**: mcal modules for stm32f407vg mcu  
**ref**: reference source  
**sample**: sample application  
**script**: script file for project  
**test**: test folder  

make clean;make all;arm-none-eabi-objdump -DleF project.elf > debuginfo_2.txt  

https://www.emobility-engineering.com/focus-ecus/  
https://www.etas.com/en/applications/applications_calibrating_automotive_electronics.php  
https://autoecuhw.blogspot.com/2019/04/functional-safety-e-gas-monitoring-general-part1.html  
https://www.ablic.com/en/semicon/products/automotive/automotive-watchdog-timer/intro/  