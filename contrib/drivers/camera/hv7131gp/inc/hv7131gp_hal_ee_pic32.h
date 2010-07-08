/*
Copyright (C) 2009 -  Claudio Salvadori and Christian Nastasi
This program is free software; you can redistribute it and/or
modify it under the terms of the GNU General Public License
as published by the Free Software Foundation; either version 2
of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.
*/

/*
 * hv7131gp_hal_ee_pic32.c
 *
 */

#ifndef HV7131GP_HAL_EE_PIC32_H_
#define HV7131GP_HAL_EE_PIC32_H_

#include "hv7131gp_types.h"
#include "hv7131gp_reg.h"
#include "mcu/microchip_pic32/inc/ee_cn.h"

/******************************************************************************/
/*                         Functions Prototypes                               */
/******************************************************************************/




hv7131gp_status_t hv7131gp_hal_init(uint8_t DMA_CH);

void hv7131gp_oc_hal_init(uint16_t period);
void hv7131gp_oc_hal_start(void);
void hv7131gp_oc_hal_stop(void);

COMPILER_INLINE void hv7131gp_hal_delay_us(uint32_t delay_count)
{
	EE_delay_us(delay_count);
}

hv7131gp_status_t hv7131gp_i2c_hal_init(void);
hv7131gp_status_t hv7131gp_i2c_hal_reg_write(hv7131gp_reg_t reg, uint8_t  val);
hv7131gp_status_t hv7131gp_i2c_hal_reg_read(hv7131gp_reg_t reg, uint8_t *val);
hv7131gp_status_t hv7131gp_dma_hal_init(uint8_t dma_ch);
hv7131gp_status_t hv7131gp_hal_capture(uint8_t *image, hv7131gp_cback_t *func);


/******************************************************************************/
/*                           Hardware Abstraction Layer                       */
/******************************************************************************/

#define HV7131GP_HAL_DRIVING_PINS           1

#define	HV7131GP_MORE_THAN_1_MS			1500
#define	HV7131GP_MORE_THAN_4_MCLK_CYCLES	1 	
#define	HV7131GP_MORE_THAN_2086000_MCLK_CYCLES	300000

//Main clock speed

#define SYSTEM_INSTRUCTION_CLOCK 80000000ul
#define	HV7131GP_MCLK_PERIOD	0x02

#ifdef __32MX360F512L__
#define HV7131GP_MAX_SIZE	19200	/**< For PIC32MX */
#endif

#ifdef __USE_DMA__
#ifndef DMA_MAX_WIDTH
#define DMA_MAX_WIDTH		160
#endif // DMA_MAX_WIDTH
#endif //__USE_DMA__



/**
* @name Enable pin
* \brief Settings for D2 pin used like camera enable pin (see HV7131GP documentation)
*/
#define HV7131GP_PIN_ENABLE_INIT() 	TRISDbits.TRISD2=0	/* Init enable pin */
#define HV7131GP_PIN_ENABLE_HIGH() 	LATDbits.LATD2=1	/* Set pin to high value*/
#define HV7131GP_PIN_ENABLE_LOW() 	LATDbits.LATD2=0	/* Set pin to low value*/
/**  @} */

/**
* @name Reset pin
* \brief Settings for D1 pin used like camera reset pin (see HV7131GP documentation)
*/
#define HV7131GP_PIN_RESETB_INIT() 	TRISDbits.TRISD1=0	/* Init reset pin */
#define HV7131GP_PIN_RESETB_HIGH() 	LATDbits.LATD1=1	/* Set pin to high value*/
#define HV7131GP_PIN_RESETB_LOW() 	LATDbits.LATD1=0	/* Set pin to low value*/
/**  @} */



/**
* @name Vertical Sync
*
* INT3. Functions to set, reset, start, stop the vertical sync interrupt
*
* @{ */
#define HV7131GP_PIN_VSYNC_INIT_POSITIVE()					\
do { 										\
	INTCONbits.INT3EP = 1;	/*  Extern Interrupt on positive edge */	\
	IPC3bits.INT3IP  = 6;	/*  Set INT3 interrupt priority */		\
} while (0)									\

#define HV7131GP_PIN_VSYNC_INIT_NEGATIVE()					\
do { 										\
	INTCONbits.INT3EP = 0;	/*  Extern Interrupt on negative edge */	\
	IPC3bits.INT3IP  = 6;	/*  Set INT3 interrupt priority */		\
} while (0)									\

#define HV7131GP_PIN_VSYNC_START()						\
do { 										\
	IEC0bits.INT3IE = 1;	/*  Enable INT3 interrupt */			\
	IFS0bits.INT3IF = 0;	/*  Reset INT3 interrupt flag */	 	\
} while (0)									\

#define HV7131GP_PIN_VSYNC_STOP()						\
do { 										\
	IEC0bits.INT3IE = 0;	/*  Disable INT3 interrupt */			\
	IFS0bits.INT3IF = 0;	/*  Reset INT3 interrupt flag */ 		\
} while (0)									\

#define HV7131GP_VSYNC_RESET_IF()						\
do { 										\
	IFS0bits.INT3IF = 0;	/*  Reset INT3 interrupt flag */	 	\
} while (0)									\

#define HV7131GP_VSYNC_IF_VALUE	IFS0bits.INT3IF /*  Return INT3 interrupt flag value*/


