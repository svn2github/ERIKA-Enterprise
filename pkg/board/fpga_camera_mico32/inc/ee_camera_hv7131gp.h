#ifdef __USE_MICO32BOARD_CAMERA_HV7131GP__

#ifndef __EE_CAMERA_HV7131GP__
#define __EE_CAMERA_HV7131GP__

/* Camera header files */
#include "board/fpga_camera_mico32/inc/ee_camera_hv7131gp_reg.h"
#include "cpu/mico32/inc/ee_internal.h"
#include "mcu/mico32/inc/ee_internal.h"
#include <cpu/mico32/inc/ee_irq.h>
#include <MicoCamera.h>
/* Other used libraries: */
#include "mcu/mico32/inc/ee_i2c.h"

/* Callback function called by camera driver handler  */
extern EE_ISR_callback ee_hv7131gp_cbk;

/* Symbols and macros */
#define EE_HV7131GP_DEVICE_ID				(HV7131GP_DEVICE_ID)
#define EE_HV7131GP_ISR_MODE				(0x01)
#define EE_HV7131GP_POLLING_MODE			(0x00)
#define EE_hv7131gp_need_enable_int(mode)	(mode)

/* Default configuration */
#define EE_HV7131GP_DEFAULT_FORMAT			(HV7131GP_OUTFMT_DEFAULT & (~HV7131GP_8BIT_OUTPUT))
#define EE_HV7131GP_DEFAULT_DIVISOR 		(HV7131GP_T_1)
#define EE_HV7131GP_DEFAULT_RESOLUTION 		(HV7131GP_1_16_SUB)
#define EE_HV7131GP_DEFAULT_WIDTH 			(640)
#define EE_HV7131GP_DEFAULT_HEIGTH 			(480)
#define EE_HV7131GP_DEFAULT_COLUMN 			(0x2)
#define EE_HV7131GP_DEFAULT_ROW 			(0x2)
#define EE_HV7131GP_DEFAULT_VBLANK			(8)
#define EE_HV7131GP_DEFAULT_HBLANK			(208)
#define EE_HV7131GP_DEFAULT_FRAME_WIDTH		(160)
#define EE_HV7131GP_DEFAULT_FRAME_HEIGHT	(120)

/* Exit status for the EE_CAMERA driver 
	(see EE_CAMERA_init EE_CAMERA_configure EE_CAMERA_capture EE_CAMERA_reg_write EE_CAMERA_reg_read)
*/
#define	HV7131GP_SUCCESS 					(0)		/**< No error */
#define	HV7131GP_FAILURE					(-19)	/**< Generic error */
#define	HV7131GP_ERR_I2C_INIT				(-20)	/**< I2C bus initialization error */
#define	HV7131GP_ERR_I2C_READ				(-21)	/**< I2C bus read error */
#define	HV7131GP_ERR_I2C_WRITE				(-22)	/**< I2C bus write error */
#define	HV7131GP_ERR_DEV_NOINIT				(-23)	/**< Device is not initialized */
#define	HV7131GP_ERR_MEM_NULL				(-24)	/**< Invalid NULL memory address */

/* Resolution value */
#define	HV7131GP_NO_SUB  					(HV7131GP_VIDEO_NORMAL)		/**< 640x480 pixel resolution*/
#define	HV7131GP_1_4_SUB					(HV7131GP_VIDEO_SUB_4)		/**< 320x240 pixel resolution*/
#define	HV7131GP_1_16_SUB					(HV7131GP_VIDEO_SUB_16)		/**< 160x120 pixel resolution */

/* Time divisor */
#define	HV7131GP_T_1  						(HV7131GP_DCF_1)		/**< Divide MCLK for 1 */
#define	HV7131GP_T_2						(HV7131GP_DCF_2)		/**< Divide MCLK for 2 */
#define	HV7131GP_T_3						(HV7131GP_DCF_4)		/**< Divide MCLK for 4 */
#define	HV7131GP_T_4						(HV7131GP_DCF_8)		/**< Divide MCLK for 8 */
#define	HV7131GP_T_5						(HV7131GP_DCF_16)		/**< Divide MCLK for 16 */
#define	HV7131GP_T_6						(HV7131GP_DCF_32)		/**< Divide MCLK for 32 */
#define	HV7131GP_T_7						(HV7131GP_DCF_64)		/**< Divide MCLK for 64 */
#define	HV7131GP_T_8						(HV7131GP_DCF_128)		/**< Divide MCLK for 128 */

