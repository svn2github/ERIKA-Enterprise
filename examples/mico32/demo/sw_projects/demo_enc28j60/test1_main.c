/*
  Name: test1_main.c
  Copyright: Evidence Srl
  Author: Dario Di Stefano
  Date: 29/03/10 18.23
  Description: ENC28J60 driver function test (eth mac mii read and write, bank selection).
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
int device_write(int type);
int device_read(int type);
int device_print(void);
#define turn_on_led() 			EE_misc_gpio_write_bit_data(1,EE_DL3_BIT)
#define turn_off_led() 			EE_misc_gpio_write_bit_data(0,EE_DL3_BIT)
#define device_config() 		EE_misc_gpio_write_bit_data(1, EE_GP1_BIT)
#define BANK0 0
#define BANK1 1
#define BANK2 2
#define BANK3 3
#define ETH_TYPE 0
#define MAC_TYPE 1
#define MII_TYPE 2
#define BANK_TYPE 3
volatile EE_UINT8 data = '0';
volatile EE_UINT8 ret_data;
volatile EE_UINT8 udata;
volatile int address;
volatile int bank;
/* ----------------- */

int print_string(const char *s)
{
	return EE_uart_send_buffer((EE_UINT8*)s,strlen(s));
}

TASK(myTask)
{
	//print_string("device_write: ERROR!\n");
	
	/* ---------------------------------------------------------------- */
	/* BANK SELECTION */
	bank = BANK0;
	address = ECON1;
	device_write(BANK_TYPE);
	print_string("\nWrite bank:\n");
	udata = '0' + bank;
	EE_uart_send_buffer((EE_UINT8*)&udata, 1);
	
	address = ECON1;
	device_read(ETH_TYPE);
	print_string("\nRead ECON1:\n");
	udata = '0' + ret_data;
	EE_uart_send_buffer((EE_UINT8*)&udata, 1);
	
	address = ERXSTL;
	device_read(ETH_TYPE);
	print_string("\nRead ERXSTL:\n");
	udata = '0' + ret_data;
	EE_uart_send_buffer((EE_UINT8*)&udata, 1);	
	
	address = EDMADSTL;
	device_read(ETH_TYPE);
	print_string("\nRead EDMADSTL:\n");
	udata = '0' + ret_data;
	EE_uart_send_buffer((EE_UINT8*)&udata, 1);	
	
	/* ---------------------------------------------------------------- */
	/* ETH */
	data = 0x01;
	address = ETXNDL;
	device_write(ETH_TYPE);
	print_string("\nWrite ETXNDL:\n");
	udata = '0' + data;
	EE_uart_send_buffer((EE_UINT8*)&udata, 1);	
	
	device_read(ETH_TYPE);
	print_string("\nRead ETXNDL:\n");
	udata = '0' + ret_data;
	EE_uart_send_buffer((EE_UINT8*)&udata, 1);	
	
	/* ---------------------------------------------------------------- */
	/* BANK SELECTION */
	bank = BANK2;
	address = MACLCON1;
	device_write(BANK_TYPE);
	print_string("\nWrite bank:\n");
	udata = '0' + bank;
	EE_uart_send_buffer((EE_UINT8*)&udata, 1);
	
	address = ECON1;
	device_read(ETH_TYPE);
	print_string("\nRead ECON1:\n");
	udata = '0' + ret_data;
	EE_uart_send_buffer((EE_UINT8*)&udata, 1);	
	
	/* ---------------------------------------------------------------- */
	/* MAC */
	data = 0x02;
	address = MACLCON1;
	device_write(MAC_TYPE);
	print_string("\nWrite MACLCON1:\n");
	udata = '0' + data;
	EE_uart_send_buffer((EE_UINT8*)&udata, 1);	
	
	device_read(MAC_TYPE);
	print_string("\nRead MACLCON1:\n");
	udata = '0' + ret_data;
	EE_uart_send_buffer((EE_UINT8*)&udata, 1);	
	
	/* ---------------------------------------------------------------- */
	/* MII */
	data = 0x03;
	address = MIREGADR;
	device_write(MII_TYPE);
	print_string("\nWrite MIREGADR:\n");
	udata = '0' + data;
	EE_uart_send_buffer((EE_UINT8*)&udata, 1);	
	
	device_read(MII_TYPE);
	print_string("\nRead MIREGADR:\n");
	udata = '0' + ret_data;
	EE_uart_send_buffer((EE_UINT8*)&udata, 1);	
	/* ---------------------------------------------------------------- */

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

int device_write(int type)
{
	if(type!=BANK_TYPE)
		WriteReg(address, data);
	else 
		BankSel(address);
		
	return 0;
}

int device_read(int type)
{
	REG r;
	
	if(type==ETH_TYPE)
	{
		r = ReadETHReg(address);
		ret_data = r.Val; // = EE_enc28j60_read_ETH_register(address);
	}
	else 
		if(type==MAC_TYPE)
		{
			r = ReadMACReg(address);
			ret_data = r.Val; // = EE_enc28j60_read_MAC_register(address);
		}
		else
			if(type==MII_TYPE)
			{
				r = ReadMACReg(address);
				ret_data = r.Val; // = EE_enc28j60_read_MII_register(address);
			}
			else
				ret_data = -100;
	
	return ret_data;
}

int device_print(void)
{
	char *str1 = "\nWrite:\n";
	char *str2 = "\nRead:\n";
	
	EE_uart_send_buffer((EE_UINT8 *)str1,strlen(str1));
	EE_uart_send_buffer((EE_UINT8*)&data, 1);
	EE_uart_send_buffer((EE_UINT8 *)str2,strlen(str2));
	EE_uart_send_buffer((EE_UINT8*)&ret_data, 1);	
	
	return 0;
}







