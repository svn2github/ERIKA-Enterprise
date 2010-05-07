# # Date             : 4/21/2010
# RT-Druid version : 
#

# these lines override the .bashrc definitions
#EEBASE = ../../..
#APPBASE = .

###
### Setting EEOPT variable:
###

EEOPT =


############################################################################
#
# User options
#
############################################################################
EEOPT += DEBUG
EEOPT += NODEPS
EEOPT += __ASSERT__


############################################################################
#
# Automatic options
#
############################################################################
EEOPT += __RTD_LINUX__
EEOPT += __MPC5674F__
EEOPT += __PPCE200Z7__
EEOPT += __DIAB__
EEOPT += __OO_ECC2__
EEOPT += __OO_EXTENDED_STATUS__
EEOPT += __OO_HAS_STARTUPHOOK__
EEOPT += __OO_HAS_ERRORHOOK__
EEOPT += __IRQ_STACK_NEEDED__
EEOPT += __MULTI__
EEOPT += __OO_HAS_USERESSCHEDULER__
EEOPT += __OO_AUTOSTART_TASK__
EEOPT += __OO_AUTOSTART_ALARM__
EEOPT += __ALLOW_NESTED_IRQ__


############################################################################
#
# Freescale MPC5674F, PPC E200Z7
#
############################################################################
ifndef EEBASE
    EEBASE  := /home/fabio/.eclipse/org.eclipse.platform_3.4.0_1473617060/plugins/com.eu.evidence.ee_1.5.1.201004080754/ee_base
endif
APPBASE := 
OUTBASE := Debug



############################################################################
#
# Flags
#
############################################################################
CFLAGS  += -g2
ASFLAGS += 
LDFLAGS += 
LDDEPS  += 
LIBS    += 



############################################################################
#
# Sources
#
############################################################################
APP_SRCS += eecfg.c main.c


############################################################################
#
# end
#
############################################################################
include $(EEBASE)/pkg/cfg/rules.mk
