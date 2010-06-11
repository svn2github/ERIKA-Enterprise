## Author: 2010 Dario Di Stefano

## Check the Console library selection
ifeq ($(findstring __LIB_LWIP__,$(LIB_OPT)),__LIB_LWIP__)
INCLUDE_LWIP = YES
endif

## Check if it's selected all libs inclusion
ifeq ($(findstring __BUILD_ALL_LIBS__,$(EEOPT)) , __BUILD_ALL_LIBS__)
INCLUDE_LWIP = YES
endif

##
## If the library is required
##
ifeq ($(INCLUDE_LWIP), YES)

##
## Library code
##

## Add the inc path to the include pathlist
ifeq ($(findstring __RTD_CYGWIN__,$(EEOPT)), __RTD_CYGWIN__) 
ALLINCPATH += -I"$(shell cygpath -w $(EEBASE)/contrib/lwip/lwip_1_3_2/src/include)"
ALLINCPATH += -I"$(shell cygpath -w $(EEBASE)/contrib/lwip/lwip_1_3_2/src/include/ipv4)"
ALLINCPATH += -I"$(shell cygpath -w $(EEBASE)/contrib/lwip/lwip_1_3_2/abstraction/inc)"
else
ALLINCPATH += -I$(EEBASE)/contrib/lwip/lwip_1_3_2/src/include
ALLINCPATH += -I$(EEBASE)/contrib/lwip/lwip_1_3_2/src/include/ipv4
ALLINCPATH += -I$(EEBASE)/contrib/lwip/lwip_1_3_2/abstraction/inc
endif
INCLUDE_PATH += $(EEBASE)/contrib/lwip/lwip_1_3_2/src/include
INCLUDE_PATH += $(EEBASE)/contrib/lwip/lwip_1_3_2/src/include/ipv4
INCLUDE_PATH += $(EEBASE)/contrib/lwip/lwip_1_3_2/abstraction/inc

## Add each file individually
EE_SRCS_LWIP +=

## If the file list is not empty, create the console lib
ifneq ($(EE_SRCS_LWIP),)

EE_OBJS_LWIP := $(addprefix $(OBJDIR)/, $(patsubst %.c,%.o,$(patsubst %.S,%.o, $(EE_SRCS_LWIP))))

LIBSRCS += $(EE_SRCS_LWIP)

liblwip.a: $(EE_OBJS_LWIP)
	@echo $(EE_SRC_LWIP)
	@printf "AR  liblwip.a\n" ;
	$(QUIET)$(EE_AR) rs liblwip.a $(EE_OBJS_LWIP)

##
## Add the library to the linker list and list of lib files
##
OPT_LIBS += -llwip
ALL_LIBS += liblwip.a

endif

endif
