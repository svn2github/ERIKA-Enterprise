/*
Copyright (C) 2009 -  Salvatore Marrapese, Claudio Salvadori 
and Christian Nastasi
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

#define _OV9650_C_

#include "../inc/ov9650.h"

/******************************************************************************/
/*                         Global Variables                                   */
/******************************************************************************/

/******************************************************************************/
/*                          Local Variables                                   */
/******************************************************************************/
/******************************************************************************/
/*                          Local Variables                                   */
/******************************************************************************/
static uint16_t  frame_height = 0;
static uint16_t  frame_width = 0;
static int32_t   frame_size = 0;

/******************************************************************************/
/*                          Function Definitions                              */
/******************************************************************************/

static void update_frame_size(void)
{
	// Color alway present
	frame_size = frame_height * frame_width * 2;
}

/* ----------------------------------------------------------------------------
|  Acknoledgement from the camera init: wait for 1st interrupt                 |
|  Returns:                                                                    |
|  1 - 1st interrupt is arrived after a timer                                  |
|                                                                              |
|  0 - 1st interrupt is not arrived                                            |
 ---------------------------------------------------------------------------- */
static ov9650_status_t init_ack(void)
{
	if (OV9650_HAL_DRIVING_PINS) {
		while (!OV9650_VSYNC_IF_VALUE)
			;
		/* Reset the IF flag */
		OV9650_VSYNC_RESET_IF();

		/* Check the correct lowering of the interrupt pin */
		while (OV9650_VSYNC_IF_VALUE)
			;
		return OV9650_SUCCESS;
	} else {
		return ov9650_hal_init_ack();
	}
}

/* ----------------------------------------------------------------------------
|  Initialization sequence for OV9650 Camera (see OV9650 Application Notes):   |
|                                                                              |
|  0 - POWER CAMERA = ON,                                                      |
|  1 - RESET Hw									                               |
|  2 - Start master clock;                                                     |
|  3 - Wait more than 1 ms (App. Note pag 6 Ts:RESET)                          |
 ---------------------------------------------------------------------------- */
static void init_sequence(void)
{
	if (OV9650_HAL_DRIVING_PINS) {
		/* Enable Power camera. */
		OV9650_PIN_PWDN_ON();
		/* No Reset Camera (We use only software reset). */
		OV9650_PIN_RESET_OFF();

		/* Start supply logic clock from Pic32 board to Camera. */
		OV9650_PIN_MCLK_START();

		/* Reset procedure. */
		ov9650_hal_delay_us(OV9650_MORE_THAN_1_MS);
		ov9650_hal_delay_us(OV9650_MORE_THAN_1_MS);
		ov9650_hal_delay_us(OV9650_MORE_THAN_1_MS);
		ov9650_hal_delay_us(OV9650_MORE_THAN_1_MS);
		ov9650_hal_delay_us(OV9650_MORE_THAN_1_MS);
		OV9650_PIN_RESET_ON();
		// Keep hardware reset pin high for at least 2ms
		ov9650_hal_delay_us(OV9650_MORE_THAN_1_MS);
		ov9650_hal_delay_us(OV9650_MORE_THAN_1_MS);
		ov9650_hal_delay_us(OV9650_MORE_THAN_1_MS);
		ov9650_hal_delay_us(OV9650_MORE_THAN_1_MS);
		ov9650_hal_delay_us(OV9650_MORE_THAN_1_MS);
		ov9650_hal_delay_us(OV9650_MORE_THAN_1_MS);
		ov9650_hal_delay_us(OV9650_MORE_THAN_1_MS);
		OV9650_PIN_RESET_OFF();
		ov9650_hal_delay_us(OV9650_MORE_THAN_1_MS);
		ov9650_hal_delay_us(OV9650_MORE_THAN_1_MS);
		ov9650_hal_delay_us(OV9650_MORE_THAN_1_MS);

		/* Delay more than 1ms 
		   Or 4096 camera clock cycle.
		   With Clk = 1MHz, for example, the delay is:
		   dy = 4096 * 10^(-6) = 4.096ms
		*/
		ov9650_hal_delay_us(OV9650_MORE_THAN_1_MS);
		ov9650_hal_delay_us(OV9650_MORE_THAN_1_MS);
		ov9650_hal_delay_us(OV9650_MORE_THAN_1_MS);
		ov9650_hal_delay_us(OV9650_MORE_THAN_1_MS);
	}
}

/* ----------------------------------------------------------------------------
|  Initializes OV9650 Camera:                                                  |
|                                                                              |
|  - init the ENABLE, RESETB, MCLK pins;                                       |
|  - init the I2C interface;                                                   |
|  - begin the initialization sequence described in the device ref. man.       |
 ---------------------------------------------------------------------------- */
