/*
  Name: main.c
  Copyright: Evidence Srl
  Author: Dario Di Stefano
  Date: 29/03/10 18.23
  Description: SPI polling regression test (test with ENC28J60 driver).
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
#include <stdarg.h>

/* ----------------- */
/* device driver macros */
#define turn_on_led() 			EE_misc_gpio_write_bit_data(1,EE_DL3_BIT)
#define turn_off_led() 			EE_misc_gpio_write_bit_data(0,EE_DL3_BIT
void device_config(void)
{
	BYTE i;
	EE_misc_gpio_write_bit_data(1, EE_GP1_BIT);
	do {
        SendSystemReset();
        i = ReadETHReg(ESTAT).Val;
    } while((i & 0x08) || (~i & ESTAT_CLKRDY));
}
/* ----------------- */

int print_string(const char *s)
{
	return EE_uart_send_buffer((EE_UINT8*)s,strlen(s));
}

void system_timer_callback(void)
{
	/* count the interrupts, waking up expired alarms */
	CounterTick(myCounter);
}

#define DATA_LEN 1500
#define MAX_CHARS 128

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
	/* SPI configuration         */
	/* -------------------------- */
	EE_net_spi_config(0);

	/* -------------------------- */
	/* Uart configuration         */
	/* -------------------------- */
	EE_uart_config(115200, EE_UART_BIT8_NO | EE_UART_BIT_STOP_1);
	EE_uart_set_ISR_mode(EE_UART_POLLING | EE_UART_RXTX_BLOCK); // polling, blocking mode  
	
	/* ------------------- */
	/* Kernel timer configuration */
	/* ------------------- */
	EE_timer_set_ISR_callback(system_timer_callback);
	EE_timer_init(MILLISECONDS_TO_TICKS(1), MICO32_TIMER_CONTROL_INT_BIT_MASK | MICO32_TIMER_CONTROL_CONT_BIT_MASK);
	
	/* ------------------- */
	/* Enable IRQ         */
	/* ------------------- */
	EE_mico32_enableIRQ();
	
	/* ------------------- */
	/* Background activity */
	/* ------------------- */
	print_string("\nRegression test!\n");
	device_config();
	turn_on_led();
	SetRelAlarm(myAlarm, 1000, 1000);
	EE_timer_on();
		
	while(1)
		;
		
    return 0;
}

/* ------------------------------------------------------- */
/* Regression test task                                    */
/* ------------------------------------------------------- */
void myprintf(const char* format, ...)
{
	char str[MAX_CHARS];
	va_list args;
	va_start( args, format );
	vsnprintf(str, MAX_CHARS, format, args);
	va_end( args );
	EE_uart_send_buffer((EE_UINT8*)str, strlen(str));
}

void print_buffer(const char* name, BYTE* buf)
{
	int i;
	myprintf(name);
	myprintf(":\n");
    for(i=0; i<DATA_LEN; i++)
    {
    	myprintf(name);
    	myprintf("[%3d]:0x%4x  ", i, buf[i]);
    }
	myprintf("\n");
}

void buffer_write_and_read_test(BYTE* txv, BYTE* rxv, int len)
{
	print_string("wr start!\n");
	// Set the SPI write pointer to the beginning of the transmit buffer (post per packet control byte)
    EE_enc28j60_write_register(EWRPTL, LOW(TXSTART+1));
    EE_enc28j60_write_register(EWRPTH, HIGH(TXSTART+1));
    print_string("put start!\n");
	EE_enc28j60_mac_put_array(txv, len);
	print_string("put end!\n");
	// Read the transmitted vector
	EE_enc28j60_write_register(ERDPTL, LOW(TXSTART+1));
    EE_enc28j60_write_register(ERDPTH, HIGH(TXSTART+1));
    print_string("get start!\n");
    EE_enc28j60_mac_get_array(rxv, len);
    print_string("get end!\n");
    print_string("wr end!\n");
}

void compare_vars(const char* name, EE_UINT32 val1, EE_UINT32 val2)
{
	myprintf(name);
	if(val1 == val2)
		myprintf(": OK!\n");
	else
		myprintf(": FAILURE!\n");
}

void compare_bufs(const char* name, EE_UINT8 *val1, EE_UINT8 *val2, int len)
{
	int i;
	myprintf(name);
	for(i=0; i<len; i++)
	{
		if(val1[i] != val2[i])
		{
			myprintf(": FAILURE! ind=%d  val1=%d val2=%d\n", i, val1[i], val2[i]);
			REG res = EE_enc28j60_read_ETH_register(ESTAT);
			myprintf("ESTAT: 0x%x\n", res.Val);
			while(1);
			return;
		}
	}
	myprintf(": OK!\n");
}

