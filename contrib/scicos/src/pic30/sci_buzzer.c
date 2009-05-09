/* ###*B*###
 * Copyright (C) Roberto Bucher (SUPSI- Lugano)
 *               Simone Mannori (Scilab / INRIA / DIGITEO)
 *
 * Copyright (C) METALAU Project (INRIA)
 * ###*E*### */
 
 
#include <machine.h>
#include <scicos_block.h>

#include <ee.h>

static void init(scicos_block *block)
{
// Initialize Output Compare Module
OC1CONbits.OCM = 0b000; // Disable Output Compare Module
OC1R = 300; // Write the duty cycle for the first PWM pulse
OC1RS = 1250; // Write the duty cycle for the second PWM pulse
OC1CONbits.OCTSEL = 1; // Select Timer 3 as output compare time base
OC1R = 1250; // Load the Compare Register Value
OC1CONbits.OCM = 0b110; // Select the Output Compare mode
// Initialize and enable Timer2
T3CONbits.TON = 0; // Disable Timer
T3CONbits.TCS = 0; // Select internal instruction cycle clock
T3CONbits.TGATE = 0; // Disable Gated Timer mode
//T2CONbits.TCKPS = 0b00; // Select 1:1 Prescaler
	T3CONbits.TCKPS = 1;
TMR3 = 0x00; // Clear timer register
PR3 = 2500; // Load the period value
IPC2bits.T3IP = 0x01; // Set Timer 2 Interrupt Priority Level
IFS0bits.T3IF = 0; // Clear Timer 2 Interrupt Flag
//IEC0bits.T2IE = 1; // Enable Timer 2 interrupt
T3CONbits.TON = 0; // Start Timer
}

EE_UINT16 buzzer_freq = 0;

static void inout(scicos_block *block)
{
	if (block->inptr[0][0] <= 10) {
		// Stop PWM
		OC1CONbits.OCM = 0;
	
		// Stop Timer3 
		T3CONbits.TON = 0;
		
		// Store frequency value 
		buzzer_freq = 0;
	} else {
		if ( ((block->inptr[0][0] - buzzer_freq) > 10) || ((block->inptr[0][0] - buzzer_freq) < -10) ) {
			// Stop PWM
			OC1CONbits.OCM = 0;

			// Stop Timer3
			T3CONbits.TON = 0;

			// Load the Period register wit the computed value 
			PR3 = 5000000ul / block->inptr[0][0];
		
			// Set the initial duty cycle 
			OC1R = PR3 >> 1;

			// Set the duty cycle 
			OC1RS = OC1R;

			// Start Timer3
			T3CONbits.TON = 1;

			// Start PWM
			OC1CONbits.OCM = 6;

			// Store frequency value 
			buzzer_freq = block->inptr[0][0];
		}
	}
}

static void end(scicos_block *block)
{
	/* Stop PWM*/
	OC1CONbits.OCM = 0;
	
	/* Stop Timer3 */
	T3CONbits.TON = 0;
}

void rt_buzzer(scicos_block *block,int flag)
{
	switch (flag) {
		case 1:	/* set output */
		case 2:	/* get input */
			inout(block);
			break;
		case 5:	/* ending */
			end(block);
			break;
		case 4:	/* initialisation */
			init(block);
			break;
	}
}
