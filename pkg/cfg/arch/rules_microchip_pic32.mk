# Enable verbose output from EE_OPT
ifeq ($(findstring VERBOSE,$(EEOPT)) , VERBOSE)
VERBOSE = 1
endif

# Initial definition of target all as predefined
all::

include $(EEBASE)/pkg/cfg/dir.mk
include $(PKGBASE)/cfg/verbose.mk
include $(PKGBASE)/cfg/compiler.mk

MCHP_DATA_DIR := $(PIC32_GCCDIR)/pic32mx
PIC32_LIB_DIR := $(MCHP_DATA_DIR)/lib
PIC32_INCLUDE_DIR := $(MCHP_DATA_DIR)/include

MCHP_SUPPORT_DIR := $(MCHP_DATA_DIR)
PIC32_H_DIR := $(MCHP_SUPPORT_DIR)/include
PIC32_LINKER_DIR := $(MCHP_SUPPORT_DIR)/lib/ldscripts

ifneq ($(ONLY_LIBS), TRUE)
ifneq ($(findstring __BIN_DISTR,$(EEALLOPT)), __BIN_DISTR) 
OPT_LIBS += -lee -L .
LIBDEP += libee.a
else
OPT_LIBS += -l$(EELIB) -L $(EEBASE)/lib
LIBDEP += $(EEBASE)/lib/lib$(EELIB).a
endif
endif

LIBDEP += $(ALL_LIBS)
LIBDEP += $(LDDEPS)
## Libraries from MC
OPT_LIBS += -lm -lc -ldsp
OPT_LIBS += -l$(subst .a,,$(subst lib,,$(PIC32_DEV_LIB)))

ifeq ($(findstring __RTD_LINUX__,$(EEOPT)) , __RTD_LINUX__)
OPT_LIBS += -L $(PIC32_LIB_DIR)
else
OPT_LIBS += -L "`cygpath -w $(PIC32_LIB_DIR)`"
endif
# check if PIC32_LIBD_DIR is empty
ifeq ($(findstring __RTD_LINUX__,$(EEOPT)) , __RTD_LINUX__)
ifneq ($(PIC32_LIBD_DIR),)
OPT_LIBS += -L $(PIC32_LIBD_DIR)
endif
else
ifneq ($(PIC32_LIBD_DIR),)
OPT_LIBS += -L "`cygpath -w $(PIC32_LIBD_DIR)`"
endif
endif

# #Includes from MC
ifeq ($(findstring __RTD_LINUX__,$(EEOPT)) , __RTD_LINUX__)
INTERNAL_GCCINCLUDEDIR := -I$(PIC32_INCLUDE_DIR)
else
INTERNAL_GCCINCLUDEDIR := -I"`cygpath -w $(PIC32_INCLUDE_DIR)`"
endif

ALLINCPATH += $(INTERNAL_GCCINCLUDEDIR)



################### PIC32-related directories
# we should look if these need to be moved inside dir.mk

#if PIC32_GCCDIR is defined
ifneq ($(PIC32_GCCDIR),)
DEFS_CC += -D__PIC32_INCLUDE_REGS__
MPLAB_INCLUDE_REGS=__PIC32_INCLUDE_REGS__
endif

# Add application file to dependencies
ifneq ($(ONLY_LIBS), TRUE)
TARGET := pic32.objdump pic32.hex
endif

# When building for MPLAB IDE, we do not have to include the source
# code of the application, but we have to include the library
# containing the EE code. 
# note that:
# - libee.a is not included in ALL_LIBS
# - when GENERATE_MPLABIDE_LIBS is defined, ONLY_LIBS is NOT defined
ifeq ($(GENERATE_MPLABIDE_LIBS), TRUE)
TARGET:=libee.a generate_eeopt

# we reset the SRCS variable (no application has to be compiled), and
# we put the eecfg.c inside the library
SRCS:=
LIBEESRCS+= $(OUTBASE)/eecfg.c
endif

include $(PKGBASE)/cfg/cfg.mk


#
# --------------------------------------------------------------------------
#

##
## Source files and paths
##

LIBEESRCS += $(EE_SRCS)
LIBEEOBJS := $(addprefix $(OBJDIR)/, $(patsubst %.c,%.o,$(patsubst %.S,%.o,$(LIBEESRCS))))

