## Author: 2008 Mauro Marinoni

## Check the Console library selection
ifeq ($(findstring __LIB_OPENZB__,$(LIB_OPT)),__LIB_OPENZB__)

##
## Application files
##

EE_SRCS += contrib/network/openzb/src/util/ozb_debug.c
EE_SRCS += contrib/network/openzb/src/phy/ozb_phy.c
EE_SRCS += contrib/network/openzb/src/mac/ozb_mac_phy_events.c
#EE_SRCS_OPENZB_COMMON := $(addprefix contrib/network/openzb/src/, $(notdir $(shell ls -1 $(EEBASE)/contrib/network/openzb/src/*.c)))
#EE_SRCS += $(EE_SRCS_OPENZB_COMMON)


## Potentially, check the architecture
#ifeq ($(findstring __PIC30__,$(EEOPT)) , __PIC30__)
## Add each file individually
#EE_SRCS += contrib/console/src/hal/pic30.c
#endif

endif
