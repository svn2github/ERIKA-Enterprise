/* ###*B*###
 * Copyright (C) Roberto Bucher (SUPSI- Lugano)
 *               Simone Mannori (Scilab / INRIA / DIGITEO)
 *
 * Copyright (C) METALAU Project (INRIA)
 * ###*E*### */
 
 
#include <machine.h>
#include <scicos_block4.h>

#include <ee.h>

/* GPIO bit allocation 

Scicos	Function	dsPIC	Flex Connectors
Pin=1	 GPIO1	RE0	CON8.P2	
Pin=2	 GPIO2	RE1	CON8.P4	
Pin=3	 GPIO3	RE2	CON8.P6	
Pin=4	 GPIO4	RE3	CON8.P8	
Pin=5	 GPIO5	RE4	CON8.P10
Pin=6	 GPIO6	RE5	CON8.P12
Pin=7	 GPIO7	RE6	CON8.P14
Pin=8	 GPIO8	RE7	CON8.P16
*/

static void init(scicos_block *block)
{
	unsigned int pin = block->ipar[0];
	
	if ((pin < 1) || (pin > 8))
	  return;

	TRISE |= 0x01 << (pin-1);
}

static void inout(scicos_block *block)
{
	float * y = block->outptr[0];

	unsigned int pin = block->ipar[0];
	
	if ((pin < 1) || (pin > 8))
		return;

	if ( PORTE & (0x01 << (pin-1)) )
		y[0] = 1.0; //** the output of a input bit is "1.0"  
	else                           //** or 
		y[0] = 0.0; //** "0.0" (float)
}

static void end(scicos_block *block)
{
}

void flex_dmb_gpin(scicos_block *block,int flag)
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
