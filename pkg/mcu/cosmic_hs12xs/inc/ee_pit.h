#ifdef __USE_PIT__

#ifndef __INCLUDE_FREESCALE_S12XS_PIT_H__
#define __INCLUDE_FREESCALE_S12XS_PIT_H__

#include "ee.h"

/* Include a file with the registers from Microchip C30 distribution */ 
#ifdef __S12XS_INCLUDE_REGS__
#include "ee_hs12xsregs.h"
#endif

extern EE_UINT8 EE_pit0_init;

__INLINE__ void __ALWAYS_INLINE__ EE_PIT0_init( unsigned char pitmtld0, unsigned char pitld0, unsigned char prio )
{
	if(EE_pit0_init==1)
		return;
	/*	PIT Module
 	*/
	  PITCFLMT      = 0x00;        //@0x340;	/* PIT control micro timer register */
	  PITFLT        = 0x00;        //@0x341;	/* PIT force load timer register */
	  PITCE         = 0x01;        //@0x342;	/* PIT channel enable register */
	  PITMUX        = 0x00;        //@0x343;	/* PIT multiplex register */
	  PITINTE       = 0x01;        //@0x344;	/* PIT interrupt enable register */
	  PITTF         = 0x01;        //@0x345;	/* PIT time-out flag register */
	  PITMTLD0      = pitmtld0;        //@0x346;	/* PIT micro timer load reg. 0 */
	  PITMTLD1      = 0x00;        //@0x347;	/* PIT micro timer load reg. 1 */
	  PITLD0        = pitld0;        //@0x348;	/* PIT load register 0 */
	  PITCNT0       = 0x00;        //@0x34a;	/* PIT count register 0 */
	  PITLD1        = 0x00;        //@0x34c;	/* PIT load register 1 */
	  PITCNT1       = 0x00;        //@0x34e;	/* PIT count register 1 */
	  PITLD2        = 0x00;        //@0x350;	/* PIT load register 2 */
	  PITCNT2       = 0x00;        //@0x352;	/* PIT count register 2 */
	  PITLD3        = 0x00;        //@0x354;	/* PIT load register 3 */
	  PITCNT3       = 0x00;        //@0x356;	/* PIT count register 3 */
	  PITCFLMT      = 0x80;        //@0x340;	/* PIT control micro timer register */
	  
	  // IVBR = 0xff;      // 0xFF default value
	  _asm("cli");
	  INT_CFADDR = 0x7A;
	  INT_CFDATA0 = prio;
	  EE_pit0_init = 1;
	  
	  return;
}

__INLINE__ void __ALWAYS_INLINE__ EE_PIT0_close( void )
{
	PITCFLMT      = 0x00;        //@0x340;	/* PIT control micro timer register */
	EE_pit0_init = 0;
}


#endif

#endif
