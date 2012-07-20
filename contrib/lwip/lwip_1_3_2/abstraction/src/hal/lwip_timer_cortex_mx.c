/*
  Name: lwip_timer_cortex_mx.c
  Copyright: Evidence Srl
  Author: Errico Guidieri
  Date: 19/07/12 15.15
  Description: Timer library for LWIP.
*/

#include <hal/lwip_timer.h>
#include "Gpt.h"

/* Is a Macro configured in Gpt_Cfg.h */
void Gpt_Notification_Channel_LWIP(void) {
  EE_lwip_timer_tick();
}

/* Timer configuration */
void EE_hal_lwip_timers_configuration(void)
{
    
    /* Set up the timer for polling and timeouts */
    /* GPT_CHANNEL_LWIP Macro configured in Gpt_Cfg.h */
    Gpt_EnableNotification(GPT_CHANNEL_LWIP);
    Gpt_StartTimer(GPT_CHANNEL_LWIP, MILLISECONDS_TO_TICKS(EE_LWIP_TIMER_PERIOD_MS,
      EE_CPU_CLOCK));
}


