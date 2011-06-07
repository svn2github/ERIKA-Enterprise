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
# dsPIC PIC30 testcases
#

#
# Global scripts
#

GLOBAL_RTDRUID += \
	( if test -e tmp/pic30_rtdruid_partial.xml; then \
		cat common/rtdruid_common/script_prologue.xml tmp/pic30_rtdruid_partial.xml common/rtdruid_common/script_epilogue.xml > tmp/build.xml; \
		cp tmp/build.xml tmp/pic30_rtdruid_global_build.xml; \
		cd tmp; java org.eclipse.core.launcher.Main -application org.eclipse.ant.core.antRunner &>rtdruid_pic30.log; \
	fi );




#
# configurations
#


# pic30_dist_src
TESTLIST += pic30_dist_src
OUTDIR_COMMANDS_pic30_dist_src = $(OUTDIR_COMMANDS_pic30)
CONF_pic30_dist_src             = $(CONF_pic30_source)
GLOBAL_CONF += $(GLOBAL_CONF_pic30_source)
DIST_pic30_dist_src            =
RTDRUID_pic30_dist_src            = $(RTDRUID_pic30_source)
CLEAN_pic30_dist_src           =
COMPILE_pic30_dist_src         = $(COMPILE_pic30_source)
#DEBUG_pic30_dist_src           =

# pic30_dist_bin_full
TESTLIST += pic30_dist_bin_full
OUTDIR_COMMANDS_pic30_dist_bin_full = $(OUTDIR_COMMANDS_pic30)
CONF_pic30_dist_bin_full             = $(CONF_pic30_binfull)
GLOBAL_CONF += $(GLOBAL_CONF_pic30_binfull)
DIST_pic30_dist_bin_full            =
RTDRUID_pic30_dist_bin_full            = $(RTDRUID_pic30_binfull)
CLEAN_pic30_dist_bin_full           =
COMPILE_pic30_dist_bin_full         = $(COMPILE_pic30_source)
#DEBUG_pic30_dist_bin_full           = DEBUG_pic30

# -------------------------------------------------------------------


TMPDIR = $(EEBASE)/testcase/tmp
FILE_LOCK = $(TMPDIR)/pic30_manual.lock
RTDRUID_GENERATE_LOCK = $(TMPDIR)/rtdruid_generate_lock.lock
LOCKFILE= lockfile -1 -r-1
DIST_LOCK = $(TMPDIR)/dist.lock


# -------------------------------------------------------------------

OUTDIR_COMMANDS_pic30 = cd $@; cp -sf ../*.* .

# -------------------------------------------------------------------


# # These are the commands used by pic30_dist_src

# this simply parses the OIL file and then raises a flag if there is need to generate a source distribution
CONF_pic30_source = \
	@echo TMPDIR=$(TMPDIR) \
	@echo CONF $(OUTDIR_PREFIX)$*; \
	cat $(OUTDIR_PREFIX)$*/appl.oil | gcc -c - -E -P -I$(EEBASE)/pkg $(addprefix -D, $(shell $(DEMUX2) $*)) -D$(thearch) -o - >$(OUTDIR_PREFIX)$*/ee.oil; \
	touch $(TMPDIR)/pic30_dist_src_buildsourcedistribution.flg;

# if the flag has been raised, generate the source distribution
GLOBAL_CONF_pic30_source = \
	( if test -e tmp/pic30_dist_src_buildsourcedistribution.flg; then \
		make -C ${EEBASE}/dist/source DIST=PIC30_TESTCASE PIC30_MOVE=Y &>tmp/pic30_dist_src_buildsourcedistribution.log; \
	fi );

RTDRUID_pic30_source = \
	@echo RTDRUID $(OUTDIR_PREFIX)$*; \
	echo \<rtdruid.Oil.Configurator inputfile=\"`cygpath -m $(OUTDIR_PREFIX)$*/ee.oil`\" outputdir=\"`cygpath -m $(OUTDIR_PREFIX)$*`/Debug\" /\> >> $(TMPDIR)/pic30_rtdruid_partial.xml;

