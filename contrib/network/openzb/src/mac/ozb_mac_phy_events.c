/* TODO: this should go, eventually with a different name, in the makefile 
	 rules.
*/
#ifndef OZB_USE_ONLY_802154_PHY	

#include <mac/ozb_mac_internal.h>

#ifdef OZB_DEBUG
#include <util/ozb_debug.h>
#include <string.h>
#include <stdio.h> //TODO: REMOVE together with the sprintf() !!!!!
#endif

int8_t ozb_PD_DATA_confirm(enum ozb_phy_code_t status)
{
	#ifdef OZB_DEBUG
	char s[100];
	char s1[30];
	ozb_debug_print_phycode(status, s1);
	sprintf(s, "PD_DATA_confirm(%s)", s1);
	ozb_debug_print(s);
	#endif
	return OZB_PHY_SUCCESS;
}
 
int8_t ozb_PD_DATA_indication(uint8_t psduLength, uint8_t *psdu, 
			      uint8_t ppduLinkQuality)
{
	#ifdef OZB_DEBUG
	char s[100];
	sprintf(s, "PD_DATA_indication(len=%u,*p=%u,lqi=%u)",
		psduLength, (uint16_t) psdu, ppduLinkQuality);
	ozb_debug_print(s);
	#endif
	return OZB_PHY_SUCCESS;
}
 

int8_t ozb_PLME_CCA_confirm(enum ozb_phy_code_t status)
{
	#ifdef OZB_DEBUG
	char s[100];
	char s1[30];
	ozb_debug_print_phycode(status, s1);
	sprintf(s, "PLME_CCA_confirm(%s)", s1);
	ozb_debug_print(s);
	#endif
	return OZB_PHY_SUCCESS;
}

int8_t ozb_PLME_ED_confirm(enum ozb_phy_code_t status, uint8_t EnergyLevel)
{
	#ifdef OZB_DEBUG
	char s[100];
	char s1[30];
	ozb_debug_print_phycode(status, s1);
	sprintf(s, "PLME_ED_confirm(%s, el=%u)", s1, EnergyLevel);
	ozb_debug_print(s);
	#endif
	return OZB_PHY_SUCCESS;
}

int8_t ozb_PLME_GET_confirm(enum ozb_phy_code_t status, 
			    enum ozb_phy_pib_id_t PIBAttribute, 
			    void *PIBAttributeValue)
{
	#ifdef OZB_DEBUG
	uint8_t value = *((uint8_t*)PIBAttributeValue);
	char s[100];
	char s1[30];
	ozb_debug_print_phycode(status, s1);
	sprintf(s, "PLME_GET_confirm(%s, a=%u, v=%u)", s1, PIBAttribute, value);
	ozb_debug_print(s);
	#endif
	return OZB_PHY_SUCCESS;
}

int8_t ozb_PLME_SET_TRX_STATE_confirm(enum ozb_phy_code_t status)
{
	#ifdef OZB_DEBUG
	char s[100];
	char s1[30];
	ozb_debug_print_phycode(status, s1);
	sprintf(s, "PLME_SET_TRX_STATE_confirm(%s)", s1);
	ozb_debug_print(s);
	#endif
	return OZB_PHY_SUCCESS;
}

int8_t ozb_PLME_SET_confirm(enum ozb_phy_code_t status, 
			    enum ozb_phy_pib_id_t PIBAttribute)
{
	#ifdef OZB_DEBUG
	char s[100];
	char s1[30];
	ozb_debug_print_phycode(status, s1);
	sprintf(s, "PLME_SET_confirm(%s, a=%u)", s1, PIBAttribute);
	ozb_debug_print(s);
	#endif
	return OZB_PHY_SUCCESS;
}

#endif /* OZB_USE_ONLY_802154_PHY */
