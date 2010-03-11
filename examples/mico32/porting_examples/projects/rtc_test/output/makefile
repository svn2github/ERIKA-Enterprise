# # Date             : 3/11/2010
# RT-Druid version : 
#

# these lines override the .bashrc definitions
#EEBASE = ../../..
#APPBASE = .

###
### Setting EEOPT variable:
###

EEOPT =


############################################################################
#
# User options
#
############################################################################
EEOPT += DEBUG_STACK
EEOPT += __USE_UART__
EEOPT += __USE_I2C__
EEOPT += __USE_MICO32BOARD_RTC__
EEOPT += __EE_RTC_USE_I2C1__
EEOPT += __USE_TIMER__


############################################################################
#
# Automatic options
#
############################################################################
EEOPT += __RTD_CYGWIN__
EEOPT += __LM32__
EEOPT += __FP__
EEOPT += __MULTI__
EEOPT += __ALARMS__


############################################################################
#
# Lattice mico 32
#
############################################################################
ifndef EVIDENCEBASE
    EVIDENCEBASE := $(shell cygpath `cygpath -ms "C:\Evidence\Evidence\eclipse\plugins\com.eu.evidence.ee_1.0.0.201002101522"`)
endif
ifndef EEBASE
    EEBASE  := $(shell cygpath `cygpath -ms "C:\Evidence\Evidence\eclipse\plugins\com.eu.evidence.ee_1.0.0.201002101522\ee_base"`)
endif
APPBASE := ..
OUTBASE := output

LD_FILE = $(OUTPUT_DIR)/linker.ld



############################################################################
#
# Flags
#
############################################################################
CFLAGS  += -g2
ASFLAGS += 
LDFLAGS += 
LDDEPS  += 
LIBS    += 



############################################################################
#
# Sources
#
############################################################################
APP_SRCS += $(OUTBASE)/eecfg.c $(OUTPUT_DIR)/crt0ram.S main.c


############################################################################
#
# More rules for Lattice mico 32
#
############################################################################
include $(OUTPUT_DIR)/platform.mk
include $(OUTPUT_DIR)/lattice.mk

# Remove the crt*.o files from the building process
$(LD_FILE): $(PLATFORM_LD_FILE)
	@echo "Patching linker script"
	$(QUIET) grep -v -E '^INPUT\(' $< > $@



############################################################################
#
# end
#
############################################################################
include $(EEBASE)/pkg/cfg/rules.mk
