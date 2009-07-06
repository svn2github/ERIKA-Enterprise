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

## Author: 2005- Paolo Gai
## CVS: $Id: rules_microchip_pic30.mk,v 1.24 2008/10/14 22:21:06 nino Exp $

# Enable verbose output from EE_OPT
ifeq ($(findstring VERBOSE,$(EEOPT)) , VERBOSE)
VERBOSE = 1
endif

# Initial definition of target all as predefined
all::

include $(EEBASE)/pkg/cfg/dir.mk
include $(PKGBASE)/cfg/verbose.mk
include $(PKGBASE)/cfg/compiler.mk

# Recomplied Microchip GCC path in Linux and Cygwin environments
EE_GCCDIR := /opt/mchp/pic30

PIC30_CRT0 := $(EEBASE)/contrib/microchip/pic30/src/crt0.s

###########################################
## OLD Automatic selection of C30 version
###########################################
##C30_VERSION := $(shell $(EE_CC) -v 2>&1)
##C30_LONGPATH := $(if $(findstring Microchip 3.10,$(C30_VERSION)),1)
#C30_VERSION := $(shell $(EE_CC) --version 2>&1 | awk '/__C30_VERSION__/{split($$0,a,"== "); print a[2]; }' )
#C30_LONGPATH := $(shell $(EE_CC) --version 2>&1 | awk '/__C30_VERSION__/{split($$0,a,"== "); if (a[2]>=310) print 1; else print 0; }' )
#
## Manual selection of C30 include path version
#ifeq ($(findstring C30_LONGPATH,$(EEOPT)) , C30_LONGPATH)
#C30_LONGPATH := 1
#endif
#
# Set include subdirectory for GCC
#ifeq ($(C30_LONGPATH), 1)
#C30SUBDIR :=
#ifeq ($(findstring 30F,$(PIC30_MODEL)) , 30F)
#C30SUBDIR := /dsPIC30F
#endif
#ifeq ($(findstring 33F,$(PIC30_MODEL)) , 33F)
#C30SUBDIR := /dsPIC33F
#endif
#ifeq ($(findstring 24H,$(PIC30_MODEL)) , 24H)
#C30SUBDIR := /PIC24H
#endif
#ifeq ($(findstring 24F,$(PIC30_MODEL)) , 24F)
#C30SUBDIR := /PIC24F
#endif
#else
#C30SUBDIR :=
#endif

##if PIC30_GCCDIR is defined
#ifneq ($(PIC30_GCCDIR),)
#PIC30_LINKERDIR := $(PIC30_GCCDIR)/Support$(C30SUBDIR)/gld
#else
#PIC30_LINKERDIR := $(PIC30_ASMDIR)/Support$(C30SUBDIR)/gld
#endif
###############################################
###############################################

# MCHP_DATA_DIR refers to the location of Microchip libraries
# Cygwin environment
ifeq ($(findstring __RTD_CYGWIN__,$(EEOPT)), __RTD_CYGWIN__) 
MCHP_DATA_DIR := $(PIC30_GCCDIR)
else
# Linux environment
MCHP_DATA_DIR := $(EE_GCCDIR)/pic30-nonfree
endif

PIC30_LIB_DIR := $(MCHP_DATA_DIR)/lib
PIC30_INCLUDE_DIR := $(MCHP_DATA_DIR)/include

# If PIC30_LIB_DIR has subdirectories... (since 3.10) 
ifneq ($(shell find $(PIC30_LIB_DIR) -mindepth 1 -type d),)
SHORT_MODEL := $(shell echo $(PIC30_MODEL) | awk '{ a = substr($$0,1,3); print a;}')
MCHP_SUPPORT_DIR := $(MCHP_DATA_DIR)/support/dsPIC$(SHORT_MODEL)
PIC30_LIBD_DIR := $(PIC30_LIB_DIR)/dsPIC$(SHORT_MODEL)
else
MCHP_SUPPORT_DIR := $(MCHP_DATA_DIR)/support
PIC30_LIBD_DIR :=
endif

PIC30_H_DIR := $(MCHP_SUPPORT_DIR)/h
PIC30_INC_DIR := $(MCHP_SUPPORT_DIR)/inc
PIC30_LINKER_DIR := $(MCHP_SUPPORT_DIR)/gld

