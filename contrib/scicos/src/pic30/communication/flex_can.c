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

/* initializagtion flag, used inside EE_eCAN1_init */
EE_UINT8 ee_ecan1_initialized = 0;

/* Buffers */
CAN_buffer CAN1_rx_buffer;
CAN_buffer CAN1_tx_buffer;
EE_UINT8 scicosCAN1_rx_buffer[CAN_PKT_LEN];					// buffer for CAN reception
EE_UINT8 scicosCAN1_tx_buffer[CAN_PKT_LEN];					// buffer for CAN transmission


extern EE_UINT32 ecan1_tx_id;     /* contain the id for can messages */
extern EE_UINT8 ecan1_tx_len;
extern EE_UINT8 ecan1_tx_canid;
extern EE_UINT8 ecan1_tx_div;

void (*EE_eCAN1_tx_cbk) (void);
void (*EE_eCAN1_rx_cbk) (void);

TASK(CAN1_TASK)
{
	EE_UINT8 msg[CAN_PKT_LEN];
	print_string("can task start!\n");
	
	if(ee_ecan1_initialized)
	{
		EE_eCAN1_send(msg, CAN_PKT_LEN, ecan1_tx_id); 
		#if 0
		if(!CAN_Buffer_Isempty(&CAN1_tx_buffer))
		{	
			// extracts and send a packet
			CAN_Buffer_Getmsg(&CAN1_tx_buffer, msg, CAN_BUF_SIZE);
			EE_eCAN1_send(msg, CAN_PKT_LEN, ecan1_tx_id); 
		}
		#endif
	}
	print_string("can task end!\n");
}

/* CAN bus 1 Interrupt, ISR2 type */
void EE_eCAN1_cbk(int flag)
{
	if(EE_eCAN1_rx_cbk!=0)
		EE_eCAN1_rx_cbk();
	if(EE_eCAN1_tx_cbk!=0)
		EE_eCAN1_tx_cbk();
}

void EE_eCAN1_send(EE_UINT8 *data, int len, int id)
{
	int i;
	ee_ecan_mID tx_ecan1message; //TX Transmission message
	
	print_string("can send start!\n");
	
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
	
	print_string("can send end!\n");
}

void EE_eCAN1_init(void)
{
	print_string("can config start!\n");
	EE_eCAN1_tx_cbk = 0;
	EE_eCAN1_rx_cbk = 0;
	EE_ecan1_set_ISR_callback(&EE_eCAN1_cbk);
	EE_ecan1_Initialize();//Initialize enhanced CAN bus number 1
	EE_ecan1_WriteRxAcptMask(0x0,0x1FFFFFFF, 0,0x1);
	EE_ecan1_WriteRxAcptFilter(0x0,1,0x1,0x1,0x0); //id=1 to buffer 1
	EE_ecan1_WriteRxAcptFilter(0x1,2,0x1,0x2,0x0); //id=2 to buffer 2
	EE_ecan1_WriteRxAcptFilter(0x2,3,0x1,0x3,0x0); //id=3 to buffer 3
	EE_ecan1_WriteRxAcptFilter(0x3,99,0x1,0x4,0x0);//id=99 to buffer 4
	print_string("can config end!\n");
}



/* Buffer library */

void CAN_Buffer_Init(CAN_buffer *buf, int dim)
{
  	buf->g = 0;
  	buf->p = 0;
  	buf->counter = 0;
  	return;
}

void CAN_Buffer_Close(CAN_buffer *buf)
{
	buf->g = 0;
  	buf->p = 0;
  	buf->counter = 0;
	return;
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










