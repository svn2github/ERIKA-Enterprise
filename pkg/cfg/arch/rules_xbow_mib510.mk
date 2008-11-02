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
## CVS: $Id: rules_xbow_mib510.mk,v 1.2 2006/12/21 15:38:52 pj Exp $


include $(EEBASE)/pkg/cfg/dir.mk
include $(PKGBASE)/cfg/verbose.mk
include $(PKGBASE)/cfg/compiler.mk

# avr5-related directories
# we should look if these need to be moved inside dir.mk
BINDIRCC = $(ECLIPSEBASE)/../../cygdrive/c/Programmi/AVRGCC\ 3.4.4/avrgcc/bin



# OPT_LIBS is used to link additional libraries (e.g., for C++ support)
ifneq ($(findstring __BIN_DISTR,$(EEALLOPT)), __BIN_DISTR) 
# the EE library is built in the current directory
OPT_LIBS += -lee -L . 
LIBDEP = libee.a
else
# the EE library is stored in the EE lib directory
#OPT_LIBS += -lee_$(EELIB) -L `cygpath -w $(EEBASE)/lib`
#LIBDEP = $(EEBASE)/lib/libee_$(EELIB).a
OPT_LIBS += -l$(EELIB) -L `cygpath -w $(EEBASE)/lib` -l libgcc -L `cygpath -w $(DIRLIBGCC)` 
LIBDEP = $(EEBASE)/lib/lib$(EELIB).a
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

LIBSRCS += $(EE_SRCS)
LIBOBJS = $(patsubst %.c,%.o,$(patsubst %.S,%.o,$(LIBSRCS)))

SRCS += $(APP_SRCS)
OBJS= $(patsubst %.c,%.o,$(patsubst %.S,%.o,$(notdir $(SRCS))))
#SRCS += $(addprefix ../, $(APP_SRCS))
#OBJS= $(patsubst %.c,%.o,$(patsubst %.S,%.o,$(SRCS)))

#vpath %.elf $(OUTBASE) $(shell mkdir -p $(OUTBASE))
#vpath %.o $(OUTBASE)
vpath %.cd $(APPBASE)
vpath %.Sd $(APPBASE)
vpath %.c $(EE_VPATH) $(APPBASE) 
vpath %.S $(EE_VPATH) $(APPBASE)
#vpath %.src $(OUTBASE)



## Intel Hex file production flags
HEX_FLASH_FLAGS = -R .eeprom

HEX_EEPROM_FLAGS = -j .eeprom
HEX_EEPROM_FLAGS += --set-section-flags=.eeprom="alloc,load"
HEX_EEPROM_FLAGS += --change-section-lma .eeprom=0

##
## Main rules: all clean
##

.PHONY: all clean

all:: atmega128.elf atmega128.lss atmega128.hex

clean::
	@echo CLEAN
	@-rm -rf *.S *.o *.cd *.Sd *.a *.src *.ld *.map *.elf *.objdump deps

atmega128.lss:atmega128.elf
	$(EE_OBJDUMP) -h -S  $< > $@
atmega128.hex:atmega128.elf
	$(EE_OBJCOPY) -O ihex $(HEX_FLASH_FLAGS)  `cygpath -w $<` $@


##
## ELF file creation
##

ifneq ($(findstring __BIN_DISTR ,$(EEALLOPT)), __BIN_DISTR)

##atmega128.elf:$(OBJS) $(LIBOBJS)
##	$(EE_CC) -mmcu=atmega128 -Wl,-Map=atmega128.map  -o `cygpath -w $@`  $(OBJS) $(LIBOBJS)


atmega128.elf: $(OBJS) $(LIBDEP) 
	@echo LD
	$(EE_CC) -mmcu=atmega128   \
                     -Wl,-Map=atmega128.map -o `cygpath -w $@` $(OBJS) \
                      -Wl,--start-group $(OPT_LIBS) --end-group \

else

atmega128.elf: $(OBJS) $(LINKDEP) \
			$(EEBASE)/lib/libee_$(EELIB).a
	@echo LD lib/liberika_$(EELIB).a
	$(EE_AR) -x $(EEBASE)/lib/libee_$(EELIB).a 
	$(EE_LINK) $(OPT_LINK) \
                     -o $@ $(OBJS) \
                     --start-group $(OPT_LIBS)  --end-group \
	             -M > atmega128.map
endif


%.o: %.S
	$(VERBOSE_PRINTCPP)
	$(EE_ASM) $(ALLINCPATH) $(DEFS_ASM) -E `cygpath -w $<` > $(notdir $(patsubst %.o,%.src,$@))
	$(VERBOSE_PRINTASM)
	$(EE_ASM) $(OPT_ASM) `cygpath -w $(notdir $(patsubst %.o,%.src,$@))` -o $(notdir $@)
%.o: %.c
	$(VERBOSE_PRINTCC)
	$(EE_CC) $(OPT_CC) $(DEFS_CC) `cygpath -w $<` -o $(notdir $@)
ifeq ($(findstring DEBUG,$(EEOPT)) , DEBUG)
	$(VERBOSE_PRINTSRC)
	$(EE_CC) $(OPT_CC) $(DEFS_CC) `cygpath -w $<` -S -o $(notdir $(patsubst %.o,%.S,$@))
endif



%.to: %.c
	$(VERBOSE_PRINTTCC)
	$(EE_TCC) $(OPT_TCC) $(DEFS_TCC) `cygpath -w $<` -o $(notdir $@)
ifeq ($(findstring DEBUG,$(EEOPT)) , DEBUG)
	$(VERBOSE_PRINTSRC)
	$(EE_TCC) $(OPT_TCC) $(DEFS_TCC) `cygpath -w $<` -S -o $(notdir $(patsubst %.to,%.src,$@))
endif

##
## Locator files
##



##
## EE Library
##

libee.a: $(LIBOBJS)
	@echo AR  libee.a
	$(EE_AR) rs libee.a $(LIBOBJS) 


##
## Automatic Generation of dependencies
##

# deps contains all the dependencies
deps: $(patsubst %.S,%.Sd,$(patsubst %.c,%.cd,$(notdir $(SRCS) $(LIBSRCS))))
	@echo GEN deps
	@cat $(patsubst %.S,%.Sd,$(patsubst %.c,%.cd,$(notdir $(SRCS) $(LIBSRCS)))) > deps

# generate dependencies for .c files and add "file.cd" to the target
%.cd: %.c 
	$(VERBOSE_PRINTDEP)
	$(EE_CC) $(OPT_CC) $(DEFS_CC) -M `cygpath -w $<` | sed "s/\($*\)\.o[ :]*/\1\.o $(notdir $@): /g" > $@ 
	@test -s $@ || rm -f $@

# generate dependencies for .S files and add "file.Sd" to the target
%.Sd: %.S
	$(VERBOSE_PRINTDEP)
	$(EE_CC) $(ALLINCPATH) $(DEFS_ASM) -M `cygpath -w $<` | sed "s/\($*\)\.o[ :]*/\1\.src $(notdir $@): /g" > $@ 
	@test -s $@ || rm -f $@

#
# --------------------------------------------------------------------------
#

ifndef NODEPS
ifneq ($(MAKECMDGOALS),clean)
-include deps
endif
endif



