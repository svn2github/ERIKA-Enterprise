/* ###*B*###
 * Copyright (C) Roberto Bucher (SUPSI- Lugano)
 *               Simone Mannori (Scilab / INRIA / DIGITEO)
 *
 * Copyright (C) METALAU Project (INRIA)
 * ###*E*### */
 
 
#include <machine.h>
#include <scicos_block4.h>

#include <ee.h>

__INLINE__ void __ALWAYS_INLINE__ EE_debugs_on(void)  { LATB |= 0x003C; }
__INLINE__ void __ALWAYS_INLINE__ EE_debugs_off(void) { LATB &= 0xFFC3; }

__INLINE__ void __ALWAYS_INLINE__ EE_debug_1_on(void)  { LATBbits.LATB2 = 1; }
__INLINE__ void __ALWAYS_INLINE__ EE_debug_1_off(void) { LATBbits.LATB2 = 0; }

__INLINE__ void __ALWAYS_INLINE__ EE_debug_2_on(void)  { LATBbits.LATB3 = 1; }
__INLINE__ void __ALWAYS_INLINE__ EE_debug_2_off(void) { LATBbits.LATB3 = 0; }

__INLINE__ void __ALWAYS_INLINE__ EE_debug_3_on(void)  { LATBbits.LATB4 = 1; }
__INLINE__ void __ALWAYS_INLINE__ EE_debug_3_off(void) { LATBbits.LATB4 = 0; }

__INLINE__ void __ALWAYS_INLINE__ EE_debug_4_on(void)  { LATBbits.LATB5 = 1; }
__INLINE__ void __ALWAYS_INLINE__ EE_debug_4_off(void) { LATBbits.LATB5 = 0; }

void debug_init(scicos_block *block)
{
	/* set LEDs state low */
	LATBbits.LATB2 = 0; 
	LATBbits.LATB3 = 0; 
	LATBbits.LATB4 = 0; 
	LATBbits.LATB5 = 0; 
	
	/* set LEDs pins as outputs */
	TRISBbits.TRISB2 = 0; 
	TRISBbits.TRISB3 = 0; 
	TRISBbits.TRISB4 = 0; 
	TRISBbits.TRISB5 = 0; 
}