/* Quality value (high level) */
#define	HV7131GP_160x120_FAST  				(HV7131GP_T_2)		/**< 160x120 + T2 divisor*/
#define	HV7131GP_160x120_MEDIUM				(HV7131GP_T_5)		/**< 160x120 + T5 divisor*/
#define	HV7131GP_160x120_SLOW				(HV7131GP_T_8)		/**< 160x120 + T8 divisor */

/* -------------------------------- CAMERA driver API -------------------------------------- */

/* Macros for Camera functions */  
#define DECLARE_FUNC_HV7131GP(uc, lc) \
__INLINE__ int __ALWAYS_INLINE__ EE_hv7131gp_init(int mode){ \
	if(mode) \
		return EE_hv7131gp_ISR_init((MicoCamera_t*)EE_BASE_ADD(uc), (int)EE_IRQ_NAME(uc)); \
	else \
		return EE_hv7131gp_polling_init((MicoCamera_t*)EE_BASE_ADD(uc)); } \
__INLINE__ void* __ALWAYS_INLINE__ EE_camera_read_address(void){ \
	return (void *)Mico_camera_read_address(EE_BASE_ADD(uc)); } \
__INLINE__ void __ALWAYS_INLINE__ EE_camera_write_address(void* addr){ \
	Mico_camera_write_address(EE_BASE_ADD(uc),addr); } \
__INLINE__ int __ALWAYS_INLINE__ EE_camera_read_status_register(void) {\
	return Mico_camera_read_status_register(EE_BASE_ADD(uc)); } \
__INLINE__ int __ALWAYS_INLINE__ EE_camera_read_IF_flag(void){ \
	return Mico_camera_read_IF_flag(EE_BASE_ADD(uc)); } \
__INLINE__ int __ALWAYS_INLINE__ EE_camera_read_ERR_flag(void){ \
	return Mico_camera_read_ERR_flag(EE_BASE_ADD(uc)); } \
__INLINE__ void __ALWAYS_INLINE__ EE_camera_start(void){ \
	Mico_camera_start(EE_BASE_ADD(uc)); } \
__INLINE__ void __ALWAYS_INLINE__ EE_camera_clear_IRQ_flag(void){ \
	Mico_camera_clear_IRQ_flag(EE_BASE_ADD(uc)); } \
__INLINE__ void __ALWAYS_INLINE__ EE_camera_reset(void){ \
	Mico_camera_reset(EE_BASE_ADD(uc)); } \
__INLINE__ void __ALWAYS_INLINE__ EE_camera_enable_IRQ(void){ \
	Mico_camera_enable_IRQ(EE_BASE_ADD(uc)); } \
__INLINE__ void __ALWAYS_INLINE__ EE_camera_disable_IRQ(void){ \
	Mico_camera_disable_IRQ(EE_BASE_ADD(uc)); } \
__INLINE__ int __ALWAYS_INLINE__ EE_camera_IRQ_enabled(void){ \
	return Mico_camera_IRQ_enabled(EE_BASE_ADD(uc)); } \
__INLINE__ void __ALWAYS_INLINE__ EE_camera_write_divisor(unsigned int div){ \
	Mico_camera_write_divisor(EE_BASE_ADD(uc), div); } \
__INLINE__ int __ALWAYS_INLINE__ EE_camera_read_divisor(void){ \
	return Mico_camera_read_divisor(EE_BASE_ADD(uc)); } \
__INLINE__ int __ALWAYS_INLINE__ EE_camera_frame_terminated(void){ \
	return Mico_camera_frame_terminated(EE_BASE_ADD(uc)); }

/* Macros for I2C-based Camera functions */  
#define DECLARE_FUNC_I2C_HV7131GP(uc, lc) \
__INLINE__ int __ALWAYS_INLINE__ EE_hv7131gp_i2c_config(int baudrate,int settings){ \
	return cat3(EE_, lc, _config)(baudrate, settings); } \
