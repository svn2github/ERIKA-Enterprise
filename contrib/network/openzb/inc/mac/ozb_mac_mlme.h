#ifndef __ozb_mac_mlme_h__
#define __ozb_mac_mlme_h__

#include <mac/ozb_mac_types.h>

int8_t ozb_MLME_ASSOCIATE_request(uint8_t LogicalChannel, uint8_t ChannelPage,
				  uint8_t CoordAddrMode, uint16_t CoordPANId,
				  ozb_mac_dev_addr_t CoordAddress,
				  uint8_t CapabilityInformation,
				  uint8_t SecurityLevel, uint8_t KeyIdMode,
				  uint8_t *KeySource, uint8_t KeyIndex);

int8_t ozb_MLME_ASSOCIATE_confirm(ozb_mac_dev_addr_short_t AssocShortAddress,
				  enum ozb_mac_code_t status,
				  uint8_t SecurityLevel, uint8_t KeyIdMode,
				  uint8_t *KeySource, uint8_t KeyIndex
);

#ifdef OZB_RFD_DISABLE_OPTIONAL
int8_t ozb_MLME_ASSOCIATE_indication(ozb_mac_dev_addr_extd_t DeviceAddress,
				     uint8_t CapabilityInformation,
				     uint8_t SecurityLevel, uint8_t KeyIdMode,
				     uint8_t *KeySource, uint8_t KeyIndex);

int8_t ozb_MLME_ASSOCIATE_response(ozb_mac_dev_addr_extd_t DeviceAddress,
				   ozb_mac_dev_addr_short_t AssocShortAddress,
				   enum ozb_mac_code_t status, 
				   uint8_t SecurityLevel, uint8_t KeyIdMode, 
				   uint8_t *KeySource, uint8_t KeyIndex);
#endif /* OZB_RFD_DISABLE_OPTIONAL */

int8_t ozb_MLME_DISASSOCIATE_request(uint8_t DeviceAddrMode, 
				     uint16_t DevicePANId,
				     ozb_mac_dev_addr_t DeviceAddress,
				     uint8_t DisassociateReason,
				     uint8_t TxIndirect, uint8_t SecurityLevel,
				     uint8_t KeyIdMode, uint8_t *KeySource,
				     uint8_t KeyIndex);

int8_t ozb_MLME_DISASSOCIATE_confirm(enum ozb_mac_code_t status,
				     uint8_t DeviceAddrMode,
				     uint16_t DevicePANId,
				     ozb_mac_dev_addr_t DeviceAddress);

int8_t ozb_MLME_DISASSOCIATE_indication(ozb_mac_dev_addr_extd_t DeviceAddress,
					uint8_t DisassociateReason,
					uint8_t SecurityLevel, 
					uint8_t KeyIdMode, uint8_t *KeySource,
					uint8_t KeyIndex);


int8_t ozb_MLME_BEACON_NOTIFY_indication(uint8_t BSN,
					 struct ozb_pan_des_t PANDescriptor,
					 uint8_t PendAddrSpec,
		 /*TODO: list? how?*/	 ozb_mac_dev_addr_t *AddrList, 
					 uint8_t sduLength, uint8_t *sdu);

int8_t ozb_MLME_GET_request(enum ozb_mac_pib_id_t PIBAttribute,
	/*TODO: enough?*/   uint16_t PIBAttributeIndex);
int8_t ozb_MLME_GET_confirm(enum ozb_mac_code_t status,
			    enum ozb_mac_pib_id_t PIBAttribute,
	/*TODO: enough?*/   uint16_t PIBAttributeIndex, 
			    void *PIBAttributeValue);

#ifdef OZB_DEVICE_DISABLE_OPTIONAL
int8_t ozb_MLME_GTS_request(uint8_t GTSCharacteristics, uint8_t SecurityLevel,
			    uint8_t KeyIdMode, uint8_t *KeySource,
			    uint8_t KeyIndex);

int8_t ozb_MLME_GTS_confirm(uint8_t GTSCharacteristics, 
			    enum ozb_mac_code_t status);

int8_t ozb_MLME_GTS_indication(ozb_mac_dev_addr_short_t DeviceAddress,
			       uint8_t GTSCharacteristics,
			       uint8_t SecurityLevel, uint8_t KeyIdMode,
			       uint8_t *KeySource, uint8_t KeyIndex);
