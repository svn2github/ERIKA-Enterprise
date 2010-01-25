# # Date             : 1/18/2010
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
EEOPT += __SEM__
EEOPT += __ASSERT__
EEOPT += __S12XS_INCLUDE_REGS__


############################################################################
#
# Automatic options
#
############################################################################
EEOPT += __RTD_CYGWIN__
EEOPT += __COSMIC__
EEOPT += __HCS12XS__
EEOPT += __USE_PIT__
EEOPT += __MC9S12XS128__
EEOPT += __DEMO9S12XSFAME__
EEOPT += __USE_POTENTIOMETER__
EEOPT += __USE_ADC__
EEOPT += __USE_BUTTONS__
EEOPT += __USE_LEDS__
EEOPT += __USE_LIGHT_SENSOR__
EEOPT += __FP__
EEOPT += __IRQ_STACK_NEEDED__
EEOPT += __ALLOW_NESTED_IRQ__
EEOPT += __MULTI__
EEOPT += __FP_NO_RESOURCES__


############################################################################
#
# Freescale S12
#
############################################################################
EVIDENCEBASE := $(shell cygpath `cygpath -ms "C:\Evidence\Evidence\eclipse\plugins\com.eu.evidence.ee_1.0.0.200912021119"`)
EEBASE  := $(shell cygpath `cygpath -ms "C:\Evidence\Evidence\eclipse\plugins\com.eu.evidence.ee_1.0.0.200912021119\ee_base"`)
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
ASFLAGS += -c -v -l 
LDFLAGS += -p -sa -m mapfile.map
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
