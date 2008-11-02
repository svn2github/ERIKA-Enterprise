# This is the makefile responsible for creating EE's binary distributions.

ifdef DISTFILE
include $(DISTFILE)
endif

include config/arch.mk
include config/conf.mk
include config/post_scripts.mk
include ../banner/banner.mk

ifndef DIST
help::
endif

.PHONY : all clean cleanall help create

all: create
	@echo $(DIST) finished!

clean:
	rm -rf out ee_* $(POST_SCRIPTS_CLEAN)

cleanall: clean
	rm -rf *.tmp

help::
	@echo Distribution makefile
	@echo
	@echo usage: make DIST=distname
	@echo
	@echo possible DISTributions:
	@echo
	@for x in $(ALL_DISTRIBUTIONS); do echo make DIST=$${x}; done
	@echo
	@echo for NIOS2, use NIOS2_MOVE=Y to directly update the Altera directory
	@echo
	@echo to add a BANNER, use BANNER=bannername
	@echo possible BANNERs: $(ALL_BANNERS)
	@echo
	@echo To generate binary distributions, I typically use:
	@echo make DIST=NIOS2_LIMITED NIOS2_MOVE=Y BANNER=Y
	@echo make DIST=NIOS2_LIMITED_ALTERA NIOS2_MOVE=Y BANNER=Y
	@echo make DIST=NIOS2_FULL NIOS2_MOVE=Y
	@echo make DIST=NIOS2_FULL_TESTCASE NIOS2_MOVE=Y
	@echo make DIST=PIC30_LIMITED PIC30_MOVE=Y BANNER=Y
	@echo make DIST=AVR5_LIMITED AVR5_MOVE=Y BANNER=Y
	


	@echo --\> looking for NIOS2 Examples in the binary distributions? these examples are generated from the source distribution directory!
	@echo
	@echo for more help please read readme.txt
	@echo


#
# Steps needed to make the binary distribution
#

create:
# Step 1 - Understanding which are the targets to be done
	@echo
	@echo STEP 1 Printing Parameters:
	@echo Building Distribution: $(DIST)
	@echo Configurations: $($(DIST))
	@echo ALLOPTIONS: $(ALLOPTIONS)

# Step 2 - Creation of the distribution directory
	@echo
	@echo STEP 2 Creating distribution directory ee_$(DIST)
	@make -j 1 --no-print-directory -C . make_distribdir
	@echo removing CVS directories...
	@rm -rf `find ee_$(DIST) -iname CVS`

# Step 3 - Library creation
	@echo
	@echo STEP 3 Compiling the libraries
	@make -j 1 --no-print-directory -C . make_libcompile

# Step 4 - eecfg.h generation
	@echo
	@echo STEP 4 eecfg.h generation
	@make -j 1 --no-print-directory -C . make_generatecfg

# Step 5 - makefile generation
	@echo
	@echo STEP 5 makefile generation
	@make -j 1 --no-print-directory -C . make_makefile

# Step 6 - signature generation
	@echo
	@echo STEP 6 signature generation
	@make -j 1 --no-print-directory -C . make_signature

# Step 7 - Post-distribution scrpts
	@echo
	@echo STEP 7 Post-Distribution Scripts
	$(foreach x, $(ALLOPTIONS), $(post_script_$(x)) )

# Step 8 - Zipping everything
	@echo
	@echo STEP 8 Zipping ee_$(DIST)
	@if !(which zip); then zip -q -r ee_$(DIST).zip ee_$(DIST); fi;
	@tar czf ee_$(DIST).tgz ee_$(DIST)
	@tar cjf ee_$(DIST).tbz2 ee_$(DIST)

# Step 2
include config/distrib.mk
# Step 3
include config/compile.mk
# Step 4
include config/eecfg.mk
# Step 5
include config/make_makefile.mk
# Step 6
include config/make_signature.mk