ov9650_status_t ov9650_init(void)
{

	if (OV9650_HAL_DRIVING_PINS) {
		/* Initializing pins */
		OV9650_PIN_PWDN_INIT();
		OV9650_PIN_RESET_INIT();
		OV9650_PIN_MCLK_INIT(OV9650_MCLK_FREQ);
		OV9650_PIN_VSYNC_INIT_POSITIVE();
		OV9650_PIN_HSYNC_INIT();
		OV9650_PIN_VCLK_INIT();
		OV9650_PIN_EOF_INIT();
		OV9650_PIN_Y_INIT();
	}

	/* Delay at least than 4096 clock cycle after hw reset 
	 */
	ov9650_hal_delay_us(OV9650_MORE_THAN_1_MS);
	ov9650_hal_delay_us(OV9650_MORE_THAN_1_MS);
	ov9650_hal_delay_us(OV9650_MORE_THAN_1_MS);
	ov9650_hal_delay_us(OV9650_MORE_THAN_1_MS);
	ov9650_hal_delay_us(OV9650_MORE_THAN_1_MS);
	ov9650_hal_delay_us(OV9650_MORE_THAN_1_MS);
	ov9650_hal_delay_us(OV9650_MORE_THAN_1_MS);
	ov9650_hal_delay_us(OV9650_MORE_THAN_1_MS);
	
	/* Initialize the internal peripheral, setting the comunication 
	   protocol */
	if (ov9650_hal_init(0) != OV9650_SUCCESS)
		return -OV9650_HAL_INIT_ERR;

	if (OV9650_HAL_DRIVING_PINS) {
		/* Start camera initialization sequence (see device refman) */
		init_sequence();
	}

	/* Delay at least than 4096 clock cycle after sw reset 
	 */
	ov9650_hal_delay_us(OV9650_MORE_THAN_1_MS);
	ov9650_hal_delay_us(OV9650_MORE_THAN_1_MS);
	ov9650_hal_delay_us(OV9650_MORE_THAN_1_MS);
	ov9650_hal_delay_us(OV9650_MORE_THAN_1_MS);

	/* The answer to the init procedure: Vsync interrupt
	   It's Ok for OV9650 but not necessary for the OV9650
	*/
	if(init_ack() != OV9650_SUCCESS) {
		return OV9650_ERR_DEV_NOINIT;
	}

	/* Default registers configuration. */
	
	return OV9650_SUCCESS; 
}

/* ----------------------------------------------------------------------------
|  Write, on I2c, an OV9650 Camera Register:                                   |
 ---------------------------------------------------------------------------- */
ov9650_status_t ov9650_reg_write(ov9650_reg_t reg, uint8_t val)
{
	return ov9650_i2c_hal_reg_write(reg, val);
}

/* ----------------------------------------------------------------------------
|  Read, on I2c bus, an OV9650 Camera Register:                               |
 ---------------------------------------------------------------------------- */
ov9650_status_t ov9650_reg_read(ov9650_reg_t reg, uint8_t *val)
{
	return ov9650_i2c_hal_reg_read(reg, val);
}

/*
 * Modify the bits set in mask of the register reg with the values from value
 */
ov9650_status_t ov9650_reg_update(ov9650_reg_t reg, uint8_t mask, uint8_t value)
{
	ov9650_status_t ret;
	uint8_t oldvalue;

	ret = ov9650_i2c_hal_reg_read(reg, &oldvalue);
	if (ret != OV9650_SUCCESS) {
		return ret;
	}

	ret = ov9650_reg_write(reg, (oldvalue & ~mask) | (value & mask));
	if (ret != OV9650_SUCCESS) {
		return ret;
	}

	return OV9650_SUCCESS; 
}

/* ----------------------------------------------------------------------------
|  Configure the image resolution, and turn on horizontal flipping on          |
|  OV9650 Camera:                                                              |
|                                                                              |
|  This function sets via I2c one of the possible values:                      |
|  OV9650_SXGA   1280x1024 pixel resolution                                    |
|  OV9650_VGA	  640x 480 pixel resolution                                    |
|  OV9650_QVGA    320x 240 pixel resolution                                    |
|  OV9650_QQVGA   160x 120 pixel resolution                                    |
|  OV9650_CIF     352x 288 pixel resolution                                    |
|  OV9650_QCIF    176x 144 pixel resolution                                    |
|  OV9650_QQCIF    88x 72 pixel resolution                                     |
|  									                                           |
|  This function can change the value frame_width, frame_height 	           |
 ---------------------------------------------------------------------------- */
