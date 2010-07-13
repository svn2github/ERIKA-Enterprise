/*
  Name: test2_main.c
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
#define EE_ENC28J60_DEVICE_ID		(0x01)
#define ENC28J60_ETXNDL		0x06
#define ENC28J60_MACLCON1	0x208
#define ENC28J60_MIREGADR	0x214
#define ENC28J60_ECON1		0x1F
#define BANK0 0
#define BANK1 1
#define BANK2 2
#define BANK3 3
int device_write(int type);
int device_read(int type);
int device_print(void);
#define EE_DL3_BIT 			(0) //(3) // mask: (0x08) (fpga output)
#define EE_GP1_BIT 			(1) //(4) // mask: (0x10) (fpga output)
#define turn_on_led() 		EE_misc_gpio_write_bit_data(1,EE_DL3_BIT)
#define turn_off_led() 		EE_misc_gpio_write_bit_data(0,EE_DL3_BIT)
#define device_config() 	EE_misc_gpio_write_bit_data(1, EE_GP1_BIT)
volatile EE_UINT8 data = '0';
volatile EE_UINT8 ret_data;
volatile EE_UINT8 udata;
volatile int address;
volatile int bank;
#define EE_enc28j60_set_slave(p1) 	EE_net_spi_set_slave(p1)
#define EE_enc28j60_set_SSO() 		EE_net_spi_set_SSO()
#define EE_enc28j60_clear_SSO()		EE_net_spi_clear_SSO()
#define EE_enc28j60_write_buffer(p1,p2)	EE_net_spi_send_buffer(p1, p2)
#define EE_enc28j60_read_buffer(p1,p2)	EE_net_spi_receive_buffer(p1, p2)
#define ETH_TYPE 0
#define MAC_TYPE 1
#define MII_TYPE 2
#define BANK_TYPE 3
#define ENC28J60_WCR (0x2<<5)				// Write Control Register command
#define ENC28J60_BFS (0x4<<5)				// Bit Field Set command
#define ENC28J60_BFC (0x5<<5)				// Bit Field Clear command
#define ENC28J60_RCR (0x0<<5)				// Read Control Register command
#define ENC28J60_RBM ((0x1<<5) | 0x1A)		// Read Buffer Memory command
#define ENC28J60_WBM ((0x3<<5) | 0x1A)		// Write Buffer Memory command
#define ENC28J60_SR  ((0x7<<5) | 0x1F)		// System Reset command does not use an address. // It requires 0x1F, however.                          			
#define	ENC28J60_ECON1_BSEL1	(1<<1)
#define	ENC28J60_ECON1_BSEL0	(1)
#define EE_ENC28J60_ADDRESS_MASK	(0x1F)
#define	ENC28J60_SUCCESS 			(0)		/* no error */
#define ENC28J60_ERXSTL		0x08
#define ENC28J60_EDMADSTL	0x14
/* ----------------- */

int print_string(const char *s)
{
	return EE_uart_send_buffer(s,strlen(s));
}

/*
 * Task 1
 */
