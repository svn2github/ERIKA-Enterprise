## Author: 2011 Riccardo Schiavi
## Check the selection


ifeq ($(findstring __LIB_TCPIP__,$(LIB_OPT)) , __LIB_TCPIP__)

##
## Application files
## 
#EE_SRCS += $(shell ls $(EEBASE)/contrib/microchip/tcpip_531/libsrc/*.c)
#EE_SRCS += $(shell ls $(EEBASE)/contrib/microchip/tcpip_531/libsrc/WiFi/*.c)
SRCS += $(shell ls $(EEBASE)/contrib/microchip/tcpip_531/libsrc/*.c)
SRCS += $(shell ls $(EEBASE)/contrib/microchip/tcpip_531/libsrc/WiFi/*.c)


endif
