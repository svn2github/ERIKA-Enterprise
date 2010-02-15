#include "mcu/mico32/inc/ee_spi.h"
//#include "ee_internal.h"

/******************************************************************************/
/*                             Utility Macros                                 */
/******************************************************************************/
#define MCHP_SPICON_MASKS (EE_SPI_MASTER | EE_SPI_SDO_ON_CLOCK_TO_IDLE | \
			   EE_SPI_CLOCK_IDLE_HIGH | EE_SPI_SDI_ON_CLOCK_END)

#define IS_MASTER(flags)	((flags) & EE_SPI_MASTER)
#define IS_DMA_TX(flags) 	((flags) & EE_SPI_DMA_TX)
#define IS_DMA_RX(flags) 	((flags) & EE_SPI_DMA_RX)

#define ADDR_VIRTUAL_TO_PHYSICAL(a) (((EE_UREG)(a)) & 0x1FFFFFFF)

/******************************************************************************/
/*                    DMA Channel Abstraction Layer                           */
/******************************************************************************/
/* Check SPI PORT 1 settings (with defaults) */
#ifndef EE_SPI_PORT1_DCHCON
#define EE_SPI_PORT1_DCHCON(m)	DCH0CON		##m	
#endif
#define SPI1_DCHCON	EE_SPI_PORT1_DCHCON()
#define SPI1_DCHCONSET	EE_SPI_PORT1_DCHCON(SET)
#define SPI1_DCHCONCLR	EE_SPI_PORT1_DCHCON(CLR)
#define SPI1_DCHCONINV	EE_SPI_PORT1_DCHCON(INV)

#ifndef EE_SPI_PORT1_DCHECON
#define EE_SPI_PORT1_DCHECON(m)	DCH0ECON	##m	
#endif
#define SPI1_DCHECON	EE_SPI_PORT1_DCHECON()
#define SPI1_DCHECONSET	EE_SPI_PORT1_DCHECON(SET)
#define SPI1_DCHECONCLR	EE_SPI_PORT1_DCHECON(CLR)
#define SPI1_DCHECONINV	EE_SPI_PORT1_DCHECON(INV)

#ifndef EE_SPI_PORT1_DCHINT
#define EE_SPI_PORT1_DCHINT(m)	DCH0INT		##m	
#endif
#define SPI1_DCHINT	EE_SPI_PORT1_DCHINT()
#define SPI1_DCHINTSET	EE_SPI_PORT1_DCHINT(SET)
#define SPI1_DCHINTCLR	EE_SPI_PORT1_DCHINT(CLR)
#define SPI1_DCHINTINV	EE_SPI_PORT1_DCHINT(INV)

#ifndef EE_SPI_PORT1_DCHSSA
#define EE_SPI_PORT1_DCHSSA(m)	DCH0SSA		##m	
#endif
#define SPI1_DCHSSA	EE_SPI_PORT1_DCHSSA()

#ifndef EE_SPI_PORT1_DCHDSA
#define EE_SPI_PORT1_DCHDSA(m)	DCH0DSA		##m	
#endif
#define SPI1_DCHDSA	EE_SPI_PORT1_DCHDSA()

#ifndef EE_SPI_PORT1_DCHSSIZ
#define EE_SPI_PORT1_DCHSSIZ(m)	DCH0SSIZ	##m	
#endif
#define SPI1_DCHSSIZ	EE_SPI_PORT1_DCHSSIZ()

#ifndef EE_SPI_PORT1_DCHDSIZ
#define EE_SPI_PORT1_DCHDSIZ(m)	DCH0DSIZ	##m	
#endif
#define SPI1_DCHDSIZ	EE_SPI_PORT1_DCHDSIZ()

#ifndef EE_SPI_PORT1_DCHCSIZ
#define EE_SPI_PORT1_DCHCSIZ(m)	DCH0CSIZ	##m	
#endif
#define SPI1_DCHCSIZ	EE_SPI_PORT1_DCHCSIZ()

