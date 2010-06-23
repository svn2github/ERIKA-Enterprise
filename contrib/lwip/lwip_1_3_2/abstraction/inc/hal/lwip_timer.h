/*
  Name: lwip_timer.h
  Copyright: Evidence Srl
  Author: Dario Di Stefano
  Date: 29/03/10 18.23
  Description: Timer configurations functions for LWIP.
*/

#ifndef __lwip_timer_h__
#define __lwip_timer_h__

#ifndef LWIP_HAL_EXTERNAL_TIMER		/* Check if no external HAL timer */
#include <hal/lwip_compiler.h>
#if defined __LM32__
#include <hal/lwip_timer_mico32.h>
#else			/* No timer */
#error "LWIP_HAL ERROR: timer hw interface not specified"
#endif	/* End Selection */
#endif /* lwip_HAL_EXTERNAL_TIMER */

#define lwip_time_diff_ms(from,to)  ((EE_UINT32)((from) - (to)) / (EE_UINT32)(CPU_FREQUENCY / 1000))
#define lwip_time_diff_us(from,to)  ((EE_UINT32)((from) - (to)) / (EE_UINT32)(CPU_FREQUENCY / 1000000))

#ifdef __LWIP_TIME_DEBUG__

/* Platform description */
#include <system_conf.h>

enum{	
	LWIP_START_ETH_OUT,
	LWIP_START_LOWLEV_OUT, 
	LWIP_START_UDP_SEND, 
	LWIP_START_LOWLEV_INIT,
	LWIP_START_LOWLEV_INPUT,
	LWIP_START_ETH_INIT,
	LWIP_START_ETH_INPUT,
	LWIP_START_UDP_INPUT,
	LWIP_START_UDP_RX_CBK,
	LWIP_START_UDP_SEND_IPROUTE,
	LWIP_START_LOWLEV_INIT_TRANSFER,
	LWIP_START_LOWLEV_WRITE,
	LWIP_START_LOWLEV_SIGNAL,
	
	LWIP_END_ETH_OUT,
	LWIP_END_LOWLEV_OUT,
	LWIP_END_UDP_SEND,
	LWIP_END_LOWLEV_INIT,
	LWIP_END_LOWLEV_INPUT,
	LWIP_END_ETH_INPUT,
	LWIP_END_ETH_INIT,
	LWIP_END_UDP_INPUT,
	LWIP_END_UDP_RX_CBK,
	LWIP_END_UDP_SEND_IPROUTE,
	LWIP_END_LOWLEV_INIT_TRANSFER,
	LWIP_END_LOWLEV_WRITE,
	LWIP_END_LOWLEV_SIGNAL,
	
	LWIP_TS_BUFFER_SIZE };
	
extern u32_t lwip_ts_buffer[LWIP_TS_BUFFER_SIZE];

__INLINE__ void __ALWAYS_INLINE__ EE_lwip_write_timestamp(u32_t id)
{
	lwip_ts_buffer[id] = EE_hal_lwip_read_timer();
}

__INLINE__ u32_t __ALWAYS_INLINE__ EE_lwip_read_timestamp(u32_t id)
{
	return lwip_ts_buffer[id];
}

__INLINE__ void __ALWAYS_INLINE__ EE_lwip_reset_timestamp(void)
{
	int i;
	for(i=0; i<LWIP_TS_BUFFER_SIZE; i++)
		lwip_ts_buffer[i] = 0;
}

#else
#define EE_lwip_write_timestamp(id)
#define EE_lwip_read_timestamp(id)	-1
#define EE_lwip_reset_timestamp()
#endif

#endif /* Header Protection */
