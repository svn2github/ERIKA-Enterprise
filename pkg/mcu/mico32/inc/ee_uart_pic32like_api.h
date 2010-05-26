/*
  Name: ee_uart_pic32like.h
  Copyright: Evidence Srl
  Author: Dario Di Stefano
  Date: 29/03/10 18.28
  Description: Uart driver functions for compatibility with pic32 projects. 
*/


#ifndef __INCLUDE_EEMCUMICO32_UART_PIC32LIKE_H__
#define __INCLUDE_EEMCUMICO32_UART_PIC32LIKE_H__

/* ------------------------------------------------ */
/* Macros for compatibility with pic32 uart driver*/ 
/* ------------------------------------------------ */

#define EE_mchp_uart_init(lc, baud, bf, mode) EE_hal_uart_config(& EE_ST_NAME(lc), baud, bf)
#define EE_mchp_uart_write_byte(lc, data) EE_hal_uart_write_byte(& EE_ST_NAME(lc), data)            
#define EE_mchp_uart_read_byte(lc, data) EE_hal_uart_read_byte(& EE_ST_NAME(lc), data)  
#define EE_mchp_uart_set_rx_callback(lc, rxcbk) EE_hal_uart_set_rx_callback(& EE_ST_NAME(lc), rxcbk)

__INLINE__ EE_INT8 __ALWAYS_INLINE__ EE_uart_init(EE_UINT8 port, EE_UINT32 baud, EE_UINT16 byte_format, EE_UINT16 mode)
{
    EE_INT8 ret;
    
    #if defined(EE_UART1_NAME_LC) && defined(EE_UART2_NAME_LC)
    if(port==1)
        ret = EE_mchp_uart_init(EE_UART1_NAME_LC, baud, byte_format, mode);
    else 
        ret = EE_mchp_uart_init(EE_UART2_NAME_LC, baud, byte_format, mode);
    #else
        #if defined(EE_UART1_NAME_LC)
        ret = EE_mchp_uart_init(EE_UART1_NAME_LC, baud, byte_format, mode);
        #else   
        ret = EE_mchp_uart_init(EE_UART2_NAME_LC, baud, byte_format, mode);
        #endif
    #endif
    
    return ret;
}

__INLINE__ EE_INT8 __ALWAYS_INLINE__ EE_uart_close(EE_UINT8 port)
{
    return EE_UART_OK;
}

__INLINE__ EE_INT8 __ALWAYS_INLINE__ EE_uart_write_byte(EE_UINT8 port, EE_UINT8 data)
{
    EE_INT8 ret;
    
    #if defined(EE_UART1_NAME_LC) && defined(EE_UART2_NAME_LC)
    if(port==1)
        ret = EE_mchp_uart_write_byte(EE_UART1_NAME_LC, data);
    else 
        ret = EE_mchp_uart_write_byte(EE_UART2_NAME_LC, data);
    #else
        #if defined(EE_UART1_NAME_LC)
        ret = EE_mchp_uart_write_byte(EE_UART1_NAME_LC, data);
        #else   
        ret = EE_mchp_uart_write_byte(EE_UART2_NAME_LC, data);
        #endif
    #endif
    
    return ret;

}

__INLINE__ EE_INT8 __ALWAYS_INLINE__ EE_uart_read_byte(EE_UINT8 port, EE_UINT8 *data)
{
    EE_INT8 ret;
    
    #if defined(EE_UART1_NAME_LC) && defined(EE_UART2_NAME_LC)
    if(port==1)
        ret = EE_mchp_uart_read_byte(EE_UART1_NAME_LC, data);
    else 
        ret = EE_mchp_uart_read_byte(EE_UART2_NAME_LC, data);
    #else
        #if defined(EE_UART1_NAME_LC)
        ret = EE_mchp_uart_read_byte(EE_UART1_NAME_LC, data);
        #else   
        ret = EE_mchp_uart_read_byte(EE_UART2_NAME_LC, data);
        #endif
    #endif
    
    return ret;

}

#ifdef __USE_UART_IRQ__
typedef void (*EE_mchp_ISR_callback)(EE_UINT8);
extern EE_mchp_ISR_callback ee_mchp_uart1_ISR_cbk;
extern EE_mchp_ISR_callback ee_mchp_uart2_ISR_cbk;
void ee_aux_uart1_ISR_cbk(void);
void ee_aux_uart2_ISR_cbk(void);

__INLINE__ EE_INT8 __ALWAYS_INLINE__ EE_uart_set_rx_callback(EE_UINT8 port, void (*RxFunc)(EE_UINT8 data), EE_UINT8 rxmode)
{
    EE_INT8 ret;
    
    #if defined(EE_UART1_NAME_LC) && defined(EE_UART2_NAME_LC)
    if(port==1)
    {
        ee_mchp_uart1_ISR_cbk = RxFunc;
        ret = EE_mchp_uart_set_rx_callback(EE_UART1_NAME_LC, ee_aux_uart1_ISR_cbk);
    }
    else 
    {
        ee_mchp_uart2_ISR_cbk = RxFunc;
        ret = EE_mchp_uart_set_rx_callback(EE_UART2_NAME_LC, ee_aux_uart2_ISR_cbk);
    }
    #else
        #if defined(EE_UART1_NAME_LC)
        ee_mchp_uart1_ISR_cbk = RxFunc;
        ret = EE_mchp_uart_set_rx_callback(EE_UART1_NAME_LC, ee_aux_uart1_ISR_cbk);
        #else   
        ee_mchp_uart2_ISR_cbk = RxFunc;
        ret = EE_mchp_uart_set_rx_callback(EE_UART2_NAME_LC, ee_aux_uart2_ISR_cbk);
        #endif
    #endif
    
    return ret;
}
#endif // #ifdef __USE_UART_IRQ__

#endif //__INCLUDE_EEMCUMICO32_UART_PIC32LIKE_H__
