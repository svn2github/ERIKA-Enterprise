/* ###*B*###
 * ERIKA Enterprise - a tiny RTOS for small microcontrollers
 *
 * Copyright (C) 2002-2008  Evidence Srl
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
 * Author: 2003 Paolo Gai
 * CVS: $Id: ee_kernel.h,v 1.4 2008/07/16 09:46:12 francesco Exp $
 */

#include "kernel/frsh/inc/ee_common.h"

#ifndef __INCLUDE_FRSH_KERN_H__
#define __INCLUDE_FRSH_KERN_H__

/* This macros are used to define a task */
#define DeclareTask(t) void Func##t(void)
#define TASK(t) void Func##t(void)

/*************************************************************************
 System functions
 *************************************************************************/

#ifndef __PRIVATE_SYS_GETTIME__
#ifdef __TIME_SUPPORT__
EE_TIME EE_frsh_sys_gettime(void);
#endif
#endif


/*************************************************************************
 Primitives
 *************************************************************************/




#ifndef __PRIVATE_THREAD_ACTIVATE__
void EE_frsh_thread_activate(EE_TID t);
#endif

#ifndef __PRIVATE_SCHEDULE__
void EE_frsh_Schedule(void);
#endif

#ifndef __PRIVATE_GETRESOURCE__
void EE_frsh_GetResource(EE_TYPERESOURCE m);
#endif

#ifndef __PRIVATE_RELEASERESOURCE__
void EE_frsh_ReleaseResource(EE_TYPERESOURCE m);
#endif



/* FRESCOR API Implementation */

#include "frsh_configuration_parameters.h"
#include "frsh_core_types.h"
#include "frsh_error.h"


/* Basic services */

#ifndef __PRIVATE_FRSH_INIT__
int EE_frsh_init(void);
#endif

#ifndef __PRIVATE_FRSH_STRERROR__
int EE_frsh_strerror(int error, char *message, size_t size);
#endif




/* Contract Creation and initialization */

#ifndef __PRIVATE_FRSH_CONTRACT_GET_BASIC_PARAMS__
int EE_frsh_contract_get_basic_params (const frsh_contract_t *contract,
				       frsh_rel_time_t *budget_min,
				       frsh_rel_time_t *period_max,
				       frsh_workload_t *workload,
				       frsh_contract_type_t *contract_type);
#endif

#ifndef __PRIVATE_FRSH_CONTRACT_GET_RESOURCE_AND_LABEL__
int EE_frsh_contract_get_resource_and_label(const frsh_contract_t *contract,
					    frsh_resource_type_t *resource_type,
					    frsh_resource_id_t *resource_id, 
					    char *contract_label);
#endif

#ifndef __PRIVATE_FRSH_CONTRACT_GET_TIMING_REQS__
int EE_frsh_contract_get_timing_reqs(const frsh_contract_t *contract, 
				     int *d_equals_t,
				     frsh_rel_time_t *deadline, 
				     frsh_signal_t *budget_overrun_signal, 
				     frsh_signal_info_t *budget_overrun_siginfo, 
				     frsh_signal_t *deadline_miss_signal, 
				     frsh_signal_info_t *deadline_miss_siginfo);
#endif






/* Negotiate Contract Functions */

#ifndef __PRIVATE_BINDTASK__
int EE_frsh_BindTask(const frsh_vres_id_t vres, const frsh_thread_id_t thread);
#endif

#ifndef __PRIVATE_UNBINDTASK__
int EE_frsh_UnbindTask(const frsh_thread_id_t thread);
#endif

#ifndef __PRIVATE_GETVRESID__
int EE_frsh_thread_get_vres_id(const frsh_thread_id_t thread, frsh_vres_id_t *vres_id);
#endif

#ifndef __PRIVATE_GETCONTRACT__
int EE_frsh_vres_get_contract (const frsh_vres_id_t vres, frsh_contract_t *contract);
#endif


#endif


