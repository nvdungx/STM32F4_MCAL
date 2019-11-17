#*******************************************************************************
# File:         Makefile
# Revision:
# Author:
# Date:         03.09.2019
# Description:  Makefile of SampleApp
#*******************************************************************************
#option input for makefile to parallel execution of rules
MAKEFLAGS += -j

# specify base path of project << shall input by tool or change manually
BASE := D:\Tool\Workspace\github\stm32
MODULE := CAN

include ../common/make/common.mak
include ../modules/$(MODULE)/make/module.mak
#include module shall be change to use input para in build script

#specify device
#specify module build
#specify toolchain path, base project path

#define compile flags
#define linker flags

#rule to build sample app
#Device
DEVICE=stm32f407vg

# TOOLCHAIN_PATH = D:\Tool\GNUToolsARMEmbedded\ARMCompiler\bin

CC = $(TOOLCHAIN_PATH)/arm-none-eabi-gcc
AS = $(TOOLCHAIN_PATH)/arm-none-eabi-as
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

CFLAGS = $(C_CPU_FLAGS) $(C_DEBUG_FLAGS) $(C_OTHER_FLAGS) $(C_OPTIMIZATION_FLAGS) $(C_LANGUAGE_FLAGS)
#--script=file warning, output mapfile , enable garbage collection of unused section
LD_FLAGS = -T SampleApp.ld -Wl,-Map=SampleApp.map -Wl,--gc-sections -nostartfiles

SRCFILES += $(wildcard *.c) $(COMMON_SRC) $(MODULE_SRC)
INCFILES += $(CURDIR) $(COMMON_INC) $(MODULE_INC)
INCFILES := $(addprefix -I,$(INCFILES))
# OBJECTS := $(SRCFILES:.c=.o)
# to get the file name only and change to target .o file
OBJECTS := $(notdir $(SRCFILES:.c=.o))
# set the dir for searching source file required by static pattern
vpath %.c $(sort $(dir $(SRCFILES)))

all: SampleApp.hex SampleApp.bin

$(OBJECTS): %.o : %.c
	$(CC) $(CFLAGS) $(INCFILES) -c $^ -o $@

startup_$(DEVICE).o : $(STARTUP)
	$(CC) $(CFLAGS) $(INCFILES) -c $< -o $@

OBJECTS += startup_$(DEVICE).o

SampleApp.elf: $(OBJECTS)
	$(CC) -o $@ $(C_CPU_FLAGS) $(LD_FLAGS) $^

SampleApp.bin: SampleApp.elf
	$(OBJCPY) -O binary $^ $@

SampleApp.hex: SampleApp.elf
	$(OBJCPY) -O ihex $^ $@

clean:
	rm -rf *.o *.elf *.bin *.hex *.map

.PHONY : debug_vars
debug_vars:
	@echo SRCFILES: $(SRCFILES)
	@echo INCFILES: $(INCFILES)
	@echo OBJECTS: $(OBJECTS)