TASK(myTask)
{
	//print_string("device_write: ERROR!\n");
	
	/* ---------------------------------------------------------------- */
	/* BANK SELECTION */
	bank = BANK0;
	device_write(BANK_TYPE);
	print_string("\nWrite bank:\n");
	udata = '0' + bank;
	EE_uart_send_buffer(&udata, 1);
	
	address = ENC28J60_ECON1;
	device_read(ETH_TYPE);
	print_string("\nRead ECON1:\n");
	udata = '0' + ret_data;
	EE_uart_send_buffer(&udata, 1);
	
	address = ENC28J60_ERXSTL;
	device_read(ETH_TYPE);
	print_string("\nRead ERXSTL:\n");
	udata = '0' + ret_data;
	EE_uart_send_buffer(&udata, 1);	
	
	address = ENC28J60_EDMADSTL;
	device_read(ETH_TYPE);
	print_string("\nRead EDMADSTL:\n");
	udata = '0' + ret_data;
	EE_uart_send_buffer(&udata, 1);	
	
	/* ---------------------------------------------------------------- */
	/* ETH */
	data = 0x09;
	address = ENC28J60_ETXNDL;
	device_write(ETH_TYPE);
	print_string("\nWrite ETXNDL:\n");
	udata = '0' + data;
	EE_uart_send_buffer(&udata, 1);	
	
	device_read(ETH_TYPE);
	print_string("\nRead ETXNDL:\n");
	udata = '0' + ret_data;
	EE_uart_send_buffer(&udata, 1);	
	
	/* ---------------------------------------------------------------- */
	/* BANK SELECTION */
	bank = BANK2;
	device_write(BANK_TYPE);
	print_string("\nWrite bank:\n");
	udata = '0' + bank;
	EE_uart_send_buffer(&udata, 1);
	
	address = ENC28J60_ECON1;
	device_read(ETH_TYPE);
	print_string("\nRead ECON1:\n");
	udata = '0' + ret_data;
	EE_uart_send_buffer(&udata, 1);	
	
	/* ---------------------------------------------------------------- */
	/* MAC */
	data = 0x08;
	address = ENC28J60_MACLCON1;
	device_write(MAC_TYPE);
	print_string("\nWrite MACLCON1:\n");
	udata = '0' + data;
	EE_uart_send_buffer(&udata, 1);	
	
	device_read(MAC_TYPE);
	print_string("\nRead MACLCON1:\n");
	udata = '0' + ret_data;
	EE_uart_send_buffer(&udata, 1);	
	
	/* ---------------------------------------------------------------- */
	/* MII */
	data = 0x07;
	address = ENC28J60_MIREGADR;
	device_write(MII_TYPE);
	print_string("\nWrite MIREGADR:\n");
	udata = '0' + data;
	EE_uart_send_buffer(&udata, 1);	
	
	device_read(MII_TYPE);
	print_string("\nRead MIREGADR:\n");
	udata = '0' + ret_data;
	EE_uart_send_buffer(&udata, 1);	
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

int EE_enc28j60_bank_select(EE_UINT8 bank)
{
	int ret;
	EE_UINT8 data[2]; 
	
	/* BIT FIELD CLEAR */
	EE_enc28j60_set_slave(EE_ENC28J60_DEVICE_ID);	
	EE_enc28j60_set_SSO();
	data[0] = ENC28J60_BFC | ENC28J60_ECON1;
	data[1] = ENC28J60_ECON1_BSEL1 | ENC28J60_ECON1_BSEL0;  
	ret = EE_enc28j60_write_buffer(data, 2);
	EE_enc28j60_clear_SSO();
	//if(ret == ...)
	
	/* BIT FIELD SET */
	EE_enc28j60_set_slave(EE_ENC28J60_DEVICE_ID);	
	EE_enc28j60_set_SSO();
	data[0] = ENC28J60_BFS | ENC28J60_ECON1;
	data[1] = bank;  
	ret = EE_enc28j60_write_buffer(data, 2);
	EE_enc28j60_clear_SSO();
	//if(ret == ...)
	
	return ret;
}

int EE_enc28j60_read_ETH_register(int address)
{
	int ret;
	EE_UINT8 add = address & EE_ENC28J60_ADDRESS_MASK;
	EE_UINT8 rx_data[1];
	EE_UINT8 tx_data[1];
	
	
	EE_enc28j60_set_slave(EE_ENC28J60_DEVICE_ID);	
	EE_enc28j60_set_SSO();
	tx_data[0] = ENC28J60_RCR | add;
	ret = EE_enc28j60_write_buffer(tx_data, 1);
	//EE_spi_clear_SSO();
	//if(ret = ...)
	//EE_spi_set_slave(EE_ENC28J60_DEVICE_ID);	
	//EE_spi_set_SSO();
	ret = EE_enc28j60_read_buffer(rx_data, 1);
	EE_enc28j60_clear_SSO();
	//if(ret = ...)
	
	if(ret >= 0)
		ret = rx_data[0];
	
	return ret;
}

int EE_enc28j60_read_MAC_register(int address)
{
	int ret;
	EE_UINT8 add = address & EE_ENC28J60_ADDRESS_MASK;
	EE_UINT8 rx_data[2];
	EE_UINT8 tx_data[1];
	
	EE_enc28j60_set_slave(EE_ENC28J60_DEVICE_ID);	
	EE_enc28j60_set_SSO();
	tx_data[0] = ENC28J60_RCR | add;
	ret = EE_enc28j60_write_buffer(tx_data, 1);
	//EE_spi_clear_SSO();
	//if(ret = ...)
	//EE_spi_set_slave(EE_ENC28J60_DEVICE_ID);	
	//EE_spi_set_SSO();
	ret = EE_enc28j60_read_buffer(rx_data, 2);
	EE_enc28j60_clear_SSO();
	//if(ret = ...)
	
	ret = rx_data[1];
	
	return ret;
}

int EE_enc28j60_read_MII_register(int address)
{
	int ret;
	EE_UINT8 add = address & EE_ENC28J60_ADDRESS_MASK;
	EE_UINT8 rx_data[2];
	EE_UINT8 tx_data[1];
	
	EE_enc28j60_set_slave(EE_ENC28J60_DEVICE_ID);	
	EE_enc28j60_set_SSO();
	tx_data[0] = ENC28J60_RCR | add;
	ret = EE_enc28j60_write_buffer(tx_data, 1);
	//EE_spi_clear_SSO();
	//if(ret = ...)
	//EE_spi_set_slave(EE_ENC28J60_DEVICE_ID);	
	//EE_spi_set_SSO();
	ret = EE_enc28j60_read_buffer(rx_data, 2);
	EE_enc28j60_clear_SSO();
	//if(ret = ...)
	
	ret = rx_data[1];
	
	return ret;
}

int EE_enc28j60_write_ETH_register(int address, EE_UINT8 data)
{
	int ret;
	EE_UINT8 add = address & EE_ENC28J60_ADDRESS_MASK;
	EE_UINT8 tx_data[2];
	
	EE_enc28j60_set_slave(EE_ENC28J60_DEVICE_ID);	
	EE_enc28j60_set_SSO();
	tx_data[0] = ENC28J60_WCR | add;
	tx_data[1] = data;
	ret = EE_enc28j60_write_buffer(tx_data, 2);
	EE_enc28j60_clear_SSO();
	//if(ret = ...)
	
	return ret;
}

int EE_enc28j60_write_MAC_register(int address, EE_UINT8 data)
{
	int ret;
	EE_UINT8 add = address & EE_ENC28J60_ADDRESS_MASK;
	EE_UINT8 tx_data[2];
	
	EE_enc28j60_set_slave(EE_ENC28J60_DEVICE_ID);	
	EE_enc28j60_set_SSO();
	tx_data[0] = ENC28J60_WCR | add;
	tx_data[1] = data;
	ret = EE_enc28j60_write_buffer(tx_data,2);
	EE_enc28j60_clear_SSO();
	//if(ret = ...)
	
	return ret;
}

int EE_enc28j60_write_MII_register(int address, EE_UINT8 data)
{
	int ret;
	EE_UINT8 add = address & EE_ENC28J60_ADDRESS_MASK;
	EE_UINT8 tx_data[2];
	
	EE_enc28j60_set_slave(EE_ENC28J60_DEVICE_ID);	
	EE_enc28j60_set_SSO();
	tx_data[0] = ENC28J60_WCR | add;
	tx_data[1] = data;
	ret = EE_enc28j60_write_buffer(tx_data,2);
	EE_enc28j60_clear_SSO();
	//if(ret = ...)
	
	return ret;
}

#if 0
/* EE_enc28j60_bit_field_set: only for ETH control register */
int EE_enc28j60_bit_field_set(int address, EE_UINT8 mask)
{
	int ret;
	EE_UINT8 add = address & EE_ENC28J60_ADDRESS_MASK;
	EE_UINT8 tx_data[2];
	
	/* BIT FIELD SET */
	EE_enc28j60_set_slave(EE_ENC28J60_DEVICE_ID);	
	EE_enc28j60_set_SSO();
	tx_data[0] = ENC28J60_BFS | add;	//ENC28J60_ECON1;
	tx_data[1] = mask;  
	ret = EE_enc28j60_write_buffer(tx_data, 2);
	EE_enc28j60_clear_SSO();
	//if(ret == ...)
	
	return ret;
}

/* EE_enc28j60_bit_field_clear: only for ETH control register */
int EE_enc28j60_bit_field_clear(int address, EE_UINT8 mask)
{
	int ret;
	EE_UINT8 add = address & EE_ENC28J60_ADDRESS_MASK;
	EE_UINT8 tx_data[2];
	
	/* BIT FIELD CLEAR */
	EE_enc28j60_set_slave(EE_ENC28J60_DEVICE_ID);	
	EE_enc28j60_set_SSO();
	tx_data[0] = ENC28J60_BFC | add;	//ENC28J60_ECON1;
	tx_data[1] = mask;					//ENC28J60_ECON1_BSEL1 | ENC28J60_ECON1_BSEL0;  
	ret = EE_enc28j60_write_buffer(tx_data, 2);
	EE_enc28j60_clear_SSO();
	//if(ret == ...)
    
	return ret;
}
#endif

int device_write(int type)
{
	int ret;
	
	if(type==ETH_TYPE)
		ret = EE_enc28j60_write_ETH_register(address, data);
	else 
		if(type==MAC_TYPE)
			ret = EE_enc28j60_write_MAC_register(address, data);
		else
			if(type==MII_TYPE)
				ret = EE_enc28j60_write_MII_register(address, data);
			else
				if(type==BANK_TYPE)
					ret = EE_enc28j60_bank_select(bank);
				else
					ret = -100;
	
	return ret;
}

int device_read(int type)
{
	if(type==ETH_TYPE)
		ret_data = EE_enc28j60_read_ETH_register(address);
	else 
		if(type==MAC_TYPE)
			ret_data = EE_enc28j60_read_MAC_register(address);
		else
			if(type==MII_TYPE)
				ret_data = EE_enc28j60_read_MII_register(address);
			else
				ret_data = -100;
	
	return ret_data;
}

int device_print(void)
{
	char *str1 = "\nWrite:\n";
	char *str2 = "\nRead:\n";
	
	EE_uart_send_buffer((EE_UINT8 *)str1,strlen(str1));
	EE_uart_send_buffer(&data, 1);
	EE_uart_send_buffer((EE_UINT8 *)str2,strlen(str2));
	EE_uart_send_buffer(&ret_data, 1);	
	
	return 0;
}








