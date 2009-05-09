/* ###*B*###
 * Copyright (C) Roberto Bucher (SUPSI- Lugano)
 *               Simone Mannori (Scilab / INRIA / DIGITEO)
 *
 * Copyright (C) METALAU Project (INRIA)
 * ###*E*### */
 
 
#include <machine.h>
#include <scicos_block4.h>

#include <ee.h>

#define VREF	3.3

static void init(scicos_block *block)
{
	int pin = block->ipar[0];
	
	if (pin > 8)
		pin = 8;
	else if (pin < 1)
		pin = 1;
	block->ipar[0]=pin;
	
	/* turn off ADC module */
	AD1CON1bits.ADON = 0;

	/* set configuration bit for ADC input */
	switch (pin) {
		case 1:	// ANin0 - RB8
			AD1PCFGL &= 0xFEFF;
			break;
		case 2:	// ANin1 - RB9
			AD1PCFGL &= 0xFDFF;
			break;
		case 3:	// ANin2 - RB10
			AD1PCFGL &= 0xFBFF;
			break;
		case 4:	// ANin3 - RB11
			AD1PCFGL &= 0xF7FF;
			break;
		case 5:	// ANin4 - RB12
			AD1PCFGL &= 0xEEFF;
			break;
		case 6:	// ANin5 - RB13
			AD1PCFGL &= 0xFDFF;
			break;
		case 7:	// ANin6 - RB15
			AD1PCFGL &= 0xF7FF;
			break;
		case 8:	// ANin7 - RC1
			AD1PCFGH &= 0xFFFE;
			break;
	}
	
	/* Set control register 1 */
	/* 12-bit, unsigned integer format, autosampling */
	AD1CON1 = 0x04E0;
	
	/* Set control register 2 */
	/* Vref = AVcc/AVdd, Scan Inputs */
	AD1CON2 = 0x0000;
	
	/* Set Samples and bit conversion time */
	/* AS = 31 Tad, Tad = 64 Tcy = 1.6us  */
	AD1CON3 = 0x1F3F; //** Last PATCH xxx
        	
	/* disable channel scanning here */
	AD1CSSL = 0x0000;
	
	/* reset ADC interrupt flag */
	IFS0bits.AD1IF = 0;           

	/* disable ADC interrupts */	  
	IEC0bits.AD1IE = 0;       

	/* turn on ADC module */
	AD1CON1bits.ADON = 1;
}

static void inout(scicos_block *block)
{
	unsigned int adcdata;
	float * y = block->outptr[0];
	
	int pin = block->ipar[0];

	/* channel select */
	switch (pin) {
		case 1:	// ANin0 - RB8
			AD1CHS0 = 8;
			break;
		case 2:	// ANin1 - RB9
			AD1CHS0 = 9;
			break;
		case 3:	// ANin2 - RB10
			AD1CHS0 = 10;
			break;
		case 4:	// ANin3 - RB11
			AD1CHS0 = 11;
			break;
		case 5:	// ANin4 - RB12
			AD1CHS0 = 12;
			break;
		case 6:	// ANin5 - RB13
			AD1CHS0 = 13;
			break;
		case 7:	// ANin6 - RB15
			AD1CHS0 = 15;
			break;
		case 8:	// ANin7 - RC1
			AD1CHS0 = 16;
			break;
	}
	
	/* Start conversion */
	AD1CON1bits.SAMP = 1;
	
	/* Wait till the EOC */
	while(!IFS0bits.AD1IF);
	
	/* reset ADC interrupt flag */
	IFS0bits.AD1IF = 0;           

	/* Acquire data */
	adcdata = ADC1BUF0;
	y[0] = (adcdata * VREF) / 4096;
}

static void end(scicos_block *block)
{
}

void rt_adcin(scicos_block *block,int flag)
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
