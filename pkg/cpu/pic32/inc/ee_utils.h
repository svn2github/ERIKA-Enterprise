#ifndef __INCLUDE_PIC32_EE_UTILS_H__
#define __INCLUDE_PIC32_EE_UTILS_H__

#include "cpu/pic32/inc/ee_compiler.h"
#include "ee_pic32regs.h"


/* External Clock Source, redefine in the application if differs from this
*  value */
#ifndef CLOCK_SOURCE
#define CLOCK_SOURCE 8000000ul
#endif 


#ifndef DEVCFG2
#define DEVCFG2  0xBFC02FF4 //virtual address of the register
#endif //DEVCFG2

#ifndef PLLIDIV_MASK
#define PLLIDIV_MASK 0x7
#endif 


/* Function used to calculate the initialize the system */
__INLINE__ void __ALWAYS_INLINE__ EE_system_init(void)
{
	EE_UREG r;

	DDPCONbits.JTAGEN = 0;  // disable JTAG port
        /* chris: TODO: understanding the meaning of this */
        asm volatile("mfc0   %0,$13" : "=r"(r));
        r |= 0x00800000; 	// set the CP0 cause IV bit high
        asm volatile("mtc0   %0,$13" : "+r"(r));
        INTCONSET = _INTCON_MVEC_MASK;
	ASM_EN_INT; 		// Enable IRQ
}

/* Function used to calculate the system clock */
__INLINE__ unsigned int __ALWAYS_INLINE__ EE_get_system_clock(void)
{
	unsigned int FPPLIDIV_VAL [8] = {1,2,3,4,5,6,10,12};
	unsigned int PLLODIV_VAL [8] = {1,2,4,8,16,32,64,256};
	unsigned int PLLMULT_VAL [8] = {15,16,17,18,19,20,21,24};

	/* Extraction of pplodiv */
	unsigned int pllodiv =  (unsigned int) OSCCONbits.PLLODIV;
	pllodiv = PLLODIV_VAL[pllodiv];	
	
	/* Extraction of pplmult */
	unsigned int pllmult =  (unsigned int) OSCCONbits.PLLMULT;
	pllmult = PLLMULT_VAL[pllmult];
	
	/* Extraction of pplidiv */
	unsigned int *app;
	app = (void *) DEVCFG2;
	unsigned int fpllidiv = *app;	
	fpllidiv =  FPPLIDIV_VAL[(fpllidiv & PLLIDIV_MASK)];
	  
	return  (CLOCK_SOURCE * pllmult / (fpllidiv * pllodiv));
}


/* Function used to calculate the peripherals clock */
__INLINE__ unsigned int __ALWAYS_INLINE__ EE_get_peripheral_clock(void)
{
	unsigned int PBDIV_VAL [4] = {1,2,4,8};
	unsigned int pbdiv = PBDIV_VAL[OSCCONbits.PBDIV];

	return  (EE_get_system_clock() / pbdiv);
}

#endif  /* __INCLUDE_PIC32_EE_UTILS_H__ */
