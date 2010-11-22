/* ###*B*###
 * ERIKA Enterprise - a tiny RTOS for small microcontrollers
 *
 * Copyright (C) 2006-2010  Evidence Srl
 *
 * This file is part of ERIKA Enterprise.
 *
 * ERIKA Enterprise is free software; you can redistribute it
 * and/or modify it under the terms of the GNU General Public License
 * version 2 as published by the Free Software Foundation, 
 * (with a special exception described below).
 *
 * Linking this code statically or dynamically with other modules is
 * making a combined work based on this code.  Thus, the terms and
 * conditions of the GNU General Public License cover the whole
 * combination.
 *
 * As a special exception, the copyright holders of this library give you
 * permission to link this code with independent modules to produce an
 * executable, regardless of the license terms of these independent
 * modules, and to copy and distribute the resulting executable under
 * terms of your choice, provided that you also meet, for each linked
 * independent module, the terms and conditions of the license of that
 * module.  An independent module is a module which is not derived from
 * or based on this library.  If you modify this code, you may extend
 * this exception to your version of the code, but you are not
 * obligated to do so.  If you do not wish to do so, delete this
 * exception statement from your version.
 *
 * ERIKA Enterprise is distributed in the hope that it will be
 * useful, but WITHOUT ANY WARRANTY; without even the implied warranty
 * of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License version 2 for more details.
 *
 * You should have received a copy of the GNU General Public License
 * version 2 along with ERIKA Enterprise; if not, write to the
 * Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
 * Boston, MA 02110-1301 USA.
 * ###*E*### */

/** 
	@file flex_can.c
	@brief www.scicos.org, www.scicoslab.org
	@author Dario Di Stefano, Evidence Srl
	@date 2006-2010
*/

#include <machine.h>
#include <scicos_block4.h>
#include "ee.h"
#include "mcu/microchip_dspic/inc/ee_ecan.h"
#include "flex_can.h"

/* initializagtion flag, used inside EE_eCAN1_init */
EE_UINT8 ee_ecan1_initialized = 0;
EE_UINT8 ecan1_tx_initialized = 0;
EE_UINT8 ecan1_rx_initialized = 0;

/* Rx and Tx buffers */
CAN_buffer CAN1_rx_buffer;
CAN_buffer CAN1_tx_buffer;
EE_UINT8 scicosCAN1_rx_buffer[CAN_PKT_LEN];					// buffer for CAN reception
EE_UINT8 scicosCAN1_tx_buffer[CAN_PKT_LEN];					// buffer for CAN transmission

/* Global variables (Transmission) */
EE_UINT8 ecan_tx_canid;
/* eCAN1 */
EE_UINT32 ecan1_tx_id;     /* contain the id for can messages */
EE_UINT8 ecan1_tx_len;
EE_UINT8 ecan1_tx_div;
void (*EE_eCAN1_tx_cbk) (void);

/* Global variables (Reception) */
EE_UINT8 ecan_rx_canid;
/* eCAN1 */
EE_UINT32 ecan1_rx_id;     /* contain the id for can messages */
EE_UINT8 ecan1_rx_len;
EE_UINT8 ecan1_rx_div;
void (*EE_eCAN1_rx_cbk) (void);
ee_ecan_mID rx_ecan1message1;//RX message for id=1
ee_ecan_mID rx_ecan1message2;//RX message for id=2
ee_ecan_mID rx_ecan1message3;//RX message for id=3
ee_ecan_mID rx_ecan1message4;//RX message for id=99

/* Task */
TASK(CAN1_TASK)
{
	can_debug_print_string("can task start!\n");
	
	if(ee_ecan1_initialized==0)
	{
		//TRISBbits.TRISB14 = 0;	// output (led)
		EE_eCAN1_init();
		ee_ecan1_initialized = 1;
	}
	else
	{
		EE_UINT8 msg[CAN_PKT_LEN];
		if(ecan1_tx_initialized)
		{
			if(!CAN_Buffer_Isempty(&CAN1_tx_buffer))
			{	
				// extracts and send a packet
				CAN_Buffer_Getmsg(&CAN1_tx_buffer, msg, CAN_BUF_SIZE);
				EE_eCAN1_send(msg, CAN_PKT_LEN, ecan1_tx_id); 
			}
		}
	}
	
	can_debug_print_string("can task end!\n");
}

