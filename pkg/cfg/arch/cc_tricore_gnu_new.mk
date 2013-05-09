# ###*B*###
# ERIKA Enterprise - a tiny RTOS for small microcontrollers
# 
# Copyright (C) 2002-2012  Evidence Srl
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
## Author: 2012,  Errico Guidieri
## Modified: 2012 Francesco Esposito (added Lin support)
##


##
## TRICORE_GNU GCC compiler version 4
## This file has been generated for HIGHTEC GCC v4.6.1.2
##

ifeq ($(call iseeopt, EE_FIND_COMPILER_IN_PATH), yes) 
## If this EE_OPT is used, the toolchain expects the compiler present in path
## This solution has been introduced because Lin does not like compiler paths
EE_LINK ?= tricore-gcc
EE_ASM  ?= tricore-gcc
EE_CC   ?= tricore-gcc
EE_AR   ?= tricore-ar
EE_OBJDUMP ?= tricore-objdump
else # EE_FIND_COMPILER_IN_PATH
## We will use "control program" gcc instead specific single tool,
## because it understand better implicit options (empirical knowledge)
## and because we can easily use HIGHTEC IDE to get the right options.
EE_LINK ?= $(TRICORE_GCCDIR)/bin/tricore-gcc
EE_ASM  ?= $(TRICORE_GCCDIR)/bin/tricore-gcc
EE_CC   ?= $(TRICORE_GCCDIR)/bin/tricore-gcc
EE_AR   ?= $(TRICORE_GCCDIR)/bin/tricore-ar
EE_OBJDUMP ?= $(TRICORE_GCCDIR)/bin/tricore-objdump
endif # EE_FIND_COMPILER_IN_PATH

# WORK AROUND TO PERSUADE LINKER TO PRESERVE SECTIONS IN SLAVE ELFs
ifeq ($(call iseeopt, __MSRP__), yes)
ifneq ($(call iseeopt, EE_USE_CUSTOM_STARTUP_CODE), yes)
ifneq ($(CPU_NUMID), 0)
OBJS += ../$(CPU_MASTER_DIR)/$(OBJDIR)/pkg/mcu/infineon_$(TRICORE_MODEL)/src/ee_tc27x_cstart.o
endif # CPU_NUMID not eq 0
endif # !EE_USE_CUSTOM_STARTUP_CODE
endif # __MSRP__

# Suffix used for Linker Scripts Files for TASKING
CC_LD_SUFFIX := ld

ifneq ($(ONLY_LIBS), TRUE)
# OPT_LIBS is used to link additional libraries (e.g., for C++ support)
ifneq ($(call iseeopt, __BIN_DISTR), yes) 
OPT_LIBS +=
else  # EEOPT __BIN_DISTR
OPT_LIBS +=
endif # EEOPT __BIN_DISTR
endif # ONLY_LIBS

# INCLUDE_PATH is a colon separated list of directories for source file searching
# -I = adds directories to the source file search path (for both gcc and gas)
# we consider the ee pkg directory and the application dir
# we also consider the current directory because the app could be compiled
# from the config files generated from eclipse...
OPT_INCLUDE = $(foreach d,$(INCLUDE_PATH),$(addprefix -I,$(call native_path,$d)))

# Tricore model remapping (TASKING and TRICORE have a different naming convention for model names :( )
ifeq ($(TRICORE_MODEL),tc27x)

CFLAGS  += -D__CPU__=$(TRICORE_MODEL)
ASFLAGS += -D__CPU__=$(TRICORE_MODEL)
GNUC_TRICORE_MODEL := tc27xx
endif

## OPT_CC are the options for compiler invocation
# -fomit-frame-pointer is neeeded to avoid that additional instructions are inserted before _START symbol
OPT_CC += -c -mcpu=$(GNUC_TRICORE_MODEL) -Wall -ffunction-sections -fomit-frame-pointer -fshort-double -Winline -finline-functions\
 -fzero-initialized-in-bss -std=gnu99

ifeq ($(call iseeopt, EE_DEBUG), yes)
OPT_CC += -g3 -ggdb -O1
else # EE_DEBUG
OPT_CC += -g -O3
endif # EE_DEBUG

