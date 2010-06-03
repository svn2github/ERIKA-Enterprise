/* ###*B*###
 * ERIKA Enterprise - a tiny RTOS for small microcontrollers
 *
 * Copyright (C) 2002-2010  Evidence Srl
 *
 * This file is part of ERIKA Enterprise.
 *
 * ERIKA Enterprise is free software; you can redistribute it
 * and/or modify it under the terms of the GNU General Public License
 * version 2 as published by the Free Software Foundation,
 * (with a special exception described below).
 *
 * Linking this code statically or dynamically with other modules is
 * making a combined work based on this code.  Thus, the terms and
 * conditions of the GNU General Public License cover the whole
 * combination.
 *
 * As a special exception, the copyright holders of this library give you
 * permission to link this code with independent modules to produce an
 * executable, regardless of the license terms of these independent
 * modules, and to copy and distribute the resulting executable under
 * terms of your choice, provided that you also meet, for each linked
 * independent module, the terms and conditions of the license of that
 * module.  An independent module is a module which is not derived from
 * or based on this library.  If you modify this code, you may extend
 * this exception to your version of the code, but you are not
 * obligated to do so.  If you do not wish to do so, delete this
 * exception statement from your version.
 *
 * ERIKA Enterprise is distributed in the hope that it will be
 * useful, but WITHOUT ANY WARRANTY; without even the implied warranty
 * of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License version 2 for more details.
 *
 * You should have received a copy of the GNU General Public License
 * version 2 along with ERIKA Enterprise; if not, write to the
 * Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
 * Boston, MA 02110-1301 USA.
 * ###*E*### */

/*
 * Author: 2010,  Dario  Di Stefano
 * Author: 2010,  Bernardo  Dal Seno
 */

#ifndef __INCLUDE_FPGA_CAMERA_BOARD_H__
#define __INCLUDE_FPGA_CAMERA_BOARD_H__


#ifdef __USE_RTC_PCF8583__
#include "board/fpga_camera_mico32/inc/ee_rtc_pcf8583.h"
#endif // __USE_RTC_PCF8583__

#ifdef __USE_CAMERA_HV7131GP__
#include "board/fpga_camera_mico32/inc/ee_camera_hv7131gp.h"
#endif // __USE_CAMERA_HV7131GP__

#ifdef __USE_ETHERNET_ENC28J60__
#include "ENC28J60.h"
#endif // __USE_ETHERNET_ENC28J60__

#ifdef __USE_ZIGBEE_MRF24J40__
#include "mrf24j40.h"
#endif // __USE_ZIGBEE_MRF24J40__

#ifdef __USE_LIGHTSENSOR_TSL2561__
#include "board/fpga_camera_mico32/inc/ee_lightsensor_tsl2561.h"
#endif

#if defined(__USE_LEDS__) || defined(__USE_SWITCHES__) || defined(__USE_TRANSISTORS__)
#include "ee_serio.h"
#endif

#endif //__INCLUDE_FPGA_CAMERA_BOARD_H__
