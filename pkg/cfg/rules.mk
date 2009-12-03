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

## Authors: 2001-2002 Paolo Gai, Enrico Bini, Alessandro Colantonio
## 2002- Paolo Gai
## 2005 Antonio Romano
## CVS: $Id: rules.mk,v 1.33 2008/01/14 10:35:34 pj Exp $

ifeq ($(findstring app.mk,$(notdir $(wildcard $(APPBASE)/*.mk))), app.mk)
include $(APPBASE)/app.mk
endif


# Enable libs support
ifeq ($(findstring __BUILD_ALL_LIBS__,$(EEOPT)) , __BUILD_ALL_LIBS__)
ENABLE_LIBS:=TRUE
ONLY_LIBS:=TRUE
endif
ifeq ($(findstring __BUILD_LIBS__,$(EEOPT)) , __BUILD_LIBS__)
ENABLE_LIBS:=TRUE
ONLY_LIBS:=TRUE
endif
ifeq ($(findstring __ADD_LIBS__,$(EEOPT)) , __ADD_LIBS__)
ENABLE_LIBS:=TRUE
endif

# Microchip dsPIC specific
ifeq ($(GENERATE_MPLABIDE_LIBS), TRUE)
ENABLE_LIBS:=TRUE
endif


# EEOPT is used to appropriately configure and compile the particular
# application. Symbols specified in EEOPT are implicithy defined when
# compiling the application using the -D compiler option

# EEALLOPT is used inside the makefile to contain the EEOPT symbols
# plus eventually the EEOPT symbols that were used to compile the
# binary distribution.

# EEOPT and EEALLOPT are DIFFERENT because only the symbols of EEOPT
# are passed using -D to the compiler. EEALLOPT contains in general
# also other symbols that are then defined in pkg/ee_libcfg.h of the
# binary distributions.

# The simbol __ERIKA__ in EE_OPT is used to check the OS in the
# contrib libraries.

EEOPT += __ERIKA__


ifeq ($(strip $(EELIB)),)
# this is not a binary distribution
EEALLOPT:=$(EEOPT)
else
# this is a binary distribution
include $(EEBASE)/pkg/cfg/options.mk
EEALLOPT:=$(EEOPT) $($(EELIB))
endif


##
## default automatic inserted dependencies
##########################################################################

ifeq ($(findstring __EDF__,$(EEOPT)) , __EDF__)
ifeq ($(findstring __TIME_SUPPORT__,$(EEOPT)) , __TIME_SUPPORT__)
else
EEOPT += __TIME_SUPPORT__
endif
endif

#ifeq ($(findstring __MULTI__,$(EEOPT)) , __MULTI__)
#ifeq ($(findstring __IRQ_STACK_NEEDED__,$(EEOPT)) , __IRQ_STACK_NEEDED__)
#else
#EEOPT += __IRQ_STACK_NEEDED__
#endif
#endif

ifeq ($(findstring __IRQ_STACK_NEEDED__,$(EEOPT)) , __IRQ_STACK_NEEDED__)
ifeq ($(findstring __MULTI__,$(EEOPT)) , __MULTI__)
else
EEOPT += __MULTI__
endif
endif

ifeq ($(findstring __COM_CCC0__,$(EEOPT)) , __COM_CCC0__)
EEOPT += __ALARMS__
endif

ifeq ($(findstring __COM_CCC1__,$(EEOPT)) , __COM_CCC1__)
EEOPT += __ALARMS__
endif

ifeq ($(findstring __EVALUATOR7T__,$(EEOPT)) , __EVALUATOR7T__)
EEOPT += __SAMSUNG_KS32C50100__
endif

ifeq ($(findstring __MPC5PROTECTED__,$(EEOPT)) , __MPC5PROTECTED__)
EEOPT += __PROTECTED__
endif

# Bugfix: to be removed!
ifeq ($(findstring __unibo_mparm__,$(EEOPT)) , __unibo_mparm__)
EEOPT += __UNIBO_MPARM__
EEALLOPT += __UNIBO_MPARM__
endif

# Bugfix: to be removed!
ifeq ($(findstring __USE_DEMOBOARD__,$(EEOPT)) , __USE_DEMOBOARD__)
else
ifeq ($(findstring __USE_MOTIONBOARD__,$(EEOPT)) , __USE_MOTIONBOARD__)
else
ifeq ($(findstring __USE_USB__,$(EEOPT)) , __USE_USB__)
EEOPT += __USE_MOTIONBOARD__
EE_SRCS += pkg/board/ee_flex/src/ee_flex_motionboard.c
endif # __USE_USB__
endif # __USE_MOTIONBOARD__
endif # __USE_DEMOBOARD__

##
## H8/300 - gcc under GNU/Linux
##########################################################################
ifeq ($(findstring __H8__,$(EEALLOPT)), __H8__) 
  include $(EEBASE)/pkg/cfg/arch/rules_lego_rcx.mk
endif 

##
## MPC5XX - gcc under GNU/Linux
##########################################################################
ifeq ($(findstring __MPC5XX__,$(EEALLOPT)) , __MPC5XX__)
ifeq ($(findstring __MPC566EVB__,$(EEALLOPT)) , __MPC566EVB__) 
include $(EEBASE)/pkg/cfg/arch/rules_axiom_mpc566evb.mk
endif
endif

ifeq ($(findstring __MPC5PROTECTED__,$(EEALLOPT)) , __MPC5PROTECTED__)
ifeq ($(findstring __MPC566EVB__,$(EEALLOPT)) , __MPC566EVB__)
include $(EEBASE)/pkg/cfg/arch/rules_axiom_mpc566evb.mk
endif
endif


##
## ARM7TDMI - GNU gcc under GNU/Linux or Cygwin
##########################################################################
ifeq ($(findstring __ARM7GNU__,$(EEALLOPT)) , __ARM7GNU__)

ifeq ($(findstring __EVALUATOR7T__,$(EEALLOPT)) , __EVALUATOR7T__)
include $(EEBASE)/pkg/cfg/arch/rules_arm_evaluator7t.mk
endif

ifeq ($(findstring __UNIBO_MPARM__,$(EEALLOPT)) , __UNIBO_MPARM__)
include $(EEBASE)/pkg/cfg/arch/rules_unibo_mparm.mk
endif

ifeq ($(findstring __TRISCENDA7S__,$(EEALLOPT)) , __TRISCENDA7S__)
include $(EEBASE)/pkg/cfg/arch/rules_triscend_a7s.mak
endif

endif


##
## AVR5 
##########################################################################
ifeq ($(findstring __AVR5__,$(EEALLOPT)), __AVR5__)

##
##  ATmega128 - GNU - stk500
##########################################################################
ifeq ($(findstring __ATMEL_STK50X__,$(EEALLOPT)), __ATMEL_STK50X__)
include $(EEBASE)/pkg/cfg/arch/rules_atmel_stk500.mk
endif 

##
##  ATmega128 - GNU - mica boarb mib510
##########################################################################

ifeq ($(findstring __XBOW_MIB5X0__,$(EEALLOPT)), __XBOW_MIB5X0__)
include $(EEBASE)/pkg/cfg/arch/rules_xbow_mib5x0.mk
endif 

endif

##
## ST10 - Tasking 6.0 under Windows
##########################################################################
ifeq ($(findstring __ST10__,$(EEALLOPT)) , __ST10__)
include $(EEBASE)/pkg/cfg/arch/rules_ertec_eva167.mk
endif


##
## Altera NIOS2 - gcc under Windows
##########################################################################
ifeq ($(findstring __NIOS2__,$(EEALLOPT)) , __NIOS2__)
include $(EEBASE)/pkg/cpu/nios2/cfg/rules.mk
endif


##
## Microchip DSPIC - gcc under Windows
##########################################################################
ifeq ($(findstring __PIC30__,$(EEALLOPT)) , __PIC30__)
include $(EEBASE)/pkg/cfg/arch/rules_microchip_pic30.mk
endif

##
## Microchip PIC32 - gcc
##########################################################################
ifeq ($(findstring __PIC32__,$(EEALLOPT)) , __PIC32__)
include $(EEBASE)/pkg/cfg/arch/rules_microchip_pic32.mk
endif

##
## Infineon Tricore - Tasking under Windows
##########################################################################
ifeq ($(findstring __TRICORE1__,$(EEALLOPT)) , __TRICORE1__)
ifeq ($(findstring __TC1775B__,$(EEALLOPT)) , __TC1775B__)
include $(EEBASE)/pkg/cfg/arch/rules_infineon_tc1775b.mk
endif
endif

##
## Freescale S12X - Cosmic compiler under windows
##########################################################################
ifeq ($(findstring __HCS12XS__,$(EEALLOPT)) , __HCS12XS__)
ifeq ($(findstring __COSMIC__,$(EEALLOPT)) , __COSMIC__)
include $(EEBASE)/pkg/cfg/arch/rules_freescale_s12x_cosmic.mk
endif
endif







##
## error checking in EEOPT
##########################################################################
ifeq ($(findstring __MONO__,$(EEOPT)) , __MONO__)
ifeq ($(findstring __MULTI__,$(EEOPT)) , __MULTI__)
$(error __MULTI__ and __MONO__ options are not compatible)
endif
endif

ifeq ($(findstring __IRQ_STACK_NEEDED__,$(EEOPT)) , __IRQ_STACK_NEEDED__)
ifeq ($(findstring __MONO__,$(EEOPT)) , __MONO__)
$(error __MONO__ and __IRQ_STACK_NEEDED__ options are not compatible)
endif
endif

