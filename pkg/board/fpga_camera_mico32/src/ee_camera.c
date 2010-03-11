/*
	RT-Clock library functions
*/

#ifdef __USE_MICO32BOARD_CAMERA__

#include "board/fpga_camera_mico32/inc/ee_camera.h"

/* Global variables */
EE_camera_callback ee_cam_cbk;

/* ---------------------- CAMERA interrupt handler ------------------------- */

void EE_camera_handler(int level)
{
	EE_camera_clear_IRQ_flag();
	
	if(ee_cam_cbk != (EE_camera_callback)NULL)
		ee_cam_cbk();

	return;
}



/* ---------------------- CAMERA Library functions ------------------------- */

/* Camera initialization */
int EE_hal_camera_init(Camera_t* cam, int irqf, int mode)
{
	EE_hal_camera_reset(cam);
	
	if(EE_camera_need_enable_int(mode))
	{
		EE_mico32_register_ISR(irqf, EE_camera_handler);
		mico32_enable_irq(irqf);
		EE_camera_enable_IRQ();
	}
	else
	{
		mico32_disable_irq(irqf);
		EE_mico32_unregister_ISR(irqf);
		EE_camera_disable_IRQ();
	}
	
	return EE_CAMERA_SUCCESS;
}

/* Set default configuration */
int EE_camera_set_default_configuration(void)
{
	int ret;
	
	//Time division: 16
	ret = EE_camera_set_time_divisor(EE_CAMERA_DEFAULT_DIVISOR);
	if (ret != EE_CAMERA_SUCCESS)
		return ret;
	// Output format
	ret = EE_camera_set_format(HV7131GP_OUTFMT_DEFAULT & (~HV7131GP_8BIT_OUTPUT));
	if (ret != EE_CAMERA_SUCCESS)
		return ret;
	//Resolution: 160x120
	ret = EE_camera_set_resolution(EE_CAMERA_DEFAULT_RESOLUTION);
	if (ret != EE_CAMERA_SUCCESS)
		return ret;
	//Full window
	ret = EE_camera_set_window(EE_CAMERA_DEFAULT_WIDTH, EE_CAMERA_DEFAULT_HEIGTH, 
								EE_CAMERA_DEFAULT_COLUMN, EE_CAMERA_DEFAULT_ROW);
	if (ret != EE_CAMERA_SUCCESS)
		return ret;
	//VBLANK: 8
	ret = EE_camera_set_vblank(EE_CAMERA_DEFAULT_VBLANK);
	if (ret != EE_CAMERA_SUCCESS)
		return ret;
	//HBLANK: 208
	ret = EE_camera_set_hblank(EE_CAMERA_DEFAULT_HBLANK);

	return ret;
}

/* Set configuration */
int EE_camera_set_configuration(int div, int fmt, int res, int w, int h, int x, int y, int hb, int vb)	// to do... aggiungere più parametri...
{
	int ret;

	// Set time divisor 
	ret = EE_camera_set_time_divisor(div);
	if (ret != EE_CAMERA_SUCCESS)
			return ret;
	// Output format
	ret = EE_camera_set_format(fmt);
	if (ret != EE_CAMERA_SUCCESS)
		return ret;
	// Set 1:16 subsampling and X-Flip
	ret = EE_camera_set_resolution(res);
	if (ret != EE_CAMERA_SUCCESS)
		return ret;
	// Set complete window 
	ret = EE_camera_set_window(w, h, x, y);
	if (ret != EE_CAMERA_SUCCESS)
		return ret;
	// Set HBLANK values
	ret = EE_camera_set_hblank(hb);
	if (ret != EE_CAMERA_SUCCESS)
		return ret;
	// Set VBLANK values
	ret = EE_camera_set_vblank(vb);

	return ret;
}

