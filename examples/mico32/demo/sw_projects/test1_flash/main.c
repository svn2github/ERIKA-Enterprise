
/* Standard library */
#include <stdio.h>
#include <stdarg.h>
#include <string.h>

#include "stdint.h"
#include "system_conf.h"
#include "DDStructs.h"
#include "MicoSPIFlash.h"
#include "MicoUart.h"


/* ***********************************************************************
 * UART Function
 * ********************************************************************* */

static MicoUart_t * const uartc = (MicoUart_t *)UART_BASE_ADDRESS;

void put_byte(const int8_t msg)
{
    uartc->lcr = 0x3; // 8N1
        while (! (uartc->lsr & MICOUART_LSR_TX_RDY_MASK))
            ;
    uartc->rxtx = msg;
}

void put_string(int8_t *str, uint16_t len)
{
	uint16_t i;
	
	for(i = 0; i < len; i++) {
		put_byte((int8_t)str[i]);
	}	
}

void print_string(int8_t *str)
{
	uint16_t i;
	
	i = 0;
	while (str[i] != '\0') {
		put_byte(str[i++]);
	}	
}

int16_t get_byte(void)
{
    while (! (uartc->lsr & MICOUART_LSR_RX_RDY_MASK))
    	;
    return uartc->rxtx;
}

/* Return an unsigned integer of `size' bytes read from UART in big-endian
 * order.  Wait until all bytes are arrived. */
uint32_t get_uint(uint32_t size)
{
    uint32_t data = 0;
    uint32_t k;
    for (k = 0; k < size; ++k)
        data = (data << 8) | get_byte();
    return data;
    
}

/* Return an 8-bit unsigned integer read from UART. Wait until all bytes are
 * arrived. */
uint8_t get_uint8(void)
{
    return (uint8_t) get_uint(1);
}

/* Return an 16-bit unsigned integer read from UART in big-endian order.  Wait
 * until all bytes are arrived. */
uint16_t get_uint16(void)
{
    return (uint16_t)get_uint(2);
}

/* Return an 32-bit unsigned integer read from UART in big-endian order.  Wait
 * until all bytes are arrived. */
uint32_t get_uint32(void)
{
    return get_uint(4);
}

/* A printf-like function */
void my_printf(const char *format, ...)
{
#define MAXCHARS 128
    int8_t printf_trunc[] = "..[TRUNCATED]..\r\n";
    int8_t str[MAXCHARS];
    uint16_t len;
    va_list args;
    va_start(args, format);
    len = vsnprintf((int8_t*)str, MAXCHARS, format, args);
    va_end(args);
    if (len > MAXCHARS - 1) {
        /* vsnptintf() returns the number of characters needed */
        put_string(str, MAXCHARS - 1 );
        put_string(printf_trunc, sizeof(printf_trunc) - 1);
    } else {
        put_string(str, len);
    }
}

int int2str(char strbuf[], int32_t num, int has_sign, unsigned int base,
    unsigned int min_dig)
{
    const char hexdig[] = "0123456789abcdef";
    int c = 0;
    uint32_t weight;
    uint32_t n;
    unsigned k;
    const unsigned maxu = 0xffffffff;
    if (has_sign && num < 0) {
        strbuf[c++] = '-';
        n = -num;
    } else {
        n = num;
    }
    /* weight = base ^ log( n ) */
    weight = 1;
    k = 1;
    while (1) {
        uint32_t nextw = weight * base;
        if (weight > maxu / base)
            /* Avoid Overflow */
            break;
        if (nextw > n && k >= min_dig)
            break;
        weight = nextw;
        ++k;
    }
    /* Build string */
    while (1) {
        uint32_t d = n / weight;
        strbuf[c++] = hexdig[d];
        if (weight == 1)
            break;
        n = n % weight;
        weight /= base;
    }
    strbuf[c] = 0;
    return c;
}

