#include <net/ozb_simple154.h>
#include <string.h>

struct ozb_simple154_flags_t {
	unsigned wait_confirm : 1;
	unsigned initialized : 1;
	unsigned coordinator : 1;
};

static struct ozb_simple154_flags_t flags = {0, 0, 0};
static int8_t mac_error = 0;
static int8_t last_error = 0;
static uint16_t coordinator_pan_id = 0;
static uint16_t coordinator_address = 0;
/* static uint8_t msdu_handle_id = 0; */
static void (*rx_callback) (int8_t, uint8_t*, uint8_t) = NULL;
static uint8_t rx_buffer[OZB_MAC_MAX_MSDU_SIZE];



#define RETURN_WITH_ERROR(e) 		\
do {					\
	last_error = (e);		\
	return (e);			\
} while (0)				\

void ozb_simple154_set_rx_callback(void (*func) (int8_t, uint8_t*, uint8_t))
{
	rx_callback = func;
}

int8_t ozb_simple154_get_mac_error(void)
{
	return mac_error;
}


int8_t ozb_simple154_init_coordinator(uint16_t coordinator_id, uint16_t pan_id,
				      uint8_t channel, uint8_t bo, uint8_t so)
{
	if (flags.initialized)
		RETURN_WITH_ERROR(-OZB_IEEE802154_ERR_ALREADYINIT);
	mac_error = ozb_mac_init(); 
	if (mac_error < 0) 
		RETURN_WITH_ERROR(-OZB_IEEE802154_ERR_INITMAC);
	
	mac_error = ozb_MLME_SET_request(OZB_MAC_SHORT_ADDRESS, 0, 
					 (void *) &coordinator_id);
	if (mac_error < 0) 
		RETURN_WITH_ERROR(-OZB_IEEE802154_ERR_SETADDR);
	/* TODO: channel scan phase */
	flags.wait_confirm = 1;		
	mac_error = ozb_MLME_START_request(pan_id, 	/* PanID */
					   channel, 	/* Logical Channel*/
					   0, 	/* Channel Page */
					   0, 	/* Srtart Time */
					   bo, 	/* BO */
					   so, 	/* SO */
					   OZB_TRUE,	/* PAN Coordinator */
					   0, 	/* Battery Life Ext */
					   OZB_FALSE,/* Coord. Realignment */
					   OZB_MAC_NULL_SECURITY_PARAMS_LIST,
					   OZB_MAC_NULL_SECURITY_PARAMS_LIST);
	if (mac_error < 0) 
		RETURN_WITH_ERROR(-OZB_IEEE802154_ERR_STARTMAC);
	while (flags.wait_confirm) ;	
	if (last_error < 0)
		return last_error;
	flags.initialized = 1;
	flags.coordinator = 1;
	coordinator_pan_id = pan_id;
	RETURN_WITH_ERROR(OZB_IEEE802154_ERR_NONE);
}

