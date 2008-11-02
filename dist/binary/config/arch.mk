# architecture dependent variables

# This file is included ALSO by the source distribution scripts!!!

# -------------------------------------------------------------------


ifeq ($(findstring NIOS2,$(DIST)) , NIOS2)
ifndef EE_NIOS2_VERSION
EE_NIOS2_VERSION=80
endif
endif

