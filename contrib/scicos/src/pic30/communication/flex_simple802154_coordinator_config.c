#include <machine.h>
#include <scicos_block4.h>
#include "flex_simple802154.h"

#ifdef __HAS_SIMPLE802154_D_CONFIG__
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
	.is_coordinator		= 1,
	.reserved		= 0
};	

static void cfg_init(scicos_block *block)
{	
	EE_INT8 i, retv, idx;

	if (flex_simple802154_flags.cfg_initialized)
		return;
	/* ipar[0] := local_address 
	 * ipar[1] := pan_id 
	 * ipar[2] := channel_id 
	 * ipar[3] := BeaconOrder 
	 * ipar[4] := SuperframeOrder 
	 * ipar[5] := gts1_addr 
	 * ipar[6] := gts1_len 
	 * ipar[7] := gts1_dir 
	 * ipar[8] := gts2_addr 
	 * ipar[9] := gts2_len 
	 * ipar[10] := gts2_dir 
	 * ipar[11] := gts3_addr 
	 * ipar[12] := gts3_len 
	 * ipar[13] := gts3_dir 
	 * ipar[14] := gts4_addr 
	 * ipar[15] := gts4_len 
	 * ipar[16] := gts4_dir 
	 * ipar[17] := gts5_addr 
	 * ipar[18] := gts5_len 
	 * ipar[19] := gts5_dir 
	 * ipar[20] := gts6_addr 
	 * ipar[21] := gts6_len 
	 * ipar[22] := gts6_dir 
	 * ipar[23] := gts7_addr 
	 * ipar[24] := gts7_len 
	 * ipar[25] := gts7_dir
	*/
	flex_simple802154_local_address = block->ipar[0];
	retv = ozb_simple154_init_coordinator(block->ipar[0], block->ipar[1],
					      block->ipar[2], block->ipar[3], 
					      block->ipar[4]);
	if (retv < 0)
		return;
	retv = ozb_simple154_gts_clear();
	if (retv < 0)
		return;
	for (i = 0; i < 7; i++) {
		idx = 5 + (i * 3);
		if (block->ipar[idx] != 0 && block->ipar[idx + 1] != 0) {
			retv = ozb_simple154_gts_add(block->ipar[idx], 
						     block->ipar[idx + 1],
						     block->ipar[idx + 2]);
			if (retv < 0)
				return;
		}
	}
	flex_simple802154_flags.is_coordinator = 1;
	flex_simple802154_flags.cfg_initialized = 1;
}

static void cfg_end(void)
{
	return;
	/* TODO: do something! */
	flex_simple802154_flags.cfg_initialized = 0;
}


void flex_simple802154_coordinator_config(scicos_block *block, int flag)
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


