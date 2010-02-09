 
//** 29 Jan 2010 : Written by Dario Di Stefano 
//**

#include <machine.h>
#include <scicos_block4.h>
#include <ee.h>
#include "string.h"
#include "flex_udp.h"

#define SIZE_OF_ELEMENT 4
#define u(i,j) ((double *)block->inptr[i])[j]

BYTE scicosUDP_tx_buffer[UDP_PKG_LEN];	// buffer for UDP transmission

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
    //UDP_remote.MACAddr.v[0] = block->ipar[2];	// 0x00;
    //UDP_remote.MACAddr.v[1] = block->ipar[3];	// 0x1E;
    //UDP_remote.MACAddr.v[2] = block->ipar[4];	// 0x33;
    //UDP_remote.MACAddr.v[3] = block->ipar[5];	// 0xC9;
    //UDP_remote.MACAddr.v[4] = block->ipar[6];	// 0xD6;
    //UDP_remote.MACAddr.v[5] = block->ipar[7];	// 0xAA;
	//	UDP_buf_size 			= block->ipar[6];	// Number of elements in the tx buffer. 
	
	for(i=0;i<UDP_PKG_LEN;i++)
			scicosUDP_tx_buffer[i] = 0;
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
