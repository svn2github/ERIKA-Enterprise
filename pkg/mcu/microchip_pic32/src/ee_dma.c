#include "mcu/microchip_pic32/inc/ee_dma.h"
#include "cpu/pic32/inc/ee_utils.h"

#ifdef __PIC32_INCLUDE_REGS__
#include "ee_pic32regs.h"
#endif


/******************************************************************************/
/*				Local Functions				      */
/******************************************************************************/

EE_INT8	dma_init_ch0(void) {


	/* Disabled the DMA interrupts */	
	IEC1CLR = _IEC1_DMA0IE_MASK;  		
	/* Cleaned the DMA interrupt flags */
	IFS1CLR = _IFS1_DMA0IF_MASK; 		
	
	/* Turn on the DMA peripheral */		
	DMACONSET = _DMACON_ON_MASK; 

	return EE_DMA_NO_ERR;
}


#ifdef __32MX795F512L__
EE_INT8	dma_init_ch4(void) {
	
	/* Disabled the DMA interrupts */	
	IEC1CLR = _IEC1_DMA4IE_MASK;  		
	/* Cleaned the DMA interrupt flags */
	IFS1CLR = _IFS1_DMA4IF_MASK; 		
	
	/* Turn on the DMA peripheral */		
	DMACONSET = _DMACON_ON_MASK; 	
	return EE_DMA_NO_ERR;

}
#endif //__32MX795F512L__



EE_INT8 dma_event_setup_ch0(EE_UINT8 subpriority, EE_UREG event_control_flags) {


	/* Setup of the priority of the channel */
	DCH0CONSET = (subpriority) & _DCH0CON_CHPRI_MASK;
	
	/* Channel disabled */ 
	DCH0CONCLR = _DCH0CON_CHEN_MASK;
	
	/* Set of the  */ 
	DCH0ECONSET = event_control_flags;

	return EE_DMA_NO_ERR;

}



#ifdef __32MX795F512L__
EE_INT8	dma_event_setup_ch4(EE_UINT8 subpriority, EE_UREG event_control_flags) {
	
	/* Setup of the priority of the channel */
	DCH4CONSET = (subpriority) & _DCH4CON_CHPRI_MASK;
	
	/* Channel disabled */ 
	DCH4CONCLR = _DCH4CON_CHEN_MASK;
	
	/* Set of the  */ 
	DCH4ECONSET = event_control_flags;

	return EE_DMA_NO_ERR;

}
#endif //__32MX795F512L__


EE_INT8 dma_init_transfer_ch0(EE_UINT16 source_size, EE_UINT16 destination_size,
		EE_UINT16 cell_size, EE_INT16 interrupt_request_source, EE_UINT8 int_prior, 
		EE_UINT8 int_subprior) {

	/* Setup of the source, destination and cell size. See refman for more
	specific information about the use	*/
	DCH0SSIZ = (EE_UINT8) source_size;
	DCH0DSIZ = (EE_UINT8) destination_size; 
	DCH0CSIZ = (EE_UINT8) cell_size;

	/* Interrupt register clean */	
	DCH0INTCLR = 0;	

	
	/* Set the interrupt source that starts the acquisition */	
	if ( interrupt_request_source >= 0 ) {
		DCH0ECON = _DCH0ECON_SIRQEN_MASK | 
			       (interrupt_request_source  << _DCH0ECON_CHSIRQ_POSITION);
	
		/* Set the interrupt priority */
		IPC9CLR = _IPC9_DMA0IP_MASK | _IPC9_DMA0IS_MASK;
		IPC9SET = ((int_prior <<_IPC9_DMA0IP_POSITION ) & _IPC9_DMA0IP_MASK)  |
			  ((int_subprior << _IPC9_DMA0IS_MASK) & _IPC9_DMA0IS_MASK);	
	}
	
	return EE_DMA_NO_ERR;
}


#ifdef __32MX795F512L__
EE_INT8 dma_init_transfer_ch4(EE_UINT16 source_size, EE_UINT16 destination_size,
		EE_UINT16 cell_size, EE_INT16 interrupt_request_source, EE_UINT8 int_prior, 
		EE_UINT8 int_subprior) {

	/* Setup of the source, destination and cell size. See refman for more
	specific information about the use	*/
	DCH4SSIZ = (EE_UINT8) source_size;
	DCH4DSIZ = (EE_UINT8) destination_size; 
	DCH4CSIZ = (EE_UINT8) cell_size;

	/* Interrupt register clean */	
	DCH4INTCLR= 0;	

	
	/* Set the interrupt source that starts the acquisition */	
	if ( interrupt_request_source >= 0 ) {
		DCH4ECON = _DCH4ECON_SIRQEN_MASK | 
			       (interrupt_request_source  << _DCH4ECON_CHSIRQ_POSITION);
	
		/* Set the interrupt priority */
		IPC10CLR = _IPC10_DMA4IP_MASK | _IPC10_DMA4IS_MASK;
		IPC10SET = ((int_prior <<_IPC10_DMA4IP_POSITION ) & _IPC10_DMA4IP_MASK)  |
			  ((int_subprior << _IPC10_DMA4IS_MASK) & _IPC10_DMA4IS_MASK);	
	}
	
	return EE_DMA_NO_ERR;
}
#endif //__32MX795F512L__




