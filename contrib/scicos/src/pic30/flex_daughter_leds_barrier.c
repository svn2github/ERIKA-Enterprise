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

#include <ee.h>

/* FLEX DMB LEDS allocation 

Scicos	Function	dsPIC
Pin=1	LED1	RF0
Pin=2	LED2	RF1
Pin=3	LED3	RF2
Pin=4	LED4	RF3
Pin=5	LED5	RD8
Pin=6	LED6	RD9
Pin=7	LED7	RD10
Pin=8	LED8	RD11
*/

void init(scicos_block *block)
{
	float led_threshold = block->rpar[0];
	
	if( led_threshold < 0.01 || led_threshold > 0.99 )
		led_threshold = 0.5;
	
	EE_daughter_leds_init();
}

void inout(scicos_block *block)
{

	int i;
	unsigned char data = 0;

	/* unsigned char data = 0;

	float led_threshold = block->rpar[0];

	//if( led_threshold < 0.01 || led_threshold > 0.99 )
	//	led_threshold = 0.5;

	for(i=7;i>=0;i--)
	{
		if(*(float *)(block->inptr[i]) >= led_threshold) data++;
		data *= 2;
}
*/

	for(i=7; i>=0; i--) {

	if(*(float *)block->inptr[i] >= 0.5) data++;
	data *= 2;
	}

	EE_leds(data);

}

static void end(scicos_block *block)
{
	EE_leds(0xFF); //** set the bit to zero at the ending 
}

void flex_daughter_leds_barrier(scicos_block *block,int flag)
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