#define HV7131GP_VSYNC_INTERRUPT()  void __attribute__((interrupt(ipl6))) \
    	 __attribute__((vector(_EXTERNAL_3_VECTOR))) isr__EXTERNAL_3_VECTOR(void) \


/**  @} */

/**
* @name Horizontal Sync
*
* CN15 (RD6). Functions to set, reset, start, stop the horizontal sync interrupt
*
* @{ */
#define HV7131GP_PIN_HSYNC_INIT()	EE_cn_init(7, 3)
#define HV7131GP_PIN_HSYNC_START()	EE_cn_enable(hv7131gp_cn15)
#define HV7131GP_PIN_HSYNC_STOP()	EE_cn_disable(hv7131gp_cn15)
#define HV7131GP_HSYNC_RESET_IF() 	
#define HV7131GP_HSYNC_INTERRUPT() 	EE_CN_HANDLER(hv7131gp_cn15) 
#define HV7131GP_HSYNC_VALUE() 		PORTDbits.RD6
/**  @} */

/**
* @name Video (Pixels) Clock
*
* INT4. It's the pixel interrupt: everytime this interrupt occurs a pixel is
* captured.
*
* @{ */
#define HV7131GP_PIN_VCLK_INIT()					\
do { 									\
	INTCONbits.INT4EP = 0;	/* Extern Interrupt on positive edge */	\
	IPC4bits.INT4IP  = 6;	/* Set INT4 interrupt priority */	\
} while (0)							
	
#define HV7131GP_PIN_VCLK_START()				\
do { 								\
	IEC0bits.INT4IE = 1;	/*Enable INT4 interrupt */	\
	IFS0bits.INT4IF = 0;	/* Reset INT4 interrupt flag */	 \
} while (0)							

#define HV7131GP_PIN_VCLK_STOP()				\
do { 								\
	IEC0bits.INT4IE = 0;	/* Disable INT4 interrupt */	\
	IFS0bits.INT4IF = 0;	/* Reset INT4 interrupt flag */	 \
} while (0)							

#define HV7131GP_VCLK_INTERRUPT()  void __attribute__((interrupt(ipl6))) \
  	 __attribute__((vector(_EXTERNAL_4_VECTOR))) isr__EXTERNAL_4_VECTOR(void) 		

#define HV7131GP_VCLK_RESET_IF() IFS0bits.INT4IF = 0
#define HV7131GP_VCLK_IF_VALUE() IFS0bits.INT4IF



/**  @} */

/**
* @name Master Clock
*
* OC1 with Timer3. The output of this pin is the master clock for HV7131GP camera.
* The master clock is the time reference of the camera. It's set a master clock
* with a frequency of 10MHz
*
* @{ */

#define HV7131GP_PIN_MCLK_INIT(p)	hv7131gp_oc_hal_init(p)	/* Init master clock */
#define HV7131GP_PIN_MCLK_START()	hv7131gp_oc_hal_start()	/* Start master clock */
#define HV7131GP_PIN_MCLK_STOP()	hv7131gp_oc_hal_stop()	/* Stop master clock */
/**  @} */

/**
* @name Pixel pins. In this set of 8 pins are received the 8 bits of each pixel.
* The pixel reception is regulated by the pixel clock
* @{ */
#define HV7131GP_PIN_Y_INIT()	TRISESET = 0x00FF 	/* Init PORT_E */
#define HV7131GP_PIN_Y_ADDRESS	(&PORTE)		/* Address PORT_E */
/**  @} */



/**
* @name Software interrupt: end of frame acquisition
*
* PMP ISR. This interrupt is generated when an entire frame is captured. This
* interrupt call inside his ISR the callback function passed on the capture
* function
* \see hv7131gp_capture
*
* @{ */


#define HV7131GP_PIN_EOF_INIT()						\
do { 									\
	IPC7bits.PMPIP  = 5;	/* Set interrupt priority */	\
	IPC7bits.PMPIS  = 0;	/* Set interrupt sub-priority */	\
	IEC1bits.PMPIE = 1;	/* Enable interrupt */		\
	IFS1bits.PMPIF = 0;	/* Reset interrupt flag */	 	\
} while (0)								

#define HV7131GP_PIN_EOF_STOP()						\
do { 									\
	IEC1bits.PMPIE = 0;	/* Disable INT0 interrupt */		\
	IFS1bits.PMPIF = 0;	/* Reset INT0 interrupt flag */	 	\
} while (0)								


#define HV7131GP_EOF_INTERRUPT() ISR2(_PMP_VECTOR)
#define HV7131GP_EOF_RESET_IF() IFS1bits.PMPIF = 0
#define HV7131GP_EOF_ACTIVATE_IF() IFS1bits.PMPIF = 1



/* Functions used by the DMA Controller */

#ifdef __USE_DMA__
#define ADDR_VIRTUAL_TO_PHYSICAL(a) (((EE_UREG)(a)) & 0x1FFFFFFF)
#endif // __USE_DMA__
/**  @} */


#define HV7131GP_HAL_DISABLE_INTERRUPTS() asm volatile("di")
#define HV7131GP_HAL_ENABLE_INTERRUPTS() asm volatile("ei")


/* For compatibilty with other HALs */
#define hv7131gp_hal_init_ack() HV7131GP_SUCCESS

#endif /* HV7131GP_HAL_EE_PIC32_H_ */
