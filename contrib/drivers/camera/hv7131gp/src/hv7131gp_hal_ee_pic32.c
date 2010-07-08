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
 * hv7131gp_hal.c
 *
 * Created on: 9-feb-2009
 * Author: Claudio Salvadori
 */

#include "hv7131gp_hal.h"
#include "hv7131gp.h"

#include "mcu/microchip_pic32/inc/ee_i2c.h"
#include "mcu/microchip_pic32/inc/ee_oc.h"


/******************************************************************************/
/*                         Global Variables                                   */
/******************************************************************************/
volatile void (* capture_complete_func) (hv7131gp_status_t) = NULL;

volatile uint8_t *frame_buffer = NULL;


/******************************************************************************/
/*                          Local Variables                                   */
/******************************************************************************/
/*static*/ volatile uint16_t  /*row_id,*/ frame_idx;
/*static*/ volatile uint16_t  height, width, image_size;
/******************************************************************************/
/*                           Hardware Abstraction Layer                       */
/******************************************************************************/
/* ----------------------------------------------------------------------------
|  Start OC1 Interface:                                                        |
|                                                                              |
|  OC1: Generate MasterClock for Sparkfun Camera (use Timer3)                  |
|       - OC in Toggle Mode -> F_MasterClock = F_TMR/2                         |
 ---------------------------------------------------------------------------- */
void hv7131gp_oc_hal_init(uint16_t period)
{
	EE_oc_init(EE_OC_1);
	/********************************/ 
	/* Set:				*/
	/* - Output Compare 1		*/
	/* - Toggle mode		*/
	/* - Timer3			*/
	/* - Period			*/
	/* - Divisor			*/
	/********************************/	
	EE_oc_setup(EE_OC_1,  EE_OC_CONFIGURE_TOGGLE | EE_OC_TIMER_3, period, 0x0); 
	/********************************/ 
	/* Set:				*/
	/* - OC1R			*/
	/* - OCR1S			*/
	/* - mode, not implemented	*/	
	/********************************/
	EE_oc_advanced_setup(EE_OC_1, 0x0, 0x1, 0);  
}

void hv7131gp_oc_hal_start(void)
{
	EE_oc_start(EE_OC_1);
}

void hv7131gp_oc_hal_stop(void)
{
	EE_oc_stop(EE_OC_1);
}

/* ----------------------------------------------------------------------------
|  EOF Interrupt                                                               |
|                                                                              |
|  Interrupt that inform about the termination of the acquisition              |
 ---------------------------------------------------------------------------- */

HV7131GP_EOF_INTERRUPT()
{
	if (capture_complete_func)
		capture_complete_func(HV7131GP_SUCCESS);
	HV7131GP_EOF_RESET_IF();	/* Clear interrupt flag */
}



/* ----------------------------------------------------------------------------
|  ISR1 CN:                                                                    |
|                                                                              |
|  New row.                                                                    |
|  Change notify interrupt to understand the start of a new row; that means    |
|  the pixel value after this interrupt are valid value. So what this interrupt|
|  does is the pixel interrupt activation (start of row) and pixel interrupt   |
|  deactivation (end of row).                                                  |
|  In this interrupt is is implemented a procedure to resync the image buffer  |
|  if some pixels are lost in the previous row.                                |
|  This interrupt manages also the end-of-frame notification, switching on     |
|  an interrupt (INT0) that call a callback function                           |
 ---------------------------------------------------------------------------- */

#ifdef HV7131GP_HSYNC_INT_MODE
HV7131GP_HSYNC_INTERRUPT()                
{
	#ifdef __USE_DMA__	
	DCH0SSA = ADDR_VIRTUAL_TO_PHYSICAL((void *)HV7131GP_PIN_Y_ADDRESS);
	DCH0DSA = ADDR_VIRTUAL_TO_PHYSICAL(&frame_buffer[frame_idx]);	
	HV7131GP_HAL_DISABLE_INTERRUPTS();
	DCH0CONSET = _DCH0CON_CHEN_MASK;

	#ifdef __INT_DMA__ 	
		//HV7131GP_PIN_VCLK_START();
	#endif //DMA_INTERRUPT
	
	while(HV7131GP_HSYNC_VALUE())
	{	
	#ifdef __INT_DMA__ //DMA Interrupt mode
		Nop();
	#else
		while(PORTAbits.RA15) ;	//Pixel clock		
			DCH0ECONSET = _DCH0ECON_CFORCE_MASK; 	// Force Tx Start 
	#endif //DMA_INTERRUPT
	}	

	#ifdef __INT_DMA__
		//HV7131GP_PIN_VCLK_STOP();	
	#endif
	
	//DCH0CONCLR = _DCH0CON_CHEN_MASK;
	
	frame_idx += DMA_MAX_WIDTH;
	HV7131GP_HAL_ENABLE_INTERRUPTS();
	/* Check if last row is ready -> frame ready? */

	if((frame_idx >= image_size) /*|| (++row_id >= height)*/){
		/* Stop row and frame syncs, notify capture complete */
		HV7131GP_PIN_HSYNC_STOP();
		HV7131GP_PIN_VSYNC_STOP();
		HV7131GP_EOF_ACTIVATE_IF(); //Activate interrupt
	}
	HV7131GP_HSYNC_RESET_IF();			/* Reset CN interrupt flag */
	#endif // __USE_DMA__
}
#endif



