
#Device
DEVICE=stm32f407VG

TOOLCHAIN_PATH = 
BASE=../

CC = $(TOOLCHAIN_PATH)/arm-none-eabi-gcc
OBJCPY = $(TOOLCHAIN_PATH)/arm-none-eabi-objcopy
GDB = $(TOOLCHAIN_PATH)/arm-none-eabi-gdb

C_CPU_FLAGS = -mcpu=cortex-m4 -mthumb -mabi=aapcs -mfloat-abi=hard -mfpu=fpv4-sp-d16 -mabi=aapcs
C_DEBUG_FLAGS = -g
C_OTHER_FLAGS = -ffunction-sections -fdata-sections -flto
C_OPTIMIZATION_FLAGS = -O0
C_LANGUAGE_FLAGS = -std=c99

# Startup code
STARTUP=$(BASE)/common/arm/startup_$(DEVICE).s

# Link for code size
GC=-Wl,--gc-sections

CFLAGS = $(C_CPU_FLAGS) $(C_DEBUG_FLAGS) $(C_OTHER_FLAGS) $(C_OPTIMIZATION_FLAGS)
#--script=file warning, output mapfile , enable garbage collection of unused section
LD_FLAGS = -T SampleApp.ld -Wl,-Map=SampleApp.map -Wl,--gc-sections -nostartfiles

SOURCES = $(BASE)/sample/SampleApp.c\
          $(BASE)/common/interrupt/Interrupt.c\
          $(BASE)/common/interrupt/Interrupt_VectorTable.c\
          $(BASE)/common/arm/src/system_stm32f407VG.c

INCLUDEFILES= $(BASE)/common/arm/include\
          $(BASE)/common/arm/include\
          $(BASE)/common/interrupt\
          $(BASE)/common/interrupt

OBJECTS = $(SOURCES:.c=.o)

all: project.hex project.bin

%.o : %.c
	$(CC) $(CFLAGS) -I $(INCLUDEFILES) -c -o $@ $< $(CFLAGS)

project.elf: $(OBJECTS)
	$(CC) -o $@ $(C_CPU_FLAGS) $(LD_FLAGS) $^

project.bin: project.elf
	$(OBJCPY) -O binary $^ $@

project.hex: project.elf
	$(OBJCPY) -O ihex $^ $@

clean:
rm -rf *.o *.elf *.bin *.hex *.map
