#
# compile.in
#

# Step 3

# This file is included by the makedist makefile and specifies the
# actions that have to be taken to generate a given library for a given
# architecture.

#make_libcompile_evaluator7t_%: ee_$(DIST)/lib/libee_%.a
#	@echo Library ee_$(DIST)/lib/libee_$*.a is up2date.
#	cp ee_$(DIST)/lib/libee_$*.a ee_$(DIST)/lib/libee_$*.a2

#ee_$(DIST)/lib/libee_%.a: ee_$(DIST)/lib config/conf.in template/eecfg.h 




LIBCOMPILE_ALLCONF= $(addprefix libcompile_conf_, $($(DIST)))









#.PHONY: $(addprefix libcompile_evaluator7t_, $($(DIST)))

make_libcompile: $(LIBCOMPILE_ALLCONF)
	@echo Libraries created. $(LIBCOMPILE_ALLCONF)






define COMPILE_template

.PHONY: libcompile_conf_$(1)
libcompile_conf_$(1):
	@if (test X$$(findstring __EVALUATOR7T__,$$($(1))) = X__EVALUATOR7T__); then (echo CONF $(1) using __EVALUATOR7T__; make --no-print-directory -C . make_libcompile_evaluator7t_$(1)); fi
	@if (test X$$(findstring __NIOS2__,$$($(1))) = X__NIOS2__); then (echo CONF $(1) using __NIOS2__; make --no-print-directory -C . make_libcompile_nios2_$(1)); fi
	@if (test X$$(findstring __PIC30__,$$($(1))) = X__PIC30__); then (echo CONF $(1) using __PIC30__; make --no-print-directory -C . make_libcompile_pic30_$(1)); fi
	@if (test X$$(findstring __AVR5__,$$($(1))) = X__AVR5__); then (echo CONF $(1) using __AVR5__; make --no-print-directory -C . make_libcompile_avr5_$(1)); fi
endef

$(foreach c,$($(DIST)),$(eval $(call COMPILE_template,$(c))))



