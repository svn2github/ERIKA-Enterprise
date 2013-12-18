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
 * Internals for Autosar layer
 * Author: 2010 Fabio Checconi
 *         2011 Bernardo  Dal Seno
 */

#ifndef __INCLUDE_AS_EE_OS_INTERNAL_H__
#define __INCLUDE_AS_EE_OS_INTERNAL_H__

#if defined(__AS_SC4__)

#include "kernel/as/inc/ee_os.h"

/**
 * EE_as_ISR_ROM_type - static ISR descriptor:
 * @ApplID:		ID of the application the ISR belongs to.
 */
typedef struct {
	ApplicationType		ApplID;
} EE_as_ISR_ROM_type;

/*
 * EE_as_ISR_RAM_type - runtime ISR descriptor:
 * @TOS:		TOS to be restored when the ISR is terminated.
 * @ISR_Terminated:	Field obtained combinig T << 16 || ISRID, with T = 1
 *			if the ISR has to be terminated.
 */
typedef struct {
	MemoryStartAddressType	TerminationTOS;
	ISRType			ISR_Terminated;
} EE_as_ISR_RAM_type;

/*
 * EE_as_Application_ROM_type - static OS Application descriptor:
 * sec_info:    Address and size of application sections
 */
typedef struct {
	EE_APP_SEC_INFO_T sec_info;
} EE_as_Application_ROM_type;

extern const EE_as_Application_ROM_type EE_as_Application_ROM[EE_MAX_APP];

/*
 * EE_as_Application_RAM_type - runtime OS Application descriptor:
 * @ISRTOS:		TOS to be used by the application's ISRs.
 * @Mode:		Mode bits, to distinguish between trusted and untrusted
 *			  applications (might be platform dependent, check in
 *			  the future ports if it can stay here or it has to be
 *			  moved to the HAL).  NOTE: it could be critical for
 *			  performance, as it is accessed on every mode switch.
 * @ApplState:		State of the application.
 */
typedef struct {
	MemoryStartAddressType	ISRTOS;
	EE_UREG			Mode;
	ApplicationStateType	ApplState;
	EE_UREG			pad;
} EE_as_Application_RAM_type;

#define EE_APP_RAM_INIT(stack, mode) { ((MemoryStartAddressType)(stack)), \
	(mode), APPLICATION_ACCESSIBLE, 0U }

/* Run-time info about applications. The first entry (INVALID_ISR) of this array
 * is empty. */
extern EE_as_Application_RAM_type EE_as_Application_RAM[EE_MAX_APP+1U];

/* LIFO list of running ISRs.  The current record is given by
 * (EE_hal_get_IRQ_nesting_level() - 1U), when an ISR is running. */
extern EE_as_ISR_RAM_type EE_as_ISR_stack[EE_MAX_NESTING_LEVEL];

/* Mapping from tasks to applications */
extern const ApplicationType EE_th_app[EE_MAX_TASK + 1];

/* Mapping from ISRs to applications */
extern const EE_as_ISR_ROM_type EE_as_ISR_ROM[EE_MAX_ISR];

/* Return the access permission for the given memory area.  Defined in the CPU
 * layer. */
AccessType EE_hal_get_app_mem_access(ApplicationType app,
	MemoryStartAddressType beg, MemorySizeType size);

#ifdef __OO_ORTI_SERVICETRACE__
#define EE_SERVICETRACE_CHECKTASKMEMORYACCESS    68U
#define EE_SERVICETRACE_CHECKISRMEMORYACCESS     70U
#define EE_SERVICETRACE_GETAPPLICATIONID         72U
#define EE_SERVICETRACE_GETISRID                 74U
#endif /* __OO_ORTI_SERVICETRACE__ */

#endif /* __AS_SC4__ */

#endif /* __INCLUDE_AS_EE_OS_INTERNAL_H__ */
