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
#define EE_scicos_encoder_get_gain() block->rpar[0]

#define EE_ENCODER_HW 		0
#define EE_ENCODER_SW 		1

#ifdef __USE_DEMOBOARD__
#define EE_ENCODER_SW_PINA	PORTDbits.RD7 	// CN16
#define EE_ENCODER_SW_PINB	PORTCbits.RC4	// digital input
#define EE_ENCODER_SW_ISR()	ISR2(_CNInterrupt) //interrupt handler
#define EE_encoder_clear_ISR_flag() IFS1bits.CNIF = 0
#else
#ifdef __USE_MOTIONBOARD__
#define EE_ENCODER_SW_PINA	PORTDbits.RD8 	// IC1
#define EE_ENCODER_SW_PINB	PORTBbits.RB11	// digital input
#define EE_ENCODER_SW_ISR()	ISR2(_IC1Interrupt)	//interrupt handler
#define EE_encoder_clear_ISR_flag() IFS0bits.IC1IF = 0
#endif
#endif

int ee_encsw_poscnts = 0;

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
		*/
		EE_encoder_init(); //** encoder initialization 
	}
	else // id==2
	{
		/**
		* The second encoder uses the SW encoder driver library
		* and associated operational modes.
		* The driver functioning is based on interrupts on every edge 
		* to update with the max resolution.
		*/
		EE_encoder_SW_init();
	}
}

static void inout(scicos_block *block)
{
	float * y = block->outptr[0];
	int id = EE_scicos_encoder_get_enc_id();
	
	if(id == EE_ENCODER_HW)
	{
		//** the encoder return a float value coded in signed pulse units
		//** this means that the dspic register MUST be read as "int" 
		//** in order to keep the signed comp. 2' bynary rapresentation.
		//** the scaling to degree/radian/centesimal/mm will be done 
		//** in a later release.
		y[0] = (float) EE_encoder_get_position(EE_scicos_encoder_get_gain());
	}
	else // id==2
	{
		y[0] = (float) EE_encoder_SW_get_position(EE_scicos_encoder_get_gain());
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

EE_ENCODER_SW_ISR()
{
	EE_encoder_clear_ISR_flag();
	if(EE_ENCODER_SW_PINA)			// if 1, means rising edge
	{
		if(EE_ENCODER_SW_PINB)		// reverse - PhaseA lags PhaseB
			ee_encsw_poscnts--;
		else						// forward - PhaseA leads PhaseB
			ee_encsw_poscnts++;
		
	}
	else							// if 0, means falling edge
	{
		if(EE_ENCODER_SW_PINB)		// forward - PhaseA leads PhaseB
			ee_encsw_poscnts++;
		else						// reverse - PhaseA lags PhaseB
			ee_encsw_poscnts--;
		
	}
}
