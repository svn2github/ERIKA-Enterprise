## Author: 2007 Mauro Marinoni

## Check the CC2420 library selection
ifeq ($(findstring __LIB_TOUCH__,$(LIB_OPT)) , __LIB_TOUCH__)
INCLUDE_TOUCH = YES
endif

## Check if it's selected all libs inclusion
ifeq ($(findstring __BUILD_ALL_LIBS__,$(EEOPT)) , __BUILD_ALL_LIBS__)
INCLUDE_TOUCH = YES
endif

##
## If the library is required
##
ifeq ($(INCLUDE_TOUCH), YES)

##
## Library code
##

## Add the inc path to the include pathlist
ifeq ($(findstring __RTD_CYGWIN__,$(EEOPT)), __RTD_CYGWIN__) 
ALLINCPATH += -I"$(shell cygpath -w $(EEBASE)/contrib/drivers/touch/inc)"
else
ALLINCPATH += -I$(EEBASE)/contrib/drivers/touch/inc
endif

endif
