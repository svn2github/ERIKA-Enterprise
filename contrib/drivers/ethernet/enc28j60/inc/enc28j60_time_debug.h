/*
  Name: enc28j60_time.h
  Copyright: Evidence Srl
  Author: Dario Di Stefano
  Date: 29/03/10 18.23
  Description: ENC28J60 time debug
*/


#ifndef __ENC28J60_TIME_DEBUG_H__
#define __ENC28J60_TIME_DEBUG_H__

#ifdef __ENC28J60_TIME_DEBUG__

#include <stdio.h>
#include <string.h>
/* Platform description */
#include <system_conf.h>

#define enc28j60_time_diff_ms(from,to)  ((EE_UINT32)((from) - (to)) / (EE_UINT32)(CPU_FREQUENCY / 1000))
#define enc28j60_time_diff_us(from,to)  ((EE_UINT32)((from) - (to)) / (EE_UINT32)(CPU_FREQUENCY / 1000000))


__INLINE__ EE_UINT32 __ALWAYS_INLINE__ EE_enc28j60_read_freetimer(void)
{
	EE_UINT32 time_val;
	EE_freetimer_get_value(&time_val);
	return time_val;
}

enum{	
	ENC28J60_START_MAC_FLUSH_WAIT,
	ENC28J60_START_MAC_FLUSH_RETX,
	ENC28J60_END_MAC_FLUSH_WAIT,
	ENC28J60_END_MAC_FLUSH_RETX,
	ENC28J60_TS_BUFFER_SIZE };
	
extern EE_UINT32 enc28j60_ts_buffer[ENC28J60_TS_BUFFER_SIZE];

__INLINE__ void __ALWAYS_INLINE__ EE_enc28j60_write_timestamp(EE_UINT32 id)
{
	enc28j60_ts_buffer[id] = EE_enc28j60_read_freetimer();
}

__INLINE__ EE_UINT32 __ALWAYS_INLINE__ EE_enc28j60_read_timestamp(EE_UINT32 id)
{
	return enc28j60_ts_buffer[id];
}

__INLINE__ void __ALWAYS_INLINE__ EE_enc28j60_reset_timestamp(void)
{
	int i;
	for(i=0; i<ENC28J60_TS_BUFFER_SIZE; i++)
		enc28j60_ts_buffer[i] = 0;
}

#else

#define EE_enc28j60_write_timestamp(id)
#define EE_enc28j60_read_timestamp(id)	-1
#define EE_enc28j60_reset_timestamp()

#endif

#endif	//__ENC28J60_TIME_DEBUG_H__