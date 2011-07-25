#ifdef __USE_SCI__

//#include "cpu/cosmic_hs12xs/inc/ee_cpu.h"
#include "ee_internal.h"
#include "cpu/cosmic_hs12xs/inc/ee_irqstub.h"

#ifdef EE_SCI_PORT_0_ISR_ENABLE
static void (*Rx0IsrFunction)(EE_UINT8 data) = NULL;
#endif

#ifdef EE_SCI_PORT_1_ISR_ENABLE
static void (*Rx1IsrFunction)(EE_UINT8 data) = NULL;
#endif

/////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////
struct EE_sci_peripheral EE_sci[2] = {
    -1, &SCI0BDH,
    -1, &SCI1BDH    
  };

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
