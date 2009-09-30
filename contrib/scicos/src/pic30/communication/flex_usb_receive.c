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
/**************************/
#include "string.h"
/**************************/
#include <ee.h>
#include "scicos_USB.h"

static void init(scicos_block *block)
{
	EE_usb_init();
}

static void inout(scicos_block *block)
{
	EE_INT16 data_id = (EE_INT16) block->ipar[0];

	if (data_id < 0 || data_id >= SCICOS_USB_CHANNELS)
		return;
	GetResource(scicosUSB_rx_buffer_mutex);
	memcpy(block->outptr[0], scicosUSB_rx_buffer + data_id,  sizeof(float));
	ReleaseResource(scicosUSB_rx_buffer_mutex);
}

static void end(scicos_block *block)
{
}

void flex_usb_receive(scicos_block *block,int flag)
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
