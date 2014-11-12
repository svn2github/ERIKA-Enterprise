#ifndef _XENSTORE_H_
#define _XENSTORE_H_

typedef uint32_t XENSTORE_RING_IDX;

struct xsd_sockmsg
{
    uint32_t type;  /* XS_??? */
    uint32_t req_id;/* Request identifier, echoed in daemon's response.  */
    uint32_t tx_id; /* Transaction id (0 if not related to a transaction). */
    uint32_t len;   /* Length of data following this. */

    /* Generally followed by nul-terminated string(s). */
};


enum xsd_sockmsg_type
{
    XS_DEBUG,
    XS_DIRECTORY,
    XS_READ,
    XS_GET_PERMS,
    XS_WATCH,
    XS_UNWATCH,
    XS_TRANSACTION_START,
    XS_TRANSACTION_END,
    XS_INTRODUCE,
    XS_RELEASE,
    XS_GET_DOMAIN_PATH,
    XS_WRITE,
    XS_MKDIR,
    XS_RM,
    XS_SET_PERMS,
    XS_WATCH_EVENT,
    XS_ERROR,
    XS_IS_DOMAIN_INTRODUCED,
    XS_RESUME,
    XS_SET_TARGET,
    XS_RESTRICT,
    XS_RESET_WATCHES
};

struct evtchn_send {
    /* IN parameters. */
    evtchn_port_t port;
};
typedef struct evtchn_send evtchn_send_t;

#define NOTIFY()							\
	do {								\
		evtchn_send_t event;					\
		event.port = store_evtchn;				\
		if (HYPERVISOR_event_channel_op(EVTCHNOP_send, &event))	\
			printk("EE: ERROR: xenstore send\n");		\
	} while(0);

#define IGNORE(n)							\
	do {								\
		char buffer[XENSTORE_RING_SIZE];			\
		xenstore_read_response(buffer, n);			\
	} while(0);


#endif /*_XENSTORE_H_*/