/* CAN bus 1 Interrupt, ISR2 type */
void EE_eCAN1_cbk(int flag)
{
	//if(EE_eCAN1_rx_cbk!=0)
	EE_eCAN1_rx_cbk();
	//if(EE_eCAN1_tx_cbk!=0)
	EE_eCAN1_tx_cbk();
}

void EE_eCAN1_send(EE_UINT8 *data, int len, int id)
{
	int i;
	ee_ecan_mID tx_ecan1message; //TX Transmission message
	
	can_debug_print_string("can send start!\n");
	//C1CTRL1bits.ABAT = 1;
	//while(C1TR01CONbits.TXREQ0){};
	tx_ecan1message.buffer			=	0;	//Buffer number
	tx_ecan1message.frame_type		=	1;	//0->Std Id, 1->Ext Id
	tx_ecan1message.id 				= 	id;	//Identifier;
	tx_ecan1message.message_type	=	0;	//0->Normal, 1->Remote Transmit
	tx_ecan1message.data_length		=	len;//Length of data (0 to 8 EE_UINT8s)
	for(i=0; i<CAN_PKT_LEN; i++) 
		tx_ecan1message.data[i] = data[i];
	EE_ecan1_SendMessage(&tx_ecan1message);
	while(C1TR01CONbits.TXREQ0){};	
	can_debug_print_string("can send end!\n");
}

void EE_eCAN1_init(void)
{
	int i;
	
	can_debug_print_string("can config start!\n");
	/* Callbacks initialization */
	EE_eCAN1_tx_cbk = EE_eCAN1_tx_service;
	EE_eCAN1_rx_cbk = EE_eCAN1_rx_service;
	EE_ecan1_set_ISR_callback(&EE_eCAN1_cbk);
	/* Buffers initialization */
	CAN_Buffer_Init(&CAN1_tx_buffer);
	CAN_Buffer_Init(&CAN1_rx_buffer);
	for(i=0;i<CAN_PKT_LEN;i++)
	{
		scicosCAN1_tx_buffer[i] = 0;
		scicosCAN1_rx_buffer[i] = 0;
	}	
	/* Can setup and initialization */
	EE_ecan1_Initialize();//Initialize enhanced CAN bus number 1
	EE_ecan1_WriteRxAcptMask(0x0,0x1FFFFFFF, 0,0x1);
	EE_ecan1_WriteRxAcptFilter(0x0,1,0x1,0x1,0x0); //id=1 to buffer 1
	EE_ecan1_WriteRxAcptFilter(0x1,2,0x1,0x2,0x0); //id=2 to buffer 2
	EE_ecan1_WriteRxAcptFilter(0x2,3,0x1,0x3,0x0); //id=3 to buffer 3
	EE_ecan1_WriteRxAcptFilter(0x3,99,0x1,0x4,0x0);//id=99 to buffer 4
	can_debug_print_string("can config end!\n");
}


void EE_eCAN1_tx_service(void)
{
	/* Transmission interrupt (nothing to be done but clear flag) */
	if(C1INTFbits.TBIF)
    	C1INTFbits.TBIF = 0;
}

