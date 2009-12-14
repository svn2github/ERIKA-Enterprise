# # Date             : 11/30/2009
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
EEOPT += MYSCHEDULE


############################################################################
#
# Automatic options
#
############################################################################
EEOPT += __RTD_CYGWIN__
EEOPT += __COSMIC__
EEOPT += __HCS12XS__
EEOPT += __MC9S12XS128__

#EEOPT += __USE_SCI__
#EEOPT += __USE_PIT__
EEOPT += __DEMO9S12XSFAME__
EEOPT += __USE_LEDS__
#EEOPT += __USE_BUTTONS__
#EEOPT += __USE_POTENTIOMETER__
#EEOPT += __USE_ADC__
#EEOPT += __USE_LIGHT_SENSOR__

EEOPT += __OO_ECC1__
EEOPT += __ALLOW_NESTED_IRQ__
EEOPT += __IRQ_STACK_NEEDED__
EEOPT += __MULTI__
EEOPT += __OO_NO_ALARMS__

EEOPT += __OO_EXTENDED_STATUS__
EEOPT += __OO_NO_RESOURCES__
EEOPT += __OO_AUTOSTART_TASK__
EEOPT += __OO_HAS_USERESSCHEDULER__


############################################################################
#
# Freescale S12
#
############################################################################
#EVIDENCEBASE := $(shell cygpath `cygpath -ms "C:\Evidence\Evidence\eclipse\plugins\com.eu.evidence.ee_1.0.0.200911272111"`)
#EEBASE  := $(shell cygpath `cygpath -ms "C:\Evidence\Evidence\eclipse\plugins\com.eu.evidence.ee_1.0.0.200911272111\ee_base"`)
EEBASE  := $(shell cygpath `cygpath -ms "C:\cygwin\home\Dario\repos\ee\trunk\ee"`)
APPBASE := 
OUTBASE := Debug

COSMIC_ASMDIR := $(shell cygpath `cygpath -ms "c:\Programmi\COSMIC\EVAL12X"`)
COSMIC_CCDIR := $(shell cygpath `cygpath -ms "c:\Programmi\COSMIC\EVAL12X"`)


############################################################################
#
# Init MCU for S12 (CUSTOM)
#
############################################################################
COSMIC_MODEL           := MC9S12XS128
COSMIC_LINKERSCRIPT    := mc9s12xs128.lkf
COSMIC_INCLUDE_H       := hs12xsregs.h
COSMIC_INCLUDE_C       := vector_s12x.c
COSMIC_INCLUDE_S       := crtsx.S


############################################################################
#
# Flags
#
############################################################################
CFLAGS  += -l +modf +fast +nowiden +warn +sprec
ASFLAGS += -v -l -c  
LDFLAGS +=  -p -sa -m mapfile.map
LDDEPS  += 
LIBS    += 



############################################################################
#
# Sources
#
############################################################################
APP_SRCS += eecfg.c $(COSMIC_INCLUDE_C) $(COSMIC_INCLUDE_S) main.c


############################################################################
#
# end
#
############################################################################
include $(EEBASE)/pkg/cfg/rules.mk
