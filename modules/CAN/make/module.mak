#*******************************************************************************
# File:         module.mak
# Revision:
# Author:
# Date:         03.09.2019
# Description:  make file rule of module part
#*******************************************************************************

# Fixed dir
MODULE_SRC := $(wildcard $(BASE)/modules/$(MODULE)/src/*.c)
# Fixed dir
MODULE_INC := $(BASE)/modules/$(MODULE)/include

.PHONY : debug_module
debug_module:
	@echo MODULE_SRC: $(MODULE_SRC)
	@echo MODULE_INC: $(MODULE_INC)