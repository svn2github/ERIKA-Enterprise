/* ###*B*###
 * ERIKA Enterprise - a tiny RTOS for small microcontrollers
 *
 * Copyright (C) 2002-2011  Evidence Srl
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
 * AUTOSAR Standard Types Header File.
 *
 * It contains all the types that are used across several modules of the basic
 * software and that are platform and compiler independend.
 *
 * Author:  2011,  Giuseppe Serano
 */


/*
 * STD014:	The standard types header files shall be protecetd against
 * 		multiple inclusion.
 */
#ifndef	STD_TYPES_H
#define	STD_TYPES_H

/*
 * STD001:	Std_Types.h shall include Platform_Types.h
 * 		Std_Types.h shall include Compiler.h
 * 		All other basic software modules shall inlcude Std_types.h
 */
#include "Platform_Types.h"
#include "Compiler.h"

/*
 * STD0005
 */
typedef	uint8	Std_ReturnType;

/*
 * STD006:	Because E_OK is already defined within OSEKm the symbol E_OK has
 *		to be shared.
 */
#ifndef	STATUSTYPEDEFINED
#define	STATUSTYPEDEFINED
#define	E_OK		0x00
typedef	unsigned char	StatusType;	/* OSEK compliance */
#endif
#define	E_NOT_OK	0x01

/*
 * STD007
 */
#define	STD_LOW		0x00	/* Physical state 0V         */
#define	STD_HIGH	0x01	/* Physical state 5V or 3.3V */

/*
 * STD010
 */
#define	STD_OFF		0x00
#define	STD_ON		0x01
/*
 * STD013
 */
#define	STD_IDLE	0x00	/* Logical state idle   */
#define	STD_ACTIVE	0x01	/* Logical state active */

/*
 * STD015
 */
typedef	struct
{
  uint16	vendorID;
  uint16	moduleID;
  uint8		sw_major_version;
  uint8		sw_minor_version;
  uint8		sw_patch_version;
/*  uint8		ar_major_version;
  uint8		ar_minor_version;
  uint8		ar_patch_version; */
} Std_VersionInfoType;

#define	STD_GET_VERSION_INFO(_vi,_module) \
	if(_vi != NULL) \
	{\
		((_vi)->vendorID = _module ## _VENDOR_ID);\
		((_vi)->moduleID = _module ## _MODULE_ID);\
		((_vi)->sw_major_version = _module ## _SW_MAJOR_VERSION);\
		((_vi)->sw_minor_version = _module ## _SW_MINOR_VERSION);\
		((_vi)->sw_patch_version = _module ## _SW_PATCH_VERSION);\
	}
/*		((_vi)->ar_major_version = _module ## _AR_MAJOR_VERSION);\
		((_vi)->ar_minor_version = _module ## _AR_MINOR_VERSION);\
		((_vi)->ar_patch_version = _module ## _AR_PATCH_VERSION);\ */
#endif	/* STD_TYPES_H */