int8_t ozb_simple154_init_device(uint16_t device_id, uint16_t coordinator_id, 
				 uint16_t pan_id, uint8_t channel)
{
	uint8_t capability;

	if (flags.initialized)
		RETURN_WITH_ERROR(-OZB_IEEE802154_ERR_ALREADYINIT);
	mac_error = ozb_mac_init(); 
	if (mac_error < 0) 
		RETURN_WITH_ERROR(-OZB_IEEE802154_ERR_INITMAC);
	capability = ozb_mac_capability_information(OZB_FALSE, /*AltPanCoord*/
						    OZB_DEVICE_FFD, /*DevType*/
						    OZB_TRUE, /*PowerSource*/
						    OZB_TRUE, /*RxOn When Idle*/
						    OZB_FALSE, /*Security*/
						    OZB_TRUE); /*Allocate Addr*/
	flags.wait_confirm = 1;		
	mac_error = ozb_MLME_ASSOCIATE_request(channel,	   /* Logical Channel*/
					       0,          /* Channel Page */
					       OZB_MAC_ADDRESS_SHORT,/* mode */
					       pan_id, 	   /* CoordPanID */
					       (void*) &coordinator_id, 
					       capability, /* Capability Infos*/
			        	       OZB_MAC_NULL_SECURITY_PARAMS_LIST
					       ); 
	if (mac_error < 0) 
		RETURN_WITH_ERROR(-OZB_IEEE802154_ERR_ASSOCIATE);
	while (flags.wait_confirm) ;	
	if (last_error < 0)
		return last_error;
	/* NOTE: setting the device address irrespective of the association! */
	mac_error = ozb_MLME_SET_request(OZB_MAC_SHORT_ADDRESS, 0, 
				    (void *) &device_id);
	if (mac_error < 0) 
		RETURN_WITH_ERROR(-OZB_IEEE802154_ERR_SETADDR);
	flags.initialized = 1;
	flags.coordinator = 0;
	coordinator_address = coordinator_id;
	coordinator_pan_id = pan_id;
	RETURN_WITH_ERROR(OZB_IEEE802154_ERR_NONE);
}

int8_t ozb_simple154_send(uint8_t *data, uint8_t len, uint16_t dst_device_id, 
			  uint8_t use_gts)
{
	/* TODO: current implementation is non-blocking and ignore if success */
	if (!flags.initialized)
		RETURN_WITH_ERROR(-OZB_IEEE802154_ERR_NOTINIT);
	if (flags.coordinator && use_gts)
		RETURN_WITH_ERROR(-OZB_IEEE802154_ERR_NOTSUPPORTED);
	if (!flags.coordinator)
		dst_device_id = coordinator_address;
//	flags.wait_confirm = 1;		
	mac_error = ozb_MCPS_DATA_request(OZB_MAC_ADDRESS_SHORT,
					  OZB_MAC_ADDRESS_SHORT, 
					  coordinator_pan_id,
					  (void *) &dst_device_id, 
					  len, data,
					  0, /* msdu_handle_id, */
					  ozb_mac_set_tx_options(0, use_gts, 0),
					  OZB_MAC_NULL_SECURITY_PARAMS_LIST); 
	if (mac_error < 0) 
		RETURN_WITH_ERROR(-OZB_IEEE802154_ERR_DATAREQ);
	/* msdu_handle_id++; */
//	while (flags.wait_confirm) ;	
//	if (last_error < 0)
//		return last_error;
	RETURN_WITH_ERROR(OZB_IEEE802154_ERR_NONE);
}

int8_t ozb_simple154_gts_clear(void) 
{
	if (!flags.initialized)
		RETURN_WITH_ERROR(-OZB_IEEE802154_ERR_NOTINIT);
	if (!flags.coordinator)
		RETURN_WITH_ERROR(-OZB_IEEE802154_ERR_GTS_NOTCOORDINATOR);
	mac_error = ozb_mac_gts_db_clean();
	if (mac_error < 0)
		RETURN_WITH_ERROR(OZB_IEEE802154_ERR_GTS_MANIPULATION);
	RETURN_WITH_ERROR(OZB_IEEE802154_ERR_NONE);
}

int8_t ozb_simple154_gts_add(uint16_t device_id, uint8_t length, uint8_t dir)
{
	if (!flags.initialized)
		RETURN_WITH_ERROR(-OZB_IEEE802154_ERR_NOTINIT);
	if (!flags.coordinator)
		RETURN_WITH_ERROR(-OZB_IEEE802154_ERR_GTS_NOTCOORDINATOR);
	mac_error = ozb_mac_gts_db_add(device_id, length, dir);
	if (mac_error < 0)
		RETURN_WITH_ERROR(OZB_IEEE802154_ERR_GTS_MANIPULATION);
	RETURN_WITH_ERROR(OZB_IEEE802154_ERR_NONE);
}