LIBEESRCS += $(LIB_SRCS)
LIBOBJS := $(addprefix $(OBJDIR)/, $(patsubst %.c,%.o,$(patsubst %.S,%.o,$(LIBSRCS))))

SRCS += $(APP_SRCS)
OBJS := $(addprefix $(OBJDIR)/, $(patsubst %.c,%.o,$(patsubst %.S,%.o, $(SRCS))))

vpath %.cd $(APPBASE)
vpath %.Sd $(APPBASE)
vpath %.c $(EE_VPATH) $(APPBASE)
vpath %.S $(EE_VPATH) $(APPBASE)


## Compute common variables ##

COMPUTED_ALLINCPATH := $(ALLINCPATH)
COMPUTED_OPT_LINK := $(OPT_LINK)
COMPUTED_OPT_ASM := $(OPT_ASM)
COMPUTED_OPT_CC := $(OPT_CC)
COMPUTED_OPT_CC_DEPS := $(OPT_CC_DEPS)

## Select input filename format ##
ifeq ($(findstring __RTD_LINUX__,$(EEOPT)) , __RTD_LINUX__)
SOURCEFILE = $<
TARGETFILE = $@
SRCFILE = $(patsubst %.o,%.src,$@)
else
SOURCEFILE = `cygpath -w $<`
TARGETFILE = `cygpath -w $@`
SRCFILE = `cygpath -w $(patsubst %.o,%.src,$@)`
endif

###########################
###########################
## Main rules: all clean ##
.PHONY: all clean

#all:: make_directories 
all:: make_directories $(ALL_LIBS) $(TARGET) 
	@printf "************************************\n\n"
	@printf "Compilation terminated successfully!\n"

clean::
	@-rm -rf *.a *.ld *.map *.$(PIC32_EXTENSION) *.objdump *.hex deps deps.pre obj ee_pic32regs.h
# to support "make clean all"
ifeq ($(findstring all,$(MAKECMDGOALS)),all)
	@printf "CLEAN (also \"all\" specified, frommchip directory not removed)\n"
else
	@printf "CLEAN\n";
	@-rm -rf frommchp
endif

pic32.objdump: pic32.$(PIC32_EXTENSION)
	@printf "OBJDUMP\n";
	$(QUIET)$(EE_OBJDUMP) -D pic32.$(PIC32_EXTENSION) > pic32.objdump

pic32.hex: pic32.$(PIC32_EXTENSION)
	@printf "BIN2HEX\n";
	$(QUIET)$(EE_BIN2HEX) pic32.$(PIC32_EXTENSION)

## Object file creation ###
# FIXME: chris: the -Map option is not working (does nothig).
pic32.$(PIC32_EXTENSION): $(OBJS) $(LINKDEP) $(LIBDEP) 
	@printf "LD\n";
	$(QUIET)$(EE_LINK) $(COMPUTED_OPT_LINK) \
		-o $(TARGETFILE) $(OBJS) \
		$(OPT_LIBS) \
		-Map=pic32.map
#--start-group $(OPT_LIBS) --end-group 
					 
ifeq ($(findstring BUILDSRC,$(EEALLOPT)), BUILDSRC)
# preprocess first the assembly code and then compile the object file
# chris: I found no *.inc file in the c32 distribution
#$(OBJDIR)/%.o: %.S ee_pic32regs.inc
$(OBJDIR)/%.o: %.S
	$(VERBOSE_PRINTPRE) $(EE_DEP) $(COMPUTED_ALLINCPATH) $(DEFS_ASM) -E "$(SOURCEFILE)" > $(SRCFILE)
	$(VERBOSE_PRINTASM) $(EE_ASM) $(COMPUTED_OPT_ASM) $(SRCFILE) -o $(TARGETFILE)
else
# produce the object file from assembly code in a single step
# chris: I found no *.inc file in the c32 distribution
#$(OBJDIR)/%.o: %.S ee_pic32regs.inc
$(OBJDIR)/%.o: %.S
	$(VERBOSE_PRINTCPP) $(EE_CC) $(COMPUTED_ALLINCPATH) $(DEFS_ASM) -c "$(SOURCEFILE)" -o $(TARGETFILE)
endif

