#ifndef __ozb_simple154_h__
#define __ozb_simple154_h__

//#include "util/ozb_memory.h" 	/* chris: test cqueue from lib memory */
//#include "util/ozb_debug.h"	/* chris: test ozb_debug */
//#include "hal/ozb_radio.h"	/* chris: test ozb osal */
//#include "kal/ozb_kal.h"	/* chris: test ozb osal */
//#include <phy/ozb_phy.h>
#include <mac/ozb_mac.h>

#define OZB_IEEE802154_ERR_NONE 		1 /* Returned as positive! */
#define OZB_IEEE802154_ERR_INITMAC 		1 
#define OZB_IEEE802154_ERR_SETADDR 		2 
#define OZB_IEEE802154_ERR_STARTMAC 		3 
#define OZB_IEEE802154_ERR_ASSOCIATE 		4 
#define OZB_IEEE802154_ERR_ALREADYINIT		5 
#define OZB_IEEE802154_ERR_NOTINIT		6 
#define OZB_IEEE802154_ERR_NOTSUPPORTED		7 
#define OZB_IEEE802154_ERR_DATAREQ		8 
#define OZB_IEEE802154_ERR_DATACONFIRM		9 
#define OZB_IEEE802154_ERR_GTS_MANIPULATION	10 
#define OZB_IEEE802154_ERR_GTS_NOTCOORDINATOR	11

void ozb_simple154_set_rx_callback(void (*func) (int8_t, uint8_t*, uint8_t));

int8_t ozb_simple154_init_coordinator(uint16_t coordinator_id, uint16_t pan_id,
				      uint8_t channel, uint8_t bo, uint8_t so);

int8_t ozb_simple154_init_device(uint16_t device_id, uint16_t coordinator_id, 
				 uint16_t pan_id, uint8_t channel);

int8_t ozb_simple154_send(uint8_t *data, uint8_t len, uint16_t dst_device_id, 
			  uint8_t use_gts);

int8_t ozb_simple154_gts_clear(void); 

int8_t ozb_simple154_gts_add(uint16_t device_id, uint8_t length, uint8_t dir);

#endif /* Header Protection */
