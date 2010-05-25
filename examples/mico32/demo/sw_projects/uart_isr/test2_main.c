/*
  Name: test2_main.c
  Copyright: Evidence Srl
  Author: Dario Di Stefano
  Date: 29/03/10 18.23
  Description: Uart isr test(polling, non-blocking mode).
*/

/* RT-Kernel */
#include <ee.h>
/* Platform description */
#include <system_conf.h>
/* Erika Mico32 interrupts */
#include <cpu/mico32/inc/ee_irq.h>
/* Lattice components */
#include <MicoMacros.h>

TASK(myTask)
{
    EE_UINT8 myArray[5];
    
    /* Single byte test */
    myArray[0] = 'A';
    if( EE_uart_send_byte(myArray[0]) < 0 )
		while(1)
			;
 	if( EE_uart_receive_byte(myArray) < 0 )
 	{
		while( !(ee_uart_st.base->lsr & MICOUART_LSR_TX_RDY_MASK) )
			;
 		if( EE_uart_send_byte('X') < 0 )
    		while(1)
    			;
 	}
    else
    {
    	while( !(ee_uart_st.base->lsr & MICOUART_LSR_TX_RDY_MASK) )
			;
    	if( EE_uart_send_byte(myArray[0]) < 0 )
    		while(1)
    			;
    }
}

void system_timer_callback(void)
{
	/* count the interrupts, waking up expired alarms */
	CounterTick(myCounter);
}


/*
 * MAIN TASK
 */
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
	EE_uart_set_ISR_mode(EE_UART_POLLING); // polling, non-blocking mode  
	
	/* ------------------- */
	/* Kernel timer configuration */
	/* ------------------- */
	EE_timer_set_ISR_callback(system_timer_callback);
	EE_timer_init(MILLISECONDS_TO_TICKS(1), MICO32_TIMER_CONTROL_INT_BIT_MASK | MICO32_TIMER_CONTROL_CONT_BIT_MASK | MICO32_TIMER_CONTROL_STOP_BIT_MASK);
	
	/* ------------------- */
	/* Enable IRQ         */
	/* ------------------- */
	EE_mico32_enableIRQ();
	
	/* ------------------- */
	/* Background activity */
	/* ------------------- */
	SetRelAlarm(myAlarm, 2500, 2500);
	EE_timer_on();
	while(1)
		;

    return 0;
}


