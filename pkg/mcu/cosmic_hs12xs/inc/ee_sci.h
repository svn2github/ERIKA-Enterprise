#ifdef __USE_SCI__

#ifndef __INCLUDE_FREESCALE_S12XS_SCI_H__
#define __INCLUDE_FREESCALE_S12XS_SCI_H__

#include "ee.h"
/* Include a file with the registers from Microchip C30 distribution */ 
#ifdef __S12XS_INCLUDE_REGS__
#include "ee_hs12xsregs.h"
#endif

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

struct sci_peripheral
{
  Bool ena;
  unsigned char *init_reg;
};

extern struct sci_peripheral sci[2];

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
__INLINE__ void __ALWAYS_INLINE__ EE_SCIOpenCommunication(unsigned char sci_num)
{

  unsigned char *sci_pt;

  sci[sci_num].ena = TRUE;
  sci_pt = sci[sci_num].init_reg;
  // Set Baud Rate Modulo Divisor
  sci_pt[SCIBDH] = (unsigned char)(13 >> 8);
  sci_pt[SCIBDL] = (unsigned char)13;
  // Trasmitter and Receiver Enable
  sci_pt[SCICR2] = 0x0C;
  
}

/////////////////////////////////////////////////////////////////////////////////////////
// SCICloseCommunication
// --------------------------------------------------------------------------------------
// Configures SCI (x) registers for disable Transmit and Receive data 
/////////////////////////////////////////////////////////////////////////////////////////
__INLINE__ void __ALWAYS_INLINE__ EE_SCICloseCommunication(unsigned char sci_num)
{

  unsigned char *sci_pt;
  unsigned char data;
  unsigned int i;

  sci[sci_num].ena = FALSE;
  sci_pt = sci[sci_num].init_reg;
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
__INLINE__ Bool __ALWAYS_INLINE__ EE_SCISendBuffer(unsigned char sci_num, unsigned char buffer)
{

  unsigned char *sci_pt;

  if(!sci[sci_num].ena)
    return(FALSE);
  sci_pt = sci[sci_num].init_reg;
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
__INLINE__ Bool __ALWAYS_INLINE__ EE_SCISendString(unsigned char sci_num, const char* s, unsigned int num)
{
	unsigned int i = 0;
	Bool res = TRUE; 	
	while( (s[i]!='\0') && (i<num) )
	{
  		res = EE_SCISendBuffer(sci_num,s[i]);
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
__INLINE__ Bool __ALWAYS_INLINE__ EE_SCISendChars(unsigned char sci_num, char* v, unsigned int num)
{
	unsigned int i = 0;
	Bool res = TRUE; 	
	while( (v[i]!='\0') && (i<num) )
	{
  		res = EE_SCISendBuffer(sci_num,v[i]);
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
__INLINE__ Bool __ALWAYS_INLINE__ EE_SCIGetBuffer(unsigned char sci_num, unsigned char *buffer)
{

  unsigned char *sci_pt;

  if(!sci[sci_num].ena)
    return(FALSE);
  sci_pt = sci[sci_num].init_reg;
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
__INLINE__ Bool __ALWAYS_INLINE__ EE_SCICheckGetBuffer(unsigned char sci_num)
{

  unsigned char *sci_pt;

  if(!sci[sci_num].ena)
    return(FALSE);
  sci_pt = sci[sci_num].init_reg;
  if(sci_pt[SCISR1]&0x20)
    return(TRUE);
  return(FALSE);

}

#endif

#endif
