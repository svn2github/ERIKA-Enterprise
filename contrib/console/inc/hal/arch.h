#ifndef __arch_h__
#define __arch_h__
/** 
* @file arch.h
* @brief Architecture definitions.
* @author Marinoni Mauro, Nastasi Christian
* @date 2008-11-03
*/

#ifdef __HCS12XS__
#ifdef __MC9S12XS128__
#include "hal/s12.h"
#endif	/* __MC9S12XS128__ */
#endif	/* __HCS12XS__ */

#ifdef __PIC30__
#include "hal/pic30.h"
#endif	/* __PIC30__ */

#ifdef __AVR5__
#include "hal/avr5.h"
#endif	/* __PIC30__ */

#endif	/* __arch_h__ */
