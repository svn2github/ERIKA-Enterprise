## Author: 2007 Antonio Romano
## CVS: $Id:


ifeq ($(findstring __LIB_ATMEL802154__,$(LIB_OPT)),__LIB_ATMEL802154__)

##
## Application files
##

ifeq ($(findstring __AT86RF230__,$(EEOPT)) , __AT86RF230__)

EE_SRCS +=      

endif

##
## Add atmel802.15.4 to the linker list of libs
##

OPT_LIBS += -lZigbEE

endif
