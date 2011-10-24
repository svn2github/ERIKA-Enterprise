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
## IAR compiler
##
## Author: 2011,  Gianluca Franchino
##


# Enable verbose output from EE_OPT
ifeq ($(call iseeopt, VERBOSE), yes)
VERBOSE = 1
endif

# Initial definition of target all as predefined
all:

include $(EEBASE)/pkg/cfg/dir.mk
include $(PKGBASE)/cfg/verbose.mk
include $(PKGBASE)/cfg/compiler.mk

#IAR_DATA_DIR refers to the location of IAR libraries
IAR_DATA_DIR := $(IAR_CCDIR)

IAR_LIB_DIR := $(IAR_DATA_DIR)/lib
IAR_INCLUDE_DIR := $(IAR_DATA_DIR)/inc/NXP
ifeq ($(call iseeopt, __USE_CUSTOM_LINKER_SCRIPT__), yes)
IAR_LINKER_DIR :=
else
IAR_LINKER_DIR := $(IAR_DATA_DIR)/config
endif
ERIKALIB = libee.a


#Add application file to dependencies
ifneq ($(ONLY_LIBS), TRUE)

## OPT_LIBS is used to link additional libraries (e.g., for C++ support)
# the EE library is built in the current directory
## Libraries from IAR. Put here the link options --search (instead of -L)
## Option -l dooes not exist with IAR linker, just put the file name of the library
##if we need to link any standard library
OPT_LIBS += $(ERIKALIB) --search .
LIBDEP += $(ERIKALIB)

endif

# Specific option from the libs dependencies
LIBDEP += $(ALL_LIBS)

# Specific option from the application makefile
LIBDEP += $(LDDEPS)


#Includes from IAR
INTERNAL_IARINCLUDEDIR := $(call native_path,$(IAR_INCLUDE_DIR))
INCLUDE_PATH += $(INTERNAL_IARINCLUDEDIR)

ifneq ($(ONLY_LIBS), TRUE)
TARGET := c_m0.hex c_m0.out
endif

include $(PKGBASE)/cfg/cfg.mk

# Add crt0 if not provided by the user
ifneq ($(call iseeopt, __USE_CUSTOM_CRT0__), yes)