#ifndef EE_SPI_PORT1_DMA_IE_MASK
#define SPI1_DMAIE_MASK		_IEC1_DMA0IE_MASK
#else 	
#define SPI1_DMAIE_MASK 	EE_SPI_PORT1_DMA_IE_MASK
#endif

#ifndef EE_SPI_PORT1_DMA_IF_MASK
#define SPI1_DMAIF_MASK		_IFS1_DMA0IF_MASK
#else 	
#define SPI1_DMAIF_MASK		EE_SPI_PORT1_DMA_IF_MASK
#endif

#ifndef EE_SPI_PORT1_DMA_IP_MASK
#define SPI1_DMAIP_MASK		_IPC9_DMA0IP_MASK
#else 	
#define SPI1_DMAIP_MASK		EE_SPI_PORT1_DMA_IP_MASK
#endif

#ifndef EE_SPI_PORT1_DMA_IS_MASK
#define SPI1_DMAIS_MASK		_IPC9_DMA0IS_MASK
#else 	
#define SPI1_DMAIS_MASK		EE_SPI_PORT1_DMA_IS_MASK
#endif

#ifndef EE_SPI_PORT1_DMA_IP_POS
#define SPI1_DMAIP_POS		_IPC9_DMA0IP_POSITION
#else 	
#define SPI1_DMAIP_POS		EE_SPI_PORT1_DMA_IP_POS
#endif

#ifndef EE_SPI_PORT1_DMA_IS_POS
#define SPI1_DMAIS_POS		_IPC9_DMA0IS_POSITION
#else 	
#define SPI1_DMAIS_POS		EE_SPI_PORT1_DMA_IS_POS
#endif

#ifndef EE_SPI_PORT1_DMA_IRQ
#define SPI1_DMA_IRQ		_DMA0_VECTOR
#else 	
#define SPI1_DMA_IRQ		EE_SPI_PORT1_DMA_IRQ
#endif

/* Check SPI PORT 2 settings (with defaults) */
#ifndef EE_SPI_PORT2_DCHCON
#define EE_SPI_PORT2_DCHCON(m)	DCH1CON		##m	
#endif
#define SPI2_DCHCON	EE_SPI_PORT2_DCHCON()
#define SPI2_DCHCONSET	EE_SPI_PORT2_DCHCON(SET)
#define SPI2_DCHCONCLR	EE_SPI_PORT2_DCHCON(CLR)
#define SPI2_DCHCONINV	EE_SPI_PORT2_DCHCON(INV)

#ifndef EE_SPI_PORT2_DCHECON
#define EE_SPI_PORT2_DCHECON(m)	DCH1ECON	##m	
#endif
#define SPI2_DCHECON	EE_SPI_PORT2_DCHECON()
#define SPI2_DCHECONSET	EE_SPI_PORT2_DCHECON(SET)
#define SPI2_DCHECONCLR	EE_SPI_PORT2_DCHECON(CLR)
#define SPI2_DCHECONINV	EE_SPI_PORT2_DCHECON(INV)

#ifndef EE_SPI_PORT2_DCHINT
#define EE_SPI_PORT2_DCHINT(m)	DCH1INT		##m	
#endif
#define SPI2_DCHINT	EE_SPI_PORT2_DCHINT()
#define SPI2_DCHINTSET	EE_SPI_PORT2_DCHINT(SET)
#define SPI2_DCHINTCLR	EE_SPI_PORT2_DCHINT(CLR)
#define SPI2_DCHINTINV	EE_SPI_PORT2_DCHINT(INV)

#ifndef EE_SPI_PORT2_DCHSSA
#define EE_SPI_PORT2_DCHSSA(m)	DCH1SSA		##m	
#endif
#define SPI2_DCHSSA	EE_SPI_PORT2_DCHSSA()

#ifndef EE_SPI_PORT2_DCHDSA
#define EE_SPI_PORT2_DCHDSA(m)	DCH1DSA		##m	
#endif
#define SPI2_DCHDSA	EE_SPI_PORT2_DCHDSA()

