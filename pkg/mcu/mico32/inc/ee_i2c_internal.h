#ifndef __EE_I2C_INTERNAL_H__
#define __EE_I2C_INTERNAL_H__

#ifdef __USE_I2C__

#include <eecfg.h>
#include "mcu/mico32/inc/ee_internal.h"
#include "OpenCoresI2CMaster.h"

/*************************************************************************
 I2C
 *************************************************************************/

#ifdef __USE_I2C_IRQ__
/*
	I2C structure:
*/

typedef struct {
	int err;							// last error condition
	int mode;							// i2c operating mode (polling, isr, ...)
	int ir;								// flag to discriminate interrupt source (rx or tx)
    OCI2CMDev_t* base;					// controller base address
    int irqf;							// irq flag
    EE_ISR_callback rxcbk;				// rx callback
    EE_ISR_callback txcbk;				// tx callback
    EE_buffer rxbuf;					// rx buffer used in isr mode
    EE_buffer txbuf;					// tx buffer used in isr mode
} EE_i2c_st;

/* Macro for the structure name generation */
#define EE_I2C_ST_NAME(lc) cat3(ee_, lc, _st)
/* Macro for Structure declaration */
#define DECLARE_STRUCT_I2C(uc, lc) \
  extern EE_i2c_st EE_I2C_ST_NAME(lc);
/* Macro for structure definition */
#define DEFINE_STRUCT_I2C(uc, lc) \
EE_i2c_st cat3(ee_, lc, _st) = { \
	.err=EE_I2C_OK, .mode= EE_I2C_POLLING | EE_I2C_RXTX_BLOCK, .base= (OCI2CMDev_t* )cat2(uc, _BASE_ADDRESS),\
	.irqf= cat2(uc, _IRQ), .rxcbk= EE_I2C_NULL_CBK, .txcbk= EE_I2C_NULL_CBK,\
	.rxbuf.data= EE_I2C_VETRX_NAME(lc),.txbuf.data= EE_I2C_VETTX_NAME(lc)};

int EE_hal_i2c_config(EE_i2c_st* i2csp, int baudrate, int setttings);									
int EE_hal_i2c_set_mode(EE_i2c_st* i2csp, int mode);												
int EE_hal_i2c_set_rx_callback(EE_i2c_st* i2csp, EE_ISR_callback isr_rx_callback);						
int EE_hal_i2c_set_tx_callback(EE_i2c_st* i2csp, EE_ISR_callback isr_tx_callback);		
int EE_hal_i2c_enable_IRQ(EE_i2c_st* i2csp);															
int EE_hal_i2c_disable_IRQ(EE_i2c_st* i2csp);															
int EE_hal_i2c_disable(EE_i2c_st* i2csp);																
int EE_hal_i2c_enable(EE_i2c_st* i2csp);																
int EE_hal_i2c_start(EE_i2c_st* i2csp);																	
int EE_hal_i2c_stop(EE_i2c_st* i2csp);																	
int EE_hal_i2c_return_error(EE_i2c_st* i2csp);			
int EE_hal_i2c_write_byte_polling(EE_i2c_st* i2csp, EE_UINT8 device, EE_UINT8 address, EE_UINT8 data);	
int EE_hal_i2c_write_byte_irq(EE_i2c_st* i2csp, EE_UINT8 device, EE_UINT8 address, EE_UINT8 data);	
int EE_hal_i2c_read_byte_polling(EE_i2c_st* i2csp, EE_UINT8 device, EE_UINT8 address, EE_UINT8 *data);	
int EE_hal_i2c_read_byte_irq(EE_i2c_st* i2csp, EE_UINT8 device, EE_UINT8 address, EE_UINT8 *data);	
int EE_hal_i2c_read_buffer_polling(EE_i2c_st* i2csp, EE_UINT8 device, EE_UINT8 address, EE_UINT8 *data, int len);
int EE_hal_i2c_read_buffer_irq(EE_i2c_st* i2csp, EE_UINT8 device, EE_UINT8 address, EE_UINT8 *data, int len);	
int EE_hal_i2c_write_buffer_polling(EE_i2c_st* i2csp, EE_UINT8 device, EE_UINT8 address, EE_UINT8 *data, int len);		
int EE_hal_i2c_write_buffer_irq(EE_i2c_st* i2csp, EE_UINT8 device, EE_UINT8 address, EE_UINT8 *data, int len);		