/* ----------------------------------------------------------------------------
|  ISR1 INT3:                                                                  |
|                                                                              |
|  New Frame.                                                                  |
|                                                                              |
|  Zeroing of row and pixel counters, set image dimension variables, start     |
|  reception of row interrupts.                                                |
|  If "Debug" configuration is possible to manage the function that measure    |
|  the frame duration, and toggle a value of output pin to show that duration  |
 ---------------------------------------------------------------------------- */

HV7131GP_VSYNC_INTERRUPT()
{	
	//row_id 		= 0;
	frame_idx 	= 0;

	//Read the size of the picture
	width 	= hv7131gp_get_width();
	height 	= hv7131gp_get_height();
	image_size = hv7131gp_get_size();

	HV7131GP_PIN_HSYNC_START();
	HV7131GP_VSYNC_RESET_IF();    /* Reset INT3 interrupt flag */
}


#ifdef __USE_DMA__
hv7131gp_status_t hv7131gp_dma_hal_init(uint8_t dma_ch){
	switch (dma_ch){
	case 0: 
		IEC1CLR = _IEC1_DMA0IE_MASK;  		
		IFS1CLR = _IFS1_DMA0IF_MASK; 		
		DMACONSET = _DMACON_ON_MASK; 
		DCH0CON = 0x3;  
		DCH0CONCLR = _DCH0CON_CHEN_MASK;
		DCH0ECON = 0;
		DCH0SSIZ = 1;
		DCH0DSIZ = DMA_MAX_WIDTH; 
		DCH0CSIZ = 1;
		DCH0INTCLR= 0;
		#ifdef __INT_DMA__
		DCH0ECON = _DCH0ECON_SIRQEN_MASK | 
			       (_EXTERNAL_4_IRQ  << _DCH0ECON_CHSIRQ_POSITION);
		HV7131GP_PIN_VCLK_INIT();
		#endif
		
		IPC9CLR = _IPC9_DMA0IP_MASK | _IPC9_DMA0IS_MASK; //SPI1_DMAIP_MASK | SPI1_DMAIS_MASK;
		IPC9SET = ((5 <<_IPC9_DMA0IP_POSITION ) & _IPC9_DMA0IP_MASK)  |
			  ((2 << _IPC9_DMA0IS_MASK) & _IPC9_DMA0IS_MASK);
		break;
	default:
		return -HV7131GP_ERR_DMA_INIT; //Fare HV7131GP_DMA_PORT_UNINPLEMENTED;
	}	
	return HV7131GP_SUCCESS;

};
#endif // __USE_DMA__


hv7131gp_status_t hv7131gp_i2c_hal_init(void)
{
	if (EE_i2c_init(EE_I2C_PORT_1, DEFAULT_400KHZ_BRG, DEFAULT_FLAGS) != EE_I2C_SUCCESS)
		return -HV7131GP_ERR_I2C_INIT;
	return HV7131GP_SUCCESS;
}

hv7131gp_status_t hv7131gp_i2c_hal_reg_write(hv7131gp_reg_t reg, uint8_t val)
{
	if (EE_i2c_write_byte(EE_I2C_PORT_1, HV7131GP_DEVICE_ID, reg, val) !=  EE_I2C_SUCCESS)
		return -HV7131GP_ERR_I2C_WRITE;
	return HV7131GP_SUCCESS;
}

hv7131gp_status_t hv7131gp_i2c_hal_reg_read(hv7131gp_reg_t reg, uint8_t *val)
{
	
	if (EE_i2c_read_byte(EE_I2C_PORT_1, HV7131GP_DEVICE_ID, reg, val) !=  EE_I2C_SUCCESS)
		return -HV7131GP_ERR_I2C_READ;
	return HV7131GP_SUCCESS; 
}


hv7131gp_status_t hv7131gp_hal_init(uint8_t dma_channel){
	
	if (hv7131gp_i2c_hal_init() != HV7131GP_SUCCESS)
		return -HV7131GP_ERR_I2C_INIT;
	#ifdef __USE_DMA__
	if (hv7131gp_dma_hal_init(dma_channel) != HV7131GP_SUCCESS)
		return -HV7131GP_ERR_DMA_INIT; 
	#endif
	return HV7131GP_SUCCESS;
}


/* ----------------------------------------------------------------------------
|  Start Capture from HV7131GP Camera :                                        |
|                                                                              |
|  - TODO:                                                                     |
 ---------------------------------------------------------------------------- */
hv7131gp_status_t hv7131gp_hal_capture(uint8_t *image, hv7131gp_cback_t *func)
{
	frame_buffer = image;
	capture_complete_func = func;

	HV7131GP_VSYNC_RESET_IF();

	//Enables the interrupt associated with the VSYN
	HV7131GP_PIN_VSYNC_START();	/* Initializes the Frame Sync */

	return HV7131GP_SUCCESS;
}

