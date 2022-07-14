#*******************************************************************************
# File:         module.mak
# Revision:     1.0.0
# Author:       Dung van Nguyen
# Date:         03.09.2019
# Description:  make file rule of module part
#*******************************************************************************

# Fixed dir
MODULE_SRC := $(wildcard $(BASE)/modules/$(MODULE)/src/*.c)
MODULE_SRC += $(wildcard $(BASE)/modules/$(MODULE)/generate/src/*.c)
# Fixed dir
MODULE_INC := $(BASE)/modules/$(MODULE)/include
MODULE_INC += $(BASE)/modules/$(MODULE)/generate/include

.PHONY : debug_module
debug_module:
	@echo MODULE_SRC: $(MODULE_SRC)
	@echo MODULE_INC: $(MODULE_INC)