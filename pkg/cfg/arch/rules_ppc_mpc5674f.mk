# ###*B*###
# ERIKA Enterprise - a tiny RTOS for small microcontrollers

# Copyright (C) 2002-2010  Evidence Srl

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

## Author: 2010 Fabio Checconi
## 2010 Bernardo  Dal Seno

# Enable verbose output from EE_OPT
ifeq ($(call iseeopt, VERBOSE), yes)
VERBOSE = 1
endif

include $(EEBASE)/pkg/cfg/dir.mk
include $(PKGBASE)/cfg/verbose.mk
include $(PKGBASE)/cfg/compiler.mk

ifeq ($(call iseeopt, __E200Z7_EXECUTE_FROM_RAM__), yes)
DLD := ram.dld
T32CMM_SRC := ram.cmm
else
DLD := rom.dld
T32CMM_SRC := flash.cmm
endif

OPT_LINK += loc_diab.dld -e __start
LINKDEP = loc_diab.dld

PPC_ARCH ?= PPCE200Z6NES:simple
CRT0_SRCS := pkg/mcu/freescale_mpc5674f/src/ee_boot.S
OPT_TARGET := -t $(PPC_ARCH)
OPT_CC += $(OPT_TARGET)
OPT_ASM += $(OPT_TARGET)
OPT_LINK += $(OPT_TARGET)

# Add application file to dependencies
ifneq ($(ONLY_LIBS), TRUE)

# OPT_LIBS is used to link additional libraries (e.g., for C++ support)
ifneq ($(call iseeopt, __BIN_DISTR), yes)
# the EE library is built in the current directory
OPT_LIBS +=  -L . -lee
LIBDEP = libee.a
else
OPT_LIBS += -L $(EEBASE)/lib -lee_$(EELIB)
endif

endif

# Specific option from the libs dependencies
LIBDEP += $(ALL_LIBS)

# Specific option from the application makefile
LIBDEP += $(LDDEPS)

# Add application file to dependencies
ifneq ($(call iseeopt, __BUILD_LIBS__), yes)
TARGET:=z7.elf
endif

include $(wildcard $(PKGBASE)/cfg/cfg.mk)


#
# --------------------------------------------------------------------------
#

##
## Common Rules
##


# Boot code containing _start should stay outside of the library in
# case of normal compilation
ifeq ($(call iseeopt, __BIN_DISTR), yes)
LIBSRCS += $(EE_BOOT_SRCS)
else
SRCS += $(EE_BOOT_SRCS)
endif

CRT0 := $(addprefix $(OBJDIR)/, $(patsubst %.c,%.o,$(patsubst %.S,%.o, $(CRT0_SRCS))))
OPT_CRT0 := -L $(dir $(CRT0)) -l:$(notdir $(CRT0))

LIBEESRCS += $(EE_SRCS)
LIBEEOBJS := $(addprefix $(OBJDIR)/, $(patsubst %.c,%.o,$(patsubst %.S,%.o,$(LIBEESRCS))))

LIBEESRCS += $(LIB_SRCS)
LIBOBJS := $(addprefix $(OBJDIR)/, $(patsubst %.c,%.o,$(patsubst %.S,%.o,$(LIBSRCS))))

SRCS += $(APP_SRCS)
OBJS := $(addprefix $(OBJDIR)/, $(patsubst %.c,%.o,$(patsubst %.S,%.o, $(SRCS))))

ALLOBJS = $(LIBEEOBJS) $(LIBOBJS) $(OBJS) $(CRT0)

OBJDIRS=$(sort $(dir $(ALLOBJS)))

# INCLUDE_PATH is a space-separated list of directories for header file searching
# we consider the ee pkg directory and the application dir
# we also consider the current directory because the app could be compiled
# from the config files generated from eclipse...
INCLUDE_PATH += $(APPBASE) $(PKGBASE) .


vpath %.c $(EE_VPATH) $(APPBASE)
vpath %.S $(EE_VPATH) $(APPBASE)

##
## Compute common variables
##

# Avoid multiple evaluations of OPT_INCLUDE, which may call `cygpath'
COMPUTED_OPT_INCLUDE := $(OPT_INCLUDE)
COMPUTED_OPT_LINK := $(OPT_LINK)
COMPUTED_OPT_ASM := $(OPT_ASM)
COMPUTED_OPT_CC := $(OPT_CC)
COMPUTED_OPT_CC_DEPS := $(OPT_CC_DEPS)
COMPUTED_OPT_TCC := $(OPT_TCC)

