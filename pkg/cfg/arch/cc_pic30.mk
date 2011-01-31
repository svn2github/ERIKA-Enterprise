# ###*B*###
# ERIKA Enterprise - a tiny RTOS for small microcontrollers
# 
# Copyright (C) 2002-2008  Evidence Srl
# 
# This file is part of ERIKA Enterprise.
# 
# ERIKA Enterprise is free software; you can redistribute it
# and/or modify it under the terms of the GNU General Public License
# version 2 as published by the Free Software Foundation, 
# (with a special exception described below).
# 
# Linking this code statically or dynamically with other modules is
# making a combined work based on this code.  Thus, the terms and
# conditions of the GNU General Public License cover the whole
# combination.
# 
# As a special exception, the copyright holders of this library give you
# permission to link this code with independent modules to produce an
# executable, regardless of the license terms of these independent
# modules, and to copy and distribute the resulting executable under
# terms of your choice, provided that you also meet, for each linked
# independent module, the terms and conditions of the license of that
# module.  An independent module is a module which is not derived from
# or based on this library.  If you modify this code, you may extend
# this exception to your version of the code, but you are not
# obligated to do so.  If you do not wish to do so, delete this
# exception statement from your version.
# 
# ERIKA Enterprise is distributed in the hope that it will be
# useful, but WITHOUT ANY WARRANTY; without even the implied warranty
# of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License version 2 for more details.
# 
# You should have received a copy of the GNU General Public License
# version 2 along with ERIKA Enterprise; if not, write to the
# Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
# Boston, MA 02110-1301 USA.
# ###*E*###

##
## PIC30 GCC compiler version 3.3 dsPIC30, Microchip 1.32
##

ifeq ($(call iseeopt, __PIC30__), yes)

# Select object file format
# IMPORTANT NOTE:
# Due to a bug in MPLAB IDE, debug symbols are only supported in COFF
PIC30_OFF := coff
PIC30_EXTENSION := cof

# Prefix for GCC tools (prefix for deps below)
PIC30_GCCPREFIX := pic30-$(PIC30_OFF)-

# Bin install directories of the various compilers
# BINDIR_C30   - Microchip C30 binary directory (includes both ASM30 and C30)
# BINDIR_ASM30 - Microchip ASM30 installed with MPLAB IDE
# BINDIR_CYG   - Cygwin gcc
# BINDIR_EVI   - C30 compiler compiled from Microchip gcc source code

BINDIR_EVI := $(PIC30_GCCDIR)/bin/bin
BINDIR_CYG := /usr/bin

# If Linux, force recompiled gcc usage

ifeq ($(call iseeopt, __RTD_LINUX__), yes) 
PIC30_USE_EEGCC_COMPILE := Y
endif
ifeq ($(call iseeopt, __RTD_CYGWIN__), yes) 
ifeq ($(wildcard $(PIC30_GCCDIR)/bin/bin),)
BINDIR_C30   := $(PIC30_GCCDIR)/bin
else
BINDIR_C30   := $(PIC30_GCCDIR)/bin/bin
endif
endif

# Make sure that the variable TEMP is defined on Cygwin/Windows.
# This is needed on some Cygwin installations, where both TEMP and TMP
# variables are unset inside ".bashrc".  A reasonable default is chosen
# after a check for the existence of the directory.
ifeq ($(call iseeopt, __RTD_CYGWIN__), yes)
ifndef TMP
ifndef TEMP
ifneq (ok,$(shell test -d "/tmp" && echo ok ))
$(error Environment variables TMP and TEMP are unset, and Cygwin /tmp directory does not exist)
endif
export TEMP = $(shell cygpath -ws /tmp)
endif
endif
endif

#BINDIR_ASM30 := $(PIC30_ASMDIR)/bin
#BINDIR_CYG   := /usr/bin
#BINDIR_EVI   := 

# Bin directories used for compilation
# BINDIR_ASM      - directory of the Assembler
# BINDIR_CC       - directory of the C compiler
# BINDIR_DEP      - directory of the C compiler used for dependencies
# BINDIR_BINUTILS - directory of the binutils

# If Linux always first branch

ifeq ($(PIC30_USE_EEGCC_COMPILE), Y)
BINDIR_ASM      := $(BINDIR_EVI)
BINDIR_CC       := $(BINDIR_EVI)
BINDIR_BINUTILS := $(BINDIR_EVI)
else
BINDIR_ASM      := $(BINDIR_C30)
BINDIR_CC       := $(BINDIR_C30)
BINDIR_BINUTILS := $(BINDIR_C30)
endif

