/*
	Name: test1_main.c
	Copyright: Evidence Srl
	Author: Dario Di Stefano
	Date: 29/03/10 18.23
	Description: 	Uart polling test(blocking mode).
					This demo shows how to use UART driver for
					Lattice Mico32 device to send and receive characters. 
					The UART controller is configured in polling mode and in blocking mode 
					so it waits one character when task calls EE_uart_receive_byte 
					and it waits 5 characters when task calls EE_uart_receive_buffer.   
					In case of error the application turns on the system led.
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

TASK(myTask)
{
    EE_UINT8 myArray[5];
    
    /* Single byte test */
    myArray[0] = 'A';
    if( EE_uart_send_byte(myArray[0]) < 0 )
    {
    	EE_led_on(EE_SERIO_SYSTEM_LED);
		while(1)
			;
    }
 	if( EE_uart_receive_byte(myArray) < 0 )
 	{
 		EE_led_on(EE_SERIO_SYSTEM_LED);
		while(1)
			;
 	}
    else
    	if( EE_uart_send_byte(myArray[0]) < 0 )
    	{
    		EE_led_on(EE_SERIO_SYSTEM_LED);
    		while(1)
    			;
    	}
	/* Array test */
	myArray[0] = 'A';
	myArray[1] = 'B';
	myArray[2] = 'C';
	myArray[3] = 'D';
	myArray[4] = 'E';
	if( EE_uart_send_buffer(myArray, 5) < 0 )
	{
		EE_led_on(EE_SERIO_SYSTEM_LED);
		while(1)
			;
	}
 	if( EE_uart_receive_buffer(myArray, 5) < 0 )
 	{
 		EE_led_on(EE_SERIO_SYSTEM_LED);
		while(1)
			;
 	}
    else
    	if( EE_uart_send_buffer(myArray, 5) < 0 )
    	{
    		EE_led_on(EE_SERIO_SYSTEM_LED);
    		while(1)
    			;
    	}
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
	EE_led_init();
	while(1)
		ActivateTask(myTask);

    return 0;
}

