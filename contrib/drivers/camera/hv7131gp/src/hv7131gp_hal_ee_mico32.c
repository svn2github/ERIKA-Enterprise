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

/******************************************************************************/
/*                         Global Variables                                   */
/******************************************************************************/
extern volatile uint8_t *frame_buffer;
extern volatile void (* capture_complete_func) (hv7131gp_status_t);

/******************************************************************************/
/*                          Local Variables                                   */
/******************************************************************************/
static volatile uint16_t  row_id, frame_idx;
static volatile uint16_t  height, width, image_size;

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
	// to do...
	return;
}

void hv7131gp_oc_hal_start(void)
{
	// to do...
	return;
}

void hv7131gp_oc_hal_stop(void)
{
	// to do...
	return;
}

// +++++++++ ISR not yet supported!!! ++++++++++++

// /* ----------------------------------------------------------------------------
// |  EOF Interrupt                                                               |
// |                                                                              |
// |  Interrupt that inform about the termination of the acquisition              |
 // ---------------------------------------------------------------------------- */

// HV7131GP_EOF_INTERRUPT()
// {
	// if (capture_complete_func)
		// capture_complete_func(HV7131GP_SUCCESS);
	// HV7131GP_EOF_RESET_IF();	/* Clear interrupt flag */
// }

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

// #ifdef HV7131GP_HSYNC_INT_MODE
// HV7131GP_HSYNC_INTERRUPT()                
// {
	// #ifdef __USE_DMA__	
	// DCH0SSA = ADDR_VIRTUAL_TO_PHYSICAL((void *)&PORTE);
	// DCH0DSA = ADDR_VIRTUAL_TO_PHYSICAL(&frame_buffer[frame_idx]);	
	// HV7131GP_HAL_DISABLE_INTERRUPTS();
	// DCH0CONSET = _DCH0CON_CHEN_MASK;

	// #ifdef __INT_DMA__ 	
		// HV7131GP_PIN_VCLK_START();
	// #endif //DMA_INTERRUPT
	
	// while(HV7131GP_HSYNC_VALUE())
	// {	
	// #ifdef __INT_DMA__ //DMA Interrupt mode
		// Nop();
	// #else
		// while(PORTAbits.RA15) ;	//Pixel clock		
			// DCH0ECONSET = _DCH0ECON_CFORCE_MASK; 	// Force Tx Start 
	// #endif //DMA_INTERRUPT
	// }	

	// #ifdef __INT_DMA__
		// HV7131GP_PIN_VCLK_STOP();	
	// #endif
	
	
	// frame_idx += DMA_MAX_WIDTH;
	// HV7131GP_HAL_ENABLE_INTERRUPTS();
	// /* Check if last row is ready -> frame ready? */

	// if((frame_idx >= image_size) || (++row_id >= height)){
		// /* Stop row and frame syncs, notify capture complete */
		// HV7131GP_PIN_HSYNC_STOP();
		// HV7131GP_PIN_VSYNC_STOP();
		// HV7131GP_EOF_ACTIVATE_IF(); //Activate interrupt
	// }
	// HV7131GP_HSYNC_RESET_IF();			/* Reset CN interrupt flag */
	// #endif // __USE_DMA__
// }
// #endif



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

// HV7131GP_VSYNC_INTERRUPT()
// {	
	// row_id 		= 0;
	// frame_idx 	= 0;

	// Read the size of the picture
	// width 	= hv7131gp_get_width();
	// height 	= hv7131gp_get_height();
	// image_size = hv7131gp_get_size();

	// HV7131GP_PIN_HSYNC_START();
	// HV7131GP_VSYNC_RESET_IF();    /* Reset INT3 interrupt flag */
// }

/* ---------------------- Driver functions --------------------------------- */

void vsync_handler(void)
{
	// to do...
	return;
}

void hsync_handler(void)
{
	// to do...
	return;
}

void vclk_handler(void)	
{
	// to do...
	return;
}

void eof_handler(void)
{
	// to do...
	return;
}

void hv7131gp_hal_delay_us(uint32_t delay_count)
{
 	MicoSleepMicroSecs((unsigned int)delay_count);
}

hv7131gp_status_t hv7131gp_i2c_hal_init(void)
{	
	if( EE_hv7131gp_i2c_config(100000,0) < 0)
		return -HV7131GP_ERR_I2C_INIT;
	
	return HV7131GP_SUCCESS;
}

