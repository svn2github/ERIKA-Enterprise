#include <mac/ozb_mac_internal.h>
#include <kal/ozb_kal.h>
#include <hal/ozb_radio.h>
#include <hal/ozb_rand.h>
#include <util/ozb_debug.h>
#ifdef OZB_DEBUG_LOG
#include <stdio.h> //TODO: REMOVE together with the sprintf() !!!!!
#endif

/******************************************************************************/
/*                          MAC Layer Private Data                            */
/******************************************************************************/
static ozb_mpdu_t rx_beacon;
static ozb_mpdu_t rx_data;
static ozb_mpdu_t rx_command;
static uint16_t rx_beacon_length;
static uint16_t rx_data_length;
static uint16_t rx_command_length;
static uint8_t beacon_payload[OZB_aMaxBeaconPayloadLength] 
	   COMPILER_ATTRIBUTE_FAR;
static uint8_t beacon_payload_length = 0; 

/******************************************************************************/
/*                          MAC Layer Public Data                             */
/******************************************************************************/
struct ozb_mac_flags_t ozb_mac_status = {
0, 0, 0, 0, 0, 0, 0, 0, 0
};
struct ozb_mac_pib_t ozb_mac_pib /*= {
	TODO: set a default values as already done for the phy_pib!	
}*/;
struct ozb_mac_gts_stat_t ozb_mac_gts_stat = {
	0, 
	OZB_MAC_SUPERFRAME_LAST_SLOT + 1,
	OZB_MAC_SUPERFRAME_FIRST_SLOT,
	0,
	OZB_MAC_SUPERFRAME_FIRST_SLOT,
	0
};
CQUEUE_DEFINE(ozb_mac_queue_gts, struct ozb_mac_frame_t,
	      OZB_MAC_GTS_QUEUE_SIZE, COMPILER_ATTRIBUTE_FAR);
CQUEUE_DEFINE(ozb_mac_queue_cap, struct ozb_mac_frame_t,
	      OZB_MAC_CAP_QUEUE_SIZE, COMPILER_ATTRIBUTE_FAR);


/******************************************************************************/
/*                                                                            */
/*                      MAC Layer Private Functions                           */
/*                                                                            */
/******************************************************************************/
/******************************************************************************/
/*                          MAC General Functions                             */
/******************************************************************************/
static void set_default_mac_pib(void)
{
	/* chris: TODO: move all this literals in some defines in the 
			mac const file as already done for the default pib 
			attribute of the PHY pib */
	ozb_mac_pib.macAckWaitDuration = 54; /* TODO: apply equation!! */
	ozb_mac_pib.macAssociatedPANCoord = 0;
	ozb_mac_pib.macAutoRequest = 1;
	ozb_mac_pib.macBattLifeExt = 0;
	ozb_mac_pib.macBattLifeExtPeriods = 6; /* TODO: apply equation!! */
	OZB_MAC_EXTD_ADDR_SET(ozb_mac_pib.macCoordExtendedAddress, 0x0, 0x0);
	ozb_mac_pib.macCoordShortAddress = 0xFFFF;
	ozb_mac_pib.macDSN = ozb_rand_8bit();
	ozb_mac_pib.macMaxBE = 5;
	ozb_mac_pib.macMaxCSMABackoffs = 4;
	ozb_mac_pib.macMaxFrameTotalWaitTime = 0; /* TODO: apply equation!! */
	ozb_mac_pib.macMaxFrameRetries = 3;
	ozb_mac_pib.macMinBE = 3;
	ozb_mac_pib.macMinLIFSPeriod = 40; /* TODO: apply table!! */
	ozb_mac_pib.macMinSIFSPeriod = 12; /* TODO: apply table!! */
	ozb_mac_pib.macPANId = 0xFFFF;
	ozb_mac_pib.macResponseWaitTime = 32;
	ozb_mac_pib.macRxOnWhenIdle = 0;
	ozb_mac_pib.macSecurityEnabled = 0;
	ozb_mac_pib.macShortAddress = 0xFFFF;
	ozb_mac_pib.macSyncSymbolOffset = 0; /* TODO: apply equation!! */
	ozb_mac_pib.macTimestampSupported = 0; /* TODO: apply equation!! */
	ozb_mac_pib.macTransactionPersistenceTime = 0x01F4;
	#ifndef OZB_DEVICE_DISABLE_OPTIONAL
	ozb_mac_pib.macGTSPermit = 1;
	#endif /* OZB_DEVICE_DISABLE_OPTIONAL */
	#ifndef OZB_RFD_DISABLE_OPTIONAL
	ozb_mac_pib.macAssociationPermit = 0;
	ozb_mac_pib.macBeaconPayload = NULL;
	ozb_mac_pib.macBeaconPayloadLenght = 0;
	ozb_mac_pib.macBeaconOrder = 15;
	ozb_mac_pib.macBeaconTxTime = 0x000000;
	ozb_mac_pib.macBSN = ozb_rand_8bit();
	ozb_mac_pib.macPromiscuousMode = 0;
	ozb_mac_pib.macSuperframeOrder = 15;
	#endif /* OZB_RFD_DISABLE_OPTIONAL */
}

