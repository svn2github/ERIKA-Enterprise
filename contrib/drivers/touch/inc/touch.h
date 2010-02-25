#ifndef __TOUCH_H__
#define __TOUCH_H__

#define __FOUR_WIRES__
#define __LOW_LEVEL_MEASUREMENT__

#include<touch_compiler.h>
#include<touch_hal.h>
#include<touch_kal.h>

#define TOUCH_X_AXIS	0
#define TOUCH_Y_AXIS	1

// Measurement Settings
#define SAMPLES_FOR_ONE_TRUE_XY_PAIR    5             // Number of Measurements for one true X/Y-Coordinate
#define END_OF_ARRAY                    SAMPLES_FOR_ONE_TRUE_XY_PAIR-1
#define MEDIAN                          (SAMPLES_FOR_ONE_TRUE_XY_PAIR-1)/2      // odd-numbered: SAMPLES_FOR_ONE_TRUE_XY_PAIR
#define MAXIMUM_LOW_LEVEL		1000          // Invalid Measurement for Low_Level > MAXIMUM_LOW_LEVEL
#define RTOUCH_MAXIMUM_LEVEL		4000
#define MAXIMUM_UNTOUCH_CONDITIONS	100           // Number of (successive) Invalid Measurements till Untouch Condition
#define SLEEP_COUNTDOWN			2000

#define TOUCH_ACTIVATION_TIME		2000

#define TOUCH_ERROR_NONE		0
#define TOUCH_ERROR_WRONG_AXIS		-1
#define TOUCH_ERROR_RAW_NOT_READY 	-2
#define TOUCH_ERROR_NOT_TUNED		-3
#define TOUCH_CONFIGURED		0
#define TOUCH_NOT_CONFIGURED		-1

/****************************************************************************
  Type definition
****************************************************************************/

typedef struct {
	unsigned STANDBY:1;
	unsigned XPOS:1;
	unsigned YPOS:1;
	unsigned Z1MEAS:1;
	unsigned Z2MEAS:1;
	unsigned UNDEF1:1;
	unsigned UNDEF2:1;
	unsigned COMPLETE:1;
} TouchFlow;

typedef struct {
	EE_UINT16 xt1;
	EE_UINT16 yt1; 
	EE_UINT16 xt2;
	EE_UINT16 yt2;
	EE_UINT16 xt3;
	EE_UINT16 yt3;	
} tune_raw_t;

typedef struct {
	double a;
	double b;
	double c;
	double d;
	double e;
	double f;
} tune_t;

/****************************************************************************
  Function definitions
****************************************************************************/

EE_INT8 touch_poll_raw_position(EE_UINT16 *,EE_UINT16 *);
void touch_wait_raw_position(EE_UINT16 *, EE_UINT16 *);
EE_INT8 touch_poll_u_position(EE_UINT8, EE_UINT16 *);
EE_INT8 touch_poll_s_position(EE_UINT8, EE_INT16 *);
EE_INT8	touch_set_dimension(EE_UINT8, EE_UINT16);

void touch_set_ADC_parameters();
void touch_set_activation_time(EE_UINT16);
void touch_raw_init();
void touch_tune(tune_raw_t *);
void touch_calibrate(tune_raw_t *);

COMPILER_INLINE void touch_start(void)
{
	touch_timer_start();
}

COMPILER_INLINE void touch_stop(void)
{
	touch_timer_stop();
}

#endif // __TOUCH_H__
