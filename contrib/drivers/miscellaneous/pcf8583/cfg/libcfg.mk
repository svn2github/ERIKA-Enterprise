## Author: 2010 Dario Di Stefano

## Check the library selection
ifeq ($(findstring __LIB_PCF8583__,$(LIB_OPT)),__LIB_PCF8583__)
INCLUDE_PCF8583 = YES
endif

## Check if it's selected all libs inclusion
ifeq ($(findstring __BUILD_ALL_LIBS__,$(EEOPT)) , __BUILD_ALL_LIBS__)
INCLUDE_PCF8583 = YES
endif

## If the library is required
ifeq ($(INCLUDE_PCF8583), YES)

##
## Library code
##

## Add the inc path to the include pathlist
ifeq ($(findstring __RTD_CYGWIN__,$(EEOPT)), __RTD_CYGWIN__) 
ALLINCPATH += -I"$(shell cygpath -w $(EEBASE)/contrib/drivers/miscellaneous/pcf8583/inc)"
else
ALLINCPATH += -I$(EEBASE)/contrib/drivers/miscellaneous/pcf8583/inc
endif
INCLUDE_PATH += $(EEBASE)/contrib/drivers/miscellaneous/pcf8583/inc

## Add each file individually
EE_SRCS_PCF8583 +=

## If the file list is not empty, create the library
ifneq ($(EE_SRCS_PCF8583),)

EE_OBJS_PCF8583 := $(addprefix $(OBJDIR)/, $(patsubst %.c,%.o,$(patsubst %.S,%.o, $(EE_SRCS_PCF8583))))

LIBSRCS += $(EE_SRCS_PCF8583)

libpcf8583.a: $(EE_OBJS_PCF8583)
	@echo $(EE_SRC_PCF8583)
	@printf "AR  libpcf8583.a\n" ;
	$(QUIET)$(EE_AR) rs libpcf8583.a $(EE_OBJS_PCF8583)

##
## Add the library to the linker list and list of lib files
##
OPT_LIBS += -pcf8583
ALL_LIBS += libpcf8583.a

endif

endif