TASK(myTask)
{
	/* initialization */
	int i;
	BYTE tx_data[DATA_LEN];
	BYTE rx_data[DATA_LEN];
	for(i=0; i<DATA_LEN; i++)
	{
		rx_data[i] = 0;
		tx_data[i] = i + 1;
	}
	
	/* Single byte test:  
	 * This section of the test is used to verify the functioning
	 * of the spi driver functions that work with single bytes: 
	 * EE_hal_spi_write_byte_polling
	 * EE_hal_spi_read_byte_polling 
	 * */
	REG res;	
	BYTE tx_val, rx_val;
	
	WORD Register = EWRPTL;
	EE_enc28j60_bank_select(Register);
	tx_val = ((WORD_VAL*)&Register)->byte.HB;
	res = EE_enc28j60_read_ETH_register(ECON1);
	rx_val = res.Val;
	myprintf("write bank: %d\n", tx_val);
	myprintf("read ECON1: %d\n", rx_val);
	compare_vars("test bank", tx_val, rx_val);

	tx_val = 0xF0;
	EE_enc28j60_write_register(ERXSTL, tx_val);
	res = EE_enc28j60_read_ETH_register(ERXSTL);
	rx_val = res.Val;
	myprintf("write ERXSTL: %d\n", tx_val);
	myprintf("read ERXSTL: %d\n", rx_val);
	compare_vars("test ERXSTL", tx_val, rx_val);
	
	tx_val = 0x1F;
	EE_enc28j60_write_register(ERXSTH, tx_val);
	res = EE_enc28j60_read_ETH_register(ERXSTH);
	rx_val = res.Val;
	myprintf("write ERXSTH: %d\n", tx_val);
	myprintf("read ERXSTH: %d\n", rx_val);
	compare_vars("test ERXSTH", tx_val, rx_val);
	
	tx_val = 0xF0;
	EE_enc28j60_write_register(ERXRDPTL, tx_val);
	res = EE_enc28j60_read_ETH_register(ERXRDPTL);
	rx_val = res.Val;
	myprintf("write ERXRDPTL: %d\n", tx_val);
	myprintf("read ERXRDPTL: %d\n", rx_val);
	
	tx_val = 0x1F;
	EE_enc28j60_write_register(ERXRDPTH, tx_val);
	res = EE_enc28j60_read_ETH_register(ERXRDPTH);
	rx_val = res.Val;
	myprintf("write ERXRDPTH: %d\n", tx_val);
	myprintf("read ERXRDPTH: %d\n", rx_val);
	res = EE_enc28j60_read_ETH_register(ERXRDPTL);
	rx_val = res.Val;
	myprintf("read ERXRDPTL: %d\n", rx_val);
	
	/* Buffer test:  
	 * This section of the test is used to verify the functioning
	 * of the spi driver functions that work with buffers: 
	 * EE_hal_spi_write_buffer_polling
	 * EE_hal_spi_read_buffer_polling
	 * */
	int len;
	//print_buffer("tx_data", tx_data);
	
	len = 1;
	buffer_write_and_read_test(tx_data, rx_data, len);
	//print_buffer("rx_data", rx_data);
	compare_bufs("test len=1", tx_data, rx_data, len);
	myprintf("PUT_ARRAY: %u\n", enc28j60_time_diff_us(EE_enc28j60_read_timestamp(ENC28J60_START_PUT_ARRAY), EE_enc28j60_read_timestamp(ENC28J60_END_PUT_ARRAY)));
	myprintf("GET_ARRAY: %u\n", enc28j60_time_diff_us(EE_enc28j60_read_timestamp(ENC28J60_START_GET_ARRAY), EE_enc28j60_read_timestamp(ENC28J60_END_GET_ARRAY)));
	EE_enc28j60_reset_timestamp();
	
	len = 2;
	buffer_write_and_read_test(tx_data, rx_data, len);
	//print_buffer("rx_data", rx_data);
	compare_bufs("test len=2", tx_data, rx_data, len);
	myprintf("PUT_ARRAY: %u\n", enc28j60_time_diff_us(EE_enc28j60_read_timestamp(ENC28J60_START_PUT_ARRAY), EE_enc28j60_read_timestamp(ENC28J60_END_PUT_ARRAY)));
	myprintf("GET_ARRAY: %u\n", enc28j60_time_diff_us(EE_enc28j60_read_timestamp(ENC28J60_START_GET_ARRAY), EE_enc28j60_read_timestamp(ENC28J60_END_GET_ARRAY)));
	EE_enc28j60_reset_timestamp();
	
	len = 3;
	buffer_write_and_read_test(tx_data, rx_data, len);
	//print_buffer("rx_data", rx_data);
	compare_bufs("test len=3", tx_data, rx_data, len);
	myprintf("PUT_ARRAY: %u\n", enc28j60_time_diff_us(EE_enc28j60_read_timestamp(ENC28J60_START_PUT_ARRAY), EE_enc28j60_read_timestamp(ENC28J60_END_PUT_ARRAY)));
	myprintf("GET_ARRAY: %u\n", enc28j60_time_diff_us(EE_enc28j60_read_timestamp(ENC28J60_START_GET_ARRAY), EE_enc28j60_read_timestamp(ENC28J60_END_GET_ARRAY)));
	EE_enc28j60_reset_timestamp();
	
	len = DATA_LEN;
	buffer_write_and_read_test(tx_data, rx_data, len);
	//print_buffer("rx_data", rx_data);
	compare_bufs("test len=DATA_LEN", tx_data, rx_data, len);
	myprintf("PUT_ARRAY: %u\n", enc28j60_time_diff_us(EE_enc28j60_read_timestamp(ENC28J60_START_PUT_ARRAY), EE_enc28j60_read_timestamp(ENC28J60_END_PUT_ARRAY)));
	myprintf("GET_ARRAY: %u\n", enc28j60_time_diff_us(EE_enc28j60_read_timestamp(ENC28J60_START_GET_ARRAY), EE_enc28j60_read_timestamp(ENC28J60_END_GET_ARRAY)));
	EE_enc28j60_reset_timestamp();
	
}












