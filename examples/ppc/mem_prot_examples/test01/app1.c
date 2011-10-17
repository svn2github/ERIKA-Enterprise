#include <ee.h>
#include <cpu/e200zx/inc/ee_irq.h>

static volatile int EE_APPLICATION_UDATA(App1) state1;

ISR2(App1Isr)
{
	if (! (state1 & 1)) {
		ActivateTask(App1Task);
	}
	state1 ^= 1;
}


TASK(App1Task)
{
	while (state1 & 1) {
		/* Wait for the next ISR invocation */
	}
	TerminateTask();
}