ifeq ($(PIC30_USE_EEGCC_DEPS), Y)
BINDIR_DEP := $(BINDIR_EVI)
PIC30_DEPPREFIX := pic30-$(PIC30_OFF)-
else
BINDIR_DEP := $(BINDIR_CYG)
PIC30_DEPPREFIX :=
endif

ifndef EE_LINK
EE_LINK:=$(BINDIR_BINUTILS)/$(PIC30_GCCPREFIX)ld
endif

ifndef EE_ASM
EE_ASM:=$(BINDIR_ASM)/$(PIC30_GCCPREFIX)as
endif

ifndef EE_CC
EE_CC:=$(BINDIR_CC)/$(PIC30_GCCPREFIX)gcc
endif

ifndef EE_DEP
EE_DEP:=$(BINDIR_DEP)/$(PIC30_DEPPREFIX)gcc
endif

ifndef EE_AR
EE_AR:=$(BINDIR_BINUTILS)/$(PIC30_GCCPREFIX)ar
endif

ifndef EE_NM
EE_NM:=$(BINDIR_BINUTILS)/$(PIC30_GCCPREFIX)nm
endif

ifndef EE_OBJCOPY
EE_OBJCOPY:=$(BINDIR_BINUTILS)/$(PIC30_GCCPREFIX)objcopy
endif

ifndef EE_OBJDUMP
EE_OBJDUMP:=$(BINDIR_BINUTILS)/$(PIC30_GCCPREFIX)objdump
endif

# ALLINCPATH is a colon separated list of directories for source file searching
# -I = adds directories to the source file search path (for both gcc and gas)
# we consider the ee pkg directory and the application dir
# we also consider the current directory because the app could be compiled
# from the config files generated from eclipse...
# please note the final backslash sequence after the shell command to
# avoid cygpath insering a trailing backslash
# INTERNAL_PKGBASEDIR is used to avoid multiple calls to cygpath
ifeq ($(findstring __RTD_CYGWIN__,$(EEOPT)), __RTD_CYGWIN__) 
INTERNAL_PKGBASEDIR := -I"$(shell cygpath -w $(PKGBASE))\\." -I"$(shell cygpath -w $(APPBASE))\\." -I.
else
INTERNAL_PKGBASEDIR := -I$(PKGBASE) -I$(APPBASE) -I.
endif
ALLINCPATH += $(INTERNAL_PKGBASEDIR)

## OPT_CC are the options for arm compiler invocation
OPT_CC = -O2 -Wall -Winline
ifeq ($(call iseeopt, DEBUG), yes)
OPT_CC += -ggdb
endif
# Specific option from the application makefile
OPT_CC += $(CFLAGS)

OPT_CC_DEPS := $(OPT_CC)

# target type, not used for dependencies if the Cygwin GCC is used
ifneq ($(PIC30_MODEL),)
OPT_CC += -mcpu=$(PIC30_MODEL)

ifeq ($(PIC30_USE_EEGCC_DEPS), Y)
OPT_CC_DEPS += -mcpu=$(PIC30_MODEL)
else
OPT_CC_DEPS += -D__dsPIC$(PIC30_MODEL)__
endif
endif

# #OPT_ASM are the options for asm invocation
OPT_ASM = -Ifrommchp
#ifeq ($(call iseeopt, DEBUG), yes)
#OPT_ASM += --gstabs
#endif
# Specific option from the application makefile
OPT_ASM += $(ASFLAGS)

## OPT_LINK represents the options for armlink invocation
OPT_LINK = 
# Specific option from the application makefile
OPT_LINK += $(LDFLAGS)

# Defining EEOPT Macros
# Each identifier that is listed in EEOPT is also inserted as a 
# command-line macro in the compiler...

DEFS_ASM = $(addprefix -D, $(EEOPT) )
DEFS_CC  = $(addprefix -D, $(EEOPT) )

ifeq ($(call iseeopt, __BIN_DISTR), yes) 
# Note: the defines used in EEOPT to compile the library
# are already added in the eecfg.h
DEFS_ASM += -D__CONFIG_$(EELIB)__
DEFS_CC  += -D__CONFIG_$(EELIB)__
endif

endif
