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

# Author: 2004, Paolo Gai

# CONF multiplexer
include ../$(EXPERIMENT)/conf.in


# PURPOSE OF THIS MAKEFILE
# This makefile is called by the ARCH multiplexer, once for each
# architecture that have to be tested for a particular EXPERIMENT
# directory
#
# This makefile uses the macros defined in the $(thearch)/arch.mk
# makefile on a custom directory to handle compilation and testing of
# the particular EXPERIMENT for the particular $(theconf)iguration.

# variables defined from now on:
# all the variables described in arch_multiplexer.mk plus:
# from arch_multiplexer.mk
# - thearch    the architecture I am testing (e.g., ee_manual)

#
# Note for writing an arch.mk file:
#
# ARCH_OUTDIR_COMMANDS is the only ARCH_* macro that is NOT called
# inside a template!!!!
#
# PARAMETERS is used inside a template BUT IT DOES NOT NEED A $$, only a $

MUX = $(EEBASE)/testcase/common/confparser/confparser_mux
DEMUX = $(EEBASE)/testcase/common/confparser/confparser_demux
DEMUX2 = $(EEBASE)/testcase/common/confparser/confparser_demux2

# Note: the existence of MUX is checked in arch_multiplexer
confs := $(shell test -e $(MUX) && $(MUX) $(conf))

PARAMETERS = $$(shell $$(DEMUX) $(1))

# note: do not use "." in the OUTDIR name...
OUTDIR_PREFIX = $(EEBASE)/testcase/$(EXPERIMENT)out_$(thearch)_
OUTDIRS = $(addprefix $(OUTDIR_PREFIX), $(confs))



include $(wildcard */test.mk)



.PHONY: all conf


#
# all
#

all_confs := $(addprefix all_, $(confs))
all: $(all_confs)
	@echo dummy > /dev/null

define all_template
.PHONY: all_$(1)
all_$(1): $$(OUTDIRS)
	@echo EXPERIMENT $$(EXPERIMENT) $(PARAMETERS)
	@echo CLEAN      $$(EXPERIMENT) $(PARAMETERS)
	@$($(CLEAN_$(thearch)))
	@echo COMPILE    $$(EXPERIMENT) $(PARAMETERS)
	@$($(COMPILE_$(thearch)))
	@echo DEBUGGER   $$(EXPERIMENT) $(PARAMETERS)
	@$($(DEBUG_$(thearch)))
endef

$(foreach c,$(confs),$(eval $(call all_template,$(c))))


#
# rtdruid
#

rtdruid_confs := $(addprefix rtdruid_, $(confs))
rtdruid: $(rtdruid_confs)
	@echo dummy > /dev/null

define rtdruid_template
.PHONY: rtdruid_$(1)
rtdruid_$(1): $$(OUTDIRS)
	@echo dummy > /dev/null
	@$($(RTDRUID_$(thearch)))
endef

$(foreach c,$(confs),$(eval $(call rtdruid_template,$(c))))



#
# dist
#

dist_confs := $(addprefix dist_, $(confs))
dist: $(dist_confs)
	@echo dummy > /dev/null

define dist_template
.PHONY: dist_$(1)
dist_$(1): $$(OUTDIRS)
	@echo dummy > /dev/null
	@$($(DIST_$(thearch)))
endef

$(foreach c,$(confs),$(eval $(call dist_template,$(c))))


#
# conf
#

conf_confs := $(addprefix conf_, $(confs))
conf: $(conf_confs)
	@echo dummy > /dev/null

define conf_template
.PHONY: conf_$(1)
conf_$(1): $$(OUTDIRS)
	@echo dummy > /dev/null
	@$($(CONF_$(thearch)))
endef

$(foreach c,$(confs),$(eval $(call conf_template,$(c))))





$(OUTDIRS):
	@echo OUT $(notdir $@)
	@mkdir $@
	@$($(OUTDIR_COMMANDS_$(thearch)))
