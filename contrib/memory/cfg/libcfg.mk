## Check the Console library selection
ifeq ($(findstring __LIB_MEMORY__,$(LIB_OPT)) , __LIB_MEMORY__)
INCLUDE_MEMORY = YES
endif

## Check if it's selected all libs inclusion
ifeq ($(findstring __BUILD_ALL_LIBS__,$(EEOPT)) , __BUILD_ALL_LIBS__)
INCLUDE_MEMORY = YES
endif

##
## If the library is required
##
ifeq ($(INCLUDE_MEMORY), YES)

##
## Library code
##

## Add the inc path to the include pathlist
ALLINCPATH += -I"$(shell cygpath -w $(EEBASE)/contrib/memory/inc)"
## Add each file individually
#EE_SRCS_MEMORY += contrib/memory/libsrc/cqueue.c
EE_SRCS_MEMORY += contrib/memory/libsrc/list.c

## If the file list is not empty, create the memory lib
ifneq ($(EE_SRCS_MEMORY),)
EE_OBJS_MEMORY := $(addprefix $(OBJDIR)/, $(patsubst %.c,%.o,$(patsubst %.S,%.o, $(EE_SRCS_MEMORY))))
LIBSRCS += $(EE_SRCS_MEMORY)

libmemory.a: $(EE_OBJS_MEMORY)
	@echo $(EE_SRC_MEMORY)
	@printf "AR  libmemory.a\n" ;
	$(QUIET)$(EE_AR) rs libmemory.a $(EE_OBJS_MEMORY)
##
## Add the library to the linker list and list of lib files
##
OPT_LIBS += -lmemory
ALL_LIBS += libmemory.a

endif

endif
