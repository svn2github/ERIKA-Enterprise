/*
  Name: test4_main.c
  Copyright: Evidence Srl
  Author: Dario Di Stefano
  Date: 29/03/10 18.23
  Description: ENC28J60 driver function test (transmission test).
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

/* ----------------------------------------------------------- */
/* My device driver */
/* ----------------------------------------------------------- */
int device_write(int type);
int device_read(int type);
int device_print(void);
void device_config(void);
#define turn_on_led() 		EE_misc_gpio_write_bit_data(1,EE_DL3_BIT)
#define turn_off_led() 		EE_misc_gpio_write_bit_data(0,EE_DL3_BIT)
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

/* ----------------------------------------------------------- */
/* Macros */
/* ----------------------------------------------------------- */
#define SIZE_OF_ETH_HEADER 			(14)
#define SIZE_OF_IP_HEADER 			(20)
#define SIZE_OF_UDP_HEADER 			(8)
#define SIZE_OF_PAYLOAD 			(4)
#define ETHTYPE_ARP       			(0x0806)
#define ETHTYPE_IP        			(0x0800)
#if 0
/* MICO32-PC simulation */
#define DEST_MAC_BYTE1            	(0x00)	
#define DEST_MAC_BYTE2            	(0x1E)	
#define DEST_MAC_BYTE3            	(0x33)	
#define DEST_MAC_BYTE4            	(0xC9)	
#define DEST_MAC_BYTE5            	(0xD6)	
#define DEST_MAC_BYTE6            	(0xAA)	
#define myIPaddress					(0xc0a80002)
#define myPort						(9760)
#define remoteIPaddress				(0xc0a80001)
#define remotePort					(9761)
#define MSG_BYTE1					(0xAA)
#define MSG_BYTE2					(0xBB)
#define MSG_BYTE3					(0xCC)
#define MSG_BYTE4					(0xDD)
#define UDP_CHKSUM					(0x0000)
#define UDP_LEN						(0x000c)
#define IP_ID						(0x0005)
#define TTL_PROTO					(0x6411)
#define IP_CHKSUM					(0xd574)
/**/
#else
/* MICO32-DSPIC simulation */
#define DEST_MAC_BYTE1            	(0x00)	// Use the default of
#define DEST_MAC_BYTE2            	(0x04)	// 00-04-A3-00-00-00 if using
#define DEST_MAC_BYTE3            	(0xA3)	// an ENCX24J600 or ZeroG ZG2100
#define DEST_MAC_BYTE4            	(0x00)	// and wish to use the internal
#define DEST_MAC_BYTE5            	(0x00)	// factory programmed MAC
#define DEST_MAC_BYTE6            	(0x00)	// address instead.
#define myIPaddress					(0xc0a80001)
#define myPort						(9762)
#define remoteIPaddress				(0xc0a80002)
#define remotePort					(9760)
#define MSG_BYTE1					(0x00)
#define MSG_BYTE2					(0x00)
#define MSG_BYTE3					(0x80)
#define MSG_BYTE4					(0x40)
#define UDP_CHKSUM					(0xB1FF)
#define UDP_LEN						(0x000c)
#define IP_ID						(0xD5CD)
#define TTL_PROTO					(0x8011)
#define IP_CHKSUM					(0xe3ab)
/**/
#endif

/* ----------------------------------------------------------- */
/* TYPES */
/* ----------------------------------------------------------- */
typedef EE_UINT8 u8_t;		/**< Unsigned 8 bit intgerer. */
typedef EE_UINT16 u16_t;	/**< Unsigned 16 bit intgerer. */
typedef EE_UINT32 u32_t;	/**< Unsigned 32 bit intgerer. */
typedef EE_INT8 s8_t;		/**< Unsigned 8 bit intgerer. */
typedef EE_INT16 s16_t;		/**< Unsigned 16 bit intgerer. */
typedef EE_INT32 s32_t;		/**< Unsigned 32 bit intgerer. */

typedef struct ip_addr_t {
  u32_t addr;
} ip_addr;

typedef struct udp_hdr_t {
  u16_t src;
  u16_t dest;  /* src/dest UDP ports */
  u16_t len;
  u16_t chksum;
} udp_hdr;

typedef struct ip_hdr_t {
  /* version / header length / type of service */
  u16_t _v_hl_tos;
  /* total length */
  u16_t _len;
  /* identification */
  u16_t _id;
  /* fragment offset field */
  u16_t _offset;
  /* time to live / protocol*/
  u16_t _ttl_proto;
  /* checksum */
  u16_t _chksum;
  /* source and destination IP addresses */
  ip_addr src;
  ip_addr dest; 
} ip_hdr;

typedef struct eth_addr_t {
  u8_t addr[6];
} eth_addr;

typedef struct eth_hdr_t {
  eth_addr dest;
  eth_addr src;
  u16_t type;
} eth_hdr;

typedef struct payload_t {
  u8_t v[SIZE_OF_PAYLOAD];
} payload;

typedef struct packet_t{
	u8_t v[SIZE_OF_ETH_HEADER + SIZE_OF_IP_HEADER + SIZE_OF_UDP_HEADER + SIZE_OF_PAYLOAD];
} packet;


/* ----------------------------------------------------------- */
/* Variables */
/* ----------------------------------------------------------- */

payload msg = {.v[0] = MSG_BYTE1, .v[1] = MSG_BYTE2, .v[2] = MSG_BYTE3, .v[3] = MSG_BYTE4};

