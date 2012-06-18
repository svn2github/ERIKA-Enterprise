/* ###*B*###
 * ERIKA Enterprise - a tiny RTOS for small microcontrollers
 *
 * Copyright (C) 2002-2011  Evidence Srl
 *
 * This file is part of ERIKA Enterprise.
 *
 * ERIKA Enterprise is free software; you can redistribute it
 * and/or modify it under the terms of the GNU General Public License
 * version 2 as published by the Free Software Foundation,
 * (with a special exception described below).
 *
 * Linking this code statically or dynamically with other modules is
 * making a combined work based on this code.  Thus, the terms and
 * conditions of the GNU General Public License cover the whole
 * combination.
 *
 * As a special exception, the copyright holders of this library give you
 * permission to link this code with independent modules to produce an
 * executable, regardless of the license terms of these independent
 * modules, and to copy and distribute the resulting executable under
 * terms of your choice, provided that you also meet, for each linked
 * independent module, the terms and conditions of the license of that
 * module.  An independent module is a module which is not derived from
 * or based on this library.  If you modify this code, you may extend
 * this exception to your version of the code, but you are not
 * obligated to do so.  If you do not wish to do so, delete this
 * exception statement from your version.
 *
 * ERIKA Enterprise is distributed in the hope that it will be
 * useful, but WITHOUT ANY WARRANTY; without even the implied warranty
 * of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License version 2 for more details.
 *
 * You should have received a copy of the GNU General Public License
 * version 2 along with ERIKA Enterprise; if not, write to the
 * Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
 * Boston, MA 02110-1301 USA.
 * ###*E*### */

/*
 * GPT367:	Gpt.c Module source file.
 *
 * AUTOSAR-"like" GPT Driver Source File.
 *
 * Author:  2011,  Giuseppe Serano
 */

/*
 * GPT293:	Gpt.c shall include Gpt.h.
 *
 * Comment: Gpt.c has implicit access to the Gpt_Cfg.h through the Gpt.h file.
 */
#include "Gpt.h"

/* 
 * GPT256:	The GPT module shall perform Inter Module Checks to avoid
 * 		integration of incompatible files. The imported included files
 * 		shall be checked by preprocessing directives. (BSW004)
 *
 * The following version numbers shall be verified:
 * - <MODULENAME>_AR_RELEASE_MAJOR_VERSION
 * - <MODULENAME>_AR_RELEASE_MINOR_VERSION
 * Where <MODULENAME> is the module abbreviation of the other (external) modules
 * which provide header files included by the GPT module.
 *
 * If the values are not identical to the expected values, an error shall be
 * reported.
 */
#define	GPT_AR_RELEASE_MAJOR_VERSION	4
#define	GPT_AR_RELEASE_MINOR_VERSION	0

#if !defined( GPT_AR_MAJOR_VERSION ) || \
    ( GPT_AR_MAJOR_VERSION != GPT_AR_RELEASE_MAJOR_VERSION )
#error	Gpt: version mismatch.
#endif

#include "ee.h"

/* Development error macros. */
#if ( GPT_DEV_ERROR_DETECT == STD_ON )

#include "Det.h"
#if defined(USE_DEM)
#include "Dem.h"
#endif

#define VALIDATE(_exp,_api,_err) \
  if( !(_exp) ) { \
    Det_ReportError(GPT_MODULE_ID,0,_api,_err); \
    return; \
  }

#define VALIDATE_IRQ(_exp,_api,_err,_flags) \
  if( !(_exp) ) { \
    Det_ReportError(GPT_MODULE_ID,0,_api,_err); \
    EE_hal_resumeIRQ(_flags); \
    return; \
  }

#define VALIDATE_W_RV(_exp,_api,_err,_rv) \
  if( !(_exp) ) { \
    Det_ReportError(GPT_MODULE_ID,0,_api,_err); \
    return (_rv); \
  }

#define VALIDATE_IRQ_W_RV(_exp,_api,_err,_rv,_flags) \
  if( !(_exp) ) { \
    Det_ReportError(GPT_MODULE_ID,0,_api,_err); \
    EE_hal_resumeIRQ(_flags); \
    return (_rv); \
  }

#else	/* GPT_DEV_ERROR_DETECT */

#define VALIDATE(_exp,_api,_err) \
  if( !(_exp) ) { \
    return; \
  }

#define VALIDATE_IRQ(_exp,_api,_err,_flags) \
  if( !(_exp) ) { \
    EE_hal_resumeIRQ(_flags); \
    return; \
  }

#define VALIDATE_W_RV(_exp,_api,_err,_rv) \
  if( !(_exp) ) { \
    return (_rv); \
  }

#define VALIDATE_IRQ_W_RV(_exp,_api,_err,_rv,_flags) \
  if( !(_exp) ) { \
    EE_hal_resumeIRQ(_flags); \
    return (_rv); \
  }

#endif	/* !GPT_DEV_ERROR_DETECT */