/* CAN bus 1 Interrupt, ISR2 type */
void EE_eCAN1_rx_service(void)
{
	ee_ecan_mID *rx_ecan1message_p = 0;
	EE_UINT8 rx_ecan1message_id = 0;
	
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
			rx_ecan1message_p = &rx_ecan1message1;
			rx_ecan1message_id = 1;
	    }

		//Filter 2(id=ID_PLANT+1): Controller to Actuator message
		if(C1RXFUL1bits.RXFUL2==1)
	    {
			/*Tells rxECAN1 the buffer to pass from DMA to RAM */
	    	rx_ecan1message2.buffer=2;

	    	C1RXFUL1bits.RXFUL2=0;
	    	EE_ecan1_Rx(&rx_ecan1message2);
			C1INTFbits.RBIF = 0;
			rx_ecan1message_p = &rx_ecan1message2;
			rx_ecan1message_id = 2;
	    }

		//Filter 3(id=ID_PLANT+2): Controller updated reference (supervision)
		if(C1RXFUL1bits.RXFUL3==1)
	    {
			/*Tells rxECAN1 the buffer to pass from DMA to RAM */
	    	rx_ecan1message3.buffer=3;

	    	C1RXFUL1bits.RXFUL3=0;
	    	EE_ecan1_Rx(&rx_ecan1message3);
			C1INTFbits.RBIF = 0;
			rx_ecan1message_p = &rx_ecan1message3;
			rx_ecan1message_id = 3;
	    }

		//Filter 4(id=99): Reserved for future improvements
		if(C1RXFUL1bits.RXFUL4==1)
	    {
			/* Tells rxECAN1 the buffer to pass from DMA to RAM */
	    	rx_ecan1message4.buffer=4;

	    	C1RXFUL1bits.RXFUL4=0;
	    	EE_ecan1_Rx(&rx_ecan1message4);
			C1INTFbits.RBIF = 0;
			rx_ecan1message_p = &rx_ecan1message4;
			rx_ecan1message_id = 4;
	    }
		
		/* Queueing */
		if(ecan1_rx_initialized)
		{
			EE_UINT8 msg[CAN_PKT_LEN];
			int i;
			if(rx_ecan1message_id == ecan1_rx_id) {
				for(i=0; i<CAN_PKT_LEN; i++)
					msg[i] = rx_ecan1message_p->data[i];
				//LATBbits.LATB14 ^= 1;	
				CAN_Buffer_Putmsg(&CAN1_rx_buffer, msg, CAN_BUF_SIZE);
			}
		}
	}
}


/* Buffer library */
void CAN_Buffer_Init(CAN_buffer *buf)
{
  	buf->g = 0;
  	buf->p = 0;
  	buf->counter = 0;
}

void CAN_Buffer_Close(CAN_buffer *buf)
{
	buf->g = 0;
  	buf->p = 0;
  	buf->counter = 0;
}

int CAN_Buffer_Putmsg(CAN_buffer *buf, EE_UINT8* msg, int dim)
{
	int i=0;
	EE_hal_disableIRQ();
	if((buf->g == buf->p) && (buf->counter==dim)) //if( ((buf->p+1) % dim) == buf->g )	
	{
		EE_hal_enableIRQ();	
		return 0; 	
	}
	for(i=0;i<CAN_PKT_LEN;i++)	
    	buf->data[buf->p][i] = msg[i];
    buf->p++;
    //if (buf->p == BUFFSIZE) buf->p = 0;
    buf->p = (buf->p % dim);
    buf->counter++;
    EE_hal_enableIRQ();	
    return 1;
}

int CAN_Buffer_Getmsg(CAN_buffer *buf, EE_UINT8* msg, int dim)
{
	int i=0;
	EE_hal_disableIRQ();
	if((buf->g == buf->p) && (buf->counter==0)) //if(buf->g == buf->p)
	{
		EE_hal_enableIRQ();	
		return 0; 	
	}
  	for(i=0;i<CAN_PKT_LEN;i++)	
    	msg[i] = buf->data[buf->g][i];
  	buf->g++;
  	//if (buf->g == BUFFSIZE) buf->g = 0;
  	buf->g = (buf->g % dim);
  	buf->counter--;
  	EE_hal_enableIRQ();	
  	return 1;
}

int CAN_Buffer_Isempty(CAN_buffer *buf)
{
	int retvalue;
	EE_hal_disableIRQ();
	if((buf->g == buf->p) && (buf->counter==0))
		retvalue = 1;
	else
		retvalue = 0; 	
	EE_hal_enableIRQ();	
	return retvalue;
}

int CAN_Buffer_Isfull(CAN_buffer *buf, int dim)
{
	int retvalue;
	EE_hal_disableIRQ();
	//if( ((buf->p+1) % dim) == buf->g )	
	//	retvalue = 1;
	if((buf->g == buf->p) && (buf->counter==dim))
		retvalue = 1;
	else
		retvalue = 0;
	EE_hal_enableIRQ();		
	return retvalue;
}

int CAN_Buffer_count(CAN_buffer *buf)
{
	int retvalue;
	EE_hal_disableIRQ();
	retvalue = buf->counter;
	EE_hal_enableIRQ();	
	return retvalue;
}








