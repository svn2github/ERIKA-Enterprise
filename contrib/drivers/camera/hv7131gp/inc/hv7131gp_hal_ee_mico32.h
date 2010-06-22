/*
Copyright (C) 2009, 2010 -  Claudio Salvadori and Christian Nastasi, Evidence Srl
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
  Name: hv7131gp_hal_ee_mico32.h
  Copyright: Evidence Srl
  Author: Dario Di Stefano
  Date: 29/03/10 18.28
  Description: camera driver hal for mico32.

  Modified by Bernardo  Dal Seno, 2010.
*/

#ifndef HV7131GP_HAL_EE_MICO32_H_
#define HV7131GP_HAL_EE_MICO32_H_

/* Required header files */
#include "hv7131gp_types.h"
#include "hv7131gp_reg.h"
#include <cpu/mico32/inc/ee_irq.h>
#include <MicoCamera.h>
/* Other used libraries: */
#include <mcu/mico32/inc/ee_i2c.h>

#ifdef __XP2_CAMERA_BOARD__
#include <board/fpga_camera_mico32/inc/ee_camera_hv7131gp.h>
#endif


/******************************************************************************/
/*                        Symbols and macros                                  */
/******************************************************************************/

/* Symbols and macros */
#define EE_HV7131GP_DEVICE_ID               (HV7131GP_DEVICE_ID)
#define EE_HV7131GP_ISR_MODE                (0x01)
#define EE_HV7131GP_POLLING_MODE            (0x00)
#define EE_hv7131gp_need_enable_int(mode)   (mode)

/* Default configuration */
#define EE_HV7131GP_DEFAULT_FORMAT          (HV7131GP_OUTFMT_DEFAULT & (~HV7131GP_8BIT_OUTPUT))
#define EE_HV7131GP_DEFAULT_DIVISOR         (HV7131GP_T_1)
#define EE_HV7131GP_DEFAULT_RESOLUTION      (HV7131GP_1_16_SUB)
#define EE_HV7131GP_DEFAULT_WIDTH           (640)
#define EE_HV7131GP_DEFAULT_HEIGTH          (480)
#define EE_HV7131GP_DEFAULT_COLUMN          (0x2)
#define EE_HV7131GP_DEFAULT_ROW             (0x2)
#define EE_HV7131GP_DEFAULT_VBLANK          (8)
#define EE_HV7131GP_DEFAULT_HBLANK          (208)
#define EE_HV7131GP_DEFAULT_FRAME_WIDTH     (160)
#define EE_HV7131GP_DEFAULT_FRAME_HEIGHT    (120)


/******************************************************************************/
/*                         Functions Prototypes                               */
/******************************************************************************/

/* Callback function called by camera driver handler  */
extern hv7131gp_cback_t *ee_hv7131gp_cbk;

/* Functions */
hv7131gp_status_t hv7131gp_hal_init_mico32(void);
#define hv7131gp_hal_init(x) hv7131gp_hal_init_mico32()
hv7131gp_status_t hv7131gp_hal_init_ack(void);
hv7131gp_status_t hv7131gp_i2c_hal_init(void);
hv7131gp_status_t hv7131gp_i2c_hal_reg_write(hv7131gp_reg_t reg, uint8_t  val);
hv7131gp_status_t hv7131gp_i2c_hal_reg_read(hv7131gp_reg_t reg, uint8_t *val);
#define hv7131gp_hal_capture(image, func) EE_hv7131gp_capture(image, func)

/* Macros for Camera functions */  
#define DECLARE_FUNC_HV7131GP(uc, lc) \
__INLINE__ void __ALWAYS_INLINE__ EE_hv7131gp_init(int irqmode){ \
    if(irqmode) \
        EE_hv7131gp_ISR_init((MicoCamera_t*)EE_BASE_ADD(uc), (int)EE_IRQ_NAME(uc)); \
    else \
        EE_hv7131gp_polling_init((MicoCamera_t*)EE_BASE_ADD(uc)); } \
__INLINE__ void* __ALWAYS_INLINE__ EE_camera_read_address(void){ \
    return Mico_camera_read_address((MicoCamera_t*)EE_BASE_ADD(uc)); } \
__INLINE__ void __ALWAYS_INLINE__ EE_camera_write_address(void* addr){ \
    Mico_camera_write_address((MicoCamera_t*)EE_BASE_ADD(uc),addr); } \
