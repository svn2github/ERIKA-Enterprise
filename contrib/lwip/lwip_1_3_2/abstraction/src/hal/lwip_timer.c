/*
  Name: lwip_timer.c
  Copyright: Evidence Srl
  Author: Dario Di Stefano
  Date: 29/03/10 18.23
  Description: Timer library for LWIP.
*/

#include <hal/lwip_timer.h>

#ifdef __LWIP_TIME_DEBUG__

u32_t lwip_ts_buffer[LWIP_TS_BUFFER_SIZE];

#endif
