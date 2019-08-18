CC = arm-none-eabi-gcc
OBJCPY = arm-none-eabi-objcopy
GDB = arm-none-eabi-gdb
 
C_CPU_FLAGS = -mcpu=cortex-m4 -mthumb -mabi=aapcs -mfloat-abi=hard -mfpu=fpv4-sp-d16 -mabi=aapcs 
C_DEBUG_FLAGS = -g
C_OTHER_FLAGS = -ffunction-sections -fdata-sections
C_OPTIMIZATION_FLAGS = -O0
C_LANGUAGE_FLAGS = -std=c11

CFLAGS = $(C_CPU_FLAGS) $(C_DEBUG_FLAGS) $(C_OTHER_FLAGS) $(C_OPTIMIZATION_FLAGS)
LD_FLAGS = -T SampleApp.ld -Wl,-Map=project.map -Wl,--gc-sections -nostartfiles
 
SOURCES = Interrupt.c Interrupt_VectorTable.c SampleApp.c startup_stm32f407vg.s
OBJECTS = Interrupt.o Interrupt_VectorTable.o SampleApp.o startup_stm32f407vg.o


all: project.hex project.bin

%.o : %.c
	$(CC) $(CFLAGS) -c -o $@ $< $(CFLAGS)
 
project.elf: $(OBJECTS)
	$(CC) -o $@ $(C_CPU_FLAGS) $(LD_FLAGS) $^
 
project.bin: project.elf
	$(OBJCPY) -O binary $^ $@
 
project.hex: project.elf
	$(OBJCPY) -O ihex $^ $@
 
clean:
	rm -rf *.o *.elf *.bin *.hex *.map

# -c -mcpu=cortex-m4 -mthumb -gdwarf-2 -MD -Wall -O0 -mapcs-frame -mthumb-interwork
 # -I <path> C:/Users/NDY3HC/Desktop/Tool/Keil_v5/ARM/CMSIS/Include
 # -D<macro>="<value>" -D<macro> -Wa,-alhms="*.lst" -o *.o 
 
# -mcpu=cortex-m4 -mthumb --gdwarf-2 -mthumb-interwork --MD *.d
 # -IC:/Users/NDY3HC/Desktop/Tool/Keil_v5/ARM/CMSIS/Include
 # -alhms="*.lst" -o *.o 

# -T ../../stm32/test/SampleApp.ld -mcpu=cortex-m4 -mthumb -mthumb-interwork -Wl,-Map="./test.map" 
# -o test.elf 
# *.o -nostartfiles -nodefaultlibs -lm
