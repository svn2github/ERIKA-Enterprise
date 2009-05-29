#include <mac/ozb_mac_internal.h>
#include <hal/ozb_radio.h>
#include <util/ozb_memory.h>
#include <util/ozb_debug.h>

/******************************************************************************/
/*                            MAC GTS Private Data                            */
/******************************************************************************/
LIST_DEFINE_STATIC(gts_list, struct ozb_gts_info_t , OZB_MAC_GTS_MAX_NUMBER);

/******************************************************************************/
/*                        MAC GTS Private Functions                           */
/******************************************************************************/
static int8_t gts_add_entry(ozb_mac_dev_addr_short_t dev_addr, 
			    uint8_t len, uint8_t dir) 
{
	struct ozb_gts_info_t *entry;

	if (len > OZB_MAC_SUPERFRAME_LAST_SLOT || dir > 1) 
		return -2; /* invalid params values */
	/*TODO: check aMinCAPLength, calculate the minCAP in slot and use it
		instead of 1
	*/
	if (list_is_full(&gts_list) || ozb_mac_gts_stat.first_cfp_tslot < len+1)
		return -1;
	for (entry = (struct ozb_gts_info_t *) list_iterator_head(&gts_list); 
	     entry != 0;
             entry = (struct ozb_gts_info_t *) list_iterate(&gts_list)) 
		if (entry->dev_address == dev_addr && entry->direction == dir)
			return 0; /*TODO: check. already added, make sense? */
	ozb_mac_gts_stat.first_cfp_tslot -= len;
	entry = list_add(&gts_list); /* NOTE: already checked if full! */
	entry->starting_tslot = ozb_mac_gts_stat.first_cfp_tslot;
	entry->length = len;
	entry->direction = dir;
	entry->dev_address = dev_addr;
	entry->expiration = 0x00; /* TODO: un-hardcode!!! */
	//ozb_mac_gts_stat.descriptor_count++;
	return 1;
}

COMPILER_INLINE void gts_clean_db(void) 
{
	list_clear(&gts_list);
	ozb_mac_gts_stat.first_cfp_tslot = OZB_MAC_SUPERFRAME_LAST_SLOT;
	ozb_mac_gts_stat.tx_start_tslot = 0;
	ozb_mac_gts_stat.tx_length = 0;
	ozb_mac_gts_stat.rx_start_tslot = 0;
	ozb_mac_gts_stat.rx_length = 0;
}

COMPILER_INLINE void set_gts_descriptor(uint8_t *des, 
					ozb_mac_dev_addr_short_t addr, 
					uint8_t tslot, uint8_t len)
{
	//memcpy(des, &addr, sizeof(ozb_mac_dev_addr_short_t));
	des[0] = addr & 0x00FF;
	des[1] = addr >> 8;
	des[2] = (len << 4) | (tslot & 0x0F);
}

/******************************************************************************/
/*                        MAC GTS General Functions                           */
/******************************************************************************/
int8_t ozb_mac_gts_init(void) 
{
	gts_clean_db();
	/* TODO: parse return values! */
	gts_add_entry(0x0002, 1, OZB_MAC_GTS_DIRECTION_OUT);
	gts_add_entry(0x0003, 3, OZB_MAC_GTS_DIRECTION_OUT);
	gts_add_entry(0x0004, 2, OZB_MAC_GTS_DIRECTION_OUT);
	return 1;
}

uint8_t ozb_mac_gts_set_gts_fields(uint8_t *gf) 
{
	struct ozb_gts_info_t *entry;
	uint8_t *tmp;
	uint8_t i = 0;
	uint8_t s = OZB_MAC_MPDU_GTS_SPEC_SIZE;

	if (ozb_mac_pib.macGTSPermit == 0) {
		OZB_MAC_GTS_SPEC_SET_EMPTY(gf);
		return s;
	}
	OZB_MAC_GTS_SPEC_SET_DESCRIPTOR_COUNT(gf, list_get_size(&gts_list));
	OZB_MAC_GTS_SPEC_SET_PERMIT(gf, ozb_mac_pib.macGTSPermit);
	if (list_is_empty(&gts_list))
		return s;
	tmp = gf + s;
	s += OZB_MAC_MPDU_GTS_DIRECTIONS_SIZE;
	for (entry = (struct ozb_gts_info_t *) list_iterator_head(&gts_list); 
	     entry != 0;
             entry = (struct ozb_gts_info_t *) list_iterate(&gts_list)) {
		OZB_MAC_GTS_DIRECTION_SET(tmp, i, entry->direction);
		set_gts_descriptor(gf + s, entry->dev_address,  
				   entry->starting_tslot, entry->length); 
		s += OZB_MAC_MPDU_GTS_DESCRIPTOR_SIZE;
		i++;
	}
	/* TODO: remove this! DEBUG TEST!!! ---------- >>>>> */
	static uint16_t aaa = 0x0005;
	//static char bbb = 1;
	if (gts_add_entry(aaa++, 1, OZB_MAC_GTS_DIRECTION_OUT) == -1) {
		gts_clean_db();
		gts_add_entry(0x0002, 1, OZB_MAC_GTS_DIRECTION_OUT);
		gts_add_entry(0x0003, 3, OZB_MAC_GTS_DIRECTION_OUT);
		gts_add_entry(0x0004, 2, OZB_MAC_GTS_DIRECTION_OUT);
		//if (bbb) {
		//	ozb_mac_pib.macBeaconOrder++;
		//	bbb = 0;
		//} else {
		//	ozb_mac_pib.macBeaconOrder--;
		//	bbb = 1;
		//}
	}
	/* <<<<<<<<<<<<-----------------  TODO REMOVE BLOCK!!! */
	return s;
}

