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

/**
 *\file hv7131gp.h
 *
 *\date  Created on: 6-feb-2009
 *\author  Author: Claudio Salvadori and Christian Nastasi
 *\brief API header
 */

/** \mainpage
 * Update chronology:
 *
 *  - 06/02/2009 definition of the driver API for HV7131GP:
 *  	-# hv7131gp_status_t hv7131gp_init(void): initialization of the camera. It return
	a success message only if the first frame interrupt is arrived.
*	-# hv7131gp_status_t hv7131gp_configure(void): HV7131GP configuration function via
*	i2c. It return when the i2c communication is finished.
*	-# hv7131gp_status_t hv7131gp_capture(uint8_t *image, void(* func)(hv7131gp_status_t)):
*	start capture images.
*	-# hv7131gp_status_t hv7131gp_reg_write(hv7131gp_reg_t reg, uint8_t val): low
*	level function to write HV7131GP register via i2c. No control on the read only
*	register
*	-# hv7131gp_status_t hv7131gp_reg_read(hv7131gp_reg_t reg, uint8_t *val): low
*	level function to write HV7131GP register via i2c.
*	-# uint8_t hv7131gp_get_width(void): read the current image width
*	-# uint8_t hv7131gp_get_height(void): read the current image height
*	-# uint16_t hv7131gp_get_size(void): read the size of the image buffer
*	-# uint8_t hv7131gp_get_Y_average(void): read the current image luminance mean value
 *  - 06/02/2009 redefinition of the layout of the HV7131GP driver
 *  - 06/02/2009 in the "Debug" configuration is possible to have the frame duration,
 *    using the function: uint16_t hv7131gp_get_fdh(void) e uint16_t hv7131gp_get_fdl(void)
 *  - 09/02/2009 finished the driver layout design
 *  - 09/02/2009 added the complete list of the HV7131GP register
 *  - 10/02/2009 added to API: hv7131gp_status_t hv7131gp_set_sleep_status(void). It set
 *    the "Sleep mode" bit to 1 (1 = sleep mode, 0 = active mode)
 *  - 10/02/2009 added to API: hv7131gp_status_t hv7131gp_set_active_status(void). It set
 *    the "Sleep mode" bit to 0 (1 = sleep mode, 0 = active mode)
 *  - 10/02/2009 in the "Debug" configuration is possible to check if there's lost frame
 *    during the image processing using the function: uint16_t hv7131gp_get_fl(void)
 *  - 10/02/2008 End-of-frame management with INT0 interrupt: ISR2(_INT0Interrupt)
 *    is the function that called the call-back function
 *    \see hv7131gp_capture
 *  - 12/02/2008 added timeout in I2C polling
 *  - 26/02/2008 finished the receive task "Command" and the demonstrator using FLTK
 *    libraries
 */

#ifndef _hv7131gp_h_
#define _hv7131gp_h_

#include "hv7131gp_reg.h"
#include "hv7131gp_compiler.h"

/******************************************************************************/
/*                           Constants Definition                             */
/******************************************************************************/

#define	HV7131GP_MORE_THAN_1_MS			1500
#define	HV7131GP_MORE_THAN_4_MCLK_CYCLES	1 	
#define	HV7131GP_MORE_THAN_2086000_MCLK_CYCLES	300000





/******************************************************************************/
/*                            Type Definitions                                */
/******************************************************************************/
/**
*\brief Exit status for the HV7131GP driver
* Values returned by the operative API function
* \see hv7131gp_init, hv7131gp_configure, hv7131gp_capture, hv7131gp_reg_write,
* hv7131gp_reg_read
*
*
*/


typedef enum {
	HV7131GP_SUCCESS = 0,		/**< No error */
	HV7131GP_FAILURE,		/**< Generic error */
	HV7131GP_ERR_I2C_INIT,		/**< I2C bus initialization error */
	HV7131GP_ERR_I2C_READ,		/**< I2C bus read error */
	HV7131GP_ERR_I2C_WRITE,		/**< I2C bus write error */
	HV7131GP_ERR_DEV_NOINIT,	/**< Device is not initialized */
	HV7131GP_ERR_MEM_NULL,		/**< Invalid NULL memory address */
	HV7131GP_ERR_DMA_INIT,	/**< Invalid NULL memory address */
	HV7131GP_HAL_INIT_ERR,
} hv7131gp_status_t;