#ifndef EE_SPI_PORT2_DCHSSIZ
#define EE_SPI_PORT2_DCHSSIZ(m)	DCH1SSIZ	##m	
#endif
#define SPI2_DCHSSIZ	EE_SPI_PORT2_DCHSSIZ()

#ifndef EE_SPI_PORT2_DCHDSIZ
#define EE_SPI_PORT2_DCHDSIZ(m)	DCH1DSIZ	##m	
#endif
#define SPI2_DCHDSIZ	EE_SPI_PORT2_DCHDSIZ()

#ifndef EE_SPI_PORT2_DCHCSIZ
#define EE_SPI_PORT2_DCHCSIZ(m)	DCH1CSIZ	##m	
#endif
#define SPI2_DCHCSIZ	EE_SPI_PORT2_DCHCSIZ()

#ifndef EE_SPI_PORT2_DMA_IE_MASK
#define SPI2_DMAIE_MASK		_IEC1_DMA1IE_MASK
#else 	
#define SPI2_DMAIE_MASK 	EE_SPI_PORT2_DMA_IE_MASK
#endif

#ifndef EE_SPI_PORT2_DMA_IF_MASK
#define SPI2_DMAIF_MASK		_IFS1_DMA1IF_MASK
#else 	
#define SPI2_DMAIF_MASK		EE_SPI_PORT2_DMA_IF_MASK
#endif

#ifndef EE_SPI_PORT2_DMA_IP_MASK
#define SPI2_DMAIP_MASK		_IPC9_DMA1IP_MASK
#else 	
#define SPI2_DMAIP_MASK		EE_SPI_PORT2_DMA_IP_MASK
#endif

#ifndef EE_SPI_PORT2_DMA_IS_MASK
#define SPI2_DMAIS_MASK		_IPC9_DMA1IS_MASK
#else 	
#define SPI2_DMAIS_MASK		EE_SPI_PORT2_DMA_IS_MASK
#endif

#ifndef EE_SPI_PORT2_DMA_IP_POS
#define SPI2_DMAIP_POS		_IPC9_DMA1IP_POSITION
#else 	
#define SPI2_DMAIP_POS		EE_SPI_PORT2_DMA_IP_POS
#endif

#ifndef EE_SPI_PORT2_DMA_IS_POS
#define SPI2_DMAIS_POS		_IPC9_DMA1IS_POSITION
#else 	
#define SPI2_DMAIS_POS		EE_SPI_PORT2_DMA_IS_POS
#endif

#ifndef EE_SPI_PORT2_DMA_IRQ
#define SPI2_DMA_IRQ		_DMA1_VECTOR
#else 	
#define SPI2_DMA_IRQ		EE_SPI_PORT2_DMA_IRQ
#endif

/* NOTE: this work under the assumption that all the DMA channels have the same 
*  control registers specification. See pic32mx family reference manual.
*/
#define SPI_DCHCON_CHEN_MASK 	_DCH0CON_CHEN_MASK
#define SPI_DCHECON_CFORCE_MASK _DCH0ECON_CFORCE_MASK
#define SPI_DCHECON_SIRQEN_MASK _DCH0ECON_SIRQEN_MASK
#define SPI_DCHECON_CHSIRQ_POS 	_DCH0ECON_CHSIRQ_POSITION
#define SPI_DCHINT_CHBCIE_MASK 	_DCH0INT_CHBCIE_MASK
#define SPI_DCHINT_CHBCIF_MASK 	_DCH0INT_CHBCIF_MASK

/******************************************************************************/
/*                       Private Local Variables                              */
/******************************************************************************/
static EE_UINT16 port1_flags;
static EE_UINT16 port2_flags;
static void (* volatile port1_tx_callback)(void) = NULL;
static void (* volatile port2_tx_callback)(void) = NULL;

/******************************************************************************/
/*                       Private Local Functions                              */
/******************************************************************************/
__INLINE__ EE_UREG get_brg(EE_UINT32 baudrate) 
{
	return 0x04; // chris: TODO: use formula to calculate brg! 
}