ifeq ($(call iseeopt, __IAR__), yes)
CORTEX_M0_STARTUP := $(EEBASE)/pkg/mcu/cortex_m0/src/iar/$(CRT0_SRCS)
else
$(Error Compiler not defined (As today, only the IAR compiler is supported!!!)
endif
# Add startup file from ARM library
EE_BOOT_SRCS := fromiar/$(CRT0_SRCS)
endif

# Boot code containing _start should stay outside of the library in
# case of normal compilation
ifeq ($(call iseeopt, __BIN_DISTR), yes)
LIBSRCS += $(EE_BOOT_SRCS)
else
SRCS += $(EE_BOOT_SRCS)
endif

# Add a custom linker script if provided by the user
ifeq ($(call iseeopt, __USE_CUSTOM_LINKER_SCRIPT__), yes)
OPT_LINK += --config $(CORTEX_M0_LINKERSCRIPT)
else
#OPT_LINK += --config $(IAR_CCDIR)/$(CORTEX_M0_LINKERSCRIPT)
OPT_LINK += --config $(CORTEX_M0_LINKERSCRIPT)
endif 

#
# --------------------------------------------------------------------------
#

##
## Source files and paths
##
LIBEESRCS += $(EE_SRCS)
LIBEEOBJS := $(addprefix $(OBJDIR)/, $(patsubst %.c,%.o,$(patsubst %.s,%.o,$(LIBEESRCS))))

LIBOBJS := $(addprefix $(OBJDIR)/, $(patsubst %.c,%.o,$(patsubst %.s,%.o,$(LIBSRCS))))

SRCS += $(APP_SRCS)
OBJS=$(addprefix $(OBJDIR)/, $(sort \
$(patsubst %.cxx, %.o, \
$(patsubst %.cc, %.o, $(patsubst %.cpp, %.o, \
$(patsubst %.C, %.o,$(CXX_SRCS)))))\
$(patsubst %.c, %.o, \
$(patsubst %.S, %.o, $(patsubst %.s, %.o, $(SRCS))))))

# Variable used to import dependencies
ALLOBJS = $(LIBEEOBJS) $(LIBOBJS) $(OBJS) 


OBJDIRS=$(sort $(dir $(ALLOBJS))) fromiar

INCLUDE_PATH += $(PKGBASE) $(APPBASE) $(OUTBASE)

vpath %.c $(EE_VPATH) $(APPBASE)
vpath %.s $(EE_VPATH) $(APPBASE)

## Compute common variables ##
COMPUTED_INCLUDE_PATH := $(addprefix -I, $(INCLUDE_PATH))
COMPUTED_OPT_LINK := $(OPT_LINK)
COMPUTED_OPT_ASM := $(OPT_ASM)
COMPUTED_OPT_CC := $(OPT_CC)

## Select input filename format ##
SOURCEFILE = $(call native_path,$<)
TARGETFILE = $(call native_path,$@)
## 


## Main rules: all clean ##

.PHONY: all clean

all: make_directories $(ALL_LIBS) $(TARGET)

clean:
	@-rm -rf *.a *.map *.sim *.$(IAR_EXTENSION) *.objdump *.hex deps deps.pre obj ee_c_m0regs.h
# to support "make clean all"
ifeq ($(findstring all,$(MAKECMDGOALS)),all)
	@echo "CLEAN (also \"all\" specified, fromiar directory not removed)"
else
	@echo "CLEAN";
	@-rm -rf fromiar
endif

c_m0.objdump: c_m0.$(IAR_EXTENSION)
	@echo "OBJDUMP";
	$(QUIET)$(EE_BIN2HEX) --code c_m0.$(IAR_EXTENSION) c_m0.objdump

c_m0.hex: c_m0.$(IAR_EXTENSION)
	@echo "BIN2HEX";
	$(QUIET)$(EE_BIN2HEX) --ihex c_m0.$(IAR_EXTENSION) c_m0.hex
	
	
## Object file creation ###
c_m0.$(IAR_EXTENSION): $(OBJS) $(LINKDEP) $(LIBDEP) 
#@echo "OBJS = $(OBJS)";
	@echo "LD";
	$(QUIET)$(EE_LINK) $(COMPUTED_OPT_LINK) -o $@ $(OBJS) $(OPT_LIBS) --map c_m0.map
	@echo "************************************"
	@echo "Compilation terminated successfully!"

#	-o $(TARGETFILE) $(OBJS) $(OPT_LIBS) \
		
		
#--start-group $(OPT_LIBS) --end-group 

# produce the object file from assembly code in a single step
#$(OBJDIR)/%.o: %.s fromiar/$(CRT0_SRCS)
$(OBJDIR)/%.o: %.s
	$(VERBOSE_PRINTASM) $(EE_ASM) $(COMPUTED_OPT_ASM) $(COMPUTED_INCLUDE_PATH) $(DEFS_ASM) $(SOURCEFILE) -o $(TARGETFILE)
#$(QUIET) $(call make-depend, $<, $@, $(subst .o,.d,$@))

# produce the object file from C code in a single step
$(OBJDIR)/%.o: %.c
	$(VERBOSE_PRINTCC) $(EE_CC) $(COMPUTED_OPT_CC) $(COMPUTED_INCLUDE_PATH) $(DEFS_CC) $(DEPENDENCY_OPT) $(SOURCEFILE) -o $(TARGETFILE)
	$(QUIET) $(call make-depend, $<, $@, $(subst .o,.d,$@))


#$(OBJDIR)/fromiar/cstartup_M.o: fromiar/$(CRT0_SRCS)
##	$(VERBOSE_PRINTASM) $(EE_ASM) $(COMPUTED_OPT_ASM) $(SOURCEFILE) -o $(TARGETFILE)
#	
#$(OBJDIR)/fromiar/cstartup_M.o: fromiar/cstartup_M.s
#$(OBJDIR)/fromiar/$(patsubst %.s, %.o, $(CRT0_SRCS)): fromiar/$(CRT0_SRCS)
#$(VERBOSE_PRINTASM) $(EE_ASM) $(COMPUTED_OPT_ASM) $(SOURCEFILE) -o $(TARGETFILE)
	
##
## IAR CORTEX_M0 (NXP LPC1227) files
##

ifneq ($(call iseeopt, __USE_CUSTOM_CRT0__), yes)
 
fromiar/$(CRT0_SRCS): $(CORTEX_M0_STARTUP) 
	@echo "CP default startup file $(CRT0_SRCS)"; cat $< > $@

else
$(CRT0_SRCS):
	@echo "Start up file provided by the user";
endif

# Check if the MCU model has been defined
ifneq ($(CORTEX_M0_MODEL),)
fromiar/$(CORTEX_M0_INCLUDE_C): $(APPBASE)/CM0/DeviceSupport/NXP/LPC12xx/$(CORTEX_M0_INCLUDE_C) | make_directories
	@echo "CP $(CORTEX_M0_INCLUDE_C)"
	$(QUIET)cat $< > $@
else
$(error Cortex_m0 model not defined!!!)
endif
	
###
### Locator files
###
#
##if IAR_CCDIR is defined
#loc_iar.icf: $(IAR_LINKER_DIR)/$(IAR_LINKERSCRIPT)
#	@echo "LOC" ; cp $(IAR_LINKER_DIR)/$(IAR_LINKERSCRIPT) loc_iar.icf
#

##
## EE Library
##

#libee.a: $(LIBEEOBJS)
$(ERIKALIB): $(LIBEEOBJS)
	@echo "AR  libee.a";
	$(QUIET)$(EE_AR) --create $@ $^

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
	$(QUIET) mkdir -p $(OBJDIRS)
	
##
## Automatic Generation of dependencies
##

dependencies=$(subst .o,.d,$(ALLOBJS))
ifneq ($(call iseeopt, NODEPS), yes) 
ifneq ($(MAKECMDGOALS),clean)
-include $(dependencies)
endif
endif