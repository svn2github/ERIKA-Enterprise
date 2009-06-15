#include <mac/uwl_mac_internal.h>
#include <util/uwl_debug.h>
#ifdef UWL_DEBUG_LOG
#include <stdio.h> //TODO: REMOVE together with the sprintf() !!!!!
#endif

#ifndef UWL_TEST_DEVICE_ADDRESS
#define UWL_TEST_DEVICE_ADDRESS 0x0002
#endif

int8_t uwl_MLME_ASSOCIATE_request(uint8_t LogicalChannel, uint8_t ChannelPage,
				  uint8_t CoordAddrMode, uint16_t CoordPANId,
				  void *CoordAddress,
				  uint8_t CapabilityInformation,
				  uint8_t SecurityLevel, uint8_t KeyIdMode,
				  uint8_t *KeySource, uint8_t KeyIndex)
{
	#ifdef UWL_DEBUG_LOG
	char s[100];
	sprintf(s, "MLME_ASSOCIATE_request(panid=%u ...)", CoordPANId);
	uwl_debug_print(s);
	#endif

	if (!uwl_mac_status.mac_initialized)
		return -UWL_MAC_ERR_NOT_INITIALIZED;
	switch (CoordAddrMode) {
	case UWL_MAC_ADDRESS_SHORT :
		memcpy(&(uwl_mac_pib.macCoordShortAddress), CoordAddress, 
		       sizeof(uwl_mac_dev_addr_short_t));
		break;
	case UWL_MAC_ADDRESS_EXTD :
		memcpy(&(uwl_mac_pib.macCoordExtendedAddress), CoordAddress, 
		       sizeof(uwl_mac_dev_addr_extd_t));
		break;
	default:
		uwl_MLME_ASSOCIATE_confirm(UWL_MAC_SHORT_ADDRESS_ASSOC_INVALID, 
					   UWL_MAC_INVALID_PARAMETER, 
					   0, 0, NULL, 0);
		return UWL_MAC_ERR_NONE;
	}
	uwl_mac_pib.macPANId = CoordPANId;
	if (uwl_radio_phy_set_channel(LogicalChannel) < 0)
		return UWL_MAC_ERR_PHY_FAILURE;
	/* TODO:use the PHY_set primitives to set ChannelPage!*/
	if (SecurityLevel != 0) {
		return -UWL_MAC_ERR_STANDARD_UNSUPPORTED;
		/* TODO: security levels management! */
	}
	/* TODO: initiate the association procedure!!!! */
	/* TODO: current dummy: assoctiation succes, and give hardcoded addr */
	uwl_mac_status.track_beacon = 1;
	uwl_mac_superframe_stop();
	uwl_mac_superframe_start(0);
	//TODO: remove, make this with std
	uwl_MLME_ASSOCIATE_confirm(UWL_TEST_DEVICE_ADDRESS, UWL_MAC_SUCCESS, 
				   0, 0, NULL, 0);
	uwl_mac_pib.macShortAddress = UWL_TEST_DEVICE_ADDRESS;
	return UWL_MAC_ERR_NONE;
}

int8_t uwl_MLME_SET_request(enum uwl_mac_pib_id_t PIBAttribute,
        /*TODO: enough?*/   uint16_t PIBAttributeIndex,
                            void *PIBAttributeValue)
{
	enum uwl_mac_code_t status = UWL_MAC_SUCCESS;
	#ifdef UWL_DEBUG_LOG
	char s[100];
	sprintf(s, "MLME_SET_request(a=0x%x, idx=0x%x *val=0x%x)", 
		PIBAttribute, PIBAttributeIndex, 
		(unsigned int) PIBAttributeValue);
	uwl_debug_print(s);
	#endif

	if (!uwl_mac_status.mac_initialized)
		return -UWL_MAC_ERR_NOT_INITIALIZED;
	switch (PIBAttribute) {
	case UWL_MAC_SHORT_ADDRESS :
		uwl_mac_pib.macShortAddress = 
			*((uwl_mac_dev_addr_short_t *) PIBAttributeValue); 
		break;
	default:
		return -UWL_MAC_ERR_STANDARD_UNSUPPORTED;
		status = UWL_MAC_UNSUPPORTED_ATTRIBUTE;
		break;
	}
	uwl_MLME_SET_confirm(status, PIBAttribute, PIBAttributeIndex);
	return UWL_MAC_ERR_NONE;
}

