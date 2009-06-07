#include "flex_simple802154.h"

EE_UINT16 flex_simple802154_address_table[SCICOS_OPENZB_ADDRESSES];
EE_UINT16 flex_simple802154_local_address;

//EE_UINT16 flex_simple802154_address_count = 0;
static cfg_initialized = 0;

static void cfg_init(scicos_block *block)
{	
	EE_INT8 retv;

	if (cfg_initialized)
		return;
	memset(flex_simple802154_address_table, 0xFF, 
	       FLEX_SIMPLE802154_ADDRESSES * sizeof(EE_UINT16));
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
	cfg_initialized = 1;
}

static void cfg_end(void)
{
	return;
	/* TODO: do something! */
	cfg_initialized = 0;
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


