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
# Altera Nios 2 testcases
#

#
# Global scripts
#

GLOBAL_RTDRUID += \
	( if test -e tmp/nios2_rtdruid_partial.xml; then \
		cat common/rtdruid_common/script_prologue.xml tmp/nios2_rtdruid_partial.xml common/rtdruid_common/script_epilogue.xml > tmp/build.xml; \
		cp tmp/build.xml tmp/nios2_rtdruid_global_build.xml; \
		cd tmp; java org.eclipse.core.launcher.Main -application org.eclipse.ant.core.antRunner; \
	fi );




#
# configurations
#


# nios2_dist_src
TESTLIST += nios2_dist_src
OUTDIR_COMMANDS_nios2_dist_src = $(OUTDIR_COMMANDS_nios2)
CONF_nios2_dist_src             = $(CONF_nios2_source)
GLOBAL_CONF += $(GLOBAL_CONF_nios2_source)
DIST_nios2_dist_src            =
RTDRUID_nios2_dist_src            = $(RTDRUID_nios2_source)
CLEAN_nios2_dist_src           =
COMPILE_nios2_dist_src         = $(COMPILE_nios2_source)
DEBUG_nios2_dist_src           = $(DEBUG_nios2)

# nios2_dist_bin_full
TESTLIST += nios2_dist_bin_full
OUTDIR_COMMANDS_nios2_dist_bin_full = $(OUTDIR_COMMANDS_nios2)
CONF_nios2_dist_bin_full             = $(CONF_nios2_binfull)
GLOBAL_CONF += $(GLOBAL_CONF_nios2_binfull)
DIST_nios2_dist_bin_full            =
#DIST_nios2_dist_bin_full            = DIST_nios2_binfull
RTDRUID_nios2_dist_bin_full            = $(RTDRUID_nios2_binfull)
CLEAN_nios2_dist_bin_full           =
COMPILE_nios2_dist_bin_full         = $(COMPILE_nios2_source)
DEBUG_nios2_dist_bin_full           =
DEBUG_nios2_dist_bin_full           = $(DEBUG_nios2)

# # nios2_dist_bin_lim
# TESTLIST += nios2_dist_bin_lim
# OUTDIR_COMMANDS_nios2_dist_bin_lim = OUTDIR_COMMANDS_nios2
# CONF_nios2_dist_bin_lim             = CONF_nios2_binlim
# DIST_nios2_dist_bin_lim            = DIST_nios2_binlim
# CLEAN_nios2_dist_bin_lim           =
# COMPILE_nios2_dist_bin_lim         = COMPILE_nios2_source
# DEBUG_nios2_dist_bin_lim           = DEBUG_nios2

# nios2_dist_trace
TESTLIST += nios2_dist_trace
OUTDIR_COMMANDS_nios2_dist_trace = $(OUTDIR_COMMANDS_nios2)
CONF_nios2_dist_trace             = $(CONF_nios2_source)
# No GLOBAL_CONF, reusing the one of nios2_dist_src
DIST_nios2_dist_trace            =
RTDRUID_nios2_dist_trace            = $(RTDRUID_nios2_source)
CLEAN_nios2_dist_trace           =
COMPILE_nios2_dist_trace         = $(COMPILE_nios2_source)
DEBUG_nios2_dist_trace           = $(DEBUG_nios2_trace)



# -------------------------------------------------------------------


TMPDIR = $(EEBASE)/testcase/tmp
FILE_LOCK = $(TMPDIR)/nios2_manual.lock
RTDRUID_GENERATE_LOCK = $(TMPDIR)/rtdruid_generate_lock.lock
LOCKFILE= lockfile -1 -r-1
DIST_LOCK = $(TMPDIR)/dist.lock


# -------------------------------------------------------------------

# These are the commands used by nios2_rtdruid

OUTDIR_COMMANDS_nios2 = cd $@; cp -sf ../*.* .

# This piece of commented code is to put an if to the generation code
# in ARCH_MK_CONF

#if test ! -e $(OUTDIR_PREFIX)$*/ee.oil; then \
#fi;\
#if test -n `grep $(OUTDIR_PREFIX)$*/ee.oil $(TMPDIR)/rtdruid_ant_partial.xml`; then \
#fi;

# CONF_nios2 = \
# 	@echo CONF $(OUTDIR_PREFIX)$*; \
# 	cat $(OUTDIR_PREFIX)$*/appl.oil | gcc -c - -E -P -I$(EEBASE)/pkg $(addprefix -D, $(shell $(DEMUX2) $*)) -D$(thearch) -o - >$(OUTDIR_PREFIX)$*/ee.oil; \
# 	echo \<rtdruid.Oil.Configurator inputfile=\"$(OUTDIR_PREFIX)$*/ee.oil\" outputdir=\"$(OUTDIR_PREFIX)$*\"/\> >> $(TMPDIR)/rtdruid_ant_partial.xml;