#else

#define EE_I2C_BASE_ADD(uc) cat2(uc, _BASE_ADDRESS)

int EE_hal_i2c_config(OCI2CMDev_t* i2cc, int baudrate, int setttings);									
int EE_hal_i2c_set_mode(OCI2CMDev_t* i2cc, int mode);																										
int EE_hal_i2c_disable(OCI2CMDev_t* i2cc);																
int EE_hal_i2c_enable(OCI2CMDev_t* i2cc);																
int EE_hal_i2c_start(OCI2CMDev_t* i2cc);																	
int EE_hal_i2c_stop(OCI2CMDev_t* i2cc);																			
int EE_hal_i2c_write_byte_polling(OCI2CMDev_t* i2cc, EE_UINT8 device, EE_UINT8 address, EE_UINT8 data);	
int EE_hal_i2c_read_byte_polling(OCI2CMDev_t* i2cc, EE_UINT8 device, EE_UINT8 address, EE_UINT8 *data);
int EE_hal_i2c_read_buffer_polling(OCI2CMDev_t* i2cc, EE_UINT8 device, EE_UINT8 address, EE_UINT8 *data, int len);		
int EE_hal_i2c_write_buffer_polling(OCI2CMDev_t* i2cc, EE_UINT8 device, EE_UINT8 address, EE_UINT8 *data, int len);	

#endif
							
/*
*/
void EE_i2c_common_handler(int level);																	

/* Macro for vectors (buffers) name generation */
#define EE_I2C_VETRX_NAME(lc) cat3(ee_, lc, _isr_rxvet)
#define EE_I2C_VETTX_NAME(lc) cat3(ee_, lc, _isr_txvet)

/* Macro for vectors (buffers) definition */  
#define DEFINE_VET_I2C(uc, lc) \
EE_UINT8 EE_I2C_VETRX_NAME(lc)[EE_I2C_BUFSIZE]; \
EE_UINT8 EE_I2C_VETTX_NAME(lc)[EE_I2C_BUFSIZE];  

/* Macros for User functions (API) */  
#ifdef __USE_I2C_IRQ__

#define DECLARE_FUNC_I2C(uc, lc) \
__INLINE__ int __ALWAYS_INLINE__ cat3(EE_, lc, _config)(int baudrate,int settings){ \
	return EE_hal_i2c_config(& EE_I2C_ST_NAME(lc), baudrate, settings); } \
__INLINE__ int __ALWAYS_INLINE__ cat3(EE_, lc, _set_mode)(int mode){ \
	return EE_hal_i2c_set_mode(& EE_I2C_ST_NAME(lc), mode); } \
__INLINE__ int __ALWAYS_INLINE__ cat3(EE_, lc, _set_rx_callback)(EE_ISR_callback rxcbk){ \
	return EE_hal_i2c_set_rx_callback(& EE_I2C_ST_NAME(lc), rxcbk); } \
__INLINE__ int __ALWAYS_INLINE__ cat3(EE_, lc, _set_tx_callback)(EE_ISR_callback txcbk){ \
	return EE_hal_i2c_set_tx_callback(& EE_I2C_ST_NAME(lc), txcbk); } \
__INLINE__ int __ALWAYS_INLINE__ cat3(EE_, lc, _write_byte)(EE_UINT8 device, EE_UINT8 address, EE_UINT8 data){ \
	int ret; \
	if(EE_i2c_tx_polling(EE_I2C_ST_NAME(lc).mode))\
		ret = EE_hal_i2c_write_byte_polling(& EE_I2C_ST_NAME(lc), device, address, data); } \
	else \
		ret = EE_hal_i2c_write_byte_irq(& EE_I2C_ST_NAME(lc), device, address, data); } \
	return ret; } \
__INLINE__ int __ALWAYS_INLINE__ cat3(EE_, lc, _read_byte)(EE_UINT8 device, EE_UINT8 address, EE_UINT8 *data){ \
	int ret; \
	if(EE_i2c_rx_polling(EE_I2C_ST_NAME(lc).mode))\
		ret = EE_hal_i2c_read_byte_polling(& EE_I2C_ST_NAME(lc), device, address, data); } \
	else \
		ret = EE_hal_i2c_read_byte_irq(& EE_I2C_ST_NAME(lc), device, address, data); } \
	return ret; } \
