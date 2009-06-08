#include <machine.h>
#include <scicos_block4.h>
#include "flex_simple802154.h"

#ifndef __HAS_SIMPLE802154_C_CONFIG__
#error "FLEX 802.15.4 ERROR: A coordinator configuration block is required."
#endif

#define COORDINATOR_USE_GTS 0

static void tx_init(void) 
{
	/* TODO: do something? */
}

static void tx_end(void)
{
	/* TODO: do something? */
}

static void tx_inout(scicos_block *block)
{
	flex_simple802154_packet_t packet;
	float *y = block->inptr[0];
	
	/* ipar[0] := data_id, ipar[1] := dst_addr */
	packet.data = *y;
	packet.data_id = block->ipar[0];	
	packet.dst_addr = block->ipar[1]; 
	packet.src_addr = flex_simple802154_local_address; 
	ozb_simple154_send((EE_UINT8 *) &packet, 
			   sizeof(flex_simple802154_packet_t), 
			   block->ipar[1], COORDINATOR_USE_GTS);
}

void flex_simple802154_coordinator_send(scicos_block *block, int flag)
{
	switch (flag) {
	case OutputUpdate:  	/* set output */
		tx_inout(block); 
		break;
	case StateUpdate: 	/* get input */
		break;
	case Initialization:  	/* initialisation */
		tx_init();
		break;
	case Ending:  		/* ending */
		tx_end();
		break;
	}
}


