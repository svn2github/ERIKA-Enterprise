
/* ###*B*###
 * 
 * Copyright (C) Francesco Prosperi (SSSA - Pisa)
 *
 * ###*E*### */
 
#include <ee.h>
#include <machine.h>
#include <scicos_block4.h>

static void init(scicos_block *block)
{
	int pin = block->ipar[0];
	
	if ((pin < 1) || (pin > 2))
		return;

	EE_pwm_init( pin-1 , 20000 , 0 );
}
 
static void inout(scicos_block *block)
{
	/* Get the PWM number [1,2]     */
	int pin = block->ipar[0];

	/* Get duty cycle from Scicos block */
	float *duty = block->inptr[0];
	
	if ((pin < 1) || (pin > 2))
		return; //** refuse not supported PWM

	EE_pwm_set_duty_f( pin-1 , *duty);
}

static void end(scicos_block *block)
{
	int pin = block->ipar[0];
	
	if ((pin < 1) || (pin > 2))
		return; //** refuse not supported PWM

	EE_pwm_close(pin);
}

void amazing_pwm(scicos_block *block,int flag)
{
	switch (flag) {
		case OutputUpdate:
			inout(block);
			break;
    		case StateUpdate:
			break;
		case Initialization:
			// Already done by AMAZING_config
			break;
		case Ending:
			end(block);
			break;
	}
}

