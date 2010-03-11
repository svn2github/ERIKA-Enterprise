#ifdef __USE_MICO32BOARD_CAMERA__

#ifndef __EE_CAMERA_HV7131GP__
#define __EE_CAMERA_HV7131GP__

/* Camera header files */
#include "board/fpga_camera_mico32/inc/ee_camera_reg.h"
#include "cpu/mico32/inc/ee_internal.h"
#include "mcu/mico32/inc/ee_internal.h"
#include <cpu/mico32/inc/ee_irq.h>
/* Libraries: */
#include "mcu/mico32/inc/ee_i2c.h"
/* Callback function called by driver handlers  */
typedef void (*EE_camera_callback)(void);

typedef struct st_Camera{
	volatile unsigned int addr;
	volatile unsigned int state;
	volatile unsigned int flag;
    volatile unsigned int cntr1;
    volatile unsigned int cntr2;
    volatile unsigned int div;
}Camera_t;

extern EE_camera_callback ee_cam_cbk;

/* Symbols and macros */
#define EE_CAMERA_OFF 					(0x80)
#define EE_CAMERA_ON					(0x00)
#define EE_CAMERA_CSREG_ADDRESS 		(0x00)
#define EE_CAMERA_DEVICE_ID				HV7131GP_DEVICE_ID
#define EE_CAMERA_ISR_MODE				(0x01)
#define EE_CAMERA_POLLING_MODE			(0x00)
#define EE_camera_need_enable_int(mode)	(mode)

/* Default configuration */
#define EE_CAMERA_DEFAULT_DIVISOR 		EE_CAMERA_T_1
#define EE_CAMERA_DEFAULT_RESOLUTION 	EE_CAMERA_1_16_SUB
#define EE_CAMERA_DEFAULT_WIDTH 		640
#define EE_CAMERA_DEFAULT_HEIGTH 		480
#define EE_CAMERA_DEFAULT_COLUMN 		0x2
#define EE_CAMERA_DEFAULT_ROW 			0x2
#define EE_CAMERA_DEFAULT_VBLANK		8
#define EE_CAMERA_DEFAULT_HBLANK		208
#define EE_CAMERA_DEFAULT_FRAME_WIDTH	160
#define EE_CAMERA_DEFAULT_FRAME_HEIGHT	120

/* Camera controller register */
#define	EE_CAMERA_CSREG 0		/**< Control/Status register  */

/* Exit status for the EE_CAMERA driver 
	(see EE_CAMERA_init EE_CAMERA_configure EE_CAMERA_capture EE_CAMERA_reg_write EE_CAMERA_reg_read)
*/
#define	EE_CAMERA_SUCCESS 			0		/**< No error */
#define	EE_CAMERA_FAILURE			-19		/**< Generic error */
#define	EE_CAMERA_ERR_I2C_INIT		-20		/**< I2C bus initialization error */
#define	EE_CAMERA_ERR_I2C_READ		-21		/**< I2C bus read error */
#define	EE_CAMERA_ERR_I2C_WRITE		-22		/**< I2C bus write error */
#define	EE_CAMERA_ERR_DEV_NOINIT	-23		/**< Device is not initialized */
#define	EE_CAMERA_ERR_MEM_NULL		-24		/**< Invalid NULL memory address */

/* Resolution value */
#define	EE_CAMERA_NO_SUB  			HV7131GP_VIDEO_NORMAL		/**< 640x480 pixel resolution*/
#define	EE_CAMERA_1_4_SUB			HV7131GP_VIDEO_SUB_4		/**< 320x240 pixel resolution*/
#define	EE_CAMERA_1_16_SUB			HV7131GP_VIDEO_SUB_16		/**< 160x120 pixel resolution */

