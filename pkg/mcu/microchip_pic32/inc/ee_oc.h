#ifndef __INCLUDE_MICROCHIP_PIC32_OUTPUT_COMPARE_H__
#define __INCLUDE_MICROCHIP_PIC32_OUTPUT_COMPARE_H__

#include "ee.h"

#define EE_OC_NO_ERRORS			1	//Used positive
#define EE_OC_ERR_BAD_TIMER_CONF	1
#define EE_OC_ERR_TIMER_INIT		2
#define EE_OC_ERR_UNIMPLEMENTED		10

#define EE_OC_CONFIGURE_PULSE	0x5
#define EE_OC_CONFIGURE_TOGGLE	0x3
#define EE_OC_PWM_NO_FAULT	0x6

#define EE_OC_TIMER_2		0x0
#define EE_OC_TIMER_3		0x8

#define EE_OC_NO_ADVANCED_SET	0x0

#define EE_OC_TIMER_32_BITS	0x20
#define EE_OC_TIMER_16_BITS	0x00
#define EE_OC_INTERRUPT_MODE	0x1

enum {
	EE_OC_1	= 1,
	EE_OC_2,
	EE_OC_3,
	EE_OC_4,
	EE_OC_5,
	EE_OC_N,
};

EE_INT8 EE_oc_init(EE_UINT8 id);
EE_INT8 EE_oc_setup(EE_UINT8 id, EE_UINT16 configuration, EE_UINT16 period, 
							EE_UINT8 prescale);
EE_INT8 EE_oc_set_callback(EE_UINT8 id, void (*f)(void)); 
EE_INT8 EE_oc_advanced_setup(EE_UINT8 id, EE_UINT32 dreg, EE_UINT32 sdreg, 
							EE_UINT8 mode);
EE_INT8 EE_oc_start(EE_UINT8 id);
EE_INT8 EE_oc_stop(EE_UINT8 id);

#if (defined __USE_OC_CLOCK_GEN__ && defined __32MX795F512L__)
EE_INT8 EE_oc_generate_clock_init(EE_UINT8 id, EE_UINT32 frequency);
EE_INT8 EE_oc_generate_clock_start(EE_UINT8 id);
EE_INT8 EE_oc_generate_clock_stop(EE_UINT8 id);
#endif // (defined __USE_OC_CLOCK_GEN__ && defined __32MX795F512L__)

#endif /* __INCLUDE_MICROCHIP_PIC32_OUTPUT_COMPARE_H__*/
