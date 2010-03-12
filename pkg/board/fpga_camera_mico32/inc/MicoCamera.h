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
#define Mico_camera_read_address(cam)			{cam->addr}
#define Mico_camera_write_address(cam, addr)	{cam->addr = addr;}
#define Mico_camera_read_status_register(cam)	{cam->state}
#define Mico_camera_read_IF_flag(cam)			{cam->flag & MICO_CAM_IF_FLAG_MASK}
#define Mico_camera_read_ERR_flag(cam)			{cam->flag & MICO_CAM_ERR_FLAG_MASK}
#define Mico_camera_start(cam)					{cam->cntr1 = MICO_CAM_START_MASK;}
#define Mico_camera_clear_IRQ_flag(cam)			{cam->cntr1 = 0;}
#define Mico_camera_reset(cam)					{cam->cntr1 = MICO_CAM_RESET_MASK;}
#define Mico_camera_enable_IRQ(cam)				{cam->cntr2 = MICO_CAM_ENABLE_IRQ_MASK;}
#define Mico_camera_disable_IRQ(cam)			{cam->cntr2 = 0;}
#define Mico_camera_IRQ_enabled(cam)			{cam->cntr2 & MICO_CAM_ENABLE_IRQ_MASK}
#define Mico_camera_write_divisor(cam, div)		{cam->div = div;}
#define Mico_camera_read_divisor(cam)			{cam->div}
#define Mico_camera_frame_terminated(cam)		{cam->flag & MICO_CAM_IF_FLAG_MASK}

#endif //#ifndef __MICO_CAMERA_HV7131GP__