ifeq ($(call iseeopt, EE_SAVE_TEMP_FILES), yes)
OPT_CC += -save-temps=obj
endif

# Specific option from the application makefile
# Add those flags at the end should be enough to give to user the option to
# completly customize build process (because last options will ovveride previous ones).
OPT_CC += $(CFLAGS)

#Functions to be used to select wrap with right options source and target for Compiler:
#Nothing special to do with source file
source_c_file=$(strip $1)
##--create stop  "control program" after object file is created
target_c_file=$(addprefix -o ,$1)


##
## OPT_ASM are the options for asm invocation
##
ifeq ($(call iseeopt, EE_MM_OPT), yes)
OPT_ASM = -c -mcpu=$(GNUC_TRICORE_MODEL) -mtc161 \
 -mcpu009 -mcpu034 -mcpu048 -mcpu050 -mcpu060 -mcpu069 -mcpu070 -mcpu072 \
 -mcpu081 -mcpu082 -mcpu083 -mcpu094 -mcpu095

else # EE_MM_OPT
OPT_ASM += -c -mcpu=$(GNUC_TRICORE_MODEL) -mtc161 -Wall -fshort-double

endif # EE_MM_OPT

ifeq ($(call iseeopt, EE_DEBUG), yes)
OPT_ASM += -Wa,--gdwarf2 
endif # EE_DEBUG


# Specific option from the application makefile
# Add those flags at the end should be enough to give to user the option to
# completly customize build process (because last options will ovveride previous ones).
OPT_ASM += $(ASFLAGS)

#Functions to be used to wrap with right options source and target for Assembler:
#Nothing special to do with source file
source_asm_file=$(strip $1)
##--create stop  "control program" after object file is created
target_asm_file=$(addprefix -o ,$1)

##
## Templates handling target and rules
##

ifneq ($(call iseeopt, EE_AS_OSAPPLICATIONS__), yes)
# apps.conf is not generated if there is no Memory Protection
apps.conf:
	@touch $@
endif # EE_AS_OSAPPLICATIONS__

# Generate configuration files for Os-Applications
ifeq ($(call iseeopt, EE_AS_OSAPPLICATIONS__), yes)
# Rule to generate MemMap.h File
MemMap.h: apps.conf $(PKGBASE)/mcu/infineon_$(TRICORE_MODEL)/cfg/MemMap.h.tmpl
# Preprocess MemMap.h.tmpl
	@echo GEN $@ from TEMPLATE $(PKGBASE)/mcu/infineon_$(TRICORE_MODEL)/cfg/$@.tmpl
	$(QUIET) awk -f $(PKGBASE)/cpu/common/cfg/memprot_generator.awk $^ > $@

# Add MemMap.h as dependency for OBJS
OBJDEP += MemMap.h
endif # EE_AS_OSAPPLICATIONS__

##
## Specific linker option from the application makefile
##

# Custom Linker Script Should be Provided with EE_LINK_SCRIPT variable
ifndef EE_LINKERSCRIPT
# Use The Erika Default One
ifeq ($(call iseeopt, EE_EXECUTE_FROM_RAM), yes)
EE_LINKERSCRIPT := ee_tc27x_gnu_ram.ld
else # EE_EXECUTE_FROM_RAM
EE_LINKERSCRIPT := ee_tc27x_gnu_flash.ld
endif # EE_EXECUTE_FROM_RAM

# Linker script start folder
EE_LINKERSCRIPT_FOLDER = $(PKGBASE)/mcu/infineon_$(TRICORE_MODEL)/cfg
# Linker Script Template
EE_LINKERSCRIPT_TEMPLATE = $(EE_LINKERSCRIPT_FOLDER)/$(EE_LINKERSCRIPT).tmpl