/******************************************************************************/
/*				Global Functions			      */
/******************************************************************************/



EE_INT8 EE_dma_init(EE_UINT8 channel) {
	switch (channel) {
		case EE_DMA_CH0:
			return dma_init_ch0();
		break;

		case EE_DMA_CH1:
			return -EE_DMA_CHANNEL_NOT_AVAILABLE;
		break;

		case EE_DMA_CH2:
			return -EE_DMA_CHANNEL_NOT_AVAILABLE;		
		break;

		case EE_DMA_CH3:
			return -EE_DMA_CHANNEL_NOT_AVAILABLE;
		break;
		
	#ifdef __32MX795F512L__
		case EE_DMA_CH4:
			return dma_init_ch4();		
		break;
		
		case EE_DMA_CH5:
			return -EE_DMA_CHANNEL_NOT_AVAILABLE;
		break;
		
		case EE_DMA_CH6:
			return -EE_DMA_CHANNEL_NOT_AVAILABLE;
		break;

		case EE_DMA_CH7:
			return -EE_DMA_CHANNEL_NOT_AVAILABLE;
		break;
	#endif
		
		default:
			return -EE_DMA_CHANNEL_NOT_AVAILABLE;
	}	


}


EE_INT8 EE_dma_advanced_setup(EE_UINT8 channel, EE_UINT8 subpriority, 
				EE_UREG event_control_flags ) {
	switch (channel) {
		case EE_DMA_CH0:
			return dma_event_setup_ch0(subpriority,
						event_control_flags);
		break;

		case EE_DMA_CH1:
			return -EE_DMA_CHANNEL_NOT_AVAILABLE;
		break;

		case EE_DMA_CH2:
			return -EE_DMA_CHANNEL_NOT_AVAILABLE;		
		break;

		case EE_DMA_CH3:
			return -EE_DMA_CHANNEL_NOT_AVAILABLE;
		break;
		
	#ifdef __32MX795F512L__
		case EE_DMA_CH4:
			return dma_event_setup_ch4(subpriority,
						event_control_flags);		
		break;
		
		case EE_DMA_CH5:
			return -EE_DMA_CHANNEL_NOT_AVAILABLE;
		break;
		
		case EE_DMA_CH6:
			return -EE_DMA_CHANNEL_NOT_AVAILABLE;
		break;

		case EE_DMA_CH7:
			return -EE_DMA_CHANNEL_NOT_AVAILABLE;
		break;
	#endif
		
		default:
			return -EE_DMA_CHANNEL_NOT_AVAILABLE;
	}	
}





EE_INT8 EE_dma_init_transfer(EE_UINT8 channel, EE_UINT16 source_size, EE_UINT16 destination_size,
		EE_UINT16 cell_size, EE_INT16 interrupt_request_source, EE_UINT8 int_prior, 
		EE_UINT8 int_subprior) {
	switch (channel) {
	
		case EE_DMA_CH0:
			return dma_init_transfer_ch0(source_size, destination_size,
					cell_size, interrupt_request_source, 
					int_prior, int_subprior);
		break;

		case EE_DMA_CH1:
			return -EE_DMA_CHANNEL_NOT_AVAILABLE;
		break;

		case EE_DMA_CH2:
			return -EE_DMA_CHANNEL_NOT_AVAILABLE;		
		break;

		case EE_DMA_CH3:
			return -EE_DMA_CHANNEL_NOT_AVAILABLE;
		break;
		
	#ifdef __32MX795F512L__
		case EE_DMA_CH4:
			return dma_init_transfer_ch4(source_size, destination_size,
					cell_size, interrupt_request_source, 
					int_prior, int_subprior);		
		break;
		
		case EE_DMA_CH5:
			return -EE_DMA_CHANNEL_NOT_AVAILABLE;
		break;
		
		case EE_DMA_CH6:
			return -EE_DMA_CHANNEL_NOT_AVAILABLE;
		break;

		case EE_DMA_CH7:
			return -EE_DMA_CHANNEL_NOT_AVAILABLE;
		break;
	#endif
		
		default:
			return -EE_DMA_CHANNEL_NOT_AVAILABLE;
	}	
}

