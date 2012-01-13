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
 * AUTOSAR Compiler Header File.
 *
 * It conatins all the macros for abstraction of compiler specific keywords used
 * for addressing data and code with declarations and definitions.
 *
 * Author:  2011,  Giuseppe Serano
 */

/*
 * COMPILER047
 */
#ifndef	COMPILER_H
#define	COMPILER_H

/*
 * COMPILER010
 */
#define	_KEIL_C_STELLARIS_

/*
 * COMPILER030
 *
 * Keil
 * µVision V4.23.00.0
 * Copyright (C) 2011 ARM Ltd and ARM Germany GmbH. All rights reserved.
 * 
 * Tool Version Numbers:
 * Toolchain:		MDK-Lite 	Version: 4.23
 * Toolchain Path:	C:\Keil\ARM\BIN40
 * C Compiler:		Armcc.Exe	V4.1.0.894 [Evaluation]
 * Assembler:		Armasm.Exe	V4.1.0.894 [Evaluation]
 * Linker/Locator:	ArmLink.Exe	V4.1.0.894 [Evaluation]
 * Librarian:		ArmAr.Exe	V4.1.0.894 [Evaluation]
 * Hex Converter:	FromElf.Exe	V4.1.0.894 [Evaluation]
 * CPU DLL:		SARMCM3.DLL	V4.23
 * Dialog DLL:		DCM.DLL		V1.4.0.0
 * Target DLL:		lmidk-agdi.dll	V???
 * Dialog DLL:		TCM.DLL		V1.4.0.0
 */

/*
 * COMPILER046
 */
#define	AUTOMATIC

/*
 * COMPILER059
 */
#define	TYPEDEF

/*
 * COMPILER051
 */
#define	NULL_PTR	((void *)0)

/*
 * COMPILER057
 */
#define	INLINE	__inline

/*
 * COMPILER060
 */
#define	LOCAL_INLINE	static __inline

/*
 * COMPILER001
 */
/* #define	FUNC(rettype, memclass)	\
		memclass rettype */
#define	FUNC(rettype, memclass)	\
	rettype

/*
 * COMPILER006
 */
/* #define	P2VAR(ptrtype, memclass, ptrclass)	\
		ptrclass ptrtype * memclass */
#define	P2VAR(ptrtype, memclass, ptrclass)	\
	ptrtype *

/*
 * COMPILER013
 */
/*#define	P2CONST(ptrtype, memclass, ptrclass)	\
		ptrclass const ptrtype * memclass */
#define	P2CONST(ptrtype, memclass, ptrclass)	\
	const ptrtype *

/*
 * COMPILER031
 */
/* #define	CONSTP2VAR(ptrtype, memclass, ptrclass)	\
		ptrclass ptrtype * const memclass */
#define	CONSTP2VAR(ptrtype, memclass, ptrclass)	\
	ptrtype * const

/*
 * COMPILER032
 */
/* #define	CONSTP2CONST(ptrtype, memclass, ptrclass)	\
		ptrclass const ptrtype * const memclass */
#define	CONSTP2CONST(ptrtype, memclass, ptrclass)	\
	const ptrtype * const

/*
 * COMPILER039
 */
/* #define	P2FUNC(rettype, ptrclass, fctname)	\
		rettype (*ptrclass fctname) */
#define	P2FUNC(rettype, ptrclass, fctname)	\
	rettype (* fctname)

/*
 * COMPILER023
 */
/* #define	CONST(consttype, memclass)	\
		const consttype memclass */
#define	CONST(consttype, memclass)	\
	const consttype

/*
 * COMPILER026
 */
/* #define	VAR(vartype, memclass)	\
		vartype memclass */
#define	VAR(vartype, memclass)	\
	vartype

#endif	/* COMPILER_H */