eth_hdr ethernet_header = {
					.dest = { 	.addr[0] = DEST_MAC_BYTE1, .addr[1] = DEST_MAC_BYTE2, .addr[2] = DEST_MAC_BYTE3, 
								.addr[3] = DEST_MAC_BYTE4, .addr[4] = DEST_MAC_BYTE5, .addr[5] = DEST_MAC_BYTE6},
  					.src = { 	.addr[0] = MY_DEFAULT_MAC_BYTE1, .addr[1] = MY_DEFAULT_MAC_BYTE2, .addr[2] = MY_DEFAULT_MAC_BYTE3, 
								.addr[3] = MY_DEFAULT_MAC_BYTE4, .addr[4] = MY_DEFAULT_MAC_BYTE5, .addr[5] = MY_DEFAULT_MAC_BYTE6},
  					.type = ETHTYPE_IP };

udp_hdr udp_header = {
					.src = myPort,
					.dest = remotePort,
					.len = UDP_LEN,
					.chksum = UDP_CHKSUM };
					
ip_hdr ip_header = {
  					._v_hl_tos = 0x4500,
  					._len = 0x0020,
  					._id = IP_ID,
  					._offset = 0x0000,
  					._ttl_proto = TTL_PROTO,
  					._chksum = IP_CHKSUM,
  					.src = {.addr = myIPaddress},
  					.dest = {.addr = remoteIPaddress} };
  					
u16_t header_plus_len = sizeof(ip_hdr) + sizeof(udp_hdr) + sizeof(payload) + sizeof(eth_hdr); 

packet test_pkt; 
char str[64];
	
/* ----------------------------------------------------------- */
/* Functions */
/* ----------------------------------------------------------- */
void system_timer_callback(void)
{
	/* count the interrupts, waking up expired alarms */
	CounterTick(myCounter);
}

int print_string(const char *s)
{
	return EE_uart_send_buffer((EE_UINT8*)s,strlen(s));
}

TASK(myTask)
{
	/**/
//	BankSel(MAADR1);
//    sprintf(str, "maadr1: %x\n", ReadMACReg((BYTE)MAADR1).Val); //WriteReg((BYTE)MAADR1, ee_myMACaddress.v[0]);
//    print_string(str);
//    sprintf(str, "maadr2: %x\n", ReadMACReg((BYTE)MAADR2).Val); //WriteReg((BYTE)MAADR2, ee_myMACaddress.v[1]);
//    print_string(str);
//    sprintf(str, "maadr3: %x\n", ReadMACReg((BYTE)MAADR3).Val); //WriteReg((BYTE)MAADR3, ee_myMACaddress.v[2]);
//    print_string(str);
//    sprintf(str, "maadr4: %x\n", ReadMACReg((BYTE)MAADR4).Val); //WriteReg((BYTE)MAADR4, ee_myMACaddress.v[3]);
//    print_string(str);
//    sprintf(str, "maadr5: %x\n", ReadMACReg((BYTE)MAADR5).Val); //WriteReg((BYTE)MAADR5, ee_myMACaddress.v[4]);
//    print_string(str);
//    sprintf(str, "maadr6: %x\n", ReadMACReg((BYTE)MAADR6).Val); //WriteReg((BYTE)MAADR6, ee_myMACaddress.v[5]);
//    print_string(str);
//    BankSel(ERDPTL);          // Return to default Bank 0 
	/**/
	print_string("start\n");
	EE_enc28j60_transfer_init();//EE_enc28j60_transfer_init(sizeof(test_pkt));
	EE_enc28j60_write((BYTE*)&test_pkt, sizeof(test_pkt));
	EE_enc28j60_signal(sizeof(test_pkt));
	print_string("flush\n");
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
	/* Packet initialization */
	int i,j=0;
	for(i = j; i<(SIZE_OF_ETH_HEADER + j); i++)
		test_pkt.v[i] = ((u8_t*)&ethernet_header)[i-j];
	j = i; // offset
	for(i = j; i<(SIZE_OF_IP_HEADER + j); i++)
		test_pkt.v[i] = ((u8_t*)&ip_header)[i-j];
	j = i; // offset
	for(i = j; i<(SIZE_OF_UDP_HEADER + j); i++)
		test_pkt.v[i] = ((u8_t*)&udp_header)[i-j];
	j = i; // offset
	for(i = j; i<(SIZE_OF_PAYLOAD + j); i++)
		test_pkt.v[i] = ((u8_t*)&msg)[i-j];
	/* Packet print */
	sprintf(str, "sizeof(test_pkt) = %d\n", sizeof(packet));
	print_string(str);
	sprintf(str, "header_plus_len = %d\n", header_plus_len);
	print_string(str);
	for(i=0; i<sizeof(test_pkt); i++)
	{
		sprintf(str, "pkt[%d] = 0x%x", i, ((BYTE *)&test_pkt)[i]);
		print_string(str);
	}
	/* Device initialization */
	print_string("\ndevice configuration in progress...");
	device_config();
	print_string("Done!\n");
	turn_on_led();
	SetRelAlarm(myAlarm, 500, 1000);
	EE_timer_on();
		
	while(1)
		;
		
    return 0;
}

/* ------------------------------------------------------- */
/* Device driver functions                                 */
/* ------------------------------------------------------- */

void device_config(void)
{ 	
	EE_enc28j60_init();
}

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