ov9650_status_t ov9650_configure_resolution(ov9650_R_Value_t res)
{
	ov9650_status_t ret;

	/* Set resolutions: */
	switch (res) {
		/* 1280x1024, 5 Mhz input clock, PLL = x4, YUV format */
		case OV9650_XSVGA:
			ret = ov9650_reg_write(OV9650_REG_COM1, 0x00);
			if (ret != OV9650_SUCCESS) {
				return ret;
			}
			ret = ov9650_reg_write(OV9650_REG_COM3, 0x00);
			if (ret != OV9650_SUCCESS) {
				return ret;
			}
			ret = ov9650_reg_write(OV9650_REG_COM4, 0x00);
			if (ret != OV9650_SUCCESS) {
				return ret;
			}
			ret = ov9650_reg_write(OV9650_REG_CLKRC, 0x80);
			if (ret != OV9650_SUCCESS) {
				return ret;
			}
			ret = ov9650_reg_write(OV9650_REG_COM7, 0x00);
			if (ret != OV9650_SUCCESS) {
				return ret;
			}
			ret = ov9650_reg_write(OV9650_REG_ADC, 0x81);
			if (ret != OV9650_SUCCESS) {
				return ret;
			}
			ret = ov9650_reg_write(OV9650_REG_ACOM, 0x93);
			if (ret != OV9650_SUCCESS) {
				return ret;
			}
			ret = ov9650_reg_write(OV9650_REG_OFON, 0x43);
			if (ret != OV9650_SUCCESS) {
				return ret;
			}
			ret = ov9650_reg_write(OV9650_REG_MVFP, 0x10);
			if (ret != OV9650_SUCCESS) {
				return ret;
			}
			frame_width  = 2* 1280;
			frame_height = 1024;
		break;
		case OV9650_VGA:
			/* 640x480, 5 Mhz input clock, PLL = x4, YUV format */
			ret = ov9650_reg_write(OV9650_REG_COM1, 0x00);
			if (ret != OV9650_SUCCESS) {
				return ret;
			}
			ret = ov9650_reg_write(OV9650_REG_COM3, 0x04);
			if (ret != OV9650_SUCCESS) {
				return ret;
			}
			ret = ov9650_reg_write(OV9650_REG_COM4, 0x80);
			if (ret != OV9650_SUCCESS) {
				return ret;
			}
			ret = ov9650_reg_write(OV9650_REG_CLKRC, 0x81);
			if (ret != OV9650_SUCCESS) {
				return ret;
			}
			ret = ov9650_reg_write(OV9650_REG_COM7, 0x40);
			if (ret != OV9650_SUCCESS) {
				return ret;
			}
			ret = ov9650_reg_write(OV9650_REG_ADC, 0x91);
			if (ret != OV9650_SUCCESS) {
				return ret;
			}
			ret = ov9650_reg_write(OV9650_REG_ACOM, 0x12);
			if (ret != OV9650_SUCCESS) {
				return ret;
			}
			ret = ov9650_reg_write(OV9650_REG_OFON, 0x43);
			if (ret != OV9650_SUCCESS) {
				return ret;
			}
			ret = ov9650_reg_write(OV9650_REG_MVFP, 0x10);
			if (ret != OV9650_SUCCESS) {
				return ret;
			}
			frame_width  = 2 * 640;
			frame_height = 480;
		break;
		case OV9650_QVGA:
			/* 320x240, 5 Mhz input clock, PLL = x4, YUV format */
			ret = ov9650_reg_write(OV9650_REG_COM1, 0x00);
			if (ret != OV9650_SUCCESS) {
				return ret;
			}
			ret = ov9650_reg_write(OV9650_REG_COM3, 0x04);
			if (ret != OV9650_SUCCESS) {
				return ret;
			}
			ret = ov9650_reg_write(OV9650_REG_COM4, 0x80);
			if (ret != OV9650_SUCCESS) {
				return ret;
			}
			ret = ov9650_reg_write(OV9650_REG_CLKRC, 0x83);
			if (ret != OV9650_SUCCESS) {
				return ret;
			}
			ret = ov9650_reg_write(OV9650_REG_COM7, 0x10);
			if (ret != OV9650_SUCCESS) {
				return ret;
			}
			ret = ov9650_reg_write(OV9650_REG_ADC, 0x91);
			if (ret != OV9650_SUCCESS) {
				return ret;
			}
			ret = ov9650_reg_write(OV9650_REG_ACOM, 0x12);
			if (ret != OV9650_SUCCESS) {
				return ret;
			}
			ret = ov9650_reg_write(OV9650_REG_OFON, 0x43);
			if (ret != OV9650_SUCCESS) {
				return ret;
			}
			ret = ov9650_reg_write(OV9650_REG_MVFP, 0x10);
			if (ret != OV9650_SUCCESS) {
				return ret;
			}
			frame_width  = 2 * 320;
			frame_height = 240;
		break;
		case OV9650_QQVGA:
			/* 160x120, 5 Mhz input clock, PLL = x4, YUV format */
			ret = ov9650_reg_write(OV9650_REG_COM1, 0x24);
			if (ret != OV9650_SUCCESS) {
				return ret;
			}
			ret = ov9650_reg_write(OV9650_REG_COM3, 0x04);
			if (ret != OV9650_SUCCESS) {
				return ret;
			}
			ret = ov9650_reg_write(OV9650_REG_COM4, 0x80);
			if (ret != OV9650_SUCCESS) {
				return ret;
			}
			ret = ov9650_reg_write(OV9650_REG_CLKRC, 0x83);
			if (ret != OV9650_SUCCESS) {
				return ret;
			}
			ret = ov9650_reg_write(OV9650_REG_COM7, 0x10);
			if (ret != OV9650_SUCCESS) {
				return ret;
			}
			ret = ov9650_reg_write(OV9650_REG_ADC, 0x91);
			if (ret != OV9650_SUCCESS) {
				return ret;
			}
			ret = ov9650_reg_write(OV9650_REG_ACOM, 0x12);
			if (ret != OV9650_SUCCESS) {
				return ret;
			}
			ret = ov9650_reg_write(OV9650_REG_OFON, 0x43);
			if (ret != OV9650_SUCCESS) {
				return ret;
			}
			ret = ov9650_reg_write(OV9650_REG_MVFP, 0x10);
			if (ret != OV9650_SUCCESS) {
				return ret;
			}
			frame_width  = 2 * 160;
			frame_height = 120;
		break;
		case OV9650_CIF:
			/* 352x288, 24 Mhz input clock, YUV format */
			ret = ov9650_reg_write(OV9650_REG_COM1, 0x00);
			if (ret != OV9650_SUCCESS) {
				return ret;
			}
			ret = ov9650_reg_write(OV9650_REG_COM3, 0x04);
			if (ret != OV9650_SUCCESS) {
				return ret;
			}
			ret = ov9650_reg_write(OV9650_REG_COM4, 0x80);
			if (ret != OV9650_SUCCESS) {
				return ret;
			}
			ret = ov9650_reg_write(OV9650_REG_CLKRC, 0x83);
			if (ret != OV9650_SUCCESS) {
				return ret;
			}
			ret = ov9650_reg_write(OV9650_REG_COM7, 0x20);
			if (ret != OV9650_SUCCESS) {
				return ret;
			}
			ret = ov9650_reg_write(OV9650_REG_ADC, 0x91);
			if (ret != OV9650_SUCCESS) {
				return ret;
			}
			ret = ov9650_reg_write(OV9650_REG_ACOM, 0x12);
			if (ret != OV9650_SUCCESS) {
				return ret;
			}
			ret = ov9650_reg_write(OV9650_REG_OFON, 0x43);
			if (ret != OV9650_SUCCESS) {
				return ret;
			}
			ret = ov9650_reg_write(OV9650_REG_MVFP, 0x10);
			if (ret != OV9650_SUCCESS) {
				return ret;
			}
			frame_width  = 2 * 352;
			frame_height = 288;
		break;
		case OV9650_QCIF:
			/* 176x144, 24 Mhz input clock, YUV format */
			ret = ov9650_reg_write(OV9650_REG_COM1, 0x00);
			if (ret != OV9650_SUCCESS) {
				return ret;
			}
			ret = ov9650_reg_write(OV9650_REG_COM3, 0x04);
			if (ret != OV9650_SUCCESS) {
				return ret;
			}
			ret = ov9650_reg_write(OV9650_REG_COM4, 0x80);
			if (ret != OV9650_SUCCESS) {
				return ret;
			}
			ret = ov9650_reg_write(OV9650_REG_CLKRC, 0x87);
			if (ret != OV9650_SUCCESS) {
				return ret;
			}
			ret = ov9650_reg_write(OV9650_REG_COM7, 0x08);
			if (ret != OV9650_SUCCESS) {
				return ret;
			}
			ret = ov9650_reg_write(OV9650_REG_ADC, 0x91);
			if (ret != OV9650_SUCCESS) {
				return ret;
			}
			ret = ov9650_reg_write(OV9650_REG_ACOM, 0x12);
			if (ret != OV9650_SUCCESS) {
				return ret;
			}
			ret = ov9650_reg_write(OV9650_REG_OFON, 0x43);
			if (ret != OV9650_SUCCESS) {
				return ret;
			}
			ret = ov9650_reg_write(OV9650_REG_MVFP, 0x10);
			if (ret != OV9650_SUCCESS) {
				return ret;
			}
			frame_width  = 2 * 176;
			frame_height = 144;
		break;
		case OV9650_QQCIF:
			/* 88x 72, 24 Mhz input clock, YUV format */
			ret = ov9650_reg_write(OV9650_REG_COM1, 0x24);
			if (ret != OV9650_SUCCESS) {
				return ret;
			}
			ret = ov9650_reg_write(OV9650_REG_COM3, 0x04);
			if (ret != OV9650_SUCCESS) {
				return ret;
			}
			ret = ov9650_reg_write(OV9650_REG_COM4, 0x80);
			if (ret != OV9650_SUCCESS) {
				return ret;
			}
			ret = ov9650_reg_write(OV9650_REG_CLKRC, 0x87);
			if (ret != OV9650_SUCCESS) {
				return ret;
			}
			ret = ov9650_reg_write(OV9650_REG_COM7, 0x08);
			if (ret != OV9650_SUCCESS) {
				return ret;
			}
			ret = ov9650_reg_write(OV9650_REG_ADC, 0x91);
			if (ret != OV9650_SUCCESS) {
				return ret;
			}
			ret = ov9650_reg_write(OV9650_REG_ACOM, 0x12);
			if (ret != OV9650_SUCCESS) {
				return ret;
			}
			ret = ov9650_reg_write(OV9650_REG_OFON, 0x43);
			if (ret != OV9650_SUCCESS) {
				return ret;
			}
			ret = ov9650_reg_write(OV9650_REG_MVFP, 0x10);
			if (ret != OV9650_SUCCESS) {
				return ret;
			}
			frame_width  = 2 * 88;
			frame_height = 120;
		break;
	}

	// Frame size 
	update_frame_size();

	return OV9650_SUCCESS;
}

