# ###*B*###
# ERIKA Enterprise - a tiny RTOS for small microcontrollers
# 
# Copyright (C) 2002-2009  Evidence Srl
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

## Authors:
## 2012 Nicola Serreli



############################################################################
#
# Workaround to remove cygwin warning messages about the usage of DOS-like paths
# that is produced the first time a DOS-like path is used:
#  - run as soon as possible a shell command that uses a path and drop 
#    the error message.
# Here is an example, using 'test' command
#  es:  $(shell test -d "c:\\dummy\\path" 2>/dev/null)
#
# Usually, check_and_set_xxx_compiler_path is called in first stages of makefile
# and it contains a test command that already drop the error message, than there
# is no need to explicitly invoke a shell command to drop the message.
#
# Note: CYGWIN=nodosfilewarning option has to be set before the first execution
#       of cygwin programs, than it cannot be set here
#
############################################################################
#$(shell test -d "c:\\dummy\\path" 2>/dev/null)


############################################################################
#
# Compiler checks
#
############################################################################


#
# Checks if a path exists and then sets the variable required by Erika makefiles.
# The resulted path is transformed using cygwin functions
#
# 1-> container name (es. PIC30_GCC). Cannot be empty.
# 2-> native compiler path (es c:/Program Files). Can be empty.
#
# es -> $(eval $(call check_and_set_cygwin_compiler_path,PIC30_GCC,C:\\Program Files))
#
define check_and_set_cygwin_compiler_path

ifndef $(1)

    ifeq ($$(strip $(2)),)
            # usually this error happens if RT-Druid was not able to find the default value
            $$(error Please set the compiler path into $(1) variable before run the makefile)
    else
        CHECK_COMPILER_PATH := $$(shell test -d "$(2)" 2>/dev/null && echo "0")
        ifneq ($$(CHECK_COMPILER_PATH),0)
            $$(error Compiler not found. Provided path is '$(2)')
        endif
        CHECK_COMPILER_PATH :=
        $(1) := $$(shell cygpath `cygpath -ms '$(2)'`)
    endif
    
else
    CHECK_COMPILER_PATH := $$(shell test -d "$$($(1))" 2>/dev/null && echo "0")
    ifneq ($$(CHECK_COMPILER_PATH),0)
        $$(error Compiler not found. Provided path is '$$($(1))')
    endif
    CHECK_COMPILER_PATH :=
endif

endef

#
# Checks if a path exists and then sets the variable required by Erika makefiles
#
# 1-> container name (es. PIC30_GCC). Cannot be empty
# 2-> native compiler path (es /opt/Program Files). Can be empty.
#
# es -> $(eval $(call check_and_set_linux_compiler_path,PIC30_GCC,/opt/Program Files))
#
define check_and_set_linux_compiler_path

ifndef $(1)

    ifeq ($$(strip $(2)),)
            # usually this error happens if RT-Druid was not able to find the default value
            $$(error Please set the compiler path into $(1) variable before run the makefile)
    else
        CHECK_COMPILER_PATH := $$(shell test -d "$(2)" 2>/dev/null && echo "0")
        ifneq ($$(CHECK_COMPILER_PATH),0)
            $$(error Compiler not found. Provided path is '$(2)')
        endif
        CHECK_COMPILER_PATH :=
        $(1) := $(2)
    endif
    
else
    CHECK_COMPILER_PATH := $$(shell test -d "$$($(1))" 2>/dev/null && echo "0")
    ifneq ($$(CHECK_COMPILER_PATH),0)
        $$(error Compiler not found. Provided path is '$$($(1))')
    endif
    CHECK_COMPILER_PATH :=
endif

endef


