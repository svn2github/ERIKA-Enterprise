#include "ee.h"
#include "mirtes.h"
#include <MicoMacros.h>
#include "console_serial.h"
#include <string.h>
#include <stdio.h>
#include <stdarg.h>


#define TICK_PERIOD 10

void myprintf(const char* format, ...);

#ifdef MIRTES_DB_IPERMOB_PARKING
EE_UINT8 demo_ipermob_parking_slot_id[8];
EE_UINT8 demo_ipermob_parking_states[8];
EE_UINT8 demo_ipermob_parking_ml = 8;
unsigned long long demo_ipermob_parking_sid = 0x495045524d4f01ULL;
#endif

/* This is an ISR Type 2 which is attached to the Timer 1 peripheral IRQ pin
 * The ISR simply calls CounterTick to implement the timing reference
 */
void system_timer_callback(void)
{
	//	static int i = 0;
	//	i++;
	//	if (!(i%10))
	//		mirtes_debug_print("timer1 ISR");
	/* count the interrupts, waking up expired alarms */
	//CounterTick(MTCPIP_STACK_TASK_COUNTER);
	CounterTick(myCounter);
}

void EE_led_off(void)
{
	EE_misc_gpio_write_bit_data(0, EE_DL3_BIT);
}

void EE_led_on(void)
{
	EE_misc_gpio_write_bit_data(1, EE_DL3_BIT);
}

TASK(serial_writer)
{
	//void
}
/******************************************************************************/
/*                              main() Section                                */
/******************************************************************************/
int main(void)
{
	/* ------------ */
	/* Disable IRQ  */
	/* ------------ */
	EE_mico32_disableIRQ();
	mico32_disable_irq_mask(0xFFFFFFFF);
	
	/* ------------------- */
	/* UART configuration  */
	/* ------------------- */
	//EE_uart_config(115200, EE_UART_BIT8_NO | EE_UART_BIT_STOP_1);
	//EE_uart_set_ISR_mode(EE_UART_POLLING | EE_UART_RXTX_BLOCK);
	
	/* ----------------- */
	/* CONSOLE */
	/* ----------------- */
	/* Serial Console configuration */
	console_descriptor_t *cons;    
	cons = console_serial_config(1, 115200, CONSOLE_SERIAL_FLAG_BIT8_NO | CONSOLE_SERIAL_FLAG_BIT_STOP1);
	if (!cons)
		for (;;) 
			; // Fatal Error
	console_init(0, cons);
	if (console_open(0) < 0)
		for (;;) 
			; // Fatal Error
	myprintf("Serial console configuration...Done!\n");

	/* ------------------- */
	/* Kernel timer configuration */
	/* ------------------- */
	EE_timer_set_ISR_callback(system_timer_callback);
	EE_timer_init(MICROSECONDS_TO_TICKS(1000), MICO32_TIMER_CONTROL_INT_BIT_MASK | MICO32_TIMER_CONTROL_CONT_BIT_MASK | MICO32_TIMER_CONTROL_STOP_BIT_MASK);
	
	/* ------------------- */
	/* Enable IRQ */
	/* ------------------- */
	EE_mico32_enableIRQ();
	
	#if 1
	/* ------------------- */
	/* MIRTES initialization */
	/* ------------------- */
	myprintf("\nMirtes init...");
	MIRTES_init();
	
	#ifdef MIRTES_DB_IPERMOB_PARKING
	demo_ipermob_parking_states[0] = 101;
	demo_ipermob_parking_states[1] = 102;
	demo_ipermob_parking_states[2] = 103;
	demo_ipermob_parking_states[3] = 104;
	demo_ipermob_parking_states[4] = 105;
	demo_ipermob_parking_states[5] = 106;
	demo_ipermob_parking_states[6] = 107;
	demo_ipermob_parking_states[7] = 108;

	demo_ipermob_parking_slot_id[0] = 1;
	demo_ipermob_parking_slot_id[1] = 2;
	demo_ipermob_parking_slot_id[2] = 3;
	demo_ipermob_parking_slot_id[3] = 4;
	demo_ipermob_parking_slot_id[4] = 5;
	demo_ipermob_parking_slot_id[5] = 6;
	demo_ipermob_parking_slot_id[6] = 7;
	demo_ipermob_parking_slot_id[7] = 8;
	#endif
	
	myprintf("\nDone!\n");
	#endif
	
	#if 0
	/* ------------------- */
    /* Light-sensor configuration */
    /* ------------------- */
	int ret;
    ret = EE_lightsensor_config(100000, 0);
    if (ret < 0)
        myprintf("Error while configuring light sensor", ret);
    else
		myprintf("Light sensor: OK!\n");
	
	/* ------------------- */
	/* Other activations   */
	/* ------------------- */
	SetRelAlarm(myAlarm, 1000, 1000);
	EE_timer_on();
	#endif
	
	/* ------------------- */
	/* Forever loop: background activities (if any) should go here */
	/* ------------------- */
	for (;;)
		;
	return 0;
}

TASK(myTask)
{
	#if 0
	static int read_count;
    int light;
    
    ++read_count;
    
    light = EE_lightsensor_read();
    if(light<0)
        myprintf("Error while reading the measure", light);
    
	myprintf("read number:%d  val:%d\n", read_count, light);
	#endif
}

#define MAX_CHARS 128
void myprintf(const char* format, ...)
{
	char str[MAX_CHARS];
	
	va_list args;
	va_start( args, format );
	vsnprintf(str, MAX_CHARS, format, args);
	va_end( args );
	EE_uart_send_buffer((EE_UINT8*)str, strlen(str));
}



