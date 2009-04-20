#include <mac/ozb_mac_internal.h>
#include <util/ozb_debug.h>
#ifdef OZB_DEBUG_LOG
#include <stdio.h> //TODO: REMOVE together with the sprintf() !!!!!
#endif

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
		return -OZB_MAC_NOT_INITIALIZED;
	switch (PIBAttribute) {
	case OZB_MAC_SHORT_ADDRESS :
		ozb_mac_pib.macShortAddress = 
			*((ozb_mac_dev_addr_short_t *) PIBAttributeValue); 
		break;
	default:
		return -OZB_MAC_STANDARD_UNSUPPORTED;
		status = OZB_UNSUPPORTED_ATTRIBUTE;
		break;
	}
	ozb_MLME_SET_confirm(status, PIBAttribute, PIBAttributeIndex);
	return 1;
}

#ifndef OZB_RFD_DISABLE_OPTIONAL
int8_t ozb_MLME_START_request(uint8_t PANId, uint8_t LogicalChannel,
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
	int8_t retv;
	#ifdef OZB_DEBUG_LOG
	char s[100];
	sprintf(s, "MLME_START_request(panid=%u bo=%u so=%u PANCoor=%u ...)", 
		PANId, BeaconOrder, SuperframeOrder, PANCoordinator);
	ozb_debug_print(s);
	#endif

	if (!ozb_mac_status.mac_initialized)
		return -OZB_MAC_NOT_INITIALIZED;
	if (BeaconOrder > 15 || (BeaconOrder < 15 && 
	    SuperframeOrder > BeaconOrder)) {
		ozb_MLME_START_confirm(OZB_MAC_INVALID_PARAMETER);
		return 1;
	}
	if (ozb_mac_pib.macShortAddress == 0xFFFF) {
		ozb_MLME_START_confirm(OZB_MAC_NO_SHORT_ADDRESS);
		return 1;
	}
	if (PANCoordinator == OZB_TRUE)
		ozb_mac_status.is_coordinator = 1; 
	if (CoordRealignment == OZB_TRUE) {
		/* TODO: issue coord realignment command (see std.) */
		return -OZB_MAC_STANDARD_UNSUPPORTED;
	} else {
		if (BeaconOrder == 15) {
			return -OZB_MAC_STANDARD_UNSUPPORTED; 
			/* TODO: non beacon enabled mode!  */
			ozb_mac_pib.macSuperframeOrder = 15;
			ozb_mac_status.beacon_enabled = 0;
		} else {
			if (!ozb_mac_status.sf_initialized) 
				return -OZB_MAC_SF_NOT_INITIALIZED;
			ozb_mac_status.beacon_enabled = 1;
			ozb_mac_pib.macBeaconOrder = BeaconOrder;
			ozb_mac_pib.macSuperframeOrder = SuperframeOrder;
			ozb_mac_pib.macPANId = PANId;
			ozb_mac_pib.macBattLifeExt = BatteryLifeExtension;
			retv = ozb_PLME_SET_request(OZB_PHY_CURRENT_CHANNEL, 
						    (void *) &LogicalChannel);
			if (retv < 0)
				return retv;
			/* TODO: how can I check the confirm primitive??? 
				 we may use a polling on a global flag. */
			/* TODO:use the PHY_set primitives to set ChannelPage!*/
		}
	}
	if (CoordRealignSecurityLevel != 0 || BeaconSecurityLevel != 0) {
		return -OZB_MAC_STANDARD_UNSUPPORTED;
		/* TODO: security levels management! */
	}
	if (StartTime == 0) {
		ozb_mac_sf_stop();
		ozb_mac_sf_start(1000);
	} else {
		return -OZB_MAC_STANDARD_UNSUPPORTED;
		/* TODO: Start Time > 0 management! */
	}
	ozb_MLME_START_confirm(OZB_MAC_SUCCESS);
	return 1;
}

#endif /* OZB_RFD_DISABLE_OPTIONAL */
