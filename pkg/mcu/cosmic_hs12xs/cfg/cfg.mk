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
## CVS: $Id: cfg.mk,v 1.2 2006/12/06 13:38:18 nino Exp $

ifeq ($(findstring __HCS12XS__,$(EEOPT)) , __HCS12XS__)

#ifeq ($(findstring __FRSH__,$(EEOPT)) , __FRSH__)
#EE_SRCS += pkg/mcu/cosmic_hs12xs/src/ee_s12xsfrsh.c
#endif

ifeq ($(findstring __OO_BCC1__,$(EEOPT)) , __OO_BCC1__)
MCU_OO=YES
endif
ifeq ($(findstring __OO_BCC2__,$(EEOPT)) , __OO_BCC2__)
MCU_OO=YES
endif
ifeq ($(findstring __OO_ECC1__,$(EEOPT)) , __OO_ECC1__)
MCU_OO=YES
endif
ifeq ($(findstring __OO_ECC2__,$(EEOPT)) , __OO_ECC2__)
MCU_OO=YES
endif

ifeq ($(MCU_OO), YES)
EE_SRCS += pkg/mcu/cosmic_hs12xs/src/ee_start.c
endif

ifeq ($(findstring __USE_SCI__,$(EEOPT)) , __USE_SCI__)
EE_SRCS += pkg/mcu/cosmic_hs12xs/src/ee_sci.c
endif

ifeq ($(findstring __USE_PIT__,$(EEOPT)) , __USE_PIT__)
EE_SRCS += pkg/mcu/cosmic_hs12xs/src/ee_pit.c
endif

# typically empty, the crts.S function is typically provided by the
# ASM30 Assembler
# EE_BOOT_SRCS +=

endif