# see also eecfg.mk
# ALL_SYMBOLS contains the list of all the variables that must have a specific value in the eecfg.h
# $(1) is the output file
# $(2) is the configuration name
# $(s) contains the name of the variable (e.g., MAX_TASK)
# $(2)_$(s) contains the name of the environment variable that should specify the variable value (in conf.in; e.g., MYDIST_MYCONF_MAX_TASK)
# $($(2)_$(s)) is the value assigned to the particular variable in a particular configuration in a particular distribution (see conf.in)
# Please note that the EE_MAX_RESOURCE, and EE_CURRENT_CPU checks are disabled!!!
generate_allsymbols_eecfg = \
	$(foreach s,$(ALL_SYMBOLS_MULTICORE),\
		(if test $($(2)_$(s)); \
			then (echo \\\#define EE_$(s) $($(2)_$(s))       $(1)); \
		elif (test $(findstring __BIN_DISTR_LIMITED__, $($(2)))) && (test EE_$(s) != EE_CURRENT_CPU) && (test EE_$(s) != EE_MAX_RESOURCE) && (test EE_$(s) != EE_ALTERA_MUTEX_BASE); \
			then ( echo ERROR\!\!\! $(2)_$(s) not defined\!; false ); \
			else (echo \\\#ifdef __EECFG_THIS_IS_ASSEMBLER__ $(1); \
                              echo .extern EE_$(s)                       $(1); \
                              echo \\\#else                              $(1); \
                              echo extern const unsigned int EE_$(s)\;   $(1); \
                              echo \\\#endif                             $(1)); \
		fi) && \
	) true



make_libcompile_evaluator7t_%:             \
			ee_$(DIST)/lib  \
			config/conf.mk
	@mkdir -p out
	@echo Creating makefile...
	@echo \# Custom makefile created by makedist script > out/makefile
	@echo EEOPT=$($*) >> out/makefile
	@echo include $$\(EEBASE\)/pkg/cfg/rules.mk >> out/makefile

	@echo Creating custom eecfg.h...
	@echo \/\* eecfg.h created by compile.mk \*\/ >out/eecfg.h

# generates all the extern symbols in eecfg.h
	$(call generate_allsymbols_eecfg,>> out/eecfg.h,$*)

	@echo Compiling $*...
	@make -C out out/libee.a

	@echo Copying library...
	@cp out/out/libee.a ee_$(DIST)/lib/libee_$*.a
	@echo Removing temporary out directory...
	@rm -rf out
	@echo Library ee_$(DIST)/lib/libee_$*.a is up2date.



#
#
# Altera NIOS2 scripts
#
#


# To be able to compile a binary distribution for NIOS2, I need to use
# the library makefiles provided by altera. In particular, I need the
# library makefiles that have been modified by Evidence that are
# currently distributed with source distributions. Since in general I
# do not know what is the source distribution that is currently
# installed in the system, the thing that I have to do is the
# following:
#
# - move away an eventual installation that is present inside the
#   altera directories
# - compile a new source distribution
# - install it
# - compile the new binary distribution
# - remove the source distribution just moved and put back the old one

make_libcompile_nios2_%:             \
			ee_$(DIST)/lib  \
			config/conf.mk
# install my source distribution to be able to compile the binary distribution
ifdef NIOS2_MOVE
	rm -rf /cygdrive/c/altera/80/nios2eds/components/evidence_ee
else
	if (test -e  /cygdrive/c/altera/80/nios2eds/components/evidence_ee); then mv /cygdrive/c/altera/80/nios2eds/components/evidence_ee evidence_ee_backup; fi;
endif
	make -C ../source clean
	make -C ../source DIST=NIOS2_FROMBINDIST NIOS2_MOVE=Y all
#this is no more needed because of NIOS2_MOVE- mv ../source/evidence_ee /cygdrive/c/altera/80/nios2eds/components/evidence_ee
# now starts the typical script
	@mkdir -p out
	@echo Creating makefile...
	@echo \# Custom makefile created by makedist script > out/makefile
	@echo EEOPT=$($*) >> out/makefile
	@echo include $$\(EEBASE\)/pkg/cfg/rules.mk >> out/makefile

	@echo Creating custom eecfg.h...
	@echo \/\* eecfg.h created by compile.mk \*\/ >out/eecfg.h

# generates all the extern symbols in eecfg.h
	$(call generate_allsymbols_eecfg,>> out/eecfg.h,$*)

# generates the defines that are going into EEOPT
	$(foreach s,$($*), \
		echo \#ifndef $(s) >> out/eecfg.h; \
		echo \#define $(s) >> out/eecfg.h; \
		echo \#endif       >> out/eecfg.h; \
	)
	echo \#define SYSTEM_BUS_WIDTH 32  >> out/eecfg.h

	@echo Compiling $*...
	@make -C out all

	@echo Copying library...
	@cp out/libee.a ee_$(DIST)/lib/libee_$*.a

	@echo Stripping library...
	@nios2-elf-strip -x ee_$(DIST)/lib/libee_$*.a

	@echo Removing temporary out directory...
	@rm -rf out
	@echo Library ee_$(DIST)/lib/libee_$*.a is up2date.

	@echo Creating a fake component.mk
	@mkdir -p ee_$(DIST)/pkg/cpu/nios2/cfg
	echo \# Custom component.mk created by makedist script > ee_$(DIST)/pkg/cpu/nios2/cfg/component.mk
	echo CFLAGS += -I$$\(SOPC_KIT_NIOS2\)/components/evidence_ee/ee/pkg >> ee_$(DIST)/pkg/cpu/nios2/cfg/component.mk

# putting the source distribution back at its place
ifndef NIOS2_MOVE
	rm -rf /cygdrive/c/altera/80/nios2eds/components/evidence_ee_NIOS2_FROMBINDIST
	mv /cygdrive/c/altera/80/nios2eds/components/evidence_ee /cygdrive/c/altera/80/nios2eds/components/evidence_ee_NIOS2_FROMBINDIST
	if (test -e evidence_ee_backup); then rm -rf /cygdrive/c/altera/nios2/components/evidence_ee; mv evidence_ee_backup /cygdrive/c/altera/80/nios2eds/components/evidence_ee; fi;
endif


# GRRR: Nios2 had an old make executable!!! (we need at least 3.80)
ifeq ($(findstring __NIOS2__,$(ALLOPTIONS)) , __NIOS2__)
libcompile_conf_%:
	@if (test X$(findstring __NIOS2__,$($*)) = X__NIOS2__); then (echo CONF $* using __NIOS2__; make --no-print-directory -C . make_libcompile_nios2_$*); fi
endif


#
#
# Microchip DSPIC scripts
#
#

make_libcompile_pic30_%:             \
			ee_$(DIST)/lib  \
			config/conf.mk
# install my source distribution to be able to compile the binary distribution
	make -C ../source clean
	make -C ../source DIST=PIC30_FROMBINDIST PIC30_MOVE=Y all
# now starts the typical script
	@mkdir -p out
	@echo Creating makefile...
	@echo \# Custom makefile created by makedist script > out/makefile
	@echo EEOPT=$($*) >> out/makefile
	@echo ECLIPSEBASE = $(shell cygpath "c:\Programmi\Evidence\eclipse") >> out/makefile
	@echo EEBASE = $$\(ECLIPSEBASE\)/../pic30/ee >> out/makefile
	@echo APPBASE = .. >> out/makefile
	@echo OUTBASE = out >> out/makefile
	@echo PIC30_LINKERSCRIPT := p30f2010.gld >> out/makefile
	@echo include $$\(EEBASE\)/pkg/cfg/rules.mk >> out/makefile 

	@echo Creating custom eecfg.h...
	@echo \/\* eecfg.h created by compile.mk \*\/ >out/eecfg.h

# generates all the extern symbols in eecfg.h
	$(call generate_allsymbols_eecfg,>> out/eecfg.h,$*)

# generates the defines that are going into EEOPT
	$(foreach s,$($*), \
		echo \#ifndef $(s) >> out/eecfg.h; \
		echo \#define $(s) >> out/eecfg.h; \
		echo \#endif       >> out/eecfg.h; \
	)

	@echo Compiling $*...
	@make -C out libee.a

	@echo Copying library...
	@cp out/libee.a ee_$(DIST)/lib/libee_$*.a

	@echo Stripping library...
	@/cygdrive/c/Programmi/Microchip/MPLAB\ ASM30\ Suite/bin/pic30-elf-strip -x ee_$(DIST)/lib/libee_$*.a

	@echo Removing temporary out directory...
	@rm -rf out
	@echo Library ee_$(DIST)/lib/libee_$*.a is up2date.


make_libcompile_avr5_%:             \
			ee_$(DIST)/lib  \
			config/conf.mk
# install my source distribution to be able to compile the binary distribution
	make -C ../source clean
	make -C ../source DIST=AVR5_FROMBINDIST AVR5_MOVE=Y all
# now starts the typical script
	@mkdir -p out
	@echo Creating makefile...
	@echo \# Custom makefile created by makedist script > out/makefile
	@echo EEOPT=$($*) >> out/makefile
	@echo ECLIPSEBASE = $(shell cygpath "c:\Programmi\Evidence\eclipse") >> out/makefile
	@echo EEBASE = $$\(ECLIPSEBASE\)/../avr5/ee >> out/makefile
	@echo APPBASE = .. >> out/makefile
	@echo OUTBASE = out >> out/makefile
	@echo include $$\(EEBASE\)/pkg/cfg/rules.mk >> out/makefile 

	@echo Creating custom eecfg.h...
	@echo \/\* eecfg.h created by compile.mk \*\/ >out/eecfg.h

# generates all the extern symbols in eecfg.h
	$(call generate_allsymbols_eecfg,>> out/eecfg.h,$*)

# generates the defines that are going into EEOPT
	$(foreach s,$($*), \
		echo \#ifndef $(s) >> out/eecfg.h; \
		echo \#define $(s) >> out/eecfg.h; \
		echo \#endif       >> out/eecfg.h; \
	)

	@echo Compiling $*...
	@make -C out libee.a

	@echo Copying library...
	@cp out/libee.a ee_$(DIST)/lib/libee_$*.a


	@echo Removing temporary out directory...
	@rm -rf out
	@echo Library ee_$(DIST)/lib/libee_$*.a is up2date.


