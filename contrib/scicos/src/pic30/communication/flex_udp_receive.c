 
//** 29 Jan 2010 : Written by Dario Di Stefano 
//**

#include <machine.h>
#include <scicos_block4.h>
#include <ee.h>
#include "string.h"
#include "flex_udp.h"

#define SIZE_OF_ELEMENT 4
#define y(i,j) ((double *)block->outptr[i])[j]

BYTE scicosUDP_rx_buffer[UDP_PKG_LEN];	// buffer for UDP reception

static void init(scicos_block *block)
{
    int i = 0;
    //TRISAbits.TRISA14=0;
   	UDP_flex_port 			= block->ipar[0];//9760;				// block->ipar[0];	// FLEX SERVER PORT NUMBER
    UDP_pc_port 			= block->ipar[1];//9761;				// block->ipar[0];	// PC SERVER PORT NUMBER
    UDP_remote.IPAddr.v[0]	= 192;				// dest_address byte 1
    UDP_remote.IPAddr.v[1]	= 168;				// dest_address byte 2
    UDP_remote.IPAddr.v[2]	= 0;				// dest_address byte 3
    UDP_remote.IPAddr.v[3]	= 1;				// dest_address byte 4
    UDP_remote.MACAddr.v[0] = 0;	// 0x00;
    UDP_remote.MACAddr.v[1] = 0;	// 0x1E;
    UDP_remote.MACAddr.v[2] = 0;	// 0x33;
    UDP_remote.MACAddr.v[3] = 0;	// 0xC9;
    UDP_remote.MACAddr.v[4] = 0;	// 0xD6;
    UDP_remote.MACAddr.v[5] = 0;	// 0xAA;
    //UDP_buf_size 			= block->ipar[0];	// Number of elements in the rx buffer. 
    for(i=0;i<UDP_PKG_LEN;i++)
			scicosUDP_rx_buffer[i] = 0;
}

static void inout(scicos_block *block)
{
	int i=0;
	if(UDP_Buffer_Getmsg(&UDP_rx_buffer, scicosUDP_rx_buffer, UDP_BUF_SIZE))
		for(i=0;i<SCICOS_UDP_CHANNELS;i++)
		{
			memcpy(&y(i,0),scicosUDP_rx_buffer+i*SIZE_OF_ELEMENT,SIZE_OF_ELEMENT);
		}
	//if(UDP_Buffer_Getmsg(&UDP_rx_buffer, scicosUDP_rx_buffer, UDP_BUF_SIZE))
	//	memcpy(&y(0,0),scicosUDP_rx_buffer,UDP_PKG_LEN);				// to be removed...
	return;
}

static void end(scicos_block *block)
{
}

void flex_udp_receive(scicos_block *block,int flag)
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
