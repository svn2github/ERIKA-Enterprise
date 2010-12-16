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

## Author: 2005 Paolo Gai
## CVS: $Id: compiler.mk,v 1.18 2006/12/06 17:39:08 pj Exp $

##
## Compiler related options
##

ifeq ($(findstring __AVR5__,$(EEALLOPT)), __AVR5__)
include $(PKGBASE)/cfg/arch/cc_avr5gnu.mk
endif


ifeq ($(findstring __ARM7GNU__,$(EEALLOPT)), __ARM7GNU__)
include $(PKGBASE)/cfg/arch/cc_arm7gnu.mk
endif

ifeq ($(findstring __ARM7ADS__,$(EEALLOPT)), __ARM7ADS__)
include $(PKGBASE)/cfg/arch/cc_arm7ads.mk
endif

ifeq ($(findstring __MPC5XX__,$(EEALLOPT)), __MPC5XX__)
include $(PKGBASE)/cfg/arch/cc_ppcgnu.mk
endif

ifeq ($(findstring __MPC5PROTECTED__,$(EEALLOPT)), __MPC5PROTECTED__)
include $(PKGBASE)/cfg/arch/cc_ppcgnu.mk
endif

ifeq ($(findstring __PPCE200Z7__,$(EEALLOPT)), __PPCE200Z7__)
ifeq ($(findstring __DIAB__,$(EEALLOPT)), __DIAB__)
include $(PKGBASE)/cfg/arch/cc_z7diab.mk
endif
endif

ifeq ($(findstring __PIC30__,$(EEALLOPT)), __PIC30__)
include $(PKGBASE)/cfg/arch/cc_pic30.mk
endif

ifeq ($(findstring __PIC32__,$(EEALLOPT)), __PIC32__)
include $(PKGBASE)/cfg/arch/cc_pic32.mk
endif

ifeq ($(findstring __TRICORE1_TASKING__,$(EEALLOPT)), __TRICORE1_TASKING__)
include $(PKGBASE)/cfg/arch/cc_tricore_tasking.mk
endif

ifeq ($(findstring __TRICORE_GNU__,$(EEALLOPT)), __TRICORE_GNU__)
include $(PKGBASE)/cfg/arch/cc_tricore_gnu.mk
endif

ifeq ($(findstring __HCS12XS__,$(EEALLOPT)) , __HCS12XS__)
ifeq ($(findstring __COSMIC__,$(EEALLOPT)), __COSMIC__)
include $(PKGBASE)/cfg/arch/cc_s12x_cosmic.mk
endif
endif

ifeq ($(findstring __LM32__,$(EEALLOPT)) , __LM32__)
include $(EEBASE)/pkg/cfg/arch/cc_mico32.mk
endif

ifeq ($(findstring __ESI_RISC__,$(EEALLOPT)) , __ESI_RISC__)
include $(EEBASE)/pkg/cfg/arch/cc_esi_risc.mk
endif

ifeq ($(findstring __MSP430__,$(EEALLOPT)) , __MSP430__)
include $(EEBASE)/pkg/cfg/arch/cc_msp430.mk
endif
