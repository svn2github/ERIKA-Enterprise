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
	float *y = block->outptr[0];

	GetResource(scicosOpenZB_rx_buffer_mutex);
	
  *y = scicosOpenZB_rx_buffer[block->ipar[0]];

	ReleaseResource(scicosOpenZB_rx_buffer_mutex);
}

static void end(scicos_block *block)
{
}

void flex_zigbee_receive(scicos_block *block,int flag)
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