static void dump_memory(void *base, unsigned size)
{
    /* Use a line-buffer, for the slooow Jtag interface */
    unsigned char *p = base;
    char lbuf[10 + 16*3 + 4];
    unsigned k, j;
    
    j = 0;
    for (k = 0; k < size; ++k) {
        if (0 == j) {
            j = int2str(lbuf, (unsigned)&p[k], 0, 16, 8);
            lbuf[j++] = ':';
            lbuf[j++] = ' ';
        }
        int2str(&lbuf[j], p[k], 0, 16, 2);
        j += 2;
        lbuf[j++] = ' ';
        if (0 == ((k+1) % 16) || k == size-1) {
            lbuf[j++] = '\r';        	
            lbuf[j++] = '\n';
            lbuf[j] = 0;
            print_string(lbuf);
            j = 0;
        } else if (0 == ((k+1) % 8)) {
            lbuf[j++] = ' ';
        }
    }
}

static unsigned read_hex_num(void)
{
    int c;
    unsigned n = 0, d;
    int end = 0;
    char s[2];

    while (1) {
        do {
            c = get_byte();
        } while (c == -1);
        s[0] = c;
        s[1] = 0;
        print_string(s);
        if (c >= '0' && c <= '9')
            d = c - '0';
        else if (c >= 'a' && c <= 'f')
            d = c - 'a' + 10;
        else if (c >= 'A' && c <= 'F')
            d = c - 'A' + 10;
        else
            end = 1;
        if (end)
            break;
        n = n * 16U + d;
    }
    return n;
}

static void dump_memory_pages(void *base, unsigned size, unsigned page_size)
{
    char *p = base;
    unsigned offset = 0;
    int c;

    while (offset < size) {
        unsigned len = offset + page_size > size ? size - offset : page_size;
        dump_memory(&p[offset], len);
        print_string("j = new address; any key = next page\r\n");
        do {
            c = get_byte();
        } while (c == -1);
        offset += page_size;
        if (c == 'j') {
            print_string("New address? ");
            unsigned addr = read_hex_num();
            unsigned newoffs = addr - (unsigned)base;
            if (addr >= (unsigned)base && newoffs < size)
                offset = newoffs & ~0xf;
            else
                print_string("Invalid address! continuing...\r\n");
        }
    }
}

/* ***********************************************************************
 * UART Function End
 * ********************************************************************* */

static void spi_flash_write_buffer(unsigned int ctrl_base, unsigned int addr,
    unsigned char *data, unsigned int len)
{
	unsigned char* pun_flash = (unsigned char*) addr;
	unsigned int value, k;
	
	for(k = 0; k < len; k++){
		*pun_flash = *data;						
		MICO_SPI_CMD_CFG_WR_BYTE_PROGRAM(ctrl_base, *pun_flash);
		do {
			MICO_SPI_STATUS_READ (ctrl_base, value);
			if ((0x00000001 & value) == 0)
				break;
		} while (1);
		pun_flash++;
		data++;
	}
}

void LatticeDDInit(void)
{

    /* initialize LM32 instance of lm32_top */
    LatticeMico32Init(&lm32_top_LM32);
                           
    /* initialize SPIFlash_boot instance of spi_flash */
    //MicoSPIFlash_Initialize(&spi_flash_SPIFlash_boot);
    
	uint32_t i, value;
	uint8_t wdata[1024];
	
	MicoSPIFlashCtx_t* spi_flash = &spi_flash_SPIFlash_boot;
    
    put_byte(get_byte());
    
	my_printf("Erase flash memory:.... ");
	MicoSPIFlash_WriteEnable(spi_flash);
	MICO_SPI_CHIP_ERASE(spi_flash->control_base);
	do {
		MICO_SPI_STATUS_READ (spi_flash->control_base, value);
		if ((0x00000001 & value) == 0)
			break;
	} while (1);
	my_printf("done.\r\n");
		
    print_string("Dumping first 1024 byte from flash memory... \r\n");
    dump_memory_pages((void *)SPIFLASH_BOOT_BASE_ADDRESS, 1024, 256);
	
	for (i = 0; i < 1024; i++)
		wdata[i] = 0xFF - i;
	
	my_printf("Write 1024 bytes from address 0: ....\r\n");
	MicoSPIFlash_WriteEnable(spi_flash);
	spi_flash_write_buffer(spi_flash->control_base, SPIFLASH_BOOT_BASE_ADDRESS,
    	wdata, 1024);

    print_string("Dumping first 1024 byte from flash memory... \r\n");
    dump_memory_pages((void *)SPIFLASH_BOOT_BASE_ADDRESS, 2048, 256);
	my_printf("\r\n");
        
	return;
}