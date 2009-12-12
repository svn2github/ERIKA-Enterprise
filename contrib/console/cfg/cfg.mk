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
ifeq ($(findstring __PIC30__,$(EEOPT)) , __PIC30__)
EE_SRCS += contrib/console/src/hal/pic30.c
endif

ifeq ($(findstring __PIC32__,$(EEOPT)) , __PIC32__)
EE_SRCS += contrib/console/src/hal/pic32.c
endif

ifeq ($(findstring __AVR5__,$(EEOPT)) , __AVR5__)
EE_SRCS += contrib/console/src/hal/avr5.c
endif

ifeq ($(findstring __HCS12XS__,$(EEOPT)) , __HCS12XS__)
ifeq ($(findstring __MC9S12XS128__,$(EEOPT)) , __MC9S12XS128__)
ALLINCPATH += -i"$(shell cygpath -w $(EEBASE)/contrib/console/inc)"
EE_SRCS += contrib/console/src/hal/s12.c
endif
endif

endif
