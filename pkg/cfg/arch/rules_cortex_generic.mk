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

##
## Cortex M4 compilation rules
##
## Author: 2011,  Giuseppe Serano
##
## Based on rules_cortex_m0.mk and on ARMv7-M Architecture Reference Manual
##


# Enable verbose output from EE_OPT
ifeq ($(call iseeopt, VERBOSE), yes)
VERBOSE = 1
endif

ERIKALIB = libee.a

# Initial definition of target all as predefined
all:

include $(EEBASE)/pkg/cfg/dir.mk
include $(PKGBASE)/cfg/verbose.mk
include $(PKGBASE)/cfg/compiler.mk

ifneq ($(ONLY_LIBS), TRUE)

ifneq ($(call iseeopt, __BIN_DISTR), yes)
LIBDEP += $(ERIKALIB)
else
LIBDEP += $(EEBASE)/lib/$(ERIKALIB)
endif

endif	# ONLY_LIBS


#Includes from Compiler
INCLUDE_PATH += $(CG_INCLUDE_DIR)

# Specific option from the libs dependencies
LIBDEP += $(ALL_LIBS)

# Specific option from the application makefile
LIBDEP += $(LDDEPS)


include $(PKGBASE)/cfg/cfg.mk

# MCU
ifeq ($(call iseeopt, __STELLARIS__), yes)
#~ STELLARIS_MODEL
#~ STELLARIS_LINKERSCRIPT
#~ STELLARIS_INCLUDE_C
#~ STELLARIS_INCLUDE_S
#~ STELLARIS_STARTUP
ifneq ($(call iseeopt, __LM4F232xxxx__), yes)
CORTEX_MCU_MODEL = $(STELLARIS_MODEL)
CORTEX_MCU_STARTUP = $(STELLARIS_STARTUP)
CORTEX_MCU_LINKERSCRIPT = $(STELLARIS_LINKERSCRIPT)
else	# !__LM4F232xxxx__
CORTEX_MCU_MODEL = LM4F232XXX
CORTEX_MCU_LINKERSCRIPT = $(EEBASE)/pkg/mcu/ti_stellaris_lm4f232xxxx/src/ee_ld_script_ccs.cmd
endif	# __LM4F232xxxx__
TARGET_NAME = c_mX
endif	# __STELLARIS__

ifeq ($(call iseeopt, __LPCXPRESSO__), yes)
#~ LPCXPRESSO_MODEL
#~ LPCXPRESSO_LINKERSCRIPT
#~ LPCXPRESSO_INCLUDE_C
#~ LPCXPRESSO_INCLUDE_S
#~ LPCXPRESSO_STARTUP
ifneq ($(call iseeopt, __LPC12xx__), yes)
CORTEX_MCU_MODEL = $(LPCXPRESSO_MODEL)
CORTEX_MCU_STARTUP = $(LPCXPRESSO_STARTUP)
CORTEX_MCU_LINKERSCRIPT = $(LPCXPRESSO_LINKERSCRIPT)
else	# !__LPC12xx__
CORTEX_MCU_MODEL = LPC12XX
CORTEX_MCU_LINKERSCRIPT = $(EEBASE)/pkg/mcu/nxp_lpcxpresso_lpc12xx/src/iar/lpc12xx_flash.icf
CORTEX_MCU_STARTUP = $(CRT0_SRCS)
endif	# __LPC12xx__
TARGET_NAME = c_m0
endif	# __LPCXPRESSO__

ifndef CORTEX_MCU_MODEL
$(error No known MCU model found in EE_OPT)
endif	# CORTEX_MCU_MODEL

# Read MCU-specific file, if it exists, but don't make it
-include $(PKGBASE)/cfg/arch/rules_cortex_$(CORTEX_MCU_MODEL).mk
$(PKGBASE)/cfg/arch/rules_cortex_$(CORTEX_MCU_MODEL).mk: ;

EE_BOOT_SRCS := $(CORTEX_MCU_STARTUP)

# Boot code containing _start should stay outside of the library in
# case of normal compilation
ifeq ($(call iseeopt, __BIN_DISTR), yes)
LIBSRCS += $(EE_BOOT_SRCS)
else
SRCS += $(EE_BOOT_SRCS)
endif

# Add a custom linker script if provided by the user
LINKDEP += $(CORTEX_MCU_LINKERSCRIPT)

#
# --------------------------------------------------------------------------
#

