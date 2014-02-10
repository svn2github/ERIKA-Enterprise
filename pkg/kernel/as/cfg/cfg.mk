# ###*B*###
# ERIKA Enterprise - a tiny RTOS for small microcontrollers
# 
# Copyright (C) 2002-2011  Evidence Srl
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


ifeq ($(call iseeopt, __AS_SC4__), yes)
EE_SRCS += pkg/kernel/as/src/ee_mem_prot.c
EE_SRCS += pkg/kernel/as/src/ee_as_base.c
EE_SRCS += pkg/kernel/as/src/ee_osapp.c
else # __AS_SC4__

ifeq ($(call iseeopt, __OO_BCC1__), yes)
KERNEL_OO=yes
endif
ifeq ($(call iseeopt, __OO_BCC2__), yes)
KERNEL_OO=yes
endif
ifeq ($(call iseeopt, __OO_ECC1__), yes)
KERNEL_OO=yes
endif
ifeq ($(call iseeopt, __OO_ECC2__), yes)
KERNEL_OO=yes
endif

ifeq ($(and $(call iseeopt, EE_SERVICE_PROTECTION__), $(KERNEL_OO)), yes)
EE_SRCS += pkg/kernel/as/src/ee_as_base.c
endif # EE_AS_SERVICE_PROTECTION__ && KERNEL_OO

# FIXME: WORKAROUND until other architectures will support full AS porting
ifeq ($(and $(call iseeopt, __MSRP__), $(KERNEL_OO), $(call iseeopt, EE_TRICORE__)), yes)
EE_SRCS += pkg/kernel/as/src/ee_as_multicore.c

ifeq ($(call iseeopt, EE_AS_USER_SPINLOCKS__), yes)
EE_SRCS += pkg/kernel/as/src/ee_as_spinlocks.c
endif # EE_AS_USER_SPINLOCKS__

ifeq ($(call iseeopt, EE_AS_RPC__), yes)
EE_SRCS += pkg/kernel/as/src/ee_as_rpc.c
endif # EE_AS_RPC__

ifeq ($(call iseeopt, EE_AS_IOC__), yes)
EE_SRCS += pkg/kernel/as/src/ee_as_ioc.c
endif # EE_AS_IOC__

endif # __MSRP__ && KERNEL_OO
endif # __AS_SC4__

