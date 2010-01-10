
# --- Variable part, automatically generated from 'conf.oil' ---

CFLAGS = -g2
ASFLAGS = 
LDFLAGS = 

# Application C/Asm source files
APP_SRCS = main.c


############################################################################
#
# Setting EEOPT variable
#
############################################################################

EEOPT =


#
# User options
#

EEOPT += 


#
# Automatic options
#

EEOPT += __LM32__
EEOPT += __FP__
EEOPT += __MONO__



# --- Fixed part ---

# Application directory
APPBASE := .

# Additional file sources
SRCS = $(OUTPUT_DIR)/eecfg.c
SRCS += $(OUTPUT_DIR)/crt0ram.S
#SRCS += $(PLATFORM_LIB_PATH)/$(PLATFORM_NAME)/crt0ram.S

LD_FILE = $(OUTPUT_DIR)/linker.ld

include $(OUTPUT_DIR)/platform.mk
include $(OUTPUT_DIR)/lattice.mk
include $(EEBASE)/pkg/cfg/rules.mk

# Remove the crt*.o files from the building process
$(LD_FILE): $(PLATFORM_LD_FILE)
	@echo "Patching linker script"
	$(QUIET) grep -v -E '^INPUT\(' $< > $@
