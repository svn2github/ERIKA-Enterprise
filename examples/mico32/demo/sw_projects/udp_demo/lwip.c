#include "ee_lwip_timers.h"

#include <ee.h>
#include <lwip/opt.h>
#include <hal/lwip_ethernet.h>
#include <arch/init.h>
#include <netif/etharp.h>


#include <MicoMacros.h>


/* Main network structure */
static struct netif netif;
/* Used to avoid useless ActivateTask while we don't disable interrupts */
static volatile int irq_pending;
static struct ee_lwip_timers timers;


/* Timer interrupt callback */
static void lwip_timer_tick(void)
{
    EE_UINT16 pending = ee_lwip_increment_timers(&timers);
    if (pending != 0)
        ActivateTask(LwipPeriodic);

    
    if (EE_enc28j60_pending_interrupt()) {
        /* We should mask ENC28J60 interrupts on the GPIO */
        /* EE_enc28j60_mask_interrupts(); */
        if (! irq_pending) {
            irq_pending = 1;
            ActivateTask(LwipReceive);
        }
    }
}


/* lwIP task for timers */
TASK(LwipPeriodic)
{
    EE_UINT16 pending;

    GetResource(LwipMutex);
    /* The access to the `pending' field must be protected from
     * interferences by the timer ISR */
    EE_hal_disableIRQ();
    pending = timers.pending;
    timers.pending = 0;
    EE_hal_enableIRQ();
    ee_lwip_maybe_call_tcp_timers(pending);
    ee_lwip_maybe_call_arp_timer(pending);
    ReleaseResource(LwipMutex);
}


/* lwIP task for handling incoming packets */
TASK(LwipReceive)
{
    GetResource(LwipMutex);
    /* We are assuming that the only interrupt source is an incoming packet */
    while (EE_enc28j60_pending_interrupt()) {
        LWIP_DEBUGF(NETIF_DEBUG | LWIP_DBG_TRACE,
            ("Got an Ethernet packet at 0x%04x\n", ReadETHReg(EIR).Val));
        ethernetif_input(&netif);
    }
    /* We should enable interrupts  */
    /* EE_enc28j60_unmask_interrupts(); */
    /* There is no race condition, as if an interrupt has become pending, it
       will be served at the next timer tick */
    irq_pending = 0;
    ReleaseResource(LwipMutex);
}


/**
 * lwIP initialization
 * This function must be called with interrupt disabled to avoid interferences
 * with the lwIP mutex.  In this way it can be called from main().
 */
void init_lwip(void)
{
    struct ip_addr my_ipaddr, netmask, gw;
    static struct ethernetif my_ethernetif;

    /* Initialize lwip */
    ee_lwip_init();
    
    /* Initialize the network interface and bring it online */
    IP4_ADDR(&my_ipaddr, MY_IPADDR_BYTE1, MY_IPADDR_BYTE2,
        MY_IPADDR_BYTE3, MY_IPADDR_BYTE4);
    IP4_ADDR(&netmask, MY_NETMASK_BYTE1, MY_NETMASK_BYTE2,
        MY_NETMASK_BYTE3, MY_NETMASK_BYTE4);
    IP4_ADDR(&gw, MY_GATEWAY_ADDR_BYTE1, MY_GATEWAY_ADDR_BYTE2,
        MY_GATEWAY_ADDR_BYTE3, MY_GATEWAY_ADDR_BYTE4);
    netif_add(&netif, &my_ipaddr, &netmask, &gw,
        (void*)&my_ethernetif, ethernetif_init, ethernet_input);
    netif_set_default(&netif);
    netif_set_up(&netif);

    /* Set up the timer for polling and timeouts */
    EE_timer_uwl_init(MILLISECONDS_TO_TICKS(EE_LWIP_TIMER_PERIOD_MS),
        MICO32_TIMER_CONTROL_INT_BIT_MASK | MICO32_TIMER_CONTROL_CONT_BIT_MASK);
    EE_timer_uwl_set_ISR_callback(lwip_timer_tick);
    EE_timer_uwl_on();
}
