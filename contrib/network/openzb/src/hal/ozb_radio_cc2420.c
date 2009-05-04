/**
* @file ozb_radio_cc2420.c
* @brief Abstract Radio functions
* @author Gianluca Franchino
* @author Christian Nastasi
* @author Mauro Nino Marinoni
* @date 2009-03-24
*
* This file contains the abstraction layer for the radio capabilities
* used by the OpenZB modules.
*
*/

#include <hal/ozb_radio_cc2420.h>
//#include <mac/ozb_mac_internal.h>

static ozb_mpdu_t beacon;
static uint8_t beacon_size;

int8_t ozb_radio_store_beacon(ozb_mpdu_ptr_t bcn, uint8_t size)
{
	if (size >= OZB_MAC_MPDU_SIZE)
		return -1;
	memcpy(beacon, bcn, size);
	beacon_size = size;
	return 1;
}

int8_t ozb_radio_send_beacon(void)
{
	return ozb_radio_send((uint8_t *) beacon, beacon_size); 
}