/******************************************************************************/
/*                       MAC Frames Build Functions                           */
/******************************************************************************/
COMPILER_INLINE 
void set_frame_control(uint8_t *fcf, uint8_t frame_type, uint8_t security, 
		       uint8_t frame_pending, uint8_t ack_request, 
		       uint8_t panid_compress, uint8_t dst_addr_mode, 
		       uint8_t src_addr_mode, uint8_t frame_version) 
{
  	  fcf[0] = (panid_compress << 6) | (ack_request << 5) | 
		   (frame_pending << 4) | (security << 3) | (frame_type << 0);	
	  fcf[1] = (src_addr_mode << 6) | (frame_version << 4) | 
		   (dst_addr_mode << 2);
} 

COMPILER_INLINE 
uint8_t set_addressing_fields(uint8_t *af, enum ozb_mac_addr_mode_t dst_mode,
			      uint16_t dst_panid, void *dst_addr,
			      enum ozb_mac_addr_mode_t src_mode,
			      uint16_t src_panid, void *src_addr, 
			      uint8_t panid_compression) 
{
	uint8_t offset = 0;

	if (dst_mode == OZB_MAC_ADDRESS_SHORT) {
		memcpy(af + offset, &dst_panid, sizeof(uint16_t));
		offset += OZB_MAC_MPDU_PANID_SIZE;
		memcpy(af + offset, (uint8_t *) dst_addr,
		       OZB_MAC_MPDU_ADDRESS_SHORT_SIZE);
		offset += OZB_MAC_MPDU_ADDRESS_SHORT_SIZE;
	} else if (dst_mode == OZB_MAC_ADDRESS_EXTD) {
		memcpy(af + offset, &dst_panid, sizeof(uint16_t));
		offset += OZB_MAC_MPDU_PANID_SIZE;
		memcpy(af + offset, (uint8_t *) dst_addr,
		       OZB_MAC_MPDU_ADDRESS_EXTD_SIZE);
		offset += OZB_MAC_MPDU_ADDRESS_EXTD_SIZE;
	}
	if (src_mode == OZB_MAC_ADDRESS_SHORT) {
		if (panid_compression == 0) {
			memcpy(af + offset, &src_panid, sizeof(uint16_t));
			offset += OZB_MAC_MPDU_PANID_SIZE;
		}
		memcpy(af + offset, (uint8_t *) src_addr,
		       OZB_MAC_MPDU_ADDRESS_SHORT_SIZE);
		offset += OZB_MAC_MPDU_ADDRESS_SHORT_SIZE;
	} else if (src_mode == OZB_MAC_ADDRESS_EXTD) {
		if (panid_compression == 0) {
			memcpy(af + offset, &src_panid, sizeof(uint16_t));
			offset += OZB_MAC_MPDU_PANID_SIZE;
		}
		memcpy(af + offset, (uint8_t *) src_addr,
		       OZB_MAC_MPDU_ADDRESS_EXTD_SIZE);
		offset += OZB_MAC_MPDU_ADDRESS_EXTD_SIZE;
	}
	return offset;
}

