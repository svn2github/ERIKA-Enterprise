## Author: 2010 Christian Nastasi

## Check the Console library selection
ifeq ($(findstring __LIB_UCV__,$(LIB_OPT)) , __LIB_UCV__)
INCLUDE_UCV = YES
endif

## Check if it's selected all libs inclusion
ifeq ($(findstring __BUILD_ALL_LIBS__,$(EEOPT)) , __BUILD_ALL_LIBS__)
INCLUDE_UCV = YES
endif

##
## If the library is required
##
ifeq ($(INCLUDE_UCV), YES)

##
## Library code
##

## Add the inc path to the include pathlist
ifeq ($(findstring __COSMIC__,$(EEOPT)), __COSMIC__)
ALLINCPATH += -i"$(shell cygpath -w $(EEBASE)/contrib/uCV/inc)"
else
ifeq ($(findstring __RTD_CYGWIN__,$(EEOPT)), __RTD_CYGWIN__) 
ALLINCPATH += -I"$(shell cygpath -w $(EEBASE)/contrib/uCV/inc)"
else
ALLINCPATH += -I$(EEBASE)/contrib/uCV/inc
endif
endif

## Add each file individually
#EE_SRCS_UCV += contrib/uCV/libsrc/libuCV.c
EE_SRCS_UCV +=

## If the file list is not empty, create the uCV lib
ifneq ($(EE_SRCS_UCV),)
EE_OBJS_UCV := $(addprefix $(OBJDIR)/, $(patsubst %.c,%.o,$(patsubst %.S,%.o, $(EE_SRCS_UCV))))
LIBSRCS += $(EE_SRCS_UCV)
libuCV.a: $(EE_OBJS_UCV)
	@echo $(EE_SRC_UCV)
	@printf "AR  libuCV.a\n" ;
	$(QUIET)$(EE_AR) rs libuCV.a $(EE_OBJS_UCV)
##
## Add the library to the linker list and list of lib files
##
OPT_LIBS += -luCV
ALL_LIBS += libuCV.a
endif

endif