#endif /* OZB_DEVICE_DISABLE_OPTIONAL */

#ifdef OZB_RFD_DISABLE_OPTIONAL
int8_t ozb_MLME_ORPHAN_indication(ozb_mac_dev_addr_extd_t OrphanAddress,
				  uint8_t SecurityLevel, uint8_t KeyIdMode,
				  uint8_t *KeySource, uint8_t KeyIndex);

int8_t ozb_MLME_ORPHAN_response(ozb_mac_dev_addr_extd_t OrphanAddress,
				ozb_mac_dev_addr_short_t ShortAddress,
				uint8_t AssociatedMember, uint8_t SecurityLevel,
				uint8_t KeyIdMode, uint8_t *KeySource,
				uint8_t KeyIndex);
#endif /* OZB_RFD_DISABLE_OPTIONAL */

int8_t ozb_MLME_RESET_request(uint8_t SetDefaultPIB);
int8_t ozb_MLME_RESET_confirm(enum ozb_mac_code_t status);

#ifdef OZB_DEVICE_DISABLE_OPTIONAL
int8_t ozb_MLME_RX_ENABLE_request(uint8_t DeferPermit, uint32_t RxOnTime,
				  uint32_t RxOnDuration);

int8_t ozb_MLME_RX_ENABLE_confirm(enum ozb_mac_code_t status);
#endif /* OZB_DEVICE_DISABLE_OPTIONAL */

int8_t ozb_MLME_SCAN_request(uint8_t ScanType, uint32_t ScanChannels,
			     uint8_t ScanDuration, uint8_t ChannelPage,
			     uint8_t SecurityLevel, uint8_t KeyIdMode,
			     uint8_t *KeySource, uint8_t KeyIndex);

int8_t ozb_MLME_SCAN_confirm(enum ozb_mac_code_t status, uint8_t ScanType,
			     uint8_t ChannelPage, uint32_t UnscannedChannels,
/*TODO: good represent.?*/   uint16_t ResultListSize, uint8_t *EnergyDetectList,
			     struct ozb_pan_des_t *PANDescriptorList);

int8_t ozb_MLME_COMM_STATUS_indication(uint16_t PANId, uint8_t SrcAddrMode,
				       ozb_mac_dev_addr_t SrcAddr,
				       uint8_t DstAddrMode,
				       ozb_mac_dev_addr_t DstAddr,
				       enum ozb_mac_code_t status,
				       uint8_t SecurityLevel, uint8_t KeyIdMode,
				       uint8_t KeySource, uint8_t KeyIndex);

int8_t ozb_MLME_SET_request(enum ozb_mac_pib_id_t PIBAttribute,
        /*TODO: enough?*/   uint16_t PIBAttributeIndex,
                            void *PIBAttributeValue);

int8_t ozb_MLME_SET_confirm(enum ozb_mac_code_t status,
			    enum ozb_mac_pib_id_t PIBAttribute,
        /*TODO: enough?*/   uint16_t PIBAttributeIndex);

#ifdef OZB_RFD_DISABLE_OPTIONAL
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
			      uint8_t BeaconKeyIndex);

int8_t ozb_MLME_START_confirm(enum ozb_mac_code_t status);
#endif /* OZB_RFD_DISABLE_OPTIONAL */

#ifdef OZB_DEVICE_DISABLE_OPTIONAL
int8_t ozb_MLME_SYNC_request(uint8_t LogicalChannel, uint8_t ChannelPage,
			     uint8_t TrackBeacon);
#endif /* OZB_DEVICE_DISABLE_OPTIONAL */

int8_t ozb_MLME_SYNC_LOSS_indication(enum ozb_mac_code_t LossReason,
				     uint8_t PANId, uint8_t LogicalChannel,
				     uint8_t ChannelPage, uint8_t SecurityLevel,
				     uint8_t KeyIdMode, uint8_t *KeySource,
				     uint8_t KeyIndex);

int8_t ozb_MLME_POLL_request(uint8_t CoordAddrMode, uint16_t CoordPANId,
			     ozb_mac_dev_addr_t CoordAddress, 
			     uint8_t SecurityLevel, uint8_t KeyIdMode,
			     uint8_t *KeySource, uint8_t KeyIndex);

int8_t ozb_MLME_POLL_confirm(enum ozb_mac_code_t status);

#endif /* Header Protection */
