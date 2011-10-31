## Author: 2011 Gianluca Franchino

ifeq ($(findstring __LIB_CMSIS__,$(LIB_OPT)) , __LIB_CMSIS__)

##
## CMSIS files
## 


SRCS += $(shell ls $(EEBASE)/contrib/nxp/lpc12xx_cmsis_v2_0/libsrc/CM0/CoreSupport/*.c)
SRCS += $(shell ls $(EEBASE)/contrib/nxp/lpc12xx_cmsis_v2_0/libsrc/CM0/DeviceSupport/NXP/LPC12xx/*.c)

#ifeq ($(call iseeopt, __IAR__), yes)
#ifneq ($(call iseeopt, __USE_CUSTOM_CRT0__), yes)
#SRCS += $(shell ls $(EEBASE)/contrib/nxp/lpc12xx_cmsis_v2_0/libsrc/CM0/DeviceSupport/NXP/LPC12xx/startup/iar/*.s)
#endif
#endif


#FIXME: lpc12xx_crc.c does not compile -> remove from the source
ifeq ($(call iseeopt, __USE_CMSIS_ALL__), yes)
SRCS += $(shell ls $(EEBASE)/contrib/nxp/lpc12xx_cmsis_v2_0/libsrc//Drivers/source/*.c | grep -v crc)

else

SRCS += $(shell ls $(EEBASE)/contrib/nxp/lpc12xx_cmsis_v2_0/libsrc//Drivers/source/lpc12xx_libcfg_default.c)

ifeq ($(call iseeopt, __USE_CMSIS_SYSCTRL__), yes)
SRCS += $(shell ls $(EEBASE)/contrib/nxp/lpc12xx_cmsis_v2_0/libsrc//Drivers/source/lpc12xx_sysctrl.c)
endif

ifeq ($(call iseeopt, __USE_CMSIS_GPIO__), yes)
SRCS += $(shell ls $(EEBASE)/contrib/nxp/lpc12xx_cmsis_v2_0/libsrc//Drivers/source/lpc12xx_gpio.c)
endif

ifeq ($(call iseeopt, __USE_CMSIS_IOCON__), yes)
SRCS += $(shell ls $(EEBASE)/contrib/nxp/lpc12xx_cmsis_v2_0/libsrc//Drivers/source/lpc12xx_iocon.c)
endif

ifeq ($(call iseeopt, __USE_CMSIS_DBGFWK__), yes)
SRCS += $(shell ls $(EEBASE)/contrib/nxp/lpc12xx_cmsis_v2_0/libsrc//Drivers/source/debug_frmwrk.c)
endif

ifeq ($(call iseeopt, __USE_CMSIS_UART__), yes)
SRCS += $(shell ls $(EEBASE)/contrib/nxp/lpc12xx_cmsis_v2_0/libsrc//Drivers/source/lpc12xx_uart.c)
endif

ifeq ($(call iseeopt, __USE_CMSIS_CRC__), yes)
$(error "!!!lpc12xx_crc.c does not compile. Currently the CMSIS CRC routines are not supported!!!")
#SRCS += $(shell ls $(EEBASE)/contrib/nxp/lpc12xx_cmsis_v2_0/libsrc//Drivers/source/lpc12xx_crc.c)
endif

ifeq ($(call iseeopt, __USE_CMSIS_SSP__), yes)
SRCS += $(shell ls $(EEBASE)/contrib/nxp/lpc12xx_cmsis_v2_0/libsrc//Drivers/source/lpc12xx_ssp.c)
endif

ifeq ($(call iseeopt, __USE_CMSIS_RTC__), yes)
SRCS += $(shell ls $(EEBASE)/contrib/nxp/lpc12xx_cmsis_v2_0/libsrc//Drivers/source/lpc12xx_rtc.c)
endif

ifeq ($(call iseeopt, __USE_CMSIS_FLASH__), yes)
SRCS += $(shell ls $(EEBASE)/contrib/nxp/lpc12xx_cmsis_v2_0/libsrc//Drivers/source/lpc12xx_flash.c)
endif

ifeq ($(call iseeopt, __USE_CMSIS_I2C__), yes)
SRCS += $(shell ls $(EEBASE)/contrib/nxp/lpc12xx_cmsis_v2_0/libsrc//Drivers/source/lpc12xx_i2c.c)
endif

ifeq ($(call iseeopt, __USE_CMSIS_PMU__), yes)
SRCS += $(shell ls $(EEBASE)/contrib/nxp/lpc12xx_cmsis_v2_0/libsrc//Drivers/source/lpc12xx_pmu.c)
endif

ifeq ($(call iseeopt, __USE_CMSIS_DMA__), yes)
SRCS += $(shell ls $(EEBASE)/contrib/nxp/lpc12xx_cmsis_v2_0/libsrc//Drivers/source/lpc12xx_dma.c)
endif

ifeq ($(call iseeopt, __USE_CMSIS_ADC__), yes)
SRCS += $(shell ls $(EEBASE)/contrib/nxp/lpc12xx_cmsis_v2_0/libsrc//Drivers/source/lpc12xx_adc.c)
endif

ifeq ($(call iseeopt, __USE_CMSIS_TIMER32__), yes)
SRCS += $(shell ls $(EEBASE)/contrib/nxp/lpc12xx_cmsis_v2_0/libsrc//Drivers/source/lpc12xx_timer32.c)
endif

ifeq ($(call iseeopt, __USE_CMSIS_WDT__), yes)
SRCS += $(shell ls $(EEBASE)/contrib/nxp/lpc12xx_cmsis_v2_0/libsrc//Drivers/source/lpc12xx_wdt.c)
endif

ifeq ($(call iseeopt, __USE_CMSIS_COMP__), yes)
SRCS += $(shell ls $(EEBASE)/contrib/nxp/lpc12xx_cmsis_v2_0/libsrc//Drivers/source/lpc12xx_comp.c)
endif

ifeq ($(call iseeopt, __USE_CMSIS_TIMER16__), yes)
SRCS += $(shell ls $(EEBASE)/contrib/nxp/lpc12xx_cmsis_v2_0/libsrc//Drivers/source/lpc12xx_timer16.c)
endif

endif

endif