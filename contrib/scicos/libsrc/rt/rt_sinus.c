#include "ee.h"

#include "machine.h"
#include "scicos_block4.h"

#include <math.h>

/* Declaration of externalad defined functions */
extern double       get_scicos_period(void);

/* block->rpar[x]         */
/* 0 : Amplitude      : A */
/* 1 : Frequency (Hz) : F */
/* 2 : phase (rad)    : P */
/* 3 : DC bias        : B */
/* 4 : act.delay(sec) : D */

# define A  (block->rpar[0])
# define F  (block->rpar[1])
# define P  (block->rpar[2])
# define B  (block->rpar[3])
# define D  (block->rpar[4])

/* Pseudocode 

   EE_UINT16    tick   : icremented by one each isr call
   double scicos_time  : isr period (sec)

   double phase        : (radian)

init 

   SP_sec   = 1 / F ; period of sinus (sec)
   SP_ticks = (EE_UINT16) (SP_sec/scicos_time) 
   
isr

   w  = tick % SP_ticks
   pt = (double) (w * scicos_time)
   phase = fmod(2*pi*F*(pt - D) - P,(2*pi))
   y = A*sin(phase)+B

*/

/* Application tick duration */
static double scicos_period;
/* Sine phase increment for each tick */
static double tick_phase_increment;
/* Ticks/period sine */
static EE_UINT32 period_ticks;

static void init(scicos_block *block)
{
    /* Scicos clock period (seconds) */    
    scicos_period = get_scicos_period();
    /* phase increment for each tick (Frequency (Hz) * tick length) */
    tick_phase_increment = F * scicos_period;
    
    /* N° ticks x period => [(1 / F) -> period (sec.)] * [(1 / scicos_period) -> n° ticks per second] => 
		1 / tick_phase_increment */
    /* N.B trick to use roundig not truncation */
    period_ticks = (EE_UINT32) ((1.0 / tick_phase_increment) + 0.5);
    
    double * y = block->outptr[0];
    y[0]=0.0;
}

static void inout(scicos_block *block)
{
    /* Pi constant */
    static const double pi = 3.1415927;
    
    /* Application actual time */
    double t = get_scicos_time();
    /* Block output pointer */
    double * y = block->outptr[0];

    if (t < D) {
        /* Activation delay time D */
        y[0] = 0.0;
    } else {
        /* internal counter (put equal to 0 at (period_ticks - 1)) */
        static EE_UINT32 tick = 0;
        /* sine phase */
        double phase = 2*pi*tick*tick_phase_increment - P;
        
        y[0] = A*sin(phase) + B ;
        
        /* incremente tic counter and reset it at the counter end */
        if(++tick == period_ticks)
            tick = 0;
    }
}

static void end(scicos_block *block)
{
    double * y = block->outptr[0];
    y[0]=0.0;
}

void rt_sinus(scicos_block *block,int flag)
{
    if (flag == 1){          /* set output */
        inout(block);
    } else if (flag == 5){     /* termination */ 
        end(block);
    } else if (flag == 4){    /* initialisation */
        init(block);
    }
}


