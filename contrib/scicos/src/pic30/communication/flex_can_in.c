/*
COPYRIGHT (C) 2007  Roberto Bucher (roberto.bucher@supsi.ch)

This library is free software; you can redistribute it and/or
modify it under the terms of the GNU Lesser General Public
License as published by the Free Software Foundation; either
version 2 of the License, or (at your option) any later version.

This library is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public
License along with this library; if not, write to the Free Software
Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA.
*/

/*
 * PRELIMINARY VERSION
 * from patch sent by Tizar Rizano (UNITN) and Roberto Bucher (SUPSI)
 */


#include <machine.h>
#include <scicos_block4.h>
#include "ee.h"
#include "mcu/microchip_dspic/inc/ee_ecan.h"
#include "flex_can.h"
#include <string.h>

static void init(scicos_block *block)
{   
	can_debug_print_string("can_rx init start!\n");
	/* to do: add eCAN2 support */
	ecan_rx_canid	=	1;	//block->ipar[2];
	if( ecan_rx_canid==1 ) 
	{
		ecan1_rx_id 	= 	block->ipar[0];							/* packet id */
		ecan1_rx_len 	= 	block->ipar[1];	  						/* number of floats */
		can_debug_print_val("can_rx block->ipar[0]: %d\n", block->ipar[0]);
		can_debug_print_val("can_rx block->ipar[1]: %d\n", block->ipar[1]);
		if(ecan1_rx_len & 0x01)
			ecan1_rx_div = ecan1_rx_len/2 + 1;	/* number of packets, odd case */
		else
			ecan1_rx_div = ecan1_rx_len/2;		/* number of packets, even case */
		ecan1_rx_initialized = 1;
	}
	can_debug_print_string("can_rx init end!\n");
	
}

static void inout(scicos_block *block)
{
	int i;
	int cnt = CAN_Buffer_count(&CAN1_rx_buffer);
	if(cnt >= ecan1_rx_div)
	{
		for(i=0; i<ecan1_rx_div; i++)
			CAN_Buffer_Getmsg(&CAN1_rx_buffer, scicosCAN1_rx_buffer, CAN_BUF_SIZE);
		for(i=0; i<ecan1_rx_len; i++)
			memcpy(&y(i,0), scicosCAN1_rx_buffer + i*SIZE_OF_ELEMENT, SIZE_OF_ELEMENT);
	}
}

static void end(scicos_block *block)
{
}

void flex_can_in(scicos_block *block,int flag)
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




