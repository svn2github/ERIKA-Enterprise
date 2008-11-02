# This file contains the post scripts that must be executed after
# having prepared the source distribution...

# post_script_ALWAYS is the name to use if you want to always execute
# something as post-script.

POST_SCRIPTS_CLEAN=evidence_ee evidence_ee_tutorials

ifdef NOCVS
post_script_ALWAYS += \
	echo Deleting CVS directories!; \
	find ee_$(DIST)/ -type d -iname CVS | xargs rm -rf;
endif

post_script_ALWAYS += \
	echo cp VERSION!; \
	cp ../../VERSION ee_$(DIST);

# --------------------------------------------------------


post_script___NIOS2__ += \
	mkdir -p evidence_ee/build evidence_ee/bin evidence_ee/ee evidence_ee/HAL/src evidence_ee/examples; \
	mv ee_$(DIST)/pkg/cpu/nios2/build/* evidence_ee/build; \
	mv ee_$(DIST)/pkg/cpu/nios2/bin/* evidence_ee/bin; \
	mv ee_$(DIST)/pkg/cpu/nios2/cfg/* evidence_ee/HAL/src; \
	mv ee_$(DIST)/examples/* evidence_ee/examples; \
	rmdir ee_$(DIST)/examples; \
	mv ee_$(DIST)/* evidence_ee/ee; \
	if !(which zip >/dev/null); then zip -r evidence_ee.zip evidence_ee; fi;

ifdef NIOS2_MOVE
#ifndef EE_DEST_DIR
	EE_DEST_DIR = /cygdrive/c/altera/80/nios2eds/components
#endif
post_script___NIOS2__ += \
	echo Moving files!; \
	rm -rf $(EE_DEST_DIR)/evidence_ee; \
	mv evidence_ee $(EE_DEST_DIR)/evidence_ee
endif

# --------------------------------------------------------

ifdef AVR5_MOVE
NOSTEP4=Y

ifndef EE_DEST_DIR
	EE_DEST_DIR = /cygdrive/c/Programmi/Evidence
endif
post_script___AVR5__ += \
	echo Moving files!; \
	rm -rf $(EE_DEST_DIR)/avr5/ee; \
	mv ee_$(DIST) $(EE_DEST_DIR)/avr5/ee;
endif

# --------------------------------------------------------

ifdef E7T_MOVE
NOSTEP4=Y

ifndef EE_DEST_DIR
	EE_DEST_DIR = /cygdrive/c/Programmi/Evidence
endif
post_script___EVALUATOR7T__ += \
	echo Moving files!; \
	rm -rf $(EE_DEST_DIR)/arm7/ee; \
	mv ee_$(DIST) $(EE_DEST_DIR)/arm7/ee;
endif

# --------------------------------------------------------

ifdef COBRA_MOVE
NOSTEP4=Y

ifndef EE_DEST_DIR
	EE_DEST_DIR = /cygdrive/c/Programmi/Evidence
endif
post_script___COBRA_ICD30__ += \
	echo Moving files!; \
	rm -rf $(EE_DEST_DIR)/arm7/ee; \
	mv ee_$(DIST) $(EE_DEST_DIR)/arm7/ee;
endif

# --------------------------------------------------------

ifdef EE_MOVE
NOSTEP4=Y

ifndef EE_DEST_DIR
	EE_DEST_DIR = /cygdrive/c/Evidence/Evidence
endif

post_script_ALWAYS +=						\
	echo Moving files!;					\
	rm -rf $(EE_DEST_DIR)/ee;				\
	rm -rf $(EE_DEST_DIR)/examples;				\
	cp -a ee_$(DIST) $(EE_DEST_DIR)/ee;			\
	if test -e $(EE_DEST_DIR)/ee/examples; then		\
		mv $(EE_DEST_DIR)/ee/examples $(EE_DEST_DIR);	\
	fi;
endif

# --------------------------------------------------------
