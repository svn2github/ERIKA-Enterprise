## Author: 2010 Christian Nastasi

## Check the FM25H20 library selection
ifeq ($(findstring __LIB_TSL2561T__,$(LIB_OPT)) , __LIB_TSL2561T__)
INCLUDE_TSL2561T = YES
endif

## Check if it's selected all libs inclusion
ifeq ($(findstring __BUILD_ALL_LIBS__,$(EEOPT)) , __BUILD_ALL_LIBS__)
INCLUDE_TSL2561T = YES
endif

## If the library is required
ifeq ($(INCLUDE_TSL2561T), YES)

##
## Library code
##

## Add the inc path to the include pathlist
ifeq ($(findstring __RTD_CYGWIN__,$(EEOPT)), __RTD_CYGWIN__) 
ALLINCPATH += -I"$(shell cygpath -w $(EEBASE)/contrib/drivers/miscellaneous/tsl2561t/inc)"
else
ALLINCPATH += -I$(EEBASE)/contrib/drivers/miscellaneous/tsl2561t/inc
endif
INCLUDE_PATH += $(EEBASE)/contrib/drivers/miscellaneous/tsl2561t/inc

## Add each file individually
EE_SRCS_TSL2561T +=

## If the file list is not empty, create the library
ifneq ($(EE_SRCS_TSL2561T),)

EE_OBJS_FM25H20 := $(addprefix $(OBJDIR)/, $(patsubst %.c,%.o,$(patsubst %.S,%.o, $(EE_SRCS_TSL2561T))))

LIBSRCS += $(EE_SRCS_TSL2561T)

libfm25h20.a: $(EE_OBJS_TSL2561T)
	@echo $(EE_SRC_TSL2561T)
	@printf "AR  libtsl2561t.a\n" ;
	$(QUIET)$(EE_AR) rs libtsl2561t.a $(EE_OBJS_TSL2561T)

##
## Add the library to the linker list and list of lib files
##
OPT_LIBS += -ltsl2561t
ALL_LIBS += libtsl2561t.a

endif

endif
