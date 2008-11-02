# This file contains the post scripts that must be executed after
# having prepared the binary distribution...

POST_SCRIPTS_CLEAN=evidence_ee

# The cfg directory does not exist in binary distributions for nios
# because component.mk is used only by source distributions
# binary distributions creates component.mk automatically

post_script___NIOS2__ = \
	mkdir -p evidence_ee/build evidence_ee/ee evidence_ee/HAL/src; \
	mv ee_$(DIST)/pkg/cpu/nios2/build/* evidence_ee/build; \
	mv ee_$(DIST)/pkg/cpu/nios2/cfg/* evidence_ee/HAL/src; \
	rm -rf ee_$(DIST)/makefile; \
	rm -rf ee_$(DIST)/pkg/cfg; \
	rm -rf ee_$(DIST)/pkg/cpu/nios2/build; \
	rm -rf ee_$(DIST)/pkg/cpu/nios2/cfg; \
	mv ee_$(DIST)/* evidence_ee/ee; \
	cd evidence_ee; \
	find . -iname *.h   | xargs unix2dos; \
	find . -iname *.c   | xargs unix2dos; \
	find . -iname *.oil | xargs unix2dos; \
	find . -iname *.txt | xargs unix2dos; \
	find . -iname *.mk  | xargs unix2dos; \
	cd ..; \
	if !(which zip); then zip -r evidence_ee.zip evidence_ee; fi;

ifdef NIOS2_MOVE
ifndef EE_DEST_DIR
	EE_DEST_DIR = /cygdrive/c/altera/80/nios2eds/components
endif
post_script___NIOS2__ += \
	rm -rf $(EE_DEST_DIR)/evidence_ee; \
	mv evidence_ee $(EE_DEST_DIR)/evidence_ee
endif

ifdef PIC30_MOVE
ifndef EE_DEST_DIR
	EE_DEST_DIR = /cygdrive/c/Programmi/Evidence
endif
post_script___PIC30__ += \
	echo Moving files!; \
	rm -rf $(EE_DEST_DIR)/pic30/ee; \
	mv ee_$(DIST) $(EE_DEST_DIR)/pic30/ee; \
	mkdir -p ee_$(DIST)
endif


ifdef AVR5_MOVE
ifndef EE_DEST_DIR
	EE_DEST_DIR = /cygdrive/c/Programmi/Evidence
endif
post_script___AVR5__ += \
	echo Moving files!; \
	rm -rf $(EE_DEST_DIR)/avr5/ee; \
	mv ee_$(DIST) $(EE_DEST_DIR)/avr5/ee; \
	mkdir -p ee_$(DIST)
endif

