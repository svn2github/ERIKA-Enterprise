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
# Cortex_m0 testcases
#

#
# Global scripts
#


ifdef RTDRUID_ECLIPSE_HOME
ECLIPSE_HOME = $(RTDRUID_ECLIPSE_HOME)
else
ECLIPSE_HOME ?= /opt/eclipse/
endif
LAUNCHER_JAR=$(shell ls $(ECLIPSE_HOME)/plugins/org.eclipse.equinox.launcher_*.jar)

GLOBAL_RTDRUID += \
	( if test -e tmp/cortex_m0_rtdruid_partial.xml; then \
		cat common/rtdruid_common/script_prologue.xml tmp/cortex_m0_rtdruid_partial.xml common/rtdruid_common/script_epilogue.xml > tmp/build.xml; \
		cp tmp/build.xml tmp/cortex_m0_rtdruid_global_build.xml; \
		cd tmp; java -jar "$(LAUNCHER_JAR)" -application org.eclipse.ant.core.antRunner >rtdruid_cortex_m0.log 2>&1; \
	fi );


#
# configurations
#

TESTLIST 		+= cortex_m0
OUTDIR_COMMANDS_cortex_m0 	= $(OUTDIR_COMMANDS_cortex_m0_source)
CONF_cortex_m0           	= $(CONF_cortex_m0_source)
GLOBAL_CONF 		+=
DIST_cortex_m0            	=
RTDRUID_cortex_m0		= $(RTDRUID_cortex_m0_source)
CLEAN_cortex_m0           	=
COMPILE_cortex_m0         	= $(COMPILE_cortex_m0_source)

# -------------------------------------------------------------------


TMPDIR = $(EEBASE)/testcase/tmp
FILE_LOCK = $(TMPDIR)/cortex_m0_manual.lock
RTDRUID_GENERATE_LOCK = $(TMPDIR)/rtdruid_generate_lock.lock
LOCKFILE= lockfile -1 -r-1
DIST_LOCK = $(TMPDIR)/dist.lock


# -------------------------------------------------------------------

OUTDIR_COMMANDS_cortex_m0_source = \
	( cd $@; cp -sf ../*.* .; \
	cp -rf ../../common/cortex_m0/CM0 .; \
	cp -rf ../../common/cortex_m0/lpc12xx_flash.icf .; \
	);\
# -------------------------------------------------------------------


# # These are the commands used by cortex_m0_dist_src

# this simply parses the OIL file and then raises a flag if there is need to generate a source distribution
CONF_cortex_m0_source = \
	@echo TMPDIR=$(TMPDIR) \
	@echo CONF $(OUTDIR_PREFIX)$*; \
	cat $(OUTDIR_PREFIX)$*/appl.oil | gcc -c - -E -P -I$(EEBASE)/pkg $(addprefix -D, $(shell $(DEMUX2) $*)) -D$(thearch) -o - >$(OUTDIR_PREFIX)$*/ee.oil; \
	touch $(TMPDIR)/cortex_m0_dist_src_buildsourcedistribution.flg;

# if the flag has been raised, generate the source distribution
GLOBAL_CONF_cortex_m0_source = \
	( if test -e tmp/cortex_m0_dist_src_buildsourcedistribution.flg; then \
		make -C ${EEBASE}/dist/source DIST=cortex_m0_TESTCASE cortex_m0_MOVE=Y &>tmp/cortex_m0_dist_src_buildsourcedistribution.log; \
	fi );

RTDRUID_cortex_m0_source = \
	@echo RTDRUID $(OUTDIR_PREFIX)$*; \
	echo \<rtdruid.Oil.Configurator inputfile=\"`cygpath -m $(OUTDIR_PREFIX)$*/ee.oil`\" outputdir=\"`cygpath -m $(OUTDIR_PREFIX)$*`/Debug\" /\> >> $(TMPDIR)/cortex_m0_rtdruid_partial.xml;

COMPILE_cortex_m0_source = +if $(MAKE) $(PARAMETERS) NODEPS=1 -C $(OUTDIR_PREFIX)$*/Debug &>$(OUTDIR_PREFIX)$*/compile.log; then echo OK $(EXPERIMENT) $(OUTDIR_PREFIX)$* >>$(TMPDIR)/ok.log; else echo ERROR $(EXPERIMENT) $(OUTDIR_PREFIX)$* >>$(TMPDIR)/errors.log; fi