__INLINE__ int __ALWAYS_INLINE__ EE_camera_read_status_register(void) {\
    return Mico_camera_read_status_register((MicoCamera_t*)EE_BASE_ADD(uc)); } \
__INLINE__ int __ALWAYS_INLINE__ EE_camera_read_IF_flag(void){ \
    return Mico_camera_read_IF_flag((MicoCamera_t*)EE_BASE_ADD(uc)); } \
__INLINE__ int __ALWAYS_INLINE__ EE_camera_read_ERR_flag(void){ \
    return Mico_camera_read_ERR_flag((MicoCamera_t*)EE_BASE_ADD(uc)); } \
__INLINE__ void __ALWAYS_INLINE__ EE_camera_start(void){ \
    Mico_camera_start((MicoCamera_t*)EE_BASE_ADD(uc)); } \
__INLINE__ void __ALWAYS_INLINE__ EE_camera_clear_IRQ_flag(void){ \
    Mico_camera_clear_IRQ_flag((MicoCamera_t*)EE_BASE_ADD(uc)); } \
__INLINE__ void __ALWAYS_INLINE__ EE_camera_reset(void){ \
    Mico_camera_reset((MicoCamera_t*)EE_BASE_ADD(uc)); } \
__INLINE__ void __ALWAYS_INLINE__ EE_camera_enable_IRQ(void){ \
    Mico_camera_enable_IRQ((MicoCamera_t*)EE_BASE_ADD(uc)); } \
__INLINE__ void __ALWAYS_INLINE__ EE_camera_disable_IRQ(void){ \
    Mico_camera_disable_IRQ((MicoCamera_t*)EE_BASE_ADD(uc)); } \
__INLINE__ int __ALWAYS_INLINE__ EE_camera_IRQ_enabled(void){ \
    return Mico_camera_IRQ_enabled((MicoCamera_t*)EE_BASE_ADD(uc)); } \
__INLINE__ void __ALWAYS_INLINE__ EE_camera_write_divisor(unsigned int div){ \
    Mico_camera_write_divisor((MicoCamera_t*)EE_BASE_ADD(uc), div); } \
__INLINE__ int __ALWAYS_INLINE__ EE_camera_read_divisor(void){ \
    return Mico_camera_read_divisor((MicoCamera_t*)EE_BASE_ADD(uc)); } \
__INLINE__ int __ALWAYS_INLINE__ EE_camera_frame_terminated(void){ \
    return Mico_camera_frame_terminated((MicoCamera_t*)EE_BASE_ADD(uc)); }

/* Macros for I2C-based Camera functions */  
#define DECLARE_FUNC_I2C_HV7131GP(uc, lc) \
__INLINE__ int __ALWAYS_INLINE__ EE_hv7131gp_i2c_config(int baudrate,int settings){ \
    return cat3(EE_, lc, _config)(baudrate, settings); } \
__INLINE__ int __ALWAYS_INLINE__  EE_hv7131gp_i2c_write_byte(EE_UINT8 address, EE_UINT8 data){ \
    return cat3(EE_, lc, _send_byte)(EE_HV7131GP_DEVICE_ID, address, data); } \
__INLINE__ int __ALWAYS_INLINE__  EE_hv7131gp_i2c_write_buffer(EE_UINT8 address, EE_UINT8 *data, int len){ \
    return cat3(EE_, lc, _send_buffer)(EE_HV7131GP_DEVICE_ID, address, data, len); } \
__INLINE__ int __ALWAYS_INLINE__  EE_hv7131gp_i2c_read_byte(EE_UINT8 address){ \
    return cat3(EE_, lc, _receive_byte)(EE_HV7131GP_DEVICE_ID, address); } \
__INLINE__ int __ALWAYS_INLINE__  EE_hv7131gp_i2c_read_buffer(EE_UINT8 address, EE_UINT8 *data, int len){ \
    return cat3(EE_, lc, _receive_buffer)(EE_HV7131GP_DEVICE_ID, address, data, len); }

/* Camera initialization */
void EE_hv7131gp_ISR_init(MicoCamera_t* cam, int irqf);
void EE_hv7131gp_polling_init(MicoCamera_t* cam);

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
int EE_hv7131gp_capture(void *image, hv7131gp_cback_t *cam_cbk);

/* Set sleep mode */
int EE_hv7131gp_set_sleep_status(void);

