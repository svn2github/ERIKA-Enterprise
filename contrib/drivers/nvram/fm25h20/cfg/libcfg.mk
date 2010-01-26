## Author: 2010 Christian Nastasi

## Check the FM25H20 library selection
ifeq ($(findstring __LIB_FM25H20__,$(LIB_OPT)) , __LIB_FM25H20__)
INCLUDE_FM25H20 = YES
endif

## Check if it's selected all libs inclusion
ifeq ($(findstring __BUILD_ALL_LIBS__,$(EEOPT)) , __BUILD_ALL_LIBS__)
INCLUDE_FM25H20 = YES
endif

## If the library is required
ifeq ($(INCLUDE_FM25H20), YES)

##
## Library code
##

## Add the inc path to the include pathlist
ifeq ($(findstring __RTD_CYGWIN__,$(EEOPT)), __RTD_CYGWIN__) 
ALLINCPATH += -I"$(shell cygpath -w $(EEBASE)/contrib/drivers/nvram/fm25h20/inc)"
else
ALLINCPATH += -I$(EEBASE)/contrib/drivers/nvram/fm25h20/inc
endif

## Add each file individually
#EE_SRCS_FM25H20 += contrib/drivers/nvram/fm25h20/libsrc/libfm25h20.c
EE_SRCS_FM25H20 +=

## If the file list is not empty, create the library
ifneq ($(EE_SRCS_FM25H20),)

EE_OBJS_FM25H20 := $(addprefix $(OBJDIR)/, $(patsubst %.c,%.o,$(patsubst %.S,%.o, $(EE_SRCS_FM25H20))))

LIBSRCS += $(EE_SRCS_FM25H20)

libfm25h20.a: $(EE_OBJS_FM25H20)
	@echo $(EE_SRC_FM25H20)
	@printf "AR  libfm25h20.a\n" ;
	$(QUIET)$(EE_AR) rs libfm25h20.a $(EE_OBJS_FM25H20)

##
## Add the library to the linker list and list of lib files
##
OPT_LIBS += -lfm25h20
ALL_LIBS += libfm25h20.a

endif

endif
