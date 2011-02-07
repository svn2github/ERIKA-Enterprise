# Generic Makefile for CAL actor networks, via C, to executable
#
# Use 'make help' to view available make targets

# delete the built-in suffixes to avoid surprises
.SUFFIXES:   

# Default definitions of tools and directories
include /home/antonio/Evidence/svn/opendf/trunk/contrib/actorsproject/share/actors-make/definitions.mk

#
# This is a good place for project-specific definitions:
# ------------------------------------------------------

# Source directory (default is current directory)
# export srcdir=/home/me/MPEG4_SP_Decoder

# Additional libraries
# override LDLIBS += -lmylib1 -mylib2
export LDLIBS

# Additional C-files to be compiled (and included in linking)
# override C_FILES += foo.c bar.c
export C_FILES

# Target architecture prefix of gcc and binutils (default is none)
ifdef ARM
export target=arm-none-linux-gnueabi-
endif

# Generate debug code
# DEBUG=Y

# Enable actor merging (experimental and potentially dangerous)
#export MERGE=Y


# ------------------------------------------------------
# Make-rules start here
#

.PHONY: all clean cleaner cleanest help


#
# Available CAL networks and those already elaborated/built
#
srcdir?=.
CAL_NETWORKS=$(wildcard $(srcdir)/*.nl)
AVAILABLE_MODELS=$(patsubst %.nl, %, $(notdir $(CAL_NETWORKS)))
CLEAN_TARGETS=$(patsubst compiled/%, clean-%, $(wildcard compiled/*))

#
# all: display help
#

all: help

#
# Make executable from CAL model/network
#

SRCDIR_ABS=$(abspath $(srcdir))
MAKEMODEL=$(MAKE) -f $(ACTORS_MAKE)/makemodel.mk srcdir=$(SRCDIR_ABS)

# Let makemodel.mk check if executable is up-to-date
.PHONY: $(AVAILABLE_MODELS)

$(AVAILABLE_MODELS) : % :
	@mkdir -p compiled/$*
	@$(MAKEMODEL) -C compiled/$* MODEL=$* EXE=../../$* all

#
# clean: Clean all build files
#

.PHONY: $(CLEAN_TARGETS)

clean: $(CLEAN_TARGETS)

$(CLEAN_TARGETS) : clean-% :
	@$(MAKEMODEL) -C compiled/$* MODEL=$* EXE=../../$* clean

clean-%:
	@echo "No build files for model $*"

#
# help: print usage
#

ifeq ("$(AVAILABLE_MODELS)", "")
  HELP_AVAILABLE="No models available in $(srcdir)/ use srcdir=directory"
else
  HELP_AVAILABLE=Available models: $(AVAILABLE_MODELS)
endif

help:
	@echo
	@echo 'Usage: make [srcdir=<source-directory>] <target>'
	@echo
	@echo '"make <model>" elaborates and builds a CAL model' 
	@echo $(HELP_AVAILABLE) 
	@echo
	@echo '"make clean-<model>" cleans build files'
	@echo
