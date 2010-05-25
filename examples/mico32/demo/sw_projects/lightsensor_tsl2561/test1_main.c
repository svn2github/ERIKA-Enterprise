/*
  Name: test1_main.c
  Copyright: Evidence Srl
  Author: Dario Di Stefano
  Date: 29/03/10 18.23
  Description: Light sensor test.
*/

/* RT-Kernel */
#include <ee.h>
/* Platform description */
#include <system_conf.h>
/* Erika Mico32 interrupts */
#include <cpu/mico32/inc/ee_irq.h>
/* Lattice components */
#include <MicoMacros.h>
#include <string.h>

#define turn_on_led() 	EE_misc_gpio_write_bit_data(1,0)
#define turn_off_led() 	EE_misc_gpio_write_bit_data(0,0)

int print_string(const char* s)
{
	return EE_uart_send_buffer((EE_UINT8*)s, strlen(s));
}

/* Write the decimal representation of `n' into `strbuf' as a null-terminated
 * string, and return the length of the string (not including the null).
 */
static int int2str(char strbuf[], int n)
{
    int c = 0;
    unsigned base = 1000*1000*1000;
    unsigned num;
    if (n < 0) {
        strbuf[c++] = '-';
        num = -n;
    } else {
        num = n;
    }
    while (base > num && base > 1)
        base /= 10;
    while (base > 1) {
        unsigned d = num / base;
        strbuf[c++] = '0' + d;
        num = num % base;
        base /= 10;
    }
    strbuf[c++] = '0' + num;
    strbuf[c] = 0;
    return c;
}

void system_timer_callback(void)
{
	CounterTick(myCounter);
}

/* demo task */
TASK(myTask)
{
	static int read_count = 0;
    char strbuf[20];
    int light;
    
    read_count++;
    
    light = EE_lightsensor_read();
    if(light<0)
    {
        print_string("Error while reading the measure");
        return;
    }
    
    int2str(strbuf, read_count);
    print_string(strbuf);
    print_string(": ");
    int2str(strbuf, light);
    print_string(strbuf);
    print_string("\n");
}


/*
 * MAIN TASK
 */
int main(void)
{
	/* ------------ */
	/* Disable IRQ  */
	/* ------------ */
	EE_mico32_disableIRQ();
	
	/* ------------------- */
	/* UART configuration */
	/* ------------------- */
	EE_uart_config(115200, EE_UART_BIT8_NO | EE_UART_BIT_STOP_1);
	EE_uart_set_ISR_mode(EE_UART_POLLING | EE_UART_RXTX_BLOCK);
	
    /* ------------------- */
    /* Light-sensor configuration */
    /* ------------------- */
    int ret;
    ret = EE_lightsensor_config(100000, 0);
    if (ret < 0) 
    {
        print_string("Error while configuring light sensor");
        while(1);
    }     
    
    /* ------------------- */
	/* Enable IRQ */
	/* ------------------- */
	EE_mico32_enableIRQ();
	
    /* ------------------- */
	/* Kernel timer configuration */
	/* ------------------- */
	EE_timer_set_ISR_callback(system_timer_callback);
	EE_timer_init(MICROSECONDS_TO_TICKS(1000), MICO32_TIMER_CONTROL_INT_BIT_MASK | MICO32_TIMER_CONTROL_CONT_BIT_MASK | MICO32_TIMER_CONTROL_STOP_BIT_MASK);
	
	/* ------------------- */
	/* Background activity */
	/* ------------------- */
	SetRelAlarm(myAlarm, 500, 500);
	EE_timer_on();
	
	/* Forever loop: background activities (if any) should go here */
	while(1)
		;
		
	return 0;
    
}

