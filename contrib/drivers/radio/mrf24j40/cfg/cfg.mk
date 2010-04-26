## Author: 2010 Christian Nastasi

## Check the MRF24J40 library selection
ifeq ($(findstring __LIB_MRF24J40__,$(LIB_OPT)),__LIB_MRF24J40__)

##
## Application files
##

EE_SRCS += contrib/drivers/radio/mrf24j40/src/mrf24j40.c
ifeq ($(findstring __MICROCHIP_DSPIC30__,$(EEOPT)) , __MICROCHIP_DSPIC30__)
EE_SRCS += contrib/drivers/radio/mrf24j40/src/mrf24j40_hal_ee_dspic.c
endif
ifeq ($(findstring __MICROCHIP_PIC32__,$(EEOPT)) , __MICROCHIP_PIC32__)
EE_SRCS += contrib/drivers/radio/mrf24j40/src/mrf24j40_hal_ee_pic32.c
endif
ifeq ($(findstring __LM32__,$(EEOPT)) , __LM32__)
EE_SRCS += contrib/drivers/radio/mrf24j40/src/mrf24j40_hal_ee_mico32.c
endif

endif
