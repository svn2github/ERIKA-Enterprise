# This is the makefile responsible for creating EE's binary distributions.

include config/arch.mk
include config/conf.mk
include config/post_scripts.mk
# Banner support is needed?
#include ../banner/banner.mk

ifdef DISTFILE
include $(DISTFILE)
endif

ifndef DIST
help::
endif

.PHONY : all clean cleanall help create

all: create
	@echo $(DIST) finished!

clean:
	rm -rf out ee_* *.zip *.tgz *.tbz2 $(POST_SCRIPTS_CLEAN)

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
	@echo
#	@echo to add a BANNER, use BANNER=bannername
#	@echo possible BANNERs: $(ALL_BANNERS)
#	@echo
	@echo To generate distributions, I typically use:
	@echo make DIST=NIOS2_ALL NIOS2_MOVE=Y
	@echo make DIST=NIOS2_TESTCASE NIOS2_MOVE=Y
	@echo
	@echo make DIST=EEFLEX EE_MOVE=Y
	@echo make DIST=EE3ARCH EE_MOVE=Y
	@echo make DIST=EE3ARCHD EE_MOVE=Y
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
	@make --no-print-directory -C . make_distribdir

# Step 3 - Post-distribution scrpts
	@echo
	@echo STEP 3 Post-Distribution Scripts
	@$(post_script_ALWAYS)
	$(foreach x, $(ALLOPTIONS), $(post_script_$(x)) )

# Step 4 - Zipping everything
ifndef NOSTEP4
	@echo
	@echo STEP 4 Zipping ee_$(DIST)
	@if !(which zip >/dev/null); then zip -q -r ee_$(DIST).zip ee_$(DIST); fi;
	@tar czf ee_$(DIST).tgz ee_$(DIST)
	@tar cjf ee_$(DIST).tbz2 ee_$(DIST)
else
	@echo
	@echo STEP 4 skipped.
endif

include config/distrib.mk
