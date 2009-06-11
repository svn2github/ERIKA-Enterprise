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

static void init(scicos_block *block)
{
	int pin = block->ipar[0];
	
	if ( (pin < 1) || (pin > 8) )
		return; //** return if outside the allowed range

	EE_demoboard_leds_init();
}

static void inout(scicos_block *block)
{
  float *u = block->inptr[0];
	int pin = block->ipar[0];
	
	if ( (pin < 1) || (pin > 8) )
		return;

	if (u[0] > 0.5) {     //** threshold is fixed to 0.5 STATIC 
		switch (pin) { //** set the bit to one 
			case 1:
				EE_led_0_on();
				break;
			case 2:
				EE_led_1_on();
				break;
			case 3:
				EE_led_2_on();
				break;
			case 4:
				EE_led_3_on();
				break;
			case 5:
				EE_led_4_on();
				break;
			case 6:
				EE_led_5_on();
				break;
			case 7:
				EE_led_6_on();
				break;
			case 8:
				EE_led_7_on();
				break;
		}
	} else {
		switch (pin) { //** set the bit to zero 
			case 1:
				EE_led_0_off();
				break;
			case 2:
				EE_led_1_off();
				break;
			case 3:
				EE_led_2_off();
				break;
			case 4:
				EE_led_3_off();
				break;
			case 5:
				EE_led_4_off();
				break;
			case 6:
				EE_led_5_off();
				break;
			case 7:
				EE_led_6_off();
				break;
			case 8:
				EE_led_7_off();
				break;
		}
	}
}

static void end(scicos_block *block)
{
	int pin = block->ipar[0];
	
	if ( (pin < 1) || (pin > 8) )
		return; //** return if outside the alowed range

	EE_leds_off(); //** set the bit to zero at the ending 
}

void flex_daughter_leds(scicos_block *block,int flag)
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