COMPILER_INLINE 
uint8_t get_addressing_fields(uint8_t *af, enum ozb_mac_addr_mode_t dst_mode,
			      uint16_t *dst_panid, void *dst_addr,
			      enum ozb_mac_addr_mode_t src_mode,
			      uint16_t *src_panid, void *src_addr,
			      uint8_t panid_compression) 
{
	uint8_t offset = 0;

	if (dst_mode == OZB_MAC_ADDRESS_SHORT) {
		if (dst_panid != NULL)
			*dst_panid = af[offset];
		offset += OZB_MAC_MPDU_PANID_SIZE;
		if (dst_addr != NULL)
			memcpy((uint8_t *) dst_addr, af + offset, 
			       OZB_MAC_MPDU_ADDRESS_SHORT_SIZE);
		offset += OZB_MAC_MPDU_ADDRESS_SHORT_SIZE;
	} else if (dst_mode == OZB_MAC_ADDRESS_EXTD) {
		if (dst_panid != NULL)
			*dst_panid = af[offset];
		offset += OZB_MAC_MPDU_PANID_SIZE;
		if (dst_addr != NULL)
			memcpy((uint8_t *) dst_addr, af + offset, 
			       OZB_MAC_MPDU_ADDRESS_EXTD_SIZE);
		offset += OZB_MAC_MPDU_ADDRESS_EXTD_SIZE;
	}
	if (src_mode == OZB_MAC_ADDRESS_SHORT) {
		if (panid_compression == 0) {
			if (src_panid != NULL)
				*src_panid = af[offset];
			offset += OZB_MAC_MPDU_PANID_SIZE;
		}
		if (src_addr != NULL)
			memcpy((uint8_t *) src_addr, af + offset,
			       OZB_MAC_MPDU_ADDRESS_SHORT_SIZE);
		offset += OZB_MAC_MPDU_ADDRESS_SHORT_SIZE;
	} else if (src_mode == OZB_MAC_ADDRESS_EXTD) {
		if (panid_compression == 0) {
			if (src_panid != NULL)
				*src_panid = af[offset];
			offset += OZB_MAC_MPDU_PANID_SIZE;
		}
		if (src_addr != NULL)
			memcpy((uint8_t *) src_addr, af + offset,
			       OZB_MAC_MPDU_ADDRESS_EXTD_SIZE);
		offset += OZB_MAC_MPDU_ADDRESS_EXTD_SIZE;
	}
	return offset;
}

COMPILER_INLINE 
uint8_t set_superframe_specification(uint8_t *ss, uint8_t bo, uint8_t so, 
				     uint8_t final_cap_slot, uint8_t ble, 
				     uint8_t pan_coord,	uint8_t assoc_permit)
{
	ss[0] = (bo << 0) | (so << 4); 
	ss[1] = (final_cap_slot << 0) | (ble) << 4 | (pan_coord << 6)  | 
		(assoc_permit << 7);
	return OZB_MAC_MPDU_SUPERFRAME_SPEC_SIZE;
}

COMPILER_INLINE uint8_t set_pending_address_fields(uint8_t *pf)
{
	OZB_MAC_PENDING_ADDR_SPEC_SET_EMPTY(pf);
	/* 
	OZB_MAC_PENDING_ADDR_SPEC_SET_SHORTS(pf, 0);
	OZB_MAC_PENDING_ADDR_SPEC_SET_EXTDS(pf, 0);
	*/
	return 1;
}

COMPILER_INLINE uint8_t set_beacon_payload(uint8_t *bp)
{
	uint8_t len;
	
	ozb_kal_mutex_wait(MAC_MUTEX);
	if (beacon_payload_length > 0)
		memcpy(bp, beacon_payload, beacon_payload_length);
	len = beacon_payload_length;
	ozb_kal_mutex_signal(MAC_MUTEX);
	return len;
}