hv7131gp_status_t hv7131gp_i2c_hal_reg_write(hv7131gp_reg_t reg, uint8_t val)
{
	if (EE_hv7131gp_i2c_write_byte(reg, val) !=  EE_I2C_OK)
		return -HV7131GP_ERR_I2C_WRITE;
	return HV7131GP_SUCCESS;
}

hv7131gp_status_t hv7131gp_i2c_hal_reg_read(hv7131gp_reg_t reg, uint8_t *val)
{
	int ret = EE_hv7131gp_i2c_read_byte(reg);
	if (ret < 0)
		return -HV7131GP_ERR_I2C_READ;
	else
		*val = ret;
	return HV7131GP_SUCCESS; 
}

hv7131gp_status_t hv7131gp_hal_init(uint8_t dma_channel){
	
	if (hv7131gp_i2c_hal_init() != HV7131GP_SUCCESS)
		return -HV7131GP_ERR_I2C_INIT;
	return HV7131GP_SUCCESS;
}

/* ---------------------- Global variables --------------------------------- */
EE_ISR_callback ee_hv7131gp_cbk;	// ISR camera callback function

/* ---------------------- CAMERA interrupt handler ------------------------- */

void EE_hv7131gp_handler(int level)
{
	EE_camera_clear_IRQ_flag();
	
	if(ee_hv7131gp_cbk != (EE_ISR_callback)0)
		ee_hv7131gp_cbk();

	return;
}

/* ---------------------- Other CAMERA Library functions ------------------------- */

/* Camera initialization */
int EE_hv7131gp_ISR_init(MicoCamera_t* cam, int irqf)
{
	/* reset camera controller FSM */
	Mico_camera_reset(cam);
	
	/* Interrupt configuration */
	EE_mico32_register_ISR(irqf, EE_hv7131gp_handler);
	mico32_enable_irq(irqf);
	EE_camera_enable_IRQ();
	
	return HV7131GP_SUCCESS;
}

int EE_hv7131gp_polling_init(MicoCamera_t* cam)
{
	/* Disable IRQ */
	EE_camera_disable_IRQ();
	
	/* reset camera controller FSM */
	Mico_camera_reset(cam);
	
	return HV7131GP_SUCCESS;
}

/* Set default configuration */
int EE_hv7131gp_set_default_configuration(void)
{
	int ret;
	
	ret = EE_hv7131gp_set_time_divisor(EE_HV7131GP_DEFAULT_DIVISOR);
	if (ret != HV7131GP_SUCCESS)
		return ret;
	
	ret = EE_hv7131gp_set_format(EE_HV7131GP_DEFAULT_FORMAT);
	if (ret != HV7131GP_SUCCESS)
		return ret;
	
	ret = EE_hv7131gp_set_resolution(EE_HV7131GP_DEFAULT_RESOLUTION);
	if (ret != HV7131GP_SUCCESS)
		return ret;
	
	ret = EE_hv7131gp_set_window(EE_HV7131GP_DEFAULT_WIDTH, EE_HV7131GP_DEFAULT_HEIGTH, 
								EE_HV7131GP_DEFAULT_COLUMN, EE_HV7131GP_DEFAULT_ROW);
	if (ret != HV7131GP_SUCCESS)
		return ret;
	
	ret = EE_hv7131gp_set_vblank(EE_HV7131GP_DEFAULT_VBLANK);
	if (ret != HV7131GP_SUCCESS)
		return ret;
	
	ret = EE_hv7131gp_set_hblank(EE_HV7131GP_DEFAULT_HBLANK);

	return ret;
}

/* Set configuration */
int EE_hv7131gp_set_configuration(int div, int fmt, int res, int w, int h, int x, int y, int hb, int vb)	// to do... aggiungere più parametri...
{
	int ret;

	ret = EE_hv7131gp_set_time_divisor(div);
	if (ret != HV7131GP_SUCCESS)
			return ret;
	
	ret = EE_hv7131gp_set_format(fmt);
	if (ret != HV7131GP_SUCCESS)
		return ret;
	
	ret = EE_hv7131gp_set_resolution(res);
	if (ret != HV7131GP_SUCCESS)
		return ret;
	
	ret = EE_hv7131gp_set_window(w, h, x, y);
	if (ret != HV7131GP_SUCCESS)
		return ret;
	
	ret = EE_hv7131gp_set_hblank(hb);
	if (ret != HV7131GP_SUCCESS)
		return ret;
	
	ret = EE_hv7131gp_set_vblank(vb);

	return ret;
}