__INLINE__ int __ALWAYS_INLINE__  EE_hv7131gp_write_byte(EE_UINT8 address, EE_UINT8 data){ \
	return cat3(EE_, lc, _send_byte)(EE_HV7131GP_DEVICE_ID, address, data); } \
__INLINE__ int __ALWAYS_INLINE__  EE_hv7131gp_write_buffer(EE_UINT8 address, EE_UINT8 *data, int len){ \
	return cat3(EE_, lc, _send_buffer)(EE_HV7131GP_DEVICE_ID, address, data, len); } \
__INLINE__ int __ALWAYS_INLINE__  EE_hv7131gp_read_byte(EE_UINT8 address){ \
	return cat3(EE_, lc, _receive_byte)(EE_HV7131GP_DEVICE_ID, address); } \
__INLINE__ int __ALWAYS_INLINE__  EE_hv7131gp_read_buffer(EE_UINT8 address, EE_UINT8 *data, int len){ \
	return cat3(EE_, lc, _receive_buffer)(EE_HV7131GP_DEVICE_ID, address, data, len); }

/* Camera initialization */
int EE_hv7131gp_ISR_init(MicoCamera_t* cam, int irqf);
int EE_hv7131gp_polling_init(MicoCamera_t* cam);

/* Set configuration */
int EE_hv7131gp_set_configuration(int div, int fmt, int res, int w, int h, int x, int y, int hb, int vb);

/* Set default configuration */
int EE_hv7131gp_set_default_configuration(void);

/* Set width */
int EE_hv7131gp_set_width(int width);

/* Get width */
int EE_hv7131gp_get_width(void);

/* Set height */
int EE_hv7131gp_set_height(int height);

/* Get height */
int EE_hv7131gp_get_height(void);

/* Get size */
int EE_hv7131gp_get_size(void);

/* Set x position */
int EE_hv7131gp_set_xpos(int x);

/* Get x position */
int EE_hv7131gp_get_xpos(void);

/* Set y position */
int EE_hv7131gp_set_ypos(int y);

/* Get y position */
int EE_hv7131gp_get_ypos(void);

/* Set hblank */
int EE_hv7131gp_set_hblank(int hb);

/* Get hblank */
int EE_hv7131gp_get_hblank(void);

/* Set vblank */
int EE_hv7131gp_set_vblank(int vb);

/* Get vblank */
int EE_hv7131gp_get_vblank(void);

/* Set window */
int EE_hv7131gp_set_window(int width, int height, int x, int y);

/* Capture an image */
int EE_hv7131gp_capture(void *image, EE_ISR_callback cam_cbk);

/* Set sleep mode */
int EE_hv7131gp_set_sleep_status(void);

/* Set active mode */
int EE_hv7131gp_set_active_status(void);

/* Camera API functions */
#ifdef __EE_HV7131GP_USE_I2C1__
	#ifdef __EE_HV7131GP_USE_I2C2__
	#error HV7131GP cannot support both i2c controllers
	#endif
	DECLARE_FUNC_I2C_HV7131GP(EE_I2C1_NAME_UC, EE_I2C1_NAME_LC)
#else //__EE_RTC_USE_I2C1__
	DECLARE_FUNC_I2C_HV7131GP(EE_I2C2_NAME_UC, EE_I2C2_NAME_LC)
#endif //__EE_RTC_USE_I2C1__
DECLARE_FUNC_HV7131GP(EE_CAMCTRL_MASTER_SLAVE_NAME_UC, EE_CAMCTRL_MASTER_SLAVE_NAME_LC)

/* Set time divisor */
__INLINE__ int __ALWAYS_INLINE__  EE_hv7131gp_set_time_divisor(int div)
{
	return EE_hv7131gp_write_byte(HV7131GP_REG_SCTRB, div);
}

/* Set format */
__INLINE__ int __ALWAYS_INLINE__ EE_hv7131gp_set_format(EE_UINT8 val)
{
	//HV7131GP_OUTFMT_DEFAULT & (~HV7131GP_8BIT_OUTPUT)
	return EE_hv7131gp_write_byte(HV7131GP_REG_OUTFMT, val);
}

