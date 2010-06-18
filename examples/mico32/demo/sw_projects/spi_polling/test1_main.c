/*
  Name: test1_main.c
  Copyright: Evidence Srl
  Author: Dario Di Stefano
  Date: 29/03/10 18.23
  Description: SPI polling test.
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

/* ----------------- */
/* My device driver */
#define EE_MRF24J40_EADR0 					(0x05)
#define EE_MRF24J40_SHORT_ADDRESS_MASK		(0x3F)
#define EE_MRF24J40_SRCR					(0x00)
#define EE_MRF24J40_SWCR					(0x01)
#define EE_MRF24J40_DEVICE_ID				(0x01)
int device_write(void);
int device_read(void);
int device_print(void);
#define EE_DL3_BIT 		(0) //(3) // mask: (0x08) (fpga output)
#define EE_GP1_BIT 		(1) //(4) // mask: (0x10) (fpga output)
#define turn_on_led() 	EE_misc_gpio_write_bit_data(1,EE_DL3_BIT)
#define turn_off_led() 	EE_misc_gpio_write_bit_data(0,EE_DL3_BIT)
#define device_config() EE_misc_gpio_write_bit_data(1, EE_GP1_BIT)
EE_UINT8 data = '0';
EE_UINT8 ret_data;
int address = EE_MRF24J40_EADR0; 
/* ----------------- */

int print_string(const char *s)
{
	return EE_uart_send_buffer(s,strlen(s));
}

TASK(myTask)
{
	int ret;
	
	data++;
	if(data > '9')
		data = '0';
	
	/* ---------------------------------------------------------------- */
	/* Write a short address register  */
	ret = device_write();
	if(ret<0)
	{
		print_string("device_write: ERROR!\n");
		while(1);
	}
	
	/* ---------------------------------------------------------------- */
	/* Read a short address register  */
	ret = device_read();
	if(ret<0)
	{
		print_string("device_read: ERROR!\n");
		while(1);
	}
	ret_data = ret;
	
	device_print();
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
	turn_on_led();
	SetRelAlarm(myAlarm, 1000, 1000);
	EE_timer_on();
		
	while(1)
		;
		
    return 0;
}

/* ------------------------------------------------------- */
/* Device driver functions                                 */
/* ------------------------------------------------------- */

int device_write(void)
{
	int ret;
	EE_UINT8 add = ((address & EE_MRF24J40_SHORT_ADDRESS_MASK) << 1) | EE_MRF24J40_SWCR;
	EE_UINT8 tx_data[2];
	
	tx_data[0] = add;
	tx_data[1] = data;
	EE_net_spi_set_slave(EE_MRF24J40_DEVICE_ID);	
	EE_net_spi_set_SSO();
	ret = EE_net_spi_send_buffer(tx_data, 2);
	EE_net_spi_clear_SSO();
	
	return ret;
}

int device_read(void)
{
	int ret;
	EE_UINT8 add = ((address & EE_MRF24J40_SHORT_ADDRESS_MASK) << 1);// | MRF24J40_SRCR;
	EE_UINT8 rx_data[1];
	EE_UINT8 tx_data[1];
	
	tx_data[0] = add;
	EE_net_spi_set_slave(EE_MRF24J40_DEVICE_ID);	
	EE_net_spi_set_SSO();
	ret = EE_net_spi_send_buffer(tx_data, 1);
	ret = EE_net_spi_receive_buffer(rx_data, 1);
	EE_net_spi_clear_SSO();
	if (ret >= 0)
		ret = rx_data[0];
	
	return ret;
}

int device_print(void)
{
	char *str1 = "\nWrite s.a.r. :\n";
	char *str2 = "\nRead s.a.r. :\n";
	
	EE_uart_send_buffer((EE_UINT8 *)str1,strlen(str1));
	EE_uart_send_buffer(&data, 1);
	EE_uart_send_buffer((EE_UINT8 *)str2,strlen(str2));
	EE_uart_send_buffer(&ret_data, 1);	
	
	return 0;
}








