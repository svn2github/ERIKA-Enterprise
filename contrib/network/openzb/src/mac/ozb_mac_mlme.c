#include <mac/ozb_mac_internal.h>
#include <util/ozb_debug.h>
#ifdef OZB_DEBUG_LOG
#include <stdio.h> //TODO: REMOVE together with the sprintf() !!!!!
#endif

int8_t ozb_MLME_ASSOCIATE_request(uint8_t LogicalChannel, uint8_t ChannelPage,
				  uint8_t CoordAddrMode, uint16_t CoordPANId,
				  void *CoordAddress,
				  uint8_t CapabilityInformation,
				  uint8_t SecurityLevel, uint8_t KeyIdMode,
				  uint8_t *KeySource, uint8_t KeyIndex)
{
	#ifdef OZB_DEBUG_LOG
	char s[100];
	sprintf(s, "MLME_ASSOCIATE_request(panid=%u ...)", CoordPANId);
	ozb_debug_print(s);
	#endif

	if (!ozb_mac_status.mac_initialized)
		return -OZB_MAC_ERR_NOT_INITIALIZED;
	switch (CoordAddrMode) {
	case OZB_MAC_ADDRESS_SHORT :
		memcpy(&(ozb_mac_pib.macCoordShortAddress), CoordAddress, 
		       sizeof(ozb_mac_dev_addr_short_t));
		break;
	case OZB_MAC_ADDRESS_EXTD :
		memcpy(&(ozb_mac_pib.macCoordExtendedAddress), CoordAddress, 
		       sizeof(ozb_mac_dev_addr_extd_t));
		break;
	default:
		ozb_MLME_ASSOCIATE_confirm(OZB_MAC_SHORT_ADDRESS_ASSOC_INVALID, 
					   OZB_MAC_INVALID_PARAMETER, 
					   0, 0, NULL, 0);
		return OZB_MAC_ERR_NONE;
	}
	ozb_mac_pib.macPANId = CoordPANId;
	if (ozb_radio_phy_set_channel(LogicalChannel) < 0)
		return OZB_MAC_ERR_PHY_FAILURE;
	/* TODO:use the PHY_set primitives to set ChannelPage!*/
	if (SecurityLevel != 0) {
		return -OZB_MAC_ERR_STANDARD_UNSUPPORTED;
		/* TODO: security levels management! */
	}
	/* TODO: initiate the association procedure!!!! */
	/* TODO: current dummy: assoctiation succes, and give hardcoded addr */
	ozb_mac_status.track_beacon = 1;
	ozb_mac_superframe_stop();
	ozb_mac_superframe_start(0);
	ozb_MLME_ASSOCIATE_confirm(0x0002, OZB_MAC_SUCCESS, 0, 0, NULL, 0);
	ozb_mac_pib.macShortAddress = 0x0002;//TODO: remove, make this with std
	return OZB_MAC_ERR_NONE;
}

int8_t ozb_MLME_SET_request(enum ozb_mac_pib_id_t PIBAttribute,
        /*TODO: enough?*/   uint16_t PIBAttributeIndex,
                            void *PIBAttributeValue)
{
	enum ozb_mac_code_t status = OZB_MAC_SUCCESS;
	#ifdef OZB_DEBUG_LOG
	char s[100];
	sprintf(s, "MLME_SET_request(a=0x%x, idx=0x%x *val=0x%x)", 
		PIBAttribute, PIBAttributeIndex, 
		(unsigned int) PIBAttributeValue);
	ozb_debug_print(s);
	#endif

	if (!ozb_mac_status.mac_initialized)
		return -OZB_MAC_ERR_NOT_INITIALIZED;
	switch (PIBAttribute) {
	case OZB_MAC_SHORT_ADDRESS :
		ozb_mac_pib.macShortAddress = 
			*((ozb_mac_dev_addr_short_t *) PIBAttributeValue); 
		break;
	default:
		return -OZB_MAC_ERR_STANDARD_UNSUPPORTED;
		status = OZB_MAC_UNSUPPORTED_ATTRIBUTE;
		break;
	}
	ozb_MLME_SET_confirm(status, PIBAttribute, PIBAttributeIndex);
	return OZB_MAC_ERR_NONE;
}

