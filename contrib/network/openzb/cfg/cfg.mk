## Author: 2008 Mauro Marinoni

## Check the Console library selection
ifeq ($(findstring __LIB_OPENZB__,$(LIB_OPT)),__LIB_OPENZB__)

##
## Application files
##

EE_SRCS += contrib/network/openzb/src/util/ozb_debug.c
EE_SRCS += contrib/network/openzb/src/hal/ozb_radio_cc2420.c
EE_SRCS += contrib/network/openzb/src/kal/ozb_kal_erika.c
ifneq ($(findstring OZB_HAL_EXTERNAL_TIMER,$(EEOPT)), OZB_HAL_EXTERNAL_TIMER)
EE_SRCS += contrib/network/openzb/src/hal/ozb_timer_dspic30.c
endif

EE_SRCS += contrib/network/openzb/src/phy/ozb_phy.c

ifneq ($(findstring OZB_USE_ONLY_802154_PHY,$(EEOPT)), OZB_USE_ONLY_802154_PHY)
EE_SRCS += contrib/network/openzb/src/mac/ozb_mac.c
EE_SRCS += contrib/network/openzb/src/mac/ozb_mac_mlme.c
EE_SRCS += contrib/network/openzb/src/mac/ozb_mac_mcps.c
EE_SRCS += contrib/network/openzb/src/mac/ozb_mac_superframe.c
EE_SRCS += contrib/network/openzb/src/mac/ozb_mac_gts.c
endif

#EE_SRCS += contrib/network/openzb/src/mac/ozb_net_mac_events.c


#EE_SRCS_OPENZB_COMMON := $(addprefix contrib/network/openzb/src/, $(notdir $(shell ls -1 $(EEBASE)/contrib/network/openzb/src/*.c)))
#EE_SRCS += $(EE_SRCS_OPENZB_COMMON)


## Potentially, check the architecture
#ifeq ($(findstring __PIC30__,$(EEOPT)) , __PIC30__)
## Add each file individually
#EE_SRCS += contrib/console/src/hal/pic30.c
#endif

endif
