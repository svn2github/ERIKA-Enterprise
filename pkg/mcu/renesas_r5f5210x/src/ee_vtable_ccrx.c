/* ###*B*###
 * ERIKA Enterprise - a tiny RTOS for small microcontrollers
 *
 * Copyright (C) 2002-2012  Evidence Srl
 *
 * This file is part of ERIKA Enterprise.
 *
 * ERIKA Enterprise is free software; you can redistribute it
 * and/or modify it under the terms of the GNU General Public License
 * version 2 as published by the Free Software Foundation, 
 * (with a special exception described below).
 *
 * Linking this code statically or dynamically with other modules is
 * making a combined work based on this code.  Thus, the terms and
 * conditions of the GNU General Public License cover the whole
 * combination.
 *
 * As a special exception, the copyright holders of this library give you
 * permission to link this code with independent modules to produce an
 * executable, regardless of the license terms of these independent
 * modules, and to copy and distribute the resulting executable under
 * terms of your choice, provided that you also meet, for each linked
 * independent module, the terms and conditions of the license of that
 * module.  An independent module is a module which is not derived from
 * or based on this library.  If you modify this code, you may extend
 * this exception to your version of the code, but you are not
 * obligated to do so.  If you do not wish to do so, delete this
 * exception statement from your version.
 *
 * ERIKA Enterprise is distributed in the hope that it will be
 * useful, but WITHOUT ANY WARRANTY; without even the implied warranty
 * of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License version 2 for more details.
 *
 * You should have received a copy of the GNU General Public License
 * version 2 along with ERIKA Enterprise; if not, write to the
 * Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
 * Boston, MA 02110-1301 USA.
 * ###*E*### */

/**
	@file ee_vtable_ccrx.c
	@brief Interrupt Vector Table for use with Renesas HEW.
	@author Gianluca Franchino
	@date 2012
 */

#include "ee.h"

/*
 * Extern declaration of the default handlers.
 */
extern void EE_rx200_default_ISR(void);		// Default Handler

#ifdef EE_RX200_BUSERR_ISR
extern void EE_RX200_BUSERR_ISR(void);	//The BUS error handler
#endif 

#ifdef EE_RX200_FIFERR_ISR
extern void EE_RX200_FIFERR_ISR(void);	//The FLASH interface handler
#endif 

#ifdef EE_RX200_FRDYI_ISR
extern void EE_RX200_FRDYI_ISR(void);	//The FLASH READY handler
#endif

#ifdef EE_RX200_SWINT_ISR
extern void EE_RX200_SWINT_ISR(void);	//The Software Interr. handler
#endif 

#ifdef EE_RX200_CMI0_ISR
extern void EE_RX200_CMI0_ISR(void);	//The Compare Match 0 handler
#endif 

#ifdef EE_RX200_CMI1_ISR
extern void EE_RX200_CMI1_ISR(void);	//The Compare Match 1 handler
#endif 

#ifdef EE_RX200_CMI2_ISR
extern void EE_RX200_CMI2_ISR(void);	//The Compare Match 2 handler
#endif

#ifdef EE_RX200_CMI3_ISR
extern void EE_RX200_CMI3_ISR(void);	//The Compare Match 3 handler
#endif

#ifdef EE_RX200_FERRF_ISR
extern void EE_RX200_FERRF_ISR(void);	//The Freq. Err. Interr. handler
#endif 

#ifdef EE_RX200_MENDF_ISR
extern void EE_RX200_MENDF_ISR(void);	//The Measur. End Interr. handler
#endif 

#ifdef EE_RX200_OVFF_ISR
extern void EE_RX200_OVFF_ISR(void);	//The Overflow Interr. handler
#endif

#ifdef EE_RX200_SPEI0_ISR
extern void EE_RX200_SPEI0_ISR(void);	//The SCI Error handler
#endif 

#ifdef EE_RX200_SPRIO_ISR
extern void EE_RX200_SPRIO_ISR(void);	//The  SCI RX Interr. handler
#endif 

#ifdef EE_RX200_SPTIO_ISR
extern void EE_RX200_SPTIO_ISR(void);	//The SCI TX Interr. handler
#endif

#ifdef EE_RX200_SPIIO_ISR
extern void EE_RX200_SPIIO_ISR(void);	//The SCI IO Interr. handler
#endif

#ifdef EE_RX200_DOPCF_ISR
extern void EE_RX200_DOPCF_ISR(void);	//The Data oper. circuit Interr. handler
#endif

#ifdef EE_RX200_COMPB0_ISR
extern void EE_RX200_COMPB0_ISR(void);	//The Comparator B0 Interr. handler
#endif

#ifdef EE_RX200_COMPB1_ISR
extern void EE_RX200_COMPB1_ISR(void);	//The Comparator B1 Interr. handler
#endif

#ifdef EE_RX200_COUNTUP_ISR
extern void EE_RX200_COUNTUP_ISR(void);	//The RTC Countup Interr. handler
#endif

#ifdef EE_RX200_IRQ0_ISR
extern void EE_RX200_IRQ0_ISR(void);	//The IRQ0 Interr. handler
#endif

#ifdef EE_RX200_IRQ1_ISR
extern void EE_RX200_IRQ1_ISR(void);	//The IRQ1 Interr. handler
#endif

#ifdef EE_RX200_IRQ2_ISR
extern void EE_RX200_IRQ2_ISR(void);	//The IRQ2 Interr. handler
#endif

#ifdef EE_RX200_IRQ3_ISR
extern void EE_RX200_IRQ3_ISR(void);	//The IRQ3 Interr. handler
#endif

#ifdef EE_RX200_IRQ4_ISR
extern void EE_RX200_IRQ4_ISR(void);	//The IRQ4 Interr. handler
#endif

#ifdef EE_RX200_IRQ5_ISR
extern void EE_RX200_IRQ5_ISR(void);	//The IRQ5 Interr. handler
#endif

#ifdef EE_RX200_IRQ6_ISR
extern void EE_RX200_IRQ6_ISR(void);	//The IRQ6 Interr. handler
#endif

#ifdef EE_RX200_IRQ7_ISR
extern void EE_RX200_IRQ7_ISR(void);	//The IRQ7 Interr. handler
#endif

