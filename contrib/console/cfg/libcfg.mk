## Author: 2007 Mauro Marinoni

## Check the Console library selection
ifeq ($(findstring __LIB_CONSOLE__,$(LIB_OPT)) , __LIB_CONSOLE__)
INCLUDE_CONSOLE = YES
endif

## Check if it's selected all libs inclusion
ifeq ($(call iseeopt, __BUILD_ALL_LIBS__), yes)
INCLUDE_CONSOLE = YES
endif

##
## If the library is required
##
ifeq ($(INCLUDE_CONSOLE), YES)

##
## Library code
##

## Add the inc path to the include pathlist
ifeq ($(call iseeopt, __COSMIC__), yes)
ALLINCPATH += -i"$(shell cygpath -w $(EEBASE)/contrib/console/inc)"
else
ifeq ($(call iseeopt, __RTD_CYGWIN__), yes) 
ALLINCPATH += -I"$(shell cygpath -w $(EEBASE)/contrib/console/inc)"
else
ALLINCPATH += -I$(EEBASE)/contrib/console/inc
endif
endif
INCLUDE_PATH += $(EEBASE)/contrib/console/inc

## Add each file individually
#EE_SRCS_CONSOLE += contrib/console/libsrc/libconsole.c
EE_SRCS_CONSOLE +=

## If the file list is not empty, create the console lib
ifneq ($(EE_SRCS_CONSOLE),)
EE_OBJS_CONSOLE := $(addprefix $(OBJDIR)/, $(patsubst %.c,%.o,$(patsubst %.S,%.o, $(EE_SRCS_CONSOLE))))
LIBSRCS += $(EE_SRCS_CONSOLE)
libconsole.a: $(EE_OBJS_CONSOLE)
	@echo $(EE_SRC_CONSOLE)
	@printf "AR  libconsole.a\n" ;
	$(QUIET)$(EE_AR) rs libconsole.a $(EE_OBJS_CONSOLE)
##
## Add the library to the linker list and list of lib files
##
OPT_LIBS += -lconsole
ALL_LIBS += libconsole.a
endif

endif
