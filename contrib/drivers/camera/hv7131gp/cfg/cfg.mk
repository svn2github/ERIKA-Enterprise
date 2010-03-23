## Author: 2009 Mauro Marinoni

## Check the MRF24J40 library selection
ifeq ($(findstring __LIB_HV7131GP__,$(LIB_OPT)),__LIB_HV7131GP__)

##
## Application files
##

EE_SRCS += contrib/drivers/camera/hv7131gp/src/hv7131gp.c
ifeq ($(findstring __MICROCHIP_DSPIC30__,$(EEOPT)) , __MICROCHIP_DSPIC30__)
EE_SRCS += contrib/drivers/camera/hv7131gp/src/hv7131gp_hal_ee_dspic.c
endif
ifeq ($(findstring __MICROCHIP_PIC32__,$(EEOPT)) , __MICROCHIP_PIC32__)
EE_SRCS += contrib/drivers/camera/hv7131gp/src/hv7131gp_hal_ee_pic32.c
endif

endif
