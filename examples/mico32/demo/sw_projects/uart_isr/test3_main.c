/*
  Name: test3_main.c
  Copyright: Evidence Srl
  Author: Dario Di Stefano
  Date: 29/03/10 18.23
  Description: Uart isr test(isr, blocking mode).
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
	
#define turn_on_led() 	EE_misc_gpio_write_bit_data(1,0)
#define turn_off_led() 	EE_misc_gpio_write_bit_data(0,0)

TASK(myTask)
{
    EE_UINT8 myArray[5];
    
    /* Single byte test */
    myArray[0] = 'A';
    if( EE_uart_send_byte(myArray[0]) < 0 )
		while(1)
			;
 	if( EE_uart_receive_byte(myArray) < 0 )
 		while(1)
    		;
    else
    	if( EE_uart_send_byte(myArray[0]) < 0 )
    		while(1)
    			;
    
    /* Array test */
	myArray[0] = 'A';
	myArray[1] = 'B';
	myArray[2] = 'C';
	myArray[3] = 'D';
	myArray[4] = 'E';
	if( EE_uart_send_buffer(myArray, 5) < 0 )
		while(1)
			;
 	if( EE_uart_receive_buffer(myArray, 5) < 0 )
		while(1)
			;
    else
    	if( EE_uart_send_buffer(myArray, 5) < 0 )
    		while(1)
    			;
}

void rx_cbk(void)
{
	turn_off_led();
	rx_cbk_counter++; 
}

void tx_cbk(void)
{
	turn_on_led();
	tx_cbk_counter++; 
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
	EE_uart_set_ISR_mode(EE_UART_RXTX_ISR | EE_UART_RXTX_BLOCK); // polling, blocking mode  
	
	/* ------------------- */
	/* Background activity */
	/* ------------------- */
	while(1)
		ActivateTask(myTask);

    return 0;
}