##
## Source files and paths
##
LIBEESRCS += $(EE_SRCS)
LIBEEOBJS := $(addprefix $(OBJDIR)/, $(patsubst %.c, %.o, $(patsubst %.s, %.o, \
$(patsubst %.asm, %.o, $(LIBEESRCS)))))

LIBOBJS := $(addprefix $(OBJDIR)/, $(patsubst %.c, %.o, $(patsubst %.s, %.o, \
$(patsubst %.asm, %.o, $(LIBSRCS)))))

SRCS += $(APP_SRCS)

OBJS := $(addprefix $(OBJDIR)/, $(sort $(patsubst %.cpp, %.o, \
$(patsubst %.cxx, %.o, $(patsubst %.cc, %.o, $(patsubst %.C, %.o, \
$(CXX_SRCS))))) $(patsubst %.c, %.o, $(patsubst %.s, %.o, \
$(patsubst %.asm, %.o, $(SRCS))))))

# Variable used to import dependencies
ALLOBJS = $(LIBEEOBJS) $(LIBOBJS) $(OBJS) 

OBJDIRS=$(sort $(dir $(ALLOBJS)))

INCLUDE_PATH += $(PKGBASE) $(APPBASE) . $(CG_INLCUDE_DIR)

vpath %.c $(EE_VPATH) $(APPBASE)
vpath %.s $(EE_VPATH) $(APPBASE)

## Compute common variables ##
COMPUTED_INCLUDE_PATH := $(OPT_INCLUDE)
COMPUTED_OPT_LINK := $(OPT_LINK)
COMPUTED_OPT_ASM := $(OPT_ASM)
COMPUTED_OPT_CC := $(OPT_CC)
COMPUTED_OPT_AR := $(OPT_AR)
COMPUTED_OPT_OBJDUMP := $(OPT_OBJDUMP)
COMPUTED_LINKERSCRIPT := $(call native_path, $(CORTEX_MCU_LINKERSCRIPT))

ifeq ($(call iseeopt, __IAR__), yes)

COMPUTED_OPT_BIN2HEX := $(OPT_BIN2HEX)

else	# __IAR__ (Default compiler toolchain)

COMPUTED_OPT_HEX2BIN := $(OPT_HEX2BIN)
COMPUTED_OPT_OBJDUMP2HEX := $(OPT_OBJDUMP2HEX)

endif	# !__IAR__ (Default compiler toolchain)

## Select input filename format ##
SOURCEFILE = $(call native_path,$<)
TARGETFILE = $(call native_path,$@)
## 


## Main rules: all clean ##

.PHONY: all clean

all: make_directories $(ALL_LIBS) $(TARGET)
	@echo "************************************"
	@echo "Compilation terminated successfully!"

clean:
	@-rm -rf obj *.a *.map *.sim *.$(CG_BIN_EXTENSION) \
	*.$(CG_OUT_EXTENSION) *.$(CG_OBJDUMP_EXTENSION) *.$(CG_HEX_EXTENSION)
# deps deps.pre ee_c_m0regs.h
	@echo "CLEAN";

### Target file creation ###

ifeq ($(call iseeopt, __IAR__), yes)

$(TARGET_NAME).$(CG_OBJDUMP_EXTENSION): $(TARGET_NAME).$(CG_OUT_EXTENSION)
	@echo "OBJDUMP";
	$(QUIET)$(EE_BIN2HEX) $(COMPUTED_OPT_OBJDUMP) \
	$(TARGET_NAME).$(CG_OUT_EXTENSION) $(TARGET_NAME).$(CG_OBJDUMP_EXTENSION)

$(TARGET_NAME).$(CG_HEX_EXTENSION): $(TARGET_NAME).$(CG_OUT_EXTENSION)
	@echo "BIN2HEX";
	$(QUIET)$(EE_BIN2HEX) $(COMPUTED_OPT_BIN2HEX) \
	$(TARGET_NAME).$(CG_OUT_EXTENSION) $(TARGET_NAME).$(CG_HEX_EXTENSION)

else	# __IAR__ (Default compiler toolchain)

$(TARGET_NAME).$(CG_BIN_EXTENSION): $(TARGET_NAME).$(CG_OUT_EXTENSION) \
				    $(TARGET_NAME).$(CG_HEX_EXTENSION)
	@echo "HEX2BIN";
	$(QUIET)$(EE_HEX2BIN) $(COMPUTED_OPT_HEX2BIN) -o $(TARGETFILE) \
	$(TARGET_NAME).$(CG_HEX_EXTENSION) $(TARGET_NAME).$(CG_OUT_EXTENSION)

