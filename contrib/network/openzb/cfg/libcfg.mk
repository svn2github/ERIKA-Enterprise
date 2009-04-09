## Author: 2007 Mauro Marinoni

## Check the Console library selection
ifeq ($(findstring __LIB_OPENZB__,$(LIB_OPT)) , __LIB_OPENZB__)
INCLUDE_OPENZB = YES
endif

## Check if it's selected all libs inclusion
ifeq ($(findstring __BUILD_ALL_LIBS__,$(EEOPT)) , __BUILD_ALL_LIBS__)
INCLUDE_OPENZB = YES
endif

##
## If the library is required
##
ifeq ($(INCLUDE_OPENZB), YES)

##
## Library code
##

## Add the inc path to the include pathlist
ALLINCPATH += -I"$(shell cygpath -w $(EEBASE)/contrib/network/openzb/inc)"

## Add each file individually
#EE_SRCS_OPENZB += contrib/network/libsrc/libopenzb.c
EE_SRCS_OPENZB +=

## If the file list is not empty, create the console lib
ifneq ($(EE_SRCS_OPENZB),)

EE_OBJS_OPENZB := $(addprefix $(OBJDIR)/, $(patsubst %.c,%.o,$(patsubst %.S,%.o, $(EE_SRCS_OPENZB))))

LIBSRCS += $(EE_SRCS_OPENZB)

libopenzb.a: $(EE_OBJS_OPENZB)
	@echo $(EE_SRC_OPENZB)
	@printf "AR  libopenzb.a\n" ;
	$(QUIET)$(EE_AR) rs libopenzb.a $(EE_OBJS_OPENZB)

##
## Add the library to the linker list and list of lib files
##
OPT_LIBS += -lopenzb
ALL_LIBS += libopenzb.a

endif

endif
