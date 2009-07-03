## Author: 2009 Francesco Prosperi
## Check the Touch library selection
ifeq ($(findstring __LIB_TOUCH__,$(LIB_OPT)),__LIB_TOUCH__)

##
## Application files
##

EE_SRCS += contrib/drivers/touch/src/touch.c
EE_SRCS += contrib/drivers/touch/src/touch_timer_dspic30.c
EE_SRCS += contrib/drivers/touch/src/touch_kal_erika.c

endif
