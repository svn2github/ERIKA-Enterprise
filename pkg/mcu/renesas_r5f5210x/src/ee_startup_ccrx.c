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

/*
 * Initialization routines and startup code.
 * Author: 2012 Gianluca Franchino
 */

#include <machine.h>
#include "mcu/renesas_r5f5210x/inc/ee_mcuregs.h"
#include "mcu/renesas_r5f5210x/inc/ee_isr.h"

#ifndef EE_USTACK_SIZE
/* Define the user stack size */
#pragma stacksize su=0x300
#endif

#ifndef EE_ISTACK_SIZE      
/* Define the interrupt stack size */
#pragma stacksize si=0x100      
#endif

/* 
 * Main and _INITSCT prototypes needed by C99 specification. 
 * This avoids a warning at compile time.
 */ 
void main(void);
void _INITSCT(void);

/* Enable interrupt (bit16 PWS register) */ 
#define EE_PSW_INIT_MASK 0x00010000

#pragma section EE_RX200_RES_REG

/*Set EE_rx200_power_on_res() as the entry routine.*/
#pragma entry EE_rx200_power_on_res
/*
 * This is entry function, called just after the power on.
 * EE_rx200_power_on_res() follows the example provided by the
 * Renesas ccrx compiler manual.
 */
void EE_rx200_power_on_res(void)
{
	/*
	* Set base address of interrupt vectore table (INTB) 
	* at the start address of variable vector table section (ROM section).  
	*/
	set_intb(__sectop("C$VECT"));

	/*Initialize RAM are section. Quoting the compiler manual:
	* Uninitialized data sections are initialized to zero. 
	* For initialized data sections, the initial values of 
	* the ROM area are copied to the RAM area."
	*/
	_INITSCT();					
	
	/*
	 *Note: We assume that C/C++ library functions are note used.
	 *To use those library functions, we have to add the initialization
	 *code as suggested by the toolchain manual. 
	 *See RX Family Compiler package manual.
	 * We may enable this code using EEOPT
	 */
	 /*
	 _INITLIB(); //This routine has to be written following the examples 
				 //provided in the manual (pages 218-219).
	 */

    nop();
	
	/*
	*Set PSW register
	*/
	set_psw(EE_PSW_INIT_MASK);
	
	/*
	* Call main function.
	*/
	main();
	
	/*
	* Call a break interrupt.
	*/
	brk();

}