uint8_t ozb_mac_gts_get_gts_fields(uint8_t *gf) 
{
	uint8_t *tmp;
	uint8_t cnt;
	uint8_t i = 0;
	uint8_t s = OZB_MAC_MPDU_GTS_SPEC_SIZE;

	ozb_mac_pib.macGTSPermit = OZB_MAC_GTS_SPEC_GET_PERMIT(gf);
	if (ozb_mac_pib.macGTSPermit == 0) 
		return s;
	cnt = OZB_MAC_GTS_SPEC_GET_DESCRIPTOR_COUNT(gf);
	tmp = gf + s;
	s += OZB_MAC_MPDU_GTS_DIRECTIONS_SIZE;
	/* NOTE: if the GTS descriptor list is malformed (more than one GTS
		 in tx or more than one in rx) this shall take the last one! */
	for (i = 0; i < cnt; i++) {
		if (OZB_MAC_GTS_DES_GET_ADDRESS(gf + s) == 
		    ozb_mac_pib.macShortAddress) {
			if (OZB_MAC_GTS_DIRECTION_GET(tmp, i) == 
			    OZB_MAC_GTS_DIRECTION_OUT) {
				ozb_mac_gts_stat.tx_start_tslot =
					OZB_MAC_GTS_DES_GET_START_SLOT(gf + s);
				ozb_mac_gts_stat.tx_length =
					OZB_MAC_GTS_DES_GET_LENGTH(gf + s);
			} else {
				ozb_mac_gts_stat.rx_start_tslot =
					OZB_MAC_GTS_DES_GET_START_SLOT(gf + s);
				ozb_mac_gts_stat.rx_length =
					OZB_MAC_GTS_DES_GET_LENGTH(gf + s);
			}
		}
		s += OZB_MAC_MPDU_GTS_DESCRIPTOR_SIZE;
	}
	return s;
}






#ifdef compila_merda_di_ricardo

/*****************************************************/
/*				GTS Variables	//RARS				     */
/*****************************************************/  
//GTS descriptor variables, coordinator usage only
EE_UINT8 final_CAP_slot=15;
EE_UINT8 GTS_descriptor_count=0;
GTSinfoEntryType GTS_db[7] __attribute__((far));
EE_UINT8 GTS_startslot=16;
EE_UINT8 GTS_id=0x01;
//null gts descriptors
GTSinfoEntryType_null GTS_null_db[7] __attribute__((far));
EE_UINT8 GTS_null_descriptor_count=0;

//COORDINATOR GTS BUFFER 	
gts_slot_element gts_slot_list[7] __attribute__((far));
EE_UINT8 available_gts_index[GTS_SEND_BUFFER_SIZE] __attribute__((far));
EE_UINT8 available_gts_index_count;
EE_UINT8 coordinator_gts_send_pending_data=0;
EE_UINT8 coordinator_gts_send_time_slot=0;


EE_UINT8 gts_schedule[16] __attribute__((far)); //for translation between timeslots and gtss

EE_UINT8 gts_confirm; //confirms that the GTS slot is present in the beacon

EE_UINT8 GTS_specification;
EE_UINT8 gts_expiration;

//node GTS variables
// 1 GTS for transmit
EE_UINT8 s_GTSss=0;           //send gts start slot
EE_UINT8 s_GTS_length=0;		 //send gts length

//1 GTS for receive
EE_UINT8 r_GTSss=0;			 //receive gts start slot
EE_UINT8 r_GTS_length=0;		 //receive gts lenght

//used to state that the device is on its transmit slot
EE_UINT8 on_s_GTS=0;
//used to state that the device is on its receive slot
EE_UINT8 on_r_GTS=0;

