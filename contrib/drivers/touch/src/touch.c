#include "touch.h"

/****************************************************************************
  Global variables
****************************************************************************/

EE_UINT16 horiz_width;
EE_UINT16 vert_height;

EE_UINT16 u_X_pos;
EE_UINT16 u_Y_pos;

EE_INT16 s_X_pos;
EE_INT16 s_Y_pos;

volatile EE_UINT8 raw_ready;

EE_UINT16 X_raw;
EE_UINT16 Y_raw;

// Touch state variable
volatile TouchFlow tf;

// Array for X-Coordinates
EE_UINT16 Reading_X[SAMPLES_FOR_ONE_TRUE_XY_PAIR];
// Array for Y-Coordinates
EE_UINT16 Reading_Y[SAMPLES_FOR_ONE_TRUE_XY_PAIR];
// Array index
volatile EE_UINT8 i_array;

static EE_UINT16 Reading_low_level;

volatile EE_UINT16 Untouch_conditions;

// Valibration values
double cal_a,cal_b,cal_c;
double cal_d,cal_e,cal_f;

// computation begins
volatile EE_UINT16 xd1,yd1;
volatile EE_UINT16 xd2,yd2;
volatile EE_UINT16 xd3,yd3;
volatile EE_UINT16 xt1,yt1;
volatile EE_UINT16 xt2,yt2;
volatile EE_UINT16 xt3,yt3;



EE_UINT16 touch_delay_count __attribute__((near)) = 0;

EE_UINT16 touch_get_position_u(
		EE_UINT8 touch_axis)
{
	if(touch_axis == TOUCH_X_AXIS)
	{
		return u_X_pos;
	}
	else if(touch_axis == TOUCH_Y_AXIS)
	{
		return u_Y_pos;
	} else return 0;
}

EE_INT16 touch_get_position_s(
		EE_UINT8 touch_axis)
{
	if(touch_axis == TOUCH_X_AXIS)
	{
		return s_X_pos;
	}
	else if(touch_axis == TOUCH_Y_AXIS)
	{
		return s_Y_pos;
	} else return 0;
}

void touch_set_dimension(
		EE_UINT8 touch_axis,
		EE_UINT8 touch_range)
{
	if(touch_axis == TOUCH_X_AXIS)
	{
		horiz_width = touch_range;
	}
	else if(touch_axis == TOUCH_Y_AXIS)
	{
		vert_height = touch_range;
	}
}

COMPILER_INLINE void touch_delay( EE_UINT8 delay_count )
{
	touch_delay_count++;
	asm volatile("outer: dec _touch_delay_count");
	asm volatile("cp0 _temp_count");
	asm volatile("bra z, done");
	asm volatile("do #3200, inner" );
	asm volatile("nop");
	asm volatile("inner: nop");
	asm volatile("bra outer");
	asm volatile("done:");
}

void touch_init(void)
{
	// Global variables reset 
	Untouch_conditions = 0;
	X_raw = 0;
	Y_raw = 0;
	
	u_X_pos = 0;
	u_Y_pos = 0;
	
	s_X_pos = 0;
	s_Y_pos = 0;
	
	raw_ready = 0;
	i_array = 0;

	// Pilot pins setting and lighting up 
#ifdef __USE_TOUCH_ALTERNATE__
	CLEARBIT(FAKE_PULL_UP_DDR,EE_T_FAKE_PULL_UP); // Set fake pull-up pin (RD8) as output
	SETBIT(FAKE_PULL_UP_OUTPUT,EE_T_FAKE_PULL_UP); // Light up fake pull-up pin.
#elif defined(__USE_TOUCH_STANDARD__)
	CLEARBIT(EE_TOUCH_EN_A_TRIS);
	CLEARBIT(EE_TOUCH_EN_B_TRIS);
	CLEARBIT(EE_TOUCH_EN_C_TRIS);
	SETBIT(EE_TOUCH_BOTTOM_TRIS);
	SETBIT(EE_TOUCH_RIGHT_TRIS);
	CLEARBIT(EE_TOUCH_BOTTOM_AD);
	CLEARBIT(EE_TOUCH_RIGHT_AD);
#endif

	STANDBY_CONFIGURATION;
	tf.STANDBY = 1;
	
	// TODO: Abstract this bits in the .h [like ADC_TURN_ON]
	AD1CHS0 = STANDBY_PIN;
	AD1CON1bits.ASAM = 1;
	AD1CON1bits.FORM = 0;
	AD1CON1bits.SSRC = 0;
	AD1CON1bits.AD12B = 1;
	AD1CON2 = 0;
	AD1CON3bits.SAMC = 16;
	AD1CON3bits.ADRC = 0;
	AD1CON3bits.ADCS = 3;
	IFS0bits.AD1IF = 0;		// reset ADC interrupt flag
	IEC0bits.AD1IE = 1;		// enable ADC interrupts, disable this interrupt if the DMA is enabled
	
	ADC_TURN_ON;			// turn on ADC
	
	touch_calibrate();
		
}

