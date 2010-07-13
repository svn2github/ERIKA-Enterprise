#include "ee.h"
#include "hw/sensor_board_tests/common/EE_power_board_hal.h"
#include "MicoMacros.h"

/* -------------------------------------- */
#include <stdio.h>
#include <string.h>
#include <stdarg.h>

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
/* -------------------------------------- */

#define PWR_ZERO 	0
#define PWR_LOW 	1
#define PWR_MEDIUM 	2
#define PWR_HIGH 	3


void system_timer_callback(void)
{
    /* count the interrupts, waking up expired alarms */
    CounterTick(myCounter);
}

TASK(myTask)
{
	EE_UINT8 val;
	static int task_counter=0;
	static int change_flag=0;
	
	task_counter++;
	myprintf("\ntest number: %d\n", task_counter);
	EE_power_board_communication_send(change_flag);
	myprintf("change_flag: 0x%x\n", change_flag);
	val = EE_power_board_communication_get_status();
	myprintf("val: 0x%x\n", val);
	change_flag++;
	if(change_flag==4)
		change_flag = 0;
//	task_counter++;
//	myprintf("\ntest number: %d\n", task_counter);
//	EE_power_board_communication_send(PWR_ZERO);
//	myprintf("PWR_ZERO: 0x%x\n", PWR_ZERO);
//	val = EE_power_board_communication_get_status();
//	myprintf("val: 0x%x\n", val);
//	EE_power_board_communication_send(PWR_LOW);
//	myprintf("PWR_LOW: 0x%x\n", PWR_LOW);
//	val = EE_power_board_communication_get_status();
//	myprintf("val: 0x%x\n", val);
//	EE_power_board_communication_send(PWR_MEDIUM);
//	myprintf("PWR_MEDIUM: 0x%x\n", PWR_MEDIUM);
//	val = EE_power_board_communication_get_status();
//	myprintf("val: 0x%x\n", val);
//	EE_power_board_communication_send(PWR_HIGH);
//	myprintf("PWR_HIGH: 0x%x\n", PWR_HIGH);
//	val = EE_power_board_communication_get_status();
//	myprintf("val: 0x%x\n", val);
}

/******************************************************************************/
/*                              main() Section                                */
/******************************************************************************/
int main(void)
{
	/* ------------------- */
    /* Disable IRQ         */
    /* ------------------- */
    EE_mico32_disableIRQ();
    
    /* -------------------------- */
    /* Uart configuration         */
    /* -------------------------- */
    EE_uart_config(115200, EE_UART_BIT8_NO | EE_UART_BIT_STOP_1);
    EE_uart_set_ISR_mode(EE_UART_POLLING | EE_UART_RXTX_BLOCK); 

    /* ------------------- */
    /* Kernel timer configuration */
    /* ------------------- */
    EE_timer_set_ISR_callback(system_timer_callback);
    EE_timer_init(MILLISECONDS_TO_TICKS(1), MICO32_TIMER_CONTROL_INT_BIT_MASK | MICO32_TIMER_CONTROL_CONT_BIT_MASK);
    
    /* ------------------- */
    /* Enable IRQ         */
    /* ------------------- */
    EE_mico32_enableIRQ();
    
     /* ------------------- */
    /* Start demo */
    /* ------------------- */
    SetRelAlarm(myAlarm, 100, 2000);
	//SetRelAlarm(myAlarm2, 20, 1000);
    EE_timer_on();
      
	EE_power_board_communication_init();
	EE_UINT8 val = EE_power_board_communication_get_status();
	myprintf("status: 0x%x\n", val);

	while(1);
	
	return 0;
}
