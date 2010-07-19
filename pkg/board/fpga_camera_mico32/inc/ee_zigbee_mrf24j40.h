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

#define EE_MRF24J40_GPIO_NAME_UC	MISC_GPIO
#define EE_MRF24J40_GPIO_NAME_LC	misc_gpio
#define EE_MRF24J40_BASE_ADDRESS	MISC_GPIO_BASE_ADDRESS
#define EE_MRF24J40_IRQ				MISC_GPIO_IRQ

// 	XP2 CAMERA BOARD:
//  LOCATE COMP "misc_gpioPIO_IO_0" SITE "75" ;     -> INT1 	(fpga input)
//  LOCATE COMP "misc_gpioPIO_IO_1" SITE "77" ;     -> INT2 	(fpga input)
//  LOCATE COMP "misc_gpioPIO_IO_2" SITE "82" ;     -> FIFOP 	(fpga input)
//  LOCATE COMP "misc_gpioPIO_IO_3" SITE "76" ;     -> CN1 		(fpga input)
//  LOCATE COMP "misc_gpioPIO_IO_0" SITE "75" ;     -> ~INT1  	(fpga input)
//  LOCATE COMP "misc_gpioPIO_IO_1" SITE "77" ;     -> ~INT2	(fpga input)
//  LOCATE COMP "misc_gpioPIO_IO_4" SITE "122";     -> DL3 		(fpga output)
//  LOCATE COMP "misc_gpioPIO_IO_5" SITE "86" ;     -> GP1 		(fpga output)
//  LOCATE COMP "misc_gpioPIO_IO_6" SITE "84" ;     -> CCA 		(fpga output)

#define EE_INT1_BIT 			(0) 
#define EE_INT2_BIT 			(1)
#define EE_FIFOP_BIT 			(2) 
#define EE_CN1_BIT 				(3)
#define EE_NOT_INT1_BIT 		(4)
#define EE_NOT_INT2_BIT			(5)
#define EE_DL3_BIT 				(0) 
#define EE_GP1_BIT 				(1)
#define EE_CCA_BIT 				(2) 

#define EE_INT1_MASK 			(0x0001) 
#define EE_INT2_MASK 			(0x0002)
#define EE_FIFOP_MASK 			(0x0004)
#define EE_CN1_MASK				(0x0008)
#define EE_NOT_INT1_MASK 		(0x0010) 
#define EE_NOT_INT2_MASK 		(0x0020)
#define EE_DL3_MASK				(0x0001) 
#define EE_GP1_MASK				(0x0002) 
#define EE_CCA_MASK				(0x0004)

#ifdef INT_POLARITY_HIGH
#define EE_INTPIN_MASK 			EE_INT2_MASK
#define EE_INTPIN_BIT 			EE_INT2_BIT
#else
#define EE_INTPIN_MASK 			EE_NOT_INT2_MASK
#define EE_INTPIN_BIT 			EE_NOT_INT2_BIT
#endif 

#define EE_MRF24J40_BOARD_FUNCTION(uc,lc) \
__INLINE__ void __ALWAYS_INLINE__ EE_mrf24j40_gpio_IRQ_pre_stub(void){ \
	return; \
} \
__INLINE__ void __ALWAYS_INLINE__ EE_mrf24j40_gpio_IRQ_post_stub(void){ \
	while(1){ \
		if( (EE_misc_gpio_read_data() & EE_INTPIN_MASK) == 0 ) \
		break; \
	} \
} \
__INLINE__ void __ALWAYS_INLINE__ EE_mrf24j40_gpio_hold_in_reset(void){ \
	cat3(EE_, lc, _write_bit_data)(0, EE_GP1_BIT); \
} \
__INLINE__ void __ALWAYS_INLINE__ EE_mrf24j40_gpio_release_reset(void){ \
	cat3(EE_, lc, _write_bit_data)(1, EE_GP1_BIT); \
} \
__INLINE__ void __ALWAYS_INLINE__ EE_mrf24j40_gpio_wake_pin(int val){ \
	cat3(EE_, lc, _write_bit_data)(val, EE_INT1_BIT); \
} \
__INLINE__ void __ALWAYS_INLINE__ EE_mrf24j40_gpio_write_output_pins(int val){ \
	cat3(EE_, lc, _write_data)(val); \
} \
__INLINE__ void __ALWAYS_INLINE__ EE_mrf24j40_gpio_enable_IRQ(void){ \
	cat3(EE_, lc, _write_bit_irqMask)(1, EE_INTPIN_BIT); \
} \
__INLINE__ void __ALWAYS_INLINE__ EE_mrf24j40_gpio_disable_IRQ(void){ \
	cat3(EE_, lc, _write_bit_irqMask)(0, EE_INT2_BIT); \
	cat3(EE_, lc, _write_bit_irqMask)(0, EE_NOT_INT2_BIT); \
} \
__INLINE__ int __ALWAYS_INLINE__ EE_mrf24j40_gpio_IRQ_enabled(void){ \
	return (cat3(EE_, lc, _read_irqMask)() & EE_INTPIN_MASK); \
}

EE_MRF24J40_BOARD_FUNCTION(EE_MRF24J40_GPIO_NAME_UC, EE_MRF24J40_GPIO_NAME_LC)

__INLINE__ void __ALWAYS_INLINE__ EE_mrf24j40_gpio_wake_active(void){
	EE_mrf24j40_gpio_wake_pin(1);
}

__INLINE__ void __ALWAYS_INLINE__ EE_mrf24j40_gpio_wake_inactive(void){
	EE_mrf24j40_gpio_wake_pin(0);
}

#endif //__EE_ZIGBEE_MRF24J40_H__
