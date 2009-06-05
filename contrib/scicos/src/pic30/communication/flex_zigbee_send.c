//** 9 Feb 2008 : Revision notes by Simone Mannori 
//**

#include <machine.h>
#include <scicos_block4.h>

#include <ee.h>

#include "scicos_openZB.h"


static void init(scicos_block *block)
{
	#ifdef DEVICE_TYPE_COORDINATOR
	unsigned int i;

	/* Configure SOURCE address for the ieee802154 stack */
	openzb_device_address = 0x00FF; /* FIXME: now address ignored!!! */
	//openzb_device_address = block->ipar[1]; // in future is src_addr 
	/* NOTE: no need to store the destination address! */
	#else
	/* Configure SOURCE address for the ieee802154 stack */
	openzb_device_address = block->ipar[1]; /* ipar[1] = src_addr */
	/* NOTE: no need to store the destination address! */
	#endif
}

static void inout(scicos_block *block)
{
	float *y = block->inptr[0];
	ScicosOpenZB_Payload packet;

	/* Build the openZB payload for scicos */
	packet.channel_id = block->ipar[0];	
	packet.src_addr = block->ipar[1]; /*ipar[1]=src_addr*/
	#ifdef DEVICE_TYPE_COORDINATOR
	packet.dst_addr = block->ipar[2]; /*ipar[1]=dst_addr*/
	#else
	packet.dst_addr = 0x00FF; /*TODO: force coordinator, ipar[1]=dst_addr*/
	#endif
	packet.data = *y;
	/* Send the packet using GTS */
	#ifdef DEVICE_TYPE_COORDINATOR
	openZB_send_bytes(&packet, sizeof(ScicosOpenZB_Payload), 0);
	#else
	openZB_send_bytes(&packet, sizeof(ScicosOpenZB_Payload), 1);
	#endif
}

static void end(scicos_block *block)
{
}

void flex_zigbee_send(scicos_block *block,int flag)
{
 switch (flag) {
    case OutputUpdate:  /* set output */
      inout(block);
      break;

    case StateUpdate: /* get input */
      break;

    case Initialization:  /* initialisation */
      init(block);
      break;

    case Ending:  /* ending */
      end(block);
      break;
  }
}
