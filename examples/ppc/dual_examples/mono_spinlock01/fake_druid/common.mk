

############################################################################
#
# Makefile created by RT-Druid
# 
# Common file
#
############################################################################

# Erika base directory
ifndef EEBASE
    EEBASE  := /extra/eclipse_mm/plugins/com.eu.evidence.ee_1.6.0.MM_201102010010/ee_base
endif


############################################################################
#
# Common EE options
#
############################################################################
EEOPT += 
EEOPT += __ASSERT__
EEOPT += __E200ZX_EXECUTE_FROM_RAM__
EEOPT += __RTD_LINUX__
EEOPT += __MSRP__
EEOPT += __PPCE200ZX__
EEOPT += __MPC5668G__
EEOPT += __FP__
EEOPT += __MONO__



############################################################################
#
# Flags
#
############################################################################
CFLAGS   = -g2

ASFLAGS  = 

LDFLAGS := 

LDDEPS  += 

LIBS    := 