# Add linker dependencies
OPT_LINK += --script=loc_gnu.ld -u__reset
LINKDEP += loc_gnu.ld

# Add application file to dependencies
ifneq ($(ONLY_LIBS), TRUE)

## OPT_LIBS is used to link additional libraries (e.g., for C++ support)
ifneq ($(findstring __BIN_DISTR,$(EEALLOPT)), __BIN_DISTR) 
# the EE library is built in the current directory
OPT_LIBS += -lee -L .
LIBDEP += libee.a
else
# the EE library is stored in the EE lib directory
OPT_LIBS += -l$(EELIB) -L $(EEBASE)/lib
LIBDEP += $(EEBASE)/lib/lib$(EELIB).a
endif

endif

# Specific option from the libs dependencies
LIBDEP += $(ALL_LIBS)

# Specific option from the application makefile
LIBDEP += $(LDDEPS)

################################################
## OLD Stuff (cont.)
################################################
## Libraries from MC
#ifneq ($(PIC30_GCCDIR),)
#OPT_LIBS += -lm -lc -ldsp -l$(subst .a,,$(subst lib,,$(PIC30_DEV_LIB))) -lpic30-$(PIC30_OFF)
#
#ifeq ($(PLATFORM), LINUX)
#OPT_LIBS += -L $(PIC30_GCCDIR)/lib
#ifeq ($(C30_LONGPATH), 1)
#OPT_LIBS += -L $(PIC30_GCCDIR)/lib$(C30SUBDIR)
#endif
#else
#OPT_LIBS += -L "`cygpath -w $(PIC30_GCCDIR)/lib`"
#ifeq ($(C30_LONGPATH), 1)
#OPT_LIBS += -L "`cygpath -w $(PIC30_GCCDIR)/lib$(C30SUBDIR)`"
#endif
#endif
#endif
## Includes from MC
# only if PIC30_GCCDIR is defined
#ifneq ($(PIC30_GCCDIR),)
# INTERNAL_GCCINCLUDEDIR is used to avoid multiple calls to cygpath
#ifeq ($(PLATFORM), LINUX)
#INTERNAL_GCCINCLUDEDIR := -I$(PIC30_GCCDIR)/include)
#else
#INTERNAL_GCCINCLUDEDIR := -I"$(shell cygpath -w $(PIC30_GCCDIR)/include)"
#endif
#ALLINCPATH += $(INTERNAL_GCCINCLUDEDIR)
#endif
################################################
################################################

## Libraries from MC
OPT_LIBS += -lm -lc -ldsp
OPT_LIBS += -l$(subst .a,,$(subst lib,,$(PIC30_DEV_LIB)))
OPT_LIBS += -lpic30-$(PIC30_OFF)

ifeq ($(findstring __RTD_CYGWIN__,$(EEOPT)), __RTD_CYGWIN__) 
OPT_LIBS += -L "`cygpath -w $(PIC30_LIB_DIR)`"
# check if PIC30_LIBD_DIR is empty
ifneq ($(PIC30_LIBD_DIR),)
OPT_LIBS += -L "`cygpath -w $(PIC30_LIBD_DIR)`"
endif
else
# Linux environment
OPT_LIBS += -L $(PIC30_LIB_DIR)
# check if PIC30_LIBD_DIR is empty
ifneq ($(PIC30_LIBD_DIR),)
OPT_LIBS += -L $(PIC30_LIBD_DIR)
endif
endif

# #Includes from MC
# INTERNAL_GCCINCLUDEDIR is used to avoid multiple calls to cygpath
ifeq ($(findstring __RTD_CYGWIN__,$(EEOPT)), __RTD_CYGWIN__) 
INTERNAL_GCCINCLUDEDIR := -I"`cygpath -w $(PIC30_INCLUDE_DIR)`"
else
# Linux environment
INTERNAL_GCCINCLUDEDIR := -I$(PIC30_INCLUDE_DIR)
endif

ALLINCPATH += $(INTERNAL_GCCINCLUDEDIR)

## PIC30-related directories
# we should look if these need to be moved inside dir.mk

