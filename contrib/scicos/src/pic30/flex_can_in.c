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

extern _t_ecan CanBuf[8];


static EE_UINT8 rxData[8] = { 0x91, 0x92, 0x93, 0x94, 0x95, 0x96, 0x97, 0x98 };
static EE_UINT32 canrx_id;     /* contain the id for can messages */
static EE_UINT8 can_dlc=0;
static EE_UINT8 filterhit;
static EE_UINT8 bufnr;
static EE_UINT8 can_data_en=0;
static EE_UINT8 n_byte;




static EE_INT8 RXCan1(EE_UINT8 data)
{
  EE_UINT16 rec_buf;
  filterhit = C1VECbits.FILHIT;
  bufnr = C1VECbits.ICODE;
  if (0 == (bufnr & 0x40))   //0x40 -> 0100 0000
    {						 
      if (can_data_en==0){
	EE_ecan_ReadMessage((EE_UINT16)&CanBuf[(C1VEC & 0x1F)],&canrx_id,&can_dlc,(EE_UINT8 *)&rxData[0]);
	can_data_en=1;
    	  	
      } 
	
	
      //azzera il bit del buffer che ha generato l'interrupt
      rec_buf = 1 << bufnr;
      rec_buf ^= 0xFFFF;
      C1RXFUL1 &= rec_buf;
    
      if (1 == C1INTFbits.RBOVIF) C1INTFbits.RBOVIF = 0;
    }

  return 0;
}


static void init(scicos_block *block)
{   
  EE_Can_Dma_Init();
  EE_Ecan1_Clk_Init();
  EE_Ecan1_RxInit(RXCan1);
  n_byte=block->ipar[0];
}

static void inout(scicos_block *block)
{
  int i;
  double *enable = (double*) block->outptr[0];
  double *DATA = (double*) block->outptr[1];

  if (can_data_en==1){
		
    can_data_en=2;
    if (can_dlc==n_byte){
      for(i=0;i<can_dlc;i++) DATA[i]=(double) (rxData[i]);
      enable[0]=1;}
    can_data_en=0;
		
  }
  else enable[0]=0;
	
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


