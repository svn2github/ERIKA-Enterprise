#ifndef __ozb_ieee802154_h__
#define __ozb_ieee802154_h__

#if 	defined OZB_USE_ONLY_802154_MAC
#include <mac/ozb_mac.h>
#elif 	defined OZB_USE_SIMPLE_802154
#include <net/ozb_simple154.h>
#elif
#error "OZB IEEE 802.15.4: A valid API access method must be declared"
#endif

#endif /* Header Protection */
