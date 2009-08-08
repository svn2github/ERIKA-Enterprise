## Author: 2007 Mauro Marinoni

## Check the Console library selection
ifeq ($(findstring __LIB_AMAZING__,$(LIB_OPT)) , __LIB_AMAZING__)
INCLUDE_AMAZING = YES
endif

## Check if it's selected all libs inclusion
ifeq ($(findstring __BUILD_ALL_LIBS__,$(EEOPT)) , __BUILD_ALL_LIBS__)
INCLUDE_AMAZING = YES
endif

##
## If the library is required
##
ifeq ($(INCLUDE_AMAZING), YES)

##
## Library code
##

## Add the inc path to the include pathlist
ifeq ($(findstring __RTD_CYGWIN__,$(EEOPT)), __RTD_CYGWIN__) 
ALLINCPATH += -I"$(shell cygpath -w $(EEBASE)/contrib/amazing/inc)"
else
ALLINCPATH += -I$(EEBASE)/contrib/amazing/inc
endif

endif
