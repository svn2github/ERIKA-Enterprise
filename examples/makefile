# Regression makefile
#
# Use this makefile to test the compilation of all examples

# ---------------------------------------------------------

# list of all architectures
ARCH_LIST = PIC30 ARM7 AVR5 ESI_RISC NIOS2 E200ZX S12XS TRICORE

# PIC30 templates
# -----------------------------------------------------------
TEMPLATE_LIST_IGNORE_PIC30 += board_flex       # OK - this is a scilab template
TEMPLATE_LIST_IGNORE_PIC30 += board_flex_proto # OK - this is a scilab template
TEMPLATE_LIST_IGNORE_PIC30 += eicaslab_flex    # OK - this is a scilab template
TEMPLATE_LIST_PIC30 += pic30_empty
TEMPLATE_LIST_PIC30 += pic30_ant_empty
TEMPLATE_LIST_PIC30 += pic30_libs
TEMPLATE_LIST_PIC30 += pic30_lib_scicos
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
TEMPLATE_LIST_PIC30 += pic30_uwl_demo_coord
TEMPLATE_LIST_PIC30 += pic30_uwl_demo_device
TEMPLATE_LIST_PIC30 += pic24_miwi_p2p_demo
TEMPLATE_LIST_PIC30 += pic30_Demo2Board_base
TEMPLATE_LIST_PIC30 += pic30_miniflex_hello

# ARM7 templates
# -----------------------------------------------------------
TEMPLATE_LIST_ARM7 += e7t_fp

# AVR5 templates
# -----------------------------------------------------------
TEMPLATE_LIST_IGNORE_AVR5 +=
TEMPLATE_LIST_AVR5 += avr5_blink
TEMPLATE_LIST_AVR5 += avr5_blink_timers
TEMPLATE_LIST_AVR5 += avr5_ConsoleLib
TEMPLATE_LIST_AVR5 += avr5_first
TEMPLATE_LIST_AVR5 += avr5_serial
TEMPLATE_LIST_AVR5 +=
TEMPLATE_LIST_AVR5 +=

# ESI_RISC templates
# -----------------------------------------------------------
TEMPLATE_LIST_ESI_RISC += ESI_RISC_EE_MONOSTACK_TEST0
TEMPLATE_LIST_ESI_RISC += ESI_RISC_EE_MONOSTACK_TEST1
TEMPLATE_LIST_ESI_RISC += ESI_RISC_EE_MONOSTACK_TEST2
TEMPLATE_LIST_ESI_RISC += ESI_RISC_EE_MONOSTACK_TEST3
TEMPLATE_LIST_ESI_RISC += ESI_RISC_EE_MONOSTACK_TEST4
TEMPLATE_LIST_ESI_RISC += ESI_RISC_EE_MONOSTACK_TEST5
TEMPLATE_LIST_ESI_RISC += ESI_RISC_EE_MONOSTACK_TEST6
TEMPLATE_LIST_ESI_RISC += ESI_RISC_EE_MONOSTACK_TEST7
TEMPLATE_LIST_ESI_RISC += ESI_RISC_EE_MONOSTACK_TEST8
TEMPLATE_LIST_ESI_RISC += ESI_RISC_EE_MULTISTACK_TEST0
TEMPLATE_LIST_ESI_RISC += ESI_RISC_EE_MULTISTACK_TEST1
TEMPLATE_LIST_ESI_RISC += ESI_RISC_EE_MULTISTACK_TEST2
TEMPLATE_LIST_ESI_RISC += ESI_RISC_EE_MULTISTACK_TEST3
TEMPLATE_LIST_ESI_RISC += ESI_RISC_EE_MULTISTACK_TEST4
TEMPLATE_LIST_ESI_RISC += ESI_RISC_EE_MULTISTACK_TEST5
TEMPLATE_LIST_ESI_RISC += ESI_RISC_EE_MULTISTACK_TEST6


