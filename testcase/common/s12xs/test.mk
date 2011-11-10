# ###*B*###
# ERIKA Enterprise - a tiny RTOS for small microcontrollers
# 
# Copyright (C) 2002-2008  Evidence Srl
# 
# This file is part of ERIKA Enterprise.
# 
# ERIKA Enterprise is free software; you can redistribute it
# and/or modify it under the terms of the GNU General Public License
# version 2 as published by the Free Software Foundation, 
# (with a special exception described below).
# 
# Linking this code statically or dynamically with other modules is
# making a combined work based on this code.  Thus, the terms and
# conditions of the GNU General Public License cover the whole
# combination.
# 
# As a special exception, the copyright holders of this library give you
# permission to link this code with independent modules to produce an
# executable, regardless of the license terms of these independent
# modules, and to copy and distribute the resulting executable under
# terms of your choice, provided that you also meet, for each linked
# independent module, the terms and conditions of the license of that
# module.  An independent module is a module which is not derived from
# or based on this library.  If you modify this code, you may extend
# this exception to your version of the code, but you are not
# obligated to do so.  If you do not wish to do so, delete this
# exception statement from your version.
# 
# ERIKA Enterprise is distributed in the hope that it will be
# useful, but WITHOUT ANY WARRANTY; without even the implied warranty
# of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License version 2 for more details.
# 
# You should have received a copy of the GNU General Public License
# version 2 along with ERIKA Enterprise; if not, write to the
# Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
# Boston, MA 02110-1301 USA.
# ###*E*###

#
# Freescale S12XS testcases
#

#
# Global scripts
#


GLOBAL_RTDRUID += \
	( if test -e tmp/s12xs_rtdruid_partial.xml; then \
		cat common/rtdruid_common/script_prologue.xml tmp/s12xs_rtdruid_partial.xml common/rtdruid_common/script_epilogue.xml > tmp/build.xml; \
		cp tmp/build.xml tmp/s12xs_rtdruid_global_build.xml; \
		cd tmp; java -jar $(LAUNCHER_JAR) -application org.eclipse.ant.core.antRunner >rtdruid_s12xs.log 2>&1; \
	fi );

#java -jar "$ECLIPSE_HOME/plugins/$LAUNCHER_JAR" -application org.eclipse.ant.core.antRunner  -Dbuild_numer=`date +"%Y%m%d_%H%M"` $@	

#GLOBAL_RTDRUID += \
#	( if test -e tmp/s12xs_rtdruid_partial.xml; then \
#		cat common/rtdruid_common/script_prologue.xml tmp/s12xs_rtdruid_partial.xml common/rtdruid_common/script_epilogue.xml > tmp/build.xml; \
#		cp tmp/build.xml tmp/s12xs_rtdruid_global_build.xml; \
#		cd tmp; java org.eclipse.core.launcher.Main -application org.eclipse.ant.core.antRunner &>rtdruid_s12xs.log; \
#	fi );

#
# configurations
#

# s12xs
TESTLIST 				+= s12xs
OUTDIR_COMMANDS_s12xs 	= $(OUTDIR_COMMANDS_s12xs_source)
CONF_s12xs             	= $(CONF_s12xs_source)
GLOBAL_CONF 			+=
DIST_s12xs            	=
RTDRUID_s12xs           = $(RTDRUID_s12xs_source)
CLEAN_s12xs           	=
COMPILE_s12xs         	= $(COMPILE_s12xs_source)
DEBUG_s12xs           	= $(DEBUG_s12xs_source)

## s12xs
#TESTLIST 				+= s12xs
#OUTDIR_COMMANDS_s12xs 	= OUTDIR_COMMANDS_s12xs_source
#CONF_s12xs             	= CONF_s12xs_source
#GLOBAL_CONF 			+= $(GLOBAL_CONF_s12xs_source)
#DIST_s12xs            	=
#RTDRUID_s12xs           = RTDRUID_s12xs_source
#CLEAN_s12xs           	=
#COMPILE_s12xs         	= COMPILE_s12xs_source
##DEBUG_s12xs           	=

