/*
  Name: ee_spi_pic32like.h
  Copyright: Evidence Srl
  Author: Dario Di Stefano
  Date: 29/03/10 18.23
  Description: SPI driver functions for compatibility with pic32 projects. 
*/

#ifndef __INCLUDE_EEMCUMICO32_SPI_PIC32LIKE_H__
#define __INCLUDE_EEMCUMICO32_SPI_PIC32LIKE_H__

/* ------------------------------------------------ */
/* Macros for compatibility with pic32 SPI driver*/ 
/* ------------------------------------------------ */

#define EE_SPI_EVT_TX_DONE 					(0x01)
#define EE_SPI_EVT_RX_DONE 					(0x00)
#ifdef __USE_SPI_IRQ__
#define EE_mchp_spi_init(lc, flags)			EE_hal_spi_config(& EE_ST_NAME(lc), flags)
#else
#define EE_mchp_spi_init(uc, flags)			EE_hal_spi_config((MicoSPI_t *)EE_BASE_ADD(uc), flags)
#endif
#define EE_mchp_spi_set_tx_cbk(lc, cbk) 	EE_hal_spi_set_tx_ISR_callback(& EE_ST_NAME(lc), cbk)
#define EE_mchp_spi_set_rx_cbk(lc, cbk) 	EE_hal_spi_set_rx_ISR_callback(& EE_ST_NAME(lc), cbk)
#define EE_mchp_spi_write(uc, data, len)	EE_hal_spi_write_buffer_polling((MicoSPI_t *)EE_BASE_ADD(uc), data, len)
#define EE_mchp_spi_read(uc, data, len)		EE_hal_spi_read_buffer_polling((MicoSPI_t *)EE_BASE_ADD(uc), data, len)

__INLINE__ EE_INT8 __ALWAYS_INLINE__ EE_spi_init(EE_UINT8 port, EE_UINT32 baudrate, EE_UINT16 flags)
{
	EE_INT8 ret;
	
	#if defined(EE_SPI1_NAME_UC) && defined(EE_SPI2_NAME_UC)
	if(port==1)
		#ifdef __USE_SPI_IRQ__
		ret = EE_mchp_spi_init(EE_SPI1_NAME_LC, flags);
		#else
		ret = EE_mchp_spi_init(EE_SPI1_NAME_UC, flags);
		#endif
	else
		#ifdef __USE_SPI_IRQ__
		ret = EE_mchp_spi_init(EE_SPI2_NAME_LC, flags);
		#else
		ret = EE_mchp_spi_init(EE_SPI2_NAME_UC, flags);
		#endif
	#else
		#if defined(EE_SPI1_NAME_UC)
		#ifdef __USE_SPI_IRQ__
		ret = EE_mchp_spi_init(EE_SPI1_NAME_LC, flags);
		#else
		ret = EE_mchp_spi_init(EE_SPI1_NAME_UC, flags);
		#endif
		#else
		#ifdef __USE_SPI_IRQ__
		ret = EE_mchp_spi_init(EE_SPI2_NAME_LC, flags);
		#else
		ret = EE_mchp_spi_init(EE_SPI2_NAME_UC, flags);
		#endif
		#endif
	#endif
		
	return ret;
}

__INLINE__ EE_INT8 __ALWAYS_INLINE__ EE_spi_close(EE_UINT8 port)
{
	// not used on LM32 device...
	return EE_SPI_OK;
}

#ifdef __USE_SPI_IRQ__
__INLINE__ EE_INT8 __ALWAYS_INLINE__ EE_spi_set_callback(EE_UINT8 port, EE_UINT8 event, void (*f)(void))
{
	EE_INT8 ret;
	
	#if defined(EE_SPI1_NAME_UC) && defined(EE_SPI2_NAME_UC)
	if(port==1)
		if(event == EE_SPI_EVT_RX_DONE)
			ret = EE_mchp_spi_set_rx_cbk(EE_SPI1_NAME_LC, f);
		else
			ret = EE_mchp_spi_set_tx_cbk(EE_SPI1_NAME_LC, f);
	else
		if(event == EE_SPI_EVT_RX_DONE)
			ret = EE_mchp_spi_set_rx_cbk(EE_SPI2_NAME_LC, f);
		else
			ret = EE_mchp_spi_set_tx_cbk(EE_SPI2_NAME_LC, f); 
	#else
		#if defined(EE_SPI1_NAME_UC)
		if(event == EE_SPI_EVT_RX_DONE)
			ret = EE_mchp_spi_set_rx_cbk(EE_SPI1_NAME_LC, f);
		else
			ret = EE_mchp_spi_set_tx_cbk(EE_SPI1_NAME_LC, f);
		#else
		if(event == EE_SPI_EVT_RX_DONE)
			ret = EE_mchp_spi_set_rx_cbk(EE_SPI2_NAME_LC, f);
		else
			ret = EE_mchp_spi_set_tx_cbk(EE_SPI2_NAME_LC, f); 
		#endif
	#endif
		
	return ret;
}
#else	//#ifdef __USE_SPI_IRQ__
__INLINE__ EE_INT8 __ALWAYS_INLINE__ EE_spi_set_callback(EE_UINT8 port, EE_UINT8 event, void (*f)(void))
{
	// not used in polling mode...
	return 0;
}
#endif 	//#ifdef __USE_SPI_IRQ__

__INLINE__ EE_INT8 __ALWAYS_INLINE__ EE_spi_write(EE_UINT8 port, EE_UINT8 *data, EE_UINT32 len)
{
	EE_INT8 ret;
	
	#if defined(EE_SPI1_NAME_UC) && defined(EE_SPI2_NAME_UC)
	if(port==1)
		ret = EE_mchp_spi_write(EE_SPI1_NAME_UC, data, len);
	else
		ret = EE_mchp_spi_write(EE_SPI2_NAME_UC, data, len);
	#else
		#if defined(EE_SPI1_NAME_UC)
		ret = EE_mchp_spi_write(EE_SPI1_NAME_UC, data, len);
		#else
		ret = EE_mchp_spi_write(EE_SPI2_NAME_UC, data, len);
		#endif
	#endif
		
	return ret;
}

__INLINE__ EE_INT8 __ALWAYS_INLINE__ EE_spi_read(EE_UINT8 port, EE_UINT8 *data, EE_UINT32 len)
{
	EE_INT8 ret;
	
	#if defined(EE_SPI1_NAME_UC) && defined(EE_SPI2_NAME_UC)
	if(port==1)
		ret = EE_mchp_spi_read(EE_SPI1_NAME_UC, data, len);
	else
		ret = EE_mchp_spi_read(EE_SPI2_NAME_UC, data, len);
	#else
		#if defined(EE_SPI1_NAME_UC)
		ret = EE_mchp_spi_read(EE_SPI1_NAME_UC, data, len);
		#else
		ret = EE_mchp_spi_read(EE_SPI2_NAME_UC, data, len);
		#endif
	#endif
		
	return ret;
}

__INLINE__ EE_INT8 __ALWAYS_INLINE__ EE_spi_cycle(EE_UINT8 port, EE_UINT8 *data_out, EE_UINT8 *data_in, EE_UINT32 len)
{
	// not implemented...
	return 0;
}

#endif //__INCLUDE_EEMCUMICO32_SPI_PIC32LIKE_H__
