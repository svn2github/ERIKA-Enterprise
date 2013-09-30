

############################################################################
#
# STM32F4XX_SPD Options
#
############################################################################
EEOPT += __USE_STM32F4XX_SPD__



############################################################################
#
# STM32F4_DISCOVERY Options
#
############################################################################
EEOPT += __USE_STM32F4_DISCOVERY__
EEOPT += __USE_STM32F4_DISCOVERY_LEDS__

### Setting Erika's variables:
# ERIKA_FILES= ../../..
# APPBASE = .
# 
# EEOPT =


RTDRUID_CONFIGURATOR_NUMBER:=1277



############################################################################
#
# User options
#
############################################################################
EEOPT += DEBUG
EEOPT += VERBOSE
EEOPT += __ASSERT__
EEOPT += __ADD_LIBS__

############################################################################
#
# Automatic options
#
############################################################################
EEOPT += __RTD_LINUX__
EEOPT += __STM32__
EEOPT += __STM32F4xx__
EEOPT += __CORTEX_MX__
EEOPT += __CORTEX_M4__
EEOPT += __GNU__
EEOPT += __FP__
EEOPT += __MONO__
EEOPT += __FP_NO_RESOURCES__
EEOPT += __DISABLE_EEOPT_DEFINES__


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
        EEBASE := $(shell cygpath `cygpath -ms 'C:\Users\Alessandro\Documenti\ee_VM\ee'`)
else
        $(warning The usage of EEBASE is deprecated. Please use ERIKA_FILES)
endif
endif # ERIKA_FILES
# ERIKA_FILES has fulfilled its role. Make sure it's not used inside Erika makefiles
ERIKA_FILES :=
$(info Using erika files in $(EEBASE))


############################################################################
#
# CORTEX M4
#
############################################################################
include $(EEBASE)/pkg/cfg/path_helper.mk
APPBASE := 
OUTBASE := Debug

ifndef GNU_ARM_ROOT
    GNU_ARM_ROOT := $(shell cygpath `cygpath -ms 'C:\Programmi\GNU Tools ARM Embedded\4.7 2013q1'`)
endif


############################################################################
#
# Init MCU for CORTEX Mx (STM32F4xx)
#
############################################################################
STM32_MODEL           := STM32F4xx


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

LIB_OPT  += __LIB_ST_CMSIS__
LIB_OPT  += __LIB_STM32F4XX_SPD__
LIB_OPT  += __LIB_STM32F4_DISCOVERY__


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