__INLINE__ int __ALWAYS_INLINE__ cat3(EE_, lc, _write_buffer)(EE_UINT8 device, EE_UINT8 address, EE_UINT8 *vet, int len){ \
	int ret; \
	if(EE_i2c_tx_polling(EE_I2C_ST_NAME(lc).mode))\
		ret = EE_hal_i2c_write_buffer_polling(& EE_I2C_ST_NAME(lc), device, address, vet, len); } \
	else \
		ret = EE_hal_i2c_write_buffer_irq(& EE_I2C_ST_NAME(lc), device, address, vet, len); } \
	return ret; } \
__INLINE__ int __ALWAYS_INLINE__ cat3(EE_, lc, _read_buffer)(EE_UINT8 device, EE_UINT8 address, EE_UINT8 *vet, int len){ \
	int ret; \
	if(EE_i2c_rx_polling(EE_I2C_ST_NAME(lc).mode))\
		ret = EE_hal_i2c_read_buffer_polling(& EE_I2C_ST_NAME(lc), device, address, vet, len); } \
	else \
		ret = EE_hal_i2c_read_buffer_irq(& EE_I2C_ST_NAME(lc), device, address, vet, len); } \
	return ret; } \
__INLINE__ int __ALWAYS_INLINE__ cat3(EE_, lc, _enable_IRQ)(void){ \
	return EE_hal_i2c_enable_IRQ(& EE_I2C_ST_NAME(lc)); } \
__INLINE__ int __ALWAYS_INLINE__ cat3(EE_, lc, _disable_IRQ)(void){ \
	return EE_hal_i2c_disable_IRQ(& EE_I2C_ST_NAME(lc)); } \
__INLINE__ int __ALWAYS_INLINE__ cat3(EE_, lc, _disable)(void){ \
	return EE_hal_i2c_disable(& EE_I2C_ST_NAME(lc)); } \
__INLINE__ int __ALWAYS_INLINE__ cat3(EE_, lc, _enable)(void){ \
	return EE_hal_i2c_enable(& EE_I2C_ST_NAME(lc)); } \
__INLINE__ int __ALWAYS_INLINE__ cat3(EE_, lc, _stop)(void){ \
	return EE_hal_i2c_stop(& EE_I2C_ST_NAME(lc)); } \
__INLINE__ int __ALWAYS_INLINE__ cat3(EE_, lc, _start)(void){ \
	return EE_hal_i2c_start(& EE_I2C_ST_NAME(lc)); } \
__INLINE__ int __ALWAYS_INLINE__ cat3(EE_, lc, _return_error)(void){ \
	return EE_hal_i2c_return_error(& EE_I2C_ST_NAME(lc)); }
	
#else

#define DECLARE_FUNC_I2C(uc, lc) \
__INLINE__ int __ALWAYS_INLINE__ cat3(EE_, lc, _config)(int baudrate,int settings){ \
	return EE_hal_i2c_config(& EE_I2C_BASE_ADD(uc), baudrate, settings); } \
__INLINE__ int __ALWAYS_INLINE__ cat3(EE_, lc, _set_mode)(int mode){ \
	return EE_hal_i2c_set_mode(& EE_I2C_BASE_ADD(uc), mode); } \
__INLINE__ int __ALWAYS_INLINE__ cat3(EE_, lc, _set_rx_callback)(EE_ISR_callback rxcbk){ \
	return EE_hal_i2c_set_rx_callback(& EE_I2C_BASE_ADD(uc), rxcbk); } \
__INLINE__ int __ALWAYS_INLINE__ cat3(EE_, lc, _set_tx_callback)(EE_ISR_callback txcbk){ \
	return EE_hal_i2c_set_tx_callback(& EE_I2C_BASE_ADD(uc), txcbk); } \
__INLINE__ int __ALWAYS_INLINE__ cat3(EE_, lc, _write_byte)(EE_UINT8 device, EE_UINT8 address, EE_UINT8 data){ \
	return EE_hal_i2c_write_byte_polling(& EE_I2C_BASE_ADD(uc), device, address, data); } \
__INLINE__ int __ALWAYS_INLINE__ cat3(EE_, lc, _read_byte)(EE_UINT8 device, EE_UINT8 address, EE_UINT8 *data){ \
	return EE_hal_i2c_read_byte_polling(& EE_I2C_BASE_ADD(uc), device, address, data); } \
