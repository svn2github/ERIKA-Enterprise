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
	int pin = block->ipar[0];
	
	if ( (pin < 1) || (pin > 8) )
		return;

	TRISE &= 0xFFFF - ( 0x01 << (pin-1) );
	LATE  &= 0xFFFF - ( 0x01 << (pin-1) ); //** preset the same output to zero 
}

static void inout(scicos_block *block)
{
	float *u = block->inptr[0];
	int pin = block->ipar[0];
	
	if ( (pin < 1) || (pin > 8) )
		return; //** return if outside the allowed range

	if (u[0] > 0.5)      //** threshold is fixed to 0.5 STATIC 
		LATE |= ( 0x01 << (pin-1) ); //** set the bit to one 
	else
		LATE &= 0xFFFF - ( 0x01 << (pin-1) ); //** set the bit to zero
}

static void end(scicos_block *block)
{
	int pin = block->ipar[0];
	
	if ( (pin < 1) || (pin > 8) )
		return;

	LATE  &= 0xFFFF - ( 0x01 << (pin-1) ); //** set the bit to zero at the ending 
}

void flex_dmb_gpout(scicos_block *block,int flag)
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
