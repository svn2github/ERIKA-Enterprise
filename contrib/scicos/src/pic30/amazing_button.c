
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

/* Buttons bit allocation 

Scicos	Function	dsPIC
Pin=1	Button1	RD4
Pin=2	Button2	RD5
Pin=3	Button3	RD6
Pin=4	Button4	RD15
*/

static void init(scicos_block *block)
{
	unsigned int pin = block->ipar[0];
#if defined(__USE_DEMOBOARD__)	
	if ((pin < 1) || (pin > 4))
#elif defined(__USE_MOTIONBOARD__)
	if ((pin < 1) || (pin > 2))
#endif
		return; //** return if outside the allowed range

	EE_button_S1_init(NULL);
	EE_button_S2_init(NULL);
}

static void inout(scicos_block *block)
{
	float * y = block->outptr[0];

	unsigned int pin = block->ipar[0];
	
#if defined(__USE_DEMOBOARD__)	
	if ((pin < 1) || (pin > 4))
#elif defined(__USE_MOTIONBOARD__)
	if ((pin < 1) || (pin > 2))
#endif
		return; //** return if outside the allowed range
	
	switch(pin) {
		case 1:
			if (EE_button_get_S1())
				y[0] = 1.0; //** the output of a input bit is "1.0"  
			else
				y[0] = 0.0; //** "0.0" (float)
			break;
		case 2:
			if (EE_button_get_S2())
				y[0] = 1.0; //** the output of a input bit is "1.0"  
			else
				y[0] = 0.0; //** "0.0" (float)
			break;
#if defined(__USE_DEMOBOARD__)	
		case 3:
			if (EE_button_get_S3())
				y[0] = 1.0; //** the output of a input bit is "1.0"  
			else
				y[0] = 0.0; //** "0.0" (float)
			break;
		case 4:
			if (EE_button_get_S4())
				y[0] = 1.0; //** the output of a input bit is "1.0"  
			else
				y[0] = 0.0; //** "0.0" (float)
			break;
#endif // USE_DEMOBOARD__	
	}
}

static void end(scicos_block *block)
{
}

void amazing_button(scicos_block *block, int flag)
{
 switch (flag) {
    case OutputUpdate:  /* set output */
      inout(block);
      break;

    case StateUpdate: /* get input */
      break;

    case Initialization:  /* initialization */
      init(block);
      break;

    case Ending:  /* ending */
      end(block);
      break;
  }
}