#ifndef UWL_RFD_DISABLE_OPTIONAL
int8_t uwl_MLME_START_request(uint16_t PANId, uint8_t LogicalChannel,
			      uint8_t ChannelPage, uint32_t StartTime,
			      uint8_t BeaconOrder, uint8_t SuperframeOrder,
			      uint8_t PANCoordinator, 
			      uint8_t BatteryLifeExtension,
			      uint8_t CoordRealignment,
			      uint8_t CoordRealignSecurityLevel,
			      uint8_t CoordRealignKeyIdMode,
			      uint8_t *CoordRealignKeySource,
			      uint8_t CoordRealignKeyIndex,
			      uint8_t BeaconSecurityLevel,
			      uint8_t BeaconKeyIdMode,
			      uint8_t *BeaconKeySource,
			      uint8_t BeaconKeyIndex)
{
	#ifdef UWL_DEBUG_LOG
	char s[100];
	sprintf(s, "MLME_START_request(panid=%u bo=%u so=%u PANCoor=%u ...)", 
		PANId, BeaconOrder, SuperframeOrder, PANCoordinator);
	uwl_debug_print(s);
	#endif

	if (!uwl_mac_status.mac_initialized)
		return -UWL_MAC_ERR_NOT_INITIALIZED;
	if (BeaconOrder > 15 || (BeaconOrder < 15 && 
	    SuperframeOrder > BeaconOrder)) {
		uwl_MLME_START_confirm(UWL_MAC_INVALID_PARAMETER);
		return UWL_MAC_ERR_NONE;
	}
	if (uwl_mac_pib.macShortAddress == UWL_MAC_SHORT_ADDRESS_INVALID) {
		uwl_MLME_START_confirm(UWL_MAC_NO_SHORT_ADDRESS);
		return UWL_MAC_ERR_NONE;
	}
	if (PANCoordinator == UWL_TRUE) {
		uwl_mac_status.is_pan_coordinator = 1; 
		uwl_mac_status.is_coordinator = 1; 
	} else {
		/* TODO: the FFD can send BCN if already associated to a 
			 PANCoord with the SF params of that PANCoord! */
	}
	if (CoordRealignment == UWL_TRUE) {
		/* TODO: issue coord realignment command (see std.) */
		return -UWL_MAC_ERR_STANDARD_UNSUPPORTED;
	} else {
		if (BeaconOrder == 15) {
			return -UWL_MAC_ERR_STANDARD_UNSUPPORTED; 
			/* TODO: non beacon enabled mode!  */
			uwl_mac_pib.macSuperframeOrder = 15;
			uwl_mac_status.beacon_enabled = 0;
		} else {
			if (!uwl_mac_status.sf_initialized) 
				return -UWL_MAC_ERR_SF_NOT_INITIALIZED;
			uwl_mac_status.beacon_enabled = 1;
			uwl_mac_pib.macBeaconOrder = BeaconOrder;
			uwl_mac_pib.macSuperframeOrder = SuperframeOrder;
			uwl_mac_pib.macPANId = PANId;
			uwl_mac_pib.macBattLifeExt = BatteryLifeExtension;
			if (uwl_radio_phy_set_channel(LogicalChannel) < 0)
				return UWL_MAC_ERR_PHY_FAILURE;
			/* TODO: how can I check the confirm primitive??? 
				 we may use a polling on a global flag. */
			/* TODO:use the PHY_set primitives to set ChannelPage!*/
		}
	}
	if (CoordRealignSecurityLevel != 0 || BeaconSecurityLevel != 0) {
		return -UWL_MAC_ERR_STANDARD_UNSUPPORTED;
		/* TODO: security levels management! */
	}
	if (uwl_mac_status.is_pan_coordinator == 1 || StartTime == 0) {
		uwl_mac_superframe_stop();
		//uwl_mac_superframe_start(1000);
		uwl_mac_superframe_start(0);
	} else {
		return -UWL_MAC_ERR_STANDARD_UNSUPPORTED;
		/* TODO: Start Time > 0 management for nonPANCoord case ! */
	}
	uwl_MLME_START_confirm(UWL_MAC_SUCCESS);
	return UWL_MAC_ERR_NONE;
}

#endif /* UWL_RFD_DISABLE_OPTIONAL */