/******************************************************************************/
/*                     MAC EVENTS (confirm, indication)                       */
/******************************************************************************/
int8_t ozb_MCPS_DATA_confirm(uint8_t msduHandle, enum ozb_mac_code_t status,
			     uint32_t Timestamp)
{
	/*
	#ifdef OZB_DEBUG_LOG
	char s[100];
	char s1[40];
	if (status == OZB_MAC_INVALID_GTS)
		return 1;
	ozb_debug_sprint_maccode(status, s1);
	sprintf(s, "MCPS_DATA_confirm(%d, %s,...)", msduHandle, s1);
	ozb_debug_print(s);
	#endif
	*/
	if (status == OZB_MAC_SUCCESS)
		last_error = -OZB_IEEE802154_ERR_DATACONFIRM;
	flags.wait_confirm = 0;
	return 1;
}

int8_t ozb_MCPS_DATA_indication(uint8_t SrcAddrMode, uint16_t SrcPANId,
				void *SrcAddr, uint8_t DstAddrMode,
				uint16_t DstPANId, void *DstAddr,
				uint8_t msduLength, uint8_t *msdu,
				uint8_t mpduLinkQuality, uint8_t DSN,
				uint32_t Timestamp, uint8_t SecurityLevel,
				uint8_t KeyIdMode, uint8_t *KeySource,
				uint8_t KeyIndex)
{
	/* TODO: solve mutex problem on test_packet due to race condition! */
	if (rx_callback != NULL && msduLength <= OZB_MAC_MAX_MSDU_SIZE) {
		memset(rx_buffer, 0x00, OZB_MAC_MAX_MSDU_SIZE);
		memcpy(rx_buffer, msdu, msduLength);
		rx_callback(OZB_IEEE802154_ERR_NONE, rx_buffer, msduLength);
	} 
	return 1;
}

int8_t ozb_MCPS_PURGE_confirm(uint8_t msduHandle, enum ozb_mac_code_t status)
{
	return 1;
}


int8_t ozb_MLME_ASSOCIATE_confirm(ozb_mac_dev_addr_short_t AssocShortAddress,
				  enum ozb_mac_code_t status,
				  uint8_t SecurityLevel, uint8_t KeyIdMode,
				  uint8_t *KeySource, uint8_t KeyIndex)
{
	mac_error = ozb_MLME_SET_request(OZB_MAC_SHORT_ADDRESS, 0, 
				    (void *) &AssocShortAddress);
	if (mac_error < 0 || status != OZB_MAC_SUCCESS) 
		last_error = -OZB_IEEE802154_ERR_ASSOCIATE;
	flags.wait_confirm = 0;
	return 1;
}

#ifndef OZB_RFD_DISABLE_OPTIONAL
int8_t ozb_MLME_ASSOCIATE_indication(ozb_mac_dev_addr_extd_t DeviceAddress,
				     uint8_t CapabilityInformation,
				     uint8_t SecurityLevel, uint8_t KeyIdMode,
				     uint8_t *KeySource, uint8_t KeyIndex)
{
	return 1;
}

#endif /* OZB_RFD_DISABLE_OPTIONAL */


int8_t ozb_MLME_DISASSOCIATE_confirm(enum ozb_mac_code_t status,
				     uint8_t DeviceAddrMode,
				     uint16_t DevicePANId,
				     ozb_mac_dev_addr_t DeviceAddress)
{
	return 1;
}

int8_t ozb_MLME_DISASSOCIATE_indication(ozb_mac_dev_addr_extd_t DeviceAddress,
					uint8_t DisassociateReason,
					uint8_t SecurityLevel, 
					uint8_t KeyIdMode, uint8_t *KeySource,
					uint8_t KeyIndex)
{
	return 1;
}


int8_t ozb_MLME_BEACON_NOTIFY_indication(uint8_t BSN,
					 struct ozb_pan_des_t PANDescriptor,
					 uint8_t PendAddrSpec,
		 /*TODO: list? how?*/	 ozb_mac_dev_addr_t *AddrList, 
					 uint8_t sduLength, uint8_t *sdu)
{
	return 1;
}