/* Time divisor */
#define	EE_CAMERA_T_1  				HV7131GP_DCF_1		/**< Divide MCLK for 1 */
#define	EE_CAMERA_T_2				HV7131GP_DCF_2		/**< Divide MCLK for 2 */
#define	EE_CAMERA_T_3				HV7131GP_DCF_4		/**< Divide MCLK for 4 */
#define	EE_CAMERA_T_4				HV7131GP_DCF_8		/**< Divide MCLK for 8 */
#define	EE_CAMERA_T_5				HV7131GP_DCF_16		/**< Divide MCLK for 16 */
#define	EE_CAMERA_T_6				HV7131GP_DCF_32		/**< Divide MCLK for 32 */
#define	EE_CAMERA_T_7				HV7131GP_DCF_64		/**< Divide MCLK for 64 */
#define	EE_CAMERA_T_8				HV7131GP_DCF_128	/**< Divide MCLK for 128 */

/* Quality value (high level) */
#define	EE_CAMERA_160x120_FAST  	EE_CAMERA_T_2		/**< 160x120 + T2 divisor*/
#define	EE_CAMERA_160x120_MEDIUM	EE_CAMERA_T_5		/**< 160x120 + T5 divisor*/
#define	EE_CAMERA_160x120_SLOW		EE_CAMERA_T_8		/**< 160x120 + T8 divisor */

/* bit masks */
#define EE_CAM_IF_FLAG_MASK 	0x0001
#define EE_CAM_ERR_FLAG_MASK 	0x0002
#define EE_CAM_START_MASK		0x0001
#define EE_CAM_IFACK_MASK		0x0002
#define EE_CAM_RESET_MASK		0x0004
#define EE_CAM_ENABLE_IRQ_MASK	0x0001

/* Read the address of the first location of the image buffer stored in the camera controller register */
__INLINE__ void* __ALWAYS_INLINE__ EE_hal_camera_read_address(Camera_t* cam)
{
	return ((void*)cam->addr);
}

/* Write the address of the image buffer in the camera controller register */
__INLINE__ void __ALWAYS_INLINE__ EE_hal_camera_write_address(Camera_t* cam, void* addr)
{
	cam->addr = (unsigned int)addr;
}

/* Read the status register of the camera controller register */
__INLINE__ int __ALWAYS_INLINE__ EE_hal_camera_read_status_register(Camera_t* cam)
{
	return cam->state;
}

/* Read the interrupt assertion flag from the camera controller flags register  */
__INLINE__ int __ALWAYS_INLINE__ EE_hal_camera_read_IF_flag(Camera_t* cam)
{
	return cam->flag & EE_CAM_IF_FLAG_MASK;
}

/* Read the err flag from the camera controller flags register */
__INLINE__ int __ALWAYS_INLINE__ EE_hal_camera_read_ERR_flag(Camera_t* cam)
{
	return cam->flag & EE_CAM_ERR_FLAG_MASK;
}

/* Start frame acquisition */
__INLINE__ void __ALWAYS_INLINE__ EE_hal_camera_start(Camera_t* cam)
{
	cam->cntr1 = EE_CAM_START_MASK;
}

/* Clear IRQ flag */
__INLINE__ void __ALWAYS_INLINE__ EE_hal_camera_clear_IRQ_flag(Camera_t* cam)
{
	cam->cntr1 = 0;
}

/* Reset the camera controller FSM */
__INLINE__ void __ALWAYS_INLINE__ EE_hal_camera_reset(Camera_t* cam)
{
	cam->cntr1 = EE_CAM_RESET_MASK;
}

/* Enable IRQ */
__INLINE__ void __ALWAYS_INLINE__ EE_hal_camera_enable_IRQ(Camera_t* cam, int irqf)
{
	cam->cntr2 = EE_CAM_ENABLE_IRQ_MASK;
}

/* Disable IRQ */
__INLINE__ void __ALWAYS_INLINE__ EE_hal_camera_disable_IRQ(Camera_t* cam)
{
	cam->cntr2 = 0;	//cam->cntr2 &= ~EE_CAM_ENABLE_IRQ_MASK; 
}

/* Read the IRQ enable register */
__INLINE__ int __ALWAYS_INLINE__ EE_hal_camera_IRQ_enabled(Camera_t* cam)
{
	return cam->cntr2 & EE_CAM_ENABLE_IRQ_MASK;	
}

/* Change the camera controller divisor */
__INLINE__ void __ALWAYS_INLINE__ EE_hal_camera_write_divisor(Camera_t* cam, unsigned int div)
{	
	cam->div = div;	
}