static uint8_t filtering_condition(uint8_t *fctrl, uint16_t dst_panid,
				   void *dst_addr, uint16_t src_panid)
{
	/* 3rd frame filter:  */
	/* TODO: check Frame Version invalid!! */
	if (OZB_MAC_FCTL_GET_FRAME_TYPE(fctrl) == OZB_MAC_TYPE_BEACON) {
		if (ozb_mac_pib.macPANId != OZB_MAC_PANID_BROADCAST && 
		    src_panid != ozb_mac_pib.macPANId) 
			return 0;
	} else {
		if (dst_panid != OZB_MAC_PANID_BROADCAST && 
		    dst_panid != ozb_mac_pib.macPANId) 
			return 0;
	}
	if ((OZB_MAC_FCTL_GET_FRAME_TYPE(fctrl) == OZB_MAC_TYPE_DATA || 
	    OZB_MAC_FCTL_GET_FRAME_TYPE(fctrl) == OZB_MAC_TYPE_COMMAND) &&
	    OZB_MAC_FCTL_GET_DST_ADDR_MODE(fctrl) == OZB_MAC_ADDRESS_NONE && 
	    OZB_MAC_FCTL_GET_SRC_ADDR_MODE(fctrl) != OZB_MAC_ADDRESS_NONE) {
		if (ozb_mac_status.is_pan_coordinator == OZB_FALSE || 
		    src_panid != ozb_mac_pib.macPANId)
			return 0;
	}
	if (OZB_MAC_FCTL_GET_DST_ADDR_MODE(fctrl) == OZB_MAC_ADDRESS_SHORT) {
		if ((*((ozb_mac_dev_addr_short_t*) dst_addr) != 
		    ozb_mac_pib.macShortAddress) && 
		    (*((ozb_mac_dev_addr_short_t*) dst_addr) !=
		    OZB_MAC_SHORT_ADDRESS_BROADCAST))
			return 0;
	} else if (OZB_MAC_FCTL_GET_DST_ADDR_MODE(fctrl)==OZB_MAC_ADDRESS_EXTD){
		if (!OZB_MAC_EXTD_ADDR_COMPARE_IMM(
			(ozb_mac_dev_addr_extd_ptr_t) dst_addr, 
			OZB_aExtendedAddress_high, OZB_aExtendedAddress_low))
			return 0;
	}
	return 1;
}

/******************************************************************************/
/*                              MAC Layer TASKs                               */
/******************************************************************************/
OZB_KAL_TASK_ASYNC(MAC_PROCESS_RX_BEACON, 25);
OZB_KAL_TASK_ASYNC(MAC_PROCESS_RX_DATA, 20);
OZB_KAL_TASK_ASYNC(MAC_PROCESS_RX_COMMAND, 20);

/* IMPORTANT NOTE: 
 * The mutexes that might be used in the context of possible PHY tasks,
 * that call the MAC notification functions, MUST be declared in the
 * file "mac/ozb_mac_mutexes.h" as body of the macro 
 * OZB_PHY_IMPORT_MAC_MUTEXES().
*/
OZB_KAL_MUTEX(MAC_RX_BEACON_MUTEX, MAC_PROCESS_RX_BEACON);
OZB_KAL_MUTEX(MAC_RX_DATA_MUTEX, MAC_PROCESS_RX_COMMAND);
OZB_KAL_MUTEX(MAC_RX_COMMAND_MUTEX, MAC_PROCESS_RX_DATA);

static void process_rx_beacon(void) 
{
	uint8_t s;
	uint8_t *bcn;
	uint16_t s_pan = 0; 
	ozb_mac_dev_addr_extd_t s_a; 

	if (ozb_kal_mutex_wait(MAC_RX_BEACON_MUTEX) < 0)
		return; /* TODO: manage error? */
	/* NOTE: Src Address is supposed to exist. NO Dst Address.
		 Assuming a pre-check in the dispatcher ? */
	bcn = OZB_MAC_MPDU_FRAME_CONTROL(rx_beacon);
	s = get_addressing_fields(OZB_MAC_MPDU_ADDRESSING_FIELDS(rx_beacon),
				OZB_MAC_ADDRESS_NONE, NULL, NULL,
				OZB_MAC_FCTL_GET_SRC_ADDR_MODE(bcn),
				&s_pan, (void *) s_a, 0);
	if (!filtering_condition(bcn, NULL, NULL, s_pan)) { 
		/* Drop the frame! */
		ozb_kal_mutex_signal(MAC_RX_BEACON_MUTEX);/*TODO:manage error?*/
		return;
	}
	bcn = OZB_MAC_MPDU_MAC_PAYLOAD(rx_beacon, s);
	ozb_mac_pib.macBeaconOrder = OZB_MAC_SF_SPEC_GET_BO(bcn); 
	ozb_mac_pib.macSuperframeOrder = OZB_MAC_SF_SPEC_GET_SO(bcn); 
	ozb_mac_gts_set_cap_end(OZB_MAC_SF_SPEC_GET_LAST_CAP_TSLOT(bcn));
	/*TODO: Use the BLE fiels w.r.t the std */
	ozb_mac_pib.macAssociationPermit=OZB_MAC_SF_SPEC_GET_ASSOC_PERMIT(bcn);
	/* TODO: read BO and SO and update the PIB!! */
	bcn += OZB_MAC_MPDU_SUPERFRAME_SPEC_SIZE;
	bcn += ozb_mac_gts_get_gts_fields(bcn); // <-- TODO: check return value
	/* TODO: compute FCS , use auto gen? */
	// consider 2 bytes in the following formula
	beacon_payload_length = rx_beacon_length - (bcn - rx_beacon);
	if (beacon_payload_length > 0)
		memcpy(beacon_payload, bcn, beacon_payload_length);		
	if (ozb_kal_mutex_signal(MAC_RX_BEACON_MUTEX) < 0)
		return; /* TODO: manage error? */
	ozb_mac_superframe_resync();
}

