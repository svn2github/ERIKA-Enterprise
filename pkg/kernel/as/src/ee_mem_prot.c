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
 * APIs and functions used for memory protection
 * Author: 2011 Bernardo  Dal Seno
 */

#include <ee_internal.h>


/*
 * Functions to enable and disable interrupts used when memory protection is
 * active.  Interrupts must be enabled/disabled when returning from the syscall
 * made from user space.
 */

/* The variables below have the "EE_oo" prefix because they could be used also
 * for the OO kernel. */

/* IRQ state at the time DisableAllInterrupts() is called.  This is global,
 * because it's used by other APIs to check if they are called inside a
 * Disable/Enable section. */
EE_FREG EE_oo_all_irq_prev_state = EE_HAL_IRQSTATE_INVALID;

/* IRQ state at the time the first SuspendAllInterrupts() is called */
static EE_FREG EE_oo_res_all_irq_prev_state;


EE_FREG EE_as_DisableAllInterrupts(EE_FREG prev)
{
	EE_FREG next;
	EE_ORTI_set_service_in(EE_SERVICETRACE_DISABLEALLINTERRUPTS);
	EE_oo_all_irq_prev_state = EE_hal_set_irq_valid_flag(prev);
	next = EE_hal_clear_irq_flag(prev);
	EE_ORTI_set_service_out(EE_SERVICETRACE_DISABLEALLINTERRUPTS);
	return next;
}


EE_FREG EE_as_EnableAllInterrupts(EE_FREG prev)
{
	EE_FREG next;
	EE_FREG prev_state;
	EE_ORTI_set_service_in(EE_SERVICETRACE_ENABLEALLINTERRUPTS);
	next = prev;
	prev_state = EE_oo_all_irq_prev_state;
	if (prev_state == EE_HAL_IRQSTATE_INVALID) {
		/* No previous DisableAllInterrupts(): do nothing */
	} else {
		EE_oo_all_irq_prev_state = EE_HAL_IRQSTATE_INVALID;
		next = EE_hal_copy_irq_flag(prev_state, next);
	}
	EE_ORTI_set_service_out(EE_SERVICETRACE_ENABLEALLINTERRUPTS);
	return next;
}


EE_FREG EE_as_SuspendAllInterrupts(EE_FREG prev)
{
	EE_FREG next;
	EE_ORTI_set_service_in(EE_SERVICETRACE_SUSPENDALLINTERRUPTS);
	next = prev;
	if (EE_oo_IRQ_disable_count == (EE_UREG)0U) {
		next = EE_hal_clear_irq_flag(next);
		EE_oo_res_all_irq_prev_state = prev;
	}
	++EE_oo_IRQ_disable_count;
	EE_ORTI_set_service_out(EE_SERVICETRACE_SUSPENDALLINTERRUPTS);
	return next;
}


EE_FREG EE_as_ResumeAllInterrupts(EE_FREG prev)
{
	EE_FREG next;
	EE_ORTI_set_service_in(EE_SERVICETRACE_RESUMEALLINTERRUPTS);
	next = prev;
	if (EE_oo_IRQ_disable_count == (EE_UREG)0U) {
		/* No previous SuspendAllInterrupts(): do nothing */
	} else {
		--EE_oo_IRQ_disable_count;
		if (EE_oo_IRQ_disable_count == (EE_UREG)0U) {
			next = EE_hal_copy_irq_flag(
				EE_oo_res_all_irq_prev_state, next);
		}
	}
	EE_ORTI_set_service_out(EE_SERVICETRACE_RESUMEALLINTERRUPTS);
	return next;
}

/* FIXME: Currently ERIKA has not defined any HAL primitives to selectively
 * disable ISR2s.  Therefore, SuspendOSInterrupts() suspends all interrupts. */

EE_FREG EE_as_SuspendOSInterrupts(EE_FREG prev)
{
	return EE_as_SuspendAllInterrupts(prev);
}

EE_FREG EE_as_ResumeOSInterrupts(EE_FREG prev)
{
	return EE_as_ResumeAllInterrupts(prev);
}


AccessType CheckTaskMemoryAccess(TaskType TaskID, MemoryStartAddressType Address,
	MemorySizeType Size)
{
	AccessType ret;

	EE_ORTI_ext_set_service_in(EE_SERVICETRACE_CHECKTASKMEMORYACCESS);
	if ((TaskID < 0) || (TaskID >= EE_MAX_TASK)) {
		/* Invalid TaskID: no permission */
		ret = (AccessType)0;
	} else {
		ApplicationType app;
		app = EE_th_app[TaskID + 1];
		ret = EE_hal_get_app_mem_access(app, Address, Size);
	}
	EE_ORTI_ext_set_service_out(EE_SERVICETRACE_CHECKTASKMEMORYACCESS);
	return ret;
}


AccessType CheckISRMemoryAccess(ISRType ISRID, MemoryStartAddressType Address,
	MemorySizeType Size)
{
	AccessType ret;

	EE_ORTI_ext_set_service_in(EE_SERVICETRACE_CHECKISRMEMORYACCESS);
	if ((ISRID < (ISRType)0U) || (ISRID >= (ISRType)EE_MAX_ISR)) {
		/* Invalid ISRID: no permission */
		ret = (AccessType)0;
	} else {
		ApplicationType app;
		app = EE_as_ISR_ROM[ISRID].ApplID;
		ret = EE_hal_get_app_mem_access(app, Address, Size);
	}
	EE_ORTI_ext_set_service_out(EE_SERVICETRACE_CHECKISRMEMORYACCESS);
	return ret;
}


StatusType CallTrustedFunction(TrustedFunctionIndexType FunctionIndex,
	TrustedFunctionParameterRefType FunctionParams)
{
	if (FunctionIndex < (TrustedFunctionIndexType)EE_MAX_SYS_SERVICEID) {
		return E_OS_SERVICEID;
	}
	return (StatusType)EE_as_raw_call_trusted_func(FunctionIndex, FunctionParams);
}


#ifdef __OO_ORTI_SERVICETRACE__
void EE_as_ORTI_set_service(EE_UINT8 srv)
{
	/* No check is done on the parameter, as this call is used for
	 * debugging, and an invalid value doesn't break the kernel */
	EE_ORTI_set_service(srv);
}
#endif /* __OO_ORTI_SERVICETRACE__ */
