/* TODO: this should go, eventually with a different name, in the makefile 
	 rules.
*/
//#ifndef OZB_USE_ONLY_802154_MAC	
#if !( (defined OZB_USE_ONLY_802154_MAC) || (defined OZB_USE_SIMPLE_802154) )

#include <mac/ozb_net_internal.h>

#ifdef OZB_DEBUG_LOG
#include <util/ozb_debug.h>
#include <string.h>
#include <stdio.h> //TODO: REMOVE together with the sprintf() !!!!!
#endif


int8_t ozb_MCPS_DATA_confirm(uint8_t msduHandle, enum ozb_mac_code_t status,
			     uint32_t Timestamp)
{
	//#ifdef OZB_DEBUG_LOG
	//char s[100];
	//char s1[30];
	//ozb_debug_sprint_maccode(status, s1);
	//sprintf(s, "SET_confirm(%s, a=%u)", s1, PIBAttribute);
	//ozb_debug_print(s);
	//#endif
	return 1;
}

int8_t ozb_MCPS_DATA_indication(uint8_t SrcAddrMode, uint16_t SrcPANId,
				ozb_mac_dev_addr_t SrcAddr, uint8_t DstAddrMode,
				uint16_t DstPANId, ozb_mac_dev_addr_t DstAddr,
				uint8_t msduLength, uint8_t *msdu,
				uint8_t mpduLinkQuality, uint8_t DSN,
				uint32_t Timestamp, uint8_t SecurityLevel,
				uint8_t KeyIdMode, uint8_t *KeySource,
				uint8_t KeyIndex)
{
	//#ifdef OZB_DEBUG_LOG
	//char s[100];
	//char s1[30];
	//ozb_debug_sprint_maccode(status, s1);
	//sprintf(s, "SET_confirm(%s, a=%u)", s1, PIBAttribute);
	//ozb_debug_print(s);
	//#endif
	return 1;
}

int8_t ozb_MCPS_PURGE_confirm(uint8_t msduHandle, enum ozb_mac_code_t status)
{
	//#ifdef OZB_DEBUG_LOG
	//char s[100];
	//char s1[30];
	//ozb_debug_sprint_maccode(status, s1);
	//sprintf(s, "SET_confirm(%s, a=%u)", s1, PIBAttribute);
	//ozb_debug_print(s);
	//#endif
	return 1;
}


int8_t ozb_MLME_ASSOCIATE_confirm(ozb_mac_dev_addr_short_t AssocShortAddress,
				  enum ozb_mac_code_t status,
				  uint8_t SecurityLevel, uint8_t KeyIdMode,
				  uint8_t *KeySource, uint8_t KeyIndex
)
{
	//#ifdef OZB_DEBUG_LOG
	//char s[100];
	//char s1[30];
	//ozb_debug_sprint_maccode(status, s1);
	//sprintf(s, "SET_confirm(%s, a=%u)", s1, PIBAttribute);
	//ozb_debug_print(s);
	//#endif
	return 1;
}

#ifndef OZB_RFD_DISABLE_OPTIONAL
int8_t ozb_MLME_ASSOCIATE_indication(ozb_mac_dev_addr_extd_t DeviceAddress,
				     uint8_t CapabilityInformation,
				     uint8_t SecurityLevel, uint8_t KeyIdMode,
				     uint8_t *KeySource, uint8_t KeyIndex)
{
	//#ifdef OZB_DEBUG_LOG
	//char s[100];
	//char s1[30];
	//ozb_debug_sprint_maccode(status, s1);
	//sprintf(s, "SET_confirm(%s, a=%u)", s1, PIBAttribute);
	//ozb_debug_print(s);
	//#endif
	return 1;
}

#endif /* OZB_RFD_DISABLE_OPTIONAL */


int8_t ozb_MLME_DISASSOCIATE_confirm(enum ozb_mac_code_t status,
				     uint8_t DeviceAddrMode,
				     uint16_t DevicePANId,
				     ozb_mac_dev_addr_t DeviceAddress)
{
	//#ifdef OZB_DEBUG_LOG
	//char s[100];
	//char s1[30];
	//ozb_debug_sprint_maccode(status, s1);
	//sprintf(s, "SET_confirm(%s, a=%u)", s1, PIBAttribute);
	//ozb_debug_print(s);
	//#endif
	return 1;
}

