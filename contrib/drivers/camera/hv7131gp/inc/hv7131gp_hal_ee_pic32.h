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

#include "hv7131gp.h"
#ifndef HV7131GP_HAL_EE_PIC32_H_
#define HV7131GP_HAL_EE_PIC32_H_

/******************************************************************************/
/*                         Functions Prototypes                               */
/******************************************************************************/




hv7131gp_status_t hv7131gp_hal_init(uint8_t DMA_CH);

void hv7131gp_oc_hal_init(uint16_t period);
void hv7131gp_oc_hal_start(void);
void hv7131gp_oc_hal_stop(void);

void hv7131gp_hal_delay_us(uint32_t delay_count);
hv7131gp_status_t hv7131gp_i2c_hal_init(void);
hv7131gp_status_t hv7131gp_i2c_hal_reg_write(hv7131gp_reg_t reg, uint8_t  val);
hv7131gp_status_t hv7131gp_i2c_hal_reg_read(hv7131gp_reg_t reg, uint8_t *val);
hv7131gp_status_t hv7131gp_dma_hal_init(uint8_t dma_ch);




/******************************************************************************/
/*                           Hardware Abstraction Layer                       */
/******************************************************************************/

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
#define HV7131GP_PIN_HSYNC_INIT()						\
do { 										\
	TRISDbits.TRISD6 = 1;	/* Set CN15 (RD6) as digital input */		\
	IPC6bits.CNIP = 7;	/* Set CN interrupt priority */			\
} while (0)									

#define HV7131GP_PIN_HSYNC_START()						\
do { 										\
	CNCONSET = _CNCON_ON_MASK;	/* Activate CN */			\
	CNENbits.CNEN15 = 1;	/* Select CN15(RD6) change interrupt */		\
	CNPUESET = 0x8000;	/* Enable weak pull-up on Change Notify	*/	\
	IEC1bits.CNIE = 1;	/* Enable CN interrupt */			\
	IFS1bits.CNIF = 0;	/* Reset CN interrupt flag */ 			\
} while (0)									

#define HV7131GP_PIN_HSYNC_STOP()						\
do { 										\
	CNCONCLR = _CNCON_ON_MASK;						\
	IEC1bits.CNIE = 0;	/* Disable CN interrupt */			\
	CNENbits.CNEN15 = 0;	/* Disable CN15(RD6) change interrupt */	\
	IFS1bits.CNIF = 0;	/* Reset CN interrupt flag */	 		\
} while (0)									

#define HV7131GP_HSYNC_RESET_IF() IFS1bits.CNIF = 0

#define HV7131GP_HSYNC_INTERRUPT() void __attribute__((interrupt(ipl7))) \
    	 __attribute__((vector(_CHANGE_NOTICE_VECTOR))) isr__CHANGE_NOTICE_VECTOR(void) 

#define HV7131GP_HSYNC_VALUE() PORTDbits.RD6



/**  @} */

/**
* @name Video (Pixels) Clock
*
* INT4. It's the pixel interrupt: everytime this interrupt occurs a pixel is
* captured.
*
* @{ */
//FIXME Era 1!!
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
#define HV7131GP_PIN_Y_INIT()	TRISE = 0x00FF 	/* Init PORT_E */
#define HV7131GP_PIN_Y_VALUE	PORTE		/* Returns PORT_E */
/**  @} */



/**
* @name Software interrupt: end of frame acquisition
*
* INT0. This interrupt is generated when an entire frame is captured. This
* interrupt call inside his ISR the callback function passed on the capture
* function
* \see hv7131gp_capture
*
* @{ */


#define HV7131GP_PIN_EOF_INIT()						\
do { 									\
	IPC0bits.INT0IP  = 5;	/* Set INT0 interrupt priority */	\
	IEC0bits.INT0IE = 1;	/* Enable INT0 interrupt */		\
	IFS0bits.INT0IF = 0;	/* Reset INT0 interrupt flag */	 	\
} while (0)								

#define HV7131GP_PIN_EOF_STOP()						\
do { 									\
	IEC0bits.INT0IE = 0;	/* Disable INT0 interrupt */		\
	IFS0bits.INT0IF = 0;	/* Reset INT0 interrupt flag */	 	\
} while (0)								


#define HV7131GP_EOF_INTERRUPT() ISR2(_EXTERNAL_0_VECTOR)
#define HV7131GP_EOF_RESET_IF() IFS0bits.INT0IF = 0
#define HV7131GP_EOF_ACTIVATE_IF() IFS0bits.INT0IF = 1



/* Functions used by the DMA Controller */

#ifdef __USE_DMA__
#define ADDR_VIRTUAL_TO_PHYSICAL(a) (((EE_UREG)(a)) & 0x1FFFFFFF)
#endif // __USE_DMA__
/**  @} */


#define HV7131GP_HAL_DISABLE_INTERRUPTS() asm volatile("di")
#define HV7131GP_HAL_ENABLE_INTERRUPTS() asm volatile("ei")


#endif /* HV7131GP_HAL_H_ */
