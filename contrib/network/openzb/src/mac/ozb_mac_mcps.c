#include <mac/ozb_mac_internal.h>
#include <util/ozb_debug.h>
#ifdef OZB_DEBUG_LOG
#include <stdio.h> //TODO: REMOVE together with the sprintf() !!!!!
#endif

/* TODO: what is the meaning of the msduHandle? */

int8_t ozb_MCPS_DATA_request(uint8_t SrcAddrMode, uint8_t DstAddrMode,
			     uint16_t DstPANId, void *DstAddr,
			     uint8_t msduLength, uint8_t *msdu,
			     uint8_t msduHandle, uint8_t TxOptions,
			     uint8_t SecurityLevel, uint8_t KeyIdMode,
			     uint8_t *KeySource, uint8_t KeyIndex)
{
	if (SrcAddrMode == OZB_MAC_ADDRESS_NONE && 
	    DstAddrMode == OZB_MAC_ADDRESS_NONE) {
		ozb_MCPS_DATA_confirm(msduHandle, OZB_MAC_INVALID_ADDRESS, 0);
		return OZB_MAC_ERR_NONE;
	}
	if (msduLength > OZB_aMaxMACPayloadSize) {
		ozb_MCPS_DATA_confirm(msduHandle, OZB_MAC_INVALID_PARAMETER, 0);
		return OZB_MAC_ERR_NONE;
	}
	if (SecurityLevel != 0) {
		return -OZB_MAC_ERR_STANDARD_UNSUPPORTED;
		/* TODO: security levels management! */
	}
	/* TODO: check other params!*/
	/* TODO: check ret value?*/
	ozb_mac_perform_data_request(SrcAddrMode, DstAddrMode, DstPANId, 
				     DstAddr, msduLength, msdu, msduHandle, 
				     TxOptions/*, SecurityLevel, KeyIdMode, 
				     KeySource, KeyIndex*/);
	
	return OZB_MAC_ERR_NONE;
}
