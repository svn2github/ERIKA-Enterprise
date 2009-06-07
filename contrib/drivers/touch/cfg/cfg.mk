## Author: 2009 Francesco Prosperi
## Check the Touch library selection
ifeq ($(findstring __LIB_TOUCH__,$(LIB_OPT)),__LIB_TOUCH__)

##
## Application files
##

EE_SRCS += contrib/drivers/touch/src/touch.c

endif
