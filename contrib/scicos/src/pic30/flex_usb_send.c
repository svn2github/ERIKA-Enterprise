/* ###*B*###
 * Copyright (C) Roberto Bucher (SUPSI- Lugano)
 *               Simone Mannori (Scilab / INRIA / DIGITEO)
 *
 * Copyright (C) METALAU Project (INRIA)
 * ###*E*### */
 
 
//** 9 Feb 2008 : Revision notes by Simone Mannori 
//**

#include <machine.h>
#include <scicos_block4.h>

#include <ee.h>

/*
*/

static void init(scicos_block *block)
{
  TRISAbits.TRISA14=0;
  EE_usb_init();
}

static unsigned char checksum(unsigned char *buf)
{
   unsigned char len=buf[1]+2, sum=0, *pt=buf+1;
   while(len--){
      sum+=*pt++;
   }
   return sum;
}

static void inout(scicos_block *block)
{
	float inputdata;
	float * y = block->inptr[0];
	unsigned char datasize;
  unsigned char buf[32];
	int logical_channel = block->ipar[0];
	buf[0] = 0xAA; // sync char
	datasize=sizeof(float) + 1; //TODO: mettere la size del dato letto in input	
	buf[1] = datasize; // len	
	buf[2] = 21;       // id
	buf[3] = *(unsigned char *)y;
	buf[4] = *((unsigned char *)y+1);
	buf[5] = *((unsigned char *)y+2);
	buf[6] = *((unsigned char *)y+3);
	buf[7] = (unsigned char)logical_channel; 	
	buf[8] = checksum(buf);
	buf[9] = 0;        // padding
	
	EE_usb_send( (unsigned int *)buf, (datasize + 5)>>1 );
}

static void end(scicos_block *block)
{
}

void flex_usb_out(scicos_block *block,int flag)
{
	switch (flag) {
		case 1:	/* set output */
			inout(block);
			break;

		case 2:	/* get input */
			inout(block);
			break;
		
		case 4:	/* initialisation */
			init(block);
			break;
		
		case 5:	/* ending */
			end(block);
			break;
	}
}
