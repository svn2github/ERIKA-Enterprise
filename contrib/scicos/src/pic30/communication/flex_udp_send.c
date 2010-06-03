 
//** 29 Jan 2010 : Written by Dario Di Stefano 
//**

#include <machine.h>
#include <scicos_block4.h>
#include <ee.h>
#include "string.h"
#include "flex_udp.h"

#define SIZE_OF_ELEMENT 4
#define u(i,j) ((double *)block->inptr[i])[j]

static void init(scicos_block *block)
{
    int i = 0;

	if(!UDP_is_initialized)
	{
		UDP_flex_port 				= block->ipar[0];	//9760;				// block->ipar[0];	// FLEX SERVER PORT NUMBER
		UDP_pc_port 				= block->ipar[1];	//9761;				// block->ipar[0];	// PC SERVER PORT NUMBER
		
		MY_DEFAULT_IP_ADDR_BYTE1 	= block->ipar[2];
		MY_DEFAULT_IP_ADDR_BYTE2 	= block->ipar[3];
		MY_DEFAULT_IP_ADDR_BYTE3 	= block->ipar[4];
		MY_DEFAULT_IP_ADDR_BYTE4 	= block->ipar[5];

		MY_DEFAULT_MASK_BYTE1		= block->ipar[6];
		MY_DEFAULT_MASK_BYTE2		= block->ipar[7];
		MY_DEFAULT_MASK_BYTE3		= block->ipar[8];
		MY_DEFAULT_MASK_BYTE4		= block->ipar[9];

		MY_DEFAULT_GATE_BYTE1		= block->ipar[10];	
		MY_DEFAULT_GATE_BYTE2		= block->ipar[11];
		MY_DEFAULT_GATE_BYTE3		= block->ipar[12];	
		MY_DEFAULT_GATE_BYTE4		= block->ipar[13];

		MY_DEFAULT_PRIMARY_DNS_BYTE1	= block->ipar[14];	
		MY_DEFAULT_PRIMARY_DNS_BYTE2	= block->ipar[15];
		MY_DEFAULT_PRIMARY_DNS_BYTE3	= block->ipar[16];
		MY_DEFAULT_PRIMARY_DNS_BYTE4	= block->ipar[17];

		MY_DEFAULT_SECONDARY_DNS_BYTE1	= block->ipar[18];
		MY_DEFAULT_SECONDARY_DNS_BYTE2	= block->ipar[19];
		MY_DEFAULT_SECONDARY_DNS_BYTE3	= block->ipar[20];
		MY_DEFAULT_SECONDARY_DNS_BYTE4	= block->ipar[21];

		UDP_remote.IPAddr.v[0]			= block->ipar[22];	//192;				// dest_address byte 1
		UDP_remote.IPAddr.v[1]			= block->ipar[23];	//168;				// dest_address byte 2
		UDP_remote.IPAddr.v[2]			= block->ipar[24];	//0;				// dest_address byte 3
		UDP_remote.IPAddr.v[3]			= block->ipar[25];	//1;				// dest_address byte 4
		
		UDP_remote.MACAddr.v[0] = 0;				// 0x00;
		UDP_remote.MACAddr.v[1] = 0;				// 0x1E;
		UDP_remote.MACAddr.v[2] = 0;				// 0x33;
		UDP_remote.MACAddr.v[3] = 0;				// 0xC9;
		UDP_remote.MACAddr.v[4] = 0;				// 0xD6;
		UDP_remote.MACAddr.v[5] = 0;				// 0xAA;
		
		for(i=0;i<UDP_PKG_LEN;i++)
			scicosUDP_tx_buffer[i] = 0;
		for(i=0;i<UDP_PKG_LEN;i++)
			scicosUDP_rx_buffer[i] = 0;
			
		UDP_is_initialized = 1;
	}
	
    // UDP_flex_port 			= block->ipar[0];//9760;				// block->ipar[0];	// FLEX SERVER PORT NUMBER
    // UDP_pc_port 			= block->ipar[1];//9761;				// block->ipar[0];	// PC SERVER PORT NUMBER
    // UDP_remote.IPAddr.v[0]	= 192;	// dest_address byte 1
    // UDP_remote.IPAddr.v[1]	= 168;	// dest_address byte 2
    // UDP_remote.IPAddr.v[2]	= 0;	// dest_address byte 3
    // UDP_remote.IPAddr.v[3]	= 1;	// dest_address byte 4
    // UDP_remote.MACAddr.v[0] = 0;	// 0x00;
    // UDP_remote.MACAddr.v[1] = 0;	// 0x1E;
    // UDP_remote.MACAddr.v[2] = 0;	// 0x33;
    // UDP_remote.MACAddr.v[3] = 0;	// 0xC9;
    // UDP_remote.MACAddr.v[4] = 0;	// 0xD6;
    // UDP_remote.MACAddr.v[5] = 0;	// 0xAA;
	
	
}

static void inout(scicos_block *block)
{	
	int i=0;
	for(i=0;i<SCICOS_UDP_CHANNELS;i++)
	{
		memcpy(scicosUDP_tx_buffer+i*SIZE_OF_ELEMENT,&u(i,0),SIZE_OF_ELEMENT);
	}
	//memcpy(scicosUDP_tx_buffer,&u(0,0),UDP_PKG_LEN);
	UDP_Buffer_Putmsg(&UDP_tx_buffer,scicosUDP_tx_buffer,UDP_BUF_SIZE);
	return;
}

static void end(scicos_block *block)
{
}

void flex_udp_send(scicos_block *block,int flag)
{
 switch (flag) {
    case OutputUpdate:  /* set output */
      inout(block);
      break;

    case StateUpdate: /* get input */
      break;

    case Initialization:  /* initialisation */
      init(block);
      break;

    case Ending:  /* ending */
      end(block);
      break;
  }
}
