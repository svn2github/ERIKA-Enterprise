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

#include <machine.h>
#include <scicos_block4.h>
#include "ee.h"
#include "mcu/microchip_dspic/inc/ee_ecan.h"
#include "flex_can.h"
#include <string.h>

EE_UINT32 ecan1_tx_id;     /* contain the id for can messages */
EE_UINT8 ecan1_tx_len;
EE_UINT8 ecan1_tx_canid;
EE_UINT8 ecan1_tx_div;

extern void (*EE_eCAN1_tx_cbk) (void);

void EE_eCAN1_tx_service(void)
{
	/* Transmission interrupt (nothing to be done but clear flag) */
	if(C1INTFbits.TBIF)
    {
    	C1INTFbits.TBIF = 0;
    }
}

static void init(scicos_block *block)
{
	int i;
	
	print_string("can init start!\n");
	ecan1_tx_canid	=	1;	//block->ipar[2];
	EE_eCAN1_tx_cbk = EE_eCAN1_tx_service;
	if( (ecan1_tx_canid==1) && (ee_ecan1_initialized==0) )
	{
		EE_eCAN1_init();
		ecan1_tx_id 	= 	block->ipar[0];							/* packet id */
		ecan1_tx_len 	= 	16; //block->ipar[1];	  						/* number of float number */
		ecan1_tx_div 	= 	1;//8; //ceil(((double)(block->ipar[1]))/2.0); 	/* number of packets */
		for(i=0;i<CAN_PKT_LEN;i++)
			scicosCAN1_tx_buffer[i] = 0;
		for(i=0;i<CAN_PKT_LEN;i++)
			scicosCAN1_rx_buffer[i] = 0;
		ee_ecan1_initialized = 1;	
	}
	//else
	//{
	//}
	print_string("can init end!\n");
}

static void inout(scicos_block *block)
{
	int i;
	print_string("can inout start!\n");
	for(i = 0; i < ecan1_tx_len; i++)
		memcpy(scicosCAN1_tx_buffer + i*SIZE_OF_ELEMENT, &u(i,0), SIZE_OF_ELEMENT);
	for(i = 0; i < ecan1_tx_div; i++)
		CAN_Buffer_Putmsg(&CAN1_tx_buffer, scicosCAN1_tx_buffer + i*CAN_PKT_LEN, CAN_BUF_SIZE);
	print_string("can inout end!\n");
}

static void end(scicos_block *block)
{
}

void flex_can_out(scicos_block *block,int flag)
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