/* Set width */
int EE_camera_set_width(int width)
{
	int ret;
	
	if( width > 0x280 ) return EE_CAMERA_FAILURE;
	
	ret = EE_camera_write_byte(HV7131GP_REG_WIWH, (width >> 8) & (0x00FF));
	if (ret != EE_CAMERA_SUCCESS) 
		return ret;
	ret = EE_camera_write_byte(HV7131GP_REG_WIWL, width & (0x00FF));
	
	return ret;
}

/* Get width */
int EE_camera_get_width(int *widthp)
{
	int ret;
	
	ret = EE_camera_read_byte(HV7131GP_REG_WIWH);
	if (ret < 0) 
		return ret;
	*widthp = (ret & 0x00FF)<<8;	
	
	ret = EE_camera_read_byte(HV7131GP_REG_WIWL);
	if (ret < 0) 
		return ret;
	
	*widthp = *widthp + (ret & 0x00FF);
	
	return ret;
}

/* Set height */
int EE_camera_set_height(int height)
{
	int ret;
	
	//Check the window size: a window have to be smaller size than 640x480
	if( height > 0x1E0 ) return EE_CAMERA_FAILURE;
	
	ret = EE_camera_write_byte(HV7131GP_REG_WIHH, (height >> 8) & (0x00FF));
	if (ret != EE_CAMERA_SUCCESS) 
		return ret;	
	ret = EE_camera_write_byte(HV7131GP_REG_WIHL, height & (0x00FF));
	
	return ret;
}

/* Get height */
int EE_camera_get_height(int *heightp)
{
	int ret;
	
	ret = EE_camera_read_byte(HV7131GP_REG_WIHH);
	if (ret < 0) 
		return ret;
	*heightp = (ret & 0x00FF)<<8;	

	ret = EE_camera_read_byte(HV7131GP_REG_WIHL);
	if (ret < 0) 
		return ret;
	
	*heightp = *heightp + (ret & 0x00FF);
	
	return ret;
}

/* Set x position */
int EE_camera_set_xpos(int x)
{
	int ret;
	
	//Check the window position: inferior limit
	if( (x < 0x2) || (x > 0x280) ) return EE_CAMERA_FAILURE;
	
	ret = EE_camera_write_byte(HV7131GP_REG_CSAH, (x >> 8) & (0x00FF));
	if (ret != EE_CAMERA_SUCCESS) 
		return ret;
	ret = EE_camera_write_byte(HV7131GP_REG_CSAL, x & (0x00FF));
	
	return ret;
}

/* Get x position */
int EE_camera_get_xpos(int *xp)
{
	int ret;
	
	ret = EE_camera_read_byte(HV7131GP_REG_CSAH);
	if (ret < 0) 
		return ret;
	*xp = (ret & 0x00FF)<<8;	

	ret = EE_camera_read_byte(HV7131GP_REG_CSAL);
	if (ret < 0) 
		return ret;
	
	*xp = *xp + (ret & 0x00FF);
	
	return ret;
}

/* Set y position */
int EE_camera_set_ypos(int y)
{
	int ret;
	
	//Check the window position: superior limit
	if( (y < 0x2) || (y > 0x1E0) ) return EE_CAMERA_FAILURE;
	
	ret = EE_camera_write_byte(HV7131GP_REG_RSAH, (y >> 8) & (0x00FF));
	if (ret != EE_CAMERA_SUCCESS) 
		return ret;
	ret = EE_camera_write_byte(HV7131GP_REG_RSAL, y & (0x00FF));
	
	return ret;
}

/* Get y position */
int EE_camera_get_ypos(int *yp)
{
	int ret;
	
	ret = EE_camera_read_byte(HV7131GP_REG_RSAH);
	if (ret < 0) 
		return ret;
	*yp = (ret & 0x00FF)<<8;	

	ret = EE_camera_read_byte(HV7131GP_REG_RSAL);
	if (ret < 0) 
		return ret;
	
	*yp = *yp + (ret & 0x00FF);
	
	return ret;
}