#ifdef EE_RX200_LVDI1_COMP1_ISR
extern void EE_RX200_LVDI1_COMP1_ISR(void);	//The LVD1/COMPA1. Interr. handler
#endif

#ifdef EE_RX200_LVDI2_COMP2_ISR
extern void EE_RX200_LVDI2_COMP2_ISR(void);	//The LVD2/COMPA2. Interr. handler
#endif

#ifdef EE_RX200_ALM_ISR
extern void EE_RX200_ALM_ISR(void);	//The RTC Alarm Interr. handler
#endif

#ifdef EE_RX200_PRD_ISR
extern void EE_RX200_PRD_ISR(void);	//The RTC Periodic Interr. handler
#endif

#ifdef EE_RX200_S12ADI0_ISR
extern void EE_RX200_S12ADI0_ISR(void);	//The 12-bit ADC scan end int. handler
#endif

#ifdef EE_RX200_GBADI_ISR
extern void EE_RX200_GBADI_ISR(void);	//The 12-bit ADC group B scan end 
#endif									//int handler

#ifdef EE_RX200_ELSR18I_ISR
extern void EE_RX200_ELSR18I_ISR(void);	//Event link SR18 int. handler
#endif

#ifdef EE_RX200_ELSR19I_ISR
extern void EE_RX200_ELSR19I_ISR(void);	//Event link SR19 int. handler
#endif

#ifdef EE_RX200_TGIA0_ISR
extern void EE_RX200_TGIA0_ISR(void);	//The MTU0.TGRA  input capture/comp match
#endif									//int. handler

#ifdef EE_RX200_TGIB0_ISR
extern void EE_RX200_TGIB0_ISR(void);	//The MTU0.TGRB input capture/comp match
#endif									//int. handler

#ifdef EE_RX200_TGIC0_ISR
extern void EE_RX200_TGIC0_ISR(void);	//The MTU0.TGRC input capture/comp match
#endif									//int. handler

#ifdef EE_RX200_TGID0_ISR
extern void EE_RX200_TGID0_ISR(void);	//The MTU0.TGRD input capture/comp match
#endif									//int. handler

#ifdef EE_RX200_TCIV0_ISR
extern void EE_RX200_TCIV0_ISR(void);	//The MTU0.TCNT overflow int. handler
#endif									

#ifdef EE_RX200_TGIE0_ISR
extern void EE_RX200_TGIE0_ISR(void);	//MTU0.TGRE compare match int. handler
#endif

#ifdef EE_RX200_TGIF0_ISR
extern void EE_RX200_TGIF0_ISR(void);	//MTU0.TGRF compare match int. handler
#endif	

#ifdef EE_RX200_TGIA1_ISR
extern void EE_RX200_TGIA1_ISR(void);	//The MTU1.TGRA  input capture/comp match
#endif									//int. handler

#ifdef EE_RX200_TGIB1_ISR
extern void EE_RX200_TGIB1_ISR(void);	//The MTU1.TGRB input capture/comp match
#endif

#ifdef EE_RX200_TCIV1_ISR
extern void EE_RX200_TCIV1_ISR(void);	//The MTU1.TCNT overflow int. handler
#endif

#ifdef EE_RX200_TCIU1_ISR
extern void EE_RX200_TCIU1_ISR(void);	//The MTU1.TCNT undeflow int. handler
#endif

#ifdef EE_RX200_TGIA2_ISR
extern void EE_RX200_TGIA2_ISR(void);	//The MTU2.TGRA  input capture/comp match
#endif									//int. handler

#ifdef EE_RX200_TGIB2_ISR
extern void EE_RX200_TGIB2_ISR(void);	//The MTU2.TGRB input capture/comp match
#endif

#ifdef EE_RX200_TCIV2_ISR
extern void EE_RX200_TCIV2_ISR(void);	//The MTU2.TCNT overflow int. handler
#endif

#ifdef EE_RX200_TCIU2_ISR
extern void EE_RX200_TCIU2_ISR(void);	//The MTU2.TCNT undeflow int. handler
#endif

#ifdef EE_RX200_TGIA3_ISR
extern void EE_RX200_TGIA3_ISR(void);	//The MTU3.TGRA  input capture/comp match
#endif									//int. handler

#ifdef EE_RX200_TGIB3_ISR
extern void EE_RX200_TGIB3_ISR(void);	//The MTU3.TGRB input capture/comp match
#endif									//int. handler

#ifdef EE_RX200_TGIC3_ISR
extern void EE_RX200_TGIC3_ISR(void);	//The MTU3.TGRC input capture/comp match
#endif									//int. handler

#ifdef EE_RX200_TGID3_ISR
extern void EE_RX200_TGID3_ISR(void);	//The MTU3.TGRD input capture/comp match
#endif									//int. handler

#ifdef EE_RX200_TCIV3_ISR
extern void EE_RX200_TCIV3_ISR(void);	//The MTU3.TCNT overflow int. handler
#endif									

#ifdef EE_RX200_TGIA4_ISR
extern void EE_RX200_TGIA4_ISR(void);	//The MTU4.TGRA  input capture/comp match
#endif									//int. handler

#ifdef EE_RX200_TGIB4_ISR
extern void EE_RX200_TGIB4_ISR(void);	//The MTU4.TGRB input capture/comp match
#endif									//int. handler

#ifdef EE_RX200_TGIC4_ISR
extern void EE_RX200_TGIC4_ISR(void);	//The MTU4.TGRC input capture/comp match
#endif									//int. handler

#ifdef EE_RX200_TGID4_ISR
extern void EE_RX200_TGID4_ISR(void);	//The MTU4.TGRD input capture/comp match
#endif									//int. handler

#ifdef EE_RX200_TCIV4_ISR
extern void EE_RX200_TCIV4_ISR(void);	//The MTU4.TCNT overflow int. handler
#endif

#ifdef EE_RX200_TGIU5_ISR
extern void EE_RX200_TGIU5_ISR(void);	//The MTU5.TGRU input capture/comp 
#endif									//match ISR

#ifdef EE_RX200_TGIV5_ISR
extern void EE_RX200_TGIV5_ISR(void);	//The MTU5.TGRV input capture/comp 
#endif									//match ISR

