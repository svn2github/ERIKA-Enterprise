

#ifdef __USE_CN__

#include "ee_cn.h"

union EE_cn_status_bits_t EE_cn_status_bits;

void EE_CN_init() {
	/* The CN pins are configured as follows:
	 * 1.  Disable CPU interrupts. */
	asm("di");
	/* 2.  Set desired CN I/O pin as input by setting corresponding TRISx
	 *     register bits = 1.
	 * Note: If the I/O pin is shared with an analog peripheral, it may be
	 * necessary to set the corresponding AD1PCFG register bit = 1 to ensure
	 * that the I/O pin is a digital input.
	// To be done by EE_CN_ENABLE() */
	/* 3. Enable CN Module ON (CNCON<15>) = 1. */
	CNCONbits.ON = 1;
	/* 4. Enable individual CN input pin(s), enable optional pull up(s). */
	// To be done by EE_CN_ENABLE()
	/* 5. Read corresponding PORT registers to clear mismatch condition on
	 * CN input pins.*/
	PORTB;
	PORTC;
	PORTD;
	PORTF;
	PORTG;
	/* 6. Configure the CN interrupt priority, CNIP<2:0>, and subpriority
	 * CNIS<1:0>. */
	// TODO: how to handle priority?
	/* 7. Clear CN interrupt flag, CNIF = 0. */
	IFS1bits.CNIF = 0;
	/* 8. Enable CN interrupt enable, CNIE = 1. */
	IEC1bits.CNIE = 1;
	/* 9. Enable CPU interrupts. */
	asm("ei");
}

/*
 * @TODO: expliciting the ISR2 macro may be faster
 */
ISR2(_CHANGE_NOTICE_VECTOR) {
	CN_CHECK(CN_RADIO)
}

#endif /* __USE_CN__ */