/* Set hblank */
int EE_camera_set_hblank(int hb)
{
	int ret;

	//hb check
	if (hb < 208 || hb > 65535) return EE_CAMERA_FAILURE;
	
	ret = EE_camera_write_byte(HV7131GP_REG_HBLANKH, (hb >> 8) & (0x00FF));
	if (ret != EE_CAMERA_SUCCESS)
		return ret;
	ret = EE_camera_write_byte(HV7131GP_REG_HBLANKL, hb & (0x00FF));
	
	return ret;
}

/* Get hblank */
int EE_camera_get_hblank(int *hbp)
{
	int ret;
	
	ret = EE_camera_read_byte(HV7131GP_REG_HBLANKH);
	if (ret < 0) 
		return ret;
	*hbp = (ret & 0x00FF)<<8;	

	ret = EE_camera_read_byte(HV7131GP_REG_HBLANKL);
	if (ret < 0) 
		return ret;
	
	*hbp = *hbp + (ret & 0x00FF);
	
	return ret;
}

/* Set vblank */
int EE_camera_set_vblank(int vb)
{
	int ret;

	//vb check
	if (vb < 8 || vb > 65535) return EE_CAMERA_FAILURE;

	ret = EE_camera_write_byte(HV7131GP_REG_VBLANKH, (vb >> 8) & (0x00FF));
	if (ret != EE_CAMERA_SUCCESS)
		return ret;
	
	ret = EE_camera_write_byte(HV7131GP_REG_VBLANKL, vb & (0x00FF));

	return ret;
}

/* Get vblank */
int EE_camera_get_vblank(int *vbp)
{
	int ret;
	
	ret = EE_camera_read_byte(HV7131GP_REG_VBLANKH);
	if (ret < 0) 
		return ret;
	*vbp = (ret & 0x00FF)<<8;	

	ret = EE_camera_read_byte(HV7131GP_REG_VBLANKL);
	
	
	*vbp = *vbp + (ret & 0x00FF);
	
	return ret;
}

/* Set window */
int EE_camera_set_window(int width, int height, int x, int y)
{
	int ret;
	
	ret = EE_camera_set_width(width);
	if (ret != EE_CAMERA_SUCCESS)
		return ret;
		
	ret = EE_camera_set_height(height);
	if (ret != EE_CAMERA_SUCCESS)
		return ret;
	
	ret = EE_camera_set_xpos(x);
	if (ret != EE_CAMERA_SUCCESS)
		return ret;
		
	ret = EE_camera_set_ypos(y);
	if (ret != EE_CAMERA_SUCCESS)
		return ret;

	return ret;
}

/* Capture an image */
int EE_camera_capture(void *image, EE_camera_callback cam_cbk)
{
	if (image == NULL)
		return EE_CAMERA_ERR_MEM_NULL;

	EE_camera_write_address(image);
	//EE_camera_enable_IRQ();
	ee_cam_cbk = cam_cbk;
	EE_camera_start();
	
    return EE_CAMERA_SUCCESS;
}

/* Set sleep mode */
int EE_camera_set_sleep_status(void)
{
	int ret = 0;
	
	ret = EE_camera_read_byte(HV7131GP_REG_SCTRB);
	if(ret < 0)
		return ret;
	
	ret = EE_camera_write_byte(HV7131GP_REG_SCTRB, ret | HV7131GP_SLEEP_MODE);
	
	return ret;
}

/* Set active mode */
int EE_camera_set_active_status(void)
{
	int ret = 0;
	
	ret = EE_camera_read_byte(HV7131GP_REG_SCTRB);
	if(ret < 0)
		return ret;
	
	ret = EE_camera_write_byte(HV7131GP_REG_SCTRB, ret & (~HV7131GP_SLEEP_MODE));
	
	return ret;
}

#endif //#ifdef __USE_MICO32BOARD_CAMERA__
