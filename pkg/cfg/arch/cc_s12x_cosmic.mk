# ###*B*###
# ERIKA Enterprise - a tiny RTOS for small microcontrollers
# 
# Copyright (C) 2009  Evidence Srl
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
## Cosmic compiler
##

ifeq ($(findstring __HCS12XS__,$(EEALLOPT)), __HCS12XS__)

# Select object file format
COSMIC_EXTENSION := xs12

BINDIR_COSMIC   := $(COSMIC_CCDIR)

# Bin directories used for compilation
# BINDIR_ASM      - directory of the Assembler
# BINDIR_CC       - directory of the C compiler
# BINDIR_DEP      - directory of the C compiler used for dependencies
# BINDIR_BINUTILS - directory of the binutils

BINDIR_ASM      := $(BINDIR_COSMIC)
BINDIR_CC       := $(BINDIR_COSMIC)
BINDIR_BINUTILS := $(BINDIR_COSMIC)
BINDIR_DEP      := $(BINDIR_COSMIC)

ifndef EE_LINK
EE_LINK:=$(BINDIR_BINUTILS)/clnk.exe
endif

ifndef EE_ASM
EE_ASM:=$(BINDIR_ASM)/cas12x.exe
endif

ifndef EE_CC
EE_CC:=$(BINDIR_CC)/cxs12x.exe
endif

ifndef EE_DEP
EE_DEP:=$(BINDIR_DEP)/cxs12x.exe
endif

ifndef EE_AR
EE_AR:=$(BINDIR_BINUTILS)/clib.exe
endif

ifndef EE_CVDWARF
EE_CVDWARF:=$(BINDIR_BINUTILS)/cvdwarf.exe
endif

#ifndef EE_OBJCOPY
#EE_OBJCOPY:=$(BINDIR_BINUTILS)/objcopy
#endif

ifndef EE_CLABS
EE_CLABS:=$(BINDIR_BINUTILS)/clabs.exe
endif

# ALLINCPATH is a colon separated list of directories for source file searching
# -I = adds directories to the source file search path (for both gcc and gas)
# we consider the ee pkg directory and the application dir
# we also consider the current directory because the app could be compiled
# from the config files generated from eclipse...
# please note the final backslash sequence after the shell command to
# avoid cygpath insering a trailing backslash
# INTERNAL_PKGBASEDIR is used to avoid multiple calls to cygpath

INTERNAL_PKGBASEDIR := -i"$(shell cygpath -w $(PKGBASE))\\." -i"$(shell cygpath -w $(APPBASE))\\." -i.

ALLINCPATH += $(INTERNAL_PKGBASEDIR)

## OPT_CC are the options for arm compiler invocation
OPT_CC = 
ifeq ($(findstring DEBUG,$(EEOPT)) , DEBUG)
OPT_CC += +debug
endif
# Specific option from the application makefile
OPT_CC += $(CFLAGS)

OPT_CC_DEPS := $(OPT_CC) -sm

# #OPT_ASM are the options for asm invocation
OPT_ASM = -i "fromcosmic"
ifeq ($(findstring DEBUG,$(EEOPT)) , DEBUG)
OPT_ASM += -xx -x
endif
# Specific option from the application makefile
OPT_ASM += $(ASFLAGS)

## OPT_LINK represents the options for armlink invocation
OPT_LINK = 
# Specific option from the application makefile
OPT_LINK += $(LDFLAGS)

# Defining EEOPT Macros
# Each identifier that is listed in EEOPT is also inserted as a 
# command-line macro in the compiler...

# MUST be EEOPT, not EEALLOPT!!!
DEFS_ASM = $(addprefix -d, $(EEOPT) )
DEFS_CC  = $(addprefix -d, $(EEOPT) )

endif
