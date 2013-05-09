# ###*B*###
# ERIKA Enterprise - a tiny RTOS for small microcontrollers

# Copyright (C) 2002-2012  Evidence Srl

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

## Author: 2012 Errico Guidieri

#Used by start scripts
T32TMP ?= C:/Temp
#Used to export symbols to slave cpus
GLOBAL_LINKSCRIPT := shared_sym.lsl
#Slave CPU List
SLAVE_CPUS := $(filter-out CPU_MASTER, $(CPU_LIST))
#Master ELF Target
MASTER_ELF_PATH := $(CPU_MASTER_DIR)/$(CPU_MASTER_ELF)

#Slave ELFs PATH
ifdef CPU1_ELF
CPU1_ELF_PATH := $(CPU1_DIR)/$(CPU1_ELF)
endif
ifdef CPU2_ELF
CPU2_ELF_PATH := $(CPU2_DIR)/$(CPU2_ELF)
endif

#ORTI Support
ifneq ($(wildcard $(CPU_MASTER_DIR)/system.orti),)
MASTER_ORTI_CD      := \&core0 cd $(CPU_MASTER_DIR)
MASTER_ORTI_CMD     := \&core0 do orti.cmm
MASTER_ORTI_CD_BACK := \&core0 cd ..
ifdef CPU1_ELF
CPU1_ORTI_CD        := \&core1 cd $(CPU1_DIR)
CPU1_ORTI_CMD       := \&core1 do orti.cmm
CPU1_ORTI_CD_BACK   := \&core1 cd ..
endif
ifdef CPU2_ELF
CPU2_ORTI_CD        := \&core2 cd $(CPU2_DIR)
CPU2_ORTI_CMD       := \&core2 do orti.cmm
CPU2_ORTI_CD_BACK   := \&core2 cd ..
endif

endif

#Preprocessing command
T32_SED_COMMAND = 's-\#MASTER_ELF\#-$(MASTER_ELF_PATH)-g' 's-\#CPU1_ELF\#-$(CPU1_ELF_PATH)-g' 's-\#CPU2_ELF\#-$(CPU2_ELF_PATH)-g'

T32_SED_COMMAND := $(addprefix -e , $(T32_SED_COMMAND)) -e 's-\#ORTICDMASTER\#-$(MASTER_ORTI_CD)-g'\
 -e 's-\#ORTICDCPU1\#-$(CPU1_ORTI_CD)-g' -e 's-\#ORTICDCPU2\#-$(CPU2_ORTI_CD)-g'\
 -e 's-\#ORTICMDMASTER\#-$(MASTER_ORTI_CMD)-g' -e 's-\#ORTICMDCPU1\#-$(CPU1_ORTI_CMD)-g' -e 's-\#ORTICMDCPU2\#-$(CPU2_ORTI_CMD)-g'\
 -e 's-\#ORTICDBACKMASTER\#-$(MASTER_ORTI_CD_BACK)-g' -e 's-\#ORTICDBACKCPU1\#-$(CPU1_ORTI_CD_BACK)-g'\
 -e 's-\#ORTICDBACKCPU2\#-$(CPU2_ORTI_CD_BACK)-g'

ifeq ($(call iseeopt, EE_EXECUTE_FROM_RAM), yes)
T32SCRIPT  := t32_tc27x_mc_ram.cmm
EE_SCRIPTS := config_tc27x_mc.t32 tc27x_mc_start.bat tc27x_mc_start.sh 
else
T32SCRIPT  := t32_tc27x_mc.cmm
EE_SCRIPTS := config_tc27x_mc.t32 tc27x_mc_start.bat tc27x_mc_start.sh tc27x_mc_flash.bat tc27x_mc_flash.sh t32_tc27x_mc_flash.cmm
endif

.PHONY: all clean
.DEFAULT_GOAL := all

all: $(foreach c, $(CPU_LIST), $(c)-all) $(EE_SCRIPTS) $(T32SCRIPT)

clean: $(foreach c, $(CPU_LIST), $(c)-clean)

