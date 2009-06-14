#include <kal/uwl_kal_erika.h>

volatile uint32_t uwl_kal_erika_time_counter = 0;

void uwl_kal_external_timer_action(void) 
{
	uwl_kal_erika_time_counter++;
	CounterTick(UWL_EE_TASK_COUNTER);                      
}
