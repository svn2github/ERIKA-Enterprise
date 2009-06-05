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

static EE_UINT8 txbuffer[8] = { 1, 2, 3, 4, 5, 6, 7, 8 };
static EE_UINT32 cantx_id;     /* contain the id for can messages */
static EE_UINT8 n_byte;

static void init(scicos_block *block)
{
  EE_Can_Dma_Init();
  EE_Ecan1_Clk_Init();
  EE_Ecan1_TxInit();
  cantx_id=block->ipar[0];
  n_byte=block->ipar[1];
}

static void inout(scicos_block *block)
{
  int i;
  double * DATA = (double *) block->inptr[0];

  for(i=0;i<(int)n_byte;i++) txbuffer[i]=(EE_UINT8) DATA[i];
   
  while ( C1TR01CONbits.TXREQ0 ==1){}
   
  EE_ecan_WriteMessage((EE_UINT16)&(CanBuf[0]),cantx_id,n_byte,0,(EE_UINT8 *)&txbuffer);
  C1TR01CONbits.TXREQ0 = 1;  
}

static void end(scicos_block *block)
{
  
}

void flex_can_out(scicos_block *block,int flag)
{
  if (flag==1){          /* set output */
    inout(block);
  }
  else if (flag==5){     /* termination */ 
    end(block);
  }
  else if (flag ==4){    /* initialisation */
    init(block);
  }
}