__INLINE__ EE_INT8 init_port1(EE_UINT32 baudrate, EE_UINT16 flags)
{
	//EE_UREG v; 
//
//	IEC0CLR = _IEC0_SPI1EIE_MASK | _IEC0_SPI1TXIE_MASK | 
//		  _IEC0_SPI1RXIE_MASK;
//	IFS0CLR = _IFS0_SPI1EIF_MASK | _IFS0_SPI1TXIF_MASK | 
//		  _IFS0_SPI1RXIF_MASK;
//	SPI1CON = 0;
//	SPI1STATCLR = _SPI1STAT_SPIROV_MASK; 
//	SPI1BRG = get_brg(baudrate); 	
//	/* Flag parsing */
//	if (!IS_MASTER(flags))
//		return -EE_SPI_ERR_UNIMPLEMENTED;
//	if (IS_DMA_RX(flags)) 
//		return -EE_SPI_ERR_UNIMPLEMENTED;
//	port1_flags = flags;
//	v = flags & MCHP_SPICON_MASKS;	// Select Microchip valid bits
//	if (IS_DMA_TX(flags)) {
//		IEC1CLR = SPI1_DMAIE_MASK;		
//		IFS1CLR = SPI1_DMAIF_MASK;		
//		IPC9CLR = SPI1_DMAIP_MASK | SPI1_DMAIS_MASK;
//		IPC9SET = ((5 << SPI1_DMAIP_POS) & SPI1_DMAIP_MASK) | 
//			  ((2 << SPI1_DMAIS_POS) & SPI1_DMAIS_MASK);
//		DMACONSET = _DMACON_ON_MASK; 
//		SPI1_DCHCON = 0; // TODO: check this, now priority = 0
//		SPI1_DCHECON = SPI_DCHECON_SIRQEN_MASK | 
//			       (_SPI1_TX_IRQ << SPI_DCHECON_CHSIRQ_POS);
//		SPI1_DCHINT = 0;
//	}
//	SPI1CON = v | _SPI1CON_ON_MASK;
//
//	return EE_SPI_NO_ERRORS;
}

__INLINE__ EE_UINT8 init_port2(EE_UINT32 baudrate, EE_UINT16 flags)
{
	//EE_UREG v; 
//
//	IEC1CLR = _IEC1_SPI2EIE_MASK | _IEC1_SPI2TXIE_MASK | 
//		  _IEC1_SPI2RXIE_MASK;
//	IFS1CLR = _IFS1_SPI2EIF_MASK | _IFS1_SPI2TXIF_MASK | 
//		  _IFS1_SPI2RXIF_MASK;
//	SPI2CON = 0;
//	SPI2STATCLR = _SPI2STAT_SPIROV_MASK; 
//	SPI2BRG = get_brg(baudrate); 	
//	/* Flag parsing */
//	if (!IS_MASTER(flags))
//		return -EE_SPI_ERR_UNIMPLEMENTED;
//	if (IS_DMA_RX(flags)) 
//		return -EE_SPI_ERR_UNIMPLEMENTED;
//	port2_flags = flags;
//	v = flags & MCHP_SPICON_MASKS;	// Select Microchip valid bits
//	if (IS_DMA_TX(flags)) {
//		IEC1CLR = SPI2_DMAIE_MASK;		
//		IFS1CLR = SPI2_DMAIF_MASK;		
//		IPC9CLR = SPI2_DMAIP_MASK | SPI2_DMAIS_MASK;
//		IPC9SET = ((5 << SPI2_DMAIP_POS) & SPI2_DMAIP_MASK) | 
//			  ((2 << SPI2_DMAIS_POS) & SPI2_DMAIS_MASK);
//		DMACONSET = _DMACON_ON_MASK; 
//		SPI2_DCHCON = 0; // TODO: check this, now priority = 0
//		SPI2_DCHECON = SPI_DCHECON_SIRQEN_MASK | 
//			       (_SPI2_TX_IRQ << SPI_DCHECON_CHSIRQ_POS);
//		SPI2_DCHINT = 0;
//	}
//	SPI2CON = v | _SPI2CON_ON_MASK;
//
//	return EE_SPI_NO_ERRORS;
}

