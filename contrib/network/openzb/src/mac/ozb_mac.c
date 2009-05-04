#include <mac/ozb_mac_internal.h>
#include <hal/ozb_radio.h>
#include <hal/ozb_rand.h>
#include <util/ozb_debug.h>
#ifdef OZB_DEBUG_LOG
#include <stdio.h> //TODO: REMOVE together with the sprintf() !!!!!
#endif

/******************************************************************************/
/*                          MAC Layer Private Data                            */
/******************************************************************************/

/******************************************************************************/
/*                          MAC Layer Public Data                             */
/******************************************************************************/
struct ozb_mac_flags_t ozb_mac_status = {0, 0, 0, 0, 0};
struct ozb_mac_pib_t ozb_mac_pib /*= {
	TODO: set a default values as already done for the phy_pib!	
}*/;

/******************************************************************************/
/*                      MAC Layer Private Functions                           */
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
HAL_INLINE void set_frame_control(uint8_t *fcf, uint8_t frame_type, 
				  uint8_t security, uint8_t frame_pending, 
				  uint8_t ack_request, uint8_t intra_pan, 
				  uint8_t dst_addr_mode, uint8_t src_addr_mode) 
{
  	  fcf[0] = (intra_pan << 6) | (ack_request << 5) | 
		   (frame_pending << 4) | (security << 3) | (frame_type << 0);	
	  fcf[1] = (src_addr_mode << 6) | (dst_addr_mode << 2);
} 

HAL_INLINE uint8_t set_addressing_fields(uint8_t *af, 
					 enum ozb_mac_addr_mode_t dst_mode,
					 uint16_t dst_panid, void *dst_addr,
					 enum ozb_mac_addr_mode_t src_mode,
					 uint16_t src_panid, void *src_addr) 
{
	uint8_t offset = OZB_MAC_MPDU_PANID_SIZE;

	if (dst_mode == OZB_MAC_ADDRESS_SHORT) {
		af[0] = dst_panid;
		memcpy(af + offset, (uint8_t *) dst_addr,
		       OZB_MAC_MPDU_ADDRESS_SHORT_SIZE);
		offset += OZB_MAC_MPDU_ADDRESS_SHORT_SIZE;
	} else if (dst_mode == OZB_MAC_ADDRESS_EXTD) {
		af[0] = dst_panid;
		memcpy(af + offset, (uint8_t *) dst_addr,
		       OZB_MAC_MPDU_ADDRESS_EXTD_SIZE);
		offset += OZB_MAC_MPDU_ADDRESS_EXTD_SIZE;
	}
	if (src_mode == OZB_MAC_ADDRESS_SHORT) {
		af[offset] = src_panid;
		offset += OZB_MAC_MPDU_PANID_SIZE;
		memcpy(af + offset, (uint8_t *) src_addr,
		       OZB_MAC_MPDU_ADDRESS_SHORT_SIZE);
	} else if (src_mode == OZB_MAC_ADDRESS_EXTD) {
		af[offset] = src_panid;
		offset += OZB_MAC_MPDU_PANID_SIZE;
		memcpy(af + offset, (uint8_t *) src_addr,
		       OZB_MAC_MPDU_ADDRESS_EXTD_SIZE);
	}
	return offset;
}

HAL_INLINE uint8_t set_superframe_specification(uint8_t *ss, uint8_t bo, 
						uint8_t so, 
						uint8_t final_cap_slot,
						uint8_t ble, uint8_t pan_coord,	
						uint8_t association_permit)
{
	ss[0] = (bo << 0) | (so << 4); 
	ss[1] = (final_cap_slot << 0) | (ble) << 4 | (pan_coord << 6)  | 
		(association_permit << 7);
	return 2;
}


uint8_t ozb_gts_get_last_cap_stlot(void) 
{
	return 15;
}

