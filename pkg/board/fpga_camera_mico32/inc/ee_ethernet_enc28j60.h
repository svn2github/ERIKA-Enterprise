/*
  Name: ee_ethernet_enc28j60.h 
  Copyright: Evidence Srl
  Author: Dario Di Stefano
  Date: 29/03/10 18.28
  Description: ethernet library header file (MICO32 CAMERA board dependent). 
*/

#ifndef __EE_ETHERNET_ENC28J60_H__
#define __EE_ETHERNET_ENC28J60_H__

/* Board-dependent macros */

#define EE_ETHERNET_SPI_NAME_UC 	NET_SPI
#define EE_ETHERNET_SPI_NAME_LC 	net_spi
#define EE_ENC28J60_GPIO_NAME_UC	MISC_GPIO
#define EE_ENC28J60_GPIO_NAME_LC	misc_gpio
#define EE_ENC28J60_BASE_ADDRESS	MISC_GPIO_BASE_ADDRESS
#define EE_ENC28J60_IRQ				MISC_GPIO_IRQ

// 	XP2 CAMERA BOARD:
//  LOCATE COMP "misc_gpioPIO_IO_1" SITE "77" ;     -> INT2 	(fpga input)
//  LOCATE COMP "misc_gpioPIO_IO_2" SITE "82" ;     -> FIFOP 	(fpga input)
//  LOCATE COMP "misc_gpioPIO_IO_3" SITE "76" ;     -> CN1 		(fpga input)
//  LOCATE COMP "misc_gpioPIO_IO_4" SITE "122";     -> DL3 		(fpga output)
//  LOCATE COMP "misc_gpioPIO_IO_5" SITE "86" ;     -> GP1 		(fpga output)
//  LOCATE COMP "misc_gpioPIO_IO_6" SITE "84" ;     -> CCA 		(fpga output)
//  LOCATE COMP "misc_gpioPIO_IO_0" SITE "75" ;     -> INT1 	(fpga output)

#define EE_INT2_BIT 			(0) // mask: (0x01) (fpga input)
#define EE_FIFOP_BIT 			(1) // mask: (0x02) (fpga input)
#define EE_CN1_BIT 				(2) // mask: (0x04) (fpga input)
#define EE_DL3_BIT 				(0) //(3) // mask: (0x08) (fpga output)
#define EE_GP1_BIT 				(1) //(4) // mask: (0x10) (fpga output)
#define EE_CCA_BIT 				(2) //(5) // mask: (0x20) (fpga output)
#define EE_INT1_BIT 			(3) //(6) // mask: (0x40) (fpga output)
#define EE_INT2_MASK 			(0x01)
#define EE_FIFOP_MASK 			(0x02)
#define EE_CN1_MASK				(0x04)
#define EE_DL3_MASK				(0x01) //(0x08)
#define EE_GP1_MASK				(0x02) //(0x10)
#define EE_CCA_MASK				(0x04) //(0x20)
#define EE_INT1_MASK 			(0x08) //(0x40)

#define EE_ENC28J60_BOARD_FUNCTION(uc,lc) \
__INLINE__ void __ALWAYS_INLINE__ EE_enc28j60_gpio_IRQ_pre_stub(void){ \
	return; \
} \
__INLINE__ void __ALWAYS_INLINE__ EE_enc28j60_gpio_IRQ_post_stub(void){ \
	while(1){ \
		if( (EE_misc_gpio_read_data() & EE_INT2_MASK) == 0 ) \
		break; \
	} \
} \
__INLINE__ void __ALWAYS_INLINE__ EE_enc28j60_gpio_hold_in_reset(void){ \
	cat3(EE_, lc, _write_bit_data)(0, EE_GP1_BIT); \
} \
__INLINE__ void __ALWAYS_INLINE__ EE_enc28j60_gpio_release_reset(void){ \
	cat3(EE_, lc, _write_bit_data)(1, EE_GP1_BIT); \
} \
__INLINE__ void __ALWAYS_INLINE__ EE_enc28j60_gpio_wake_pin(int val){ \
	cat3(EE_, lc, _write_bit_data)(val, EE_INT1_BIT); \
} \
__INLINE__ void __ALWAYS_INLINE__ EE_enc28j60_gpio_write_output_pins(int val){ \
	cat3(EE_, lc, _write_data)(val); \
} \
__INLINE__ void __ALWAYS_INLINE__ EE_enc28j60_gpio_enable_IRQ(void){ \
	cat3(EE_, lc, _write_bit_irqMask)(1, EE_INT2_BIT); \
} \
__INLINE__ void __ALWAYS_INLINE__ EE_enc28j60_gpio_disable_IRQ(void){ \
	cat3(EE_, lc, _write_bit_irqMask)(0, EE_INT2_BIT); \
} \
__INLINE__ int __ALWAYS_INLINE__ EE_enc28j60_gpio_IRQ_enabled(void){ \
	return (cat3(EE_, lc, _read_irqMask)() & EE_INT2_MASK); \
}

EE_ENC28J60_BOARD_FUNCTION(EE_ENC28J60_GPIO_NAME_UC, EE_ENC28J60_GPIO_NAME_LC)

//#define EE_enc28j60_int_enable()			EE_misc_gpio_write_bit_irqMask(1, EE_INT2_BIT)
//#define EE_enc28j60_int_disable()			EE_misc_gpio_write_bit_irqMask(0, EE_INT2_BIT)
__INLINE__ void __ALWAYS_INLINE__ EE_enc28j60_gpio_wake_active(void){
	EE_enc28j60_gpio_wake_pin(1);
}

__INLINE__ void __ALWAYS_INLINE__ EE_enc28j60_gpio_wake_inactive(void){
	EE_enc28j60_gpio_wake_pin(0);
}

#endif //__EE_ETHERNET_ENC28J60_H__
