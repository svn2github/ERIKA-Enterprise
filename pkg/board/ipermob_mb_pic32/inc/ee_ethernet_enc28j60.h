#ifndef __EE_ETHERNET_ENC28J60_H__
#define __EE_ETHERNET_ENC28J60_H__



#if defined __32MX360F512L__
#define EE_ENC28J60_SPI_PORT		EE_SPI_PORT_2
#define EE_ENC28J60_IRQ_SPECIFIC_FLAG	IFS0bits.INT2IF
#define EE_ENC28J60_IRQ_SPECIFIC_ENABLE	IEC0bits.INT2IE
			
#elif defined __32MX795F512L__
#define EE_ENC28J60_SPI_PORT		EE_SPI_PORT_2A	
#define EE_ENC28J60_IRQ_SPECIFIC_FLAG	IFS0bits.INT2IF
#define EE_ENC28J60_IRQ_SPECIFIC_ENABLE	IEC0bits.INT2IE

#else
#error "ENC28J60 mcu not supported"
#endif 


#define EE_ENC28J60_SPI_BAUDRATE	20000000ul
#define EE_ENC28J60_SPI_FLAGS		EE_SPI_DEFAULT





#ifndef EE_ENC28J60_SPI_CS_TRIS	 
#define EE_ENC28J60_SPI_CS_TRIS		(TRISDbits.TRISD1)
#endif //EE_ENC28J60_WAKE_PIN_TRIS



#ifndef EE_ENC28J60_WAKE_PIN_LAT
#define EE_ENC28J60_WAKE_PIN_LAT		//TODO: not connected!!
#endif

#ifndef EE_ENC28J60_WAKE_PIN_TRIS
#define EE_ENC28J60_WAKE_PIN_TRIS		//TODO: not connected!!
#endif //EE_ENC28J60_WAKE_PIN_TRIS


/******************************************************************************/
/* 			Chip Select PIN Functions			      */
/******************************************************************************/




#ifndef EE_ENC28J60_SPI_CS 
#define EE_ENC28J60_SPI_CS 		(PORTDbits.RD1)
#endif



/* Used to initialize the TRIS register associated to the ENC28J60 Chip Select*/
#define EE_ENC28J60_spi_cs_init()	(EE_ENC28J60_SPI_CS_TRIS = 0)	



#define EE_ENC28J60_SPI_CS_LOW()	(EE_ENC28J60_SPI_CS = 0)



#define EE_ENC28J60_SPI_CS_HIGH()	(EE_ENC28J60_SPI_CS = 1)


#define EE_ENC28J60_set_CS()		EE_ENC28J60_SPI_CS_LOW()
#define EE_ENC28J60_clear_CS()		EE_ENC28J60_SPI_CS_HIGH()



/******************************************************************************/
/* 			Reset PIN Functions				      */
/******************************************************************************/

#ifndef EE_ENC28J60_RESET_TRIS
#define EE_ENC28J60_RESET_TRIS			(TRISFbits.TRISF0)
#endif

#ifndef EE_ENC28J60_RESET_LAT
#define EE_ENC28J60_RESET_LAT			(LATFbits.LATF0)
#endif

/* Inverted by bold evil electronic */
#define EE_ENC28J60_RESET_HIGH()		EE_ENC28J60_RESET_LAT = 0

/* Inverted by electronic */
#define EE_ENC28J60_RESET_LOW()			EE_ENC28J60_RESET_LAT = 1



#define EE_ENC28J60_gpio_init_reset()		(EE_ENC28J60_RESET_TRIS = 0)
#define EE_enc28j60_gpio_hold_in_reset()	EE_ENC28J60_RESET_HIGH()
#define	EE_enc28j60_gpio_release_reset() 	EE_ENC28J60_RESET_LOW()



/******************************************************************************/
/* 			Interrupt PIN FUNCTIONS				      */
/******************************************************************************/



#define	EE_ENC28J60_INT_ENABLE_CLR()	(EE_ENC28J60_IRQ_SPECIFIC_ENABLE = 0)
#define	EE_ENC28J60_INT_ENABLE_SET()	(EE_ENC28J60_IRQ_SPECIFIC_ENABLE = 1)
#define	EE_ENC28J60_INT_ENABLE_GET()	(EE_ENC28J60_IRQ_SPECIFIC_ENABLE)


/******************************************************************************/
/* 			Wake PIN FUNCTIONS				      */
/******************************************************************************/

//TODO: in this board the wake pin is not connected, so this function must
// do nothing 	

#define EE_enc28j60_gpio_wake_pin(val)		

#define EE_enc28j60_gpio_wake_pin_set()	
#define EE_enc28j60_gpio_wake_pin_clr()	






/******************************************************************************/
/* 				INLINE Functions			      */
/******************************************************************************/


__INLINE__ void __ALWAYS_INLINE__ EE_enc28j60_gpio_enable_IRQ(void){ \
	EE_ENC28J60_INT_ENABLE_SET();
}



__INLINE__ void __ALWAYS_INLINE__ EE_enc28j60_gpio_disable_IRQ(void){ \
	EE_ENC28J60_INT_ENABLE_CLR();
}


__INLINE__ int __ALWAYS_INLINE__ EE_enc28j60_gpio_IRQ_enabled(void){ \
	return EE_ENC28J60_INT_ENABLE_GET();	
	//return (cat3(EE_, lc, _read_irqMask)() & EE_INTPIN_MASK); 
} 

/*
__INLINE__ int __ALWAYS_INLINE__ EE_enc28j60_pending_interrupt(void){ \
	return (cat3(EE_, lc, _read_data)() & EE_INTPIN_MASK); \
}
*/

__INLINE__ void __ALWAYS_INLINE__ EE_enc28j60_gpio_wake_active(void){
	EE_enc28j60_gpio_wake_pin_set();
}

__INLINE__ void __ALWAYS_INLINE__ EE_enc28j60_gpio_wake_inactive(void){
	EE_enc28j60_gpio_wake_pin_clr();
}

void EE_enc28j60_handler(int level);

#endif //__EE_ETHERNET_ENC28J60_H__
