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

## Author: 2004 Paolo Gai
## CVS: $Id: cfg.mk,v 1.4 2006/12/03 22:07:50 pj Exp $

ifeq ($(findstring __OO_BCC1__,$(EEOPT)) , __OO_BCC1__)
OO=YES
endif
ifeq ($(findstring __OO_BCC2__,$(EEOPT)) , __OO_BCC2__)
OO=YES
OO2=YES
endif
ifeq ($(findstring __OO_ECC1__,$(EEOPT)) , __OO_ECC1__)
OO=YES
OO_ECC=YES
endif
ifeq ($(findstring __OO_ECC2__,$(EEOPT)) , __OO_ECC2__)
OO=YES
OO_ECC=YES
OO2=YES
endif

ifeq ($(OO), YES)
EE_SRCS += pkg/kernel/oo/src/ee_activate.c
EE_SRCS += pkg/kernel/oo/src/ee_schedule.c
EE_SRCS += pkg/kernel/oo/src/ee_force_schedule.c
EE_SRCS += pkg/kernel/oo/src/ee_terminat.c
EE_SRCS += pkg/kernel/oo/src/ee_thendin.c
EE_SRCS += pkg/kernel/oo/src/ee_irqendin.c
EE_SRCS += pkg/kernel/oo/src/ee_tstub.c
EE_SRCS += pkg/kernel/oo/src/ee_lookup.c
EE_SRCS += pkg/kernel/oo/src/ee_rq_exchg.c
EE_SRCS += pkg/kernel/oo/src/ee_rq_inser.c
EE_SRCS += pkg/kernel/oo/src/ee_shtdown.c
EE_SRCS += pkg/kernel/oo/src/ee_startos.c

ifeq ($(OO2), YES)
EE_SRCS += pkg/kernel/oo/src/ee_rq_first.c
endif

ifneq ($(findstring __OO_NO_CHAINTASK__,$(EEOPT)) , __OO_NO_CHAINTASK__)
EE_SRCS += pkg/kernel/oo/src/ee_chaintas.c
endif

ifneq ($(findstring __OO_NO_RESOURCES__,$(EEOPT)) , __OO_NO_RESOURCES__)
EE_SRCS += pkg/kernel/oo/src/ee_lockres.c
EE_SRCS += pkg/kernel/oo/src/ee_ulockres.c
endif


ifneq ($(findstring __OO_NO_ALARMS__,$(EEOPT)) , __OO_NO_ALARMS__)
EE_SRCS += pkg/kernel/oo/src/ee_alcancel.c
EE_SRCS += pkg/kernel/oo/src/ee_algetbase.c
EE_SRCS += pkg/kernel/oo/src/ee_alget.c
EE_SRCS += pkg/kernel/oo/src/ee_alsetabs.c
EE_SRCS += pkg/kernel/oo/src/ee_alsetrel.c
EE_SRCS += pkg/kernel/oo/src/ee_altick.c
endif

ifeq ($(OO_ECC) , YES)
EE_SRCS += pkg/kernel/oo/src/ee_evclear.c
EE_SRCS += pkg/kernel/oo/src/ee_evget.c
EE_SRCS += pkg/kernel/oo/src/ee_evset.c
EE_SRCS += pkg/kernel/oo/src/ee_evwait.c 
endif

ifeq ($(findstring __BIN_DISTR,$(EEOPT)) , __BIN_DISTR)
EE_SRCS += pkg/kernel/oo/src/ee_disableallinterrupts.c
EE_SRCS += pkg/kernel/oo/src/ee_enableallinterrupts.c
EE_SRCS += pkg/kernel/oo/src/ee_suspendallinterrupts.c
EE_SRCS += pkg/kernel/oo/src/ee_resumeallinterrupts.c
EE_SRCS += pkg/kernel/oo/src/ee_suspendosinterrupts.c
EE_SRCS += pkg/kernel/oo/src/ee_resumeosinterrupts.c
EE_SRCS += pkg/kernel/oo/src/ee_getactiveapplicationmode.c
EE_SRCS += pkg/kernel/oo/src/ee_gettaskid.c
EE_SRCS += pkg/kernel/oo/src/ee_gettaskstate.c
endif

ifeq ($(findstring __OO_SEM__,$(EEOPT)) , __OO_SEM__)
EE_SRCS += pkg/kernel/oo/src/ee_sempost.c
EE_SRCS += pkg/kernel/oo/src/ee_semtrywait.c
EE_SRCS += pkg/kernel/oo/src/ee_semgetvalue.c

ifeq ($(OO_ECC) , YES)
EE_SRCS += pkg/kernel/oo/src/ee_semwait.c
endif
endif

endif
