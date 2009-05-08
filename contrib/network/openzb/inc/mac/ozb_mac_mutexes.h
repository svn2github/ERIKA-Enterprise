#ifndef __ozb_mac_mutexes_h__
#define __ozb_mac_mutexes_h__

#include <osal/ozb_osal.h>

#define OZB_PHY_IMPORT_MAC_MUTEXES(task_id)		\
	OZB_OSAL_MUTEX(MAC_RX_BEACON_MUTEX, task_id);	\
	OZB_OSAL_MUTEX(MAC_RX_DATA_MUTEX, task_id);	\
	OZB_OSAL_MUTEX(MAC_RX_COMMAND_MUTEX, task_id);	\

#endif /* Header Protection */