static void process_rx_data(void) 
{
	uint8_t s, len;
	uint8_t *data;
	uint16_t s_pan = 0, d_pan = 0; 
	ozb_mac_dev_addr_extd_t s_a, d_a; 

	if (ozb_kal_mutex_wait(MAC_RX_DATA_MUTEX) < 0)
		return; /* TODO: manage error? */
	data = OZB_MAC_MPDU_FRAME_CONTROL(rx_data);
	s = get_addressing_fields(OZB_MAC_MPDU_ADDRESSING_FIELDS(rx_data),
				  OZB_MAC_FCTL_GET_DST_ADDR_MODE(data),
				  &d_pan, (void *) d_a,
				  OZB_MAC_FCTL_GET_SRC_ADDR_MODE(data),
				  &s_pan, (void *) s_a, 
				  OZB_MAC_FCTL_GET_PANID_COMPRESS(data));
	if (!filtering_condition(data, d_pan, (void*) d_a, s_pan)){
		ozb_kal_mutex_signal(MAC_RX_DATA_MUTEX);/*TODO:manage error?*/
		return;
	}
	if (OZB_MAC_FCTL_GET_PANID_COMPRESS(data))
		s_pan = d_pan;
	len = rx_data_length - OZB_MAC_MPDU_FRAME_CONTROL_SIZE - 
	      OZB_MAC_MPDU_SEQ_NUMBER_SIZE - s;
	ozb_MCPS_DATA_indication(OZB_MAC_FCTL_GET_SRC_ADDR_MODE(data), 
				 s_pan, (void *) s_a,
				 OZB_MAC_FCTL_GET_DST_ADDR_MODE(data),
				 d_pan, (void *) d_a, len,
				 OZB_MAC_MPDU_MAC_PAYLOAD(rx_data, s), 
				 0 /*TODO: mpduLinkQuality*/,
				 *(OZB_MAC_MPDU_SEQ_NUMBER(rx_data))/*CHECK!*/,
				 0 /*TODO: timestamp!! */,
				 OZB_MAC_NULL_SECURITY_PARAMS_LIST);
	if (ozb_kal_mutex_signal(MAC_RX_DATA_MUTEX) < 0)
		return; /* TODO: manage error? */
}

static void process_rx_command(void) 
{
	if (ozb_kal_mutex_wait(MAC_RX_COMMAND_MUTEX) < 0)
		return; /* TODO: manage error? */
	if (ozb_kal_mutex_signal(MAC_RX_COMMAND_MUTEX) < 0)
		return; /* TODO: manage error? */
}

COMPILER_INLINE int8_t init_rx_tasks(void)
{
	int retv;

	retv = ozb_kal_init(0); 
	if (retv < 0)
		return retv;
	retv = ozb_kal_set_body(MAC_PROCESS_RX_BEACON, process_rx_beacon);
	if (retv < 0)
		return retv;
	retv = ozb_kal_set_body(MAC_PROCESS_RX_DATA, process_rx_data);
	if (retv < 0)
		return retv;
	retv = ozb_kal_set_body(MAC_PROCESS_RX_COMMAND, process_rx_command);
	if (retv < 0)
		return retv;
	return 1;
}

