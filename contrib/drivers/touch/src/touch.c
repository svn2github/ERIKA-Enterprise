#include "touch.h"
#include "touch_kal.h"

#ifdef __USE_TOUCH__

/****************************************************************************
  Global variables
****************************************************************************/

static EE_UINT16 horiz_width;
static EE_UINT16 vert_height;
EE_UINT16 u_X_pos;
EE_UINT16 u_Y_pos;
static EE_INT16 s_X_pos;
static EE_INT16 s_Y_pos;
static volatile EE_UINT8 is_raw_initialized = 0;
static volatile EE_UINT8 is_raw_ready;
static volatile EE_UINT8 is_final_ready;
static EE_UINT16 X_raw;
static EE_UINT16 Y_raw;

static EE_UINT16 touch_tick_us;

//static tune_t tune;
tune_t tune;
volatile EE_UINT8 is_tuned;

// Touch state variable
static volatile TouchFlow tf;

// Array index
static volatile EE_UINT8 i_array;
// Array for X-Coordinates
EE_UINT16 Reading_X[SAMPLES_FOR_ONE_TRUE_XY_PAIR];
// Array for Y-Coordinates
EE_UINT16 Reading_Y[SAMPLES_FOR_ONE_TRUE_XY_PAIR];

static EE_UINT16 Reading_low_level;
static volatile EE_UINT16 Untouch_conditions;

EE_INT8 touch_poll_raw_position(
		EE_UINT16 *raw_choord_x,
		EE_UINT16 *raw_choord_y)
{
	if(!is_raw_ready)
		return TOUCH_ERROR_RAW_NOT_READY;

	*raw_choord_x = X_raw;
	*raw_choord_y = Y_raw;

	is_raw_ready = 0;
	
	return TOUCH_ERROR_NONE;
}

void touch_wait_raw_position(
		EE_UINT16 *raw_choord_x,
		EE_UINT16 *raw_choord_y)
{
	while(!is_raw_ready);

	*raw_choord_x = X_raw;
 	*raw_choord_y = Y_raw;

	is_raw_ready = 0;
}

EE_INT8 touch_poll_u_position(
		EE_UINT8 touch_axis,
		EE_UINT16 *u_choord)
{
	if(touch_axis == TOUCH_X_AXIS)
	{
		*u_choord = u_X_pos;
	}
	else if(touch_axis == TOUCH_Y_AXIS)
	{
		*u_choord = u_Y_pos;
	} else return TOUCH_ERROR_WRONG_AXIS;
	
	if(!is_tuned)
		return TOUCH_ERROR_NOT_TUNED;

	return TOUCH_ERROR_NONE;
}

EE_INT8 touch_poll_s_position(
		EE_UINT8 touch_axis,
		EE_INT16 *s_choord)
{
	if(touch_axis == TOUCH_X_AXIS)
	{
		*s_choord = s_X_pos;
	}
	else if(touch_axis == TOUCH_Y_AXIS)
	{
		*s_choord = s_Y_pos;
	} else return TOUCH_ERROR_WRONG_AXIS;
	
	if(!is_tuned)
		return TOUCH_ERROR_NOT_TUNED;

	return TOUCH_ERROR_NONE;
}

EE_INT8 touch_set_dimension(
		EE_UINT8 touch_axis,
		EE_UINT16 touch_range)
{
	if(touch_axis == TOUCH_X_AXIS)
	{
		horiz_width = touch_range;
	}
	else if(touch_axis == TOUCH_Y_AXIS)
	{
		vert_height = touch_range;
	} else return TOUCH_ERROR_WRONG_AXIS;

	return TOUCH_ERROR_NONE;
}

void touch_set_ADC_parameters()
{
	// Pilot pins setting and lighting up 

	CLEARBIT(EE_TOUCH_EN_A_TRIS);
	CLEARBIT(EE_TOUCH_EN_B_TRIS);
	CLEARBIT(EE_TOUCH_EN_C_TRIS);
	SETBIT(EE_TOUCH_BOTTOM_TRIS);
	SETBIT(EE_TOUCH_RIGHT_TRIS);
	CLEARBIT(EE_TOUCH_BOTTOM_AD);
	CLEARBIT(EE_TOUCH_RIGHT_AD);

	STANDBY_CONFIGURATION;
	tf.STANDBY = 1;
	
	ADC_SELECTED_PIN = STANDBY_PIN;
	SETBIT(ADC_ASAM);
	ADC_FORM = 0;
	ADC_SSRC = 0;
	SETBIT(ADC_AD12B);
	ADC_CON2 = 0;
	ADC_SAMC = 16;
	ADC_ADRC = 0;
	ADC_ADCS = 3;
	
	// reset ADC interrupt flag
	CLEARBIT(ADC_INTERRUPT_FLAG);
	// enable ADC interrupts, disable this interrupt if the DMA is enabled
	SETBIT(ADC_INTERRUPT_ENABLE);
	// turn on ADC
	ADC_TURN_ON;
}

