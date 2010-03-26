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

ifeq ($(findstring __LM32__,$(EEOPT)) , __LM32__)

ifeq ($(findstring __USE_MICO32BOARD_RTC_PCF8583__,$(EEOPT)) ,__USE_MICO32BOARD_RTC_PCF8583__)
EE_SRCS += pkg/board/fpga_camera_mico32/src/ee_rtc_pcf8583.c
endif

ifeq ($(findstring __USE_MICO32BOARD_CAMERA_HV7131GP__,$(EEOPT)) , __USE_MICO32BOARD_CAMERA_HV7131GP__)
EE_SRCS += pkg/board/fpga_camera_mico32/src/ee_camera_hv7131gp.c
endif

ifeq ($(findstring __USE_MICO32BOARD_ETHCTRL_ENC28J60__,$(EEOPT)) , __USE_MICO32BOARD_ETHCTRL_ENC28J60__)
EE_SRCS += pkg/board/fpga_camera_mico32/src/ee_ethctrl_enc28j60.c
endif

ifeq ($(findstring __USE_MICO32BOARD_WIFICTRL_MRF24J40__,$(EEOPT)) , __USE_MICO32BOARD_WIFICTRL_MRF24J40__)
EE_SRCS += pkg/board/fpga_camera_mico32/src/ee_wifictrl_mrf24j40.c
endif

endif #__LM32__