/* Read the camera controller divisor */
__INLINE__ int __ALWAYS_INLINE__ EE_hal_camera_read_divisor(Camera_t* cam)
{	
	return cam->div;
}

/* Check the end of the frame transmission */
__INLINE__ int __ALWAYS_INLINE__ EE_hal_camera_frame_terminated(Camera_t* cam)
{
	return cam->flag & EE_CAM_IF_FLAG_MASK;
}

/* Internal functions */
/* Macros for Camera API */  
// EE_SLAVE_NAME_UC, EE_SLAVE_NAME_LC
#define DECLARE_FUNC_CAMERA(uc, lc) \
__INLINE__ int __ALWAYS_INLINE__ EE_camera_init(int mode){ \
	return EE_hal_camera_init((Camera_t*)EE_BASE_ADD(uc), (int)EE_IRQ_NAME(uc), mode); }\
__INLINE__ void* __ALWAYS_INLINE__ EE_camera_read_address(void){ \
	return EE_hal_camera_read_address((Camera_t*)EE_BASE_ADD(uc)); } \
__INLINE__ void __ALWAYS_INLINE__ EE_camera_write_address(void* addr){ \
	EE_hal_camera_write_address((Camera_t*)EE_BASE_ADD(uc),addr); } \
__INLINE__ int __ALWAYS_INLINE__ EE_camera_read_status_register(void) {\
	return EE_hal_camera_read_status_register((Camera_t*)EE_BASE_ADD(uc)); } \
__INLINE__ int __ALWAYS_INLINE__ EE_camera_read_IF_flag(void){ \
	return EE_hal_camera_read_IF_flag((Camera_t*)EE_BASE_ADD(uc)); } \
__INLINE__ int __ALWAYS_INLINE__ EE_camera_read_ERR_flag(void){ \
	return EE_hal_camera_read_ERR_flag((Camera_t*)EE_BASE_ADD(uc)); } \
__INLINE__ void __ALWAYS_INLINE__ EE_camera_start(void){ \
	EE_hal_camera_start((Camera_t*)EE_BASE_ADD(uc)); } \
__INLINE__ void __ALWAYS_INLINE__ EE_camera_clear_IRQ_flag(void){ \
	EE_hal_camera_clear_IRQ_flag((Camera_t*)EE_BASE_ADD(uc)); } \
__INLINE__ void __ALWAYS_INLINE__ EE_camera_reset(void){ \
	EE_hal_camera_reset((Camera_t*)EE_BASE_ADD(uc)); } \
__INLINE__ void __ALWAYS_INLINE__ EE_camera_enable_IRQ(void){ \
	EE_hal_camera_enable_IRQ((Camera_t*)EE_BASE_ADD(uc), (int)EE_IRQ_NAME(uc)); } \
__INLINE__ void __ALWAYS_INLINE__ EE_camera_disable_IRQ(void){ \
	EE_hal_camera_disable_IRQ((Camera_t*)EE_BASE_ADD(uc)); } \
__INLINE__ int __ALWAYS_INLINE__ EE_camera_IRQ_enabled(void){ \
	return EE_hal_camera_IRQ_enabled((Camera_t*)EE_BASE_ADD(uc)); } \
__INLINE__ void __ALWAYS_INLINE__ EE_camera_write_divisor(unsigned int div){ \
	EE_hal_camera_write_divisor((Camera_t*)EE_BASE_ADD(uc), div); } \
__INLINE__ int __ALWAYS_INLINE__ EE_camera_read_divisor(void){ \
	return EE_hal_camera_read_divisor((Camera_t*)EE_BASE_ADD(uc)); } \
__INLINE__ int __ALWAYS_INLINE__ EE_camera_frame_terminated(void){ \
	return EE_hal_camera_frame_terminated((Camera_t*)EE_BASE_ADD(uc)); }

/* Macros for I2C-based Camera functions */  
#define DECLARE_FUNC_I2C_CAMERA(uc, lc) \
__INLINE__ int __ALWAYS_INLINE__ EE_camera_i2c_config(int baudrate,int settings){ \
	return cat3(EE_, lc, _config)(baudrate, settings); } \
