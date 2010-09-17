/*
	Name: test4_main.c
	Copyright: Evidence Srl
	Author: Dario Di Stefano
	Date: 29/03/10 18.23
  	Description: 	Uart isr test(isr, non-blocking mode).
					This demo shows how to use UART driver for
					Lattice Mico32 device to send and receive characters. 
					The UART controller is configured in ISR mode and in 
					non-blocking mode for tx and rx.
					The demo is as shown in test1 but the led is turned on/off
					in the ISR callbacks. 
					The demo requires a RS232 serial connection with a 115200 bps,8N1 configuration.
*/

/* RT-Kernel */
#include <ee.h>
/* Platform description */
#include <system_conf.h>
/* Erika Mico32 interrupts */
#include <cpu/mico32/inc/ee_irq.h>
/* Lattice components */
#include <MicoMacros.h>

volatile int rx_cbk_counter = 0;
volatile int tx_cbk_counter = 0;
	
TASK(myTask)
{
    EE_UINT8 myArray[2];
    
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
    	if( EE_uart_send_byte(myArray[0]) < 0 )
    		while(1)
    			;
    
    /* Array test */
	myArray[0] = 'B';
	myArray[1] = 'C';
	if( EE_uart_send_buffer(myArray, 2) < 0 )
		while(1)
			;
 	if( EE_uart_receive_buffer(myArray, 2) < 0 )
	{
 		while( !(ee_uart_st.base->lsr & MICOUART_LSR_TX_RDY_MASK) )
			;
 		if( EE_uart_send_byte('Y') < 0 )
    		while(1)
    			;
 	}
    else
    	if( EE_uart_send_buffer(myArray, 2) < 0 )
    		while(1)
    			;
}

void rx_cbk(void)
{
	EE_led_off(EE_SERIO_SYSTEM_LED);
	rx_cbk_counter++; 
}

void tx_cbk(void)
{
	EE_led_on(EE_SERIO_SYSTEM_LED);
	tx_cbk_counter++; 
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
	EE_uart_set_rx_ISR_callback(rx_cbk);
	EE_uart_set_tx_ISR_callback(tx_cbk);
	EE_uart_config(115200, EE_UART_BIT8_NO | EE_UART_BIT_STOP_1);
	EE_uart_set_ISR_mode(EE_UART_RXTX_ISR); // isr, non-blocking mode  
	
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
	EE_led_init();
	SetRelAlarm(myAlarm, 1000, 5000);
	EE_timer_on();
	while(1)
		;

    return 0;
}


