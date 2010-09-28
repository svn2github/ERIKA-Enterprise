/* ###*B*###
* Copyright (C) Roberto Bucher (SUPSI- Lugano)
*               Simone Mannori (Scilab / INRIA / DIGITEO)
*
* Copyright (C) METALAU Project (INRIA)
* ###*E*### */


//** 9 Feb 2008 : Revision notes by Simone Mannori 
//** 26 July 2010 : SW encoder added by Dario Di Stefano 


#include <machine.h>
#include <scicos_block4.h>
#include <ee.h>

/* Encoder bit allocation 
	HW encoder pins (motion demoII board, demo board):
	QEA/RB4 pin
	QEB/RB5 pin
	SW encoder pins (motion demoII board):
	IC1/RD8 pin (channel A) -> irq
	RB11 pin	(channel B)
	SW encoder pins (demo board):
	CN16/RD7 pin (channel A) -> irq
	RC4 pin		 (channel B)
*/

#define EE_scicos_encoder_get_enc_id() block->ipar[0]
//#define EE_scicos_encoder_get_gain() block->rpar[0]
//#define Deg_2_Rad			1.745329251994330e-002F
//#define EE_ENCODER_HW_GAIN	Deg_2_Rad
//#define EE_ENCODER_SW_GAIN	Deg_2_Rad*2.0                           // 2.0 

static void init(scicos_block *block)
{
	int id = EE_scicos_encoder_get_enc_id();
	
	if(id == EE_ENCODER_HW)
	{
		/**
		* The first encoder uses the Quadrature Encoder Interface
		* (QEI) module and associated operational modes.
		* The QEI module provides the interface to incremental
		* encoders for obtaining mechanical position data.
		* Max Resolution: 4x.
		*/
		EE_encoder_init(1, 1); 
	}
	else // sw encoder
	{
		/**
		* The second encoder uses the SW encoder driver library
		* and associated operational modes.
		* The driver functioning is based on interrupts on every edge 
		* of channel A so we haven't the max resolution, but only 2x.
		*/
		EE_encoder_SW_init(1, 1);
	}
}

static void inout(scicos_block *block)
{
	float *y = block->outptr[0];
	int id = EE_scicos_encoder_get_enc_id();
	
	if(id == EE_ENCODER_HW)
	{
		/** 
		* The encoder return a float value coded in signed pulse units
		* this means that the dspic register MUST be read as "int" 
		* in order to keep the signed comp. 2' bynary rapresentation.
		* the scaling to degree/radian/centesimal/mm must be done 
		* in the scicos diagram.
		*/
		y[0] = (float) EE_encoder_get_ticks();
	}
	else // sw encoder
	{
		/** 
		* Because of 2x resolution, we have to double the number of counter ticks
		* to have the same behaviour of hw encoder. 
		* TODO: 4x resolution in the next releases...
		*/
		y[0] = (float) EE_encoder_SW_get_ticks() * 2.0;
	}
}

static void end(scicos_block *block)
{
}

void flex_daughter_encoder(scicos_block *block,int flag)
{
	switch (flag) {
	case OutputUpdate:  /* set output */
		inout(block);
		break;

	case StateUpdate:  /* get input */
		break;

	case Initialization:  /* initialisation */
		init(block);
		break;

	case Ending:  /* ending */
		end(block);
		break;
	}
}