//used to determine if the next time slot is used for transmission
EE_UINT8 next_on_s_GTS=0;
//used to determine if the next time slot is used for reception
EE_UINT8 next_on_r_GTS=0;

//variable stating if the coordinator allow GTS allocations
EE_UINT8 allow_gts=1;

//gts buffer used to store the gts messages both in COORDINATOR and NON COORDINATOR
MPDU gts_send_buffer[GTS_SEND_BUFFER_SIZE] __attribute__((far));

//NON PAN COORDINATOR BUFFER management
//buffering for sending
EE_UINT8 gts_send_buffer_count=0;
EE_UINT8 gts_send_buffer_msg_in=0;
EE_UINT8 gts_send_buffer_msg_out=0;
EE_UINT8 gts_send_pending_data=0;


//////////////////////////////////////////////////////////////
////////////////////////GTS functions////////////////////////
/////////////////////////////////////////////////////////////

void init_GTS_db()
{
	//initialization of the GTS database
	EE_UINT8 i;

	for (i=0 ; i < 7 ; i++)
		{
			GTS_db[i].gts_id=0x00;
			GTS_db[i].starting_slot=0x00;
			GTS_db[i].length=0x00;
			GTS_db[i].direction=0x00;
			GTS_db[i].DevAddressType=0x0000;
		
		}
		
		memset(gts_schedule,255,sizeof(gts_schedule));
	
return;
}
/*//RARS TODO REMOVE GTS FUNCTION
result_t remove_gts_entry(uint16_t DevAddressType)
{
	int r_lenght=0;
	//int r_start_slot=7;
	int i;
	atomic{
		for (i=0; i < 7 ; i++)
		{
			if( GTS_db[i].DevAddressType == DevAddressType )
			{
				
				r_lenght = GTS_db[i].length;
				//r_start_slot = i;
				//delete the values
				GTS_db[i].gts_id=0x00;
				GTS_db[i].starting_slot=0x00;
				GTS_db[i].length=0x00;
				GTS_db[i].direction=0x00;
				GTS_db[i].DevAddressType=0x0000;
				GTS_db[i].expiration=0x00;
				
				//////////////////printfUART("GTS Entry removed dev:%i len:%i pos %i\n", DevAddressType,r_lenght,i);
				GTS_startslot = GTS_startslot + r_lenght;
				GTS_descriptor_count--;
				final_CAP_slot = final_CAP_slot + r_lenght;
			}
			
			if ( r_lenght > 0)
			{
				if ( GTS_db[i].gts_id != 0x00 && GTS_db[i].DevAddressType !=0x0000)
				{				
					GTS_db[i-r_lenght].gts_id = GTS_db[i].gts_id;
					GTS_db[i-r_lenght].starting_slot = i-r_lenght;
					GTS_db[i-r_lenght].length = GTS_db[i].length;
					GTS_db[i-r_lenght].direction = GTS_db[i].direction;
					GTS_db[i-r_lenght].DevAddressType = GTS_db[i].DevAddressType;
					GTS_db[i-r_lenght].expiration = GTS_db[i].expiration;
					
					//delete the values
					GTS_db[i].gts_id=0x00;
					GTS_db[i].starting_slot=0x00;
					GTS_db[i].length=0x00;
					GTS_db[i].direction=0x00;
					GTS_db[i].DevAddressType=0x0000;
					GTS_db[i].expiration=0x00;
					
					//////////////////printfUART("UPDATED\n","" );
				}
			}
		}
	}
return SUCCESS;
}
*/

EE_UINT8 add_gts_entry(EE_UINT8 gts_length,EE_UINT8 direction,EE_UINT16 DevAddressType, EE_UINT16 GTS_startslotindex)
{
	EE_UINT8 i;

	//RARS TODO
	//check aMinCAPLength maybe use a global variable with the number of alocated gtss
	if (GTS_descriptor_count >= 7)
		{
			return 0;
		}
	
	//check if the address already exists in the GTS list
	for (i=0 ; i < 7 ; i++)
	{
		if ( GTS_db[i].DevAddressType == DevAddressType && GTS_db[i].direction == direction && GTS_db[i].gts_id > 0)
		{
			//////////////////printfUART("ALREADY ADDED\n", ""); 
			return 0;
		}
		if ( GTS_null_db[i].DevAddressType == DevAddressType && GTS_null_db[i].gts_id > 0)
		{
			//////////////////printfUART("REJECTED\n", ""); 
			return 0;
		}

	}

	////////printfUART("GTS_startslot: %i\n", GTS_startslot); 
	//GTS_startslot = GTS_startslot - gts_length;
	
	GTS_startslot = GTS_startslotindex;

	GTS_db[GTS_descriptor_count].gts_id=GTS_id;
	GTS_db[GTS_descriptor_count].starting_slot=GTS_startslot;
	GTS_db[GTS_descriptor_count].length=gts_length;
	GTS_db[GTS_descriptor_count].direction=direction;
	GTS_db[GTS_descriptor_count].DevAddressType=DevAddressType;
	GTS_db[GTS_descriptor_count].expiration=0x00;

	////////printfUART("GTS Entry added start:%i len:%i\n", GTS_startslot,gts_length); 
	
	//CHANGED FOR WC DIMENSIONING
	for(i=GTS_startslot; i < GTS_startslot+ gts_length ; i++)
		gts_schedule[i] = GTS_descriptor_count;
	
	GTS_id++;
	GTS_descriptor_count++;
	
	final_CAP_slot = final_CAP_slot - gts_length; //update final cap slot
	
	
	//for(i=0; i<16; i++)
		////printfUART("GTS schedule: %i len:%i\n",i, gts_schedule[i]); 
	return 1;
}