#ifdef EE_RX200_TCIW5_ISR
extern void EE_RX200_TCIW5_ISR(void);	//The MTU5.TGRW input capture/comp 
#endif									//match ISR

#ifdef EE_RX200_OEI1_ISR
extern void EE_RX200_OEI1_ISR(void);	//The Port Output 1 (POE1) int. handler.
#endif

#ifdef EE_RX200_OEI2_ISR
extern void EE_RX200_OEI2_ISR(void);	//The Port Output 2 (POE2) int. handler.
#endif

#ifdef EE_RX200_CMIA0_ISR
extern void EE_RX200_CMIA0_ISR(void);	//The TMR0 compare match A int. handler.
#endif									

#ifdef EE_RX200_CMIB0_ISR
extern void EE_RX200_CMIB0_ISR(void);	//The TMR0 compare match B int. handler.
#endif

#ifdef EE_RX200_OVI0_ISR
extern void EE_RX200_OVI0_ISR(void);	//The TMR0 TCNT overflow int. handler.
#endif

#ifdef EE_RX200_CMIA1_ISR
extern void EE_RX200_CMIA1_ISR(void);	//The TMR1 compare match A int. handler.
#endif									

#ifdef EE_RX200_CMIB1_ISR
extern void EE_RX200_CMIB1_ISR(void);	//The TMR1 compare match B int. handler.
#endif

#ifdef EE_RX200_OVI1_ISR
extern void EE_RX200_OVI1_ISR(void);	//The TMR1 TCNT overflow int. handler.
#endif

#ifdef EE_RX200_CMIA2_ISR
extern void EE_RX200_CMIA2_ISR(void);	//The TMR2 compare match A int. handler.
#endif									

#ifdef EE_RX200_CMIB2_ISR
extern void EE_RX200_CMIB2_ISR(void);	//The TMR2 compare match B int. handler.
#endif

#ifdef EE_RX200_OVI2_ISR
extern void EE_RX200_OVI2_ISR(void);	//The TMR2 TCNT overflow int. handler.
#endif

#ifdef EE_RX200_CMIA3_ISR
extern void EE_RX200_CMIA3_ISR(void);	//The TMR3 compare match A int. handler.
#endif									

#ifdef EE_RX200_CMIB3_ISR
extern void EE_RX200_CMIB3_ISR(void);	//The TMR3 compare match B int. handler.
#endif

#ifdef EE_RX200_OVI3_ISR
extern void EE_RX200_OVI3_ISR(void);	//The TMR3 TCNT overflow int. handler.
#endif

#ifdef EE_RX200_DMAC0I_ISR
extern void EE_RX200_DMAC0I_ISR(void);	//The DMAC channel 0 transfer end ISR.
#endif

#ifdef EE_RX200_DMAC1I_ISR
extern void EE_RX200_DMAC1I_ISR(void);	//The DMAC channel 1 transfer end ISR.
#endif									

#ifdef EE_RX200_DMAC2I_ISR
extern void EE_RX200_DMAC2I_ISR(void);	//The DMAC channel 2 transfer end ISR.
#endif

#ifdef EE_RX200_DMAC3I_ISR
extern void EE_RX200_DMAC3I_ISR(void);	//The DMAC channel 3 transfer end ISR.
#endif

#ifdef EE_RX200_ERI0_ISR
extern void EE_RX200_ERI0_ISR(void);	//The SCI0 Receive Error int. handler.
#endif

#ifdef EE_RX200_RXI0_ISR
extern void EE_RX200_RXI0_ISR(void);	//The SCI0 RX int. handler.
#endif									

#ifdef EE_RX200_TXI0_ISR
extern void EE_RX200_TXI0_ISR(void);	//The SCI0 TX empty int. handler.
#endif

#ifdef EE_RX200_TEI0_ISR
extern void EE_RX200_TEI0_ISR(void);	//The SCI0 TX end int. handler.
#endif

#ifdef EE_RX200_ERI1_ISR
extern void EE_RX200_ERI1_ISR(void);	//The SCI1 Receive Error int. handler.
#endif

#ifdef EE_RX200_RXI1_ISR
extern void EE_RX200_RXI1_ISR(void);	//The SCI1 RX int. handler.
#endif									

#ifdef EE_RX200_TXI1_ISR
extern void EE_RX200_TXI1_ISR(void);	//The SCI1 TX int. handler.
#endif

#ifdef EE_RX200_TEI1_ISR
extern void EE_RX200_TEI1_ISR(void);	//The SCI1 TX empty int. handler.
#endif

#ifdef EE_RX200_ERI5_ISR
extern void EE_RX200_ERI5_ISR(void);	//The SCI5 Receive Error int. handler.
#endif

#ifdef EE_RX200_RXI5_ISR
extern void EE_RX200_RXI5_ISR(void);	//The SCI5 RX int. handler.
#endif									

#ifdef EE_RX200_TXI5_ISR
extern void EE_RX200_TXI5_ISR(void);	//The SCI5 TX int. handler.
#endif

#ifdef EE_RX200_TEI5_ISR
extern void EE_RX200_TEI5_ISR(void);	//The SCI5 TX empty int. handler.
#endif

#ifdef EE_RX200_ERI6_ISR
extern void EE_RX200_ERI6_ISR(void);	//The SCI6 Receive Error int. handler.
#endif

#ifdef EE_RX200_RXI6_ISR
extern void EE_RX200_RXI6_ISR(void);	//The SCI6 RX int. handler.
#endif									

#ifdef EE_RX200_TXI6_ISR
extern void EE_RX200_TXI6_ISR(void);	//The SCI6 TX int. handler.
#endif

#ifdef EE_RX200_TEI6_ISR
extern void EE_RX200_TEI6_ISR(void);	//The SCI6 TX empty int. handler.
#endif

#ifdef EE_RX200_ERI8_ISR
extern void EE_RX200_ERI8_ISR(void);	//The SCI8 Receive Error int. handler.
#endif

#ifdef EE_RX200_RXI8_ISR
extern void EE_RX200_RXI8_ISR(void);	//The SCI8 RX int. handler.
#endif									