/**
* @brief Resolution value
*/
typedef enum {
	HV7131GP_NO_SUB  	= 0x00,		/**< 640x480 pixel resolution*/
	HV7131GP_1_4_SUB	= 0x01,		/**< 320x240 pixel resolution*/
	HV7131GP_1_16_SUB	= 0x02,		/**< 160x120 pixel resolution */
} hv7131gp_R_Value_t;

/**
* @brief Time divisor
*
*/
typedef enum {
	HV7131GP_T_1	= 0x00,		/**< Divide MCLK for 1 */
	HV7131GP_T_2	= 0x01,		/**< Divide MCLK for 2 */
	HV7131GP_T_3	= 0x02,		/**< Divide MCLK for 4 */
	HV7131GP_T_4	= 0x03,		/**< Divide MCLK for 8 */
	HV7131GP_T_5	= 0x04,		/**< Divide MCLK for 16 */
	HV7131GP_T_6	= 0x05,		/**< Divide MCLK for 32 */
	HV7131GP_T_7	= 0x06,		/**< Divide MCLK for 64 */
	HV7131GP_T_8	= 0x07,		/**< Divide MCLK for 128 */
} hv7131gp_T_D_Value_t;


/**
* @brief Quality value (high level)
*/
typedef enum {
	HV7131GP_160x120_FAST  	= 0x00,		/**< 160x120 + T2 divisor*/
	HV7131GP_160x120_MEDIUM	= 0x01,		/**< 160x120 + T4 divisor*/
	HV7131GP_160x120_SLOW	= 0x02,		/**< 160x120 + T7 divisor */
} hv7131gp_Q_Value_t;

/**
* @name Type representation
* @{ */

//TODO: utilizzare definizione standard


/**  @} */



/******************************************************************************/
/*                         Function Declarations                              */
/******************************************************************************/
/**
* @brief Init a HV7131GP Camera with 10MHz master clock
*
* @return Returns \c HV7131GP_SUCCESS if no error occurs,
*         otherwise a specific error code.
*/
hv7131gp_status_t hv7131gp_init(void);

/**
* @brief Reset the camera at the start configuration
*
* @return Returns \c HV7131GP_SUCCESS if no error occurs,
*         otherwise a specific error code.
*/
hv7131gp_status_t hv7131gp_init_configure(void);

/**
* @brief Configure the clock division on HV7131GP Camera
*
* \param div		Divisor value
*
* \see hv7131gp_T_D_Value_t
*
* @return Returns \c HV7131GP_SUCCESS if no error occurs,
*         otherwise a specific error code.
*/
hv7131gp_status_t hv7131gp_configure_time_divisor(hv7131gp_T_D_Value_t div);

/**
* @brief Configure the resolution on HV7131GP Camera
*
* \param res		Resolution value
*
* \see hv7131gp_R_Value_t
*
* @return Returns \c HV7131GP_SUCCESS if no error occurs,
*         otherwise a specific error code.
*/
hv7131gp_status_t hv7131gp_configure_resolution(hv7131gp_R_Value_t res);

/**
* @brief Set a window on HV7131GP Camera.
*
* \param width		Width of image to read out
* \param height		Height of image to read out
* \param x		Column start address of image to read out
* \param y		Row start address of image to read out
*
* @return Returns \c HV7131GP_SUCCESS if no error occurs,
*         otherwise a specific error code.
*/
hv7131gp_status_t hv7131gp_window_set(int16_t width, int16_t height, int16_t x, 
								int16_t y);

/**
* @brief Configure HBLANK value via i2c
*
* \param hb		Effective HBLANK value to set. hb is represented like
* 			2 8bit register and have to be bigger than 208
*
* @return Returns \c HV7131GP_SUCCESS if no error occurs,
*         otherwise a specific error code.
*/
hv7131gp_status_t hv7131gp_hblank_set(int16_t hb);