/*
 * Gpt Enable Channel
 *
 * param	Channel	Numeric ID of a GPT Channel.
 */
static void Gpt_EnableChannel(
  Gpt_ChannelType	Channel
)
{



}

#if ( GPT_DEINIT_API == STD_ON )
/*
 * Gpt Disable Channel
 *
 * param	Channel	Numeric ID of a GPT Channel.
 */
static void Gpt_DisableChannel(
  Gpt_ChannelType	Channel
)
{

  
}

/*
 * Gpt Reset Channel
 *
 * param	Channel	Numeric ID of a GPT Channel.
 */
static void Gpt_ResetChannel(
  Gpt_ChannelType	Channel
)
{

  

}
#endif

/*
 * Gpt Channel Initialization.
 */
static void Gpt_InitGptChannel(
  const Gpt_ChannelConfigType *	ConfigPtr
)
{

  

}

/*
 * Gpt Channel De-Initialization.
 */
#if ( GPT_DEINIT_API == STD_ON )
static void Gpt_DeInitGptChannel(
  const Gpt_ChannelConfigType *	ConfigPtr
)
{

}
#endif

/*
 * Gpt_Init implementation.
 */
void Gpt_Init(
  const Gpt_ConfigType *	ConfigPtr
)
{


}

#if ( GPT_DEINIT_API == STD_ON )
/*
 * Gpt_DeInit implementation.
 */
void Gpt_DeInit(
  void
)
{


}
#endif

#if ( \
  ( GPT_TIME_ELAPSED_API == STD_ON ) || ( GPT_TIME_REMAINING_API == STD_ON ) \
)
/*
 * Gpt_GetHWTimeRemaining implementation.
 */
static Gpt_ValueType Gpt_GetHWTimeRemaining(
  Gpt_ChannelType	Channel
)
{


}
#endif	/* 
	 * ( GPT_TIME_ELAPSED_API == STD_ON ) ||
	 * ( GPT_TIME_REMAINING_API == STD_ON )
	 */

#if ( GPT_TIME_ELAPSED_API == STD_ON )
/*
 * Gpt_GetHWStartTime implementation.
 */
static Gpt_ValueType Gpt_GetHWStartTime(
  Gpt_ChannelType	Channel
)
{

}

/*
 * Gpt_GetTimeElapsed implementation.
 */
Gpt_ValueType Gpt_GetTimeElapsed(
  Gpt_ChannelType	Channel
)
{

}
#endif

#if ( GPT_TIME_REMAINING_API == STD_ON )
/*
 * Gpt_GetTimeRemainig implementation.
 */
Gpt_ValueType Gpt_GetTimeRemaining(
  Gpt_ChannelType	Channel
)
{

}
#endif

/*
 * Gpt_StartTimer implementation.
 */
void Gpt_StartTimer(
  Gpt_ChannelType	Channel,
  Gpt_ValueType		Value
)
{


}

/*
 * Gpt_StopTimer implementation.
 */
void Gpt_StopTimer(
  Gpt_ChannelType	Channel
)
{

}

#if ( GPT_ENABLE_DISABLE_NOTIFICATION_API == STD_ON )
/*
 * Gpt_EnableNotification implementation.
 */
void Gpt_EnableNotification(
  Gpt_ChannelType	Channel
)
{

}

/*
 * Gpt_DisableNotification implementation.
 */
void Gpt_DisableNotification(
  Gpt_ChannelType	Channel
)
{

}
#endif

#if ( \
  ( GPT_REPORT_WAKEUP_SOURCE == STD_ON ) && \
  ( GPT_WAKEUP_FUNCTIONALITY_API == STD_ON ) \
)
/*
 * Gpt_SetMode implementation.
 */
void Gpt_SetMode(
  Gpt_ModeType	Mode
)
{

}

/*
 * Gpt_DisableWakeup implementation.
 */
void Gpt_DisableWakeup(
  Gpt_ChannelType	Channel
)
{


}

/*
 * Gpt_EnableWakeup implementation.
 */
void Gpt_EnableWakeup(
  Gpt_ChannelType	Channel
)
{

}

/*
 * Gpt_CheckWakeup implementation.
 */
void Gpt_CheckWakeup(
  EcuM_WakeupSourceType	WakeupSource
)
{


  EE_hal_resumeIRQ(flags);

}
#endif

#if ( GPT_CHANNEL_WAKEUP_FUNCTIONALITY_API == STD_ON )
/*
 * Gpt_GoToSleep implementation.
 */
Std_ReturnType Gpt_GoToSleep(
  Gpt_ChannelType	Channel
)
{

 

}

/*
 * Gpt_Wakeup implementation.
 */
Std_ReturnType Gpt_Wakeup(
  Gpt_ChannelType	Channel
)
{
 
}

/*
 * Gpt_GetStatus implementation.
 */
Gpt_StatusType Gpt_GetStatus(
  Gpt_ChannelType	Channel
)
{

  

}
#endif
