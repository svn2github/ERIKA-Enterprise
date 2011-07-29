# ###*B*###
# ERIKA Enterprise - a tiny RTOS for small microcontrollers
# 
# Copyright (C) 2011  Evidence Srl
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

## Author: 2009 - Paolo Gai
## CVS: $Id: rules_freescale_s12x_cosmic.mk,v 1.00 2009/11/11 22:21:06 Paolo Exp $

# Enable verbose output from EE_OPT
ifeq ($(call iseeopt, VERBOSE), yes)
VERBOSE = 1
endif

# Initial definition of target all as predefined
all::

include $(EEBASE)/pkg/cfg/dir.mk
include $(PKGBASE)/cfg/verbose.mk
include $(PKGBASE)/cfg/compiler.mk

#HCS12_CRT0 := $(BINDIR_HCS12)/HS12x/crtsx.S

# HCS12_DATA_DIR refers to the location of HCS12 libraries
HCS12_DATA_DIR := $(COSMIC_CCDIR)

HCS12_LIB_DIR := $(HCS12_DATA_DIR)/Lib
#HCS12_INCLUDE_DIR := $(HCS12_DATA_DIR)/HS12x
#HCS12_LINKER_DIR := $(HCS12_DATA_DIR)/Link_files

# Add linker dependencies
OPT_LINK += 
LINKDEP += $(APPBASE)/$(COSMIC_LINKERSCRIPT)

# Specific option from the libs dependencies
LIBDEP += $(ALL_LIBS)

# Specific option from the application makefile
LIBDEP += $(LDDEPS)

# path for libraries
OPT_LIBS += -l "`cygpath -w $(HCS12_LIB_DIR)`"
OPT_LIBS += -l "`cygpath -w $(shell pwd)`"


# INTERNAL_CCINCLUDEDIR is used to avoid multiple calls to cygpath
#INTERNAL_CCINCLUDEDIR := -i"`cygpath -w $(HCS12_INCLUDE_DIR)`"
#ALLINCPATH += $(INTERNAL_CCINCLUDEDIR)


## HCS12-related directories
# we should look if these need to be moved inside dir.mk

#if COSMIC_CCDIR is defined
ifneq ($(COSMIC_CCDIR),)
DEFS_CC += -d__HCS12_INCLUDE_REGS__
HCS12_INCLUDE_REGS=__HCS12_INCLUDE_REGS__
endif

include $(PKGBASE)/cfg/cfg.mk


#
# --------------------------------------------------------------------------
#

##
## Source files and paths
##

# Add crtsx.s from MC
#EE_BOOT_SRCS := fromHCS12/crtsx.S

SRCS += 

LIBEESRCS += $(EE_SRCS)
LIBEEOBJS := $(addprefix $(OBJDIR)/, $(patsubst %.c,%.o,$(patsubst %.S,%.o,$(LIBEESRCS))))

#LIBEESRCS += $(LIBSRCS)
#LIBOBJS := $(addprefix $(OBJDIR)/, $(patsubst %.c,%.o,$(patsubst %.S,%.o,$(LIBSRCS))))

SRCS += $(APP_SRCS)
#SRCS += $(EE_SRCS)
OBJS := $(addprefix $(OBJDIR)/, $(patsubst %.c,%.o,$(patsubst %.S,%.o, $(SRCS))))

LIBDEP += libee.x12

vpath %.cd $(APPBASE)
vpath %.Sd $(APPBASE)
vpath %.c $(EE_VPATH) $(APPBASE)
vpath %.S $(EE_VPATH) $(APPBASE)

##
## Compute common variables
##

COMPUTED_ALLINCPATH := $(ALLINCPATH)
COMPUTED_OPT_LINK := $(OPT_LINK)
COMPUTED_OPT_ASM := $(OPT_ASM)
COMPUTED_OPT_CC := $(OPT_CC)
COMPUTED_OPT_CC_DEPS := $(OPT_CC_DEPS)

## Select input filename format
SOURCEFILE = `cygpath -w $<`
TARGETFILE = `cygpath -w $@`
TARGET := hs12xs.objdump
SRCFILE = `cygpath -w $(patsubst %.o,%.src,$@)`

##
## Main rules: all clean
##

.PHONY: all clean

all:: make_directories $(ALL_LIBS) $(TARGET) 
	@printf "************************************\n\n"
	@printf "Compilation terminated successfully!\n"

clean::
	@-rm -rf *.a *.ls *.ld *.map *.elf *.$(HCS12_EXTENSION) *.objdump deps deps.pre obj *.x12
# to support "make clean all"
ifeq ($(findstring all,$(MAKECMDGOALS)),all)
	@printf "CLEAN (also \"all\" specified)\n"
else
	@printf "CLEAN\n";
endif

hs12xs.objdump: hs12xs.$(HCS12_EXTENSION)
	@printf "OBJDUMP\n";
	$(QUIET)$(EE_CLABS) -v hs12xs.$(HCS12_EXTENSION) > hs12xs.objdump
	@printf "ELF\n";
	$(QUIET)$(EE_CVDWARF) hs12xs.$(HCS12_EXTENSION)

##
## Object file creation
##

# ATT!!! tolta l'opzione -m > hs12xs.map
hs12xs.$(HCS12_EXTENSION): $(OBJS) $(LINKDEP) $(LIBDEP) 
	@printf "LD\n";
	$(QUIET)$(EE_LINK) $(COMPUTED_OPT_LINK) \
                     -o $(TARGETFILE) $(OPT_LIBS) $(LINKDEP) $(OBJS) $(LIBDEP) \
                     
                    

