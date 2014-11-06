#define HVMOP_set_param           0
#define HVMOP_get_param           1
struct xen_hvm_param {
    domid_t  domid;    /* IN */
    uint32_t index;    /* IN */
    uint64_t value;    /* IN/OUT */
};
typedef struct xen_hvm_param xen_hvm_param_t;

#define HVM_PARAM_STORE_PFN    1
#define HVM_PARAM_STORE_EVTCHN 2

#define XENSTORE_RING_SIZE 1024
typedef uint32_t XENSTORE_RING_IDX;
#define MASK_XENSTORE_IDX(idx) ((idx) & (XENSTORE_RING_SIZE-1))
struct xenstore_domain_interface {
    char req[XENSTORE_RING_SIZE]; /* Requests to xenstore daemon. */
    char rsp[XENSTORE_RING_SIZE]; /* Replies and async watch events. */
    XENSTORE_RING_IDX req_cons, req_prod;
    XENSTORE_RING_IDX rsp_cons, rsp_prod;
};

extern int HYPERVISOR_hvm_op(int what, struct xen_hvm_param *xhv);

static inline int hvm_get_parameter(int idx, uint64_t *value)
{
        struct xen_hvm_param xhv;
        int ret;

        xhv.domid = DOMID_SELF;
        xhv.index = idx;
        ret = HYPERVISOR_hvm_op(HVMOP_get_param, &xhv);
        if (ret < 0) {
                BUG();
        }
        *value = xhv.value;
        return ret;
}

void arch_init_xenbus(struct xenstore_domain_interface **xenstore_buf, uint32_t *store_evtchn) {
        uint64_t value;
        uint64_t xenstore_pfn;

        if (hvm_get_parameter(HVM_PARAM_STORE_EVTCHN, &value))
                BUG();

        *store_evtchn = (int)value;

        if(hvm_get_parameter(HVM_PARAM_STORE_PFN, &value))
                BUG();
        xenstore_pfn = (unsigned long)value;

        *xenstore_buf = pfn_to_virt(xenstore_pfn);
}
