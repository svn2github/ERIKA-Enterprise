/* ###*B*###
 * ERIKA Enterprise - a tiny RTOS for small microcontrollers
 *
 * Copyright (C) 2002-2008  Evidence Srl
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

/*
 * PRELIMINARY VERSION
 * from patch sent by Tizar Rizano (UNITN) and Roberto Bucher (SUPSI)
 */

#include "ee_internal.h"
#include "cpu/pic30/inc/ee_irqstub.h"
#include "mcu/microchip_dspic/inc/ee_ecan.h"


/******************************************************************/

//  type        1 = extended identifier
//              0 = standard identifier
//  identifier  sid[10:0] , if type = 0 only lower 11bits are relevant
//              sid[10:0],eid[17:0] if type = 1 then 29bits are relevant, sid in upper bits
//              
//  len         len of data frame
//
//  dptr        contain address where the data comming from 

void EE_ecan_WriteMessage(EE_UINT16 bufptr,
			  EE_UINT32 identifier,
			  EE_UINT8  len,
			  EE_UINT8  type,
			  EE_UINT8  *dptr)
{	 
  EE_UINT8 cnt;
  
  /* DMAbuffer for TXB0 located at DMAbase +  DMA0STA  */  

  _t_ecan * txMsgBox = (_t_ecan *)bufptr;      

  if (type) /* extended identifier requested */
    {
      txMsgBox -> sid = ((identifier >> 16) & 0x1FFC) | type;	
      txMsgBox -> eidh = (identifier >> 6L);
      txMsgBox -> eidl_dlc = ((identifier << 10L) & 0xFC00) | len ;
    }
  else      /* standard identifier */
    {
      txMsgBox -> sid = ((identifier << 2) & 0x1FFC);	
      txMsgBox -> eidl_dlc = len ;
    }
  
  for (cnt=0;cnt <= len;cnt++)
    {
      txMsgBox -> data[cnt] = *dptr++;
    }
}

/******************************************************************/

void EE_ecan_ReadMessage(EE_UINT16 bufptr,
			 EE_UINT32 *identifier,
			 EE_UINT8  *len,
			 EE_UINT8  *dptr)
{
  EE_UINT8 cnt;
  
  /* DMAbuffer for RXB0 located at DMAbase +  DMA3STA + (C1BUFPNT1bits.F0BP * buffersize) */  

  _t_ecan *rx2MsgBox = (_t_ecan *)bufptr;
  
  *len = rx2MsgBox -> eidl_dlc & 15L;
    
  if (rx2MsgBox -> sid & 1)     /* extended identifier */
    {
      *identifier = ((EE_UINT32)(rx2MsgBox -> sid) << 16) & 0x1FFC0000;
      *identifier |= ((EE_UINT32)(rx2MsgBox -> eidh) << 6) & 0x1FFFFFC0;
      *identifier |= (rx2MsgBox -> eidl_dlc >>  10L);
    }
  else
    {
      *identifier = ((EE_UINT32)(rx2MsgBox -> sid) >> 2) & 0x7FF;
    }

  for (cnt = 0; cnt <= *len ; cnt++) 
    {
      *dptr++ = rx2MsgBox -> data[cnt];
    }
}

/******************************************************************/

void EE_ecan_SetFilter(EE_UINT8  module,
		       EE_UINT8  nr,
		       EE_UINT8  type,
		       EE_UINT32 id)
{
  EE_UINT16 * ptr;
  //u_lw tid;
  //tid.lng = id;
  
  ptr = (EE_UINT16 *)&C1RXF0SID + (nr << 1) + (module << 8) ;   /* filter F0 plus offset of 4 byte per filter or 2 word of 16 bit */
  
  if (0 == type )                 /* standatd identifier */
    {
      *ptr = (((u_lw)id).w.lw << 5) & 0xFFE0;     
    }
  else
    {    
      *ptr++ = ((id << 5) & 0xFFE0) | 8U | ((u_lw)id).w.hw >> 11U;
      *ptr = (id >> 11U) & 0xFFFF;
      //    *ptr++ = ((((u_lw)id).w.hw & 0x1FFC) << 3) | (((u_lw)id).w.hw & 0x0003) | 8;
      //    *ptr = ((u_lw)id).w.lw;
    }
}

/******************************************************************/


/*
  static uint16_t A430;
  static uint16_t A432;
*/
static   u_lw tid;
    
void EE_ecan_SetMask(EE_UINT8  module,
		     EE_UINT8  nr,
		     EE_UINT8  type,
		     EE_UINT32 id)
{
  EE_UINT16* ptr;

  ptr = ((EE_UINT16* )&C1RXM0SID)+ (nr << 1) +(module << 8);   /* filter M0 plus offset of 4 per filter */
   
  if (0 == type )                 /* standatd identifier */
    {
      //*ptr = (((u_lw)id).w.lw << 5) & 0xFFE0;         
      tid.w.lw = (((u_lw)id).w.lw << 5) & 0xFFE0;         
      *ptr = tid.w.lw;
    }
  else   
    {
      //*ptr++ = ((id << 5) & 0xFFE0) | 8U | ((u_lw)id).w.hw >> 11U;
      tid.w.lw = ((id << 5) & 0xFFE0) | 8U | ((u_lw)id).w.hw >> 11U;
      //*ptr = (id >> 11U) & 0xFFFF;
      tid.w.hw = (id >> 11U) & 0xFFFF;
      *ptr++ = tid.w.lw;
      *ptr = tid.w.hw;
    }
}

/******************************************************************/

EE_UINT16 EE_ecan_GetFilterHit(EE_UINT16 bufptr)
{
  EE_UINT16 temp;
  
  _t_ecan *rx2MsgBox = (_t_ecan *)bufptr;
  
  temp = (rx2MsgBox -> config << 8 ) & 0x1F;
  
  return temp;
}  

/******************************************************************/

#ifdef __USE_CAN1__

EE_INT8 (*RxCan1IsrFunction)(EE_UINT8 data)=NULL;
_t_ecan CanBuf[8] __attribute__ ((address(0x7800)));
EE_UINT8 can1_dma_flag=0;
EE_UINT8 can1_clk_flag=0;

ISR2(_C1Interrupt)
{
  _C1IF = 0;
	
}

ISR2(_C1TxReqInterrupt)
{
  _C1TXIF = 0;
	 
}

ISR2(_C1RxRdyInterrupt)
{
  _C1RXIF = 0;
	 
}

ISR2(_DMA1Interrupt)
{		
  if (RxCan1IsrFunction != NULL) {
    (*RxCan1IsrFunction)(0x00);
  }
	
  _DMA1IF = 0;
	 
  
}

#endif // __USE_CAN1__
