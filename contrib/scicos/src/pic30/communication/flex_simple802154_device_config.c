#include <machine.h>
#include <scicos_block4.h>
#include <string.h>
#include "flex_simple802154.h"

#ifdef __HAS_SIMPLE802154_C_CONFIG__
#error FLEX 802.15.4 ERROR: usage of coordinator and device blocks \
	at the same time is forbidden.
#endif

EE_UINT16 flex_simple802154_address_table[FLEX_SIMPLE802154_ADDRESSES];
EE_UINT16 flex_simple802154_local_address;
flex_simple802154_flags_t flex_simple802154_flags = {
	.cfg_initialized 	= 0,
	.rx_initialized		= 0,
	.tx_initialized		= 0,
	.lookup_initialized	= 0,
	.is_coordinator		= 0,
	.reserved		= 0
};	

static void cfg_init(scicos_block *block)
{	
	EE_INT8 retv;

	if (flex_simple802154_flags.cfg_initialized)
		return;
	/* ipar[0] := local_address 
	 * ipar[1] := pan_id 
	 * ipar[2] := channel_id 
	 * ipar[3] := coordinator_address 
	*/
	flex_simple802154_local_address = block->ipar[0];
	retv = ozb_simple154_init_device(block->ipar[0], block->ipar[3],
					 block->ipar[1], block->ipar[2]);
	if (retv < 0)
		return;
	flex_simple802154_flags.is_coordinator = 0;
	flex_simple802154_flags.cfg_initialized = 1;
}

static void cfg_end(void)
{
	return;
	/* TODO: do something! */
	flex_simple802154_flags.cfg_initialized = 0;
}


void flex_simple802154_device_config(scicos_block *block, int flag)
{
	switch (flag) {
	case OutputUpdate:  /* set output */
		break;
	case StateUpdate: /* get input */
		break;
	case Initialization:  /* initialisation */
		cfg_init(block);
		break;
	case Ending:  /* ending */
		cfg_end();
		break;
	}
}


