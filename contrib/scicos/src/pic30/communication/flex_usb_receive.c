/* ###*B*###
 * Copyright (C) Roberto Bucher (SUPSI- Lugano)
 *               Simone Mannori (Scilab / INRIA / DIGITEO)
 *
 * Copyright (C) METALAU Project (INRIA)
 * ###*E*### */
 
 
//** 9 Feb 2008 : Revision notes by Simone Mannori 
//**

#include <machine.h>
#include <scicos_block4.h>

#include <ee.h>
#include "scicos_USB.h"

static void init(scicos_block *block)
{
	EE_usb_init();
}

static void inout(scicos_block *block)
{
	GetResource(scicosUSB_rx_buffer_mutex);
	*((float*) block->outptr[0]) = scicosUSB_rx_buffer[block->ipar[0]];
	ReleaseResource(scicosUSB_rx_buffer_mutex);
}

static void end(scicos_block *block)
{
}

void flex_usb_receive(scicos_block *block,int flag)
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
