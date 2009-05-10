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

/******************************************************************************/
/*                          MAC Layer Public Data                             */
/******************************************************************************/
struct ozb_mac_flags_t ozb_mac_status = {0, 0, 0, 0, 0};
struct ozb_mac_pib_t ozb_mac_pib /*= {
	TODO: set a default values as already done for the phy_pib!	
}*/;

/******************************************************************************/
/*                              MAC Layer TASK                                */
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
}

static void process_rx_data(void) 
{
}

static void process_rx_command(void) 
{
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
	OZB_SET_MAC_EXTD_ADDR(ozb_mac_pib.macCoordExtendedAddress, 0x0, 0x0);
	ozb_mac_pib.macCoordShortAddress = 0xFFFF;
	ozb_mac_pib.macDSN = ozb_rand_8bit();
	ozb_mac_pib.macMaxBE = 5;
	ozb_mac_pib.macMaxCSMABackoffs = 4;
	ozb_mac_pib.macMaxFrameTotalWaitTime = 0; /* TODO: apply equation!! */
	ozb_mac_pib.macMaxFrameRetries = 3;
	ozb_mac_pib.macMinBE = 3;
	ozb_mac_pib.macMinLIFSPeriod = 40; /* TODO: apply equation!! */
	ozb_mac_pib.macMinSIFSPeriod = 12; /* TODO: apply equation!! */
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
			      uint16_t src_panid, void *src_addr) 
{
	uint8_t offset = 0;

	if (dst_mode == OZB_MAC_ADDRESS_SHORT) {
		af[offset] = dst_panid;
		offset += OZB_MAC_MPDU_PANID_SIZE;
		memcpy(af + offset, (uint8_t *) dst_addr,
		       OZB_MAC_MPDU_ADDRESS_SHORT_SIZE);
		offset += OZB_MAC_MPDU_ADDRESS_SHORT_SIZE;
	} else if (dst_mode == OZB_MAC_ADDRESS_EXTD) {
		af[offset] = dst_panid;
		offset += OZB_MAC_MPDU_PANID_SIZE;
		memcpy(af + offset, (uint8_t *) dst_addr,
		       OZB_MAC_MPDU_ADDRESS_EXTD_SIZE);
		offset += OZB_MAC_MPDU_ADDRESS_EXTD_SIZE;
	}
	if (src_mode == OZB_MAC_ADDRESS_SHORT) {
		af[offset] = src_panid;
		offset += OZB_MAC_MPDU_PANID_SIZE;
		memcpy(af + offset, (uint8_t *) src_addr,
		       OZB_MAC_MPDU_ADDRESS_SHORT_SIZE);
		offset += OZB_MAC_MPDU_ADDRESS_SHORT_SIZE;
	} else if (src_mode == OZB_MAC_ADDRESS_EXTD) {
		af[offset] = src_panid;
		offset += OZB_MAC_MPDU_PANID_SIZE;
		memcpy(af + offset, (uint8_t *) src_addr,
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
	return 2;
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
	return 0;
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
	ozb_mac_status.is_coordinator= 0;
	ozb_mac_status.beacon_enabled = 0;
	ozb_mac_status.sf_initialized = 0;
	ozb_mac_status.sf_context = 0;
	ozb_rand_init();
	retv = ozb_phy_init();
	if (retv < 0)
		return retv;
	set_default_mac_pib();
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

/******************************************************************************/
/*                       MAC Frames Build Functions                           */
/******************************************************************************/
uint8_t ozb_mac_create_beacon(ozb_mpdu_ptr_t beacon)
{
	uint8_t s;

	memset(beacon, 0x0, sizeof(ozb_mpdu_t));
	set_frame_control(OZB_MAC_MPDU_FRAME_CONTROL(beacon), 
			  OZB_MAC_TYPE_BEACON, 
			  ozb_mac_pib.macSecurityEnabled, 
			  0, /* TODO: Use Pending List flag */
			  0, 0, /* Zeros and ignored in case of Beacon */
			  OZB_MAC_ADDRESS_NONE, OZB_MAC_ADDRESS_SHORT,
			  ozb_mac_pib.macSecurityEnabled /*TODO: check std*/);
	*OZB_MAC_MPDU_SEQ_NUMBER(beacon) = ozb_mac_pib.macBSN++;
	s = set_addressing_fields(OZB_MAC_MPDU_ADDRESSING_FIELDS(beacon),
				  OZB_MAC_ADDRESS_NONE, 0, NULL, 
				  OZB_MAC_ADDRESS_SHORT, ozb_mac_pib.macPANId, 
				  &(ozb_mac_pib.macShortAddress));
	/* TODO: think to security infos? */
	s += set_superframe_specification(OZB_MAC_MPDU_MAC_PAYLOAD(beacon, s),
					  ozb_mac_pib.macBeaconOrder, 
					  ozb_mac_pib.macSuperframeOrder, 
					  ozb_mac_gts_last_cap_slot(), 
					  0, /*TODO: Use w.r.t the std */
					  ozb_mac_status.is_coordinator, 
					  ozb_mac_pib.macAssociationPermit);
	s += ozb_mac_gts_set_gts_fields(OZB_MAC_MPDU_MAC_PAYLOAD(beacon, s));
	s += set_pending_address_fields(OZB_MAC_MPDU_MAC_PAYLOAD(beacon, s));
	s += set_beacon_payload(OZB_MAC_MPDU_MAC_PAYLOAD(beacon, s));
	/* TODO: compute FCS , use auto gen? */
	//*((uint16_t *) OZB_MAC_MPDU_MAC_FCS(beacon, s)) = 0;
	//s += OZB_MAC_MPDU_MHR_BASE_SIZE + OZB_MAC_MPDU_MFR_SIZE;
	s += OZB_MAC_MPDU_MHR_BASE_SIZE;
	return s;
}

/******************************************************************************/
/*                       MAC MPDU Parsing Functions                           */
/******************************************************************************/
void ozb_mac_parse_received_mpdu(uint8_t *psdu, uint8_t len)
{
	switch (OZB_MAC_MPDU_FRAME_CONTROL_GET_FRAME_TYPE(psdu)) {
	case OZB_MAC_TYPE_BEACON :
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