## Select input filename format
SOURCEFILE = $(call native_path, $<)
TARGETFILE = $(call native_path, $@)
SRCFILE = $(call native_path, $(patsubst %.o,%.src,$@))


##
## Main rules: all clean
##

.PHONY: all clean t32

all: $(TARGET) t32
# The success message is printed by the $(TARGET) rule, so we get a "Nothing
# do be done" message when everything is up to date

clean:
	@echo "CLEAN\n" ;
	@-rm -rf *.a *.ld *.dld *.map *.elf *.objdump deps deps.pre	\
		debug.bat *.cmm obj *.men *.o *.cd *.src

##
## Lauterbach targets
##
T32BASE ?= /opt/case/emulator/lauterbach/t32
T32BIN ?= $(T32BASE)/demo/powerpc/flash/quad/c90fl5674.bin
T32GENMENU ?= $(T32BASE)/demo/kernel/orti/genmenu

T32TARGETS := t32.cmm orti.cmm
ifneq ($(wildcard system.orti),)
T32TARGETS += orti.cmm orti.men ortiperf.men
T32ORTISTR := do orti.cmm
else
T32ORTISTR :=
endif

t32: $(T32TARGETS)

t32.cmm:
	$(QUIET)sed -e 's:flashdriver=.*$$:flashdriver="$(T32BIN)":'	\
		-e 's:ORTICMD:$(T32ORTISTR):'				\
		"$(PKGBASE)/mcu/freescale_mpc5674f/cfg/$(T32CMM_SRC)" > $@

orti.cmm ortiperf.men: t32.cmm
	@cp $(PKGBASE)/mcu/freescale_mpc5674f/cfg/orti.cmm .
	@cp $(PKGBASE)/mcu/freescale_mpc5674f/cfg/ortiperf.men .

orti.men: $(T32GENMENU)
	@$(T32GENMENU) system.orti

##
## ELF file creation
##

$(TARGET): $(CRT0) $(OBJS) $(LINKDEP) $(LIBDEP)
	@printf "LD\n";
	$(QUIET)$(EE_LINK) $(COMPUTED_OPT_LINK)				\
		-o $(TARGETFILE) $(OPT_CRT0) $(OBJS) $(OPT_LIBS) -lc -m > z7.map
	@echo
	@echo "Compilation terminated successfully"
	@echo

##
## Object file creation
##

$(OBJDIR)/%.o: %.S
	$(VERBOSE_PRINTPRE)	$(EE_CC)  $(COMPUTED_OPT_INCLUDE) $(DEFS_ASM) $(DEPENDENCY_OPT) -E $(SOURCEFILE) > $(SRCFILE)
	$(VERBOSE_PRINTASM)	$(EE_ASM) $(COMPUTED_OPT_ASM) -o $(TARGETFILE) $(SRCFILE)
	$(call make-depend, $<, $@, $(subst .o,.d,$@))

$(OBJDIR)/%.o: %.c
	$(VERBOSE_PRINTCC)  $(EE_CC) $(COMPUTED_OPT_CC) $(COMPUTED_OPT_INCLUDE) $(DEFS_CC) $(DEPENDENCY_OPT) -c $(SOURCEFILE) -o $(TARGETFILE)
	$(call make-depend, $<, $@, $(subst .o,.d,$@))


##
## Locator files
##

loc_diab.dld: $(PKGBASE)/mcu/freescale_mpc5674f/cfg/$(DLD)
	@printf "LOC\n" ;
	@cp $(PKGBASE)/mcu/freescale_mpc5674f/cfg/$(DLD) loc_diab.dld

##
## EE Library
##

libee.a: $(LIBEEOBJS)
	@printf "AR  libee.a\n" ;
	$(QUIET)$(EE_AR) rs libee.a $(LIBEEOBJS)

##
## Automatic Generation of dependencies
##

dependencies=$(subst .o,.d,$(ALLOBJS))
ifndef NODEPS
ifneq ($(MAKECMDGOALS),clean)
-include $(dependencies)
endif
endif


##
## Directories
##

.PHONY: make_directories

# Objects depend on directories, but they are not remade if directories change
$(ALLOBJS): | make_directories

make_directories: $(OBJDIRS)

# Directories are (re)created only when some of them don't exist already
$(OBJDIRS):
	@echo "MAKE_DIRECTORIES"
	$(QUIET) mkdir -p $(OBJDIRS)