__INLINE__ int __ALWAYS_INLINE__  EE_camera_write_byte(EE_UINT8 address, EE_UINT8 data){ \
	return cat3(EE_, lc, _write_byte)(EE_CAMERA_DEVICE_ID, address, data); } \
__INLINE__ int __ALWAYS_INLINE__  EE_camera_write_buffer(EE_UINT8 address, EE_UINT8 *data, int len){ \
	return cat3(EE_, lc, _write_buffer)(EE_CAMERA_DEVICE_ID, address, data, len); } \
__INLINE__ int __ALWAYS_INLINE__  EE_camera_read_byte(EE_UINT8 address){ \
	return cat3(EE_, lc, _read_byte)(EE_CAMERA_DEVICE_ID, address); } \
__INLINE__ int __ALWAYS_INLINE__  EE_camera_read_buffer(EE_UINT8 address, EE_UINT8 *data, int len){ \
	return cat3(EE_, lc, _read_buffer)(EE_CAMERA_DEVICE_ID, address, data, len); }\
__INLINE__ int __ALWAYS_INLINE__  EE_camera_set_time_divisor(int div){ \
	return cat3(EE_, lc, _write_byte)(EE_CAMERA_DEVICE_ID, HV7131GP_REG_SCTRB, div); }

/* Camera initialization */
int EE_hal_camera_init(Camera_t* cam, int irqf, int mode);

/* Set configuration */
int EE_camera_set_configuration(int div, int fmt, int res, int w, int h, int x, int y, int hb, int vb);

/* Set default configuration */
int EE_camera_set_default_configuration(void);

/* Set width */
int EE_camera_set_width(int width);

/* Get width */
int EE_camera_get_width(int *widthp);

/* Set height */
int EE_camera_set_height(int height);

/* Get height */
int EE_camera_get_height(int *heightp);

/* Set x position */
int EE_camera_set_xpos(int x);

/* Get x position */
int EE_camera_get_xpos(int *xp);

/* Set y position */
int EE_camera_set_ypos(int y);

/* Get y position */
int EE_camera_get_ypos(int *yp);

/* Set hblank */
int EE_camera_set_hblank(int hb);

/* Get hblank */
int EE_camera_get_hblank(int *hbp);

/* Set vblank */
int EE_camera_set_vblank(int vb);

/* Get vblank */
int EE_camera_get_vblank(int *vbp);

/* Set window */
int EE_camera_set_window(int width, int height, int x, int y);

/* Capture an image */
int EE_camera_capture(void *image, EE_camera_callback cam_cbk);

/* Set sleep mode */
int EE_camera_set_sleep_status(void);

/* Set active mode */
int EE_camera_set_active_status(void);

/* Camera API */
#ifdef __EE_CAMERA_USE_I2C1__
#ifdef __EE_CAMERA_USE_I2C2__
#error CAMERA cannot support both i2c controllers
#endif
DECLARE_FUNC_I2C_CAMERA(EE_I2C1_NAME_UC, EE_I2C1_NAME_LC)
#else //__EE_RTC_USE_I2C1__
DECLARE_FUNC_I2C_CAMERA(EE_I2C2_NAME_UC, EE_I2C2_NAME_LC)
#endif //__EE_RTC_USE_I2C1__
DECLARE_FUNC_CAMERA(EE_SLAVE_NAME_UC, EE_SLAVE_NAME_LC)

/* Set format */
__INLINE__ int __ALWAYS_INLINE__ EE_camera_set_format(EE_UINT8 val)
{
	//HV7131GP_OUTFMT_DEFAULT & (~HV7131GP_8BIT_OUTPUT)
	return EE_camera_write_byte(HV7131GP_REG_OUTFMT, val);
}

/* Get format */
__INLINE__ int __ALWAYS_INLINE__ EE_camera_get_format(void)
{
	//HV7131GP_OUTFMT_DEFAULT & (~HV7131GP_8BIT_OUTPUT)
	return EE_camera_read_byte(HV7131GP_REG_OUTFMT);
}

