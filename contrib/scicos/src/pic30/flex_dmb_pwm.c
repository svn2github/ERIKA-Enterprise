/* ###*B*###
 * Copyright (C) Roberto Bucher (SUPSI- Lugano)
 *               Simone Mannori (Scilab / INRIA / DIGITEO)
 *
 * Copyright (C) METALAU Project (INRIA)
 * ###*E*### */
 
// Last modify by Francesco Prosperi
 
#include <machine.h>
#include <scicos_block4.h>

#include <ee.h>

static void init(scicos_block *block)
{
	int pin = block->ipar[0];
	
	if ((pin < 1) || (pin > 2))
		return;

	EE_pwm_init( pin , 20000 , 0 );
}
 
static void inout(scicos_block *block)
{
	/* Get the PWM number [1,2,3,4]     */
	int pin = block->ipar[0];

	/* Get duty cycle from Scicos block */
	float *duty = block->inptr[0];
	
	if ((pin < 1) || (pin > 2))
		return; //** refuse not supported PWM

	EE_pwm_set_duty_f( pin , 1.0 - *duty);
}

static void end(scicos_block *block)
{
	int pin = block->ipar[0];
	
	if ((pin < 1) || (pin > 2))
		return; //** refuse not supported PWM

	EE_pwm_close(pin);
}

void flex_dmb_pwm(scicos_block *block,int flag)
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
