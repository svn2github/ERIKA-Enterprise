//** 9 Feb 2008 : Revision notes by Simone Mannori 
//**

#include <machine.h>
#include <scicos_block4.h>

#include <ee.h>

#include "scicos_openZB.h"

/*
*/


static void init(scicos_block *block)
{

}

static void inout(scicos_block *block)
{
	float inputdata;
	float *y = block->inptr[0];
	unsigned char datasize;
	unsigned char buf[32];

	/* Build the openZB payload for scicos */
	ScicosOpenZB_Payload packet;
	packet.channel_id = block->ipar[0];
	//memcpy(y, packet.data, sizeof(float));
  packet.data = *y;
	/* Send the packet using GTS */
	openZB_send_bytes(&packet, sizeof(ScicosOpenZB_Payload), 0);
}

static void end(scicos_block *block)
{
}

void flex_zigbee_send(scicos_block *block,int flag)
{
	switch (flag) {
		case 1:	/* set output */
			inout(block);
			break;

		case 2:	/* get input */
			inout(block);
			break;
		
		case 4:	/* initialisation */
			init(block);
			break;
		
		case 5:	/* ending */
			end(block);
			break;
	}
}
