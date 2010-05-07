/*
  Name: ee_camera_hv7131gp.h
  Copyright: Evidence Srl
  Author: Dario Di Stefano
  Date: 29/03/10 18.28
  Description: hv7131gp camera header file for MICO32 CAMERA board. 
*/

#ifndef __EE_CAMERA_HV7131GP__
#define __EE_CAMERA_HV7131GP__

/* Board dependent macros */
// void

#if(0)

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

#endif // #if(0)

#endif //#ifndef __EE_CAMERA_HV7131GP__


