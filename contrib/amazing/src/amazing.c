#include "ee.h"
#include "amazing.h"
#include "dee_emulation_16-bit.h"
#include "touch.h"
#include "cpu/pic30/inc/ee_irqstub.h"

#define AMAZING_LAPS			2
#define AMAZING_ALREADY_SET_ADDR	2
#define AMAZING_TUNE_ADDR		4
#define AMAZING_DUTY_MIN		1200
#define AMAZING_DUTY_MAX		1800

volatile EE_UINT8 pwm_phase = 0;
volatile EE_UINT8 modified = 0;

/* Program the Timer9 peripheral to raise interrupts */
static void T9_program(void)
{
	T9CON = 0;		/* Stops the Timer9 and reset control reg	*/
	TMR9  = 0;		/* Clear contents of the timer register	*/
	PR9 = 40000;
	IPC13bits.T9IP = 5;	/* Set Timer9 priority to 1		*/
	IFS3bits.T9IF = 0;	/* Clear the Timer1 interrupt status flag	*/
	IEC3bits.T9IE = 1;	/* Enable Timer1 interrupts		*/
	T9CONbits.TON = 1;	/* Start Timer1 with prescaler settings at 1:1  and clock source set to the internal  instruction cycle */
}

/* Clear the Timer9 interrupt status flag */
static void T9_clear(void)
{
	IFS3bits.T9IF = 0;
}

ISR2(_T9Interrupt)
{
	static EE_UINT16 c_tick = 0;
	// clear the interrupt source
	T9_clear();

	if(c_tick == 2000){

		switch(pwm_phase%4)
		{
			case 0: 
				EE_pwm_set_duty(EE_PWM_PORT1,AMAZING_DUTY_MIN);
				EE_pwm_set_duty(EE_PWM_PORT2,AMAZING_DUTY_MIN);
				break;
			case 1:
				EE_pwm_set_duty(EE_PWM_PORT1,AMAZING_DUTY_MAX);
				break;
			case 2:
				EE_pwm_set_duty(EE_PWM_PORT2,AMAZING_DUTY_MAX);
				break;
			case 3:
				EE_pwm_set_duty(EE_PWM_PORT1,AMAZING_DUTY_MIN);
				break;
		}

		if(++pwm_phase == AMAZING_LAPS*4) T9CONbits.TON = 0; 

		c_tick = 0;

	} else c_tick++;
}

void amazing_reset_body()
{
	DataEEInit();
	dataEEFlags.val = 0;	
	DataEEWrite(0x00,AMAZING_ALREADY_SET_ADDR);
	asm("reset");
}

static EE_UINT8 read_permanent_conf(tune_t *tn)
{
	EE_UINT8 i;
	
	if(DataEERead(AMAZING_ALREADY_SET_ADDR) == 0xEE){	
		for(i=0; i<sizeof(tune_t); i++)
			tn->value[i] = DataEERead(AMAZING_TUNE_ADDR+i);
		return 1;
	}

	return 0;
}

static void write_permanent_conf(tune_t *tn)
{
	EE_UINT8 i;
	for(i=0; i<sizeof(tune_t); i++)
		DataEEWrite(tn->value[i],AMAZING_TUNE_ADDR+i);
}

