#include <kal/ozb_kal_erika.h>

volatile uint32_t ozb_kal_erika_time_counter = 0;

void ozb_kal_external_timer_action(void) 
{
	ozb_kal_erika_time_counter++;
	CounterTick(OZB_EE_TASK_COUNTER);                      
}