/* Set width */
int EE_hv7131gp_set_width(int width)
{
	int ret;
	
	if( width > 0x280 ) return HV7131GP_FAILURE;
	
	ret = EE_hv7131gp_i2c_write_byte(HV7131GP_REG_WIWH, (width >> 8) & (0x00FF));
	if (ret != HV7131GP_SUCCESS) 
		return ret;
	ret = EE_hv7131gp_i2c_write_byte(HV7131GP_REG_WIWL, width & (0x00FF));
	
	return ret;
}

/* Get width */
int EE_hv7131gp_get_width(void)
{
	int ret;
	int width;
	
	ret = EE_hv7131gp_i2c_read_byte(HV7131GP_REG_WIWH);
	if (ret < 0) 
		return ret;
	width = (ret & 0x00FF)<<8;	
	
	ret = EE_hv7131gp_i2c_read_byte(HV7131GP_REG_WIWL);
	if (ret < 0) 
		return ret;
	
	width = width + (ret & 0x00FF);
	
	return width;
}

/* Set height */
int EE_hv7131gp_set_height(int height)
{
	int ret;
	
	if( height > 0x1E0 ) return HV7131GP_FAILURE;
	
	ret = EE_hv7131gp_i2c_write_byte(HV7131GP_REG_WIHH, (height >> 8) & (0x00FF));
	if (ret != HV7131GP_SUCCESS) 
		return ret;	
	ret = EE_hv7131gp_i2c_write_byte(HV7131GP_REG_WIHL, height & (0x00FF));
	
	return ret;
}

/* Get height */
int EE_hv7131gp_get_height(void)
{
	int ret;
	int height;
	
	ret = EE_hv7131gp_i2c_read_byte(HV7131GP_REG_WIHH);
	if (ret < 0) 
		return ret;
	height = (ret & 0x00FF)<<8;
		
	ret = EE_hv7131gp_i2c_read_byte(HV7131GP_REG_WIHL);
	if (ret < 0) 
		return ret;
	
	height = height + (ret & 0x00FF);
	
	return height;
}

/* Set x position */
int EE_hv7131gp_set_xpos(int x)
{
	int ret;
	
	if( (x < 0x2) || (x > 0x280) ) return HV7131GP_FAILURE;
	
	ret = EE_hv7131gp_i2c_write_byte(HV7131GP_REG_CSAH, (x >> 8) & (0x00FF));
	if (ret != HV7131GP_SUCCESS) 
		return ret;
	ret = EE_hv7131gp_i2c_write_byte(HV7131GP_REG_CSAL, x & (0x00FF));
	
	return ret;
}

/* Get x position */
int EE_hv7131gp_get_xpos(void)
{
	int ret;
	int x;
	
	ret = EE_hv7131gp_i2c_read_byte(HV7131GP_REG_CSAH);
	if (ret < 0) 
		return ret;
	x = (ret & 0x00FF)<<8;	

	ret = EE_hv7131gp_i2c_read_byte(HV7131GP_REG_CSAL);
	if (ret < 0) 
		return ret;
	
	x = x + (ret & 0x00FF);
	
	return x;
}

/* Set y position */
int EE_hv7131gp_set_ypos(int y)
{
	int ret;
	
	if( (y < 0x2) || (y > 0x1E0) ) return HV7131GP_FAILURE;
	
	ret = EE_hv7131gp_i2c_write_byte(HV7131GP_REG_RSAH, (y >> 8) & (0x00FF));
	if (ret != HV7131GP_SUCCESS) 
		return ret;
	ret = EE_hv7131gp_i2c_write_byte(HV7131GP_REG_RSAL, y & (0x00FF));
	
	return ret;
}

/* Get y position */
int EE_hv7131gp_get_ypos(void)
{
	int ret;
	int y;
	
	ret = EE_hv7131gp_i2c_read_byte(HV7131GP_REG_RSAH);
	if (ret < 0) 
		return ret;
	y = (ret & 0x00FF)<<8;	

	ret = EE_hv7131gp_i2c_read_byte(HV7131GP_REG_RSAL);
	if (ret < 0) 
		return ret;
	
	y = y + (ret & 0x00FF);
	
	return y;
}

