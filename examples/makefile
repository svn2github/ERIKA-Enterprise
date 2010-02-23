# Regression makefile
#
# Use this makefile to test the compilation of all examples

# ---------------------------------------------------------

# PIC30 templates

#TEMPLATE_LIST_PIC30 += board_flex       # OK - this is a scilab template
#TEMPLATE_LIST_PIC30 += board_flex_proto # OK - this is a scilab template
#TEMPLATE_LIST_PIC30 += eicaslab_flex    # OK - this is a scilab template

# check why they do not work
#TEMPLATE_LIST_PIC30 += pic30_empty
#TEMPLATE_LIST_PIC30 += pic30_ant_empty
#TEMPLATE_LIST_PIC30 += pic30_libs
#TEMPLATE_LIST_PIC30 += pic30_lib_scicos
#TEMPLATE_LIST_PIC30 += pic30_uwl_demo_device
#TEMPLATE_LIST_PIC30 += pic30_uwl_demo_coord

TEMPLATE_LIST_PIC30 += pic30_DemoBoard_base
TEMPLATE_LIST_PIC30 += pic30_DemoBoard_ConsoleLib
TEMPLATE_LIST_PIC30 += pic30_dspicdem11plus_device
TEMPLATE_LIST_PIC30 += pic30_edf_periodic
TEMPLATE_LIST_PIC30 += pic30_Explorer16_Devices
TEMPLATE_LIST_PIC30 += pic30_explorer16_resource_lcd
TEMPLATE_LIST_PIC30 += pic30_Firmware_February
TEMPLATE_LIST_PIC30 += pic30_frsh_coverage
TEMPLATE_LIST_PIC30 += pic30_MiWiP2P
TEMPLATE_LIST_PIC30 += pic30_oo_event
TEMPLATE_LIST_PIC30 += pic30_oo_resource
TEMPLATE_LIST_PIC30 += pic30_oo_task
TEMPLATE_LIST_PIC30 += board_flex_openzb_demo
TEMPLATE_LIST_PIC30 += pic30_res_scheduler
TEMPLATE_LIST_PIC30 += pic30_semaphore
TEMPLATE_LIST_PIC30 += pic30_MultiBus_Serial

# -----------------------------------------------------------

ifndef TEMPLATE_LIST
TEMPLATE_LIST := $(TEMPLATE_LIST_$(ARCH))
endif

.PHONY: help all clean list listmissing witherrors

help:
	@echo Regression makefile
	@echo -----------------------------------------
	@echo Usage:
	@echo 1 - Cleaning the repository
	@echo "      make clean"
	@echo 2 - making the regression
	@echo "   NOTE:"
	@echo "    - will create a regression directory"
	@echo "    - already done examples will not be compiled"
	@echo "    - use -j to speed up!"
	@echo
	@echo "      make -j 4 all TEMPLATE_LIST=templatename"
	@echo "      make -j 4 all ARCH=PIC30"
	@echo 3 - list all available templates
	@echo "      make list"
	@echo 4 - list all templates not tested during this session
	@echo "      make listmissing"
	@echo 5 - list all templates with errors during the current session
	@echo "      make witherrors"


BATCH_DIR=/cygdrive/c/Evidence/eclipse/evidence
BATCH_TEMPLATE=$(BATCH_DIR)/template_launcher.bat
BATCH_GENERATOR=$(BATCH_DIR)/rtd_launcher.bat

ECLIPSE_HOME="C:\\Evidence\\eclipse"

FLAGS=$(addsuffix /doneflag.txt,$(addprefix regression/,$(TEMPLATE_LIST)))

all: $(FLAGS)

regression/%/doneflag.txt:
	@rm -rf regression/$*
	@mkdir -p regression/$*
	@printf "$*: START\n"
	@printf "$*: START\n" >>regression/output.log
	@printf "$*: template\n"
	@printf "$*: template\n" >>regression/output.log
	@cd regression/$*; export ECLIPSE_HOME=$(ECLIPSE_HOME); $(BATCH_TEMPLATE) --template $* --output . 2>&1 >>output.log
	@printf "$*: OIL\n"
	@printf "$*: OIL\n" >>regression/output.log
	@cd regression/$*; export ECLIPSE_HOME=$(ECLIPSE_HOME); $(BATCH_GENERATOR) --template $* --output . 2>&1 >>output.log
	@printf "$*: Compile\n"
	@printf "$*: Compile\n" >>regression/output.log
	@+make -C regression/$*/Debug 2>&1 >>regression/$*/output.log
	@printf "$*: OK\n-------------------------------------\n"
	@printf "$*: OK\n-------------------------------------\n" >>regression/output.log
	@touch regression/$*/doneflag.txt

clean:
	rm -rf regression

regression/templatelist:
	@mkdir -p regression
	@find . -iname template.xml | xargs grep ID | sed s/.*ID=\"// | sed s/\"\>// >regression/templatelist

list: regression/templatelist
	@cat regression/templatelist

regression/current_ok_tests: regression/output.log
	@mkdir -p regression
	@grep -e ': OK$$' regression/output.log | sed "s/: OK//" >regression/current_ok_tests


regression/current_missing_tests: regression/templatelist regression/current_ok_tests
	@mkdir -p regression
	@grep -v -f regression/current_ok_tests regression/templatelist > regression/current_missing_tests

listmissing: regression/current_missing_tests
	@cat regression/current_missing_tests

# difference between the directory listing and the tests which are ok
witherrors: regression/current_ok_tests
	@find regression -maxdepth 1 -type d | grep "regression/" | sed "s/regression\\///" | grep -v -f regression/current_ok_tests