void touch_set_activation_time(EE_UINT16 _touch_tick_us)
{
	touch_tick_us = _touch_tick_us;
}

void touch_raw_init()
{
	if(is_raw_initialized)
		return;

	// Global variables reset 
	Untouch_conditions = 0;

	X_raw = 0;
	Y_raw = 0;
	
	u_X_pos = horiz_width/2;
	u_Y_pos = vert_height/2;
	
	s_X_pos = 0;
	s_Y_pos = 0;
	
	is_raw_ready = 0;
	is_tuned = 0;
	is_final_ready = 0;
	i_array = 0;

	touch_set_ADC_parameters();
	touch_set_activation_time(TOUCH_ACTIVATION_TIME);
	touch_kal_init(touch_tick_us);
	
	is_raw_initialized = 1;
}

void touch_tune(tune_t *tun)
{
	if(is_tuned)
		return;

	tune = *tun;

	is_tuned = 1;
}

void sorted_insertion(EE_UINT16 Array[])
{
	EE_INT8 i;
	EE_UINT8 j;
	EE_UINT16 current;

	// Sort Array[]
	for(j=1; j<SAMPLES_FOR_ONE_TRUE_XY_PAIR; j++)
	{
		current = Array[j];
		i = j - 1;
		while(i>=0 && Array[i]>current)
		{
			Array[i+1] = Array[i];
			i--;
		}
		Array[i+1] = current;
	}
}

void store_valid_data(void)
{
        // Store valid Data in Array

	if(i_array==(END_OF_ARRAY))
	{
		// Array Management

		// Sort X/Y Readings To Get Median
		sorted_insertion(Reading_X);
		sorted_insertion(Reading_Y);

		X_raw = Reading_X[MEDIAN];
		Y_raw = Reading_Y[MEDIAN];
		is_raw_ready = 1;

		//GetResource(mutex_posRead);

		if(is_tuned)
		{

			u_X_pos = (EE_UINT16)(tune.cal.a*X_raw+tune.cal.b*Y_raw+tune.cal.c);
        	u_Y_pos = (EE_UINT16)(tune.cal.d*X_raw+tune.cal.e*Y_raw+tune.cal.f);

           	if(u_X_pos<0)
				u_X_pos = 0;
			else if(u_X_pos>horiz_width-1)
				u_X_pos = horiz_width-1;
			
			if(u_Y_pos<0)
				u_Y_pos = 0;
			else if(u_Y_pos>vert_height-1)
				u_Y_pos = vert_height-1;
			
			s_X_pos = (int)u_X_pos - horiz_width/2;
			s_Y_pos = (int)u_Y_pos - vert_height/2;
			is_final_ready = 1;

		}

		//ReleaseResource(mutex_posRead);

		i_array = 0;

    } else i_array++;
}

#ifdef __LOW_LEVEL_MEASUREMENT__
TASK(TASK_TOUCH_MANAGER)
{
	if(ADC_CONVERSION_DONE)
	{
		ADC_CONVERSION_RESET;
		if(tf.STANDBY)
		{
			Reading_low_level = ADC_RESULT_BUFFER;
			if(Reading_low_level < MAXIMUM_LOW_LEVEL)
			{
				tf.STANDBY = 0;
				tf.YPOS = 1;
				if(tf.COMPLETE)
				{
					store_valid_data();
				}
				Y_POS_CONFIGURATION;
				ADC_SELECTED_PIN = ADC_Y;
				Untouch_conditions = 0;
			} else
			{
				tf.COMPLETE = 0;
				if(MAXIMUM_UNTOUCH_CONDITIONS == Untouch_conditions )
				{
					is_raw_ready = 0;
					X_raw = 0;
					Y_raw = 0;
					is_final_ready = 0;
				} else Untouch_conditions++;
			}

		} else if(tf.YPOS)
		{
			Reading_Y[i_array] = ADC_RESULT_BUFFER;
			tf.YPOS = 0;
			tf.XPOS = 1;
			X_POS_CONFIGURATION;
			ADC_SELECTED_PIN = ADC_X;
		} else if(tf.XPOS)
		{
			Reading_X[i_array] = ADC_RESULT_BUFFER;
			tf.XPOS = 0;
			tf.STANDBY = 1;
			tf.COMPLETE = 1;
			STANDBY_CONFIGURATION;
			ADC_SELECTED_PIN = STANDBY_PIN;
		}
	} else
	{
		ADC_CONVERSION_START;
	}
}
#endif // __LOW_LEVEL_MEASUREMENT__

ISR2(ADC_INTERRUPT_NAME)
{
	CLEARBIT(ADC_INTERRUPT_FLAG);
	ActivateTask(TASK_TOUCH_MANAGER);
}

#endif // __USE_TOUCH__