/* ----------------------------------------------------------------------------
|  Starting configuration of OV9650 Camera:                                    |
|                                                                              |
|  This function is called inside the OV9650 init function to preset           |
|  some variables; in this way is prevented the un-initialization of certain   |
|  variables that are absolutely necessary to capture an image, and it is      |
|  possible to use the camera without calling any configuration function.      |
|  Default settings are:                                                       |
|  1. Tests some Id registers.                                                 |
|  2. Load default configuration into register.						           |
|  3. Set 160x120 resolution                                                   |
 ---------------------------------------------------------------------------- */
ov9650_status_t ov9650_init_configure(void)
{
	ov9650_status_t ret;
	uint8_t id;

	/* Test Hw. */
	ret = ov9650_reg_read(OV9650_REG_MIDH, &id);
	if (ret != OV9650_SUCCESS) {
		return ret;
	}
	if (id != OV9650_PROD_IDH) {
		return OV9650_ERR_WRONG_PRODUCT;
	}

	// QQVGA
	ov9650_reg_write(OV9650_REG_COM1, 0x24);
	ov9650_reg_write(OV9650_REG_COM3, 0x04);
	ov9650_reg_write(OV9650_REG_COM4, 0x80);
	ov9650_reg_write(OV9650_REG_CLKRC, 0x83);
	ov9650_reg_write(OV9650_REG_COM7, 0x10);
	ov9650_reg_write(OV9650_REG_ADC, 0x91);
	ov9650_reg_write(OV9650_REG_ACOM, 0x12);
	ov9650_reg_write(OV9650_REG_OFON, 0x43);
	ov9650_reg_write(OV9650_REG_MVFP, 0x10);
	/* Driver Linux
	ov9650_reg_write(OV9650_REG_COM7, 0x10);    // Set as default thr QVGA output mode RGB.
	
    ov9650_reg_write(OV9650_REG_CLKRC, 0x81);   // Pll enabled and CLK divided by 2.
    ov9650_reg_write(OV9650_REG_DBLV, 0x0a);    // DBLV (reserved). The setting was taken by Linux driver.
    ov9650_reg_write(OV9650_REG_MBD, 0x41);     // Banding Filter On.
    ov9650_reg_write(OV9650_REG_COM11, 0x09);   // Use half frame for banding filter mode.
	ov9650_reg_write(OV9650_REG_COM8, 0xe0);    // Fast AGC/AEC.
    ov9650_reg_write(OV9650_REG_BLUE, 0x80);	// Gain Blue channel.
	ov9650_reg_write(OV9650_REG_RED, 0x80);	 	// Gain Red channel.
	ov9650_reg_write(OV9650_REG_GAIN, 0x00);	// Default GAIN value.
    ov9650_reg_write(OV9650_REG_AECH, 0x00);    // AECH
    ov9650_reg_write(OV9650_REG_COM8, 0xe5);    // Enabled AGC/AEC
    ov9650_reg_write(OV9650_REG_OFON, 0x43);    // OPON  ???
    ov9650_reg_write(OV9650_REG_ACOM, 0x12);    // ACOM  ???
	ov9650_reg_write(OV9650_REG_ADC, 0x00);	 	// ADC   ???
    ov9650_reg_write(OV9650_REG_RSVD1, 0x91);   // RSVD1 ???
    ov9650_reg_write(OV9650_REG_COM5, 0x20);    // COM5  ???
    ov9650_reg_write(OV9650_REG_MVFP, 0x30);    // Mirror and VFlip enabled
    ov9650_reg_write(OV9650_REG_COM1, 0x20);    // QQVGA, QQCIF, No skip HREF and CCIR656 format.
    ov9650_reg_write(OV9650_REG_COM3, 0x00);    // COM3 default value
	ov9650_reg_write(OV9650_REG_COM4, 0x00);	// COM4	No VarioPixel

	// window start and stop for output size control
	// HSTOP is the high 8 bit of H STOP (low 3 bits are at HREF[5:3])
	// Because HREF[5:3] = 0b100, HSTOP = 0x28*2^3 + 4 = 0x144
	// HSTART[REG17h] is the high 8-bit of H START (low 3 bits are at HREF[2:0])
	// Because HREF[2:0] = 0b100, HSTART = 0x14*2^3 + 4 = 0x0A4
	// Therefore HSTOP-HSTART = (0x144+4)-(0x0A4+4) = 0x0A0 (160 dec.)
    ov9650_reg_write(OV9650_REG_HREF, 0xA4);  // H_STOP_LSB = 0b100, H_START_LSB = 0b100.
    ov9650_reg_write(OV9650_REG_HSTOP, 0x28);
    ov9650_reg_write(OV9650_REG_HSTART, 0x14);

	// VREF[REG03h] contains the start and end low 3 bits for VSTOP and VSTRT
	// VSTOP = 0x1E*2^3 + 4 = 0x0F4
	// VSTRT = 0x0F*2^3 + 4 = 0x07C
	// Therefore VSTOP - VSTRT = (0x0F4 + 4) - (0x07C + 4) = 0x78 (120 dec.)
    ov9650_reg_write(OV9650_REG_VREF, 0x24);      // V_STOP_LSB = 0b100, V_START_LSB = 0b100.
	ov9650_reg_write(OV9650_REG_VSTOP, 0x1E);
    ov9650_reg_write(OV9650_REG_VSTRT, 0x0F);
 
    ov9650_reg_write(OV9650_REG_COM9, 0x1A);     // Gain 2x, VSYNC always exists.
    ov9650_reg_write(OV9650_REG_COM10, 0x10);    // Slave mode horizontal sync.
	ov9650_reg_write(OV9650_REG_EDGE, 0xA6);	 // ???

	ov9650_reg_write(OV9650_REG_COM16, 0x02);	 // ???
	ov9650_reg_write(OV9650_REG_COM17, 0xC1);	 // ???
    ov9650_reg_write(OV9650_REG_PSHFT, 0x00);    // Pixel delay = 0

	ov9650_reg_write(OV9650_REG_RSVD0, 0x06);	 // ???
    ov9650_reg_write(OV9650_REG_CHLF, 0xe2);     // ???
	ov9650_reg_write(OV9650_REG_ARBLM, 0xbf);    // ???

	ov9650_reg_write(OV9650_REG_RSVD26, 0x04);	 // ???
 	ov9650_reg_write(OV9650_REG_TSLB, 0x00); 	 // Output YUYV
 
	ov9650_reg_write(OV9650_REG_COM24, 0x00);	 // ???
    ov9650_reg_write(OV9650_REG_COM12, 0x77);    // Bit reserved, enabled UV average

	ov9650_reg_write(OV9650_REG_COM21,0x06);     // ???
	ov9650_reg_write(OV9650_REG_RSVD24,0x88);    // ???
	ov9650_reg_write(OV9650_REG_RSVD25,0x88);    // ???
	ov9650_reg_write(OV9650_REG_COM15, 0xc1);    // Output range 00 -> FF, reserved bit
	ov9650_reg_write(OV9650_REG_Gr_COM, 0x3f);   // Reserved bits.
	ov9650_reg_write(OV9650_REG_COM6, 0x42);     // Reset timing on format changes
	ov9650_reg_write(OV9650_REG_COM13, 0x92);    // Output Y/UV delay
	ov9650_reg_write(OV9650_REG_HV, 0x40);	     // Manual Banding Filter MSB
	ov9650_reg_write(OV9650_REG_RSVD18, 0xB9);	 // 0x59 -> 0x61 all RSVD
	ov9650_reg_write(OV9650_REG_RSVD19, 0x96);	 //
	ov9650_reg_write(OV9650_REG_RSVD20,0x10);    //
	ov9650_reg_write(OV9650_REG_RSVD15, 0xc0);   //
	ov9650_reg_write(OV9650_REG_RSVD16, 0xaf);   //
	ov9650_reg_write(OV9650_REG_RSVD21, 0xe0);   //
	ov9650_reg_write(OV9650_REG_RSVD22, 0x8c);   //
	ov9650_reg_write(OV9650_REG_RSVD23, 0x20);   //

	ov9650_reg_write(OV9650_REG_RSVD17, 0x55);	 // REG[0x59-0x61] all RSVD
	ov9650_reg_write(OV9650_REG_RSVD3, 0xf0);	 // REG[0x43-0x4E] all RSVD
	ov9650_reg_write(OV9650_REG_RSVD4, 0x10);    //
	ov9650_reg_write(OV9650_REG_RSVD5, 0x68);    //
	ov9650_reg_write(OV9650_REG_RSVD6, 0x96);    //
	ov9650_reg_write(OV9650_REG_RSVD7, 0x60);    //
	ov9650_reg_write(OV9650_REG_RSVD8, 0x80);    //

	ov9650_reg_write(OV9650_REG_COM26, 0xD9);	 // RSVD
	ov9650_reg_write(OV9650_REG_COM25, 0x74);	 // RSVD
	ov9650_reg_write(OV9650_REG_COM23, 0x02);	 // color bar test mode disable, digital AWB enable
	ov9650_reg_write(OV9650_REG_COM8, 0xE7);	 // AGC, AWB, AEC all enabled here
	
	ov9650_reg_write(OV9650_REG_MTX1, 0x3A);	 // REG[4F-58] are Matrix coefficients
	ov9650_reg_write(OV9650_REG_MTX2, 0x3D);     //
	ov9650_reg_write(OV9650_REG_MTX3, 0x03);     //
	ov9650_reg_write(OV9650_REG_MTX4, 0x12);     //
	ov9650_reg_write(OV9650_REG_MTX5, 0x26);     //
	ov9650_reg_write(OV9650_REG_MTX6, 0x38);     //
	ov9650_reg_write(OV9650_REG_MTX7, 0x40);     //
	ov9650_reg_write(OV9650_REG_MTX8, 0x40);     //
	ov9650_reg_write(OV9650_REG_MTX9, 0x40);     //
	ov9650_reg_write(OV9650_REG_MTXS, 0x0D);     //

	ov9650_reg_write(OV9650_REG_COM22, 0x23);	 // De-noise enable, white-pixel erase enable
	ov9650_reg_write(OV9650_REG_COM14, 0x02);    //
	
	ov9650_reg_write(OV9650_REG_ACOM2, 0xB8);	 // REG[A8-AA] all RSVD
	ov9650_reg_write(OV9650_REG_ACOM3, 0x92);
	ov9650_reg_write(OV9650_REG_ACOM4, 0x0A);

	ov9650_reg_write(OV9650_REG_DBLC1, 0xdf);	 // Digital BLC offset sign???

	ov9650_reg_write(OV9650_REG_DBLC_B, 0x00);	 // Digital BLC B channel offset value set default
	ov9650_reg_write(OV9650_REG_DBLC_R, 0x00);	 // Digital BLC R channel offset value set default
	ov9650_reg_write(OV9650_REG_DBLC_Gb, 0x00);	 // Digital BLC Gb channel offset value set default
	ov9650_reg_write(OV9650_REG_DBLC_Gr, 0x00);	 // Digital BLC Gr channel offset value set default

	ov9650_reg_write(OV9650_REG_AEB, 0x88);	     // AEW stable operating region lower limit
	ov9650_reg_write(OV9650_REG_VPT, 0xd3);	     // AGC/AEC fast mode operating region
	ov9650_reg_write(OV9650_REG_EXHCH, 0x00);	 // Horizontal dummy pixel insert MSB
	ov9650_reg_write(OV9650_REG_EXHCL, 0x00);	 // Horizontal dummy insert LSB
	ov9650_reg_write(OV9650_REG_ADVFL, 0x00);    // Gamma curve.

	ov9650_reg_write(OV9650_REG_GSP, 0x40);	 // REG[6C-7B] are Gamma Curve setup GSP
	ov9650_reg_write(OV9650_REG_GSP1, 0x30);	 
	ov9650_reg_write(OV9650_REG_GSP2, 0x4B);
	ov9650_reg_write(OV9650_REG_GSP3, 0x60);
	ov9650_reg_write(OV9650_REG_GSP4, 0x70);
	ov9650_reg_write(OV9650_REG_GSP5, 0x70);
	ov9650_reg_write(OV9650_REG_GSP6, 0x70);
	ov9650_reg_write(OV9650_REG_GSP7, 0x70);
	ov9650_reg_write(OV9650_REG_GSP8, 0x60);
	ov9650_reg_write(OV9650_REG_GSP9, 0x60);
	ov9650_reg_write(OV9650_REG_GSPA, 0x50);
	ov9650_reg_write(OV9650_REG_GSPB, 0x48);
	ov9650_reg_write(OV9650_REG_GSPC, 0x3A);
	ov9650_reg_write(OV9650_REG_GSPD, 0x2E);
	ov9650_reg_write(OV9650_REG_GSPE, 0x28);
	ov9650_reg_write(OV9650_REG_GSPF, 0x22);

	ov9650_reg_write(OV9650_REG_GST, 0x04);	 // REG[7C-8A] are Gamma Curve setup GST
	ov9650_reg_write(OV9650_REG_GST1, 0x07);
	ov9650_reg_write(OV9650_REG_GST2, 0x10);
	ov9650_reg_write(OV9650_REG_GST3, 0x28);
	ov9650_reg_write(OV9650_REG_GST4, 0x36);
	ov9650_reg_write(OV9650_REG_GST5, 0x44);
	ov9650_reg_write(OV9650_REG_GST6, 0x52);
	ov9650_reg_write(OV9650_REG_GST7, 0x60);
	ov9650_reg_write(OV9650_REG_GST8, 0x6c);
	ov9650_reg_write(OV9650_REG_GST9, 0x78);
	ov9650_reg_write(OV9650_REG_GSTA, 0x8c);
	ov9650_reg_write(OV9650_REG_GSTB, 0x9e);
	ov9650_reg_write(OV9650_REG_GSTC, 0xbb);
	ov9650_reg_write(OV9650_REG_GSTD, 0xd2);
	ov9650_reg_write(OV9650_REG_GSTE, 0xe6);
	*/

	//Resolution: 160x120 Colour
	frame_width  = 2 * 160;
	frame_height = 120;

	// Frame size 
	update_frame_size();

	return OV9650_SUCCESS;
}

