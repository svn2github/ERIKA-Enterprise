# # Date             : 12/1/2009
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
EEOPT += __ASSERT__
EEOPT += __CODEWARRIOR__

############################################################################
#
# Automatic options
#
############################################################################
EEOPT += __RTD_CYGWIN__
EEOPT += __COSMIC__
EEOPT += __HCS12XS__
EEOPT += __MC9S12XS128__
EEOPT += __OO_BCC1__
EEOPT += __ALLOW_NESTED_IRQ__
EEOPT += __OO_EXTENDED_STATUS__
EEOPT += __MONO__
EEOPT += __OO_NO_ALARMS__
EEOPT += __OO_AUTOSTART_TASK__

EEOPT += __S12XS_INCLUDE_REGS__

EEOPT += __USE_SCI__
EEOPT += __USE_PIT__
EEOPT += __DEMO9S12XSFAME__
EEOPT += __USE_LEDS__
EEOPT += __USE_BUTTONS__
#EEOPT += __USE_POTENTIOMETER__
#EEOPT += __USE_ADC__
#EEOPT += __USE_LIGHT_SENSOR__


############################################################################
#
# Freescale S12
#
############################################################################
APPBASE := 
OUTBASE := Debug_fake

COSMIC_ASMDIR := $(shell cygpath `cygpath -ms "C:\Programmi\Freescale\CWS12v5.1"`)
COSMIC_CCDIR := $(shell cygpath `cygpath -ms "C:\Programmi\Freescale\CWS12v5.1"`)

############################################################################
#
# Init MCU for S12 (CUSTOM)
#
############################################################################
COSMIC_MODEL           := MC9S12XS128
COSMIC_LINKERSCRIPT    := SofTec_HCS12_linker.prm
COSMIC_INCLUDE_C       := Start12.c

############################################################################
#
# Flags
#
############################################################################
CFLAGS  += -D__FAR_DATA -Onf
ASFLAGS += 
LDFLAGS += -addansixb.lib
LDDEPS  += 
LIBS    += 


############################################################################
#
# Sources
#
############################################################################
APP_SRCS += eecfg.c $(COSMIC_INCLUDE_C) $(COSMIC_INCLUDE_S) main.c Vectors.c CPU12ISRs.c


############################################################################
#
# end
#
############################################################################
include $(EEBASE)/pkg/cfg/rules.mk