/******************************************************************************/
/*                                                                            */
/*                       MAC Layer Public Functions                           */
/*                                                                            */
/******************************************************************************/
/******************************************************************************/
/*                          MAC General Functions                             */
/******************************************************************************/
int8_t ozb_mac_init(void) 
{
	int8_t retv = 1;

	#ifdef OZB_DEBUG
	if (ozb_debug_init() < 0)
		return -OZB_MAC_ERR_DEBUG_INIT;
	#endif
	ozb_mac_status.mac_initialized = 0;
	ozb_mac_status.is_pan_coordinator = 0;
	ozb_mac_status.is_coordinator = 0;
	ozb_mac_status.is_associated = 0;
	ozb_mac_status.beacon_enabled = 0;
	ozb_mac_status.sf_initialized = 0;
	ozb_mac_status.sf_context = 0;
	ozb_rand_init();
	retv = ozb_phy_init();
	if (retv < 0)
		return retv;
	set_default_mac_pib();
	cqueue_clear(&ozb_mac_queue_gts);
	cqueue_clear(&ozb_mac_queue_cap);
	retv = init_rx_tasks();
	if (retv < 0)
		return retv;
	retv = ozb_mac_superframe_init();
	if (retv < 0)
		return retv;
	retv = ozb_mac_gts_init();
	if (retv < 0)
		return retv;
	//return -OZB_MAC_INIT_ERROR;
	ozb_mac_status.mac_initialized = 1;
	return 1;
}

int8_t ozb_mac_get_beacon_payload(uint8_t *data, uint8_t len)
{
	/* NOTE: mutex condition is guaranteed due to 
	 * task activation mechanism and the following flag */
	if (!ozb_mac_status.has_rx_beacon)
		return -100; //TODO: add error code 
	if (beacon_payload_length == 0)
		return 0;
	if (len > beacon_payload_length)
		len = beacon_payload_length;
	memcpy(data, beacon_payload, len);
	return (int8_t) len;
}


int8_t ozb_mac_set_beacon_payload(uint8_t *data, uint8_t len)
{
	if (len > OZB_aMaxBeaconPayloadLength)
		return -OZB_MAC_ERR_INVALID_LENGTH;
	ozb_kal_mutex_wait(MAC_MUTEX);
	if (len > 0)
		memcpy(beacon_payload, data, len);
	beacon_payload_length = len;
	ozb_kal_mutex_signal(MAC_MUTEX);
	return OZB_MAC_ERR_NONE;
}