/* Set resolution */
__INLINE__ int __ALWAYS_INLINE__ EE_camera_set_resolution(EE_UINT8 val)
{
	//HV7131GP_REG_SCTRA, res | HV7131GP_X_FLIP
	return EE_camera_write_byte(HV7131GP_REG_SCTRA, val);
}

/* Get resolution */
__INLINE__ int __ALWAYS_INLINE__ EE_camera_get_resolution(void)
{
	//HV7131GP_REG_SCTRA, res | HV7131GP_X_FLIP
	return EE_camera_read_byte(HV7131GP_REG_SCTRA);
}
/* Get Y average */
__INLINE__ int __ALWAYS_INLINE__ EE_camera_get_Y_average(void)
{
	return EE_camera_read_byte(HV7131GP_REG_YFMEAN);
}



/* Global variables (external declaration...) */
//...

/*-----------------------------------------------------------------------------*/

/*
	__INLINE__ int __ALWAYS_INLINE__  EE_camera_start(void)
		This function is used to turn on the camera
		Arguments: 
			- none 
		Actions: 
			- turn on the camera
		Return values:
			- the function return the result:	EE_I2C_ERR_DEV_ACK if ACK is not received after slave address transmission
												EE_I2C_ERR_ADD_ACK if ACK is not received after memory address transmission
												EE_I2C_ERR_DATA_ACK if ACK is not received after data transmission
												EE_I2C_ERR_ARB_LOST if arbitration is lost
												EE_I2C_OK if no errors found							
*/
//__INLINE__ int __ALWAYS_INLINE__  EE_CAMERA_start(void);



