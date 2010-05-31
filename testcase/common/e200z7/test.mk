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
# Freescale e200z7 testcases
#

ECLIPSE_HOME ?= /opt/eclipse/
LAUNCHER_JAR=$(shell ls $(ECLIPSE_HOME)/plugins/org.eclipse.equinox.launcher_*.jar)

#
# Global scripts
#

GLOBAL_RTDRUID += \
	( if test -e tmp/e200z7_rtdruid_partial.xml; then \
		cat common/rtdruid_common/script_prologue.xml tmp/e200z7_rtdruid_partial.xml common/rtdruid_common/script_epilogue.xml > tmp/build.xml; \
		cp tmp/build.xml tmp/e200z7_rtdruid_global_build.xml; \
		cd tmp; java -jar "$(LAUNCHER_JAR)" -application org.eclipse.ant.core.antRunner &>rtdruid_e200z7.log; \
	fi );

#
# configurations
#

# e200z7
TESTLIST 		+= e200z7
OUTDIR_COMMANDS_e200z7 	= OUTDIR_COMMANDS_e200z7_source
CONF_e200z7            	= CONF_e200z7_source
GLOBAL_CONF 		+=
DIST_e200z7            	=
RTDRUID_e200z7		= RTDRUID_e200z7_source
CLEAN_e200z7           	=
COMPILE_e200z7         	= COMPILE_e200z7_source
DEBUG_e200z7           	= DEBUG_e200z7_source

# -------------------------------------------------------------------

TMPDIR = $(EEBASE)/testcase/tmp
FILE_LOCK = $(TMPDIR)/e200z7_manual.lock
RTDRUID_GENERATE_LOCK = $(TMPDIR)/rtdruid_generate_lock.lock
LOCKFILE= lockfile -1 -r-1
DIST_LOCK = $(TMPDIR)/dist.lock

# -------------------------------------------------------------------

OUTDIR_COMMANDS_e200z7_source = \
	( cd $@; cp -sf ../*.* .; \
	);

# -------------------------------------------------------------------
# # These are the commands used by e200z7_dist_src

# this simply parses the OIL file and then raises a flag if there is need to generate a source distribution
CONF_e200z7_source = \
	@echo TMPDIR=$(TMPDIR) \
	@echo CONF $$(OUTDIR_PREFIX)$(1); \
	cat $$(OUTDIR_PREFIX)$(1)/appl.oil | gcc -c - -E -P -I$$(EEBASE)/pkg $$(addprefix -D, $$(shell $$(DEMUX2) $(1))) -D$$(thearch) -o - >$$(OUTDIR_PREFIX)$(1)/ee.oil; \
	touch $$(TMPDIR)/e200z7_dist_src_buildsourcedistribution.flg;

# if the flag has been raised, generate the source distribution
GLOBAL_CONF_e200z7_source = \
	( if test -e tmp/e200z7_dist_src_buildsourcedistribution.flg; then \
		make -C $${EEBASE}/dist/source DIST=e200z7_TESTCASE e200z7_MOVE=Y &>tmp/e200z7_dist_src_buildsourcedistribution.log; \
	fi );

# Generate the rt-druid files...
RTDRUID_e200z7_source = \
	@echo RTDRUID $$(OUTDIR_PREFIX)$(1); \
	echo \<rtdruid.Oil.Configurator inputfile=\"$$(OUTDIR_PREFIX)$(1)/ee.oil\" outputdir=\"$$(OUTDIR_PREFIX)$(1)/Debug\" /\> >> $$(TMPDIR)/e200z7_rtdruid_partial.xml;

# take also a look to GLOBAL_RTDRUID at the top of the file!!!

COMPILE_e200z7_source = +if $$(MAKE) $(PARAMETERS) NODEPS=1 -C $$(OUTDIR_PREFIX)$(1)/Debug &>$$(OUTDIR_PREFIX)$(1)/compile.log; then echo OK $$(EXPERIMENT) $$(OUTDIR_PREFIX)$(1) >>$$(TMPDIR)/ok.log; else echo ERROR $$(EXPERIMENT) $$(OUTDIR_PREFIX)$(1) >>$$(TMPDIR)/errors.log; fi

DEBUG_e200z7_source = \
	@cp e200z7/t32.cmm $$(OUTDIR_PREFIX)$(1); \
	$$(LOCKFILE) $$(FILE_LOCK); \
		echo chdir $$(OUTDIR_PREFIX)$(1) >> $$(TMPDIR)/t32_jobs.cmm; \
		echo "write \#1 \"$$(OUTDIR_PREFIX)$(1)\"" >> $$(TMPDIR)/t32_jobs.cmm; \
		echo area.select Messages >> $$(TMPDIR)/t32_jobs.cmm; \
		echo print >> $$(TMPDIR)/t32_jobs.cmm; \
		echo print \"$$(OUTDIR_PREFIX)$(1)\" >> $$(TMPDIR)/t32_jobs.cmm; \
		echo area.select A000 >> $$(TMPDIR)/t32_jobs.cmm; \
		echo do t32.cmm >> $$(TMPDIR)/t32_jobs.cmm; \
		cp -u e200z7/t32_quit.cmm $$(TMPDIR)/t32.cmm; \
	rm -f $$(FILE_LOCK);

