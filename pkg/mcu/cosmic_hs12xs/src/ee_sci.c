#ifdef __USE_SCI__

#include "mcu/cosmic_hs12xs/inc/ee_sci.h"
#include "ee_internal.h"
#include "cpu\cosmic_hs12xs\inc\ee_irqstub.h"

#ifdef EE_SCI_PORT_0_ISR_ENABLE
static void (*Rx0IsrFunction)(EE_UINT8 data) = NULL;
#endif

#ifdef EE_SCI_PORT_1_ISR_ENABLE
static void (*Rx1IsrFunction)(EE_UINT8 data) = NULL;
#endif

/////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////
struct sci_peripheral
{
  Bool ena;
  unsigned char *init_reg;
} sci[2] = {
    FALSE, &SCI0BDH,
    FALSE, &SCI1BDH    
  };

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
void EE_SCIOpenCommunication(unsigned char sci_num)
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
void EE_SCICloseCommunication(unsigned char sci_num)
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
Bool EE_SCISendBuffer(unsigned char sci_num, unsigned char buffer)
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
// SCIGetBuffer
// --------------------------------------------------------------------------------------
// SCI Receive Data, True if the buffer has been received
/////////////////////////////////////////////////////////////////////////////////////////
Bool EE_SCIGetBuffer(unsigned char sci_num, unsigned char *buffer)
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
Bool EE_SCICheckGetBuffer(unsigned char sci_num)
{

  unsigned char *sci_pt;

  if(!sci[sci_num].ena)
    return(FALSE);
  sci_pt = sci[sci_num].init_reg;
  if(sci_pt[SCISR1]&0x20)
    return(TRUE);
  return(FALSE);

}


#ifdef EE_SCI_PORT_0_ISR_ENABLE
ISR2(_SCI0RXInterrupt)
{
	//if (Rx0IsrFunction != NULL) {
//		/* Execute callback function */
//		Rx0IsrFunction(U1RXREG & 0x00FF);
//	}
//	IFS0bits.U1RXIF = 0;           
}
#endif

#ifdef EE_SCI_PORT_1_ISR_ENABLE
ISR2(_SCI1RXInterrupt)
{
//	if (Rx1IsrFunction != NULL) {
//		/* Execute callback function */
//		Rx1IsrFunction(U2RXREG & 0x00FF);
//	}
//	IFS1bits.U2RXIF = 0;           
}
#endif

#endif
