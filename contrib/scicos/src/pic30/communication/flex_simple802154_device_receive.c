#include <ee.h>
#include <machine.h>		// TODO: serve?
#include <scicos_block4.h>
#include <string.h>
#include "flex_simple802154.h"

#ifndef __HAS_SIMPLE802154_D_CONFIG__
#error "FLEX 802.15.4 ERROR: A device configuration block is required."
#endif

static float rx_buffer[FLEX_SIMPLE802154_ADDRESSES][FLEX_SIMPLE802154_CHANNELS];

/* ---------------------------------------------------------------------------- 
|  Rx callback function:                                                       |
|                                                                              |
|  Called by the network stack when data have been received.                   |
 ---------------------------------------------------------------------------- */
static void rx_data(int8_t status, uint8_t *data, uint8_t len)
{
	EE_INT16 id, addr;

	flex_simple802154_packet_t *packet = (flex_simple802154_packet_t*) data;
	/* Check Packet */
	if (len != sizeof(flex_simple802154_packet_t)) 
	  	return;	/* Wrong size */
	if (packet->dst_addr != flex_simple802154_local_address)
		return;	/* Wrong destination */
	id = packet->data_id;
	if (id >= FLEX_SIMPLE802154_CHANNELS)
		return; /* Bad data identifier */
	addr = flex_simple802154_address_lookup(packet->src_addr);
	if (addr >= FLEX_SIMPLE802154_ADDRESSES) 
	  	return; /* Bad Address (unknown by the lookup table) */
	/* Put the float data into the data_id buffer */
	GetResource(flex_simple802154_rx_buffer_mutex);
	rx_buffer[addr][id] = packet->data;
	ReleaseResource(flex_simple802154_rx_buffer_mutex);
}

static void rx_init(scicos_block *block) 
{
	if (!flex_simple802154_flags.rx_initialized) {
		ozb_simple154_set_rx_callback(rx_data);
		flex_simple802154_flags.rx_initialized = 1;
	}
	flex_simple802154_add_lookup(block->ipar[1]); /* ipar[1] := src_addr */
}

static void rx_end(void)
{
	return;
	/* TODO: do something! : clen lookup table? */
	flex_simple802154_flags.rx_initialized = 0;
}

static void rx_inout(scicos_block *block)
{
	EE_UINT16 id, addr;

	/* ipar[0] := data_id, ipar[1] := src_addr */
	id = block->ipar[0];
	addr = flex_simple802154_address_lookup(block->ipar[1]); 
	if (addr >= FLEX_SIMPLE802154_ADDRESSES)
		return;
	GetResource(flex_simple802154_rx_buffer_mutex);
	*((float *) block->outptr[0]) = rx_buffer[addr][id];
	ReleaseResource(flex_simple802154_rx_buffer_mutex);
}



void flex_simple802154_device_receive(scicos_block *block, int flag)
{
	switch (flag) {
	case OutputUpdate:  /* set output */
		rx_inout(block);
		break;
	case StateUpdate: /* get input */
		break;
	case Initialization:  /* initialisation */
		rx_init(block);
		break;
	case Ending:  /* ending */
		rx_end();
		break;
	}
}


