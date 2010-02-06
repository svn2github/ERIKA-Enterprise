#ifndef __INCLUDE_EE_BOARD_H__
#define __INCLUDE_EE_BOARD_H__

#include "mcu/microchip_pic32/inc/ee_mcu.h"

#ifndef IPERMOB_MB_PIC32_VERSION
#define IPERMOB_MB_PIC32_VERSION 0
#endif

#if IPERMOB_MB_PIC32_VERSION == 0

#ifdef __USE_LEDS__
__INLINE__ void __ALWAYS_INLINE__ EE_leds_init(void) 
{
	TRISECLR = 0x0F;
	LATECLR = 0X0F;
}

#define EE_led_0_on	(LATESET = 0x01)
#define EE_led_1_on	(LATESET = 0x02)
#define EE_led_2_on	(LATESET = 0x04)
#define EE_led_3_on	(LATESET = 0x08)
#define EE_led_on(n)	EE_led_##n##_on

#define EE_led_0_off	(LATECLR = 0x01)
#define EE_led_1_off	(LATECLR = 0x02)
#define EE_led_2_off	(LATECLR = 0x04)
#define EE_led_3_off	(LATECLR = 0x08)
#define EE_led_off(n)	EE_led_##n##_off

#define EE_led_0_toggle		(LATEINV = 0x01)
#define EE_led_1_toggle		(LATEINV = 0x02)
#define EE_led_2_toggle		(LATEINV = 0x04)
#define EE_led_3_toggle		(LATEINV = 0x08)
#define EE_led_toggle(n)	EE_led_##n##_toggle

#endif	/* __USE_LEDS__ */

#else 
#error "IPERMOB_MB_PIC32: Invalid board version."
#endif	/* IPERMOB_MB_PIC32_VERSION version selection */


#endif /* __INCLUDE_EE_BOARD_H__ */
