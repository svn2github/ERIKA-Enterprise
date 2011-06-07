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
# Freescale PowerPc e200zX testcases
#

ifdef RTDRUID_ECLIPSE_HOME
ECLIPSE_HOME = $(RTDRUID_ECLIPSE_HOME)
else
ECLIPSE_HOME ?= /opt/eclipse/
endif
LAUNCHER_JAR=$(shell ls $(ECLIPSE_HOME)/plugins/org.eclipse.equinox.launcher_*.jar)

#
# Global scripts
#

GLOBAL_RTDRUID += \
	( if test -e tmp/e200zx_rtdruid_partial.xml; then \
		cat common/rtdruid_common/script_prologue.xml tmp/e200zx_rtdruid_partial.xml common/rtdruid_common/script_epilogue.xml > tmp/build.xml; \
		cp tmp/build.xml tmp/e200zx_rtdruid_global_build.xml; \
		cd tmp; java -jar "$(LAUNCHER_JAR)" -application org.eclipse.ant.core.antRunner >rtdruid_e200zx.log 2>&1; \
	fi );

#
# configurations
#

# e200zx
TESTLIST 		+= e200zx
OUTDIR_COMMANDS_e200zx 	= $(OUTDIR_COMMANDS_e200zx_source)
CONF_e200zx            	= $(CONF_e200zx_source)
GLOBAL_CONF 		+=
DIST_e200zx            	=
RTDRUID_e200zx		= $(RTDRUID_e200zx_source)
CLEAN_e200zx           	=
COMPILE_e200zx         	= $(COMPILE_e200zx_source)
DEBUG_e200zx           	= $(DEBUG_e200zx_source)

# -------------------------------------------------------------------

TMPDIR = $(EEBASE)/testcase/tmp
FILE_LOCK = $(TMPDIR)/e200zx_manual.lock
RTDRUID_GENERATE_LOCK = $(TMPDIR)/rtdruid_generate_lock.lock
LOCKFILE= lockfile -1 -r-1
DIST_LOCK = $(TMPDIR)/dist.lock

# -------------------------------------------------------------------

OUTDIR_COMMANDS_e200zx_source = \
	( cd $@; cp -sf ../*.* .; \
	);

# -------------------------------------------------------------------
# # These are the commands used by e200zx_dist_src

# this simply parses the OIL file and then raises a flag if there is need to generate a source distribution
CONF_e200zx_source = \
	echo CONF $(OUTDIR_PREFIX)$*; \
	cat $(OUTDIR_PREFIX)$*/appl.oil | gcc -c - -E -P -I$(EEBASE)/pkg $(addprefix -D, $(shell $(DEMUX2) $*)) -D$(thearch) -o - >$(OUTDIR_PREFIX)$*/ee.oil; \
	touch $(TMPDIR)/e200zx_dist_src_buildsourcedistribution.flg;

# if the flag has been raised, generate the source distribution
GLOBAL_CONF_e200zx_source = \
	( if test -e tmp/e200zx_dist_src_buildsourcedistribution.flg; then \
		make -C ${EEBASE}/dist/source DIST=e200zx_TESTCASE e200zx_MOVE=Y >tmp/e200zx_dist_src_buildsourcedistribution.log 2>&1; \
	fi );

# Generate the rt-druid files...
RTDRUID_e200zx_source = \
	@echo RTDRUID $(OUTDIR_PREFIX)$*; \
	echo \<rtdruid.Oil.Configurator inputfile=\"$(OUTDIR_PREFIX)$*/ee.oil\" outputdir=\"$(OUTDIR_PREFIX)$*/Debug\" /\> >> $(TMPDIR)/e200zx_rtdruid_partial.xml;

# take also a look to GLOBAL_RTDRUID at the top of the file!!!

COMPILE_e200zx_source = +if $(MAKE) $(PARAMETERS) NODEPS=1 -C $(OUTDIR_PREFIX)$*/Debug >$(OUTDIR_PREFIX)$*/compile.log 2>&1; then echo OK $(EXPERIMENT) $(OUTDIR_PREFIX)$* >>$(TMPDIR)/ok.log; else echo ERROR $(EXPERIMENT) $(OUTDIR_PREFIX)$* >>$(TMPDIR)/errors.log; fi

DEBUG_e200zx_source = \
	@cp e200zx/t32.cmm $(OUTDIR_PREFIX)$*; \
	$(LOCKFILE) $(FILE_LOCK); \
		echo "&count=&count+1" >> $(TMPDIR)/t32_jobs.cmm; \
		echo chdir $(OUTDIR_PREFIX)$* >> $(TMPDIR)/t32_jobs.cmm; \
		echo "write \#1 \"$(OUTDIR_PREFIX)$*\"" >> $(TMPDIR)/t32_jobs.cmm; \
		echo area.select Messages >> $(TMPDIR)/t32_jobs.cmm; \
		echo print >> $(TMPDIR)/t32_jobs.cmm; \
		echo print '"Test no. "' '%Decimal' '&count' '" ("' '&failed' \
		'" errors so far)"' >> $(TMPDIR)/t32_jobs.cmm; \
		echo print \"$(OUTDIR_PREFIX)$*\" >> $(TMPDIR)/t32_jobs.cmm; \
		echo area.select A000 >> $(TMPDIR)/t32_jobs.cmm; \
		echo do t32.cmm >> $(TMPDIR)/t32_jobs.cmm; \
		cp -u e200zx/t32_quit.cmm $(TMPDIR)/t32.cmm; \
	rm -f $(FILE_LOCK);