/* Set hblank */
int EE_hv7131gp_set_hblank(int hb)
{
	int ret;

	if (hb < 208 || hb > 65535) return HV7131GP_FAILURE;
	
	ret = EE_hv7131gp_i2c_write_byte(HV7131GP_REG_HBLANKH, (hb >> 8) & (0x00FF));
	if (ret != HV7131GP_SUCCESS)
		return ret;
	ret = EE_hv7131gp_i2c_write_byte(HV7131GP_REG_HBLANKL, hb & (0x00FF));
	
	return ret;
}

/* Get hblank */
int EE_hv7131gp_get_hblank(void)
{
	int ret;
	int hb;
	
	ret = EE_hv7131gp_i2c_read_byte(HV7131GP_REG_HBLANKH);
	if (ret < 0) 
		return ret;
	hb = (ret & 0x00FF)<<8;	

	ret = EE_hv7131gp_i2c_read_byte(HV7131GP_REG_HBLANKL);
	if (ret < 0) 
		return ret;
	
	hb = hb + (ret & 0x00FF);
	
	return hb;
}

/* Set vblank */
int EE_hv7131gp_set_vblank(int vb)
{
	int ret;

	if (vb < 8 || vb > 65535) return HV7131GP_FAILURE;

	ret = EE_hv7131gp_i2c_write_byte(HV7131GP_REG_VBLANKH, (vb >> 8) & (0x00FF));
	if (ret != HV7131GP_SUCCESS)
		return ret;
	
	ret = EE_hv7131gp_i2c_write_byte(HV7131GP_REG_VBLANKL, vb & (0x00FF));

	return ret;
}

/* Get vblank */
int EE_hv7131gp_get_vblank(void)
{
	int ret;
	int vb;
	
	ret = EE_hv7131gp_i2c_read_byte(HV7131GP_REG_VBLANKH);
	if (ret < 0) 
		return ret;
	vb = (ret & 0x00FF)<<8;	

	ret = EE_hv7131gp_i2c_read_byte(HV7131GP_REG_VBLANKL);
	if (ret < 0) 
		return ret;
		
	vb = vb + (ret & 0x00FF);
	
	return vb;
}

int EE_hv7131gp_get_size(void)
{
	int width, height;
	
	width = EE_hv7131gp_get_width();
	if(width < 0)
		return width;
		
	height = EE_hv7131gp_get_height();
	if(height < 0)
		return height;
		
	return width*height;	//size
}

/* Set window */
int EE_hv7131gp_set_window(int width, int height, int x, int y)
{
	int ret;
	
	ret = EE_hv7131gp_set_width(width);
	if (ret != HV7131GP_SUCCESS)
		return ret;
		
	ret = EE_hv7131gp_set_height(height);
	if (ret != HV7131GP_SUCCESS)
		return ret;
	
	ret = EE_hv7131gp_set_xpos(x);
	if (ret != HV7131GP_SUCCESS)
		return ret;
		
	ret = EE_hv7131gp_set_ypos(y);
	if (ret != HV7131GP_SUCCESS)
		return ret;

	return ret;
}

/* Capture an image */
int EE_hv7131gp_capture(void *image, EE_ISR_callback cam_cbk)
{
	if (image == NULL)
		return HV7131GP_ERR_MEM_NULL;

	EE_camera_write_address(image);		// image buffer
	ee_hv7131gp_cbk = cam_cbk;				// set the callback function
	EE_camera_start();					// activate frame acquisition
	
    return HV7131GP_SUCCESS;
}

/* Set sleep mode */
int EE_hv7131gp_set_sleep_status(void)
{
	int ret = 0;
	
	ret = EE_hv7131gp_i2c_read_byte(HV7131GP_REG_SCTRB);
	if(ret < 0)
		return ret;
	
	ret = EE_hv7131gp_i2c_write_byte(HV7131GP_REG_SCTRB, ret | HV7131GP_SLEEP_MODE);
	
	return ret;
}

/* Set active mode */
int EE_hv7131gp_set_active_status(void)
{
	int ret = 0;
	
	ret = EE_hv7131gp_i2c_read_byte(HV7131GP_REG_SCTRB);
	if(ret < 0)
		return ret;
	
	ret = EE_hv7131gp_i2c_write_byte(HV7131GP_REG_SCTRB, ret & (~HV7131GP_SLEEP_MODE));
	
	return ret;
}

