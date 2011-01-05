## Author: 2010 Dario Di Stefano 

## Check the ENC28J60 library selection
ifeq ($(findstring __LIB_ENC28J60__,$(LIB_OPT)),__LIB_ENC28J60__)

##
## Application files
##

EE_SRCS += contrib/drivers/ethernet/enc28j60/src/enc28j60.c

ifeq ($(call iseeopt, __LM32__), yes)
EE_SRCS += contrib/drivers/ethernet/enc28j60/src/enc28j60_hal_ee_mico32.c
endif

ifeq ($(call iseeopt, __PIC32__), yes)
EE_SRCS += contrib/drivers/ethernet/enc28j60/src/enc28j60_hal_ee_pic32.c
endif

endif