__INLINE__ EE_INT8 write_dma_port1(EE_UINT8 *data, EE_UINT32 len)
{
	///* TODO: limit someway the lenght? */
//	if ((SPI1_DCHCON & SPI_DCHCON_CHEN_MASK) || 
//	   (SPI1STAT & _SPI1STAT_SPIBUSY_MASK))
//		return -EE_SPI_ERR_BUSY;
//	IFS0CLR = _IFS0_SPI1TXIF_MASK;		// Clear SPITX IRQ flag 
//	IEC1CLR = SPI1_DMAIE_MASK;		// Stop DMA channel IRQ
//	IFS1CLR = SPI1_DMAIF_MASK;		// Clear DMA channel IRQ
//	SPI1_DCHINT = 0;			// Clear IRQ sources
//	SPI1_DCHSSA = ADDR_VIRTUAL_TO_PHYSICAL(data);
//	SPI1_DCHDSA = ADDR_VIRTUAL_TO_PHYSICAL((void *)&SPI1BUF);
//	SPI1_DCHSSIZ = len;
//	SPI1_DCHDSIZ = 1;
//	SPI1_DCHCSIZ = 1;
//	SPI1_DCHINTSET = SPI_DCHINT_CHBCIE_MASK;// IRQ Source is end-of-block
//	IEC1SET = SPI1_DMAIE_MASK;		// Enable DMA channel IRQ
//	SPI1_DCHCONSET = SPI_DCHCON_CHEN_MASK;	// Enable DMA Channel 
//	SPI1_DCHECONSET = SPI_DCHECON_CFORCE_MASK; 	// Force Tx Start 
//
//	return EE_SPI_NO_ERRORS;
}

__INLINE__ EE_INT8 write_dma_port2(EE_UINT8 *data, EE_UINT32 len)
{
//	/* TODO: limit someway the lenght? */
//	if ((SPI2_DCHCON & SPI_DCHCON_CHEN_MASK) || 
//	   (SPI2STAT & _SPI2STAT_SPIBUSY_MASK))
//		return -EE_SPI_ERR_BUSY;
//	IFS1CLR = _IFS1_SPI2TXIF_MASK;		// Clear SPITX IRQ flag 
//	IEC1CLR = SPI2_DMAIE_MASK;		// Stop DMA channel IRQ
//	IFS1CLR = SPI2_DMAIF_MASK;		// Clear DMA channel IRQ
//	SPI2_DCHINT = 0;			// Clear IRQ sources
//	SPI2_DCHSSA = ADDR_VIRTUAL_TO_PHYSICAL(data);
//	SPI2_DCHDSA = ADDR_VIRTUAL_TO_PHYSICAL((void *)&SPI2BUF);
//	SPI2_DCHSSIZ = len;
//	SPI2_DCHDSIZ = 1;
//	SPI2_DCHCSIZ = 1;
//	SPI2_DCHINTSET = SPI_DCHINT_CHBCIE_MASK;// IRQ Source is end-of-block
//	IEC1SET = SPI2_DMAIE_MASK;		// Enable DMA channel IRQ
//	SPI2_DCHCONSET = SPI_DCHCON_CHEN_MASK;	// Enable DMA Channel 
//	SPI2_DCHECONSET = SPI_DCHECON_CFORCE_MASK; 	// Force Tx Start 
//
//	return EE_SPI_NO_ERRORS;
}

