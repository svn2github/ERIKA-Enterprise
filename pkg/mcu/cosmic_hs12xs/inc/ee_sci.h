#ifdef __USE_SCI__

#ifndef __INCLUDE_FREESCALE_S12XS_SCI_H__
#define __INCLUDE_FREESCALE_S12XS_SCI_H__

/* Include a file with the registers of the s12 micro-controller */ 
#ifdef __S12XS_INCLUDE_REGS__
#include "ee_hs12xsregs.h"
#endif

//#include "ee.h"

/////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////
#define SCI_0             0
#define SCI_1             1
#define ALL				  65000

#define SCIBDH            0x00
#define SCIBDL            0x01
#define SCICR1            0x02
#define SCIASR1           0x00
#define SCIACR1           0x01
#define SCIACR2           0x02
#define SCICR2            0x03
#define SCISR1            0x04
#define SCISR2            0x05
#define SCIDRH            0x06
#define SCIDRL            0x07

/////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////
//void EE_SCIOpenCommunication(unsigned char sci_num);
//void EE_SCICloseCommunication(unsigned char sci_num);
//Bool EE_SCISendBuffer(unsigned char sci_num, unsigned char buffer);
//Bool EE_SCIGetBuffer(unsigned char sci_num, unsigned char *buffer);
//Bool EE_SCICheckGetBuffer(unsigned char sci_num);

struct EE_sci_peripheral
{
  Bool ena;
  unsigned char *init_reg;
};

extern struct EE_sci_peripheral EE_sci[2];

/////////////////////////////////////////////////////////////////////////////////////////
// SCIOpenCommunication
// --------------------------------------------------------------------------------------
// Configures SCI registers for Enable Transmit and Receive data
// SCI BAUD RATE = BUSCLK/(16*BR)
// BUSCLK = 2 MHz
// BAUD RATE = 9600
// BR = 13 
// Baud rate mismatch = 0.160 %
/////////////////////////////////////////////////////////////////////////////////////////
__INLINE__ void __ALWAYS_INLINE__ EE_sci_open(unsigned char sci_num, unsigned long int busclock, unsigned long int baudrate)
{
	unsigned int br = 0;
  unsigned char *sci_pt;

  EE_sci[sci_num].ena = TRUE;
  sci_pt = EE_sci[sci_num].init_reg;
  // Set Baud Rate Modulo Divisor
  br = (unsigned int)(busclock/(baudrate*((unsigned long int)16)));
  
  sci_pt[SCIBDH] = (unsigned char)(br >> 8);
  sci_pt[SCIBDL] = (unsigned char)(br&0x00FF);
  
  // Trasmitter and Receiver Enable
  sci_pt[SCICR2] = 0x0C;
  
}

/////////////////////////////////////////////////////////////////////////////////////////
// SCICloseCommunication
// --------------------------------------------------------------------------------------
// Configures SCI (x) registers for disable Transmit and Receive data 
/////////////////////////////////////////////////////////////////////////////////////////
__INLINE__ void __ALWAYS_INLINE__ EE_sci_close(unsigned char sci_num)
{

  unsigned char *sci_pt;
  unsigned char data;
  unsigned int i;

  EE_sci[sci_num].ena = FALSE;
  sci_pt = EE_sci[sci_num].init_reg;
  i = 0;
  // Verify that Receive Data Register is FULL
  while(i < 1000 && !(sci_pt[SCISR1]&0x20))
    i++;
  if (sci_pt[SCISR1]&0x20)
    // Clear RDRF Flag
    data = sci_pt[SCIDRL];

  sci_pt[SCIBDH] = 0;
  sci_pt[SCIBDL] = 0;
  // Trasmitter and Receiver Disable
  sci_pt[SCICR2] = 0;
  
}

/////////////////////////////////////////////////////////////////////////////////////////
// SCISendBuffer
// --------------------------------------------------------------------------------------
// SCI Transmit Data. True if the buffer has been transmitted.
/////////////////////////////////////////////////////////////////////////////////////////
__INLINE__ Bool __ALWAYS_INLINE__ EE_sci_send_byte(unsigned char sci_num, unsigned char buffer)
{

  unsigned char *sci_pt;

  if(!EE_sci[sci_num].ena)
    return(FALSE);
  sci_pt = EE_sci[sci_num].init_reg;
  // Wait until Transmit Data Register is empty.
  while(!(sci_pt[SCISR1]&0x80))
    ;
  // Send Buffer and clear TDRE flag  
  sci_pt[SCIDRL] = buffer;
  return(TRUE);

}

/////////////////////////////////////////////////////////////////////////////////////////
// SCISendString
// --------------------------------------------------------------------------------------
// SCI Transmit Data. True if the buffer has been transmitted.
/////////////////////////////////////////////////////////////////////////////////////////
__INLINE__ Bool __ALWAYS_INLINE__ EE_sci_send_string(unsigned char sci_num, const char* s, unsigned int num)
{
	unsigned int i = 0;
	Bool res = TRUE; 	
	while( (s[i]!='\0') && (i<num) )
	{
  		res = EE_sci_send_byte(sci_num,s[i]);
  		i++;
  		if(res==FALSE)
  			break;
	}
  	return res;
}

/////////////////////////////////////////////////////////////////////////////////////////
// SCISendChars
// --------------------------------------------------------------------------------------
// SCI Transmit Data. True if the buffer has been transmitted.
/////////////////////////////////////////////////////////////////////////////////////////
__INLINE__ Bool __ALWAYS_INLINE__ EE_sci_send_bytes(unsigned char sci_num, char* v, unsigned int num)
{
	unsigned int i = 0;
	Bool res = TRUE; 	
	while( (v[i]!='\0') && (i<num) )
	{
  		res = EE_sci_send_byte(sci_num,v[i]);
  		i++;
  		if(res==FALSE)
  			break;
	}
  	return res;
}

/////////////////////////////////////////////////////////////////////////////////////////
// SCIGetBuffer
// --------------------------------------------------------------------------------------
// SCI Receive Data, True if the buffer has been received
/////////////////////////////////////////////////////////////////////////////////////////
__INLINE__ Bool __ALWAYS_INLINE__ EE_sci_get_byte(unsigned char sci_num, unsigned char *buffer)
{

  unsigned char *sci_pt;

  if(!EE_sci[sci_num].ena)
    return(FALSE);
  sci_pt = EE_sci[sci_num].init_reg;
  while(!(sci_pt[SCISR1]&0x20))
    ;
  // Get Buffer and clear RDRF flag
  *buffer = sci_pt[SCISR1];
  *buffer = sci_pt[SCIDRL];
  return(TRUE);

}

/////////////////////////////////////////////////////////////////////////////////////////
// SCICheckGetBuffer
// --------------------------------------------------------------------------------------
// SCI Check Receive Data, True if receiver data register (SCIDR) is full
/////////////////////////////////////////////////////////////////////////////////////////
__INLINE__ Bool __ALWAYS_INLINE__ EE_sci_getcheck(unsigned char sci_num)
{

  unsigned char *sci_pt;

  if(!EE_sci[sci_num].ena)
    return(FALSE);
  sci_pt = EE_sci[sci_num].init_reg;
  if(sci_pt[SCISR1]&0x20)
    return(TRUE);
  return(FALSE);

}

#endif

#endif
