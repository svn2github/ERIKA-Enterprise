/*
	Name: test1_main.c
	Copyright: Evidence Srl
	Author: Dario Di Stefano
	Date: 29/03/10 18.23
	Description: 	SPI polling test.
					In this demo is shown how to use SPI driver functions
					to communicate with an external device (MRF24J40 in this example).
					The demo requires a RS232 serial connection with a 115200 bps,8N1 configuration.
					The demo requires a SPI bus to communicate with the device.
					The demo requires a GPIO pin to turn on the device. 
					User has to indicate the number of the bit of the GPIO pin (see DEVICE_GPIO_BIT macro).
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
#include <stdio.h>
#include <stdarg.h>

#define MAX_CHARS 128
#define die(a)			myprintf("\nError! code: %d\n", a)

/* This function is used to send info by serial interface. */
void myprintf(const char* format, ...)
{
	char str[MAX_CHARS];
	
	va_list args;
	va_start( args, format );
	vsnprintf(str, MAX_CHARS, format, args);
	va_end( args );
	EE_uart_send_buffer((EE_UINT8*)str, strlen(str));
}

/* ----------------- */
/* My device driver */
#define MRF24J40_EADR0 					(0x05)
#define MRF24J40_SHORT_ADDRESS_MASK		(0x3F)
#define MRF24J40_SRCR					(0x00)
#define MRF24J40_SWCR					(0x01)
#define MRF24J40_DEVICE_ID				(0x01)
int device_write(EE_UINT32 address, EE_UINT8 data);
int device_read(EE_UINT32 address);
int device_print(EE_UINT8 data1, EE_UINT8 data2);
#define DEVICE_GPIO_BIT 		(1) //(4) // mask: (0x10) (fpga output)
#define device_config() EE_misc_gpio_write_bit_data(1, DEVICE_GPIO_BIT)
/* ----------------- */

TASK(myTask)
{
	int ret_data;
	static EE_UINT8 data = '9';
	
	if(data >= '9')
		data = '0';
	else
		data++;
	
	/* ---------------------------------------------------------------- */
	/* Write a short address register  */
	ret_data = device_write(MRF24J40_EADR0, data);
	if(ret_data < 0){
		die(1);
		while(1)
			;
	}
	
	/* ---------------------------------------------------------------- */
	/* Read a short address register  */
	ret_data = device_read(MRF24J40_EADR0);
	if(ret_data < 0){
		die(2);
		while(1)
			;
	}
	
	/* ---------------------------------------------------------------- */
	/* Print results  */
	device_print(data, ret_data);
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
	EE_uart_set_ISR_mode(EE_UART_POLLING | EE_UART_RXTX_BLOCK); // polling, blocking mode  
	
	/* -------------------------- */
	/* SPI configuration         */
	/* -------------------------- */
	EE_net_spi_config(0);
	
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
	device_config();
	SetRelAlarm(myAlarm, 1000, 1000);
	EE_timer_on();
		
	while(1)
		;
		
    return 0;
}

/* ------------------------------------------------------- */
/* Device driver functions                                 */
/* ------------------------------------------------------- */

int device_write(EE_UINT32 address, EE_UINT8 data)
{
	int ret;
	EE_UINT8 add = ((address & MRF24J40_SHORT_ADDRESS_MASK) << 1) | MRF24J40_SWCR;
	EE_UINT8 tx_data[2];
	
	tx_data[0] = add;
	tx_data[1] = data;
	EE_net_spi_set_slave(MRF24J40_DEVICE_ID);	
	EE_net_spi_set_SSO();
	ret = EE_net_spi_send_buffer(tx_data, 2);
	EE_net_spi_clear_SSO();
	
	return ret;
}

int device_read(EE_UINT32 address)
{
	int ret;
	EE_UINT8 add = ((address & MRF24J40_SHORT_ADDRESS_MASK) << 1);// | MRF24J40_SRCR;
	EE_UINT8 rx_data[1];
	EE_UINT8 tx_data[1];
	
	tx_data[0] = add;
	EE_net_spi_set_slave(MRF24J40_DEVICE_ID);	
	EE_net_spi_set_SSO();
	ret = EE_net_spi_send_buffer(tx_data, 1);
	ret = EE_net_spi_receive_buffer(rx_data, 1);
	EE_net_spi_clear_SSO();
	if (ret >= 0)
		ret = rx_data[0];
	
	return ret;
}

int device_print(EE_UINT8 data1, EE_UINT8 data2)
{
	char *str1 = "\nWrite s.a.r. :\n";
	char *str2 = "\nRead s.a.r. :\n";
	
	EE_uart_send_buffer((EE_UINT8 *)str1,strlen(str1));
	EE_uart_send_buffer(&data1, 1);
	EE_uart_send_buffer((EE_UINT8 *)str2,strlen(str2));
	EE_uart_send_buffer(&data2, 1);	
	
	return 0;
}