/* Set active mode */
int EE_hv7131gp_set_active_status(void);

DECLARE_FUNC_I2C_HV7131GP(CAMERA_I2C, camera_i2c)
DECLARE_FUNC_HV7131GP(CAMERA, camera)

/* Set time divisor */
__INLINE__ int __ALWAYS_INLINE__  EE_hv7131gp_set_time_divisor(int div)
{
    return EE_hv7131gp_i2c_write_byte(HV7131GP_REG_SCTRB, div);
}

/* Set format */
__INLINE__ int __ALWAYS_INLINE__ EE_hv7131gp_set_format(EE_UINT8 val)
{
    //HV7131GP_OUTFMT_DEFAULT & (~HV7131GP_8BIT_OUTPUT)
    return EE_hv7131gp_i2c_write_byte(HV7131GP_REG_OUTFMT, val);
}

/* Get format */
__INLINE__ int __ALWAYS_INLINE__ EE_hv7131gp_get_format(void)
{
    //HV7131GP_OUTFMT_DEFAULT & (~HV7131GP_8BIT_OUTPUT)
    return EE_hv7131gp_i2c_read_byte(HV7131GP_REG_OUTFMT);
}

/* Set resolution */
__INLINE__ int __ALWAYS_INLINE__ EE_hv7131gp_set_resolution(EE_UINT8 val)
{
    //HV7131GP_REG_SCTRA, res | HV7131GP_X_FLIP
    return EE_hv7131gp_i2c_write_byte(HV7131GP_REG_SCTRA, val);
}

/* Get resolution */
__INLINE__ int __ALWAYS_INLINE__ EE_hv7131gp_get_resolution(void)
{
    //HV7131GP_REG_SCTRA, res | HV7131GP_X_FLIP
    return EE_hv7131gp_i2c_read_byte(HV7131GP_REG_SCTRA);
}

/* Get Y average */
__INLINE__ int __ALWAYS_INLINE__ EE_hv7131gp_get_Y_average(void)
{
    return EE_hv7131gp_i2c_read_byte(HV7131GP_REG_YFMEAN);
}

void EE_hv7131gp_handler(int level);
#ifndef __STATIC_ISR_TABLE__
__INLINE__ void __ALWAYS_INLINE__ EE_hal_hv7131gp_handler_setup(int irqf)
{
    /* Register IRQ handler */
    EE_mico32_register_ISR(irqf, EE_hv7131gp_handler);
}
#else // __STATIC_ISR_TABLE__
__INLINE__ void __ALWAYS_INLINE__ EE_hal_hv7131gp_handler_setup(int irqf)
{
    /* Just unmask the IRQ */
    mico32_enable_irq(irqf);
}
#endif // __STATIC_ISR_TABLE__

/******************************************************************************/
/*                           Hardware Abstraction Layer                       */
/******************************************************************************/
#define HV7131GP_HAL_DRIVING_PINS           0

/* Effectively disable hv7131gp_configure_safe(), which is not safe enough to
 * do check the actual buffer size */
#define HV7131GP_MAX_SIZE   0


/*  For compatibility with other HALs that deal with low-level details */

#define HV7131GP_PIN_ENABLE_INIT()
#define HV7131GP_PIN_ENABLE_HIGH()
#define HV7131GP_PIN_EOF_INIT() 
#define HV7131GP_PIN_MCLK_INIT(p)
#define HV7131GP_PIN_MCLK_START()
#define HV7131GP_PIN_RESETB_INIT()
#define HV7131GP_PIN_RESETB_HIGH()
#define HV7131GP_PIN_RESETB_LOW()
#define HV7131GP_PIN_HSYNC_INIT()
#define HV7131GP_PIN_VCLK_INIT()
#define HV7131GP_PIN_VSYNC_INIT_POSITIVE()
#define HV7131GP_PIN_Y_INIT()   
#define HV7131GP_VSYNC_RESET_IF()
#define HV7131GP_VSYNC_IF_VALUE 1
#define HV7131GP_MORE_THAN_1_MS                 0
#define HV7131GP_MORE_THAN_4_MCLK_CYCLES        0
#define HV7131GP_MORE_THAN_2086000_MCLK_CYCLES  0
#define hv7131gp_hal_delay_us(x)  INVALID_ASM_INSTR



#endif /* HV7131GP_HAL_EE_MICO32_H_ */
