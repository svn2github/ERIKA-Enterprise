#ifndef __ee_lwip_timers_h__
#define __ee_lwip_timers_h__

#include <ee.h>
#include <lwip/tcp.h>
#include <netif/etharp.h>

#define EE_LWIP_TIMER_PERIOD_MS 2U

#define EE_LWIP_ARP_PERIOD      (ARP_TMR_INTERVAL / EE_LWIP_TIMER_PERIOD_MS)
#define EE_LWIP_TCP_FAST_PERIOD (TCP_FAST_INTERVAL / EE_LWIP_TIMER_PERIOD_MS)
#define EE_LWIP_TCP_SLOW_PERIOD (TCP_SLOW_INTERVAL / EE_LWIP_TIMER_PERIOD_MS)

/* Masks for `pending' in struct ee_lwip_timers */
#define EE_LWIP_TIMER_ARP       1
#define EE_LWIP_TIMER_TCP_FAST  2
#define EE_LWIP_TIMER_TCP_SLOW  4

struct ee_lwip_timers
{
    EE_UINT16 arp_ticks;
#if LWIP_TCP
    EE_UINT16 tcp_fast_ticks;
    EE_UINT16 tcp_slow_ticks;
#endif
    /** Bit mask indicating which timer callback is to be called */
    volatile EE_UINT16 pending;
};

#if LWIP_TCP
__INLINE__ EE_UINT16 ee_lwip_update_tcp_timers(struct ee_lwip_timers *tmrs,
    EE_UINT16 pending);
__INLINE__ void ee_lwip_maybe_call_tcp_timers(EE_UINT16 pending);
#else
#define ee_lwip_update_tcp_timers(tmrs, pending) (pending)
#define ee_lwip_maybe_call_tcp_timers(pending)
#endif

/**
 * @brief Increment timer ticks and update the pending status.
 * This function must be called with interrupts disabled.
 * @return the new pending status
 */
__INLINE__ EE_UINT16 ee_lwip_increment_timers(struct ee_lwip_timers *tmrs)
{
    /* Keep a copy of pending, which is volatile */
    EE_UINT16 pending = tmrs->pending;
    tmrs->arp_ticks += 1;
    if (tmrs->arp_ticks >= EE_LWIP_ARP_PERIOD) {
        tmrs->arp_ticks = 0;
        pending |= EE_LWIP_TIMER_ARP;
    }
    pending = ee_lwip_update_tcp_timers(tmrs, pending);
    tmrs->pending = pending;
    return pending;
}

#if LWIP_TCP
/** Update TCP timers, but don't modify the pending field in the struct. */
__INLINE__ EE_UINT16 __ALWAYS_INLINE__ ee_lwip_update_tcp_timers(
    struct ee_lwip_timers *tmrs, EE_UINT16 pending)
{
    tmrs->tcp_fast_ticks += 1;
    if (tmrs->tcp_fast_ticks >= EE_LWIP_TCP_FAST_PERIOD) {
        tmrs->tcp_fast_ticks = 0;
        pending |= EE_LWIP_TIMER_TCP_FAST;
    }
    tmrs->tcp_slow_ticks += 1;
    if (tmrs->tcp_slow_ticks >= EE_LWIP_TCP_SLOW_PERIOD) {
        tmrs->tcp_slow_ticks = 0;
        pending |= EE_LWIP_TIMER_TCP_SLOW;
    }
    return pending;
}

/** Call TCP timer callbacks if needed */
__INLINE__ void __ALWAYS_INLINE__ ee_lwip_maybe_call_tcp_timers(
    EE_UINT16 pending)
{
    if (pending & EE_LWIP_TIMER_TCP_FAST)
        tcp_fasttmr();
    if (pending & EE_LWIP_TIMER_TCP_SLOW)
        tcp_slowtmr();
}

#endif /* LWIP_TCP */

/** Call ARP timer callback if needed */
__INLINE__ void __ALWAYS_INLINE__ ee_lwip_maybe_call_arp_timer(
    EE_UINT16 pending)
{
    if (pending & EE_LWIP_TIMER_ARP)
        etharp_tmr();
}

#endif /* __ee_lwip_timers_h__ */
