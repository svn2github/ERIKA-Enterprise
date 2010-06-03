/*
  Name: ee_gpio.c
  Copyright: Evidence Srl
  Author: Dario Di Stefano
  Date: 29/03/10 18.23
  Description: GPIO library functions.
*/

#include "mcu/mico32/inc/ee_gpio.h"


/******************************************************************************/
/*                             Global Variables                               */
/******************************************************************************/
#ifdef EE_GPIO1_NAME_UC
DEFINE_STRUCT_GPIO(EE_GPIO1_NAME_UC, EE_GPIO1_NAME_LC)
#endif

#ifdef EE_GPIO2_NAME_UC
DEFINE_STRUCT_GPIO(EE_GPIO2_NAME_UC, EE_GPIO2_NAME_LC)
#endif

#ifdef EE_GPIO3_NAME_UC
DEFINE_STRUCT_GPIO(EE_GPIO3_NAME_UC, EE_GPIO3_NAME_LC)
#endif

#ifdef EE_GPIO4_NAME_UC
DEFINE_STRUCT_GPIO(EE_GPIO4_NAME_UC, EE_GPIO4_NAME_LC)
#endif


/******************************************************************************/
/*                              ISRs                                          */
/******************************************************************************/
#if defined(__USE_GPIO_IRQ__) || defined(__USE_ETHERNET_IRQ__) || defined(__USE_ZIGBEE_IRQ__)
void EE_gpio_common_handler(int level)
{
    EE_gpio_st *gpio_sp = EE_get_gpio_st_from_level(level);
    MicoGPIO_t *gp = gpio_sp->base; 
	
    /* Save edgeCpature register */
    gpio_sp->flag = EE_hal_gpio_read_edgeCapture(gp);
    /* Clear edgeCpature register */
    EE_hal_gpio_write_edgeCapture(gp, ~gpio_sp->flag);
    /* Call user callback */
    if( gpio_sp->cbk != EE_NULL_CBK )
        gpio_sp->cbk();

    return;	
}
#endif
