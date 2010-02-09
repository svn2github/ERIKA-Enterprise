# ###*B*###
# Copyright (C) Roberto Bucher (SUPSI- Lugano)
#               Simone Mannori (Scilab / INRIA / DIGITEO)
#
# Copyright (C) METALAU Project (INRIA)
# ###*E*###
 
 
## Author: 2007 Mauro Marinoni
## CVS: $Id: cfg.mk,v 1.5 2008/07/18 11:24:24 pj Exp $

ifeq ($(findstring __LIB_SCICOS__,$(LIB_OPT)),__LIB_SCICOS__)

EE_VPATH += $(EEBASE)/contrib/scicos/src/pic30
EE_VPATH += $(EEBASE)/contrib/scicos/src/pic30/communication
EE_VPATH += $(EEBASE)/contrib/scicos/src/pic30/communication/udp
EE_VPATH += $(EEBASE)/contrib/scicos/libsrc/rt
EE_VPATH += $(EEBASE)/contrib/scicos/libsrc/core

ifeq ($(findstring __RTD_CYGWIN__,$(EEOPT)), __RTD_CYGWIN__) 
ALLINCPATH += -I"$(shell cygpath -w $(EEBASE)/contrib/scicos/inc/core)"
ALLINCPATH += -I"$(shell cygpath -w $(EEBASE)/contrib/scicos/inc/pic30/communication)"
ALLINCPATH += -I"$(shell cygpath -w $(EEBASE)/contrib/scicos/inc/pic30/communication/udp)"
else
ALLINCPATH += -I$(EEBASE)/contrib/scicos/inc/core
ALLINCPATH += -I$(EEBASE)/contrib/scicos/inc/pic30/communication
ALLINCPATH += -I$(EEBASE)/contrib/scicos/inc/pic30/communication/udp
endif
##
## Application files
##

ifeq ($(findstring __NIOS2__,$(EEOPT)) , __NIOS2__)

EE_SRCS +=      contrib/scicos/src/nios2/led.c \
		contrib/scicos/src/nios2/button.c \
		contrib/scicos/src/nios2/sevenseg.c 

endif

ifeq ($(findstring __EE_FLEX__,$(EEOPT)) , __EE_FLEX__)

#If the  blocks list (from Scicos Code Generation) is empty, compile all the pic30 block sources
ifeq ($(EE_SRCS_SCICOS),)

EE_SRCS_SCICOS_DSPIC := $(addprefix contrib/scicos/src/pic30/, $(notdir $(shell ls -1 $(EEBASE)/contrib/scicos/src/pic30/*.c)))
EE_SRCS += $(EE_SRCS_SCICOS_DSPIC)

ifeq ($(findstring __LIB_IEEE802154__,$(LIB_OPT)),__LIB_IEEE802154__)
EE_SRCS_SCICOS_DSPIC_OPENZB := $(addprefix contrib/scicos/src/pic30/openzb/, $(notdir $(shell ls -1 $(EEBASE)/contrib/scicos/src/pic30/openzb/*.c)))
EE_SRCS += $(EE_SRCS_SCICOS_DSPIC_OPENZB)
endif

##
## Add Scicos to the linker list of libs
##
OPT_LIBS += -lscicos

else 

EE_SRCS += $(EE_SRCS_SCICOS)

ifeq ($(findstring __USE_UDP__,$(EEOPT)) , __USE_UDP__)
EE_SRCS += contrib/scicos/src/pic30/communication/flex_udp.c
endif


endif

endif

endif




