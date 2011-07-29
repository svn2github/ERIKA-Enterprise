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
EEOPT += __ASSERT__


############################################################################
#
# Automatic options
#
############################################################################
EEOPT += __RTD_CYGWIN__
EEOPT += __CODEWARRIOR__
EEOPT += __COSMIC__
EEOPT += __HCS12XS__
EEOPT += __MC9S12XS128__
EEOPT += __FP__
EEOPT += __MONO__
EEOPT += __FP_NO_RESOURCES__


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
CFLAGS  += -D__FAR_DATA
ASFLAGS += 
LDFLAGS += -addansixbi.lib
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