# The default linker script is made by a memory description part and a rules part
# (Select the right memory part in case of multicore build)
ifeq ($(call iseeopt, __MSRP__), yes)
EE_LINKERMEMORY = $(EE_LINKERSCRIPT_FOLDER)/multicore/ee_tc27x_gnu_memory_core$(CPU_NUMID).x
# Slave CPUs: add linkerscript with global shared symbols
ifneq ($(CPU_NUMID), 0)
ADDITIONAL_LINKSCRIPT = $(GLOBAL_LINKSCRIPT)
endif # CPU_NUMID not eq 0
else # __MSRP__
EE_LINKERMEMORY = $(EE_LINKERSCRIPT_FOLDER)/ee_tc27x_gnu_memory_singlecore.x
endif # __MSRP__

# If shared symbol container in slaves multicore build is defined, it has to be
# concatenated with linker memory descriptions and linker rules to obtain the
# complete linker script
$(EE_LINKERSCRIPT): apps.conf $(EE_LINKERMEMORY) $(EE_LINKERSCRIPT_TEMPLATE) $(ADDITIONAL_LINKSCRIPT)
	@echo GEN $@ from TEMPLATE $(notdir $(EE_LINKERSCRIPT_TEMPLATE))
	$(QUIET) awk -f $(PKGBASE)/cpu/common/cfg/memprot_generator.awk $^ > $@
else # EE_LINKERSCRIPT

# Slave CPUs: queue linkerscript with global shared symbols
ifeq ($(call iseeopt, __MSRP__), yes)
ifneq ($(CPU_NUMID), 0)
ADDITIONAL_LINKSCRIPT = $(GLOBAL_LINKSCRIPT)
endif # CPU_NUMID not eq 0
endif # __MSRP__

# Copy EE_LINKERSCRIPT in building folder eventually enqueuing shared symbols
# informations
$(EE_LINKERSCRIPT) : $(APPBASE)/$(EE_LINKERSCRIPT) $(ADDITIONAL_LINKSCRIPT)
	@echo GEN $@
	$(QUIET) rm -f $@
	$(QUIET) cat $^ >> $@

endif # EE_LINKERSCRIPT

# If default compiler behaviour is chosen do not add linkerscript to dependencies and
# do not add it to linker options. Moreover do not disable startup code linking.
ifneq ($(call iseeopt, EE_COMPILER_DEFAULT),yes)

# Add Linker Script to Link Dependencies
LINKDEP += $(EE_LINKERSCRIPT)

OPT_LINK += -T $(EE_LINKERSCRIPT) -nostartfiles
endif

OPT_LINK += -mcpu=$(GNUC_TRICORE_MODEL) -Wl,--gc-sections -Wl,--mem-holes\
 -Wl,-Map="$(basename $(notdir $@)).map" -Wl,--cref -fshort-double -Wl,--extmap="a"

ifeq ($(call iseeopt, EE_DEBUG), yes)
OPT_LINK +=
endif

# Specific option from the application makefile
# Add those flags at the end should be enough to give to user the option to
# completly customize build process (because last options will ovveride previous ones).
OPT_LINK += $(LDFLAGS)

#Functions to be used to wrap with right options target for Linker:
target_ld_file=$(addprefix -o ,$1)

# Options for Archiver
OPT_AR += -r -c

# Defining EEOPT Macros
# Each identifier that is listed in EEOPT is also inserted as a 
# command-line macro in the compiler...
DEFS_ASM = $(addprefix -D, $(EEOPT) )
DEFS_CC  = $(addprefix -D, $(EEOPT) )

# Automatic dependency generation
ifeq ($(call iseeopt, NODEPS), yes)
DEPENDENCY_OPT =
make-depend =
else # NODEPS
# Create dependency for all headers, and add a target for each header
DEPENDENCY_OPT = -MD -MF $(call native_path,$(subst .o,.d_tmp,$(@)))
# Create dependency for all headers, and add a target for each header
DEPENDENCY_OPT_ASM = -MD -MF $(call native_path,$(subst .o,.d_tmp,$(@)))
# Dependencies on Windows need path translation and quote remotion
make-depend = sed -e 's_\\\(.\)_/\1_g' -e 's_\<\([a-zA-Z]\):/_/cygdrive/\l\1/_g' < $1_tmp > $1 && rm $1_tmp
endif # NODEPS