void touch_calibrate(void)
{
	// touch input P1 (90%,50%)
	xd1 = (EE_UINT16)(0.9*horiz_width);
	yd1 = (EE_UINT16)( 0.5*vert_height);
	// touch input P2 (50%,10%)
	xd2 = (EE_UINT16)(0.5*horiz_width);
	yd2 = (EE_UINT16)(0.9*vert_height);
	// touch input P3 (10%,90%)
	xd3 = (EE_UINT16)(0.1*horiz_width);
	yd3 = (EE_UINT16)(0.1*vert_height);

	/*

	touch_stop();
	touch_delay(Delay_1S_Cnt/3);
	touch_start();

	//  Outing: Touch P1!

	EE_led_on();
	raw_ready = 0;
	while(!raw_ready);
	xt1 = X_raw;
	yt1 = Y_raw;
	raw_ready = 0;
	EE_led_off();

	touch_stop();
	touch_delay(Delay_1S_Cnt/3);
	touch_start();

	//  Outing: Touch P2!

	EE_led_on();
	while(!raw_ready);
	xt2 = X_raw;
	yt2 = Y_raw;
	raw_ready = 0;
	EE_led_off();

	touch_stop();
	touch_delay(Delay_1S_Cnt/3);
	touch_start();

	//  Outing: Touch P2!

	EE_led_on();
	while(!raw_ready);
	xt3 = X_raw;
	yt3 = Y_raw;
	raw_ready = 0;
	EE_led_off();

	touch_stop();

	*/

	/*xt1 = 2990;
	yt1 = 1890;
	xt2 = 2110;
	yt2 = 2770;
	xt3 = 1300;
	yt3 = 1040;*/

	/*xt1 = 3104;
	yt1 = 1944;
	xt2 = 2102;
	yt2 = 2876;
	xt3 = 1128;
	yt3 = 988;*/
	
	xt1 = 2919;
	yt1 = 1592;
	xt2 = 1703;
	yt2 = 2567;
	xt3 = 496;
	yt3 = 631;
	

	cal_a = ((long)yt1*xd3-(long)yt1*xd2-(long)yt2*xd3+(long)xd2*yt3-(long)xd1*yt3+(long)xd1*yt2);
	cal_a /= (-(long)xt1*yt3+(long)xt2*yt3-(long)xt2*yt1+(long)xt3*yt1-(long)xt3*yt2+(long)xt1*yt2);

	cal_b = cal_a*((float)xt3-xt2)+xd2-xd3;
	cal_b /= (yt2-yt3);

	cal_c = xd3-cal_a*xt3-cal_b*yt3;

	cal_d = -((long)yt2*yd3-(long)yt2*yd1-(long)yt1*yd3-(long)yt3*yd2+(long)yt3*yd1+(long)yt1*yd2);
	cal_d /= (-(long)yt2*xt3+(long)yt2*xt1+(long)yt1*xt3+(long)yt3*xt2-(long)yt3*xt1-(long)yt1*xt2);

	cal_e = cal_d*((float)xt3-xt2)+yd2-yd3;
	cal_e /= yt2-yt3;

	cal_f = yd3-cal_d*xt3-cal_e*yt3;
}

#ifdef __LOW_LEVEL_MEASUREMENT__
TASK(touch_Manager)
{
	if(CONVERSION_DONE)
	{
		CONVERSION_RESET;
		if(tf.STANDBY)
		{
			Reading_low_level = ADC1BUF0;
			if(Reading_low_level < MAXIMUM_LOW_LEVEL)
			{
				tf.STANDBY = 0;
				tf.YPOS = 1;
				if(tf.COMPLETE)
				{
					store_valid_data();
				}
				Y_POS_CONFIGURATION;
				AD1CHS0 = ADC_Y;
				Untouch_conditions = 0;
			} else
			{
				tf.COMPLETE = 0;
				if(MAXIMUM_UNTOUCH_CONDITIONS == Untouch_conditions )
				{
					X_raw = 0;
					Y_raw = 0;
				} else Untouch_conditions++;
			}

		} else if(tf.YPOS)
		{
			Reading_Y[i_array] = ADC1BUF0;
			tf.YPOS = 0;
			tf.XPOS = 1;
			X_POS_CONFIGURATION;
			AD1CHS0 = ADC_X;
		} else if(tf.XPOS)
		{
			Reading_X[i_array] = ADC1BUF0;
			tf.XPOS = 0;
			tf.STANDBY = 1;
			tf.COMPLETE = 1;
			STANDBY_CONFIGURATION;
			AD1CHS0 = STANDBY_PIN;
		}
	} else
	{
		START_CONVERSION;
	}
}
#endif // __LOW_LEVEL_MEASUREMENT__

ISR2(_ADC1Interrupt)
{
	IFS0bits.AD1IF = 0;
	ActivateTask(touch_Manager);
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
		raw_ready = 1;

		// Translation to (PX,PY)

		//GetResource(mutex_posRead);

		u_X_pos = cal_a*X_raw+cal_b*Y_raw+cal_c;
		u_Y_pos = cal_d*X_raw+cal_e*Y_raw+cal_f;
		
		if(u_X_pos<0)
			u_X_pos = 0;
		else if(u_X_pos>horiz_width-1)
			u_X_pos = horiz_width-1;
			
		if(u_Y_pos<0)
			u_Y_pos = 0;
		else if(u_Y_pos>vert_height-1)
			u_Y_pos = vert_height-1;
				
		s_X_pos = (EE_INT16)u_X_pos - horiz_width/2;
		s_Y_pos = (EE_INT16)u_Y_pos - vert_height/2;		
				
		/*uposRead.x = cal_a*X_raw+cal_b*Y_raw+cal_c;
		uposRead.y = cal_d*X_raw+cal_e*Y_raw+cal_f;

		sposRead.x = (signed int)uposRead.x - horiz_width/2;
		sposRead.y = (signed int)uposRead.y - vert_height/2;

		if(uposRead.x > horiz_width)
			uposRead.x = horiz_width;
		if(uposRead.y > vert_height)
			uposRead.y = vert_height;*/

		//ReleaseResource(mutex_posRead);

		i_array = 0;

    } else	i_array++;
}



