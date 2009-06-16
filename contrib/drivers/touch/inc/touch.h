#ifndef __TOUCH_H__
#define __TOUCH_H__

#define __FOUR_WIRES__
#define __LOW_LEVEL_MEASUREMENT__

#include<touch_compiler.h>
#include<touch_hal.h>

#define TOUCH_X_AXIS	0
#define TOUCH_Y_AXIS	1

// Measurement Settings
#define SAMPLES_FOR_ONE_TRUE_XY_PAIR    5             // Number of Measurements for one true X/Y-Coordinate
#define END_OF_ARRAY                    SAMPLES_FOR_ONE_TRUE_XY_PAIR-1
#define MEDIAN                          (SAMPLES_FOR_ONE_TRUE_XY_PAIR-1)/2      // odd-numbered: SAMPLES_FOR_ONE_TRUE_XY_PAIR
#define MAXIMUM_LOW_LEVEL           	1000           // Invalid Measurement for Low_Level > MAXIMUM_LOW_LEVEL
#define RTOUCH_MAXIMUM_LEVEL			4000
#define MAXIMUM_UNTOUCH_CONDITIONS   	100           // Number of (successive) Invalid Measurements till Untouch Condition
#define SLEEP_COUNTDOWN                 2000

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

/****************************************************************************
  Function definitions
****************************************************************************/

EE_UINT16 touch_get_position_u(EE_UINT8 touch_axis);
EE_INT16 touch_get_position_s(EE_UINT8 axis);
EE_UINT16 touch_get_position_raw(EE_UINT8 touch_axis);
void	touch_set_dimension(EE_UINT8, EE_UINT8);
void 	touch_init(void);
void	touch_calibrate(void);
void 	store_valid_data(void);
void 	sorted_insertion(EE_UINT16 Array[]);

COMPILER_INLINE void touch_start(void)
{
	SetRelAlarm(AlarmTouchManager,10,2);
}

COMPILER_INLINE void touch_stop(void)
{
	CancelAlarm(AlarmTouchManager);
}

#endif // __TOUCH_H__
