/*
  Name: test2_main.c
  Copyright: Evidence Srl
  Author: Dario Di Stefano
  Date: 29/03/10 18.23
  Description: ENC28J60 driver function test (phy read and write, bfs, bfc).
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
#define turn_on_led() 		EE_misc_gpio_write_bit_data(1,EE_DL3_BIT)
#define turn_off_led() 		EE_misc_gpio_write_bit_data(0,EE_DL3_BIT)
#define device_config() 	EE_misc_gpio_write_bit_data(1, EE_GP1_BIT)
#define BANK0 0
#define BANK1 1
#define BANK2 2
#define BANK3 3
#define ETH_TYPE 0
#define MAC_TYPE 1
#define MII_TYPE 2
#define BANK_TYPE 3
#define BFC_TYPE 4
#define BFS_TYPE 5
#define PHY_TYPE 6
volatile EE_UINT8 mask;
volatile EE_UINT8 data = '0';
volatile EE_UINT8 ret_data;
volatile EE_UINT8 udata;
volatile EE_UINT16 phy_data;
volatile EE_UINT16 ret_phy_data;
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
	
	device_read(ETH_TYPE);
	print_string("\nRead ECON1:\n");
	udata = '0' + ret_data;
	EE_uart_send_buffer((EE_UINT8*)&udata, 1);
	
	/* ---------------------------------------------------------------- */
	/* ETH */
	data = 0x09;
	address = ETXNDL;
	
	device_write(ETH_TYPE);
	print_string("\nWrite ETXNDL:\n");
	udata = '0' + data;
	EE_uart_send_buffer((EE_UINT8*)&udata, 1);	
	
	device_read(ETH_TYPE);
	print_string("\nRead ETXNDL:\n");
	udata = '0' + ret_data;
	EE_uart_send_buffer((EE_UINT8*)&udata, 1);	
	
	mask = 0x0A;
	device_write(BFC_TYPE);
	print_string("\nBFC, ETXNDL expected:\n");
	udata = '0' + (data & ~mask);	
	EE_uart_send_buffer((EE_UINT8*)&udata, 1);	
	
	device_read(ETH_TYPE);
	print_string("\nRead ETXNDL:\n");
	udata = '0' + ret_data;
	EE_uart_send_buffer((EE_UINT8*)&udata, 1);	
	
	mask = 0x08;
	device_write(BFS_TYPE);
	print_string("\nBFS, ETXNDL expected:\n");
	udata = '0' + data;
	EE_uart_send_buffer((EE_UINT8*)&udata, 1);	
	
	device_read(ETH_TYPE);
	print_string("\nRead ETXNDL:\n");
	udata = '0' + ret_data;
	EE_uart_send_buffer((EE_UINT8*)&udata, 1);	
	
	/* ---------------------------------------------------------------- */
	/* PHY */
	phy_data = 0x3332;
	address = PHLCON;
	
	device_write(PHY_TYPE);
	//SetLEDConfig(0x3472);
	print_string("\nWrite PHLCON:\n");
	udata = 'x';
	EE_uart_send_buffer((EE_UINT8*)&udata, 1);	
	udata = '0' + ((phy_data&0xF000) >> 12);
	EE_uart_send_buffer((EE_UINT8*)&udata, 1);	
	udata = '0' + ((phy_data&0x0F00) >> 8);
	EE_uart_send_buffer((EE_UINT8*)&udata, 1);
	udata = '0' + ((phy_data&0x00F0) >> 4);
	EE_uart_send_buffer((EE_UINT8*)&udata, 1);	
	udata = '0' + (phy_data&0x000F);
	EE_uart_send_buffer((EE_UINT8*)&udata, 1);	
	
	device_read(PHY_TYPE);
	print_string("\nRead PHLCON:\n");
	udata = 'x';
	EE_uart_send_buffer((EE_UINT8*)&udata, 1);	
	udata = '0' + ((ret_phy_data&0xF000) >> 12);
	EE_uart_send_buffer((EE_UINT8*)&udata, 1);	
	udata = '0' + ((ret_phy_data&0x0F00) >> 8);
	EE_uart_send_buffer((EE_UINT8*)&udata, 1);
	udata = '0' + ((ret_phy_data&0x00F0) >> 4);
	EE_uart_send_buffer((EE_UINT8*)&udata, 1);	
	udata = '0' + (ret_phy_data&0x000F);
	EE_uart_send_buffer((EE_UINT8*)&udata, 1);

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
	SetRelAlarm(myAlarm, 500, 2000);
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
	if((type==ETH_TYPE) || (type==MAC_TYPE) || (type==MII_TYPE))
		WriteReg(address, data);
	else 
		if(type==BANK_TYPE)
			BankSel(address);
		else 
			if(type==BFC_TYPE)
				BFCReg(address, mask);
			else
				if(type==BFS_TYPE)
					BFSReg(address, mask);
				else
					if(type==PHY_TYPE)
						WritePHYReg(address, phy_data);
	return 0;
}

int device_read(int type)
{
	REG r;
	PHYREG pr;
	
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
				if(type==PHY_TYPE)
				{
					pr = ReadPHYReg(address);
					ret_phy_data = pr.Val;
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