__INLINE__ EE_INT8 write_polling_port1(EE_UINT8 *data, EE_UINT32 len) 
{
	//EE_UINT32 i;
//	register EE_UREG dummy;
//
//	/* TODO: what if Slave mode?  */
//	for (i = 0; i < len; i++) {
//		/* TODO: use the SPIROV in IRQ mode */
//		SPI1STATCLR = _SPI1STAT_SPIROV_MASK; 
//   		while (!SPI1STATbits.SPITBE) ; 
//   		SPI1BUF = data[i];
//   		while (!SPI1STATbits.SPIRBF) ;
//		SPI1STATCLR = _SPI1STAT_SPIROV_MASK; 
//		dummy = SPI1BUF & 0x00FF;
//	}
//	return EE_SPI_NO_ERRORS;
}

__INLINE__ EE_INT8 write_polling_port2(EE_UINT8 *data, EE_UINT32 len) 
{
	//EE_UINT32 i;
//	register EE_UREG dummy;
//
//	/* TODO: what if Slave mode?  */
//	for (i = 0; i < len; i++) {
//		/* TODO: use the SPIROV in IRQ mode */
//		SPI2STATCLR = _SPI2STAT_SPIROV_MASK; 
//   		while (!SPI2STATbits.SPITBE) ; 
//   		SPI2BUF = data[i];
//   		while (!SPI2STATbits.SPIRBF) ;
//		SPI2STATCLR = _SPI2STAT_SPIROV_MASK; 
//		dummy = SPI2BUF & 0x00FF;
//	}
//	return EE_SPI_NO_ERRORS;
}

__INLINE__ EE_INT8 read_polling_port1(EE_UINT8 *data, EE_UINT32 len) 
{
	//EE_UINT32 i;
//
//	/* TODO: what if Slave mode?  */
//	for (i = 0; i < len; i++) {
//		/* TODO: use the SPIROV in IRQ mode */
//		SPI1STATCLR = _SPI1STAT_SPIROV_MASK; 
//   		while (!SPI1STATbits.SPITBE) ; 
//   		SPI1BUF = 0;
//   		while (!SPI1STATbits.SPIRBF) ;
//		SPI1STATCLR = _SPI1STAT_SPIROV_MASK; 
//		data[i] = SPI1BUF & 0x00FF;
//	}
//	return EE_SPI_NO_ERRORS;
}

__INLINE__ EE_INT8 read_polling_port2(EE_UINT8 *data, EE_UINT32 len) 
{
	//EE_UINT32 i;
//
//	/* TODO: what if Slave mode?  */
//	for (i = 0; i < len; i++) {
//		/* TODO: use the SPIROV in IRQ mode */
//		SPI2STATCLR = _SPI2STAT_SPIROV_MASK; 
//   		while (!SPI2STATbits.SPITBE) ; 
//   		SPI2BUF = 0;
//   		while (!SPI2STATbits.SPIRBF) ;
//		SPI2STATCLR = _SPI2STAT_SPIROV_MASK; 
//		data[i] = SPI2BUF & 0x00FF;
//	}
//	return EE_SPI_NO_ERRORS;
}

/******************************************************************************/
/*                                SPI ISRs                                    */
/******************************************************************************/
ISR2(SPI1_DMA_IRQ) 
{
	//register EE_UREG dummy;
//
//	// TODO: when DMA rx is done, rebuild this ISR!
//	IFS1CLR = SPI1_DMAIF_MASK;			// Clear DMA channel IRQ
//	if (SPI1_DCHINT & SPI_DCHINT_CHBCIF_MASK) {	// Check BlockEnd IRQ
//		SPI1_DCHINTCLR = SPI_DCHINT_CHBCIF_MASK;// Clear IRQ source
//		// TODO: check if this leads to deadlock
//		while (SPI1STAT & _SPI1STAT_SPIBUSY_MASK) ; // Wait bus done
//		dummy = SPI1BUF;			// Clean the SPIRBF bit
//		if (port1_tx_callback)
//			port1_tx_callback();
//	}
}

