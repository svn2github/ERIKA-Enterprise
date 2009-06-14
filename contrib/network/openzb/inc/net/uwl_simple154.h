#ifndef __uwl_simple154_h__
#define __uwl_simple154_h__

#include <mac/uwl_mac.h>

#define UWL_SIMPLE154_ERR_NONE 			1 /* Returned as positive! */
#define UWL_SIMPLE154_ERR_INITMAC 			1 
#define UWL_SIMPLE154_ERR_SETADDR 			2 
#define UWL_SIMPLE154_ERR_STARTMAC 			3 
#define UWL_SIMPLE154_ERR_ASSOCIATE 			4 
#define UWL_SIMPLE154_ERR_ALREADYINIT			5 
#define UWL_SIMPLE154_ERR_NOTINIT			6 
#define UWL_SIMPLE154_ERR_NOTSUPPORTED			7 
#define UWL_SIMPLE154_ERR_DATAREQ			8 
#define UWL_SIMPLE154_ERR_DATACONFIRM			9 
#define UWL_SIMPLE154_ERR_GTS_MANIPULATION		10 
#define UWL_SIMPLE154_ERR_GTS_NOTCOORDINATOR		11
#define UWL_SIMPLE154_ERR_INVALID_LENGTH		12
#define UWL_SIMPLE154_ERR_SUPERFRAME_CALLBACKS_DISABLED 13

void uwl_simple154_set_rx_callback(void (*func) (int8_t, uint8_t*, uint8_t));

int8_t uwl_simple154_init_coordinator(uint16_t coordinator_id, uint16_t pan_id,
				      uint8_t channel, uint8_t bo, uint8_t so);

int8_t uwl_simple154_init_device(uint16_t device_id, uint16_t coordinator_id, 
				 uint16_t pan_id, uint8_t channel);

int8_t uwl_simple154_send(uint8_t *data, uint8_t len, uint16_t dst_device_id, 
			  uint8_t use_gts);

int8_t uwl_simple154_gts_clear(void); 

int8_t uwl_simple154_gts_add(uint16_t device_id, uint8_t length, uint8_t dir);

COMPILER_INLINE
int8_t uwl_simple154_set_beacon_payload(uint8_t *data, uint8_t len) 
{
	if (uwl_mac_set_beacon_payload(data, len) < 0)
		return -UWL_SIMPLE154_ERR_INVALID_LENGTH;
	return UWL_SIMPLE154_ERR_NONE;
}

COMPILER_INLINE
int8_t uwl_simple154_get_beacon_payload(uint8_t *data, uint8_t len)
{
	int8_t retv;
	
	retv = uwl_mac_get_beacon_payload(data, len);
	if (retv < 0)
		return -UWL_SIMPLE154_ERR_INVALID_LENGTH;
	return retv;
}
COMPILER_INLINE
int8_t uwl_simple154_set_on_beacon_callback(void (* func)(void)) 
{
	if (uwl_mac_set_on_beacon_callback(func) < 0)
		return -UWL_SIMPLE154_ERR_INVALID_LENGTH;
	return UWL_SIMPLE154_ERR_NONE;
}

COMPILER_INLINE
int8_t uwl_simple154_set_before_beacon_callback(void (* func)(void))
 {
	if (uwl_mac_set_before_beacon_callback(func) < 0)
		return -UWL_SIMPLE154_ERR_INVALID_LENGTH;
	return UWL_SIMPLE154_ERR_NONE;
}

#endif /* Header Protection */
