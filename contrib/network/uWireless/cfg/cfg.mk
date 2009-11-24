## Author: 2008 Mauro Marinoni

## Check the Console library selection
ifeq ($(findstring __LIB_UWIRELESS__,$(LIB_OPT)),__LIB_UWIRELESS__)

##
## Application files
##

EE_SRCS += contrib/network/uWireless/src/kal/uwl_kal_erika.c
EE_SRCS += contrib/network/uWireless/src/util/uwl_debug.c

ifeq ($(findstring __LIB_CC2420__,$(LIB_OPT)),__LIB_CC2420__)
#ifeq ($(findstring USE_CC2420,$(LIB_OPT)), USE_CC2420)
EE_SRCS += contrib/network/uWireless/src/hal/uwl_radio_cc2420.c
endif

ifeq ($(findstring __LIB_MRF24J40__,$(LIB_OPT)),__LIB_MRF24J40__)
#ifeq ($(findstring USE_MRF24J40,$(LIB_OPT)),USE_MRF24J40)
EE_SRCS += contrib/network/uWireless/src/hal/uwl_radio_mrf24j40.c
endif

ifneq ($(findstring UWL_HAL_EXTERNAL_TIMER,$(EEOPT)), UWL_HAL_EXTERNAL_TIMER)
EE_SRCS += contrib/network/uWireless/src/hal/uwl_timer_dspic30.c
endif

EE_SRCS += contrib/network/uWireless/src/phy/uwl_phy.c

ifneq ($(findstring UWL_USE_ONLY_802154_PHY,$(EEOPT)), UWL_USE_ONLY_802154_PHY)
EE_SRCS += contrib/network/uWireless/src/mac/uwl_mac.c
EE_SRCS += contrib/network/uWireless/src/mac/uwl_mac_mlme.c
EE_SRCS += contrib/network/uWireless/src/mac/uwl_mac_mcps.c
EE_SRCS += contrib/network/uWireless/src/mac/uwl_mac_superframe.c
EE_SRCS += contrib/network/uWireless/src/mac/uwl_mac_gts.c
endif

ifneq ($(findstring UWL_USE_ONLY_802154_MAC,$(EEOPT)), UWL_USE_ONLY_802154_MAC)
ifeq ($(findstring UWL_USE_SIMPLE_802154,$(EEOPT)), UWL_USE_SIMPLE_802154)
EE_SRCS += contrib/network/uWireless/src/net/uwl_simple154.c
endif
endif

#EE_SRCS += contrib/network/uWireless/src/mac/uwl_net_mac_events.c


#EE_SRCS_uWireless_COMMON := $(addprefix contrib/network/uWireless/src/, $(notdir $(shell ls -1 $(EEBASE)/contrib/network/uWireless/src/*.c)))
#EE_SRCS += $(EE_SRCS_uWireless_COMMON)


## Potentially, check the architecture
#ifeq ($(findstring __PIC30__,$(EEOPT)) , __PIC30__)
## Add each file individually
#EE_SRCS += contrib/console/src/hal/pic30.c
#endif

endif
