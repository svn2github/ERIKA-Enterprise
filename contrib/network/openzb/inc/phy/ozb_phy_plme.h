/**
* @file phy_plme.h
* @brief IEEE 802.15.4 PLME-SAP Primitives
* @author Christian Nastasi
* @date 2009-03-19
*
* The file contains the declaration of the PLME service primitives
* of the IEEE 802.15.4 standard.
* The definition of the \b request funtions takes place in the phy subtree,
* while the \b confirm ones are defined in the mac subree.
* \todo Make a specific reference to the files that implement these primitives.
*/
#ifndef __ozb_phy_plme_h__
#define __ozb_phy_plme_h__

#include <phy/ozb_phy_types.h>

int8_t ozb_PLME_CCA_request(void);
int8_t ozb_PLME_CCA_confirm(enum ozb_phy_code_t status);

int8_t ozb_PLME_ED_request(void);
int8_t ozb_PLME_ED_confirm(enum ozb_phy_code_t status, uint8_t EnergyLevel);

int8_t ozb_PLME_GET_request(enum ozb_phy_pib_id_t PIBAttribute);
int8_t ozb_PLME_GET_confirm(enum ozb_phy_code_t status,
			    enum ozb_phy_pib_id_t PIBAttribute,
			    void *PIBAttributeValue);

int8_t ozb_PLME_SET_TRX_STATE_request(enum ozb_phy_code_t state);
int8_t ozb_PLME_SET_TRX_STATE_confirm(enum ozb_phy_code_t status);

int8_t ozb_PLME_SET_request(enum ozb_phy_pib_id_t PIBAttribute,
			    void *PIBAttributeValue);
int8_t ozb_PLME_SET_confirm(enum ozb_phy_code_t status,
			    enum ozb_phy_pib_id_t PIBAttribute);

#endif /* Header Protection */