uint8_t ozb_gts_set_gts_fields(uint8_t *gf) 
{
	OZB_MAC_GTS_SPEC_SET_EMPTY(gf);
	/*
	OZB_MAC_GTS_SPEC_SET_DESCRIPTOR_COUNT(gf, 0);
	OZB_MAC_GTS_SPEC_SET_PERMIT(gf, 0);
	*/
	return 1;

//	uint8_t i;
//	uint8_t packet_length = 25;
//	int data_count=0;
//	uint8_t short_addr_pending=0;
//	uint8_t long_addr_pending=0;
//	uint8_t gts_directions=0x00;
//
////assign the gts specification field
//	mac_beacon_txmpdu_ptr->data[8] = set_gts_specification(GTS_descriptor_count,mac_PIB.macGTSPermit);
//	
//	//assign the pending address specification field
//	mac_beacon_txmpdu_ptr->data[9] = set_pending_address_specification(short_addr_pending,long_addr_pending);
//	
//	//moving in the position of the beacon data payload	
//	data_count = 9;
//	//after the addressing the the beacon fields the beacon has the size of 15 bytes
//	packet_length = 15;
//		
//	//BUILDING the GTS DESCRIPTORS
//	//RARS todo
//	
//	if( (GTS_descriptor_count + GTS_null_descriptor_count) > 0 )
//	{
//		data_count++;
//				
//		for(i=0; i< 7 ; i++)
//		{
//		
//			if( GTS_db[i].gts_id != 0x00 && GTS_db[i].DevAddressType != 0x0000) 
//			{
//				
//			mac_beacon_txmpdu_ptr->data[data_count] = (uint8_t) (GTS_db[i].DevAddressType );
//		
//		//ee_console_out16_radix(mac_beacon_txmpdu_ptr->data[data_count], 16);
//				data_count++;
//			
//				mac_beacon_txmpdu_ptr->data[data_count] = (uint8_t) (GTS_db[i].DevAddressType >> 8 );;
//				//////////////printfUART("B gts %i\n",  GTS_db[i].DevAddressType ); 
//				
//		//ee_console_out16_radix(mac_beacon_txmpdu_ptr->data[data_count], 16);
//				
//				data_count++;
//				
//			mac_beacon_txmpdu_ptr->data[data_count] = (uint8_t) set_gts_descriptor(GTS_db[i].starting_slot,GTS_db[i].length);
//				data_count++;
//			 
//			 
//				
//				packet_length = packet_length + 3;
//				
//				if ( GTS_db[i].direction == 1 )
//				{
//					gts_directions = gts_directions | (1 << i); 
//				}
//				else
//				{
//					gts_directions = gts_directions | (0 << i); 
//				}
//				//////printfUART("dir %i\n", gts_directions); 
//			}
//		}
//		mac_beacon_txmpdu_ptr->data[9] = gts_directions;
//		//CHECK
//		packet_length++;
//		//BUILDING the NULL GTS DESCRIPTORS
//		/*
//		if ( GTS_null_descriptor_count > 0 )
//		{
//			for(i=0; i< 7 ; i++)
//			{
//				if( GTS_null_db[i].DevAddressType != 0x0000) 
//				{
//					mac_beacon_txmpdu_ptr->data[data_count] = GTS_null_db[i].DevAddressType;
//					//////////////printfUART("B gts %i\n", (GTS_db[i].DevAddressType >> 8 ) ); 
//					data_count++;
//					mac_beacon_txmpdu_ptr->data[data_count] = (GTS_null_db[i].DevAddressType >> 8 );
//					//////////////printfUART("B gts %i\n",  GTS_db[i].DevAddressType ); 
//					data_count++;
//					mac_beacon_txmpdu_ptr->data[data_count] = 0x00;
//					data_count++;
//					//////////////printfUART("B gts %i\n", set_gts_descriptor(GTS_db[i].starting_slot,GTS_db[i].length) ); 
//					packet_length = packet_length +3;
//				}
//			}
//		}
//		*/
//		//resetting the GTS specification field
//		mac_beacon_txmpdu_ptr->data[8] = set_gts_specification(GTS_descriptor_count + GTS_null_descriptor_count,mac_PIB.macGTSPermit);
//		
//
//	}
//	
//	/*
//	pending_data_index = data_count;
//	data_count++;
//	//IMPLEMENT PENDING ADDRESSES
//	//temporary
//	//indirect_trans_count =0;
//		
//	if (indirect_trans_count > 0 )
//{
//			//IMPLEMENT THE PENDING ADDRESSES CONSTRUCTION
//
//		for(i=0;i<INDIRECT_BUFFER_SIZE;i++)
//		{
//			if (indirect_trans_queue[i].handler > 0x00)
//			{
//				pkt_ptr = (MPDU *)&indirect_trans_queue[i].frame;
//				//ADD INDIRECT TRANSMISSION DESCRIPTOR
//				if(get_fc2_dest_addr(pkt_ptr->frame_control2) == SHORT_ADDRESS)
//				{
//					short_addr_pending++;
//					packet_length = packet_length + 2;
//					mac_beacon_txmpdu_ptr->data[data_count]=pkt_ptr->data[2];
//					data_count++;
//					mac_beacon_txmpdu_ptr->data[data_count]=pkt_ptr->data[3];
//					data_count++;
//				}
//			}
//		}
//		for(i=0;i<INDIRECT_BUFFER_SIZE;i++)
//		{
//			if (indirect_trans_queue[i].handler > 0x00)
//			{
//				if(get_fc2_dest_addr(pkt_ptr->frame_control2) == LONG_ADDRESS)
//				{
//					long_addr_pending++;
//					packet_length = packet_length + 8;
//
//					mac_beacon_txmpdu_ptr->data[data_count]=pkt_ptr->data[0];
//					data_count++;
//					mac_beacon_txmpdu_ptr->data[data_count]=pkt_ptr->data[1];
//					data_count++;
//					mac_beacon_txmpdu_ptr->data[data_count]=pkt_ptr->data[2];
//					data_count++;
//					mac_beacon_txmpdu_ptr->data[data_count]=pkt_ptr->data[3];
//					data_count++;
//					mac_beacon_txmpdu_ptr->data[data_count]=pkt_ptr->data[4];
//					data_count++;
//					mac_beacon_txmpdu_ptr->data[data_count]=pkt_ptr->data[5];
//					data_count++;
//					mac_beacon_txmpdu_ptr->data[data_count]=pkt_ptr->data[6];
//					data_count++;
//					mac_beacon_txmpdu_ptr->data[data_count]=pkt_ptr->data[7];
//					data_count++;
//					
//				}
//			}
//		}
//			
//	}
//	mac_beacon_txmpdu_ptr->data[pending_data_index] = set_pending_address_specification(short_addr_pending,long_addr_pending);
//	*/	
//	/*
//	//adding the beacon payload
//	if (mac_PIB.macBeaconPayloadLenght > 0 )
//	{
//		for (i=0;i < mac_PIB.macBeaconPayloadLenght;i++)
//		{
//			mac_beacon_txmpdu_ptr->data[data_count] = mac_PIB.macBeaconPayload[i];
//			data_count++;
//			packet_length++;
//		}
//	
//	
//	}
//	*/
//		
//	//short_addr_pending=0;
//	//long_addr_pending=0;
//		
//	mac_beacon_txmpdu_ptr->length = packet_length;
//	return 0;
}

