#*******************************************************************************
# File:         common.mak
# Revision:
# Author:
# Date:         03.09.2019
# Description:  make file rule of common part
#*******************************************************************************
# Recursive Wildcard Function to find all file in sub folder
# rwildcard=$(foreach d,$(wildcard $1*),$(call rwildcard,$d/,$2)\
  # $(filter $(subst *,%,$2),$d))
# $(call rwildcard,/tmp/,*.c *.h)
# for each "d" in "input top dir", recursive call, filter folder include in "d" list
rwildcard=$(foreach d,$(wildcard $1*),$(call rwildcard,$d/,$2)\
  $(filter %$2,$d))

#find all "src" folder path in common top folder
COMMON_SRC := $(call rwildcard,$(BASE)/common/,.c)
#find all "include" folder path in common top folder
COMMON_INC := $(call rwildcard,$(BASE)/common/,include)

.PHONY : debug_common
debug_common:
	@echo COMMON_SRC: $(COMMON_SRC)
	@echo COMMON_INC: $(COMMON_INC)