void amazing_tuner_body(EE_UINT16 horiz_width,EE_UINT16 vert_height)
{
	tune_t tun;
	EE_UINT16 X_raw,Y_raw;
	EE_UINT16 xd1,yd1,xd2,yd2,xd3,yd3;
	EE_UINT16 xt1,yt1,xt2,yt2,xt3,yt3;
	EE_UINT16 min_x=65535,max_x=0;
	EE_UINT16 min_y=65535,max_y=0;

	tun.cal.a = 0;
	tun.cal.b = 0;
	tun.cal.c = 0;
	tun.cal.d = 0;
	tun.cal.e = 0;
	tun.cal.f = 0;

	DataEEInit();
	dataEEFlags.val = 0;	

	touch_set_dimension(TOUCH_X_AXIS,horiz_width);
	touch_set_dimension(TOUCH_Y_AXIS,vert_height);
	touch_raw_init();

	EE_pwm_init( EE_PWM_PORT1 , 20000 , 0 );
	EE_pwm_init( EE_PWM_PORT2 , 20000 , 0 );

	if(!read_permanent_conf(&tun))
	{
	        // touch input P1 (90%,50%)
	        xd1 = (EE_UINT16)(0.9*horiz_width);
	        yd1 = (EE_UINT16)(0.5*vert_height);
	        // touch input P2 (50%,10%)
	        xd2 = (EE_UINT16)(0.5*horiz_width);
	        yd2 = (EE_UINT16)(0.9*vert_height);
	        // touch input P3 (10%,90%)
	        xd3 = (EE_UINT16)(0.1*horiz_width);
	        yd3 = (EE_UINT16)(0.1*vert_height);
	
		pwm_phase = 0;
		T9_program();
	
		#ifdef CONFIG_AMAZING_UART_DEBUG
		EE_uart_write_byte(EE_UART_PORT_2,'S');		
		#endif
	
		while(1)
		{
			modified = 0;
			touch_wait_raw_position(&X_raw,&Y_raw);
	
	        	if(X_raw < min_x){
	        	        min_x = X_raw;
	        	        modified = 1;
	        	}
	        	else if(X_raw > max_x){
	        	        max_x = X_raw;
	        	        modified = 1;
	        	}
	
	        	if(Y_raw < min_y){
	        	        min_y = Y_raw;
	        	        modified = 1;
	        	}
	        	else if(Y_raw > max_y){
	        	        max_y = Y_raw;
	        	        modified = 1;
	        	}
	
	        	if(!modified){
	
				if(pwm_phase>=AMAZING_LAPS*4) break;
	
			}
	        	else 
			{ 
				#ifdef CONFIG_AMAZING_UART_DEBUG
				EE_uart_write_byte(EE_UART_PORT_2,'<');
				EE_uart_write_byte(EE_UART_PORT_2,(X_raw >> 8) & 0xFF);
				EE_uart_write_byte(EE_UART_PORT_2,X_raw & 0xFF);
				EE_uart_write_byte(EE_UART_PORT_2,(Y_raw >> 8) & 0xFF);
				EE_uart_write_byte(EE_UART_PORT_2,Y_raw & 0xFF);
				EE_uart_write_byte(EE_UART_PORT_2,'>');
				#endif
	
	        	        xt1 = min_x + 0.9*(max_x-min_x);  
	        	        yt1 = min_y + 0.5*(max_y-min_y);  
	        	        xt2 = min_x + 0.5*(max_x-min_x);  
	        	        yt2 = min_y + 0.9*(max_y-min_y);  
	        	        xt3 = min_x + 0.1*(max_x-min_x);  
	        	        yt3 = min_y + 0.1*(max_y-min_y);
	
				tun.cal.a = ((long)yt1*xd3-(long)yt1*xd2-(long)yt2*xd3+(long)xd2*yt3-(long)xd1*yt3+(long)xd1*yt2);
				tun.cal.a /= (-(long)xt1*yt3+(long)xt2*yt3-(long)xt2*yt1+(long)xt3*yt1-(long)xt3*yt2+(long)xt1*yt2);
			
				tun.cal.b = tun.cal.a*((float)xt3-xt2)+xd2-xd3;
				tun.cal.b /= (yt2-yt3);
			
				tun.cal.c = xd3-tun.cal.a*xt3-tun.cal.b*yt3;
			
				tun.cal.d = -((long)yt2*yd3-(long)yt2*yd1-(long)yt1*yd3-(long)yt3*yd2+(long)yt3*yd1+(long)yt1*yd2);
				tun.cal.d /= (-(long)yt2*xt3+(long)yt2*xt1+(long)yt1*xt3+(long)yt3*xt2-(long)yt3*xt1-(long)yt1*xt2);
			
				tun.cal.e = tun.cal.d*((float)xt3-xt2)+yd2-yd3;
				tun.cal.e /= yt2-yt3;
			
				tun.cal.f = yd3-tun.cal.d*xt3-tun.cal.e*yt3;
	
			}
		}
	
		DataEEWrite(0xEE,AMAZING_ALREADY_SET_ADDR);
		write_permanent_conf(&tun);
	}

	touch_tune(&tun);
}

