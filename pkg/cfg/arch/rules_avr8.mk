# ###*B*###
# ERIKA Enterprise - a tiny RTOS for small microcontrollers
# 
# Copyright (C) 2002-2013  Evidence Srl
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

## Author: 2013,  Giuseppe Serano

# Enable verbose output from EE_OPT
ifeq ($(call iseeopt, VERBOSE), yes)
VERBOSE = 1
endif


include $(EEBASE)/pkg/cfg/dir.mk
include $(PKGBASE)/cfg/verbose.mk
include $(PKGBASE)/cfg/compiler.mk


# Add application file to dependencies
ifneq ($(ONLY_LIBS), TRUE)
## OPT_LIBS is used to link additional libraries (e.g., for C++ support)
ifneq ($(call iseeopt, __BIN_DISTR), yes)
# Erika LIB name
EELIB = ee
ERIKALIB_NAME = lib$(EELIB)
ERIKALIB = $(ERIKALIB_NAME).a
# the EE library is built in the current directory
OPT_LIBS += -l$(EELIB) -L .
LIBDEP += $(ERIKALIB)
else
# the EE library is stored in the EE lib directory
OPT_LIBS += -l$(EELIB) -L $(EEBASE)/lib
LIBDEP += $(EEBASE)/lib/lib$(EELIB).a
endif # EEOPT __BIN_DISTR
endif # ONLY_LIBS


# Specific option from the libs dependencies
LIBDEP += $(ALL_LIBS)
# Specific option from the application makefile
LIBDEP += $(LDDEPS)

# Define the TARGET
ifeq ($(findstring atxmega, $(AVR8_MCU)), atxmega)
TARGET_NAME := $(AVR8_MCU)
else	# ATXMEGA
TARGET_NAME := avr
endif	# ATXMEGA

# Add application file to dependencies
ifneq ($(call iseeopt, __BUILD_LIBS__), yes)
TARGET := 	$(TARGET_NAME).eep \
		$(TARGET_NAME).hex \
		$(TARGET_NAME).lss \
		$(TARGET_NAME).srec
endif	# EEOPT __BUILD_LIBS__


include $(PKGBASE)/cfg/cfg.mk


#
# --------------------------------------------------------------------------
#

##
## Source files and paths
##


# Boot code containing _start should stay outside of the library in
# case of normal compilation
#ifeq ($(call iseeopt, __BIN_DISTR), yes)
#LIBSRCS += $(EE_BOOT_SRCS)
#else
#SRCS += $(EE_BOOT_SRCS)
#endif

LIBEESRCS	+= $(EE_SRCS)
LIBEEOBJS	:= \
$(addprefix $(OBJDIR)/, $(patsubst %.c,%.o,$(patsubst %.S,%.o,$(LIBEESRCS))))

LIBEESRCS	+= $(LIB_SRCS)
LIBOBJS		:= \
$(addprefix $(OBJDIR)/, $(patsubst %.c,%.o,$(patsubst %.S,%.o,$(LIBSRCS))))

SRCS		+= $(APP_SRCS)
OBJS		:= \
$(addprefix $(OBJDIR)/, $(patsubst %.c,%.o,$(patsubst %.S,%.o, $(SRCS))))

# Variable used to import dependencies
ALLOBJS = $(LIBEEOBJS) $(LIBOBJS) $(OBJS) 

OBJDIRS=$(sort $(dir $(ALLOBJS)))

# Add basic include paths
INCLUDE_PATH += $(PKGBASE) $(APPBASE) .

vpath %.c $(EE_VPATH) $(APPBASE)
vpath %.S $(EE_VPATH) $(APPBASE)

##
## Compute common variables
##

COMPUTED_ALLINCPATH := $(ALLINCPATH)
COMPUTED_OPT_LINK := $(OPT_LINK)
COMPUTED_OPT_ASM := $(OPT_ASM)
COMPUTED_OPT_AR := $(OPT_AR)
COMPUTED_OPT_CC := $(OPT_CC)

## Intel Hex file production flags
ifeq ($(AVR8_MCU),atxmega16d4)
FLASH_FLAGS = -R .eeprom -R .fuse -R .lock -R .signature
EEPROM_FLAGS = -j .eeprom
EEPROM_FLAGS += --set-section-flags=.eeprom="alloc,load"
EEPROM_FLAGS += --change-section-lma .eeprom=0 --no-change-warnings
else	# ATXMEGA
HEX_FLASH_FLAGS = -R .eeprom
HEX_EEPROM_FLAGS = -j .eeprom
HEX_EEPROM_FLAGS += --set-section-flags=.eeprom="alloc,load"
HEX_EEPROM_FLAGS += --change-section-lma .eeprom=0
endif	# ATXMEGA