ifeq ($(findstring BUILDSRC,$(EEALLOPT)), BUILDSRC)
# produce first the assembly from C code and then compile the object file
$(OBJDIR)/%.o: %.c ee_pic32regs.h
	$(VERBOSE_PRINTCPP) $(EE_CC) $(COMPUTED_OPT_CC) $(COMPUTED_ALLINCPATH) $(DEFS_CC) "$(SOURCEFILE)" -S -o $(SRCFILE)
	$(VERBOSE_PRINTASM) $(EE_ASM) $(COMPUTED_OPT_ASM) $(SRCFILE) -o $(TARGETFILE)
else
# produce the object file from C code in a single step
$(OBJDIR)/%.o: %.c ee_pic32regs.h
	$(VERBOSE_PRINTCPP) $(EE_CC) $(COMPUTED_OPT_CC) $(COMPUTED_ALLINCPATH) $(DEFS_CC) -c "$(SOURCEFILE)" -o $(TARGETFILE)
endif


##
## Microchip C32 files
##

# Check if the MCU model has been defined
ifneq ($(PIC32_MODEL),)

ee_pic32regs.h: frommchp/$(PIC32_INCLUDE_C)
	@printf "GEN ee_pic32regs.h\n"
	@printf "/* Automatically generated from Makefile */\n" > ee_pic32regs.h
	@printf "#include \"frommchp/$(PIC32_INCLUDE_C)\"\n" >> ee_pic32regs.h

# chris: I found no *.inc file in the c32 distribution
#ee_pic32regs.inc: frommchp/$(PIC32_INCLUDE_S)
#	@printf "GEN ee_pic32regs.inc\n"
#	@printf "; Automatically generated from Makefile\n" > ee_pic32regs.inc
#	@printf "	.equ __$(PIC32_MODEL), 1 \n" >> ee_pic32regs.inc
#	@printf "	.include \"frommchp/$(PIC32_INCLUDE_S)\" \n" >> ee_pic32regs.inc

frommchp/$(PIC32_INCLUDE_C): $(PIC32_H_DIR)/$(PIC32_INCLUDE_C)
	@printf "CP $(PIC32_INCLUDE_C)\n"; cp $(SOURCEFILE) $(TARGETFILE)

# chris: I found no *.inc file in the c32 distribution
#frommchp/$(PIC32_INCLUDE_S): $(PIC32_INC_DIR)/$(PIC32_INCLUDE_S)
#	@printf "CP $(PIC32_INCLUDE_S)\n"; cp $(SOURCEFILE) $(TARGETFILE)

else

# no MCU model defined
ee_pic32regs.h: frommchp/$(PIC32_INCLUDE_C)
	@printf "GEN ee_pic32regs.h\n"
	@printf "/* Automatically generated from Makefile */\n" > ee_pic32regs.h
	@printf "/* WARNING! No MCU model selected! */\n" >> ee_pic32regs.h

# chris: I found no *.inc file in the c32 distribution
#ee_pic32regs.inc: frommchp/$(PIC32_INCLUDE_S)
#	@printf "GEN ee_pic32regs.inc\n"
#	@printf "; Automatically generated from Makefile \n" > ee_pic32regs.inc
#	@printf "; WARNING! No MCU model selected! \n" >> ee_pic32regs.inc
endif


##
## Locator files
##

#if PIC32_GCCDIR is defined
#loc_gnu.ld: $(PIC32_LINKERDIR)/$(PIC32_LINKERSCRIPT)
#	@printf "LOC\n" ; cp $(PIC32_LINKERDIR)/$(PIC32_LINKERSCRIPT) loc_gnu.ld
loc_gnu.ld: $(PIC32_LINKER_DIR)/$(PIC32_LINKERSCRIPT)
	@printf "LOC\n" ; cp $(PIC32_LINKER_DIR)/$(PIC32_LINKERSCRIPT) loc_gnu.ld

##
## EE Library
##

libee.a: $(LIBEEOBJS)
	@printf "AR  libee.a\n" ;
	$(QUIET)$(EE_AR) rs libee.a $(LIBEEOBJS)


##
## Automatic Generation of dependencies
##

# deps depends on the flag and not on the PHONY rule!
deps: $(OBJDIR)/.make_directories_flag deps.pre
	@printf "GEN deps\n"
	@sed "s/ \<\([A-Za-z]\):/ \/cygdrive\/\l\1/g" < deps.pre > deps