# take also a look to GLOBAL_RTDRUID at the top of the file!

COMPILE_pic30_source = +if $(MAKE) $(PARAMETERS) NODEPS=1 -C $(OUTDIR_PREFIX)$*/Debug &>$(OUTDIR_PREFIX)$*/compile.log; then echo OK $(EXPERIMENT) $(OUTDIR_PREFIX)$* >>$(TMPDIR)/ok.log; else echo ERROR $(EXPERIMENT) $(OUTDIR_PREFIX)$* >>$(TMPDIR)/errors.log; fi


# -------------------------------------------------------------------

# These are the commands used by pic30_dist_bin_full

CONF_pic30_binfull = \
	@echo CONF $(OUTDIR_PREFIX)$*; \
	cat $(OUTDIR_PREFIX)$*/appl.oil | gcc -c - -E -P -I$(EEBASE)/pkg $(addprefix -D, $(shell $(DEMUX2) $*)) -D$(thearch) -o - >$(OUTDIR_PREFIX)$*/ee.oil; \
	echo \<rtdruid.Oil.DistributionBuilder inputfile=\"`cygpath -m $(OUTDIR_PREFIX)$*/ee.oil`\" outputFile=\"`cygpath -m $(TMPDIR)/bindistrfull_partial.mk`\" DistributionName=\"$(subst /,,$(EXPERIMENT))_$*\" DistributionType=\"full\"/\> >> $(TMPDIR)/pic30_ant_partial.xml;


GLOBAL_CONF_pic30_binfull = \
	( if test pic30_dist_bin_full = $(ARCH); then \
		cat common/rtdruid_common/script_prologue.xml tmp/pic30_ant_partial.xml common/rtdruid_common/script_epilogue.xml > tmp/build.xml; \
		cp tmp/build.xml tmp/pic30_ant_global_build.xml; \
		cd tmp; java org.eclipse.core.launcher.Main -application org.eclipse.ant.core.antRunner; cd ..; \
		echo "ALL_DISTRIBUTIONS += RTDRUID" > tmp/pic30_bindistrfull.mk; \
		cat tmp/bindistrfull_partial.mk >> tmp/pic30_bindistrfull.mk; \
		false; \
		make -C ${EEBASE}/dist/binary DISTFILE=${EEBASE}/testcase/tmp/pic30_bindistrfull.mk DIST=RTDRUID PIC30_MOVE=Y; \
	fi );

RTDRUID_pic30_binfull = \
	@echo RTDRUID $(OUTDIR_PREFIX)$*; \
	echo \<rtdruid.Oil.Configurator inputfile=\"`cygpath -m $(OUTDIR_PREFIX)$*/ee.oil`\" outputdir=\"`cygpath -m $(OUTDIR_PREFIX)$*`\" Signatures_file=\"`cygpath -m $(EE_PIC30_IDE_BASE)/../../components/evidence_ee/ee/signature/signature.xml`\" /\> >> $(TMPDIR)/pic30_rtdruid_partial.xml;
#binDistrSignatures_file=\"`cygpath -m $(EE_PIC30_IDE_BASE)/../../components/evidence_ee/ee/signature/signature.xml`\"

# take also a look to GLOBAL_RTDRUID at the top of the file!




# -------------------------------------------------------------------

# # These are the commands used by pic30_dist_bin_lim

# CONF_pic30_binlim = \
# 	@echo CONF $(OUTDIR_PREFIX)$*; \
# 	cat $(OUTDIR_PREFIX)$*/appl.oil | gcc -c - -E -P -I$(EEBASE)/pkg $(addprefix -D, $(shell $(DEMUX2) $*)) -D$(thearch) -o - >$(OUTDIR_PREFIX)$*/ee.oil; \
# 	echo \<rtdruid.Oil.Configurator inputfile=\"$(OUTDIR_PREFIX)$*/ee.oil\" outputdir=\"$(OUTDIR_PREFIX)$*\" bindistrlimited_file=\"bindistrlimited.mk\" /\> >> $(TMPDIR)/rtdruid_ant_partial.xml;

