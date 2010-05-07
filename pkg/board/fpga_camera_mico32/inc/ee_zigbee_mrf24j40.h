/*
  Name: ee_zigbee_mrf24j40.h 
  Copyright: Evidence Srl
  Author: Dario Di Stefano
  Date: 29/03/10 18.28
  Description: zigbee library header file (MICO32 CAMERA board dependent). 
*/

#ifndef __EE_ZIGBEE_MRF24J40_H__
#define __EE_ZIGBEE_MRF24J40_H__

/* Board-dependent macros */
#define EE_INT1_BIT 	(0) // mask: (0x01) (fpga output)
#define EE_INT2_BIT 	(1) // mask: (0x02) (fpga input)
#define EE_FIFOP_BIT 	(2) // mask: (0x04) (fpga input)
#define EE_CN1_BIT 		(3) // mask: (0x08) (fpga input)
#define EE_DL3_BIT 		(4) // mask: (0x10) (fpga output)
#define EE_GP1_BIT 		(5) // mask: (0x20) (fpga output)
#define EE_CCA_BIT 		(6) // mask: (0x40) (fpga output)
#define EE_INT1_MASK 	(0x01)
#define EE_INT2_MASK 	(0x02)
#define EE_FIFOP_MASK 	(0x04)
#define EE_CN1_MASK		(0x08)
#define EE_DL3_MASK		(0x10)
#define EE_GP1_MASK		(0x20)
#define EE_CCA_MASK		(0x40)
#define EE_MRF24J40_OUTPUT_MASK (0x71)
#define EE_mrf24j40_hold_in_reset()	EE_misc_gpio_write_bit_data(0, EE_GP1_BIT)
#define EE_mrf24j40_release_reset()	EE_misc_gpio_write_bit_data(1, EE_GP1_BIT)
#define EE_mrf24j40_wake_pin(val)	EE_misc_gpio_write_bit_data((val), EE_INT1_BIT)
#define EE_mrf24j40_output_pins_select(val) EE_misc_gpio_write_tristate(val);
#define EE_mrf24j40_write_output_pins(val) EE_misc_gpio_write_data(val);
#define EE_mrf24j40_int_enable()	EE_misc_gpio_write_bit_irqMask(1, EE_INT2_BIT)
#define EE_mrf24j40_int_disable()	EE_misc_gpio_write_bit_irqMask(0, EE_INT2_BIT)

// extern int ee_mrf24j40_dummy_flag;
// #define MRF24J40_INTERRUPT_FLAG		ee_mrf24j40_dummy_flag
#define MRF24J40_WAKE_ACTIVE()		EE_mrf24j40_wake_pin(1)
#define MRF24J40_WAKE_INACTIVE()	EE_mrf24j40_wake_pin(0) 
#define EE_MRF24J40_BASE_ADDRESS	MISC_GPIO_BASE_ADDRESS
#define EE_MRF24J40_IRQ				MISC_GPIO_IRQ

#define EE_MRF24J40_BOARD_IRQ_PRE_STUB()
#define EE_MRF24J40_BOARD_IRQ_POST_STUB() \
while(1){ \
	if( (EE_misc_gpio_read_data() & EE_INT2_MASK) == 0 ) \
	break; \
}

#endif //__EE_ZIGBEE_MRF24J40_H__