#if PIC30_GCCDIR is defined
ifneq ($(PIC30_GCCDIR),)
DEFS_CC += -D__PIC30_INCLUDE_REGS__
MPLAB_INCLUDE_REGS=__PIC30_INCLUDE_REGS__
endif

# Add application file to dependencies
ifneq ($(ONLY_LIBS), TRUE)
TARGET:=pic30.objdump
endif

# When building for MPLAB IDE, we do not have to include the source
# code of the application, but we have to include the library
# containing the EE code. 
# note that:
# - libee.a is not included in ALL_LIBS
# - when GENERATE_MPLABIDE_LIBS is defined, ONLY_LIBS is NOT defined
ifeq ($(GENERATE_MPLABIDE_LIBS), TRUE)
TARGET:=libee.a generate_eeopt

# we reset the SRCS variable (no application has to be compiled), and
# we put the eecfg.c inside the library
SRCS:=
LIBEESRCS+= $(OUTBASE)/eecfg.c
endif

include $(PKGBASE)/cfg/cfg.mk


#
# --------------------------------------------------------------------------
#

##
## Source files and paths
##
## TODO - Select if compile crt0.s or link libpic30-$(PIC30_OFF).a
##

# Add crt0.s from MC
EE_BOOT_SRCS := frommchp/crt0.S

# Boot code containing _start should stay outside of the library in
# case of normal compilation
ifeq ($(findstring __BIN_DISTR,$(EEOPT)), __BIN_DISTR)
LIBSRCS += $(EE_BOOT_SRCS)
else
SRCS += $(EE_BOOT_SRCS)
endif

LIBEESRCS += $(EE_SRCS)
LIBEEOBJS := $(addprefix $(OBJDIR)/, $(patsubst %.c,%.o,$(patsubst %.S,%.o,$(LIBEESRCS))))

LIBEESRCS += $(LIB_SRCS)
LIBOBJS := $(addprefix $(OBJDIR)/, $(patsubst %.c,%.o,$(patsubst %.S,%.o,$(LIBSRCS))))

SRCS += $(APP_SRCS)
OBJS := $(addprefix $(OBJDIR)/, $(patsubst %.c,%.o,$(patsubst %.S,%.o, $(SRCS))))

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
ifeq ($(findstring __RTD_CYGWIN__,$(EEOPT)), __RTD_CYGWIN__) 
SOURCEFILE = `cygpath -w $<`
TARGETFILE = `cygpath -w $@`
SRCFILE = `cygpath -w $(patsubst %.o,%.src,$@)`
else
SOURCEFILE = $<
TARGETFILE = $@
SRCFILE = $(patsubst %.o,%.src,$(TARGETFILE))
endif

##
## Main rules: all clean
##

.PHONY: all clean

all:: make_directories $(ALL_LIBS) $(TARGET) 
	@printf "************************************\n\n"
	@printf "Compilation terminated successfully!\n"

clean::
	@-rm -rf *.a *.ld *.map *.$(PIC30_EXTENSION) *.objdump deps deps.pre obj
# to support "make clean all"
ifeq ($(findstring all,$(MAKECMDGOALS)),all)
	@printf "CLEAN (also \"all\" specified, frommchip directory not removed)\n"
else
	@printf "CLEAN\n";
	@-rm -rf frommchp
endif

pic30.objdump: pic30.$(PIC30_EXTENSION)
	@printf "OBJDUMP\n";
	$(QUIET)$(EE_OBJDUMP) -D pic30.$(PIC30_EXTENSION) > pic30.objdump

##
## Object file creation
##


pic30.$(PIC30_EXTENSION): $(OBJS) $(LINKDEP) $(LIBDEP) 
	@printf "LD\n";
	$(QUIET)$(EE_LINK) $(COMPUTED_OPT_LINK) \
                     -o $(TARGETFILE) $(OBJS) \
                     --start-group $(OPT_LIBS) --end-group \
                     -M > pic30.map

					 
