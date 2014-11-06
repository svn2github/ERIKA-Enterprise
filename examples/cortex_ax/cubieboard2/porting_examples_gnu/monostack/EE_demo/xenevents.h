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

#define SCHEDOP_block		1
#define SCHEDOP_yield		0