void ozb_mac_perform_data_request(uint8_t src_mode, uint8_t dst_mode,
				  uint16_t dst_panid, void *dst_addr,
				  uint8_t len, uint8_t *payload,
				  uint8_t handle, uint8_t tx_opt /*,
				  uint8_t sec_lev, uint8_t key_id_mode,
				  uint8_t *key_src, uint8_t key_idx */)
{
	uint8_t s;
	struct {
		unsigned compress : 1;
		unsigned version : 1;
	} flag;
	struct ozb_mac_frame_t *frame;
	ozb_mac_dev_addr_extd_t e_addr;

	if (OZB_MAC_TX_OPTION_GTS(tx_opt) == OZB_TRUE) {
		if (!ozb_mac_superframe_has_tx_gts()) {
			ozb_MCPS_DATA_confirm(handle, OZB_MAC_INVALID_GTS, 0);
			return;
		}
		if (!ozb_mac_superframe_check_gts(len)) {
			//ozb_debug_print("DEVICE:  GTS CHECK FAIL ");
			ozb_MCPS_DATA_confirm(handle, OZB_MAC_INVALID_GTS, 0);
			return;
		} 
		/* Store in the GTS queue! */
		frame=(struct ozb_mac_frame_t*) cqueue_push(&ozb_mac_queue_gts);
		if (frame == 0) {
			//ozb_debug_print("DEVICE:  GTS QUEUE FULL!!! ");
			/* TODO: we have to choose a well formed reply
				 for the indication primitive (status=??) */
			ozb_MCPS_DATA_confirm(handle, OZB_MAC_INVALID_GTS, 0);
			return; 
		}
	} else { /* Store in the CSMA-CA queue */
		//ozb_debug_print("DEVICE:  CSMA QUEUE FULL!!! ");
		frame=(struct ozb_mac_frame_t*) cqueue_push(&ozb_mac_queue_cap);
		if (frame == 0) {
			/* TODO: we have to choose a well formed reply
				 for the indication primitive (status=??) */
			ozb_MCPS_DATA_confirm(handle, 
					      OZB_MAC_CHANNEL_ACCESS_FAILURE,0);
			return; 
		}
	}
	frame->msdu_handle = handle;
	/* Build the mpdu header (MHR) */
	memset(frame->mpdu, 0x0, sizeof(ozb_mpdu_t));
	flag.compress = (src_mode != OZB_MAC_ADDRESS_NONE && 
			 dst_mode != OZB_MAC_ADDRESS_NONE && 
			 dst_panid == ozb_mac_pib.macPANId) ?  1 : 0;
	flag.version = (/*TODO: if has security set (sec_level?) &&*/ 
		        len > OZB_aMaxMACSafePayloadSize) ?  1 : 0;
	set_frame_control(OZB_MAC_MPDU_FRAME_CONTROL(frame->mpdu), 
			  OZB_MAC_TYPE_DATA, 
			  0,/* TODO: Use security infos (sec_level, etc.) */
			  0, /* TODO: Use Pending List flag */
			  OZB_MAC_TX_OPTION_ACK(tx_opt), 
			  flag.compress, dst_mode, src_mode, flag.version);
	*(OZB_MAC_MPDU_SEQ_NUMBER(frame->mpdu)) = ozb_mac_pib.macDSN++;
	if (src_mode == OZB_MAC_ADDRESS_EXTD || 
	    (src_mode == OZB_MAC_ADDRESS_SHORT && 
	    (ozb_mac_pib.macShortAddress == OZB_MAC_SHORT_ADDRESS_USE_EXTD ||
	    ozb_mac_pib.macShortAddress == OZB_MAC_SHORT_ADDRESS_INVALID)))
		OZB_MAC_EXTD_ADDR_SET(e_addr, OZB_aExtendedAddress_high, 
				      OZB_aExtendedAddress_low);
	else /* TODO: can be short_none??? */
		memcpy(e_addr, &(ozb_mac_pib.macShortAddress), 
		       OZB_MAC_MPDU_ADDRESS_SHORT_SIZE);
	s = set_addressing_fields(OZB_MAC_MPDU_ADDRESSING_FIELDS(frame->mpdu),
				  dst_mode, dst_panid, dst_addr, 
				  src_mode, ozb_mac_pib.macPANId, 
			  	  (void *) e_addr, flag.compress);
	/* TODO: think to security infos? */
	/* Store the msdu (Mac Payload) */
	memcpy(OZB_MAC_MPDU_MAC_PAYLOAD(frame->mpdu, s), payload, len);
	/* TODO: compute FCS , use auto gen? */
	//*((uint16_t *) OZB_MAC_MPDU_MAC_FCS(bcn, s)) = 0;
	frame->mpdu_size = OZB_MAC_MPDU_FRAME_CONTROL_SIZE + 
			   OZB_MAC_MPDU_SEQ_NUMBER_SIZE + s + len /* + 
			   sizeof(uint16_t) */;
	if (OZB_MAC_TX_OPTION_GTS(tx_opt) == OZB_TRUE) 
		ozb_mac_superframe_gts_wakeup(); 
}

