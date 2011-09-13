#ifdef __USE_PIT__

#ifndef __INCLUDE_FREESCALE_S12XS_PIT_H__
#define __INCLUDE_FREESCALE_S12XS_PIT_H__

extern volatile EE_UINT8 EE_pit0_initialized;

__INLINE__ void __ALWAYS_INLINE__ EE_pit0_init( unsigned char pitmtld0, unsigned char pitld0, unsigned char prio ) {
	if (EE_pit0_initialized==1) {
		return;
	}
	PITCFLMT      = 0x00;        /* PIT control micro timer register */
	PITFLT        = 0x00;        /* PIT force load timer register */
	PITCE         = 0x01;        /* PIT channel enable register */
	PITMUX        = 0x00;        /* PIT multiplex register */
	PITINTE       = 0x01;        /* PIT interrupt enable register */
	PITTF         = 0x01;        /* PIT time-out flag register */
	PITMTLD0      = pitmtld0;    /* PIT micro timer load reg. 0 */
	PITMTLD1      = 0x00;        /* PIT micro timer load reg. 1 */
	PITLD0        = pitld0;      /* PIT load register 0 */
	PITCNT0       = 0x00;        /* PIT count register 0 */
	PITLD1        = 0x00;        /* PIT load register 1 */
	PITCNT1       = 0x00;        /* PIT count register 1 */
	PITLD2        = 0x00;        /* PIT load register 2 */
	PITCNT2       = 0x00;        /* PIT count register 2 */
	PITLD3        = 0x00;        /* PIT load register 3 */
	PITCNT3       = 0x00;        /* PIT count register 3 */
	PITCFLMT      = 0x80;        /* PIT control micro timer register */
	  
	_asm("cli");
	INT_CFADDR = 0x7A;
	INT_CFDATA0 = prio;
	EE_pit0_initialized = 1;
}

__INLINE__ void __ALWAYS_INLINE__ EE_pit0_close( void ) {
	PITCFLMT = 0x00;        /* PIT control micro timer register */
	EE_pit0_initialized = 0;
}

__INLINE__ void __ALWAYS_INLINE__ EE_pit0_clear_ISRflag( void ) {
	PITTF = 0x01;        
}


#endif

#endif
