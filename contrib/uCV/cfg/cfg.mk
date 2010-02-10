## Author: 2010 Christian Nastasi

## Check the uCV library selection
ifeq ($(findstring __LIB_UCV__,$(LIB_OPT)),__LIB_UCV__)

##
## Application files
##

#EE_SRCS += contrib/uCV/src/ucv.c
EE_SRCS_UCV_COMMON := $(addprefix contrib/uCV/src/, $(notdir $(shell ls -1 $(EEBASE)/contrib/uCV/src/*.c)))
EE_SRCS += $(EE_SRCS_UCV_COMMON)

## Add the inc path to the include pathlist
ifeq ($(findstring __COSMIC__,$(EEOPT)), __COSMIC__)
ALLINCPATH += -i"$(shell cygpath -w $(EEBASE)/contrib/uCV/inc)"
else
ifeq ($(findstring __RTD_CYGWIN__,$(EEOPT)), __RTD_CYGWIN__) 
ALLINCPATH += -I"$(shell cygpath -w $(EEBASE)/contrib/uCV/inc)"
else
ALLINCPATH += -I$(EEBASE)/contrib/uCV/inc
endif
endif

endif