# preprocess first the assembly code and then compile the object file
#$(OBJDIR)/%.o: %.S
#	$(VERBOSE_PRINTPRE) $(EE_PREP) $(GCC_ALLINCPATH) $(DEFS_GCCASM) -E -P "$(SOURCEFILE)" > $(SRCFILE)
#	$(VERBOSE_PRINTASM) $(EE_ASM) $(COMPUTED_OPT_ASM) -o $(TARGETFILE) $(SRCFILE) 

# preprocess first the assembly code and then compile the object file
$(OBJDIR)/%.o: %.S
	$(VERBOSE_PRINTPRE) $(EE_PREP) $(COMPUTED_ALLINCPATH) $(DEFS_CC) -e "$(SOURCEFILE)" > $(SRCFILE)
	$(VERBOSE_PRINTASM) $(EE_ASM) $(COMPUTED_OPT_ASM) -o $(TARGETFILE) $(SRCFILE) 

# produce the object file from assembly code in a single step ATT!!!
#$(OBJDIR)/%.o: %.S
#	$(VERBOSE_PRINTCPP) $(EE_CC) $(COMPUTED_ALLINCPATH) $(DEFS_ASM) -a"-o $(TARGETFILE)" "$(SOURCEFILE)" 

# produce the object file from C code in a single step	ATT!!! tolta opzione -c!!! e tolta l'opzione -o $(TARGETFILE) 
$(OBJDIR)/%.o: %.c ee_hs12xsregs.h  
	$(VERBOSE_PRINTCPP) $(EE_CC) $(COMPUTED_OPT_CC) $(COMPUTED_ALLINCPATH) $(DEFS_CC) -a"-o $(TARGETFILE)" "$(SOURCEFILE)" 

##
## EE Library
##


libee.x12: $(LIBEEOBJS)
	@printf "AR  libee.x12\n" ;
	$(QUIET)$(EE_AR) -c libee.x12 $(LIBEEOBJS)
	@echo
	$(QUIET)$(EE_AR) -t -s libee.x12
	@echo


##
## Automatic Generation of dependencies
##

# deps depends on the flag and not on the PHONY rule!
deps: $(OBJDIR)/.make_directories_flag deps.pre
	@printf "GEN deps\n"
	@sed "s/ \<\([A-Za-z]\):/ \/cygdrive\/\l\1/g" < deps.pre > deps

deps.pre: $(addprefix $(OBJDIR)/, $(patsubst %.S,%.Sd,$(patsubst %.c,%.cd, $(SRCS) $(LIBEESRCS) $(LIBSRCS))))
	@printf "GEN deps.pre\n" ; cat $^ > deps.pre

# generate dependencies for .c files and add "file.cd" to the target
$(OBJDIR)/%.cd: %.c ee_hs12xsregs.h
	$(VERBOSE_PRINTDEP) $(EE_DEP) $(COMPUTED_OPT_CC_DEPS) $(COMPUTED_ALLINCPATH) $(DEFS_CC) -M "$(SOURCEFILE)" > $(TARGETFILE).tmp
	@echo -n $(TARGETFILE) $(dir $(TARGETFILE)) | cat - $(TARGETFILE).tmp > $(TARGETFILE)
	@rm -rf $(TARGETFILE).tmp
	@test -s $(TARGETFILE) || rm -f $(TARGETFILE)

# generate dependencies for .S files and add "file.Sd" to the target
$(OBJDIR)/%.Sd: %.S
	$(VERBOSE_PRINTDEP) $(EE_DEP) $(COMPUTED_ALLINCPATH) $(DEFS_ASM) -M "$(SOURCEFILE)" > $(TARGETFILE).tmp
	@echo -n $(TARGETFILE) $(dir $(TARGETFILE)) | cat - $(TARGETFILE).tmp > $(TARGETFILE)
	@rm -rf $(TARGETFILE).tmp
	@test -s $(TARGETFILE) || rm -f $(TARGETFILE)


ee_hs12xsregs.h: $(APPBASE)/$(COSMIC_INCLUDE_H)
	@printf "GEN ee_hs12xsregs.h\n"
	@printf "/* Automatically generated from Makefile */\n" > ee_hs12xsregs.h
	@printf "#include \"$(APPBASE)/$(COSMIC_INCLUDE_H)\"\n" >> ee_hs12xsregs.h


#
# --------------------------------------------------------------------------
#

# interesting read: http://www.cmcrossroads.com/content/view/6936/120/

# this forces the directory creation when issuing the "make all"
# rule. there is need for this rule because it may be that the user
# asks for a "make clean all". "clean" removes the directories which
# are then needed for "all", so that when "all" arrives the
# directories must be recreated. We cannot use a flag file like in the
# rule just after because when there is a "clean all" the check for
# prerequisites is not done again when doing "all".
.PHONY: make_directories
make_directories:
ifneq ($(findstring clean,$(MAKECMDGOALS)),clean)
	@printf "MAKE_DIRECTORIES (after a clean)\n"
	$(QUIET)mkdir -p $(dir $(basename $(addprefix $(OBJDIR)/, $(SRCS) $(LIBEESRCS) $(LIBSRCS))))
endif

# this checks but not forces the directory creation when creating dependencies
$(OBJDIR)/.make_directories_flag:
	@printf "MAKE_DIRECTORIES\n"
	$(QUIET)mkdir -p $(dir $(basename $(addprefix $(OBJDIR)/, $(SRCS) $(LIBEESRCS) $(LIBSRCS))))
	$(QUIET)touch $(TARGETFILE)

#
# --------------------------------------------------------------------------
#

ifndef NODEPS
ifneq ($(MAKECMDGOALS),clean)
ifneq ($(call iseeopt, NODEPS), yes) 
#-include deps
endif
endif
endif