HAL_INLINE uint8_t set_pending_address_fields(uint8_t *pf)
{
	OZB_MAC_PENDING_ADDR_SPEC_SET_EMPTY(pf);
	/* 
	OZB_MAC_PENDING_ADDR_SPEC_SET_SHORTS(pf, 0);
	OZB_MAC_PENDING_ADDR_SPEC_SET_EXTDS(pf, 0);
	*/
	return 1;
}

HAL_INLINE uint8_t set_beacon_payload(uint8_t *bp)
{
	return 0;
}

/******************************************************************************/
/*                      MAC Layer General Functions                           */
/******************************************************************************/
int8_t ozb_mac_init(void) 
{
	int8_t retv = 1;

	#ifdef OZB_DEBUG_LOG
	if (ozb_debug_init() < 0)
		return -OZB_MAC_DEBUG_INIT_ERROR;
	#endif
	ozb_rand_init();
	retv = ozb_phy_init();
	if (retv < 0)
		return retv;
	retv = ozb_mac_sf_init();
	if (retv < 0)
		return retv;
	set_default_mac_pib();
	//return -OZB_MAC_INIT_ERROR;
	ozb_mac_status.mac_initialized = 1;
	return 1;
}

uint8_t ozb_mac_create_beacon(ozb_mpdu_ptr_t beacon)
{
	uint8_t s;
	ozb_mac_dev_addr_short_t addr = 0xFFFF;

	/* TODO: change this hard-coding! */
	set_frame_control(OZB_MAC_MPDU_FRAME_CONTROL(beacon), 
			  OZB_MAC_TYPE_BEACON, 0, 0, 0, 1, 
			  OZB_MAC_ADDRESS_SHORT, OZB_MAC_ADDRESS_SHORT);
	*OZB_MAC_MPDU_SEQ_NUMBER(beacon) = ozb_mac_pib.macBSN++;
	/* TODO: change this hard-coding: what do I set for source_PANID? */	
	s = set_addressing_fields(OZB_MAC_MPDU_ADDRESSING_FIELDS(beacon),
				  OZB_MAC_ADDRESS_SHORT, ozb_mac_pib.macPANId, 
				  (void *) &addr, OZB_MAC_ADDRESS_SHORT, 0, 
				  &(ozb_mac_pib.macShortAddress));
	/* TODO: think to security infos? */
	/* TODO: change this hard-coding: what do I set for BLE? */	
	s += set_superframe_specification(OZB_MAC_MPDU_MAC_PAYLOAD(beacon, s),
					  ozb_mac_pib.macBeaconOrder, 
					  ozb_mac_pib.macSuperframeOrder, 
					  ozb_gts_get_last_cap_stlot(), 0, 
					  ozb_mac_status.is_coordinator, 
					  ozb_mac_pib.macAssociationPermit);
	s += ozb_gts_set_gts_fields(OZB_MAC_MPDU_MAC_PAYLOAD(beacon, s));
	s += set_pending_address_fields(OZB_MAC_MPDU_MAC_PAYLOAD(beacon, s));
	s += set_beacon_payload(OZB_MAC_MPDU_MAC_PAYLOAD(beacon, s));
	/* TODO: compute FCS , use auto gen? */
	//*((uint16_t *) OZB_MAC_MPDU_MAC_FCS(beacon, s)) = 0;
	//s += OZB_MAC_MPDU_MHR_BASE_SIZE + OZB_MAC_MPDU_MFR_SIZE;
	s += OZB_MAC_MPDU_MHR_BASE_SIZE;
	return s;
}
