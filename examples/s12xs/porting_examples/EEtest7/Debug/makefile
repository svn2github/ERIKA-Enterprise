# # Date             : 10/28/2009
# RT-Druid version : 
#

# these lines override the .bashrc definitions
#EEBASE = ../../..
#APPBASE = .

###
### Setting EEOPT variable:
###

EEOPT = #VERBOSE

############################################################################
#
# User options
#
############################################################################
EEOPT += DEBUG
EEOPT += NODEPS
#EEOPT += __ADD_LIBS__

############################################################################
#
# Automatic options
#
############################################################################
EEOPT += __COSMIC__
EEOPT += __HCS12XS__
EEOPT += __ALLOW_NESTED_IRQ__
EEOPT += __OO_BCC1__
#EEOPT += __OO_EXTENDED_STATUS__ # errori standard e errori estesi 
EEOPT += __MONO__
EEOPT += __OO_AUTOSTART_TASK__

############################################################################
#
# COSMIC
#
############################################################################
EVIDENCEBASE := $(shell cygpath `cygpath -ms "C:\Evidence\Evidence\eclipse\plugins\com.eu.evidence.ee_1.0.0.200910121138"`)
EEBASE  := $(shell cygpath `cygpath -ms "C:\cygwin\home\Dario\repos\ee\trunk\ee"`)

APPBASE := ..
OUTBASE := Debug

COSMIC_ASMDIR := $(shell cygpath `cygpath -ms "C:\Programmi\COSMIC\EVAL12X"`)
COSMIC_CCDIR := $(shell cygpath `cygpath -ms "C:\Programmi\COSMIC\EVAL12X"`)


############################################################################
#
# Init MCU for PIC30 (PIC33FJ256MC710)
#
############################################################################
#COSMIC_MODEL           := MC9S12XS128
COSMIC_LINKERSCRIPT    := mc9s12xs128.lkf
#COSMIC_DEV_LIB         := libmc9s12xs128-elf.a
COSMIC_INCLUDE_C       := vector_s12x.c
COSMIC_INCLUDE_S       := crtsx.S
COSMIC_INCLUDE_H		:= hs12xsregs.h


############################################################################
#
# Flags
#
############################################################################
CFLAGS  += -l +modf +fast +nowiden +warn +sprec #-v -wa921638 -wb1224
ASFLAGS += -c -v -l 
LDFLAGS += -p -sa -m mapfile.map 
LDDEPS  +=
LIBS    +=

LIB_OPT  += 

############################################################################
#
# Sources
#
############################################################################
APP_SRCS += $(OUTBASE)/eecfg.c main.c $(COSMIC_INCLUDE_C) $(COSMIC_INCLUDE_S)


############################################################################
#
# end
#
############################################################################
include $(EEBASE)/pkg/cfg/rules.mk