///**
//* @brief Init a HV7131GP Camera with 10MHz master clock
//*
//* @return Returns \c HV7131GP_SUCCESS if no error occurs,
//*         otherwise a specific error code.
//*/
//hv7131gp_status_t hv7131gp_init(void);
//
///**
//* @brief Reset the camera at the start configuration
//*
//* @return Returns \c HV7131GP_SUCCESS if no error occurs,
//*         otherwise a specific error code.
//*/
//hv7131gp_status_t hv7131gp_init_configure(void);
//
///**
//* @brief Configure the clock division on HV7131GP Camera
//*
//* \param div		Divisor value
//*
//* \see hv7131gp_T_D_Value_t
//*
//* @return Returns \c HV7131GP_SUCCESS if no error occurs,
//*         otherwise a specific error code.
//*/
//hv7131gp_status_t hv7131gp_configure_time_divisor(hv7131gp_T_D_Value_t div);
//
///**
//* @brief Configure the resolution on HV7131GP Camera
//*
//* \param res		Resolution value
//*
//* \see hv7131gp_R_Value_t
//*
//* @return Returns \c HV7131GP_SUCCESS if no error occurs,
//*         otherwise a specific error code.
//*/
//hv7131gp_status_t hv7131gp_configure_resolution(hv7131gp_R_Value_t res);
//
///**
//* @brief Set a window on HV7131GP Camera.
//*
//* \param width		Width of image to read out
//* \param height		Height of image to read out
//* \param x		Column start address of image to read out
//* \param y		Row start address of image to read out
//*
//* @return Returns \c HV7131GP_SUCCESS if no error occurs,
//*         otherwise a specific error code.
//*/
//hv7131gp_status_t hv7131gp_window_set(int width, int height, int x, int y);
//
///**
//* @brief Configure HBLANK value via i2c
//*
//* \param hb		Effective HBLANK value to set. hb is represented like
//* 			2 8bit register and have to be bigger than 208
//*
//* @return Returns \c HV7131GP_SUCCESS if no error occurs,
//*         otherwise a specific error code.
//*/
//hv7131gp_status_t hv7131gp_hblank_set(int hb);
//
///**
//* @brief Configure VBLANK value via i2c
//*
//* \param vb		Effective VBLANK value to set. vb is represented like
//* 			2 8bit register and have to be bigger than 8
//*
//* @return Returns \c HV7131GP_SUCCESS if no error occurs,
//*         otherwise a specific error code.
//*/
//hv7131gp_status_t hv7131gp_vblank_set(int vb);
//
///**
//* @brief Configure windowing an resolution in safe mode on HV7131GP Camera.
//* "Safe mode" means the buffer size is checked with the maximum possible size
//* for specified hardware.
//*
//* \see MAX_SIZE_PIC_30
//*
//* \param width		Width of image to read out
//* \param height		Height of image to read out
//* \param x		Column start address of image to read out
//* \param y		Row start address of image to read out
//* \param res		Resolution value
//*
//* \see hv7131gp_R_Value_t
//*
//* @return Returns \c HV7131GP_SUCCESS if no error occurs,
//*         otherwise a specific error code.
//*/
//hv7131gp_status_t hv7131gp_configure_safe(int width, int height, int x, int y,
//					  hv7131gp_R_Value_t res);
//
///**
//* @brief Highest level configuration function where is possible to set a
//* quality value that correspond to a 160x120 resolution, variable time divisor,
//* fixed HBLAN (208) and fixed VBLANK(8)
//*
//*
//* \param Q		Quality value
//*
//* \see hv7131gp_Q_Value_t
//*
//* @return Returns \c HV7131GP_SUCCESS if no error occurs,
//*         otherwise a specific error code.
//*/
//hv7131gp_status_t hv7131gp_configure(hv7131gp_Q_Value_t Q);
//
///**
//* @brief Capture the first available frame HV7131GP Camera
//*
//* @param *image 			Pointer to a buffer.
//* @param (* func) (hv7131gp_status_t) 	Call-back function pointer called after a
//* frame is completely captured. This call-back function has to return a
//* hv7131gp_status_t value.
//*
//* @return Returns \c HV7131GP_SUCCESS if no error occurs,
//*         otherwise a specific error code.
//*/
//hv7131gp_status_t hv7131gp_capture(uint8_t *image, void (*func) (hv7131gp_status_t));
//
///**
//* @brief Write a HV7131GP Camera register
//*
//* @param reg Device register address
//* @param val Register value
//*
//* @return Returns \c HV7131GP_SUCCESS if no error occurs,
//*         otherwise a specific error code.
//*/
//hv7131gp_status_t hv7131gp_reg_write(hv7131gp_reg_t reg, uint8_t val);
//
///**
//* @brief Read a HV7131GP Camera register
//*
//* @param reg Device register address
//* @param val Register value
//*
//* @return Returns \c HV7131GP_SUCCESS if no error occurs,
//*         otherwise a specific error code.
//*/
//hv7131gp_status_t hv7131gp_reg_read(hv7131gp_reg_t reg, uint8_t *val);
//
///**
//* @brief Returns the image width
//*
//*
//* @return Returns \c uint8_t value that represent the number of pixel of
//* each row
//*/
//uint8_t hv7131gp_get_width(void);
//
///**
//* @brief Returns the image height
//*
//*
//* @return Returns \c uint8_t value that represent the number of pixel of
//* each column
//*/
//uint8_t hv7131gp_get_height(void);
//
///**
//* @brief Returns the image size
//*
//*
//* @return Returns \c uint16_t value that represent the number of pixel of an image.
//*/
//uint16_t hv7131gp_get_size(void);
//
///**
//* @brief Returns the luminance mean value
//*
//*
//* @return Returns \c uint8_t value that represent luminance mean value
//*/
//uint8_t hv7131gp_get_Y_average(void);
//
///**
//* @brief Set the camera to sleep mode. This function read
//* 		 the SCTRB register and set high the "Sleep mode" bit.
//*
//* @return Returns \c HV7131GP_SUCCESS if no error occurs,
//*         otherwise a specific error code.
//*/
//hv7131gp_status_t hv7131gp_set_sleep_status(void);
//
///**
//* @brief Set the camera to active mode. This function read
//* 		 the SCTRB register and set low the "Sleep mode" bit.
//*
//* @return Returns \c HV7131GP_SUCCESS if no error occurs,
//*         otherwise a specific error code.
//*/
//hv7131gp_status_t hv7131gp_set_active_status(void);

#endif //#ifndef __EE_CAMERA_HV7131GP__

#endif //#ifdef __USE_MICO32BOARD_CAMERA__
