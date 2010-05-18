# # Date             : 5/18/2010
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
EEOPT += __USE_LEDS__
EEOPT += __USE_BUTTONS__
EEOPT += MYSCHEDULE


############################################################################
#
# Automatic options
#
############################################################################
EEOPT += __RTD_LINUX__
EEOPT += __MPC5674F__
EEOPT += __PPCE200Z7__
EEOPT += __DIAB__
EEOPT += __OO_BCC2__
EEOPT += __OO_EXTENDED_STATUS__
EEOPT += __MONO__
EEOPT += __OO_NO_ALARMS__
EEOPT += __OO_NO_RESOURCES__
EEOPT += __OO_AUTOSTART_TASK__


############################################################################
#
# Freescale MPC5674F, PPC E200Z7
#
############################################################################
ifndef EEBASE
    EEBASE  := /home/fabio/.eclipse/org.eclipse.platform_3.4.0_1473617060/plugins/com.eu.evidence.ee_1.5.1.201005171756/ee_base
endif
APPBASE := 
OUTBASE := Debug



############################################################################
#
# Flags
#
############################################################################
CFLAGS  += 
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