/******************************************************************************/
/*                       MAC Frames Build Functions                           */
/******************************************************************************/
uint8_t ozb_mac_create_beacon(ozb_mpdu_ptr_t bcn)
{
	uint8_t s;
	ozb_mac_dev_addr_extd_t e_addr;

	memset(bcn, 0x0, sizeof(ozb_mpdu_t));
	set_frame_control(OZB_MAC_MPDU_FRAME_CONTROL(bcn), 
			  OZB_MAC_TYPE_BEACON, 
			  ozb_mac_pib.macSecurityEnabled, 
			  0, /* TODO: Use Pending List flag */
			  0, 0, /* Zeros and ignored in case of Beacon */
			  OZB_MAC_ADDRESS_NONE, OZB_MAC_ADDRESS_SHORT,
			  ozb_mac_pib.macSecurityEnabled /*TODO: check std*/);
	*(OZB_MAC_MPDU_SEQ_NUMBER(bcn)) = ozb_mac_pib.macBSN++;
	if (ozb_mac_pib.macShortAddress == OZB_MAC_SHORT_ADDRESS_USE_EXTD) {
		OZB_MAC_EXTD_ADDR_SET(e_addr, OZB_MAC_DEVICE_EXTD_ADDRESS_HIGH,
				      OZB_MAC_DEVICE_EXTD_ADDRESS_LOW);
		s = set_addressing_fields(OZB_MAC_MPDU_ADDRESSING_FIELDS(bcn),
					  OZB_MAC_ADDRESS_NONE, 0, NULL, 
					  OZB_MAC_ADDRESS_EXTD, 
					  ozb_mac_pib.macPANId, (void*) e_addr,
					  0);
	} else {
		s = set_addressing_fields(OZB_MAC_MPDU_ADDRESSING_FIELDS(bcn),
					  OZB_MAC_ADDRESS_NONE, 0, NULL, 
					  OZB_MAC_ADDRESS_SHORT, 
					  ozb_mac_pib.macPANId, 
				  	  (void*)&(ozb_mac_pib.macShortAddress),
					  0);
	}
	/* TODO: think to security infos? */
	s += set_superframe_specification(OZB_MAC_MPDU_MAC_PAYLOAD(bcn, s),
					  ozb_mac_pib.macBeaconOrder, 
					  ozb_mac_pib.macSuperframeOrder, 
					  ozb_mac_gts_get_cap_end(), 
					  0, /*TODO: Use w.r.t the std */
					  ozb_mac_status.is_pan_coordinator, 
					  ozb_mac_pib.macAssociationPermit);
	s += ozb_mac_gts_set_gts_fields(OZB_MAC_MPDU_MAC_PAYLOAD(bcn, s));
	s += set_pending_address_fields(OZB_MAC_MPDU_MAC_PAYLOAD(bcn, s));
	s += set_beacon_payload(OZB_MAC_MPDU_MAC_PAYLOAD(bcn, s));
	/* TODO: compute FCS , use auto gen? */
	//*((uint16_t *) OZB_MAC_MPDU_MAC_FCS(bcn, s)) = 0;
	//s += OZB_MAC_MPDU_MHR_BASE_SIZE + OZB_MAC_MPDU_MFR_SIZE;
	s += OZB_MAC_MPDU_MHR_BASE_SIZE;
	return s;
}

/******************************************************************************/
/*                       MAC MPDU Parsing Functions                           */
/******************************************************************************/
void ozb_mac_parse_received_mpdu(uint8_t *psdu, uint8_t len)
{
	/* 1st frame filter: FCS */
	/* TODO: Checksum is done by the transceiver, fix this!!! */
	/* 2nd frame filter: promiscuous mode */
	if (ozb_mac_pib.macPromiscuousMode == OZB_TRUE)
		return; /* TODO: pass the frame to the upper layer! (see std) */
	/* TODO: perform some discarding action depending on the context :
		 What if I am coordinator? */
	switch (OZB_MAC_FCTL_GET_FRAME_TYPE(psdu)) {
	case OZB_MAC_TYPE_BEACON :
		if (ozb_mac_status.is_pan_coordinator || 
		    ozb_mac_status.is_coordinator)
			return; /* TODO: check if this is correct w.r.t std */
		/* TODO: make an extra compare, to see if Frame Control Field 
			 is valid for a beacon, no_dest address, a_src address*/
		if (ozb_kal_mutex_wait(MAC_RX_BEACON_MUTEX) < 0)
			return; /* TODO: manage error? */
		memcpy(rx_beacon, psdu, len);
		rx_beacon_length = len;
		ozb_kal_activate(MAC_PROCESS_RX_BEACON);
		if (ozb_kal_mutex_signal(MAC_RX_BEACON_MUTEX) < 0)
			return; /* TODO: manage error? */
		break;
	case OZB_MAC_TYPE_DATA :
		if (ozb_kal_mutex_wait(MAC_RX_DATA_MUTEX) < 0)
			return; /* TODO: manage error? */
		memcpy(rx_data, psdu, len);
		rx_data_length = len;
		ozb_kal_activate(MAC_PROCESS_RX_DATA);
		if (ozb_kal_mutex_signal(MAC_RX_DATA_MUTEX) < 0)
			return; /* TODO: manage error? */
		break;
	case OZB_MAC_TYPE_COMMAND :
		if (ozb_kal_mutex_wait(MAC_RX_COMMAND_MUTEX) < 0)
			return; /* TODO: manage error? */
		memcpy(rx_command, psdu, len);
		rx_command_length = len;
		ozb_kal_activate(MAC_PROCESS_RX_COMMAND);
		if (ozb_kal_mutex_signal(MAC_RX_COMMAND_MUTEX) < 0)
			return; /* TODO: manage error? */
		break;
	case OZB_MAC_TYPE_ACK :
		break;
	default:
		break;
	}
}

