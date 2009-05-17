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

static void init(scicos_block *block)
{
	int pin = block->ipar[0];
	
	if ((pin < 1) || (pin > 2))
		return;

	EE_pwm_init( 0, pin );
}

static void inout(scicos_block *block)
{
	/* Get the PWM number [1,2,3,4]     */
	int pin = block->ipar[0];

	/* Get duty cycle from Scicos block */
	float * duty = block->inptr[0];
	
	if ((pin < 1) || (pin > 2))
		return; //** refuse not supported PWM

	EE_pwm_set_duty( *duty, pin );
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
		case 1:	/* set output */
			inout(block);
			break;

		case 2:	/* get input */
			inout(block);
			break;
		
		case 4:	/* initialisation */
			init(block);
			break;
		
		case 5:	/* ending */
			end(block);
			break;
	}
}
