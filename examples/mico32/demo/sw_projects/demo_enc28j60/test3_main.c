/*
  Name: test3_main.c
  Copyright: Evidence Srl
  Author: Dario Di Stefano
  Date: 29/03/10 18.23
  Description: ENC28J60 driver function test (software reset, checksum function).
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


/* ----------------- */
/* My device driver */
WORD _CalcIPBufferChecksum(WORD len);
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

TASK(myTask1)
{
	//print_string("device_write: ERROR!\n");
	
	/* ---------------------------------------------------------------- */
	/* ETH */
	data = 0x09;
	
	address = ECON1;
	
	device_read(ETH_TYPE);
	print_string("\nRead ECON1:\n");
	udata = '0' + ret_data;
	EE_uart_send_buffer((EE_UINT8*)&udata, 1);
	
	address = ETXNDL;
	
	device_read(ETH_TYPE);
	print_string("\nRead ETXNDL:\n");
	udata = '0' + ret_data;
	EE_uart_send_buffer((EE_UINT8*)&udata, 1);	
	
	device_write(ETH_TYPE);
	print_string("\nWrite ETXNDL:\n");
	udata = '0' + data;
	EE_uart_send_buffer((EE_UINT8*)&udata, 1);	
	
	device_read(ETH_TYPE);
	print_string("\nRead ETXNDL:\n");
	udata = '0' + ret_data;
	EE_uart_send_buffer((EE_UINT8*)&udata, 1);	
	
	/* ---------------------------------------------------------------- */
	/* SW RESET */
	SendSystemReset();
	
	/* ---------------------------------------------------------------- */
	/* Checksum */
	EE_UINT16 res;
	char str[64];
	res = _CalcIPBufferChecksum(3);
	sprintf(str, "\nChecksum: 0x%x\n", res);
	print_string(str);
}

TASK(myTask2)
{
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
	SetRelAlarm(myAlarm1, 500, 2000);
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



WORD _CalcIPBufferChecksum(WORD len)
{
	int i;
	char str[64];
    DWORD_VAL Checksum = {0x00000000ul};
    WORD ChunkLen;
    WORD DataBuffer[10];
    WORD *DataPtr;

	for(i=0; i<10; i++)
		DataBuffer[i] = 0xFFFF; 

    while(len)
    {
        // Obtain a chunk of data (less SPI overhead compared
        // to requesting one byte at a time)
        ChunkLen = len > sizeof(DataBuffer) ? sizeof(DataBuffer) : len;
        //MACGetArray((BYTE*)DataBuffer, ChunkLen);
        ((BYTE*)DataBuffer)[0] = 0x89;
        ((BYTE*)DataBuffer)[1] = 0xAB;
        ((BYTE*)DataBuffer)[2] = 0xCD;
    
        len -= ChunkLen;

        // Take care of a last odd numbered data byte
        if(((WORD_VAL*)&ChunkLen)->bits.b0)
        {
            ((BYTE*)DataBuffer)[ChunkLen] = 0x00;
            ChunkLen++;
        }

		print_string("\n");
		for(i=0; i<10; i++)	
		{
			sprintf(str, "DataBuffer[%d]: 0x%x\n", i, DataBuffer[i]);
			print_string(str);
		}

        // Calculate the checksum over this chunk
        DataPtr = DataBuffer;
        while(ChunkLen)
        {
            Checksum.Val += *DataPtr++;
            ChunkLen -= 2;
        }
    }
	sprintf(str, "Checksum.Val: 0x%x\n", Checksum.Val);
	print_string(str);

	// Do an end-around carry (one's complement arrithmatic)
	Checksum.Val = (DWORD)Checksum.w[0] + (DWORD)Checksum.w[1];
	sprintf(str, "Checksum.Val: 0x%x\n", Checksum.Val);
	print_string(str);
	
    // Do another end-around carry in case if the prior add
    // caused a carry out
    Checksum.w[0] += Checksum.w[1];
	sprintf(str, "Checksum.Val: 0x%x\n", Checksum.Val);
	print_string(str);
	
    // Return the resulting checksum
    return ~Checksum.w[0];
}



