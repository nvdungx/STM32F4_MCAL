#*******************************************************************************
# File:         Makefile
# Revision:
# Author:
# Date:         03.09.2019
# Description:  Makefile of SampleApp
#*******************************************************************************

include ../common/make/common.mak
include ../modules/CAN/make/module.mak
#include module shall be change to use input para in build script

#specify device
#specify module build
#specify toolchain path, base project path

#define compile flags
#define linker flags

#rule to build sample app
#Device
DEVICE=stm32f407VG

TOOLCHAIN_PATH = C:\Users\NDY3HC\Desktop\Tool\gcc\gcc-arm-none-eabi-7-2018-q2-update-win32\bin
BASE=../

CC = $(TOOLCHAIN_PATH)/arm-none-eabi-gcc
LD = $(TOOLCHAIN_PATH)/arm-none-eabi-ld
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

OBJECTS = $(SRCFILES:.c=.o)

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
