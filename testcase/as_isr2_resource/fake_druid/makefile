### Setting Erika's variables:
# ERIKA_FILES= ../../..
# APPBASE = .
# 
# EEOPT =


RTDRUID_CONFIGURATOR_NUMBER:=1276



############################################################################
#
# User options
#
############################################################################

EEOPT += __ASSERT__
EEOPT += DEBUG
EEOPT += __E200ZX_EXECUTE_FROM_RAM__


############################################################################
#
# Automatic options
#
############################################################################
EEOPT += __RTD_LINUX__
EEOPT += __PPCE200ZX__
EEOPT += __MPC5674F__
EEOPT += __PPCE200Z7__
EEOPT += __DIAB__
EEOPT += __OO_ECC1__
EEOPT += __OO_HAS_ERRORHOOK__
EEOPT += __MULTI__
EEOPT += __OO_NO_ALARMS__
EEOPT += __OO_NO_EVENTS__
EEOPT += __DISABLE_EEOPT_DEFINES__
EEOPT += __ALLOW_NESTED_IRQ__
EEOPT += __OO_ISR2_RESOURCES__
EEOPT += __OO_STARTOS_OLD__
ifdef EXT
EEOPT += __OO_EXTENDED_STATUS__
endif
EEOPT += EE_ISR_DYNAMIC_TABLE

############################################################################
#
# Erika base directory
#
############################################################################
ifdef ERIKA_FILES
ifdef EEBASE
    $(warning EEBASE is set, but it has been overridden by ERIKA_FILES)
endif
EEBASE := ${ERIKA_FILES}

else # ERIKA_FILES

ifndef EEBASE
        EEBASE := /home/eguidieri/evidence/eclipse/plugins/com.eu.evidence.ee_1.6.0.20111215_1046/ee_files
else
        $(warning The usage of EEBASE is deprecated. Please use ERIKA_FILES)
endif
endif # ERIKA_FILES
# ERIKA_FILES has fulfilled its role. Make sure it's not used inside Erika makefiles
ERIKA_FILES :=


############################################################################
#
# Freescale MPC5674F, PPC E200Z7
#
############################################################################
APPBASE := ..
OUTBASE := output



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
APP_SRCS += eecfg.c code.c testcase/common/e200zx/test_irq.c


############################################################################
#
# end
#
############################################################################
include $(EEBASE)/pkg/cfg/rules.mk