#ifdef EE_RX200_TXI8_ISR
extern void EE_RX200_TXI8_ISR(void);	//The SCI8 TX int. handler.
#endif

#ifdef EE_RX200_TEI8_ISR
extern void EE_RX200_TEI8_ISR(void);	//The SCI8 TX empty int. handler.
#endif

#ifdef EE_RX200_ERI9_ISR
extern void EE_RX200_ERI9_ISR(void);	//The SCI9 Receive Error int. handler.
#endif

#ifdef EE_RX200_RXI9_ISR
extern void EE_RX200_RXI9_ISR(void);	//The SCI9 RX int. handler.
#endif									

#ifdef EE_RX200_TXI9_ISR
extern void EE_RX200_TXI9_ISR(void);	//The SCI9 TX int. handler.
#endif

#ifdef EE_RX200_TEI9_ISR
extern void EE_RX200_TEI9_ISR(void);	//The SCI9 TX empty int. handler.
#endif

#ifdef EE_RX200_ERI12_ISR
extern void EE_RX200_ERI12_ISR(void);	//The SCI12 Receive Error int. handler.
#endif

#ifdef EE_RX200_RXI12_ISR
extern void EE_RX200_RXI12_ISR(void);	//The SCI12 RX int. handler.
#endif									

#ifdef EE_RX200_TXI12_ISR
extern void EE_RX200_TXI12_ISR(void);	//The SCI12 TX int. handler.
#endif

#ifdef EE_RX200_TEI12_ISR
extern void EE_RX200_TEI12_ISR(void);	//The SCI12 TX empty int. handler.
#endif
/* Extended Serial Mode Control Interrupt handlers (SCI12) */
#ifdef EE_RX200_SCIX0_ISR
extern void EE_RX200_SCIX0_ISR(void);	
#endif

#ifdef EE_RX200_SCIX1_ISR
extern void EE_RX200_SCIX1_ISR(void);	
#endif									

#ifdef EE_RX200_SCIX2_ISR
extern void EE_RX200_SCIX2_ISR(void);
#endif

#ifdef EE_RX200_SCIX3_ISR
extern void EE_RX200_SCIX3_ISR(void);
#endif

#ifdef EE_RX200_EEI0_ISR
extern void EE_RX200_EEI0_ISR(void);	//The RIIC0 Event/Error int. handler.
#endif

#ifdef EE_RX200_RXI0_ISR
extern void EE_RX200_RXI0_ISR(void);	//The RIIC0 Receive Data Full int. handler.
#endif									

#ifdef EE_RX200_TXI0_ISR
extern void EE_RX200_TXI0_ISR(void);	//The RIIC0 TX end int. handler.
#endif

#ifdef EE_RX200_TEI0_ISR
extern void EE_RX200_TEI0_ISR(void);	//The RIIC0 TX data empty int. handler.
#endif

//#pragma interrupt cmia0_handler(vect=174)
//extern void cmia0_handler(void);
/*
 * Allocate EE_rx200_vtable into Relocatable Vector Table section.
 */ 
 
#pragma section C C$VECT

