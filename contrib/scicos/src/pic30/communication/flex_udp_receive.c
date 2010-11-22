/* ###*B*###
 * ERIKA Enterprise - a tiny RTOS for small microcontrollers
 *
 * Copyright (C) 2006-2010  Evidence Srl
 *
 * This file is part of ERIKA Enterprise.
 *
 * ERIKA Enterprise is free software; you can redistribute it
 * and/or modify it under the terms of the GNU General Public License
 * version 2 as published by the Free Software Foundation, 
 * (with a special exception described below).
 *
 * Linking this code statically or dynamically with other modules is
 * making a combined work based on this code.  Thus, the terms and
 * conditions of the GNU General Public License cover the whole
 * combination.
 *
 * As a special exception, the copyright holders of this library give you
 * permission to link this code with independent modules to produce an
 * executable, regardless of the license terms of these independent
 * modules, and to copy and distribute the resulting executable under
 * terms of your choice, provided that you also meet, for each linked
 * independent module, the terms and conditions of the license of that
 * module.  An independent module is a module which is not derived from
 * or based on this library.  If you modify this code, you may extend
 * this exception to your version of the code, but you are not
 * obligated to do so.  If you do not wish to do so, delete this
 * exception statement from your version.
 *
 * ERIKA Enterprise is distributed in the hope that it will be
 * useful, but WITHOUT ANY WARRANTY; without even the implied warranty
 * of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License version 2 for more details.
 *
 * You should have received a copy of the GNU General Public License
 * version 2 along with ERIKA Enterprise; if not, write to the
 * Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
 * Boston, MA 02110-1301 USA.
 * ###*E*### */

/** 
	@file flex_udp_receive.c
	@brief www.scicos.org, www.scicoslab.org
	@author Dario Di Stefano, Evidence Srl
	@date 2006-2010
*/

#include <machine.h>
#include <scicos_block4.h>
#include <ee.h>
#include "string.h"
#include "flex_udp.h"

#define SIZE_OF_ELEMENT 4
#define y(i,j) ((double *)block->outptr[i])[j]

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
