## Author: 2009 Gianluca Franchino

## Check the MiWiP2P library selection
ifeq ($(findstring __LIB_MIWIP2P__,$(LIB_OPT)) , __LIB_MIWIP2P__)
INCLUDE_MIWIP2P = YES
endif

## Check if it's selected all libs inclusion
ifeq ($(findstring __BUILD_ALL_LIBS__,$(EEOPT)) , __BUILD_ALL_LIBS__)
INCLUDE_MIWIP2P = YES
endif

##
## If the library is required
##
ifeq ($(INCLUDE_MIWIP2P), YES)

##
## Library code
##

## Add the inc path to the include pathlist
ALLINCPATH += -I"$(shell cygpath -w $(EEBASE)/contrib/MiWiP2P/inc)"

## Add each file individually
EE_SRCS_MIWIP2P +=

## If the file list is not empty, create the console lib
ifneq ($(EE_SRCS_MIWIP2P),)

EE_OBJS_MIWIP2P := $(addprefix $(OBJDIR)/, $(patsubst %.c,%.o,$(patsubst %.S,%.o, $(EE_SRCS_MIWIP2P))))

LIBSRCS += $(EE_SRCS_MIWIP2P)

libmiwip2p.a: $(EE_OBJS_MIWIP2P)
	@echo $(EE_SRC_MIWIP2P)
	@printf "AR  libmiwip2p.a\n" ;
	$(QUIET)$(EE_AR) rs libmiwip2p.a $(EE_OBJS_MIWIP2P)

##
## Add the library to the linker list and list of lib files
##
OPT_LIBS += -lmiwip2p
ALL_LIBS += libmiwip2p.a

endif

endif
