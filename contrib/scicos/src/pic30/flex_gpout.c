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

   WARNING : the GPIO Pin are allocated on CN5 AND CN6 
             look closely at the "Flex Connectors" allocation 

Scicos   Function   dsPIC   Flex Connectors
Pin=1    GPIO0	    RD8	    CON5.P7	
Pin=2    GPIO1      RD9	    CON5.P10	
Pin=3    GPIO2	    RD10	CON5.P9
Pin=4    GPIO3      RD11	CON5.P12
Pin=5    GPIO4      RD12	CON5.P15
Pin=6    GPIO5      RD13	CON5.P18
Pin=7    GPIO6      RD14	CON6.P35 : 
Pin=8    GPIO7      RD15	CON6.P38 : 
*/

static void init(scicos_block *block)
{
	int pin = block->ipar[0];
	
	if ( (pin < 1) || (pin > 8) )
		return;
	//** TRISx(x=A,B,C,D,...) is the hree state oout enable bit, one bit for each output
	//
	// ---------------------> WARNING: <-------------------------------------
	//**  TRISx works AS OPPOSITE AS standard I/O bit control register because
	//** "0" => is an OUTPUT
	//** "1" => is an INPUT 
    //
	//** The bit position is offset because
	//** the first Scicos Pin is the first I/O bit (zero)
	//** the first I/O bit is in postion "8" in the 16 bit I/O register 
	//** To define an OUTPUT, but te corresponding bit to ZERO
	TRISD &= 0xFFFF - ( 0x01 << (pin-1+8) ); //** "-1+8" because  Pin=1 => RegisterPort_D.bit8
	LATB  &= 0xFFFF - ( 0x01 << (pin-1+8) ); //** preset the same output to zero 
}

static void inout(scicos_block *block)
{
  float *u = block->inptr[0];
	int pin = block->ipar[0];
	
    //** Mark in 
    LATBbits.LATB5 = 1;
	
	if ( (pin < 1) || (pin > 8) )
		return;

	if (u[0] > 0.5)      //** threshold is fixed to 0.5 STATIC 
		LATD |= ( 0x01 << (pin-1+8) ); //** set the bit to one 
	else
		LATD &= 0xFFFF - ( 0x01 << (pin-1+8) ); //** set the bit to zero

    //** Mark out 
    LATBbits.LATB5 = 0;
}

static void end(scicos_block *block)
{
	int pin = block->ipar[0];
	
	if ( (pin < 1) || (pin > 8) )
		return;

	LATD  &= 0xFFFF - ( 0x01 << (pin-1+8) ); //** set the bit to zero at the ending 
}

void flex_gpout(scicos_block *block,int flag)
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