SOURCEFILE = $(call native_path,$<)
TARGETFILE = $(call native_path,$@)

##
## Main rules: all clean
##

.PHONY: all clean

all:: make_directories  $(ALL_LIBS) $(TARGET)
	@printf "************************************\n"
	@printf "Compilation terminated successfully!\n"

clean::
	@printf "CLEAN\n";
	@-rm -rf *.a *.map *.elf obj
ifeq ($(AVR8_MCU),atxmega16d4)
	@-rm -rf *.eep *.hex *.lss *.srec
else
	@-rm -rf *.hex *.lss *.srec
endif


#
# --------------------------------------------------------------------------
#


VERBOSE_PRINTEEP=$(QUIET)printf "EEP  $(EXPERIMENT) $(TARGET_NAME)\\n";
$(TARGET_NAME).eep: $(TARGET_NAME).elf
	$(VERBOSE_PRINTEEP) $(EE_OBJCOPY) -O ihex $(EEPROM_FLAGS) \
	$(SOURCEFILE) $(TARGETFILE)

ifeq ($(findstring atxmega, $(AVR8_MCU)), atxmega)

VERBOSE_PRINTHEX=$(QUIET)printf "HEX  $(EXPERIMENT) $(TARGET_NAME)\\n";
$(TARGET_NAME).hex: $(TARGET_NAME).elf
	$(VERBOSE_PRINTHEX) $(EE_OBJCOPY) -O ihex $(FLASH_FLAGS) $(SOURCEFILE) \
	$(TARGETFILE)

VERBOSE_PRINTLSS=$(QUIET)printf "LSS  $(EXPERIMENT) $(TARGET_NAME)\\n";
$(TARGET_NAME).lss: $(TARGET_NAME).elf
	$(VERBOSE_PRINTLSS) $(EE_OBJDUMP) -h -S  $(SOURCEFILE) > $(TARGETFILE)

VERBOSE_PRINTSREC=$(QUIET)printf "SREC $(EXPERIMENT) $(TARGET_NAME)\\n";
$(TARGET_NAME).srec: $(TARGET_NAME).elf
	$(VERBOSE_PRINTSREC) $(EE_OBJCOPY) -O srec $(FLASH_FLAGS) \
	$(SOURCEFILE) $(TARGETFILE)

else

avr.hex: avr.elf
	@printf "HEX\n";
	$(QUIET)$(EE_OBJCOPY) -O ihex $(HEX_FLASH_FLAGS) $(SOURCEFILE) $(TARGETFILE)

avr.lss: avr.elf
	@printf "LSS\n";
	$(QUIET)$(EE_OBJDUMP) -h -D  $(SOURCEFILE) > $(TARGETFILE)

avr.srec: avr.hex
	@printf "SREC\n";
	$(QUIET)$(EE_OBJCOPY) --output-target=srec avr.hex avr.srec

endif


##
## ELF file creation
##


VERBOSE_PRINTLD=$(QUIET)printf "LD   $(EXPERIMENT) $(TARGET_NAME)\\n";
$(TARGET_NAME).elf: $(OBJS) $(LIBDEP)
	$(VERBOSE_PRINTLD) $(EE_LINK) $(COMPUTED_OPT_LINK) $(OBJS) \
	-o $(TARGETFILE) $(OPT_LIBS) -Wl,-Map=$(TARGET_NAME).map
	$(QUIET)$(EE_SIZE) $(TARGETFILE)

$(OBJDIR)/%.o: %.S
	$(VERBOSE_PRINTASM) $(EE_ASM) $(DEFS_ASM) $(COMPUTED_ALLINCPATH) \
	$(COMPUTED_OPT_ASM) $(DEPENDENCY_OPT) -o $(TARGETFILE) $(SOURCEFILE)
	$(QUIET)$(call make-depend, $(subst .o,.d,$(@)))

$(OBJDIR)/%.o: %.c
	$(VERBOSE_PRINTCC) $(EE_CC) $(DEFS_CC) $(COMPUTED_ALLINCPATH) \
	$(COMPUTED_OPT_CC) $(DEPENDENCY_OPT) -o $(TARGETFILE) $(SOURCEFILE)
	$(QUIET)$(call make-depend, $(subst .o,.d,$(@)))


##
## EE Library
##


VERBOSE_PRINTAR=$(QUIET)printf "AR   $(EXPERIMENT) $(ERIKALIB_NAME)\\n";
$(ERIKALIB): $(LIBEEOBJS)
	$(VERBOSE_PRINTAR) $(EE_AR) $(COMPUTED_OPT_AR) $(ERIKALIB) $(LIBEEOBJS)


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