ISR2(SPI2_DMA_IRQ) 
{
	//register EE_UREG dummy;
//
//	// TODO: when DMA rx is done, rebuild this ISR!
//	IFS1CLR = SPI2_DMAIF_MASK;			// Clear DMA channel IRQ
//	if (SPI2_DCHINT & SPI_DCHINT_CHBCIF_MASK) {	// Check BlockEnd IRQ
//		SPI2_DCHINTCLR = SPI_DCHINT_CHBCIF_MASK;// Clear IRQ source
//		// TODO: check if this leads to deadlock
//		while (SPI2STAT & _SPI2STAT_SPIBUSY_MASK) ; // Wait bus done
//		dummy = SPI2BUF;			// Clean the SPIRBF bit
//		if (port2_tx_callback)
//			port2_tx_callback();
//	}
}

/******************************************************************************/
/*                       Public Global Functions                              */
/******************************************************************************/
EE_INT8 EE_spi_init(EE_UINT8 port, EE_UINT32 baudrate, EE_UINT16 flags) 
{
	//if (port == EE_SPI_PORT_1) {
//		init_port1(baudrate, flags); 
//		return EE_SPI_NO_ERRORS;
//	} else if (port == EE_SPI_PORT_2) {
//		init_port2(baudrate, flags); 
//		return EE_SPI_NO_ERRORS;
//	}
//	return -EE_SPI_ERR_BAD_PORT;
}

EE_INT8 EE_spi_close(EE_UINT8 port)
{
	//if (port == EE_SPI_PORT_1) {
//		SPI1CONCLR= _SPI1CON_ON_MASK;
//		port1_flags = 0;
//		return EE_SPI_NO_ERRORS;
//	} else if (port == EE_SPI_PORT_2) {
//		SPI2CONCLR= _SPI2CON_ON_MASK;
//		port2_flags = 0;
//		return EE_SPI_NO_ERRORS;
//	}
//	return -EE_SPI_ERR_BAD_PORT;
}

EE_INT8 EE_spi_set_callback(EE_UINT8 port, EE_UINT8 event, void (*f)(void))
{	
	//if (port == EE_SPI_PORT_1) {
//		switch (event) {
//		case EE_SPI_EVT_TX_DONE :
//			port1_tx_callback = f;
//			break;
//		case EE_SPI_EVT_RX_DONE :
//		default :
//			return -EE_SPI_ERR_BAD_ARGS;
//		}
//		return EE_SPI_NO_ERRORS;
//	} else if (port == EE_SPI_PORT_2) {
//		switch (event) {
//		case EE_SPI_EVT_TX_DONE :
//			port2_tx_callback = f;
//			break;
//		case EE_SPI_EVT_RX_DONE :
//		default :
//			return -EE_SPI_ERR_BAD_ARGS;
//		}
//		return EE_SPI_NO_ERRORS;
//	}
//	return -EE_SPI_ERR_BAD_PORT;
}

EE_INT8 EE_spi_write(EE_UINT8 port, EE_UINT8 *data, EE_UINT32 len)
{
	//if (port == EE_SPI_PORT_1) {
//		if(IS_DMA_TX(port1_flags))
//			return write_dma_port1(data, len);
//		return write_polling_port1(data, len);
//	} else if (port == EE_SPI_PORT_2) {
//		if(IS_DMA_TX(port2_flags)) 
//			return write_dma_port2(data, len);
//		return write_polling_port2(data, len);
//	}
//	return -EE_SPI_ERR_BAD_PORT;

}

EE_INT8 EE_spi_read(EE_UINT8 port, EE_UINT8 *data, EE_UINT32 len)
{
	//if (port == EE_SPI_PORT_1) {
//		if(IS_DMA_RX(port1_flags)) 
//		//	read write_dma_port1(data, len);
//			return -EE_SPI_ERR_UNIMPLEMENTED;
//		return read_polling_port1(data, len);
//	} else if (port == EE_SPI_PORT_2) {
//		if(IS_DMA_RX(port2_flags)) 
//		//	read write_dma_port2(data, len);
//			return -EE_SPI_ERR_UNIMPLEMENTED;
//		return read_polling_port2(data, len);
//	}
//	return -EE_SPI_ERR_BAD_PORT;

}