# NIOS2 templates
# -----------------------------------------------------------
TEMPLATE_LIST_NIOS2 += nios2_oo_event
TEMPLATE_LIST_NIOS2 += nios2_oo_resource
TEMPLATE_LIST_NIOS2 += nios2_oo_task
TEMPLATE_LIST_NIOS2 += nios2_2cpu
TEMPLATE_LIST_NIOS2 += nios2_2cpu_fifo
TEMPLATE_LIST_NIOS2 += nios2_frsh_coverage_multiirq
TEMPLATE_LIST_NIOS2 += nios2_frsh_coverage_singleirq
TEMPLATE_LIST_NIOS2 += nios2_frsh_multicpu1
TEMPLATE_LIST_NIOS2 += nios2_frsh_multicpu2


# E200ZX templates
# -----------------------------------------------------------
TEMPLATE_LIST_E200ZX += E200Z7_EE_MONOSTACK_RESOURCE_DEMO
TEMPLATE_LIST_E200ZX += E200Z7_EE_MONOSTACK_TASK_DEMO
TEMPLATE_LIST_E200ZX += E200Z7_EE_MULTISTACK_EVENT_DEMO
TEMPLATE_LIST_E200ZX += E200Z7_EE_MULTISTACK_TASK_DEMO

# S12XS templates
# -----------------------------------------------------------
TEMPLATE_LIST_S12XS += S12XS_COSMIC_EE_TEST9_MONOSTACK_CONSOLEDEMO
TEMPLATE_LIST_S12XS += S12XS_COSMIC_EE_TEST9_MONOSTACK_RESOURCEDEMO
TEMPLATE_LIST_S12XS += S12XS_COSMIC_EE_TEST9_MONOSTACK_TASKDEMO
TEMPLATE_LIST_S12XS += S12XS_COSMIC_EE_MULTISTACK_EVENT_DEMO
TEMPLATE_LIST_S12XS += S12XS_COSMIC_EE_MULTISTACK_TASK_DEMO
TEMPLATE_LIST_S12XS += S12XS_COSMIC_EE_TEST0
TEMPLATE_LIST_S12XS += S12XS_COSMIC_EE_TEST1
TEMPLATE_LIST_S12XS += S12XS_COSMIC_EE_TEST2
TEMPLATE_LIST_S12XS += S12XS_COSMIC_EE_TEST3
TEMPLATE_LIST_S12XS += S12XS_COSMIC_EE_TEST4
TEMPLATE_LIST_S12XS += S12XS_COSMIC_EE_TEST5
TEMPLATE_LIST_S12XS += S12XS_COSMIC_EE_TEST6
TEMPLATE_LIST_S12XS += S12XS_COSMIC_EE_TEST7
TEMPLATE_LIST_S12XS += S12XS_COSMIC_EE_TEST8
TEMPLATE_LIST_S12XS += S12XS_COSMIC_EE_TEST0_MULTISTACK
TEMPLATE_LIST_S12XS += S12XS_COSMIC_EE_TEST1_MULTISTACK
TEMPLATE_LIST_S12XS += S12XS_COSMIC_EE_TEST2_MULTISTACK
TEMPLATE_LIST_S12XS += S12XS_COSMIC_EE_TEST3_MULTISTACK
TEMPLATE_LIST_S12XS += S12XS_COSMIC_EE_TEST4_MULTISTACK
TEMPLATE_LIST_S12XS += S12XS_COSMIC_EE_TEST5_MULTISTACK
TEMPLATE_LIST_S12XS += S12XS_COSMIC_EE_TEST6_MULTISTACK

# TRICORE templates
# -----------------------------------------------------------
TEMPLATE_LIST_TRICORE += tricore_hello
TEMPLATE_LIST_TRICORE += tricore_base_isr


# -----------------------------------------------------------
# -----------------------------------------------------------
# -----------------------------------------------------------
# -----------------------------------------------------------

ifndef TEMPLATE_LIST
TEMPLATE_LIST := $(TEMPLATE_LIST_$(ARCH))
endif

ifndef TEMPLATE_LIST_IGNORE
TEMPLATE_LIST_IGNORE := $(foreach a, $(ARCH_LIST), $(TEMPLATE_LIST_IGNORE_$(a))) $(foreach a, $(filter-out $(ARCH),$(ARCH_LIST)), $(TEMPLATE_LIST_$(a)))
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
	@echo ""
	@echo "    - architecture list: $(ARCH_LIST)"
	@echo 3 - list all available templates
	@echo "      make list"
	@echo 4 - list all templates not tested during this session
	@echo "      make listmissing"
	@echo 5 - list all templates with errors during the current session
	@echo "      make witherrors"
	@echo 6 - produce an XML output compatible with Hudson
	@echo "      make xml ARCH=PIC30"

