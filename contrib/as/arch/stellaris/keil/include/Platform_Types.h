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
 * AUTOSAR Platform Types Header File.
 *
 * It conatins all platform dependent types and symbols. Those types must be
 * abstracted in order to become platform and compiler independend.
 *
 * Author:  2011,  Giuseppe Serano
 */

#ifndef	PLATFORM_TYPES_H
#define	PLATFORM_TYPES_H

/*
 * PLATFORM057
 */
#define	CPU_TYPE_8	8
#define	CPU_TYPE_16	16
#define	CPU_TYPE_32	32

#define	MSB_FIRST	0
#define	LSB_FIRST	1

#define	HIGH_BYTE_FIRST	0
#define	LOW_BYTE_FIRST	1

/*
 * PLATFORM044, PLATFORM045
 */
#define	CPU_TYPE	CPU_TYPE_32 

/*
 * PLATFORM038, PLATFORM043, PLATFORM048, PLATFORM049
 */
#define	CPU_BIT_ORDER	LSB_FIRST	/* Little Endian */

/*
 * PLATFORM039, PLATFORM046, PLATFORM050, PLATFORM051
 */
#define	CPU_BYTE_ORDER	LOW_BYTE_FIRST	/* Little Endian */

#include <stdbool.h>	/* Keil RVMDK stdbool.h */

/*
 * PLATFORM027
 */
typedef	_Bool	boolean;

/*
 * PLATFORM054, PLATFORM056
 */
#ifndef	FALSE
#define	FALSE	0
#endif
#ifndef	TRUE
#define	TRUE	1
#endif

#include <stdint.h>	/* Keil RVMDK stdint.h */

/*
 * PLATFORM013
 */
typedef	uint8_t		uint8;

/*
 * PLATFORM014
 */
typedef	uint16_t	uint16;

/*
 * PLATFORM015
 */
typedef	uint32_t	uint32;

/*
 * PLATFORM016
 */
typedef	int8_t		sint8;

/*
 * PLATFORM017
 */
typedef	int16_t		sint16;

/*
 * PLATFORM018
 */
typedef	int32_t		sint32;

/*
 * PLATFORM020
 */
typedef	uint_fast8_t	uint8_least;

/*
 * PLATFORM021
 */
typedef	uint_fast16_t	uint16_least;

/*
 * PLATFORM022
 */
typedef	uint_fast32_t	uint32_least;

/*
 * PLATFORM023
 */
typedef	int_fast8_t	sint8_least;

/*
 * PLATFORM024
 */
typedef	int_fast16_t	sint16_least;

/*
 * PLATFORM025
 */
typedef	int_fast32_t	sint32_least;

/*
 * PLATFORM041
 */
typedef	float		float32;

/*
 * PLATFORM042
 */
typedef	double		float64;  

#endif	/* PLATFORM_TYPES_H */
