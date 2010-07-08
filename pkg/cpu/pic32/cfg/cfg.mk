ifeq ($(findstring __PIC32__,$(EEOPT)) , __PIC32__)
EE_SRCS += pkg/cpu/pic32/src/ee_hal.S
EE_SRCS += pkg/cpu/pic32/src/ee_hal_c.c
EE_SRCS += pkg/cpu/pic32/src/ee_utils.c

ifeq ($(findstring __OO_BCC1__,$(EEOPT)) , __OO_BCC1__)
CPU_OO=YES
endif
ifeq ($(findstring __OO_BCC2__,$(EEOPT)) , __OO_BCC2__)
CPU_OO=YES
endif
ifeq ($(findstring __OO_ECC1__,$(EEOPT)) , __OO_ECC1__)
CPU_OO=YES
endif
ifeq ($(findstring __OO_ECC2__,$(EEOPT)) , __OO_ECC2__)
CPU_OO=YES
endif

ifeq ($(CPU_OO), YES)
EE_SRCS += pkg/cpu/pic32/src/ee_oo.S
endif

endif