ECLIPSE_HOME?="C:\\Evidence\\eclipse"
BATCH_DIR?=/cygdrive/c/Evidence/eclipse/evidence

OLD_BATCH_FILES=$(shell if [ -f "$(BATCH_DIR)/template_launcher.bat" ]; \
then echo "true"; \
else echo "false"; \
fi)

ifeq ($(OLD_BATCH_FILES), true)
	BATCH_TEMPLATE=$(BATCH_DIR)/template_launcher.bat
	BATCH_GENERATOR=$(BATCH_DIR)/rtd_launcher.bat
	COMPILE_SCRIPT=./old_compile.sh
else
	BATCH_TEMPLATE=$(BATCH_DIR)/instantiate_template.sh
	BATCH_GENERATOR=$(BATCH_DIR)/generate_code.sh
	COMPILE_SCRIPT=./compile.sh
endif


FLAGS=$(addsuffix /doneflag.txt,$(addprefix regression/,$(TEMPLATE_LIST)))

all: $(FLAGS)

regression/%/doneflag.txt:
	@$(COMPILE_SCRIPT) $* $(ECLIPSE_HOME) $(BATCH_TEMPLATE) $(BATCH_GENERATOR) || true

clean:
	rm -rf regression

# from the list of template.xml present in the current subdirectories (typically the SVN
regression/templatelist:
	@mkdir -p regression
	@find . -iname template.xml | xargs grep ID | sed s/.*ID=\"// | sed s/\"\>// >regression/templatelist

list: regression/templatelist
	@cat regression/templatelist

# from the log of the compilation
regression/current_ok_tests: regression/output.log
	@mkdir -p regression
	@grep -e ': OK$$' regression/output.log | sed "s/: OK//" >regression/current_ok_tests


regression/current_missing_tests: regression/templatelist regression/current_ok_tests
	@mkdir -p regression
	@grep -v -f regression/current_ok_tests regression/templatelist > regression/current_missing_tests

listmissing: regression/current_missing_tests
	@cat regression/current_missing_tests

# difference between the directory listing and the tests which are ok
regression/current_witherrors_tests: regression/current_ok_tests
	@find regression -maxdepth 1 -type d | grep "regression/" | sed "s/regression\\///" | grep -v -f regression/current_ok_tests > regression/current_witherrors_tests

witherrors: regression/current_witherrors_tests
	@cat regression/current_witherrors_tests


#.PHONY because it depends on the architecture selected as parameter
.PHONY: regression/current_ignored_tests

# all ignored tests plus all tests of the other architectures
regression/current_ignored_tests:
	@rm -f regression/current_ignored_tests
	@for x in $(TEMPLATE_LIST_IGNORE); do echo $${x} >> regression/current_ignored_tests; done

ignored: regression/current_ignored_tests
	@cat regression/current_ignored_tests



# regression tests with Hudson
# ----------------------------
# this target replaces the output XML with an XML containing a report of the current build system.

# We do have three kind of targets:
# - A template which is listed in the current architecture, and compiles ok --> XML ok
# - A template which is listed in the current architecture, and does not compile --> XML error
# - A template which is listed in the current architecture, and is marked as IGNORED --> XML ignore
# - A template which is not listed in the current architecture --> XML ignore
# - A template which is not listed at all in any architectures --> XML not ok


.PHONY: xml regression/results.xml
regression/results.xml: regression/templatelist regression/current_ok_tests regression/current_witherrors_tests regression/current_ignored_tests
	@rm regression/results.xml
	@echo "<report name=""regression_tests"" categ=""$(ARCH)"">" >regression/results.xml
	@for t in `cat regression/templatelist`; do echo XML processing $${t}; ./xmltest.sh $${t} >>regression/results.xml; done
	@echo "</report>" >>regression/results.xml

xml: regression/results.xml
