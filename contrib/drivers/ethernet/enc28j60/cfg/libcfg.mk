## Author: 2010 Dario Di Stefano 

## Check the ENC28J60 library selection
ifeq ($(findstring __LIB_ENC28J60__,$(LIB_OPT)) , __LIB_ENC28J60__)
INCLUDE_ENC28J60 = YES
endif

## Check if it's selected all libs inclusion
ifeq ($(findstring __BUILD_ALL_LIBS__,$(EEOPT)) , __BUILD_ALL_LIBS__)
INCLUDE_ENC28J60 = YES
endif

##
## If the library is required
##
ifeq ($(INCLUDE_ENC28J60), YES)

##
## Library code
##

## Add the inc path to the include pathlist
ifeq ($(findstring __RTD_CYGWIN__,$(EEOPT)), __RTD_CYGWIN__) 
ALLINCPATH += -I"$(shell cygpath -w $(EEBASE)/contrib/drivers/ethernet/enc28j60/inc)"
else
ALLINCPATH += -I$(EEBASE)/contrib/drivers/ethernet/enc28j60/inc
endif
INCLUDE_PATH += $(EEBASE)/contrib/drivers/ethernet/enc28j60/inc

## Add each file individually
EE_SRCS_ENC28J60 +=

## If the file list is not empty, create the console lib
ifneq ($(EE_SRCS_ENC28J60),)

EE_OBJS_ENC28J60 := $(addprefix $(OBJDIR)/, $(patsubst %.c,%.o,$(patsubst %.S,%.o, $(EE_SRCS_ENC28J60))))

LIBSRCS += $(EE_SRCS_ENC28J60)

libenc28j60.a: $(EE_OBJS_ENC28J60)
	@echo $(EE_SRC_ENC28J60)
	@printf "AR  libenc28j60.a\n" ;
	$(QUIET)$(EE_AR) rs libenc28j60.a $(EE_OBJS_ENC28J60)

##
## Add the library to the linker list and list of lib files
##
OPT_LIBS += -lenc28j60
ALL_LIBS += libenc28j60.a

endif

endif