void* const EE_rx200_vtable[] =
//void (* const EE_rx200_vtable[])(void) =
{
	0,					// Reserved
	0,					// Reserved
    0,					// Reserved
    0,					// Reserved
	0,					// Reserved
    0,					// Reserved
    0,					// Reserved
    0,					// Reserved
	0,					// Reserved
    0,					// Reserved
    0,					// Reserved
    0,					// Reserved
	0,					// Reserved
    0,					// Reserved
    0,					// Reserved
    0,					// Reserved
#ifdef EE_RX200_BUSERR_ISR
	EE_RX200_BUSERR_ISR,
#else
    EE_rx200_default_ISR,
#endif	
	0,					// Reserved
    0,					// Reserved
    0,					// Reserved
    0,					// Reserved
#ifdef EE_RX200_FIFERR_ISR
	(void *) EE_RX200_FIFERR_ISR,
#else
    EE_rx200_default_ISR,
#endif
	0,					// Reserved
#ifdef EE_RX200_FRDYI_ISR
	(void *) EE_RX200_FRDYI_ISR,	//The FLASH READY handler
#else
    EE_rx200_default_ISR,
#endif
	0,					// Reserved
	0,					// Reserved
	0,					// Reserved
#ifdef EE_RX200_SWINT_ISR
	(void *) EE_RX200_SWINT_ISR, //The Software Interr. handler
#else
    EE_rx200_default_ISR,
#endif	
#ifdef EE_RX200_CMI0_ISR
	(void *) EE_RX200_CMI0_ISR, //The Compare Match 0 handler
#else
    EE_rx200_default_ISR,
#endif
#ifdef EE_RX200_CMI1_ISR
	(void *) EE_RX200_CMI1_ISR, //The Compare Match 1 handler
#else
    EE_rx200_default_ISR,
#endif
#ifdef EE_RX200_CMI2_ISR
	(void *) EE_RX200_CMI2_ISR, //The Compare Match 2 handler
#else
    EE_rx200_default_ISR,
#endif
#ifdef EE_RX200_CMI3_ISR
	(void *) EE_RX200_CMI3_ISR, //The Compare Match 3 handler
#else
    EE_rx200_default_ISR,
#endif
#ifdef EE_RX200_FERRF_ISR
	(void *) EE_RX200_FERRF_ISR, //The Freq. Err. Interr. handler
#else
    EE_rx200_default_ISR,
#endif
#ifdef EE_RX200_MENDF_ISR
	(void *) EE_RX200_MENDF_ISR, //The Measur. End Interr. handler
#else
    EE_rx200_default_ISR,
#endif
#ifdef EE_RX200_OVFF_ISR
	(void *) EE_RX200_OVFF_ISR, //The Overflow Interr. handler
#else
    EE_rx200_default_ISR,
#endif
	0,					// Reserved
	0,					// Reserved
	0,					// Reserved
	0,					// Reserved
	0,					// Reserved
	0,					// Reserved
	0,					// Reserved
	0,					// Reserved
	0,					// Reserved
#ifdef EE_RX200_SPEI0_ISR
	(void *) EE_RX200_SPEI0_ISR, //The SCI Error handler
#else
    EE_rx200_default_ISR,
#endif	
#ifdef EE_RX200_SPRIO_ISR
	(void *) EE_RX200_SPRIO_ISR, //The  SCI RX Interr. handler
#else
    EE_rx200_default_ISR,
#endif
#ifdef EE_RX200_SPTIO_ISR
	(void *) EE_RX200_SPTIO_ISR, //The  SCI RX Interr. handler
#else
    EE_rx200_default_ISR,
#endif
#ifdef EE_RX200_SPIIO_ISR
	(void *) EE_RX200_SPIIO_ISR, //The SCI IO Interr. handler
#else
    EE_rx200_default_ISR,
#endif
	0,					// Reserved
	0,					// Reserved
	0,					// Reserved
	0,					// Reserved
	0,					// Reserved
	0,					// Reserved
	0,					// Reserved
	0,					// Reserved
	0,					// Reserved
#ifdef EE_RX200_DOPCF_ISR
	(void *) EE_RX200_DOPCF_ISR, //The Data oper. circuit Interr. handler
#else
    EE_rx200_default_ISR,
#endif
#ifdef EE_RX200_COMPB0_ISR
(void *) EE_RX200_COMPB0_ISR,	//The Comparator B0 Interr. handler
#else
    EE_rx200_default_ISR,
#endif
#ifdef EE_RX200_COMPB1_ISR
	(void *) EE_RX200_COMPB1_ISR,	//The Comparator B1 Interr. handler
#else
    EE_rx200_default_ISR,
#endif
	0,					// Reserved
	0,					// Reserved
	0,					// Reserved
#ifdef EE_RX200_COUNTUP_ISR
	(void *) EE_RX200_COUNTUP_ISR,	//The RTC Countup Interr. handler
#else
    EE_rx200_default_ISR,
#endif
#ifdef EE_RX200_IRQ0_ISR
	(void *) EE_RX200_IRQ0_ISR,	//The IRQ0 Interr. handler
#else
    EE_rx200_default_ISR,
#endif
#ifdef EE_RX200_IRQ1_ISR
	(void *) EE_RX200_IRQ1_ISR,	//The IRQ1 Interr. handler
#else
    EE_rx200_default_ISR,
#endif
#ifdef EE_RX200_IRQ2_ISR
	(void *) EE_RX200_IRQ2_ISR,	//The IRQ2 Interr. handler
#else
    EE_rx200_default_ISR,
#endif
#ifdef EE_RX200_IRQ3_ISR
	(void *) EE_RX200_IRQ3_ISR,	//The IRQ3 Interr. handler
#else
    EE_rx200_default_ISR,
#endif
#ifdef EE_RX200_IRQ4_ISR
	(void *) EE_RX200_IRQ4_ISR,	//The IRQ4 Interr. handler
#else
    EE_rx200_default_ISR,
#endif
#ifdef EE_RX200_IRQ5_ISR
	(void *) EE_RX200_IRQ5_ISR,	//The IRQ5 Interr. handler
#else
    EE_rx200_default_ISR,
#endif
#ifdef EE_RX200_IRQ6_ISR
	(void *) EE_RX200_IRQ6_ISR,	//The IRQ6 Interr. handler
#else
    EE_rx200_default_ISR,
#endif
#ifdef EE_RX200_IRQ7_ISR
	(void *) EE_RX200_IRQ7_ISR,	//The IRQ7 Interr. handler
#else
    EE_rx200_default_ISR,
#endif
	0,					// Reserved
	0,					// Reserved
	0,					// Reserved
	0,					// Reserved
	0,					// Reserved
	0,					// Reserved
	0,					// Reserved
	0,					// Reserved
	0,					// Reserved
	0,					// Reserved
	0,					// Reserved
	0,					// Reserved
	0,					// Reserved
	0,					// Reserved
	0,					// Reserved
	0,					// Reserved
#ifdef EE_RX200_LVDI1_COMP1_ISR
	(void *) EE_RX200_LVDI1_COMP1_ISR,	//The LVD1/COMPA1. Interr. handler
#else
    EE_rx200_default_ISR,
#endif
#ifdef EE_RX200_LVDI2_COMP2_ISR
	(void *) EE_RX200_LVDI2_COMP2_ISR,	//The LVD2/COMPA2. Interr. handler
#else
    EE_rx200_default_ISR,
#endif
	0,					// Reserved
	0,					// Reserved
#ifdef EE_RX200_ALM_ISR
	(void *) EE_RX200_ALM_ISR,	//The RTC Alarm Interr. handler
#else
    EE_rx200_default_ISR,
#endif
#ifdef EE_RX200_PRD_ISR
	(void *) EE_RX200_PRD_ISR,	//The RTC Periodic Interr. handler
#else
    EE_rx200_default_ISR,
#endif
	0,					// Reserved
	0,					// Reserved	
	0,					// Reserved
	0,					// Reserved
	0,					// Reserved
	0,					// Reserved
	0,					// Reserved
	0,					// Reserved
#ifdef EE_RX200_S12ADI0_ISR
	(void *) EE_RX200_S12ADI0_ISR,	//The 12-bit ADC scan end int. handler
#else
    EE_rx200_default_ISR,
#endif
#ifdef EE_RX200_GBADI_ISR
	(void *) EE_RX200_GBADI_ISR,	//The 12-bit ADC group B scan end int. handler
#else
    EE_rx200_default_ISR,
#endif								
	0,					// Reserved
	0,					// Reserved
#ifdef EE_RX200_ELSR18I_ISR
	(void *) EE_RX200_ELSR18I_ISR,	//Event link SR18 int. handler
#else
    EE_rx200_default_ISR,
#endif
#ifdef EE_RX200_ELSR19I_ISR
	(void *) EE_RX200_ELSR19I_ISR,	//Event link SR19 int. handler
#else
    EE_rx200_default_ISR,
#endif
	0,					// Reserved
	0,					// Reserved
	0,					// Reserved
	0,					// Reserved
	0,					// Reserved
	0,					// Reserved
#ifdef EE_RX200_TGIA0_ISR
	(void *) EE_RX200_TGIA0_ISR,	//The MTU0.TGRA  input capture/comp match
#else
    EE_rx200_default_ISR,
#endif									
#ifdef EE_RX200_TGIB0_ISR
	(void *) EE_RX200_TGIB0_ISR,	//The MTU0.TGRB input capture/comp match
#else
    EE_rx200_default_ISR,
#endif									
#ifdef EE_RX200_TGIC0_ISR
	(void *) EE_RX200_TGIC0_ISR,	//The MTU0.TGRC input capture/comp match
#else
    EE_rx200_default_ISR,
#endif
#ifdef EE_RX200_TGID0_ISR
	(void *) EE_RX200_TGID0_ISR,	//The MTU0.TGRD input capture/comp match
#else
    EE_rx200_default_ISR,
#endif
#ifdef EE_RX200_TCIV0_ISR
	(void *) EE_RX200_TCIV0_ISR,	//The MTU0.TCNT overflow int. handler
#else
    EE_rx200_default_ISR,
#endif									
#ifdef EE_RX200_TGIE0_ISR
	(void *) EE_RX200_TGIE0_ISR,	//MTU0.TGRE compare match int. handler
#else
    EE_rx200_default_ISR,
#endif
#ifdef EE_RX200_TGIF0_ISR
	(void *) EE_RX200_TGIF0_ISR,	//MTU0.TGRF compare match int. handler
#else
    EE_rx200_default_ISR,
#endif	
#ifdef EE_RX200_TGIA1_ISR
	(void *) EE_RX200_TGIA1_ISR,	//The MTU1.TGRA  input capture/comp match
#else
    EE_rx200_default_ISR,
#endif									
#ifdef EE_RX200_TGIB1_ISR
	(void *) EE_RX200_TGIB1_ISR,	//The MTU1.TGRB input capture/comp match
#else
    EE_rx200_default_ISR,
#endif
#ifdef EE_RX200_TCIV1_ISR
	(void *) EE_RX200_TCIV1_ISR,	//The MTU1.TCNT overflow int. handler
#else
    EE_rx200_default_ISR,
#endif
#ifdef EE_RX200_TCIU1_ISR
	(void *) EE_RX200_TCIU1_ISR,	//The MTU1.TCNT undeflow int. handler
#else
    EE_rx200_default_ISR,
#endif
#ifdef EE_RX200_TGIA2_ISR
	(void *) EE_RX200_TGIA2_ISR,	//The MTU2.TGRA  input capture/comp match
#else
    EE_rx200_default_ISR,
#endif									
#ifdef EE_RX200_TGIB2_ISR
	(void *) EE_RX200_TGIB2_ISR,	//The MTU2.TGRB input capture/comp match
#else
    EE_rx200_default_ISR,
#endif
#ifdef EE_RX200_TCIV2_ISR
	(void *) EE_RX200_TCIV2_ISR,	//The MTU2.TCNT overflow int. handler
#else
    EE_rx200_default_ISR,
#endif
#ifdef EE_RX200_TCIU2_ISR
	(void *) EE_RX200_TCIU2_ISR,	//The MTU2.TCNT undeflow int. handler
#else
    EE_rx200_default_ISR,
#endif
#ifdef EE_RX200_TGIA3_ISR
	(void *) EE_RX200_TGIA3_ISR,	//The MTU3.TGRA  input capture/comp match
#else
    EE_rx200_default_ISR,	
#endif					
#ifdef EE_RX200_TGIB3_ISR
	(void *) EE_RX200_TGIB3_ISR,	//The MTU3.TGRB input capture/comp match
#else
    EE_rx200_default_ISR,	
#endif										
#ifdef EE_RX200_TGIC3_ISR
	(void *) EE_RX200_TGIC3_ISR,	//The MTU3.TGRC input capture/comp match
#else
    EE_rx200_default_ISR,	
#endif									
#ifdef EE_RX200_TGID3_ISR
	(void *) EE_RX200_TGID3_ISR,	//The MTU3.TGRD input capture/comp match
#else
    EE_rx200_default_ISR,	
#endif	
#ifdef EE_RX200_TCIV3_ISR
	(void *) EE_RX200_TCIV3_ISR,	//The MTU3.TCNT overflow int. handler
#else
    EE_rx200_default_ISR,	
#endif									
#ifdef EE_RX200_TGIA4_ISR
	(void *) EE_RX200_TGIA4_ISR,	//The MTU4.TGRA  input capture/comp match
#else
    EE_rx200_default_ISR,	
#endif
#ifdef EE_RX200_TGIB4_ISR
	(void *) EE_RX200_TGIB4_ISR,	//The MTU4.TGRB input capture/comp match
#else
    EE_rx200_default_ISR,	
#endif
#ifdef EE_RX200_TGIC4_ISR
	(void *) EE_RX200_TGIC4_ISR,	//The MTU4.TGRC input capture/comp match
#else
    EE_rx200_default_ISR,	
#endif
#ifdef EE_RX200_TGID4_ISR
	(void *) EE_RX200_TGID4_ISR,	//The MTU4.TGRD input capture/comp match
#else
    EE_rx200_default_ISR,	
#endif
#ifdef EE_RX200_TCIV4_ISR
	(void *) EE_RX200_TCIV4_ISR,	//The MTU4.TCNT overflow int. handler
#else
    EE_rx200_default_ISR,	
#endif
#ifdef EE_RX200_TGIU5_ISR
	(void *) EE_RX200_TGIU5_ISR,	//The MTU5.TGRU input capture/comp 
#else
    EE_rx200_default_ISR,	
#endif
#ifdef EE_RX200_TGIV5_ISR
	(void *) EE_RX200_TGIV5_ISR,	//The MTU5.TGRV input capture/comp 
#else
    EE_rx200_default_ISR,	
#endif	
#ifdef EE_RX200_TCIW5_ISR
	(void *) EE_RX200_TCIW5_ISR,	//The MTU5.TGRW input capture/comp 
#else
    EE_rx200_default_ISR,	
#endif
	0,					// Reserved
	0,					// Reserved
	0,					// Reserved
	0,					// Reserved
	0,					// Reserved
	0,					// Reserved
	0,					// Reserved
	0,					// Reserved
	0,					// Reserved
	0,					// Reserved
	0,					// Reserved
	0,					// Reserved
	0,					// Reserved
	0,					// Reserved
	0,					// Reserved
	0,					// Reserved
	0,					// Reserved
	0,					// Reserved
	0,					// Reserved
	0,					// Reserved
	0,					// Reserved
	0,					// Reserved
	0,					// Reserved
	0,					// Reserved
	0,					// Reserved
	0,					// Reserved
	0,					// Reserved
	0,					// Reserved
#ifdef EE_RX200_OEI1_ISR
	(void *) EE_RX200_OEI1_ISR,	//The Port Output 1 (POE1) int. handler.
#else
    EE_rx200_default_ISR,	
#endif
#ifdef EE_RX200_OEI2_ISR
	(void *) EE_RX200_OEI2_ISR,	//The Port Output 2 (POE2) int. handler.
#else
    EE_rx200_default_ISR,	
#endif
	0,					// Reserved
	0,				// Reserved
#ifdef EE_RX200_CMIA0_ISR
	(void*) EE_RX200_CMIA0_ISR,	//The TMR0 compare match A int. handler.
#else
    EE_rx200_default_ISR,	
#endif									
#ifdef EE_RX200_CMIB0_ISR
	(void *) EE_RX200_CMIB0_ISR,	//The TMR0 compare match B int. handler.
#else
    EE_rx200_default_ISR,	
#endif
#ifdef EE_RX200_OVI0_ISR
	(void *) EE_RX200_OVI0_ISR,	//The TMR0 TCNT overflow int. handler.
#else
    EE_rx200_default_ISR,	
#endif
#ifdef EE_RX200_CMIA1_ISR
	(void *) EE_RX200_CMIA1_ISR,	//The TMR1 compare match A int. handler.
#else
    EE_rx200_default_ISR,	
#endif									
#ifdef EE_RX200_CMIB1_ISR
	(void *) EE_RX200_CMIB1_ISR,	//The TMR1 compare match B int. handler.
#else
    EE_rx200_default_ISR,	
#endif
#ifdef EE_RX200_OVI1_ISR
	(void *) EE_RX200_OVI1_ISR,	//The TMR1 TCNT overflow int. handler.
#else
    EE_rx200_default_ISR,	
#endif
#ifdef EE_RX200_CMIA2_ISR
	(void *) EE_RX200_CMIA2_ISR,	//The TMR2 compare match A int. handler.
#else
    EE_rx200_default_ISR,	
#endif								
#ifdef EE_RX200_CMIB2_ISR
	(void *) EE_RX200_CMIB2_ISR,	//The TMR2 compare match B int. handler.
#else
    EE_rx200_default_ISR,	
#endif
#ifdef EE_RX200_OVI2_ISR
	(void *) EE_RX200_OVI2_ISR,	//The TMR2 TCNT overflow int. handler.
#else
    EE_rx200_default_ISR,	
#endif
#ifdef EE_RX200_CMIA3_ISR
	(void *) EE_RX200_CMIA3_ISR,	//The TMR3 compare match A int. handler.
#else
    EE_rx200_default_ISR,	
#endif									
#ifdef EE_RX200_CMIB3_ISR
	(void *) EE_RX200_CMIB3_ISR,	//The TMR3 compare match B int. handler.
#else
    EE_rx200_default_ISR,	
#endif
#ifdef EE_RX200_OVI3_ISR
	(void *) EE_RX200_OVI3_ISR,	//The TMR3 TCNT overflow int. handler.
#else
    EE_rx200_default_ISR,	
#endif
	0,					// Reserved
	0,					// Reserved
	0,					// Reserved
	0,					// Reserved
	0,					// Reserved
	0,					// Reserved	
	0,					// Reserved
	0,					// Reserved
	0,					// Reserved
	0,					// Reserved
	0,					// Reserved
	0,					// Reserved
#ifdef EE_RX200_DMAC0I_ISR
	(void *) EE_RX200_DMAC0I_ISR,	//The DMAC channel 0 transfer end ISR.
#else
    EE_rx200_default_ISR,	
#endif
#ifdef EE_RX200_DMAC1I_ISR
	(void *) EE_RX200_DMAC1I_ISR,	//The DMAC channel 1 transfer end ISR.
#else
    EE_rx200_default_ISR,	
#endif									
#ifdef EE_RX200_DMAC2I_ISR
	(void *) EE_RX200_DMAC2I_ISR,	//The DMAC channel 2 transfer end ISR.
#else
    EE_rx200_default_ISR,	
#endif
#ifdef EE_RX200_DMAC3I_ISR
	(void *) EE_RX200_DMAC3I_ISR,	//The DMAC channel 3 transfer end ISR.
#else
    EE_rx200_default_ISR,	
#endif
	0,					// Reserved
	0,					// Reserved
	0,					// Reserved
	0,					// Reserved
	0,					// Reserved
	0,					// Reserved	
	0,					// Reserved
	0,					// Reserved
	0,					// Reserved
	0,					// Reserved
	0,					// Reserved
	0,					// Reserved
#ifdef EE_RX200_ERI0_ISR
	(void *) EE_RX200_ERI0_ISR,	//The SCI0 Receive Error int. handler.
#else
    EE_rx200_default_ISR,	
#endif
#ifdef EE_RX200_RXI0_ISR
	(void *) EE_RX200_RXI0_ISR,	//The SCI0 RX int. handler.
#else
    EE_rx200_default_ISR,	
#endif									
#ifdef EE_RX200_TXI0_ISR
	(void *) EE_RX200_TXI0_ISR,	//The SCI0 TX empty int. handler.
#else
    EE_rx200_default_ISR,	
#endif
#ifdef EE_RX200_TEI0_ISR
	(void *) EE_RX200_TEI0_ISR,	//The SCI0 TX end int. handler.
#else
    EE_rx200_default_ISR,	
#endif
#ifdef EE_RX200_ERI1_ISR
	(void *) EE_RX200_ERI1_ISR,	//The SCI1 Receive Error int. handler.
#else
    EE_rx200_default_ISR,	
#endif
#ifdef EE_RX200_RXI1_ISR
	(void *) EE_RX200_RXI1_ISR,	//The SCI1 RX int. handler.
#else
    EE_rx200_default_ISR,	
#endif								
#ifdef EE_RX200_TXI1_ISR
	(void *) EE_RX200_TXI1_ISR,	//The SCI1 TX int. handler.
#else
    EE_rx200_default_ISR,	
#endif
#ifdef EE_RX200_TEI1_ISR
	(void *) EE_RX200_TEI1_ISR,	//The SCI1 TX empty int. handler.
#else
    EE_rx200_default_ISR,	
#endif
#ifdef EE_RX200_ERI5_ISR
	(void *) EE_RX200_ERI5_ISR,	//The SCI5 Receive Error int. handler.
#else
    EE_rx200_default_ISR,	
#endif
#ifdef EE_RX200_RXI5_ISR
	(void *) EE_RX200_RXI5_ISR,	//The SCI5 RX int. handler.
#else
    EE_rx200_default_ISR,	
#endif									
#ifdef EE_RX200_TXI5_ISR
	(void *) EE_RX200_TXI5_ISR,	//The SCI5 TX int. handler.
#else
    EE_rx200_default_ISR,	
#endif
#ifdef EE_RX200_TEI5_ISR
	(void *) EE_RX200_TEI5_ISR,	//The SCI5 TX empty int. handler.
#else
    EE_rx200_default_ISR,	
#endif
#ifdef EE_RX200_ERI6_ISR
	(void *) EE_RX200_ERI6_ISR,	//The SCI6 Receive Error int. handler.
#else
    EE_rx200_default_ISR,	
#endif
#ifdef EE_RX200_RXI6_ISR
	(void *) EE_RX200_RXI6_ISR,	//The SCI6 RX int. handler.
#else
    EE_rx200_default_ISR,	
#endif									
#ifdef EE_RX200_TXI6_ISR
	(void *) EE_RX200_TXI6_ISR,	//The SCI6 TX int. handler.
#else
    EE_rx200_default_ISR,	
#endif
#ifdef EE_RX200_TEI6_ISR
	(void *) EE_RX200_TEI6_ISR,	//The SCI6 TX empty int. handler.
#else
    EE_rx200_default_ISR,	
#endif
#ifdef EE_RX200_ERI8_ISR
	(void *) EE_RX200_ERI8_ISR,	//The SCI8 Receive Error int. handler.
#else
    EE_rx200_default_ISR,	
#endif
#ifdef EE_RX200_RXI8_ISR
	(void *) EE_RX200_RXI8_ISR,	//The SCI8 RX int. handler.
#else
    EE_rx200_default_ISR,	
#endif									
#ifdef EE_RX200_TXI8_ISR
	(void *) EE_RX200_TXI8_ISR,	//The SCI8 TX int. handler.
#else
    EE_rx200_default_ISR,	
#endif
#ifdef EE_RX200_TEI8_ISR
	(void *) EE_RX200_TEI8_ISR,	//The SCI8 TX empty int. handler.
#else
    EE_rx200_default_ISR,	
#endif
#ifdef  EE_RX200_ERI9_ISR
	(void *) EE_RX200_ERI9_ISR,	//The SCI9 Receive Error int. handler.
#else
    EE_rx200_default_ISR,	
#endif
#ifdef EE_RX200_RXI9_ISR
	 (void *) EE_RX200_RXI9_ISR,	//The SCI9 RX int. handler.
#else
    EE_rx200_default_ISR,	
#endif								
#ifdef EE_RX200_TXI9_ISR
	(void *) EE_RX200_TXI9_ISR,	//The SCI9 TX int. handler.
#else
    EE_rx200_default_ISR,	
#endif
#ifdef EE_RX200_TEI9_ISR
	(void *) EE_RX200_TEI9_ISR,	//The SCI9 TX empty int. handler.
#else
    EE_rx200_default_ISR,	
#endif
#ifdef EE_RX200_ERI12_ISR
	(void *) EE_RX200_ERI12_ISR,	//The SCI12 Receive Error int. handler.
#else
    EE_rx200_default_ISR,	
#endif
#ifdef EE_RX200_RXI12_ISR
	(void *) EE_RX200_RXI12_ISR,	//The SCI12 RX int. handler.
#else
    EE_rx200_default_ISR,	
#endif								
#ifdef EE_RX200_TXI12_ISR
	(void *) EE_RX200_TXI12_ISR,	//The SCI12 TX int. handler.
#else
    EE_rx200_default_ISR,	
#endif
#ifdef EE_RX200_TEI12_ISR
	(void *) EE_RX200_TEI12_ISR,	//The SCI12 TX empty int. handler.
#else
    EE_rx200_default_ISR,	
#endif
// Extended Serial Mode Control Interrupt handlers (SCI12)
#ifdef EE_RX200_SCIX0_ISR
	(void *) EE_RX200_SCIX0_ISR,	
#else
    EE_rx200_default_ISR,	
#endif
#ifdef EE_RX200_SCIX1_ISR
	(void *) EE_RX200_SCIX1_ISR,	
#endif									
#ifdef EE_RX200_SCIX2_ISR
	(void *) EE_RX200_SCIX2_ISR,
#else
    EE_rx200_default_ISR,	
#endif
#ifdef EE_RX200_SCIX3_ISR
	(void *) EE_RX200_SCIX3_ISR,
#else
    EE_rx200_default_ISR,	
#endif
#ifdef EE_RX200_EEI0_ISR
	(void *) EE_RX200_EEI0_ISR,	//The RIIC0 Event/Error int. handler.
#else
    EE_rx200_default_ISR,	
#endif
#ifdef EE_RX200_RXI0_ISR
	(void *) EE_RX200_RXI0_ISR,	//The RIIC0 Receive Data Full int. handler.
#else
    EE_rx200_default_ISR,	
#endif									
#ifdef EE_RX200_TXI0_ISR
	(void *) EE_RX200_TXI0_ISR,	//The RIIC0 TX end int. handler.
#else
    EE_rx200_default_ISR,	
#endif
#ifdef EE_RX200_TEI0_ISR
	(void *) EE_RX200_TEI0_ISR,	//The RIIC0 TX data empty int. handler.
#else
    EE_rx200_default_ISR,	
#endif
	0,					// Reserved
	0,					// Reserved
	0,					// Reserved
	0,					// Reserved
	0,					// Reserved
	0					// Reserved
};

