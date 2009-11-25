# # Date             : 11/24/2009
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


############################################################################
#
# Automatic options
#
############################################################################
EEOPT += __RTD_CYGWIN__
EEOPT += __COSMIC__
EEOPT += __HCS12XS__
EEOPT += __MC9S12XS128__
EEOPT += __FP__
EEOPT += __MONO__
EEOPT += __ALARMS__


############################################################################
#
# Cosmic S12
#
############################################################################
#EVIDENCEBASE := $(shell cygpath `cygpath -ms "C:\Evidence\Evidence\eclipse\plugins\com.eu.evidence.ee_1.0.0.200910121138"`)
EEBASE  := $(shell cygpath `cygpath -ms "C:\cygwin\home\Dario\repos\ee\trunk\ee"`)

APPBASE := ..
OUTBASE := Debug

COSMIC_ASMDIR := $(shell cygpath `cygpath -ms "C:\Programmi\COSMIC\EVAL12X"`)
COSMIC_CCDIR := $(shell cygpath `cygpath -ms "C:\Programmi\COSMIC\EVAL12X"`)


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
APP_SRCS += $(OUTBASE)/eecfg.c $(COSMIC_INCLUDE_C) $(COSMIC_INCLUDE_S) main.c


############################################################################
#
# end
#
############################################################################
include $(EEBASE)/pkg/cfg/rules.mk