ifeq ($(findstring BUILDSRC,$(EEALLOPT)), BUILDSRC)
# preprocess first the assembly code and then compile the object file
$(OBJDIR)/%.o: %.S ee_pic30regs.inc
	$(VERBOSE_PRINTPRE) $(EE_DEP) $(COMPUTED_ALLINCPATH) $(DEFS_ASM) -E "$(SOURCEFILE)" > $(SRCFILE)
	$(VERBOSE_PRINTASM) $(EE_ASM) $(COMPUTED_OPT_ASM) $(SRCFILE) -o $(TARGETFILE)
else
# produce the object file from assembly code in a single step
$(OBJDIR)/%.o: %.S ee_pic30regs.inc
	$(VERBOSE_PRINTCPP) $(EE_CC) $(COMPUTED_ALLINCPATH) $(DEFS_ASM) -c "$(SOURCEFILE)" -o $(TARGETFILE)
endif

ifeq ($(findstring BUILDSRC,$(EEALLOPT)), BUILDSRC)
# produce first the assembly from C code and then compile the object file
$(OBJDIR)/%.o: %.c ee_pic30regs.h
	$(VERBOSE_PRINTCPP) $(EE_CC) $(COMPUTED_OPT_CC) $(COMPUTED_ALLINCPATH) $(DEFS_CC) "$(SOURCEFILE)" -S -o $(SRCFILE)
	$(VERBOSE_PRINTASM) $(EE_ASM) $(COMPUTED_OPT_ASM) $(SRCFILE) -o $(TARGETFILE)
else
# produce the object file from C code in a single step
$(OBJDIR)/%.o: %.c ee_pic30regs.h
	$(VERBOSE_PRINTCPP) $(EE_CC) $(COMPUTED_OPT_CC) $(COMPUTED_ALLINCPATH) $(DEFS_CC) -c "$(SOURCEFILE)" -o $(TARGETFILE)
endif


$(OBJDIR)/frommchp/crt0.o: frommchp/crt0.s
	$(VERBOSE_PRINTASM) $(EE_ASM) $(COMPUTED_OPT_ASM) $(SOURCEFILE) -o $(TARGETFILE)


##
## Microchip C30 files
##

frommchp/crt0.S: $(PIC30_CRT0)
	@printf "\nCP crt0.s\n"; cp $(SOURCEFILE) $(TARGETFILE)

# Check if the MCU model has been defined
ifneq ($(PIC30_MODEL),)

ee_pic30regs.h: frommchp/$(PIC30_INCLUDE_C)
	@printf "GEN ee_pic30regs.h\n"
	@printf "/* Automatically generated from Makefile */\n" > ee_pic30regs.h
	@printf "#include \"frommchp/$(PIC30_INCLUDE_C)\"\n" >> ee_pic30regs.h

ee_pic30regs.inc: frommchp/$(PIC30_INCLUDE_S)
	@printf "GEN ee_pic30regs.inc\n"
	@printf "; Automatically generated from Makefile\n" > ee_pic30regs.inc
	@printf "	.equ __$(PIC30_MODEL), 1 \n" >> ee_pic30regs.inc
	@printf "	.include \"frommchp/$(PIC30_INCLUDE_S)\" \n" >> ee_pic30regs.inc

#frommchp/$(PIC30_INCLUDE_C): $(PIC30_GCCDIR)/support$(C30SUBDIR)/h/$(PIC30_INCLUDE_C)
frommchp/$(PIC30_INCLUDE_C): $(PIC30_H_DIR)/$(PIC30_INCLUDE_C)
	@printf "CP $(PIC30_INCLUDE_C)\n"; cp $(SOURCEFILE) $(TARGETFILE)

#frommchp/$(PIC30_INCLUDE_S): $(PIC30_EXTRA_INCLUDE)/support$(C30SUBDIR)/inc/$(PIC30_INCLUDE_S)
frommchp/$(PIC30_INCLUDE_S): $(PIC30_INC_DIR)/$(PIC30_INCLUDE_S)
	@printf "CP $(PIC30_INCLUDE_S)\n"; cp $(SOURCEFILE) $(TARGETFILE)

else

# no MCU model defined
ee_pic30regs.h: frommchp/$(PIC30_INCLUDE_C)
	@printf "GEN ee_pic30regs.h\n"
	@printf "/* Automatically generated from Makefile */\n" > ee_pic30regs.h
	@printf "/* WARNING! No MCU model selected! */\n" >> ee_pic30regs.h

