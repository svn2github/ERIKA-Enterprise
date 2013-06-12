# ###*B*###
# ERIKA Enterprise - a tiny RTOS for small microcontrollers
# 
# Copyright (C) 2002-2012  Evidence Srl
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

## Author: 2012 Carlo Caione

##Check if is the stack that we're asking for
ifeq ($(call iseeopt, __USE_STM32F4XX_EVAL__), yes)

## Check the EVAL library selection
ifeq ($(findstring __LIB_EVAL__,$(LIB_OPT)) , __LIB_EVAL__)
INCLUDE_STM32F4XX_EVAL = YES
endif

## Check if it's selected all libs inclusion
ifeq ($(call iseeopt, __BUILD_ALL_LIBS__), yes)
INCLUDE_STM32F4XX_EVAL = YES
endif

##
## If the library is required
##
ifeq ($(INCLUDE_STM32F4XX_EVAL), YES)

EEOPT += USE_STM32F4_DISCOVERY

EEOPT += __USE_SPD_GPIO__
EEOPT += __USE_SPD_CRYP_EXTI__
EEOPT += __USE_SPD_MISC__
EEOPT += __USE_SPD_HASH_RCC__
EEOPT += __USE_SPD_HASH_SYSCFG__

INCLUDE_PATH += $(EEBASE)/contrib/st/STM32_EVAL/inc

EE_SRCS_EVAL += contrib/st/STM32_EVAL/src/stm32f4_discovery.c

EE_OBJS_EVAL := $(addprefix $(OBJDIR)/, $(patsubst %.c,%.o,$(patsubst %.s,%.o,$(EE_SRCS_EVAL))))
LIBSRCS += $(EE_SRCS_EVAL)

STM32F4XXEVALLIB := libstm32f4xxeval.a

$(STM32F4XXEVALLIB): $(EE_OBJS_EVAL)
	@echo "AR    $(STM32F4XXEVALLIB)";
	$(QUIET)$(EE_AR) $(COMPUTED_OPT_AR) $@ $^
OPT_LIBS += $(STM32F4XXEVALLIB)
ALL_LIBS += $(STM32F4XXEVALLIB)

endif	# INCLUDE_STM32F4XX_EVAL

endif	#  __USE_STM32F4XX_EVAL__