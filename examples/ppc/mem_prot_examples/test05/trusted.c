#include <ee.h>
#include <cpu/e200zx/inc/ee_irq.h>
#include "app.h"
#include "trusted.h"
#include "error.h"

EE_UREG EE_APPLICATION_UDATA(TrustedApp) gvar;
/* flag1 is allocated in the OS segment */
static volatile int flag1;
static ApplicationType EE_APPLICATION_UDATA(TrustedApp) myid;


TASK(MainTask)
{
	myid = GetApplicationID();
	if (myid == INVALID_OSAPPLICATION) {
		error(err_invalid_task_app);
	}
	ActivateTask(TrustedTask1);
	ActivateTask(App1Init);
	ActivateTask(App2Init);
	TerminateTask();
}

TASK(TrustedTask1)
{
	ApplicationType id;
	ISRType isr;
	int locvar;
	AccessType perm;
	id = GetApplicationID();
	if (id != myid) {
		error(err_wrong_isr_app);
	}
	isr = GetISRID();
	if (isr != INVALID_ISR) {
		error(err_notinvalid_isr);
	}
	perm = CheckTaskMemoryAccess(TrustedTask1, &locvar, sizeof(locvar));
	if (! OSMEMORY_IS_READABLE(perm)) {
		error(err_perm_loc_noread);
	}
	if (! OSMEMORY_IS_WRITEABLE(perm)) {
		error(err_perm_loc_nowrite);
	}
	if (! OSMEMORY_IS_STACKSPACE(perm)) {
		error(err_perm_loc_nostack);
	}
	perm = CheckTaskMemoryAccess(App1Task, &locvar, sizeof(locvar));
	if (OSMEMORY_IS_WRITEABLE(perm)) {
		error(err_perm_othapp_write);
	}
	perm = CheckTaskMemoryAccess(App1Task, (MemoryStartAddressType)&counter1,
		sizeof(counter1));
	if (! OSMEMORY_IS_READABLE(perm)) {
		error(err_perm_glob_noread);
	}
	if (! OSMEMORY_IS_WRITEABLE(perm)) {
		error(err_perm_glob_nowrite);
	}
	if (OSMEMORY_IS_STACKSPACE(perm)) {
		error(err_perm_glob_stack);
	}
	perm = CheckTaskMemoryAccess(TrustedTask1, &gvar, sizeof(gvar));
	if (! OSMEMORY_IS_READABLE(perm)) {
		error(err_perm_glob_noread);
	}
	if (! OSMEMORY_IS_WRITEABLE(perm)) {
		error(err_perm_glob_nowrite);
	}
	if (OSMEMORY_IS_STACKSPACE(perm)) {
		error(err_perm_glob_stack);
	}
	perm = CheckTaskMemoryAccess(TrustedTask1, error, 1U);
	if (! OSMEMORY_IS_EXECUTABLE(perm)) {
		error(err_perm_code_noexec);
	}
	if (OSMEMORY_IS_STACKSPACE(perm)) {
		error(err_perm_code_stack);
	}
	init_trusted_timer();
	init_app2_timer();
	TerminateTask();
}


ISR2(TrustedIsr)
{
	ApplicationType id;
	ISRType isr;
	int locvar;
	AccessType perm;
	id = GetApplicationID();
	if (id != myid) {
		error(err_wrong_isr_app);
	}
	isr = GetISRID();
	perm = CheckISRMemoryAccess(isr, &locvar, sizeof(locvar));
	if (! OSMEMORY_IS_READABLE(perm)) {
		error(err_perm_loc_noread);
	}
	if (! OSMEMORY_IS_WRITEABLE(perm)) {
		error(err_perm_loc_nowrite);
	}
	if (! OSMEMORY_IS_STACKSPACE(perm)) {
		error(err_perm_loc_nostack);
	}
	perm = CheckTaskMemoryAccess(App1Task, &locvar, sizeof(locvar));
	if (OSMEMORY_IS_WRITEABLE(perm)) {
		error(err_perm_othapp_write);
	}
	perm = CheckTaskMemoryAccess(App1Task, (MemoryStartAddressType)&counter1,
		sizeof(counter1));
	if (! OSMEMORY_IS_READABLE(perm)) {
		error(err_perm_glob_noread);
	}
	if (! OSMEMORY_IS_WRITEABLE(perm)) {
		error(err_perm_glob_nowrite);
	}
	if (OSMEMORY_IS_STACKSPACE(perm)) {
		error(err_perm_glob_stack);
	}
	perm = CheckISRMemoryAccess(isr, &gvar, sizeof(gvar));
	if (! OSMEMORY_IS_READABLE(perm)) {
		error(err_perm_glob_noread);
	}
	if (! OSMEMORY_IS_WRITEABLE(perm)) {
		error(err_perm_glob_nowrite);
	}
	if (OSMEMORY_IS_STACKSPACE(perm)) {
		error(err_perm_glob_stack);
	}
	perm = CheckISRMemoryAccess(isr, error, 1U);
	if (! OSMEMORY_IS_EXECUTABLE(perm)) {
		error(err_perm_code_noexec);
	}
	if (OSMEMORY_IS_STACKSPACE(perm)) {
		error(err_perm_code_stack);
	}
	init_app1_timer();
}