/**
* @brief Configure VBLANK value via i2c
*
* \param vb		Effective VBLANK value to set. vb is represented like
* 			2 8bit register and have to be bigger than 8
*
* @return Returns \c HV7131GP_SUCCESS if no error occurs,
*         otherwise a specific error code.
*/
hv7131gp_status_t hv7131gp_vblank_set(int16_t vb);

/**
* @brief Configure windowing an resolution in safe mode on HV7131GP Camera.
* "Safe mode" means the buffer size is checked with the maximum possible size
* for specified hardware.
*
* \see MAX_SIZE_PIC_30
*
* \param width		Width of image to read out
* \param height		Height of image to read out
* \param x		Column start address of image to read out
* \param y		Row start address of image to read out
* \param res		Resolution value
*
* \see hv7131gp_R_Value_t
*
* @return Returns \c HV7131GP_SUCCESS if no error occurs,
*         otherwise a specific error code.
*/
hv7131gp_status_t hv7131gp_configure_safe(int16_t width, int16_t height, int16_t x, int16_t y,
					  hv7131gp_R_Value_t res);

/**
* @brief Highest level configuration function where is possible to set a
* quality value that correspond to a 160x120 resolution, variable time divisor,
* fixed HBLAN (208) and fixed VBLANK(8)
*
*
* \param Q		Quality value
*
* \see hv7131gp_Q_Value_t
*
* @return Returns \c HV7131GP_SUCCESS if no error occurs,
*         otherwise a specific error code.
*/
hv7131gp_status_t hv7131gp_configure(hv7131gp_Q_Value_t Q);

/**
* @brief Capture the first available frame HV7131GP Camera
*
* @param *image 			Pointer to a buffer.
* @param (* func) (hv7131gp_status_t) 	Call-back function pointer called after a
* frame is completely captured. This call-back function has to return a
* hv7131gp_status_t value.
*
* @return Returns \c HV7131GP_SUCCESS if no error occurs,
*         otherwise a specific error code.
*/
hv7131gp_status_t hv7131gp_capture(uint8_t *image, void (*func) (hv7131gp_status_t));

/**
* @brief Write a HV7131GP Camera register
*
* @param reg Device register address
* @param val Register value
*
* @return Returns \c HV7131GP_SUCCESS if no error occurs,
*         otherwise a specific error code.
*/
hv7131gp_status_t hv7131gp_reg_write(hv7131gp_reg_t reg, uint8_t val);

/**
* @brief Read a HV7131GP Camera register
*
* @param reg Device register address
* @param val Register value
*
* @return Returns \c HV7131GP_SUCCESS if no error occurs,
*         otherwise a specific error code.
*/
hv7131gp_status_t hv7131gp_reg_read(hv7131gp_reg_t reg, uint8_t *val);

/**
* @brief Returns the image width
*
*
* @return Returns \c uint8_t value that represent the number of pixel of
* each row
*/
uint8_t hv7131gp_get_width(void);

/**
* @brief Returns the image height
*
*
* @return Returns \c uint8_t value that represent the number of pixel of
* each column
*/
uint8_t hv7131gp_get_height(void);

/**
* @brief Returns the image size
*
*
* @return Returns \c uint16_t value that represent the number of pixel of an image.
*/
uint16_t hv7131gp_get_size(void);

/**
* @brief Returns the luminance mean value
*
*
* @return Returns \c uint8_t value that represent luminance mean value
*/
uint8_t hv7131gp_get_Y_average(void);

/**
* @brief Set the camera to sleep mode. This function read
* 		 the SCTRB register and set high the "Sleep mode" bit.
*
* @return Returns \c HV7131GP_SUCCESS if no error occurs,
*         otherwise a specific error code.
*/
hv7131gp_status_t hv7131gp_set_sleep_status(void);

/**
* @brief Set the camera to active mode. This function read
* 		 the SCTRB register and set low the "Sleep mode" bit.
*
* @return Returns \c HV7131GP_SUCCESS if no error occurs,
*         otherwise a specific error code.
*/
hv7131gp_status_t hv7131gp_set_active_status(void);


#endif
