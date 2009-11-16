# # Date             : 10/28/2009
# RT-Druid version : 
#

###
### Setting EEOPT variable:
###

VERBOSE = 1

EEOPT =


############################################################################
#
# User options
#
############################################################################
EEOPT += DEBUG


############################################################################
#
# Automatic options
#
############################################################################
EEOPT += __RTD_CYGWIN__
EEOPT += __COSMIC__
EEOPT += __HCS12XS__
EEOPT += __USE_LEDS__
EEOPT += __FP__
EEOPT += __MONO__
EEOPT += __ALARMS__


############################################################################
#
# s12xs
#
############################################################################
EVIDENCEBASE := $(shell cygpath `cygpath -ms "C:\cygwin\home\Dario\repos\ee\trunk\ee\com.eu.evidence.ee_1.0.0.200910121138"`)
EEBASE  := $(shell cygpath `cygpath -ms "C:\cygwin\home\Dario\repos\ee\trunk\ee\com.eu.evidence.ee_1.0.0.200910121138\ee_base"`)

APPBASE := ..
OUTBASE := Debug
COSMICFOLDER := fromcosmic
COSMIC_BASE = $(shell cygpath `cygpath -ms "C:\Programmi\COSMIC\EVAL12X"`)
COSMIC_ASMDIR = $(COSMIC_BASE)
COSMIC_CCDIR = $(COSMIC_BASE)
COSMIC_INC = HS12x


############################################################################
#
# Init MCU for S12XS (MC9S12XS128)
#
############################################################################
FREESCALE_MODEL           := MC9S12XS128

ifeq ($(S12XS_MODEL), MC9S12XS128)
S12XS_ASMDIR := $(shell cygpath `cygpath -ms "C:\Programmi\COSMIC\EVAL12X"`)
S12XS_CCDIR := $(shell cygpath `cygpath -ms "C:\Programmi\COSMIC\EVAL12X"`)
S12XS_LNKDIR := $(shell cygpath `cygpath -ms "C:\Programmi\COSMIC\EVAL12X"`)
S12XS_ELFDIR := $(shell cygpath `cygpath -ms "C:\Programmi\COSMIC\EVAL12X"`)
S12XS_LINKERSCRIPT := demo12x.lkf
S12XS_LIB :=
S12XS_INCLUDE_H := ioxs256.h
S12XS_INCLUDE_S := crtsx.S
S12XS_INCLUDE_C := vector_s12x.c
OUTFILE = demo
EXT = hs12xs
endif

############################################################################
#
# Flags
#
############################################################################
CFLAGS  += -l -v +modf +fast +nowiden +debug +warn +sprec #-v -wa921638 -wb1224
ASFLAGS += -c -v -l -xx -x
LDFLAGS += -p -sa -m mapfile.map #-bs0
LDDEPS  +=
LIBS    +=


############################################################################
#
# Sources
#
############################################################################
APP_SRCS += eecfg.c $(APPBASE)/code.c
#APP_SRCS += $(APPBASE)/code.c


############################################################################
#
# end
#
############################################################################
include $(EEBASE)/pkg/cfg/rules.mk