/* ----------------------------------------------------------------------------
|  Start Capture from OV9650 Camera :                                        |
|                                                                              |
|  - TODO:                                                                     |
 ---------------------------------------------------------------------------- */
uint16_t ov9650_get_width(void)
{
	// Frame width with component colour
	return frame_width / 2;
}

uint16_t ov9650_get_height(void)
{
	return frame_height;
}

uint32_t ov9650_get_size(void)
{
	return frame_size;
}

/* ----------------------------------------------------------------------------
|  Configure the clock division on OV9650 Camera by CLKRC register:            |
|                                                                              |
|  This function set via i2c the prescaler value of the master clock (Mclk)    |
|  the VCLK (pixel clock) and the frame rate. For more infos read the related  |
|  documentation.                                                              |
|  1. MCLK divided by 1                                                        |
|  2. MCLK divided by 2                                                        |
|  3. MCLK divided by 4                                                        |
|  4. MCLK divided by 8                                                        |
|  5. MCLK divided by 16                                                       |
|  6. MCLK divided by 32                                                       |
|  7. MCLK divided by 64                                                       |
|  8. MCLK divided by 128                                                      |
 ---------------------------------------------------------------------------- */
ov9650_status_t ov9650_configure_time_divisor(ov9650_T_D_Value_t div)
{
	ov9650_status_t help;

	switch(div) {
		case OV9650_T_1:	// Divisor set to 1
			help = ov9650_reg_write(OV9650_REG_CLKRC, 0);
			if (help != OV9650_SUCCESS) {
				return help;
			}
		break;
		case OV9650_T_2:	// Divisor set to 2
			help = ov9650_reg_write(OV9650_REG_CLKRC, 1);
			if (help != OV9650_SUCCESS) {
				return help;
			}
		break;
		case OV9650_T_3:	// Divisor set to 4
			help = ov9650_reg_write(OV9650_REG_CLKRC, 3);
			if (help != OV9650_SUCCESS) {
				return help;
			}
		break;
		case OV9650_T_4:	//Divisor set to 8
			help = ov9650_reg_write(OV9650_REG_CLKRC, 7);
			if (help != OV9650_SUCCESS) {
				return help;
			}
		break;
		case OV9650_T_5:	//Divisor set to 16
			help = ov9650_reg_write(OV9650_REG_CLKRC, 15);
			if (help != OV9650_SUCCESS) {
				return help;
			}
		break;
		case OV9650_T_6:	//Divisor set to 32
			help = ov9650_reg_write(OV9650_REG_CLKRC, 31);
			if (help != OV9650_SUCCESS) {
				return help;
			}
		break;
		case OV9650_T_7:	//Divisor set to 64
			help = ov9650_reg_write(OV9650_REG_CLKRC, 63);
			if (help != OV9650_SUCCESS) {
				return help;
			}
		break;
		default:
			return OV9650_FAILURE;
		break;
	}
	return OV9650_SUCCESS;
}

