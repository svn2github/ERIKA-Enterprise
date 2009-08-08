## Author: 2009 Francesco Prosperi

#Check the Microchip EEPROM Emulation Library
ifeq ($(findstring __LIB_DEE_EMULATION__,$(LIB_OPT)) , __LIB_DEE_EMULATION__)
INCLUDE_DEE_EMULATION = YES
endif

## Check if it's selected all libs inclusion
ifeq ($(findstring __BUILD_ALL_LIBS__,$(EEOPT)) , __BUILD_ALL_LIBS__)
INCLUDE_DEE_EMULATION = YES
endif

##
## If the library is required
##
ifeq ($(INCLUDE_DEE_EMULATION), YES)

##
## Library code
##

## Add the inc path to the include pathlist
ifeq ($(findstring __RTD_CYGWIN__,$(EEOPT)), __RTD_CYGWIN__) 
ALLINCPATH += -I"$(shell cygpath -w $(EEBASE)/contrib/microchip/dee_emulation/inc)"
else
ALLINCPATH += -I$(EEBASE)/contrib/microchip/dee_emulation/inc
endif

endif