__INLINE__ int __ALWAYS_INLINE__ cat3(EE_, lc, _write_buffer)(EE_UINT8 device, EE_UINT8 address, EE_UINT8 *vet, int len){ \
	return EE_hal_i2c_write_buffer_polling(& EE_I2C_BASE_ADD(uc), device, address, vet, len); } \
__INLINE__ int __ALWAYS_INLINE__ cat3(EE_, lc, _read_buffer)(EE_UINT8 device, EE_UINT8 address, EE_UINT8 *vet, int len){ \
	return EE_hal_i2c_read_buffer_polling(& EE_I2C_BASE_ADD(uc), device, address, vet, len); } \
__INLINE__ int __ALWAYS_INLINE__ cat3(EE_, lc, _enable_IRQ)(void){ \
	return EE_hal_i2c_enable_IRQ(& EE_I2C_BASE_ADD(uc)); } \
__INLINE__ int __ALWAYS_INLINE__ cat3(EE_, lc, _disable_IRQ)(void){ \
	return EE_hal_i2c_disable_IRQ(& EE_I2C_BASE_ADD(uc)); } \
__INLINE__ int __ALWAYS_INLINE__ cat3(EE_, lc, _disable)(void){ \
	return EE_hal_i2c_disable(& EE_I2C_BASE_ADD(uc)); } \
__INLINE__ int __ALWAYS_INLINE__ cat3(EE_, lc, _enable)(void){ \
	return EE_hal_i2c_enable(& EE_I2C_BASE_ADD(uc)); } \
__INLINE__ int __ALWAYS_INLINE__ cat3(EE_, lc, _stop)(void){ \
	return EE_hal_i2c_stop(& EE_I2C_BASE_ADD(uc)); } \
__INLINE__ int __ALWAYS_INLINE__ cat3(EE_, lc, _start)(void){ \
	return EE_hal_i2c_start(& EE_I2C_BASE_ADD(uc)); } \
__INLINE__ int __ALWAYS_INLINE__ cat3(EE_, lc, _return_error)(void){ \
	return EE_hal_i2c_return_error(& EE_I2C_BASE_ADD(uc)); }
		
#endif //#ifdef __USE_I2C_IRQ__


/* User functions (API): */  
#ifdef EE_I2C1_NAME_UC
#ifdef __USE_I2C_IRQ__
DECLARE_STRUCT_I2C(EE_I2C1_NAME_UC, EE_I2C1_NAME_LC)
#endif	//#ifdef __USE_I2C_IRQ__
DECLARE_FUNC_I2C(EE_I2C1_NAME_UC, EE_I2C1_NAME_LC)
#endif	//#ifdef EE_I2C1_NAME_UC

#ifdef EE_I2C2_NAME_UC
#ifdef __USE_I2C_IRQ__
DECLARE_STRUCT_I2C(EE_I2C2_NAME_UC, EE_I2C2_NAME_LC)
#endif	//#ifdef __USE_I2C_IRQ__
DECLARE_FUNC_I2C(EE_I2C2_NAME_UC, EE_I2C2_NAME_LC)
#endif	//#ifdef EE_I2C2_NAME_UC


#ifdef __USE_I2C_IRQ__

/* Return the I2C structure for the componente associated with the given IRQ
 * level */
__DECLARE_INLINE__ EE_i2c_st *EE_get_i2c_st_from_level(int level);
#ifndef EE_I2C2_NAME_UC
/* If there is only one component of this kind, no test is done */
__INLINE__ EE_i2c_st * __ALWAYS_INLINE__ EE_get_i2c_st_from_level(int level)
{
    return & EE_I2C_ST_NAME(EE_I2C1_NAME_LC);
}
#else /* #ifndef EE_I2C2_NAME_UC */
__INLINE__ EE_i2c_st * __ALWAYS_INLINE__ EE_get_i2c_st_from_level(int level)
{
    if (level == EE_I2C_IRQ_NAME(EE_I2C1_NAME_UC))
        return & EE_I2C_ST_NAME(EE_I2C1_NAME_LC);
    else
        return & EE_I2C_ST_NAME(EE_I2C2_NAME_LC);
}
#endif /* #ifndef EE_I2C2_NAME_UC */

#endif	//#ifdef __USE_I2C_IRQ__





#endif // #ifdef __USE_I2C__

#endif //__EE_I2C_INTERNAL_H__
