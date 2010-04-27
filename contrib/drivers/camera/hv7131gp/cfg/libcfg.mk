## Author: 2009 Mauro Marinoni

## Check the MRF24J40 library selection
ifeq ($(findstring __LIB_HV7131GP__,$(LIB_OPT)) , __LIB_HV7131GP__)
INCLUDE_HV7131GP = YES
endif

## Check if it's selected all libs inclusion
ifeq ($(findstring __BUILD_ALL_LIBS__,$(EEOPT)) , __BUILD_ALL_LIBS__)
INCLUDE_HV7131GP = YES
endif

##
## If the library is required
##
ifeq ($(INCLUDE_HV7131GP), YES)

##
## Library code
##

## Add the inc path to the include pathlist
ifeq ($(findstring __RTD_CYGWIN__,$(EEOPT)), __RTD_CYGWIN__) 
ALLINCPATH += -I"$(shell cygpath -w $(EEBASE)/contrib/drivers/camera/hv7131gp/inc)"
else
ALLINCPATH += -I$(EEBASE)/contrib/drivers/camera/hv7131gp/inc
endif
INCLUDE_PATH += $(EEBASE)/contrib/drivers/camera/hv7131gp/inc

## Add each file individually
EE_SRCS_HV7131GP +=

## If the file list is not empty, create the console lib
ifneq ($(EE_SRCS_HV7131GP),)

EE_OBJS_HV7131GP := $(addprefix $(OBJDIR)/, $(patsubst %.c,%.o,$(patsubst %.S,%.o, $(EE_SRCS_HV7131GP))))

LIBSRCS += $(EE_SRCS_HV7131GP)

libmrf24j40.a: $(EE_OBJS_HV7131GP)
	@echo $(EE_SRC_HV7131GP)
	@printf "AR  hv7131gp.a\n" ;
	$(QUIET)$(EE_AR) rs libhv7131gp.a $(EE_OBJS_HV7131GP)

##
## Add the library to the linker list and list of lib files
##
OPT_LIBS += -lhv7131gp
ALL_LIBS += libhv7131gp.a

endif

endif
