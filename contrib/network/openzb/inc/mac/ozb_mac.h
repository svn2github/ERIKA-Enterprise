#ifndef __ozb_mac_h__
#define __ozb_mac_h__

/* chris: TODO: solve conflict in the naming: OSB_MAC is used here but 
		also in the MAC enumerations. The PHY should be set as well */
//#define OZB_MAC_SUCCESS			1

#define OZB_MAC_INIT_ERROR		1
#define OZB_MAC_DEBUG_INIT_ERROR	2
#define OZB_MAC_INVALID_PARAM		3
#define OZB_MAC_STANDARD_UNSUPPORTED	4
#define OZB_MAC_SF_NOT_INITIALIZED	5
#define OZB_MAC_NOT_INITIALIZED		6

#include <mac/ozb_mac_const.h>
#include <mac/ozb_mac_types.h>	
#include <mac/ozb_mac_mcps.h>
#include <mac/ozb_mac_mlme.h>

#define OZB_SET_MAC_EXTD_ADDR(address, high, low) 	\
do {							\
	(address)[0] = (low);				\
	(address)[1] = (high);				\
} while (0)


#define OZB_GET_MAC_EXTD_ADDR(address, high, low) 	\
do {							\
	(low) = (address)[0];				\
	(high) = (address)[1];				\
} while (0)


int8_t ozb_mac_init(void); 

#endif /* Header Protection */
