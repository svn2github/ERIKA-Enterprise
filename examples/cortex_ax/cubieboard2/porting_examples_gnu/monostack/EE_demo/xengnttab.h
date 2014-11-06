#ifndef _ERIKA_XEN_GNTTAB_
#define _ERIKA_XEN_GNTTAB_

#define GNTTABOP_setup_table	2
#define GTF_permit_access	(1U<<0)
typedef short int16_t;

struct grant_entry_header {
    uint16_t flags;
    domid_t  domid;
};
typedef struct grant_entry_header grant_entry_header_t;

typedef uint32_t grant_ref_t;

#if 0
union grant_entry_v2 {
    grant_entry_header_t hdr;

    struct {
        grant_entry_header_t hdr;
        uint32_t pad0;
        uint64_t frame;
    } full_page;
    struct {
        grant_entry_header_t hdr;
        uint16_t page_off;
        uint16_t length;
        uint64_t frame;
    } sub_page;

    struct {
        grant_entry_header_t hdr;
        domid_t trans_domid;
        uint16_t pad0;
        grant_ref_t gref;
    } transitive;

    uint32_t __spacer[4]; /* Pad to a power of two */
};
typedef union grant_entry_v2 grant_entry_v2_t;
typedef grant_entry_v2_t grant_entry_t;
#endif

struct grant_entry_v1 {
    /* GTF_xxx: various type and flag information.  [XEN,GST] */
    uint16_t flags;
    /* The domain being granted foreign privileges. [GST] */
    domid_t  domid;
    /*
     * GTF_permit_access: Frame that @domid is allowed to map and access. [GST]
     * GTF_accept_transfer: Frame whose ownership transferred by @domid. [XEN]
     */
    uint32_t frame;
};
typedef struct grant_entry_v1 grant_entry_v1_t;
typedef grant_entry_v1_t grant_entry_t;

struct gnttab_setup_table {
    /* IN parameters. */
    domid_t  dom;
    uint32_t nr_frames;
    /* OUT parameters. */
    int16_t  status;              /* => enum grant_status */
    unsigned long *frame_list;
};

#endif /*_ERIKA_XEN_GNTTAB_*/