# Create a pattern rule for each CPU; one pattern for `all', and one for `clean'
define all-clean-template
 .PHONY: $(1)-all $(1)-clean
 $(1)-all $(1)-clean: $(1)-%:
	$(MAKE) -C $($(1)_DIR) TARGET_NAME=$(basename $($(1)_ELF)) CPU_NUMID=$($(1)_ID) GLOBAL_LINKSCRIPT=../$(GLOBAL_LINKSCRIPT) $$*
endef

$(foreach c, $(CPU_LIST), $(eval $(call all-clean-template,$c)))

#Targets Dependencies
$(foreach s, $(SLAVE_CPUS), $(s)-all): $(GLOBAL_LINKSCRIPT)

config_tc27x_mc.t32: %: $(PKGBASE)/mcu/infineon_$(TRICORE_MODEL)/cfg/multicore/%
	@echo CP $@
	$(QUIET) cp $< $@

tc27x_mc_start.bat tc27x_mc_start.sh: %: $(PKGBASE)/mcu/infineon_$(TRICORE_MODEL)/cfg/multicore/%
	@echo GEN $@
	$(QUIET) sed -e 's-#T32SYS#-$(T32SYS)-g'	\
		-e 's-#T32TMP#-$(T32TMP)-g'				\
		-e 's-#T32SCRIPT#-$(T32SCRIPT)-g'		\
		-e 's-#T32ARCH#-$(T32ARCH)-g'			\
		$< > $@
	$(QUIET) chmod 777 $@

tc27x_mc_flash.bat:
	@echo GEN $@
	@echo "@ECHO OFF" > $@
	@echo "REM script to flash TriCore". >> $@
	@echo $(T32SYS)/bin/$(T32ARCH)/t32mtc -s t32_tc27x_mc_flash.cmm >> $@
	$(QUIET) chmod 777 $@

#	@echo GEN $@
#	@echo "@ECHO OFF" > $@
#	@echo "REM script to flash TriCore". >> $@
#ifdef CPU1_DIR
#	@echo cd $(CPU1_DIR) >> $@
#	@echo $(T32SYS)/bin/windows/t32mtc >> $@
#	@echo cd .. >> $@
#endif
#ifdef CPU2_DIR
#	@echo cd $(CPU2_DIR) >> $@
#	@echo $(T32SYS)/bin/windows/t32mtc >> $@
#	@echo cd .. >> $@
#endif
#	@echo cd $(CPU_MASTER_DIR) >> $@
#	@echo $(T32SYS)/bin/windows/t32mtc >> $@
#	@echo cd .. >> $@

tc27x_mc_flash.sh:
	@echo GEN $@
	@echo "#! /bin/bash\n" > $@
	@echo $(T32SYS)/bin/$(T32ARCH)/t32mtc -s t32_tc27x_mc_flash.cmm >> $@
	$(QUIET) chmod 777 $@

$(T32SCRIPT) t32_tc27x_mc_flash.cmm: %: $(PKGBASE)/mcu/infineon_$(TRICORE_MODEL)/cfg/multicore/%
	@echo GEN $@
	$(QUIET) sed $(T32_SED_COMMAND) $< > $@

$(MASTER_ELF_PATH): CPU_MASTER-all

# FIXME: Add some compiler awareness in master makefile

# Generator command for AWK
ifeq ($(call iseeopt, EE_TASKING__), yes)
AWK_GEN_CMD = printf("\"%s\" := 0x%s;\n", m[2], m[1])
else
AWK_GEN_CMD = printf("%s = 0x%s;\n", m[2], m[1])
endif

# I will use objdump always because: the target is an ELF file and,even though TASKING copiler has is own,
# obj utility but I don't know how to get the right output
$(GLOBAL_LINKSCRIPT): $(MASTER_ELF_PATH)
	@echo Building shared symbol table
	$(QUIET) objdump -t -w -j ee_mcglobalc -j ee_mcglobald		\
                -j ee_mcglobalu -j ee_fast_mcglobalc			\
                -j ee_fast_mcglobald -j ee_fast_mcglobalu		\
                -j ee_mcglobalt -j ee_kernel_start $<	|		\
		awk '/^[0-9a-fA-F]+ ......[O,F]/ {						\
			match($$0, "^([0-9a-fA-F]+) .+ ([^ ]+)$$", m);		\
			$(AWK_GEN_CMD)	}' > $@