int8_t ozb_MLME_GET_confirm(enum ozb_mac_code_t status,
			    enum ozb_mac_pib_id_t PIBAttribute,
	/*TODO: enough?*/   uint16_t PIBAttributeIndex, 
			    void *PIBAttributeValue)
{
	return 1;
}

#ifndef OZB_DEVICE_DISABLE_OPTIONAL
int8_t ozb_MLME_GTS_confirm(uint8_t GTSCharacteristics, 
			    enum ozb_mac_code_t status)
{
	return 1;
}

int8_t ozb_MLME_GTS_indication(ozb_mac_dev_addr_short_t DeviceAddress,
			       uint8_t GTSCharacteristics,
			       uint8_t SecurityLevel, uint8_t KeyIdMode,
			       uint8_t *KeySource, uint8_t KeyIndex)
{
	return 1;
}
#endif /* OZB_DEVICE_DISABLE_OPTIONAL */

#ifndef OZB_RFD_DISABLE_OPTIONAL
int8_t ozb_MLME_ORPHAN_indication(ozb_mac_dev_addr_extd_t OrphanAddress,
				  uint8_t SecurityLevel, uint8_t KeyIdMode,
				  uint8_t *KeySource, uint8_t KeyIndex)
{
	return 1;
}

#endif /* OZB_RFD_DISABLE_OPTIONAL */

int8_t ozb_MLME_RESET_confirm(enum ozb_mac_code_t status)
{
	return 1;
}

#ifndef OZB_DEVICE_DISABLE_OPTIONAL

int8_t ozb_MLME_RX_ENABLE_confirm(enum ozb_mac_code_t status)
{
	return 1;
}
#endif /* OZB_DEVICE_DISABLE_OPTIONAL */

int8_t ozb_MLME_SCAN_confirm(enum ozb_mac_code_t status, uint8_t ScanType,
			     uint8_t ChannelPage, uint32_t UnscannedChannels,
/*TODO: good represent.?*/   uint16_t ResultListSize, uint8_t *EnergyDetectList,
			     struct ozb_pan_des_t *PANDescriptorList)
{
	return 1;
}

int8_t ozb_MLME_COMM_STATUS_indication(uint16_t PANId, uint8_t SrcAddrMode,
				       ozb_mac_dev_addr_t SrcAddr,
				       uint8_t DstAddrMode,
				       ozb_mac_dev_addr_t DstAddr,
				       enum ozb_mac_code_t status,
				       uint8_t SecurityLevel, uint8_t KeyIdMode,
				       uint8_t KeySource, uint8_t KeyIndex)
{
	return 1;
}

int8_t ozb_MLME_SET_confirm(enum ozb_mac_code_t status,
			    enum ozb_mac_pib_id_t PIBAttribute,
        /*TODO: enough?*/   uint16_t PIBAttributeIndex)
{
	flags.wait_confirm = 0;
	return 1;
}

#ifndef OZB_RFD_DISABLE_OPTIONAL
int8_t ozb_MLME_START_confirm(enum ozb_mac_code_t status)
{
	if (status != OZB_MAC_SUCCESS) 
		last_error = -OZB_IEEE802154_ERR_STARTMAC;
	flags.wait_confirm = 0;
	return 1;
}
#endif /* OZB_RFD_DISABLE_OPTIONAL */

int8_t ozb_MLME_SYNC_LOSS_indication(enum ozb_mac_code_t LossReason,
				     uint8_t PANId, uint8_t LogicalChannel,
				     uint8_t ChannelPage, uint8_t SecurityLevel,
				     uint8_t KeyIdMode, uint8_t *KeySource,
				     uint8_t KeyIndex)
{
	return 1;
}

int8_t ozb_MLME_POLL_confirm(enum ozb_mac_code_t status)
{
	return 1;
}