#ifndef OZB_RFD_DISABLE_OPTIONAL
int8_t ozb_MLME_START_request(uint16_t PANId, uint8_t LogicalChannel,
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
	#ifdef OZB_DEBUG_LOG
	char s[100];
	sprintf(s, "MLME_START_request(panid=%u bo=%u so=%u PANCoor=%u ...)", 
		PANId, BeaconOrder, SuperframeOrder, PANCoordinator);
	ozb_debug_print(s);
	#endif

	if (!ozb_mac_status.mac_initialized)
		return -OZB_MAC_ERR_NOT_INITIALIZED;
	if (BeaconOrder > 15 || (BeaconOrder < 15 && 
	    SuperframeOrder > BeaconOrder)) {
		ozb_MLME_START_confirm(OZB_MAC_INVALID_PARAMETER);
		return OZB_MAC_ERR_NONE;
	}
	if (ozb_mac_pib.macShortAddress == OZB_MAC_SHORT_ADDRESS_INVALID) {
		ozb_MLME_START_confirm(OZB_MAC_NO_SHORT_ADDRESS);
		return OZB_MAC_ERR_NONE;
	}
	if (PANCoordinator == OZB_TRUE) {
		ozb_mac_status.is_pan_coordinator = 1; 
		ozb_mac_status.is_coordinator = 1; 
	} else {
		/* TODO: the FFD can send BCN if already associated to a 
			 PANCoord with the SF params of that PANCoord! */
	}
	if (CoordRealignment == OZB_TRUE) {
		/* TODO: issue coord realignment command (see std.) */
		return -OZB_MAC_ERR_STANDARD_UNSUPPORTED;
	} else {
		if (BeaconOrder == 15) {
			return -OZB_MAC_ERR_STANDARD_UNSUPPORTED; 
			/* TODO: non beacon enabled mode!  */
			ozb_mac_pib.macSuperframeOrder = 15;
			ozb_mac_status.beacon_enabled = 0;
		} else {
			if (!ozb_mac_status.sf_initialized) 
				return -OZB_MAC_ERR_SF_NOT_INITIALIZED;
			ozb_mac_status.beacon_enabled = 1;
			ozb_mac_pib.macBeaconOrder = BeaconOrder;
			ozb_mac_pib.macSuperframeOrder = SuperframeOrder;
			ozb_mac_pib.macPANId = PANId;
			ozb_mac_pib.macBattLifeExt = BatteryLifeExtension;
			if (ozb_radio_phy_set_channel(LogicalChannel) < 0)
				return OZB_MAC_ERR_PHY_FAILURE;
			/* TODO: how can I check the confirm primitive??? 
				 we may use a polling on a global flag. */
			/* TODO:use the PHY_set primitives to set ChannelPage!*/
		}
	}
	if (CoordRealignSecurityLevel != 0 || BeaconSecurityLevel != 0) {
		return -OZB_MAC_ERR_STANDARD_UNSUPPORTED;
		/* TODO: security levels management! */
	}
	if (ozb_mac_status.is_pan_coordinator == 1 || StartTime == 0) {
		ozb_mac_superframe_stop();
		//ozb_mac_superframe_start(1000);
		ozb_mac_superframe_start(0);
	} else {
		return -OZB_MAC_ERR_STANDARD_UNSUPPORTED;
		/* TODO: Start Time > 0 management for nonPANCoord case ! */
	}
	ozb_MLME_START_confirm(OZB_MAC_SUCCESS);
	return OZB_MAC_ERR_NONE;
}

#endif /* OZB_RFD_DISABLE_OPTIONAL */