//GTS null functions
void init_GTS_null_db()
{
	//initialization of the GTS database
	EE_UINT8 i;
		for (i=0 ; i < 7 ; i++)
		{
			GTS_null_db[i].gts_id=0x00;
			GTS_null_db[i].starting_slot=0x00;
			GTS_null_db[i].length=0x00;
			//GTS_null_db[i].direction=0x00;
			GTS_null_db[i].DevAddressType=0x0000;
			GTS_null_db[i].persistencetime=0x00;
		}
	
return;
}

void init_available_gts_index()
{
	EE_UINT8 i;
		
	available_gts_index_count = GTS_SEND_BUFFER_SIZE;
	for(i=0;i < GTS_SEND_BUFFER_SIZE;i++)
		{
			available_gts_index[i]=i;
		}
	return;
}
	
/*****************************GTS BUFFER******************************/
void init_gts_slot_list()
{
	EE_UINT8 i;
	
	for(i=0;i<7;i++)
	{
		gts_slot_list[i].element_count = 0x00;
		gts_slot_list[i].element_in = 0x00;
		gts_slot_list[i].element_out = 0x00;
	}
}
//RARS todo 
	/*
	void create_gts_request_cmd(uint8_t gts_characteristics)
	{
	atomic{
		cmd_gts_request *mac_gts_request;
		
		MPDU *frame_pkt;
		
		uint16_t frame_control;
		////printfUART("create_gts_request_cmd\n", "");
		
		
		if (send_buffer_msg_in == SEND_BUFFER_SIZE)
			send_buffer_msg_in=0;

		frame_pkt = (MPDU *) &send_buffer[send_buffer_msg_in];
		
		mac_gts_request= (cmd_gts_request*) &send_buffer[send_buffer_msg_in].data;

		frame_pkt->length = 11;
	
		if ( get_characteristic_type(gts_characteristics) != 0 )
		{   
			//frame_pkt->frame_control = set_frame_control(TYPE_CMD,0,0,1,1,0,SHORT_ADDRESS);   //dest | source
		
			frame_control = set_frame_control(TYPE_CMD,0,0,1,1,0,SHORT_ADDRESS); 
			frame_pkt->frame_control1 =(uint8_t)( frame_control);
			frame_pkt->frame_control2 =(uint8_t)( frame_control >> 8);
		}
		else
		{	
			//frame_pkt->frame_control = set_frame_control(TYPE_CMD,0,0,1,1,0,SHORT_ADDRESS);
			
			frame_control = set_frame_control(TYPE_CMD,0,0,1,1,0,SHORT_ADDRESS);
			frame_pkt->frame_control1 =(uint8_t)( frame_control);
			frame_pkt->frame_control2 =(uint8_t)( frame_control >> 8);
		}
		
		frame_pkt->seq_num = mac_PIB.macDSN;
		
		gts_request_seq_num = frame_pkt->seq_num;
		
		mac_PIB.macDSN++;
		
		//enable retransmissions
		send_buffer[send_buffer_msg_in].retransmission =1;
		send_buffer[send_buffer_msg_in].indirect = 0;
		
		//mac_gts_request->source_PAN_identifier = 0x0001;
		mac_gts_request->source_PAN_identifier = mac_PIB.macPANId;
		
		mac_gts_request->source_address = mac_PIB.macShortAddress;
	
		mac_gts_request->command_frame_identifier = CMD_GTS_REQUEST;
		
		//mac_gts_request->gts_characteristics = set_gts_characteristics(2,1,1);
		mac_gts_request->gts_characteristics =gts_characteristics;
		
		//increment the send buffer variables
		send_buffer_count++;
		send_buffer_msg_in++;
		
		post send_frame_csma();
		
		}

	return;
	}
*/
#endif 
