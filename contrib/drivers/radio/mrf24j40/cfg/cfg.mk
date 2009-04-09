## Author: 2009 Mauro Marinoni

## Check the MRF24J40 library selection
ifeq ($(findstring __LIB_MRF24J40__,$(LIB_OPT)),__LIB_MRF24J40__)

##
## Application files
##

EE_SRCS += contrib/drivers/radio/mrf24j40/src/mrf24j40.c
EE_SRCS += contrib/drivers/radio/mrf24j40/src/mrf24j40_hal_ee.c
#EE_SRCS_MRF24J40_COMMON := $(addprefix contrib/drivers/radio/mrf24j40/src/, $(notdir $(shell ls -1 $(EEBASE)/contrib/drivers/radio/mrf24j40/src/*.c)))
#EE_SRCS += $(EE_SRCS_MRF24J40_COMMON)


## Potentially, check the architecture
#ifeq ($(findstring __PIC30__,$(EEOPT)) , __PIC30__)
## Add each file individually
#EE_SRCS += contrib/console/src/hal/pic30.c
#endif

endif