$(TARGET_NAME).$(CG_HEX_EXTENSION): $(TARGET_NAME).$(CG_OBJDUMP_EXTENSION)
	@echo "OBJDUMP2HEX";
	$(QUIET)$(EE_OBJDUMP2HEX) $(COMPUTED_OPT_OBJDUMP2HEX) \
	$(SOURCEFILE) > $(TARGETFILE)

$(TARGET_NAME).$(CG_OBJDUMP_EXTENSION): $(TARGET_NAME).$(CG_OUT_EXTENSION)
	@echo "OBJDUMP";
	$(QUIET)$(EE_OBJDUMP) $(COMPUTED_OPT_OBJDUMP) \
	$(SOURCEFILE) > $(TARGETFILE)

endif	# __IAR__ (Default compiler toolchain)

$(TARGET_NAME).$(CG_OUT_EXTENSION): $(OBJS) $(LINKDEP) $(LIBDEP) 
	@echo "LD";
ifeq ($(call iseeopt, __IAR__), yes)
	$(QUIET)$(EE_LINK) $(COMPUTED_OPT_LINK) -o $@ $(OBJS) $(OPT_LIBS) \
	--config $(COMPUTED_LINKERSCRIPT)
else
ifneq ($(call iseeopt, __CCS__), yes)
	$(QUIET)$(EE_LINK) $(COMPUTED_OPT_LINK) -o $@ $(OBJS) $(OPT_LIBS)
else
	$(QUIET)$(EE_LINK) $(COMPUTED_OPT_LINK) \
	-m$(call native_path, $(patsubst %.$(CG_OUT_EXTENSION), %.map, $@)) \
	-o $@ $(OBJS) $(OPT_LIBS) $(COMPUTED_LINKERSCRIPT)
endif
endif

### Object file creation ###

# produce the object file from assembly code in a single step
$(OBJDIR)/%.o: %.s
ifneq ($(call iseeopt, __CCS__), yes)
	$(VERBOSE_PRINTASM) $(EE_ASM) $(COMPUTED_OPT_ASM) \
	$(COMPUTED_INCLUDE_PATH) $(DEFS_ASM) $(SOURCEFILE) -o $(TARGETFILE)
else
	$(VERBOSE_PRINTASM) $(EE_ASM) $(COMPUTED_OPT_ASM) \
	$(COMPUTED_INCLUDE_PATH) $(DEFS_ASM) $(DEPENDENCY_OPT) $(SOURCEFILE) \
	--output_file $(TARGETFILE)
endif

# produce the object file from C code in a single step
$(OBJDIR)/%.o: %.c
ifneq ($(call iseeopt, __CCS__), yes)
	$(VERBOSE_PRINTCC) $(EE_CC) $(COMPUTED_OPT_CC) \
	$(COMPUTED_INCLUDE_PATH) $(DEFS_CC) $(DEFS_ISR) $(DEPENDENCY_OPT) $(SOURCEFILE) \
	-o $(TARGETFILE)
else
	$(VERBOSE_PRINTCC) $(EE_CC) $(COMPUTED_OPT_CC) \
	$(COMPUTED_INCLUDE_PATH) $(DEFS_CC) $(DEFS_ISR) $(DEPENDENCY_OPT) $(SOURCEFILE) \
	--output_file $(TARGETFILE)
endif
	$(QUIET)$(call make-depend, $<, $@, $(subst .o,.d,$@))

# TODO: produce the object file from C++ code in a single step
# $(OBJDIR)/%.o: %.cpp
# $(OBJDIR)/%.o: %.cxx
# $(OBJDIR)/%.o: %.cc
# $(OBJDIR)/%.o: %.C

##
## EE Library
##

#libee.a: $(LIBEEOBJS)
$(ERIKALIB): $(LIBEEOBJS)
	@echo "AR  $(ERIKALIB)";
	$(QUIET)$(EE_AR) $(COMPUTED_OPT_AR) $@ $^

##
## Directories
##

.PHONY: make_directories

## Objects depend on directories, but they are not remade if directories change
$(ALLOBJS): | make_directories

make_directories: $(OBJDIRS)

## Directories are (re)created only when some of them don't exist already
$(OBJDIRS): 
	@echo "MAKE_DIRECTORIES"
	$(QUIET)mkdir -p $(OBJDIRS)

##
## Automatic Generation of dependencies
##

dependencies=$(subst .o,.d,$(ALLOBJS))
ifneq ($(call iseeopt, NODEPS), yes) 
ifneq ($(MAKECMDGOALS),clean)
-include $(dependencies)
endif
endif