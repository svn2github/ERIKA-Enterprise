#include <machine.h>
#include <scicos_block4.h>
#include <string.h>
#include "flex_simple802154.h"

#ifdef __HAS_SIMPLE802154_D_CONFIG__
#error "FLEX 802.15.4 ERROR: usage of coordinator and device blocks" \
	"at the same time is forbidden."
#endif

EE_UINT16 flex_simple802154_address_table[FLEX_SIMPLE802154_ADDRESSES];
EE_UINT16 flex_simple802154_local_address;

//EE_UINT16 flex_simple802154_address_count = 0;
static EE_UINT8 cfg_initialized = 0;

static void cfg_init(scicos_block *block)
{	
	EE_INT8 retv;

	if (cfg_initialized)
		return;
	memset(flex_simple802154_address_table, 0xFF, 
	       FLEX_SIMPLE802154_ADDRESSES * sizeof(EE_UINT16));
	/* TODO: init global params! */

	/* Configure SOURCE addresses for the ieee802154 stack 
	   - Set the GTS table (NOTE: GTS used onlu Device->Coordinator ONLY! 
	   - Set the reception address for the lookup table
	 */
//	for (i = 0; i < 4; i++)  // NOTE: 4 is the number of devices for GTS 
//		if (openzb_device_addresses[i] == block->ipar[1]) /*src_addr*/
//			break;
//	if (i == 4) { // The address is not in the GTS table, add it somewhere!
//		openzb_device_addresses[scicosOpenZB_address_count] = 
//							block->ipar[1];
//		scicosOpenZB_address_count = (scicosOpenZB_address_count + 1)%4;
//	}

	/* ipar[0] := local_address 
	 * ipar[1] := pan_id 
	 * ipar[2] := channel_id 
	 * ipar[3] := BeaconOrder 
	 * ipar[4] := SuperframeOrder 
	*/
	flex_simple802154_local_address = block->ipar[0];
	retv = ozb_simple154_init_coordinator(block->ipar[0], block->ipar[1],
					      block->ipar[2], block->ipar[3], 
					      block->ipar[4]);
	if (retv < 0)
		return;
//	retv = ozb_simple154_gts_clear();
//	if (retv < 0)
//		return;
//	retv = ozb_simple154_gts_add(TEST_DEV_A_ADDR, TEST_DEV_GTS_LEN,
//				     OZB_MAC_GTS_DIRECTION_OUT);
//	if (retv < 0)
//		return;
	cfg_initialized = 1;
}

static void cfg_end(void)
{
	return;
	/* TODO: do something! */
	cfg_initialized = 0;
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


