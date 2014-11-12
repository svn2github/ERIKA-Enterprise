#include "xenstore.h"

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

static volatile int req_id = 0;

extern int HYPERVISOR_hvm_op(int what, struct xen_hvm_param *xhv);

static inline int hvm_get_parameter(int idx, uint64_t *value)
{
        struct xen_hvm_param xhv;
        int ret;

        xhv.domid = DOMID_SELF;
        xhv.index = idx;
        ret = HYPERVISOR_hvm_op(HVMOP_get_param, &xhv);
        if (ret < 0) {
		printk("EE: ERROR: cannot get parameter\n");
		goto out;
        }
        *value = xhv.value;
out:
        return ret;
}

void arch_init_xenbus(struct xenstore_domain_interface **xenstore_buf, uint32_t *store_evtchn) {
        uint64_t value;
        uint64_t xenstore_pfn;

	if (hvm_get_parameter(HVM_PARAM_STORE_EVTCHN, &value)) {
		printk("EE: ERROR: cannot get xenstore evtchn\n");
		return;
	}

        *store_evtchn = (int)value;

        if (hvm_get_parameter(HVM_PARAM_STORE_PFN, &value)) {
		printk("EE: ERROR: cannot get xenstore pfn\n");
		return;
	}
        xenstore_pfn = value;

        *xenstore_buf = pfn_to_virt(xenstore_pfn);
}

int xenstore_write_request(char *message, int length)
{
	int i;
	if (length > XENSTORE_RING_SIZE)
		return -1;
	for (i = xenstore_buf->req_prod ; length > 0 ; i++, length--) {
		XENSTORE_RING_IDX data;
		do {
			data = i - xenstore_buf->req_cons;
			mb();
		} while (data >= sizeof(xenstore_buf->req));
		xenstore_buf->req[MASK_XENSTORE_IDX(i)] = *message;
		message++;
	}
	wmb();
	xenstore_buf->req_prod = i;
	return 0;
}

int xenstore_read_response(char *message, int length)
{
	int i;
	for (i = xenstore_buf->rsp_cons ; length > 0 ; i++, length--) {
		XENSTORE_RING_IDX data;
		do {
			data = xenstore_buf->rsp_prod - i;
			mb();
		} while (data == 0);
		*message = xenstore_buf->rsp[MASK_XENSTORE_IDX(i)];
		message++;
	}
	xenstore_buf->rsp_cons = i;
	return 0;
}

int strlnx(char *s)
{
        const char *sc;
        for (sc = s; *sc != '\0' && *sc != '\n' ; ++sc);
        return (int)(sc - s);
}


int xenstore_write(char *key, char *value)
{
	int key_length = strlnx(key);
	int value_length = strlnx(value);
	struct xsd_sockmsg msg;

	msg.type = XS_WRITE;
	msg.req_id = req_id;
	msg.tx_id = 0;
	msg.len = 1 + key_length + value_length;
	xenstore_write_request((char *)&msg, sizeof(msg));
	/*
	 * NOTE: key must be null-terminated, but value
	 *       must NOT be null-terminated, or the
	 *       inserted value will include trailing
	 *       characters...
	 */
	xenstore_write_request(key, key_length + 1);
	xenstore_write_request(value, value_length);
	NOTIFY();
	xenstore_read_response((char *)&msg, sizeof(msg));
	IGNORE(msg.len);
	if (msg.req_id != req_id++)
		return -1;

	return 0;
}

int xenstore_read(char *key, char *value, int value_length)
{
	int key_length = strlnx(key);
	struct xsd_sockmsg msg;
	msg.type = XS_READ;
	msg.req_id = req_id;
	msg.tx_id = 0;
	msg.len = 1 + key_length;
	xenstore_write_request((char *)&msg, sizeof(msg));
	xenstore_write_request(key, key_length + 1);
	NOTIFY();
	xenstore_read_response((char *)&msg, sizeof(msg));
	if (msg.req_id != req_id++) {
		IGNORE(msg.len);
		return -1;
	}
	if (value_length >= msg.len) {
		xenstore_read_response(value, msg.len);
		return 0;
	}
	xenstore_read_response(value, value_length);
	IGNORE(msg.len - value_length);
	return -2;
}
