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

# Enable verbose output from EE_OPT
ifeq ($(findstring VERBOSE,$(EEOPT)) , VERBOSE)
VERBOSE = 1
endif

include $(EEBASE)/pkg/cfg/dir.mk
include $(PKGBASE)/cfg/verbose.mk
include $(PKGBASE)/cfg/compiler.mk

ifneq ($(findstring __E200Z7_EXECUTE_FROM_RAM__,$(EEOPT)),)
DLD := ram.dld
else
DLD := rom.dld
endif

OPT_LINK += loc_diab.dld -e __start
LINKDEP = loc_diab.dld

CRT0_SRCS := pkg/mcu/freescale_mpc5674f/src/ee_boot.S
OPT_TARGET := -t PPCE200Z6NES:windiss
OPT_CC += $(OPT_TARGET)
OPT_ASM += $(OPT_TARGET)
OPT_LINK += $(OPT_TARGET)

# Add application file to dependencies
ifneq ($(ONLY_LIBS), TRUE)

# OPT_LIBS is used to link additional libraries (e.g., for C++ support)
ifneq ($(findstring __BIN_DISTR,$(EEALLOPT)), __BIN_DISTR)
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
ifneq ($(findstring __BUILD_LIBS__,$(EEOPT)) , __BUILD_LIBS__)
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
ifeq ($(findstring __BIN_DISTR,$(EEOPT)), __BIN_DISTR)
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
THUMB_OBJS= $(addprefix $(OBJDIR)/, $(patsubst %.c,%.to, $(THUMB_SRCS)))


vpath %.cd $(APPBASE)
vpath %.Sd $(APPBASE)
vpath %.td $(APPBASE)
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
COMPUTED_OPT_TCC := $(OPT_TCC)

SOURCEFILE = $<
TARGETFILE = $@
SRCFILE = $(patsubst %.o,%.src,$(TARGETFILE))
TOSRCFILE = $(patsubst %.to,%.src,$(TARGETFILE))

##
## Main rules: all clean
##

.PHONY: all clean

all:: make_directories $(ALL_LIBS) $(TARGET)
	@printf "************************************\n\n"
	@printf "Compilation terminated successfully!\n"

clean::
	@printf "CLEAN\n" ;
	@-rm -rf *.a *.ld *.map *.elf *.objdump deps deps.pre debug.bat t32* obj *.men

##
## ELF file creation
##

z7.elf: $(CRT0) $(OBJS) $(THUMB_OBJS) $(LINKDEP) $(LIBDEP)
	@printf "LD\n";
	$(QUIET)$(EE_LINK) $(COMPUTED_OPT_LINK)				\
		-o $(TARGETFILE) $(OPT_CRT0) $(OBJS) $(OPT_LIBS) -lc -m > z7.map

$(OBJDIR)/%.o: %.S
	$(VERBOSE_PRINTPRE)	$(EE_CC)  $(COMPUTED_ALLINCPATH) $(DEFS_ASM) -E $< > $(SRCFILE)
	$(VERBOSE_PRINTASM)	$(EE_ASM) $(COMPUTED_OPT_ASM)  -o $(TARGETFILE) $(SRCFILE)

$(OBJDIR)/%.o: %.c
	$(VERBOSE_PRINTCC)  $(EE_CC) $(COMPUTED_OPT_CC) $(COMPUTED_ALLINCPATH) $(DEFS_CC) $< -o $(TARGETFILE)
	$(VERBOSE_PRINTASM)	$(EE_CC) $(COMPUTED_OPT_CC) $(COMPUTED_ALLINCPATH) $(DEFS_CC) $< -S -o $(SRCFILE)

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

# deps depends on the flag and not on the PHONY rule!
deps: $(OBJDIR)/.make_directories_flag deps.pre
	@printf "GEN deps\n"
	@sed "s/ \<\([A-Za-z]\):/ \/cygdrive\/\l\1/g" < deps.pre > deps

deps.pre: $(addprefix $(OBJDIR)/, $(patsubst %.S,%.Sd,$(patsubst %.c,%.cd, $(SRCS) $(LIBEESRCS) $(LIBSRCS))))
	@printf "GEN deps.pre\n" ; cat $^ > deps.pre

# generate dependencies for .c files and add "file.cd" to the target
$(OBJDIR)/%.cd: %.c
	$(VERBOSE_PRINTDEP) $(EE_CC) $(COMPUTED_OPT_CC)			\
		$(COMPUTED_ALLINCPATH) $(DEFS_CC) -Xmake-dependency $<	\
		> $(TARGETFILE).tmp
	@echo -n $(TARGETFILE) $(dir $(TARGETFILE))			\
		| cat - $(TARGETFILE).tmp > $(TARGETFILE)
	@rm -rf $(TARGETFILE).tmp
	@test -s $(TARGETFILE) || rm -f $(TARGETFILE)

# generate dependencies for .S files and add "file.Sd" to the target
$(OBJDIR)/%.Sd: %.S
	$(VERBOSE_PRINTDEP) $(EE_CC) $(COMPUTED_ALLINCPATH)		\
		$(DEFS_ASM) -Xmake-dependency $<			\
		> $(TARGETFILE).tmp
	@echo -n $(TARGETFILE) $(dir $(TARGETFILE))			\
		| cat - $(TARGETFILE).tmp > $(TARGETFILE)
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
	$(QUIET)mkdir -p $(dir $(basename $(addprefix $(OBJDIR)/, $(CRT0_SRCS) $(SRCS) $(LIBEESRCS) $(LIBSRCS))))
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
ifneq ($(findstring NODEPS,$(EEALLOPT)), NODEPS)
-include deps
endif
endif
endif