# COMPILE_nios2 = +@$(MAKE) $(PARAMETERS) NODEPS=1 -C $(OUTDIR_PREFIX)$*



DEBUG_nios2 = \
	cp nios2/testcase.cmm $(OUTDIR_PREFIX)$*/Debug; \
	$(LOCKFILE) $(FILE_LOCK); \
		echo chdir `cygpath -w $(OUTDIR_PREFIX)$*/Debug` >> $(TMPDIR)/t32_jobs.cmm; \
		echo area.select Messages >> $(TMPDIR)/t32_jobs.cmm; \
		echo print >> $(TMPDIR)/t32_jobs.cmm; \
		echo print \"`cygpath -w $(OUTDIR_PREFIX)$*/Debug`\" >> $(TMPDIR)/t32_jobs.cmm; \
		echo area.select A000 >> $(TMPDIR)/t32_jobs.cmm; \
		echo do testcase.cmm >> $(TMPDIR)/t32_jobs.cmm; \
		cp -u nios2/t32.cmm $(TMPDIR)/t32.cmm; \
	rm -f $(FILE_LOCK); \


DEBUG_nios2_trace = \
	cp nios2/testcase_trace.cmm $(OUTDIR_PREFIX)$*/Debug; \
	$(LOCKFILE) $(FILE_LOCK); \
		echo chdir `cygpath -w $(OUTDIR_PREFIX)$*/Debug` >> $(TMPDIR)/t32_jobs.cmm; \
		echo area.select Messages >> $(TMPDIR)/t32_jobs.cmm; \
		echo print >> $(TMPDIR)/t32_jobs.cmm; \
		echo print \"`cygpath -w $(OUTDIR_PREFIX)$*/Debug`\" >> $(TMPDIR)/t32_jobs.cmm; \
		echo area.select A000 >> $(TMPDIR)/t32_jobs.cmm; \
		echo do testcase_trace.cmm >> $(TMPDIR)/t32_jobs.cmm; \
		cp -u nios2/t32.cmm $(TMPDIR)/t32.cmm; \
	rm -f $(FILE_LOCK); \



# -------------------------------------------------------------------


# # These are the commands used by nios2_dist_src

# this simply parses the OIL file and then raises a flag if there is need to generate a source distribution
CONF_nios2_source = \
	@echo CONF $(OUTDIR_PREFIX)$*; \
	cat $(OUTDIR_PREFIX)$*/appl.oil | gcc -c - -E -P -I$(EEBASE)/pkg $(addprefix -D, $(shell $(DEMUX2) $*)) -D$(thearch) -o - >$(OUTDIR_PREFIX)$*/ee.oil; \
	touch $(TMPDIR)/nios2_dist_src_buildsourcedistribution.flg;

# if the flag has been raised, generate the source distribution
GLOBAL_CONF_nios2_source = \
	( if test -e tmp/nios2_dist_src_buildsourcedistribution.flg; then \
		make -C ${EEBASE}/dist/source DIST=NIOS2_TESTCASE NIOS2_MOVE=Y; \
	fi );

#COMPILE_nios2_source = +$(MAKE) $(PARAMETERS) NODEPS=1 EEBASE=$(OUTDIR_PREFIX)$*/ee_RTDRUID -C $(OUTDIR_PREFIX)$*

# workaround for a bug in RT-Druid that does not generate the results in the right directory
# moreover the make version in Nios II is a 3.80. To call it we use the script mymake.sh
# we cannot use make 3.81 shipped with cygwin because it does not support windows pathnames in the directory name
# we cannot use make380 in cygwin because of the CR-LF problem
# I also had to make a symbolic link in /home in the nios2 cygwin installation
COMPILE_nios2_source = mkdir $(OUTDIR_PREFIX)$*/Debug; mv $(OUTDIR_PREFIX)$*/makefile $(OUTDIR_PREFIX)$*/Debug; mv $(OUTDIR_PREFIX)$*/default_cpu $(OUTDIR_PREFIX)$*/Debug; mv $(OUTDIR_PREFIX)$*/common.mk $(OUTDIR_PREFIX)$*/Debug; $(EEBASE)/testcase/common/nios2/mymake.sh $(PARAMETERS) NODEPS=1 EEBASE=$(OUTDIR_PREFIX)$*/ee_RTDRUID -C $(OUTDIR_PREFIX)$*/Debug