ee_pic30regs.inc: frommchp/$(PIC30_INCLUDE_S)
	@printf "GEN ee_pic30regs.inc\n"
	@printf "; Automatically generated from Makefile \n" > ee_pic30regs.inc
	@printf "; WARNING! No MCU model selected! \n" >> ee_pic30regs.inc
endif


##
## Locator files
##

#if PIC30_GCCDIR is defined
#loc_gnu.ld: $(PIC30_LINKERDIR)/$(PIC30_LINKERSCRIPT)
#	@printf "LOC\n" ; cp $(PIC30_LINKERDIR)/$(PIC30_LINKERSCRIPT) loc_gnu.ld
loc_gnu.ld: $(PIC30_LINKER_DIR)/$(PIC30_LINKERSCRIPT)
	@printf "LOC\n" ; cp $(PIC30_LINKER_DIR)/$(PIC30_LINKERSCRIPT) loc_gnu.ld

##
## EE Library
##

libee.a: $(LIBEEOBJS)
	@printf "AR  libee.a\n" ;
	$(QUIET)$(EE_AR) rs libee.a $(LIBEEOBJS)


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
$(OBJDIR)/%.cd: %.c ee_pic30regs.h
	$(VERBOSE_PRINTDEP) $(EE_DEP) $(COMPUTED_OPT_CC_DEPS) $(COMPUTED_ALLINCPATH) $(DEFS_CC) -M "$(SOURCEFILE)" > $(TARGETFILE).tmp
	@echo -n $(TARGETFILE) $(dir $(TARGETFILE)) | cat - $(TARGETFILE).tmp > $(TARGETFILE)
	@rm -rf $(TARGETFILE).tmp
	@test -s $(TARGETFILE) || rm -f $(TARGETFILE)

# generate dependencies for .S files and add "file.Sd" to the target
$(OBJDIR)/%.Sd: %.S ee_pic30regs.inc
	$(VERBOSE_PRINTDEP) $(EE_DEP) $(COMPUTED_ALLINCPATH) $(DEFS_ASM) -M "$(SOURCEFILE)" > $(TARGETFILE).tmp
	@echo -n $(TARGETFILE) $(dir $(TARGETFILE)) | cat - $(TARGETFILE).tmp > $(TARGETFILE)
	@rm -rf $(TARGETFILE).tmp
	@test -s $(TARGETFILE) || rm -f $(TARGETFILE)


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
	$(QUIET)mkdir -p $(dir $(basename $(addprefix $(OBJDIR)/, $(SRCS) $(LIBEESRCS) $(LIBSRCS)))) frommchp obj/frommchp
endif

# this checks but not forces the directory creation when creating dependencies
$(OBJDIR)/.make_directories_flag:
	@printf "MAKE_DIRECTORIES\n"
	$(QUIET)mkdir -p $(dir $(basename $(addprefix $(OBJDIR)/, $(SRCS) $(LIBEESRCS) $(LIBSRCS)))) frommchp obj/frommchp
	$(QUIET)touch $(TARGETFILE)

#
# --------------------------------------------------------------------------
#

# the eeopt file is generated when dealing with MPLAB IDE!
#
# this is a phony because the source code does not depend on this file
# and its content higly depends on the EEOPT variables...
#
.PHONY: generate_eeopt
generate_eeopt:
	@printf "MPLAB - eeopt.h\n"
	@echo // This part of the include file includes all the options > eeopt.h
	@echo // which are typically inserted with >> eeopt.h
	@echo // the -D compiler directive. >> eeopt.h
	@echo // This part is automatically generated by the makefile only for MPLABIDE. >> eeopt.h
	@for x in $(EEOPT) $(MPLAB_INCLUDE_REGS); do \
		echo \#ifndef $${x}      >> eeopt.h; \
		echo \#define $${x}      >> eeopt.h; \
		echo \#endif             >> eeopt.h; \
	done;



#
# --------------------------------------------------------------------------
#

ifndef NODEPS
ifneq ($(MAKECMDGOALS),clean)
ifneq ($(findstring NODEPS,$(EEALLOPT)), NODEPS) 
-include deps
endif
endif
endif
