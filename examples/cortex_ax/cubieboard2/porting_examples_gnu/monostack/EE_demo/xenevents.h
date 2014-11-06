#define EVTCHNOP_bind_interdomain 0
#define EVTCHNOP_bind_virq        1
#define EVTCHNOP_bind_pirq        2
#define EVTCHNOP_close            3
#define EVTCHNOP_send             4
#define EVTCHNOP_status           5
#define EVTCHNOP_alloc_unbound    6
#define EVTCHNOP_bind_ipi         7
#define EVTCHNOP_bind_vcpu        8
#define EVTCHNOP_unmask           9
#define EVTCHNOP_reset           10
#define EVTCHNOP_init_control    11
#define EVTCHNOP_expand_array    12
#define EVTCHNOP_set_priority    13

/*
 * EVTCHNOP_alloc_unbound: Allocate a port in domain <dom> and mark as
 * accepting interdomain bindings from domain <remote_dom>. A fresh port
 * is allocated in <dom> and returned as <port>.
 * NOTES:
 *  1. If the caller is unprivileged then <dom> must be DOMID_SELF.
 *  2. <rdom> may be DOMID_SELF, allowing loopback connections.
 */
struct evtchn_alloc_unbound {
    /* IN parameters */
    domid_t dom, remote_dom;
    /* OUT parameters */
    evtchn_port_t port;
};
typedef struct evtchn_alloc_unbound evtchn_alloc_unbound_t;

struct evtchn_bind_vcpu {
    /* IN parameters. */
    evtchn_port_t port;
    uint32_t vcpu;
};
typedef struct evtchn_bind_vcpu evtchn_bind_vcpu_t;

#define EVTCHNOP_unmask           9
struct evtchn_unmask {
        /* IN parameters. */
        evtchn_port_t port;
};
typedef struct evtchn_unmask evtchn_unmask_t;

#define SCHEDOP_block		1
#define SCHEDOP_yield		0

#define smp_processor_id() 0

static __inline__ int test_and_set_bit(int nr, volatile void * addr)
{
        unsigned long *tmp = (unsigned long *)addr;
        int x = tmp[nr >> 5] & (1 << (nr & 0x1f));
        tmp[nr >> 5] |= (1 << (nr & 0x1f));
        return x;
}

static __inline__ int synch_test_and_set_bit(int nr, volatile void * addr)
{
        //TODO:
        return test_and_set_bit(nr, addr);
}

#define test_bit(nr,addr) (((unsigned long *)addr)[nr >> 5] & (1 << (nr & 0x1f)))
#define synch_test_bit(nr,addr) test_bit(nr, addr)

#define force_evtchn_callback(void) do {} while(0)

static inline void unmask_evtchn(uint32_t port)
{
    shared_info_t *s = HYPERVISOR_shared_info;
    vcpu_info_t *vcpu_info = &s->vcpu_info[smp_processor_id()];

    synch_clear_bit(port, &s->evtchn_mask[0]);

    if (  synch_test_bit        (port,    &s->evtchn_pending[0]) &&
         !synch_test_and_set_bit(port / (sizeof(unsigned long) * 8),
              &vcpu_info->evtchn_pending_sel) )
    {
        vcpu_info->evtchn_upcall_pending = 1;
        force_evtchn_callback();
    }
}