deps.pre: $(addprefix $(OBJDIR)/, $(patsubst %.S,%.Sd,$(patsubst %.c,%.cd, $(SRCS) $(LIBEESRCS) $(LIBSRCS))))
	@printf "GEN deps.pre\n" ; cat $^ > deps.pre

# generate dependencies for .c files and add "file.cd" to the target
$(OBJDIR)/%.cd: %.c ee_pic32regs.h
	$(VERBOSE_PRINTDEP) $(EE_DEP) $(COMPUTED_OPT_CC_DEPS) $(COMPUTED_ALLINCPATH) $(DEFS_CC) -M "$(SOURCEFILE)" > $(TARGETFILE).tmp
	@echo -n $(TARGETFILE) $(dir $(TARGETFILE)) | cat - $(TARGETFILE).tmp > $(TARGETFILE)
	@rm -rf $(TARGETFILE).tmp
	@test -s $(TARGETFILE) || rm -f $(TARGETFILE)

# generate dependencies for .S files and add "file.Sd" to the target
# chris: I found no *.inc file in the c32 distribution
#$(OBJDIR)/%.Sd: %.S ee_pic32regs.inc
$(OBJDIR)/%.Sd: %.S 
	$(VERBOSE_PRINTDEP) $(EE_DEP) $(COMPUTED_ALLINCPATH) $(DEFS_ASM) -M "$(SOURCEFILE)" > $(TARGETFILE).tmp
	@echo -n $(TARGETFILE) $(dir $(TARGETFILE)) | cat - $(TARGETFILE).tmp > $(TARGETFILE)
	@rm -rf $(TARGETFILE).tmp
	@test -s $(TARGETFILE) || rm -f $(TARGETFILE)


#
# --------------------------------------------------------------------------
#

# interesting read: http://www.cmcrossroads.com/content/view/6936/120/

# this forces the directory creation when issuing the "make all"
# rule. there is need for this rule because it may be that the user
# asks for a "make clean all". "clean" removes the directories which
# are then needed for "all", so that when "all" arrives the
# directories must be recreated. We cannot use a flag file like in the
# rule just after because when there is a "clean all" the check for
# prerequisites is not done again when doing "all".
.PHONY: make_directories
make_directories:
ifneq ($(findstring clean,$(MAKECMDGOALS)),clean)
	@printf "MAKE_DIRECTORIES (after a clean)\n"
	$(QUIET)mkdir -p $(dir $(basename $(addprefix $(OBJDIR)/, $(SRCS) $(LIBEESRCS) $(LIBSRCS)))) frommchp #obj/frommchp
endif

# this checks but not forces the directory creation when creating dependencies
$(OBJDIR)/.make_directories_flag:
	@printf "MAKE_DIRECTORIES\n"
	$(QUIET)mkdir -p $(dir $(basename $(addprefix $(OBJDIR)/, $(SRCS) $(LIBEESRCS) $(LIBSRCS)))) frommchp #obj/frommchp
	$(QUIET)touch $(TARGETFILE)

#
# --------------------------------------------------------------------------
#

# the eeopt file is generated when dealing with MPLAB IDE!
#
# this is a phony because the source code does not depend on this file
# and its content higly depends on the EEOPT variables...
#
.PHONY: generate_eeopt
generate_eeopt:
	@printf "MPLAB - eeopt.h\n"
	@echo // This part of the include file includes all the options > eeopt.h
	@echo // which are typically inserted with >> eeopt.h
	@echo // the -D compiler directive. >> eeopt.h
	@echo // This part is automatically generated by the makefile only for MPLABIDE. >> eeopt.h
	@for x in $(EEOPT) $(MPLAB_INCLUDE_REGS); do \
		echo \#ifndef $${x}      >> eeopt.h; \
		echo \#define $${x}      >> eeopt.h; \
		echo \#endif             >> eeopt.h; \
	done;



#
# --------------------------------------------------------------------------
#

ifndef NODEPS
ifneq ($(MAKECMDGOALS),clean)
ifneq ($(findstring NODEPS,$(EEALLOPT)), NODEPS) 
-include deps
endif
endif
endif
