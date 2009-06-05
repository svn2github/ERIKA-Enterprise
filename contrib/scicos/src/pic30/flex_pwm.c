/* ###*B*###
 * Copyright (C) Roberto Bucher (SUPSI- Lugano)
 *               Simone Mannori (Scilab / INRIA / DIGITEO)
 *
 * Copyright (C) METALAU Project (INRIA)
 * ###*E*### */
 
 
#include <machine.h>
#include <scicos_block4.h>

#include <ee.h>

static void init(scicos_block *block)
{
	int pin = block->ipar[0];
	
	if ((pin < 1) || (pin > 4))
		return;
		
	switch(pin) {
		case 1:	// PWMout1
			
			/* Set OC1 as output */
			TRISDbits.TRISD0 = 0;
		
			/* Set the initial duty cycle */
			OC1R = 0;

			/* Set the duty cycle */
			OC1RS = 0;

			/* Set OC1 module: PWM, no fault check, Timer2 */
			OC1CON = 0x0006;

			break;

		case 2:	// PWMout2
			
			/* Set OC2 as output */
			TRISDbits.TRISD1 = 0;
		
			/* Set the initial duty cycle */
			OC2R = 0;

			/* Set the duty cycle */
			OC2RS = 0;

			/* Set OC2 module: PWM, no fault check, Timer2 */
			OC2CON = 0x0006;

			break;

		case 3:	// PWMout3
			
			/* Set OC3 as output */
			TRISDbits.TRISD2 = 0;
		
			/* Set the initial duty cycle */
			OC3R = 0;

			/* Set the duty cycle */
			OC3RS = 0;

			/* Set OC3 module: PWM, no fault check, Timer2 */
			OC3CON = 0x0006;

			break;

		case 4:	// PWMout4
			
			/* Set OC4 as output */
			TRISDbits.TRISD3 = 0;
		
			/* Set the initial duty cycle */
			OC4R = 0;

			/* Set the duty cycle */
			OC4RS = 0;

			/* Set OC4 module: PWM, no fault check, Timer2 */
			OC4CON = 0x0006;

			break;
	}
}

static void inout(scicos_block *block)
{
	/* Get the PWM number [1,2,3,4]     */
	int pin = block->ipar[0];

    /* Get duty cycle from Scicos block */
	double * duty = block->inptr[0];
	
	/* The computed duty cycle*/
	double duty_out ; 

	/* Get period from Timer2 period register PR2 */
	unsigned int period = PR2;	
	
	if ((pin < 1) || (pin > 4))
		return; //** refuse not supported PWM

	if (duty[0] <= 0.0)
		duty_out = 0; //** for negative values assume zero 
	else if(duty[0] >= 1.0)
		duty_out = 1; //** for exessive values assume one 
	else
        duty_out = duty[0]; //** for the correct values ... 

	switch(pin) {
		case 1:	// PWMout1
			OC1RS = duty_out * (period+1);
			break;
		case 2:	// PWMout2
			OC2RS = duty_out * (period+1);
			break;
		case 3:	// PWMout3
			OC3RS = duty_out * (period+1);
			break;
		case 4:	// PWMout4
			OC4RS = duty_out * (period+1);
			break;
	}
}

static void end(scicos_block *block)
{
	int pin = block->ipar[0];
	
	if ((pin < 1) || (pin > 4))
		return;

	switch(pin) {
		case 1:	// PWMout1
			OC1RS  = 0;
			OC1CON = 0;
		case 2:	// PWMout2
			OC2RS  = 0;
			OC2CON = 0;
		case 3:	// PWMout3
			OC3RS  = 0;
			OC3CON = 0;
		case 4:	// PWMout4
			OC4RS  = 0;
			OC4CON = 0;
	}
}

void flex_pwm(scicos_block *block,int flag)
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
