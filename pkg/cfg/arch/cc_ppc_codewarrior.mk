# ###*B*###
# ERIKA Enterprise - a tiny RTOS for small microcontrollers

# Copyright (C) 2002-2011  Evidence Srl

# This file is part of ERIKA Enterprise.

# ERIKA Enterprise is free software; you can redistribute it
# and/or modify it under the terms of the GNU General Public License
# version 2 as published by the Free Software Foundation,
# (with a special exception described below).

# Linking this code statically or dynamically with other modules is
# making a combined work based on this code.  Thus, the terms and
# conditions of the GNU General Public License cover the whole
# combination.

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

# ERIKA Enterprise is distributed in the hope that it will be
# useful, but WITHOUT ANY WARRANTY; without even the implied warranty
# of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License version 2 for more details.

# You should have received a copy of the GNU General Public License
# version 2 along with ERIKA Enterprise; if not, write to the
# Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
# Boston, MA 02110-1301 USA.
# ###*E*###

##
## Freescale (CodeWarrior) compiler for PPC
## Author: 2011 Bernardo  Dal Seno
##

# BINDIR is the directory of assembler, compiler, linker...
MCUToolsBaseDirEnv ?= $(PPC_CW_BASEDIR)
CW_SUPPORTDIR = $(MCUToolsBaseDirEnv)/PA_Support
ifeq ($(call iseeopt, __RTD_CYGWIN__), yes)
CW_TOOLSDIR = $(MCUToolsBaseDirEnv)/PowerPC_EABI_Tools
else # RTD_CYGWIN
CW_TOOLSDIR = $(MCUToolsBaseDirEnv)/PA_Tools
endif # else RTD_CYGWIN
BINDIR = $(CW_TOOLSDIR)/Command_Line_Tools/
MWCIncludes ?= $(CW_SUPPORTDIR)/ewl/EWL_C/include
MWLibraries ?= $(CW_SUPPORTDIR)/ewl/lib
ifeq ($(call iseeopt, __PPCE200Z0__), yes)
MW_LIB_FLAVOR = _E200z0_VLE
else
ifeq ($(or $(call iseeopt, __PPCE200Z6__), $(call iseeopt, __PPCE200Z7__)), yes)
MW_LIB_FLAVOR = _E200z650
endif
ifndef MW_LIB_FLAVOR
$(error CPU unsupported by know CodeWarrior libraries)
endif
ifeq ($(call iseeopt, __VLE__), yes)
MW_LIB_FLAVOR := $(MW_LIB_FLAVOR)_VLE
endif
endif # PPCE200Z0
# Apparently, libc_XXX works on Windows, librt_XXX on Linux
ifeq ($(call iseeopt, __RTD_CYGWIN__), yes)
MW_LIBS = $(addsuffix $(MW_LIB_FLAVOR), c m)
else
MW_LIBS = $(addsuffix $(MW_LIB_FLAVOR), rt m)
endif


# Compilers
EE_LINK = $(BINDIR)mwldeppc
EE_ASM = $(BINDIR)mwasmeppc
EE_CC = $(BINDIR)mwcceppc
EE_AR = $(EE_LINK)

INCLUDE_PATH += $(MWCIncludes)
OPT_INCLUDE = $(foreach d,$(INCLUDE_PATH),$(addprefix -I,$(call native_path,$d)))

OPT_TARGET := -proc Zen
# Defaults:
# -abi eabi -model absolute -fp soft -big
ifeq ($(call iseeopt, __VLE__), yes)
VLE_OPT = -vle
OPT_CC += -ppc_asm_to_vle
else
VLE_OPT =
endif

## Candidate OPT_CC
OPT_CC = $(CFLAGS) $(OPT_TARGET) $(VLE_OPT) -use_lmw_stmw on -RTTI off \
 -Cpp_exceptions off -flag require_prototypes -msgstyle gcc -gccinc \
 -char unsigned -nostdinc -rostr -O4 -ipa file -inline on,auto -schedule on \
 -pragma "section RW \".stack\" \".ustack\""

## OPT_ASM are the options for asm invocation
OPT_ASM += $(OPT_TARGET) $(VLE_OPT) -msgstyle gcc -gccinc -gnu_mode

# OPT_LINK represents the options for ld invocation
LINK_SCRIPT = loc_codewarrior.lcf
OPT_LINK += $(OPT_TARGET) -L$(call native_path,$(MWLibraries))
OPT_LINK += $(addprefix -l, $(MW_LIBS))
OPT_LINK += -lcf $(LINK_SCRIPT) -msgstyle gcc -nostdlib -char unsigned
LINKDEP = $(LINK_SCRIPT)
MAP_OPT = -map $(native_path $(MAP_FILE))

ifeq ($(call iseeopt, __DEFAULT_LD_SCRIPT__), yes)
$(error "EEOPT __DEFAULT_LD_SCRIPT__ not supported")
endif

ifneq ($(call iseeopt, __BIN_DISTR), yes)
ifeq ($(call iseeopt, DEBUG), yes)
OPT_CC += -g
OPT_ASM += -g
OPT_LINK += -g
endif
endif


# OPT_AR: options for library generation
OPT_AR = -library -o

DEFS_ASM = $(addprefix -D, $(EEOPT) )
DEFS_CC  = $(addprefix -D, $(EEOPT) )

# Automatic dependency generation
ifeq ($(call iseeopt, NODEPS), yes)
DEPENDENCY_OPT = 
make-depend =
else # NODEPS
ifeq ($(call iseeopt, __RTD_CYGWIN__), yes)
# Create dependency for all headers, and add a target for each header
DEPENDENCY_OPT = -MDfile $(call native_path,$(subst .o,.d_tmp,$@))
# Dependencies on Windows need path translation
make-depend = sed -e 's_\\\(.\)_/\1_g' -e 's_\<\([a-zA-Z]\):/_/cygdrive/\l\1/_g' < $3_tmp > $3 && rm $3_tmp
else # __RTD_CYGWIN__
# Create dependency for all headers, and add a target for each header
DEPENDENCY_OPT = -MDfile $(subst .o,.d_tmp,$@)
#-gccdep ??
make-depend = mv $3_tmp $3
endif # __RTD_CYGWIN__
endif # NODEPS
