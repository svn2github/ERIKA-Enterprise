/*
  Name: test1_main.c
  Copyright: Evidence Srl
  Author: Dario Di Stefano
  Date: 29/03/10 18.23
  Description: Uart isr test(polling, blocking mode).
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
	EE_uart_set_ISR_mode(EE_UART_POLLING | EE_UART_RXTX_BLOCK); // polling, blocking mode  
	
	/* ------------------- */
	/* Background activity */
	/* ------------------- */
	while(1)
		ActivateTask(myTask);

    return 0;
}