int8_t ozb_MLME_DISASSOCIATE_indication(ozb_mac_dev_addr_extd_t DeviceAddress,
					uint8_t DisassociateReason,
					uint8_t SecurityLevel, 
					uint8_t KeyIdMode, uint8_t *KeySource,
					uint8_t KeyIndex)
{
	//#ifdef OZB_DEBUG_LOG
	//char s[100];
	//char s1[30];
	//ozb_debug_sprint_maccode(status, s1);
	//sprintf(s, "SET_confirm(%s, a=%u)", s1, PIBAttribute);
	//ozb_debug_print(s);
	//#endif
	return 1;
}


int8_t ozb_MLME_BEACON_NOTIFY_indication(uint8_t BSN,
					 struct ozb_pan_des_t PANDescriptor,
					 uint8_t PendAddrSpec,
		 /*TODO: list? how?*/	 ozb_mac_dev_addr_t *AddrList, 
					 uint8_t sduLength, uint8_t *sdu)
{
	//#ifdef OZB_DEBUG_LOG
	//char s[100];
	//char s1[30];
	//ozb_debug_sprint_maccode(status, s1);
	//sprintf(s, "SET_confirm(%s, a=%u)", s1, PIBAttribute);
	//ozb_debug_print(s);
	//#endif
	return 1;
}

int8_t ozb_MLME_GET_confirm(enum ozb_mac_code_t status,
			    enum ozb_mac_pib_id_t PIBAttribute,
	/*TODO: enough?*/   uint16_t PIBAttributeIndex, 
			    void *PIBAttributeValue)
{
	//#ifdef OZB_DEBUG_LOG
	//char s[100];
	//char s1[30];
	//ozb_debug_sprint_maccode(status, s1);
	//sprintf(s, "SET_confirm(%s, a=%u)", s1, PIBAttribute);
	//ozb_debug_print(s);
	//#endif
	return 1;
}

#ifndef OZB_DEVICE_DISABLE_OPTIONAL
int8_t ozb_MLME_GTS_confirm(uint8_t GTSCharacteristics, 
			    enum ozb_mac_code_t status)
{
	//#ifdef OZB_DEBUG_LOG
	//char s[100];
	//char s1[30];
	//ozb_debug_sprint_maccode(status, s1);
	//sprintf(s, "SET_confirm(%s, a=%u)", s1, PIBAttribute);
	//ozb_debug_print(s);
	//#endif
	return 1;
}

int8_t ozb_MLME_GTS_indication(ozb_mac_dev_addr_short_t DeviceAddress,
			       uint8_t GTSCharacteristics,
			       uint8_t SecurityLevel, uint8_t KeyIdMode,
			       uint8_t *KeySource, uint8_t KeyIndex)
{
	//#ifdef OZB_DEBUG_LOG
	//char s[100];
	//char s1[30];
	//ozb_debug_sprint_maccode(status, s1);
	//sprintf(s, "SET_confirm(%s, a=%u)", s1, PIBAttribute);
	//ozb_debug_print(s);
	//#endif
	return 1;
}
#endif /* OZB_DEVICE_DISABLE_OPTIONAL */

#ifndef OZB_RFD_DISABLE_OPTIONAL
int8_t ozb_MLME_ORPHAN_indication(ozb_mac_dev_addr_extd_t OrphanAddress,
				  uint8_t SecurityLevel, uint8_t KeyIdMode,
				  uint8_t *KeySource, uint8_t KeyIndex)
{
	//#ifdef OZB_DEBUG_LOG
	//char s[100];
	//char s1[30];
	//ozb_debug_sprint_maccode(status, s1);
	//sprintf(s, "SET_confirm(%s, a=%u)", s1, PIBAttribute);
	//ozb_debug_print(s);
	//#endif
	return 1;
}

#endif /* OZB_RFD_DISABLE_OPTIONAL */