## s12xs_dist_bin_full
#TESTLIST += s12xs_dist_bin_full
#OUTDIR_COMMANDS_s12xs_dist_bin_full = OUTDIR_COMMANDS_s12xs
#CONF_s12xs_dist_bin_full             = CONF_s12xs_binfull
#GLOBAL_CONF += $(GLOBAL_CONF_s12xs_binfull)
#DIST_s12xs_dist_bin_full            =
#RTDRUID_s12xs_dist_bin_full            = RTDRUID_s12xs_binfull
#CLEAN_s12xs_dist_bin_full           =
#COMPILE_s12xs_dist_bin_full         = COMPILE_s12xs_source
##DEBUG_s12xs_dist_bin_full           = DEBUG_s12xs

# -------------------------------------------------------------------

TMPDIR = $(EEBASE)/testcase/tmp
FILE_LOCK = $(TMPDIR)/s12xs_manual.lock
RTDRUID_GENERATE_LOCK = $(TMPDIR)/rtdruid_generate_lock.lock
LOCKFILE= lockfile -1 -r-1
DIST_LOCK = $(TMPDIR)/dist.lock

# -------------------------------------------------------------------

OUTDIR_COMMANDS_s12xs_source = \
	( cd $@; cp -sf ../*.* .; \
	cp ../../common/s12xs/hs12xsregs.h ../../common/s12xs/vector_s12x.c ../../common/s12xs/crtsx.S ../../common/s12xs/mc9s12xs128_lkf_template .; \
	cp ../../common/s12xs/Full_Chip_Simulation.ini ../../common/s12xs/C_Layout.hwl ../../common/s12xs/SofTec_HCS12.ini .; );

# -------------------------------------------------------------------
# # These are the commands used by s12xs_dist_src

# this simply parses the OIL file and then raises a flag if there is need to generate a source distribution
CONF_s12xs_source = \
	@echo CONF $(OUTDIR_PREFIX)$*; \
	cat $(OUTDIR_PREFIX)$*/appl.oil | gcc -c - -E -P -I$(EEBASE)/pkg $(addprefix -D, $(shell $(DEMUX2) $*)) -D$(thearch) -o - >$(OUTDIR_PREFIX)$*/ee.oil;

# Generate the rt-druid files...
RTDRUID_s12xs_source = \
	@echo RTDRUID $(OUTDIR_PREFIX)$*; \
	echo \<rtdruid.Oil.Configurator inputfile=\"$(call native_path,$(OUTDIR_PREFIX)$*/ee.oil)\" outputdir=\"$(call native_path,$(OUTDIR_PREFIX)$*/Debug)\" /\> >> $(TMPDIR)/s12xs_rtdruid_partial.xml;

# take also a look to GLOBAL_RTDRUID at the top of the file!!!

COMPILE_s12xs_source = \
	+@unset EEBASE; \
	if $(MAKE) $(PARAMETERS) NODEPS=1 -C $(OUTDIR_PREFIX)$*/Debug >$(OUTDIR_PREFIX)$*/compile.log 2>&1; then echo OK $(EXPERIMENT) $(OUTDIR_PREFIX)$* >>$(TMPDIR)/ok.log; else echo ERROR $(EXPERIMENT) $(OUTDIR_PREFIX)$* >>$(TMPDIR)/errors.log; fi

DEBUG_s12xs_source = \
	cp s12xs/testcase.cmd $(OUTDIR_PREFIX)$*; \
	$(LOCKFILE) $(FILE_LOCK); \
		echo "                                     " >> $(TMPDIR)/s12xs_jobs.cmd; \
		echo "cd `cygpath -w $(OUTDIR_PREFIX)$*`" >> $(TMPDIR)/s12xs_jobs.cmd; \
		echo "cf testcase.cmd                      " >> $(TMPDIR)/s12xs_jobs.cmd; \
		cp -u s12xs/s12xs.cmd $(TMPDIR)/s12xs.cmd; \
	rm -f $(FILE_LOCK); \


# cf script\modistarc_task_1_script.txt
#DEBUG_s12xs_source = \
#	cp s12xs/testcase.cmd $(OUTDIR_PREFIX)$*; \
#	$(LOCKFILE) $(FILE_LOCK); \
#		echo "cf `cygpath -w $(OUTDIR_PREFIX)$*`" >> $(TMPDIR)/s12xs_jobs.cmd; \
#		cp -u s12xs/s12xs.cmd $(TMPDIR)/s12xs.cmd; \
#	rm -f $(FILE_LOCK); \


# -------------------------------------------------------------------

# These are the commands used by s12xs_dist_bin_full

#CONF_s12xs_binfull = \
#	@echo CONF $(OUTDIR_PREFIX)$*; \
#	cat $(OUTDIR_PREFIX)$*/appl.oil | gcc -c - -E -P -I$(EEBASE)/pkg $(addprefix -D, $(shell $(DEMUX2) $*)) -D$(thearch) -o - >$(OUTDIR_PREFIX)$*/ee.oil; \
#	echo \<rtdruid.Oil.DistributionBuilder inputfile=\"`cygpath -m $(OUTDIR_PREFIX)$*/ee.oil`\" outputFile=\"`cygpath -m $(TMPDIR)/bindistrfull_partial.mk`\" DistributionName=\"$(subst /,,$(EXPERIMENT))_$*\" DistributionType=\"full\"/\> >> $(TMPDIR)/s12xs_ant_partial.xml;


#GLOBAL_CONF_s12xs_binfull = \
#	( if test s12xs_dist_bin_full = $(ARCH); then \
#		cat common/rtdruid_common/script_prologue.xml tmp/s12xs_ant_partial.xml common/rtdruid_common/script_epilogue.xml > tmp/build.xml; \
#		cp tmp/build.xml tmp/s12xs_ant_global_build.xml; \
#		cd tmp; java org.eclipse.core.launcher.Main -application org.eclipse.ant.core.antRunner; cd ..; \
#		echo "ALL_DISTRIBUTIONS += RTDRUID" > tmp/s12xs_bindistrfull.mk; \
#		cat tmp/bindistrfull_partial.mk >> tmp/s12xs_bindistrfull.mk; \
#		false; \
#		make -C ${EEBASE}/dist/binary DISTFILE=${EEBASE}/testcase/tmp/s12xs_bindistrfull.mk DIST=RTDRUID s12xs_MOVE=Y; \
#	fi );

#RTDRUID_s12xs_binfull = \
#	@echo RTDRUID $(OUTDIR_PREFIX)$*; \
#	echo \<rtdruid.Oil.Configurator inputfile=\"`cygpath -m $(OUTDIR_PREFIX)$*/ee.oil`\" outputdir=\"`cygpath -m $(OUTDIR_PREFIX)$*`\" Signatures_file=\"`cygpath -m $(EE_s12xs_IDE_BASE)/../../components/evidence_ee/ee/signature/signature.xml`\" /\> >> $(TMPDIR)/s12xs_rtdruid_partial.xml;
##binDistrSignatures_file=\"`cygpath -m $(EE_s12xs_IDE_BASE)/../../components/evidence_ee/ee/signature/signature.xml`\"

# take also a look to GLOBAL_RTDRUID at the top of the file!

# -------------------------------------------------------------------

# # These are the commands used by s12xs_dist_bin_lim

# CONF_s12xs_binlim = \
# 	@echo CONF $(OUTDIR_PREFIX)$*; \
# 	cat $(OUTDIR_PREFIX)$*/appl.oil | gcc -c - -E -P -I$(EEBASE)/pkg $(addprefix -D, $(shell $(DEMUX2) $*)) -D$(thearch) -o - >$(OUTDIR_PREFIX)$*/ee.oil; \
# 	echo \<rtdruid.Oil.Configurator inputfile=\"$(OUTDIR_PREFIX)$*/ee.oil\" outputdir=\"$(OUTDIR_PREFIX)$*\" bindistrlimited_file=\"bindistrlimited.mk\" /\> >> $(TMPDIR)/rtdruid_ant_partial.xml;

