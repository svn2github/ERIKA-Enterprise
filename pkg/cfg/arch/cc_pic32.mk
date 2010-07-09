ifeq ($(findstring __PIC32__,$(EEALLOPT)), __PIC32__)

PIC32_EXTENSION := elf
PIC32_GCCPREFIX := pic32-

BINDIR_CYG := /usr/bin
BINDIR_C32   := $(PIC32_GCCDIR)/bin

BINDIR_ASM      := $(BINDIR_C32)
BINDIR_CC       := $(BINDIR_C32)
BINDIR_BINUTILS := $(BINDIR_C32)

BINDIR_DEP := $(BINDIR_CYG)
PIC32_DEPPREFIX :=

ifndef EE_LINK
EE_LINK:=$(BINDIR_BINUTILS)/$(PIC32_GCCPREFIX)gcc
#EE_LINK:=$(BINDIR_BINUTILS)/$(PIC32_GCCPREFIX)ld
endif

ifndef EE_ASM
EE_ASM:=$(BINDIR_ASM)/$(PIC32_GCCPREFIX)as
endif

ifndef EE_CC
EE_CC:=$(BINDIR_CC)/$(PIC32_GCCPREFIX)gcc
endif

ifndef EE_DEP
EE_DEP:=$(BINDIR_DEP)/$(PIC32_DEPPREFIX)gcc
endif

ifndef EE_AR
EE_AR:=$(BINDIR_BINUTILS)/$(PIC32_GCCPREFIX)ar
endif

ifndef EE_NM
EE_NM:=$(BINDIR_BINUTILS)/$(PIC32_GCCPREFIX)nm
endif

ifndef EE_OBJCOPY
EE_OBJCOPY:=$(BINDIR_BINUTILS)/$(PIC32_GCCPREFIX)objcopy
endif

ifndef EE_OBJDUMP
EE_OBJDUMP:=$(BINDIR_BINUTILS)/$(PIC32_GCCPREFIX)objdump
endif

ifndef EE_BIN2HEX
EE_BIN2HEX:=$(BINDIR_BINUTILS)/$(PIC32_GCCPREFIX)bin2hex
endif

ifeq ($(findstring __RTD_LINUX__,$(EEOPT)) , __RTD_LINUX__)
INTERNAL_PKGBASEDIR := -I$(PKGBASE) -I$(APPBASE) -I.
else
INTERNAL_PKGBASEDIR := -I"$(shell cygpath -w $(PKGBASE))\\." -I"$(shell cygpath -w $(APPBASE))\\." -I.
endif
ALLINCPATH += $(INTERNAL_PKGBASEDIR)

## OPT_CC are the options for compiler invocation
OPT_CC = -O2 -Wall -Winline -x c
ifeq ($(findstring DEBUG,$(EEOPT)) , DEBUG)
OPT_CC += -ggdb 
endif
# Specific option from the application makefile
OPT_CC += $(CFLAGS)

OPT_CC_DEPS := $(OPT_CC) -D__LANGUAGE_C__ 

# target type, not used for dependencies if the Cygwin GCC is used
ifneq ($(PIC32_MODEL),)
OPT_CC += -mprocessor=$(PIC32_MODEL)
endif

# #OPT_ASM are the options for asm invocation
OPT_ASM = -Ifrommchp
#ifeq ($(findstring DEBUG,$(EEOPT)) , DEBUG)
#OPT_ASM += --gstabs
#endif
# Specific option from the application makefile
OPT_ASM += $(ASFLAGS)

## OPT_LINK represents the options for armlink invocation
OPT_LINK = 
# Specific option from the application makefile
OPT_LINK += $(LDFLAGS)
ifeq ($(findstring DEBUG,$(EEOPT)) , DEBUG)
OPT_LINK += -mdebugger
endif

# Defining EEOPT Macros
# Each identifier that is listed in EEOPT is also inserted as a 
# command-line macro in the compiler...

# MUST be EEOPT, not EEALLOPT!!!
#DEFS_ASM = $(addprefix -D, $(EEOPT) )
#DEFS_CC  = $(addprefix -D, $(EEOPT) )
# NOTE: the pic32 processors include files define the DEBUG symbol as register
#       name, thus we CANNOT pass -DDEBUG from the compiler command line
#       TODO: maybe we should do the same for all the architectures by simply
#             renaming all DEBUG in the ERIKA tree with EE_DEBUG and adapting
#             the RT-Druid. Do the same with VERBOSE?
DEFS_ASM = $(addprefix -D, $(patsubst DEBUG, EE_DEBUG, $(EEOPT)))
DEFS_CC  = $(addprefix -D, $(patsubst DEBUG, EE_DEBUG, $(EEOPT)))

ifeq ($(findstring __BIN_DISTR,$(EEOPT)), __BIN_DISTR) 
# Note: the defines used in EEOPT to compile the library
# are already added in the eecfg.h
DEFS_ASM += -D__CONFIG_$(EELIB)__
DEFS_CC  += -D__CONFIG_$(EELIB)__
endif

endif
