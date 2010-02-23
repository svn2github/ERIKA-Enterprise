#ifndef __EE_TIMER_INTERNAL_H__
#define __EE_TIMER_INTERNAL_H__

#include <eecfg.h>

/*************************************************************************
 Timers
 *************************************************************************/
 
#ifdef __USE_TIMER__

#include "MicoTimer.h"					// to use LATTICE data structures.

typedef struct {
    EE_UINT32 base;
    EE_ISR_callback cbk;
} EE_timer_st;

/* Return the Timer structure for the componente associated with the given IRQ
 * level */
__DECLARE_INLINE__ EE_timer_st *EE_get_timer_st_from_level(int level);


#ifndef EE_TIMER2_NAME_UC
/* If there is only one component of this kind, no test is done */
__INLINE__ EE_timer_st * __ALWAYS_INLINE__ EE_get_timer_st_from_level(int level)
{
    return & EE_TIMER_ST_NAME(EE_TIMER1_NAME_LC);
}
#else /* #ifndef EE_TIMER_NAME2_UC */
__INLINE__ EE_timer_st * __ALWAYS_INLINE__ EE_get_timer_st_from_level(int level)
{
    switch (level) {
    default:
        return & EE_TIMER_ST_NAME(EE_TIMER1_NAME_LC);
#ifdef EE_TIMER2_NAME_UC
    case EE_TIMER_IRQ_NAME(EE_TIMER2_NAME_UC):
        return & EE_TIMER_ST_NAME(EE_TIMER2_NAME_LC);
#endif
#ifdef EE_TIMER3_NAME_UC
    case EE_TIMER_IRQ_NAME(EE_TIMER3_NAME_UC):
        return & EE_TIMER_ST_NAME(EE_TIMER3_NAME_LC);
#endif
#ifdef EE_TIMER4_NAME_UC
    case EE_TIMER_IRQ_NAME(EE_TIMER4_NAME_UC):
        return & EE_TIMER_ST_NAME(EE_TIMER4_NAME_LC);
#endif
    }
}
#endif /* #ifndef EE_TIMER_NAME2_UC */

#endif //#ifdef __USE_TIMER__

#endif //__EE_TIMER_INTERNAL_H__
