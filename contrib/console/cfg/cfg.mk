## Author: 2008 Mauro Marinoni

## Check the Console library selection
ifeq ($(findstring __LIB_CONSOLE__,$(LIB_OPT)),__LIB_CONSOLE__)

##
## Application files
##

#EE_SRCS += contrib/console/src/console.c
EE_SRCS_CONSOLE_COMMON := $(addprefix contrib/console/src/, $(notdir $(shell ls -1 $(EEBASE)/contrib/console/src/*.c)))
EE_SRCS += $(EE_SRCS_CONSOLE_COMMON)


## Check the architecture
ifeq ($(call iseeopt, __PIC30__), yes)
EE_SRCS += contrib/console/src/hal/pic30.c
endif

ifeq ($(call iseeopt, __PIC32__), yes)
EE_SRCS += contrib/console/src/hal/pic32.c
endif

ifeq ($(call iseeopt, __AVR5__), yes)
EE_SRCS += contrib/console/src/hal/avr5.c
endif

ifeq ($(call iseeopt, __LM32__), yes)
EE_SRCS += contrib/console/src/hal/mico32.c
endif

ifeq ($(call iseeopt, __MC9S12__), yes)
EE_HC12_CONSOLE=YES
endif
ifeq ($(call iseeopt, __HCS12XS__), yes)
EE_HC12_CONSOLE=YES
endif
ifeq ($(EE_HC12_CONSOLE), YES)
EE_SRCS += contrib/console/src/hal/s12.c
endif

INCLUDE_PATH += $(EEBASE)/contrib/console/inc

endif