RTDRUID_nios2_source = \
	@echo RTDRUID $(OUTDIR_PREFIX)$*; \
	echo \<rtdruid.Oil.Configurator inputfile=\"`cygpath -m $(OUTDIR_PREFIX)$*/ee.oil`\" outputdir=\"`cygpath -m $(OUTDIR_PREFIX)$*`\" /\> >> $(TMPDIR)/nios2_rtdruid_partial.xml;

# take also a look to GLOBAL_RTDRUID at the top of the file!


# -------------------------------------------------------------------

# These are the commands used by nios2_dist_bin_full

CONF_nios2_binfull = \
	@echo CONF $(OUTDIR_PREFIX)$*; \
	cat $(OUTDIR_PREFIX)$*/appl.oil | gcc -c - -E -P -I$(EEBASE)/pkg $(addprefix -D, $(shell $(DEMUX2) $*)) -D$(thearch) -o - >$(OUTDIR_PREFIX)$*/ee.oil; \
	echo \<rtdruid.Oil.DistributionBuilder inputfile=\"`cygpath -m $(OUTDIR_PREFIX)$*/ee.oil`\" outputFile=\"`cygpath -m $(TMPDIR)/bindistrfull_partial.mk`\" DistributionName=\"$(subst /,,$(EXPERIMENT))_$*\" DistributionType=\"full\"/\> >> $(TMPDIR)/nios2_ant_partial.xml;

# non serve perchè fa append
#	echo $(OUTDIR_PREFIX)$*/bindistrfull.mk >> $(TMPDIR)/nios2_bindistrfull_list.txt
#questo era dopo nella parte global		cat `cat tmp/nios2_bindistrfull_list.txt` > tmp/nios2_bindistrfull.mk2; \



GLOBAL_CONF_nios2_binfull = \
	( if test nios2_dist_bin_full = $(ARCH); then \
		cat common/rtdruid_common/script_prologue.xml tmp/nios2_ant_partial.xml common/rtdruid_common/script_epilogue.xml > tmp/build.xml; \
		cp tmp/build.xml tmp/nios2_ant_global_build.xml; \
		cd tmp; java org.eclipse.core.launcher.Main -application org.eclipse.ant.core.antRunner; cd ..; \
		echo "ALL_DISTRIBUTIONS += RTDRUID" > tmp/nios2_bindistrfull.mk; \
		cat tmp/bindistrfull_partial.mk >> tmp/nios2_bindistrfull.mk; \
		false; \
		make -C ${EEBASE}/dist/binary DISTFILE=${EEBASE}/testcase/tmp/nios2_bindistrfull.mk DIST=RTDRUID NIOS2_MOVE=Y; \
	fi );

RTDRUID_nios2_binfull = \
	@echo RTDRUID $(OUTDIR_PREFIX)$*; \
	echo \<rtdruid.Oil.Configurator inputfile=\"`cygpath -m $(OUTDIR_PREFIX)$*/ee.oil`\" outputdir=\"`cygpath -m $(OUTDIR_PREFIX)$*`\" Signatures_file=\"`cygpath -m $(EE_NIOS2_IDE_BASE)/../../components/evidence_ee/ee/signature/signature.xml`\" /\> >> $(TMPDIR)/nios2_rtdruid_partial.xml;
#binDistrSignatures_file=\"`cygpath -m $(EE_NIOS2_IDE_BASE)/../../components/evidence_ee/ee/signature/signature.xml`\"

# take also a look to GLOBAL_RTDRUID at the top of the file!




# -------------------------------------------------------------------

# # These are the commands used by nios2_dist_bin_lim

# CONF_nios2_binlim = \
# 	@echo CONF $(OUTDIR_PREFIX)$*; \
# 	cat $(OUTDIR_PREFIX)$*/appl.oil | gcc -c - -E -P -I$(EEBASE)/pkg $(addprefix -D, $(shell $(DEMUX2) $*)) -D$(thearch) -o - >$(OUTDIR_PREFIX)$*/ee.oil; \
# 	echo \<rtdruid.Oil.Configurator inputfile=\"$(OUTDIR_PREFIX)$*/ee.oil\" outputdir=\"$(OUTDIR_PREFIX)$*\" bindistrlimited_file=\"bindistrlimited.mk\" /\> >> $(TMPDIR)/rtdruid_ant_partial.xml;

# DIST_nios2_binlim = \
# 	@echo DIST $(OUTDIR_PREFIX)$*; \
# 	$(LOCKFILE) $(DIST_LOCK); \
# 		make -C $(EEBASE)/dist/binary DISTFILE=$(OUTDIR_PREFIX)$*/bindistrlimited.mk DIST=RTDRUID; \
# 		mv $(EEBASE)/dist/binary/ee_RTDRUID $(OUTDIR_PREFIX)$*; \
# 		make -C $(EEBASE)/dist/binary clean; \
# 	rm -rf $(DIST_LOCK)