int8_t ozb_MLME_RESET_confirm(enum ozb_mac_code_t status)
{
	//#ifdef OZB_DEBUG_LOG
	//char s[100];
	//char s1[30];
	//ozb_debug_sprint_maccode(status, s1);
	//sprintf(s, "SET_confirm(%s, a=%u)", s1, PIBAttribute);
	//ozb_debug_print(s);
	//#endif
	return 1;
}

#ifndef OZB_DEVICE_DISABLE_OPTIONAL

int8_t ozb_MLME_RX_ENABLE_confirm(enum ozb_mac_code_t status)
{
	//#ifdef OZB_DEBUG_LOG
	//char s[100];
	//char s1[30];
	//ozb_debug_sprint_maccode(status, s1);
	//sprintf(s, "SET_confirm(%s, a=%u)", s1, PIBAttribute);
	//ozb_debug_print(s);
	//#endif
	return 1;
}
#endif /* OZB_DEVICE_DISABLE_OPTIONAL */

int8_t ozb_MLME_SCAN_confirm(enum ozb_mac_code_t status, uint8_t ScanType,
			     uint8_t ChannelPage, uint32_t UnscannedChannels,
/*TODO: good represent.?*/   uint16_t ResultListSize, uint8_t *EnergyDetectList,
			     struct ozb_pan_des_t *PANDescriptorList)
{
	//#ifdef OZB_DEBUG_LOG
	//char s[100];
	//char s1[30];
	//ozb_debug_sprint_maccode(status, s1);
	//sprintf(s, "SET_confirm(%s, a=%u)", s1, PIBAttribute);
	//ozb_debug_print(s);
	//#endif
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
	//#ifdef OZB_DEBUG_LOG
	//char s[100];
	//char s1[30];
	//ozb_debug_sprint_maccode(status, s1);
	//sprintf(s, "SET_confirm(%s, a=%u)", s1, PIBAttribute);
	//ozb_debug_print(s);
	//#endif
	return 1;
}

int8_t ozb_MLME_SET_confirm(enum ozb_mac_code_t status,
			    enum ozb_mac_pib_id_t PIBAttribute,
        /*TODO: enough?*/   uint16_t PIBAttributeIndex)
{
	//#ifdef OZB_DEBUG_LOG
	//char s[100];
	//char s1[30];
	//ozb_debug_sprint_maccode(status, s1);
	//sprintf(s, "SET_confirm(%s, a=%u)", s1, PIBAttribute);
	//ozb_debug_print(s);
	//#endif
	return 1;
}

#ifndef OZB_RFD_DISABLE_OPTIONAL

int8_t ozb_MLME_START_confirm(enum ozb_mac_code_t status)
{
	//#ifdef OZB_DEBUG_LOG
	//char s[100];
	//char s1[30];
	//ozb_debug_sprint_maccode(status, s1);
	//sprintf(s, "SET_confirm(%s, a=%u)", s1, PIBAttribute);
	//ozb_debug_print(s);
	//#endif
	return 1;
}
#endif /* OZB_RFD_DISABLE_OPTIONAL */

int8_t ozb_MLME_SYNC_LOSS_indication(enum ozb_mac_code_t LossReason,
				     uint8_t PANId, uint8_t LogicalChannel,
				     uint8_t ChannelPage, uint8_t SecurityLevel,
				     uint8_t KeyIdMode, uint8_t *KeySource,
				     uint8_t KeyIndex)
{
	//#ifdef OZB_DEBUG_LOG
	//char s[100];
	//char s1[30];
	//ozb_debug_sprint_maccode(status, s1);
	//sprintf(s, "SET_confirm(%s, a=%u)", s1, PIBAttribute);
	//ozb_debug_print(s);
	//#endif
	return 1;
}

int8_t ozb_MLME_POLL_confirm(enum ozb_mac_code_t status)
{
	//#ifdef OZB_DEBUG_LOG
	//char s[100];
	//char s1[30];
	//ozb_debug_sprint_maccode(status, s1);
	//sprintf(s, "SET_confirm(%s, a=%u)", s1, PIBAttribute);
	//ozb_debug_print(s);
	//#endif
	return 1;
}

#endif /* ! (OZB_USE_ONLY_802154_MAC || OZB_USE_SIMPLE_802154) */