/* Get format */
__INLINE__ int __ALWAYS_INLINE__ EE_hv7131gp_get_format(void)
{
	//HV7131GP_OUTFMT_DEFAULT & (~HV7131GP_8BIT_OUTPUT)
	return EE_hv7131gp_read_byte(HV7131GP_REG_OUTFMT);
}

/* Set resolution */
__INLINE__ int __ALWAYS_INLINE__ EE_hv7131gp_set_resolution(EE_UINT8 val)
{
	//HV7131GP_REG_SCTRA, res | HV7131GP_X_FLIP
	return EE_hv7131gp_write_byte(HV7131GP_REG_SCTRA, val);
}

/* Get resolution */
__INLINE__ int __ALWAYS_INLINE__ EE_hv7131gp_get_resolution(void)
{
	//HV7131GP_REG_SCTRA, res | HV7131GP_X_FLIP
	return EE_hv7131gp_read_byte(HV7131GP_REG_SCTRA);
}
/* Get Y average */
__INLINE__ int __ALWAYS_INLINE__ EE_hv7131gp_get_Y_average(void)
{
	return EE_hv7131gp_read_byte(HV7131GP_REG_YFMEAN);
}

/*---------------------------------------------------------------------------*/
/* Macros, types and functions added for compatibility */
typedef int hv7131gp_reg_t;
typedef int hv7131gp_status_t;
typedef int hv7131gp_R_Value_t;
typedef int hv7131gp_T_D_Value_t;
typedef int hv7131gp_Q_Value_t;

#define hv7131gp_configure_resolution(res)  	EE_hv7131gp_set_resolution(res)
#define hv7131gp_configure_time_divisor(div)	EE_hv7131gp_set_time_divisor(div)
#define hv7131gp_set_sleep_status()				EE_hv7131gp_set_sleep_status()
#define hv7131gp_set_active_status()			EE_hv7131gp_set_active_status()
#define hv7131gp_hblank_set(hb)					EE_hv7131gp_set_hblank(hb)
#define hv7131gp_vblank_set(vb)					EE_hv7131gp_set_vblank(vb)
#define hv7131gp_window_set(w,h,x,y)			EE_hv7131gp_set_window(w, h, x, y)
#define hv7131gp_reg_write(reg,val)				EE_hv7131gp_write_byte(reg, val)		
#define hv7131gp_get_Y_average()				EE_hv7131gp_get_Y_average()
#define hv7131gp_get_width()					EE_hv7131gp_get_width()
#define hv7131gp_get_height()					EE_hv7131gp_get_height()
#define hv7131gp_get_size()						EE_hv7131gp_get_size()
#define hv7131gp_capture(add, cbk)				EE_hv7131gp_capture(add, cbk)
#define hv7131gp_configure(div)					EE_hv7131gp_set_configuration(div, EE_HV7131GP_DEFAULT_FORMAT,\
												EE_HV7131GP_DEFAULT_RESOLUTION, EE_HV7131GP_DEFAULT_WIDTH,\
												EE_HV7131GP_DEFAULT_HEIGTH, EE_HV7131GP_DEFAULT_COLUMN,\
												EE_HV7131GP_DEFAULT_ROW, EE_HV7131GP_DEFAULT_HBLANK, EE_HV7131GP_DEFAULT_VBLANK)

__INLINE__ int __ALWAYS_INLINE__ hv7131gp_init(void)
{
	EE_hv7131gp_init(EE_HV7131GP_ISR_MODE);
	return EE_hv7131gp_set_default_configuration();
}

//__INLINE__ int __ALWAYS_INLINE__ hv7131gp_get_fdh(void)
//{
//	return 0;
//}
//
//__INLINE__ int __ALWAYS_INLINE__ hv7131gp_get_fdl(void)
//{
//	return 0;
//}
//
//__INLINE__ int __ALWAYS_INLINE__ hv7131gp_get_fl(void)
//{
//	return 0;
//}

#endif //#ifndef __EE_CAMERA_HV7131GP__

#endif //#ifdef __USE_MICO32BOARD_CAMERA_HV7131GP__
