## Author: 2008 Mauro Marinoni

## Check the Console library selection
ifeq ($(findstring __LIB_CONSOLE__,$(LIB_OPT)),__LIB_CONSOLE__)

##
## Application files
##

#EE_SRCS += contrib/console/src/console.c
EE_SRCS_CONSOLE_COMMON := $(addprefix contrib/console/src/, $(notdir $(shell ls -1 $(EEBASE)/contrib/console/src/*.c)))
EE_SRCS += $(EE_SRCS_CONSOLE_COMMON)


## Potentially, check the architecture
ifeq ($(findstring __PIC30__,$(EEOPT)) , __PIC30__)

## Add each file individually
EE_SRCS += contrib/console/src/hal/pic30.c

endif

endif
