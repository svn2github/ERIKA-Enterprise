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

static EE_UINT8 ecan1_rxbuffer[EE_CAN_BUF_SIZE];
static ee_ecan_mID rx_ecan1message1;//RX message for id=1
static ee_ecan_mID rx_ecan1message2;//RX message for id=2
static ee_ecan_mID rx_ecan1message3;//RX message for id=3
static ee_ecan_mID rx_ecan1message4;//RX message for id=99
static EE_UINT32 ecan1_rx_id;     /* contain the id for can messages */
static EE_UINT8 ecan1_rx_len;
static int ecan1_rx_cnt = 0;

extern void (*EE_eCAN1_rx_cbk) (void);

static void init(scicos_block *block)
{   
	EE_eCAN1_rx_cbk = EE_eCAN1_rx_service;
	EE_eCAN1_init();
	ecan1_rx_id 		= 	block->ipar[0];
	ecan1_rx_len 		= 	block->ipar[1] * SIZE_OF_ELEMENT;
}

static void inout(scicos_block *block)
{
	int i;
	if(ecan1_rx_cnt >= ecan1_rx_len)
	{
		for(i=0;i<SCICOS_CAN_CHANNELS;i++)
			memcpy(&y(i,0), ecan1_rxbuffer + i*SIZE_OF_ELEMENT, SIZE_OF_ELEMENT);
		ecan1_rx_cnt = 0;
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

/* CAN bus 1 Interrupt, ISR2 type */
void EE_eCAN1_rx_service(void)
{
	ee_ecan_mID *rx_ecan1message_p;
	int i;

	/*Reception interrupt, different code for different filtered id's */
    if(C1INTFbits.RBIF)
    {
    	//Filter 1(id=ID_PLANT): Sensor to controller message
    	if(C1RXFUL1bits.RXFUL1==1)
	    {
    		/* Tells rxECAN1 the buffer to pass from DMA to RAM */
	    	rx_ecan1message1.buffer=1;

	    	C1RXFUL1bits.RXFUL1=0;
	    	EE_ecan1_Rx(&rx_ecan1message1);
			C1INTFbits.RBIF = 0;
	    }

		//Filter 2(id=ID_PLANT+1): Controller to Actuator message
		if(C1RXFUL1bits.RXFUL2==1)
	    {
			/*Tells rxECAN1 the buffer to pass from DMA to RAM */
	    	rx_ecan1message2.buffer=2;

	    	C1RXFUL1bits.RXFUL2=0;
	    	EE_ecan1_Rx(&rx_ecan1message2);
			C1INTFbits.RBIF = 0;
	    }

		//Filter 3(id=ID_PLANT+2): Controller updated reference (supervision)
		if(C1RXFUL1bits.RXFUL3==1)
	    {
			/*Tells rxECAN1 the buffer to pass from DMA to RAM */
	    	rx_ecan1message3.buffer=3;

	    	C1RXFUL1bits.RXFUL3=0;
	    	EE_ecan1_Rx(&rx_ecan1message3);
			C1INTFbits.RBIF = 0;
	    }

		//Filter 4(id=99): Reserved for future improvements
		if(C1RXFUL1bits.RXFUL4==1)
	    {
			/* Tells rxECAN1 the buffer to pass from DMA to RAM */
	    	rx_ecan1message4.buffer=4;

	    	C1RXFUL1bits.RXFUL4=0;
	    	EE_ecan1_Rx(&rx_ecan1message4);
			C1INTFbits.RBIF = 0;
	    }
		
		/* Queueing */
		if(ecan1_rx_id==1)
			rx_ecan1message_p = &rx_ecan1message1;
		else if (ecan1_rx_id==2)
			rx_ecan1message_p = &rx_ecan1message2;
		else if(ecan1_rx_id==3)
			rx_ecan1message_p = &rx_ecan1message3;
		else if(ecan1_rx_id==99)
			rx_ecan1message_p = &rx_ecan1message4;
		else
			rx_ecan1message_p = 0;
		if(rx_ecan1message_p!=0)
		{
			for(i=0; i<8; i++) {
				ecan1_rxbuffer[ecan1_rx_cnt] = rx_ecan1message_p->data[i];
				ecan1_rx_cnt++;
			}
		}
	}
}


