#ifndef __AMAZING_H__
#define __AMAZING_H__

#ifndef __USE_TOUCH__
#error AMAZING: this functionality requires TOUCH support.
#endif

#ifndef __USE_PWM__
#error AMAZING: this functionality requires PWM support.
#endif

#ifdef CONFIG_AMAZING_UART_DEBUG

#ifdef __USE_UART__
#include "mcu/microchip_dspic/inc/ee_uart.h"
#else
#error CONFIG_AMAZING_UART_DEBUG: this functionality requires UART support.
#endif

#endif

#ifdef CONFIG_AMAZING_UART_DEBUG_TUNING

#ifdef __USE_UART__
#include "mcu/microchip_dspic/inc/ee_uart.h"
#else
#error CONFIG_AMAZING_UART_DEBUG: this functionality requires UART support.
#endif

#endif

void amazing_reset_body(void);
void amazing_tuner_body(EE_UINT16,EE_UINT16);

#define touch_set_dimension(a, b)		touch_1_set_dimension(a, b) 
#define touch_raw_init()				touch_1_raw_init()
#define touch_start()					touch_1_start()
#define touch_wait_raw_position(a, b)	touch_1_wait_raw_position(a, b)
#define touch_tune(a)					touch_1_tune(a)
#define touch_poll_s_position(a, b) 	touch_1_poll_s_position(a, b)

#endif // __AMAZING_H__
