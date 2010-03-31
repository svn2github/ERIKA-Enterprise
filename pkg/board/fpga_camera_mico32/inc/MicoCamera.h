#ifndef __MICO_CAMERA_HV7131GP__
#define __MICO_CAMERA_HV7131GP__

/* Camera controller registers */
typedef struct st_MicoCamera{
	volatile void* addr;
	volatile unsigned int state;
	volatile unsigned int flag;
    volatile unsigned int cntr1;
    volatile unsigned int cntr2;
    volatile unsigned int div;
}MicoCamera_t;

/* Camera controller bit masks */
#define MICO_CAM_IF_FLAG_MASK 		0x0001				/* bit 1 in FLAG register */
#define MICO_CAM_ERR_FLAG_MASK 		0x0002				/* bit 2 in FLAG register */
#define MICO_CAM_START_MASK			0x0001				/* bit 1 in CNTR1 register */
#define MICO_CAM_IFACK_MASK			0x0002				/* bit 2 in CNTR1 register */
#define MICO_CAM_RESET_MASK			0x0004				/* bit 3 in CNTR1 register */
#define MICO_CAM_ENABLE_IRQ_MASK	0x0001				/* bit 1 in CNTR2 register */

/* MICO CAMERA Macros */

//#define Mico_camera_read_address(cam)			(((MicoCamera_t*)cam)->addr)
__INLINE__ int __ALWAYS_INLINE__ Mico_camera_read_address(MicoCamera_t* cam)
{
	return cam->addr;	
}

//#define Mico_camera_write_address(cam, address)	(((MicoCamera_t*)cam)->addr = address)
__INLINE__ int __ALWAYS_INLINE__ Mico_camera_write_address(MicoCamera_t* cam, int address)
{
	cam->addr = address;
	return 0;	
}

//#define Mico_camera_read_status_register(cam)	(((MicoCamera_t*)cam)->state)
__INLINE__ int __ALWAYS_INLINE__ Mico_camera_read_status_register(MicoCamera_t* cam)
{
	return cam->state;
}

//#define Mico_camera_read_IF_flag(cam)			(((MicoCamera_t*)cam)->flag & MICO_CAM_IF_FLAG_MASK)
__INLINE__ int __ALWAYS_INLINE__ Mico_camera_read_IF_flag(MicoCamera_t* cam)
{
	return cam->flag & MICO_CAM_IF_FLAG_MASK;
}

//#define Mico_camera_read_ERR_flag(cam)			(((MicoCamera_t*)cam)->flag & MICO_CAM_ERR_FLAG_MASK)
__INLINE__ int __ALWAYS_INLINE__ Mico_camera_read_ERR_flag(MicoCamera_t* cam)
{
	return cam->flag & MICO_CAM_ERR_FLAG_MASK;
}

//#define Mico_camera_start(cam)					(((MicoCamera_t*)cam)->cntr1 = MICO_CAM_START_MASK)
__INLINE__ int __ALWAYS_INLINE__ Mico_camera_start(MicoCamera_t* cam)
{
	return cam->cntr1 = MICO_CAM_START_MASK;
}

//#define Mico_camera_clear_IRQ_flag(cam)			(((MicoCamera_t*)cam)->cntr1 = 0)
__INLINE__ int __ALWAYS_INLINE__ Mico_camera_clear_IRQ_flag(MicoCamera_t* cam)
{
	cam->cntr1 = 0;
	return 0;
}

//#define Mico_camera_reset(cam)					(((MicoCamera_t*)cam)->cntr1 = MICO_CAM_RESET_MASK)
__INLINE__ int __ALWAYS_INLINE__ Mico_camera_reset(MicoCamera_t* cam)
{
	cam->cntr1 = MICO_CAM_RESET_MASK;
	return 0;
}

//#define Mico_camera_enable_IRQ(cam)				(((MicoCamera_t*)cam)->cntr2 = MICO_CAM_ENABLE_IRQ_MASK)
__INLINE__ int __ALWAYS_INLINE__ Mico_camera_enable_IRQ(MicoCamera_t* cam)
{
	cam->cntr2 = MICO_CAM_ENABLE_IRQ_MASK;
	return 0;
}

//#define Mico_camera_disable_IRQ(cam)			(((MicoCamera_t*)cam)->cntr2 = 0)
__INLINE__ int __ALWAYS_INLINE__ Mico_camera_disable_IRQ(MicoCamera_t* cam)
{
	cam->cntr2 = 0;
	return 0;
}

//#define Mico_camera_IRQ_enabled(cam)			(((MicoCamera_t*)cam)->cntr2 & MICO_CAM_ENABLE_IRQ_MASK)
__INLINE__ int __ALWAYS_INLINE__ Mico_camera_IRQ_enabled(MicoCamera_t* cam)
{
	return cam->cntr2 & MICO_CAM_ENABLE_IRQ_MASK;
}

//#define Mico_camera_write_divisor(cam, divisor) (((MicoCamera_t*)cam)->div = divisor)
__INLINE__ int __ALWAYS_INLINE__ Mico_camera_write_divisor(MicoCamera_t* cam, int divisor)
{
	cam->div = divisor;
	return 0;
}

//#define Mico_camera_read_divisor(cam)			(((MicoCamera_t*)cam)->div)
__INLINE__ int __ALWAYS_INLINE__ Mico_camera_read_divisor(MicoCamera_t* cam)
{
	return cam->div;
}

//#define Mico_camera_frame_terminated(cam)		(((MicoCamera_t*)cam)->flag & MICO_CAM_IF_FLAG_MASK)
__INLINE__ int __ALWAYS_INLINE__ Mico_camera_frame_terminated(MicoCamera_t* cam)
{
	return cam->flag & MICO_CAM_IF_FLAG_MASK;
}

#endif //#ifndef __MICO_CAMERA_HV7131GP__
