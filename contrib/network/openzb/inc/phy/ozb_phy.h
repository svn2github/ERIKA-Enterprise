/**
* @file phy.h
* @brief IEEE 802.15.4 PHY Layer Definition
* @author Christian Nastasi
* @date 2009-03-22
*
* This file is the entry point for the IEEE 802.15.4 PHY primitives.
*/
#ifndef __ozb_phy_h__
#define __ozb_phy_h__

#include <phy/ozb_phy_const.h>	/* Include the PHY constants definition. */
#include <phy/ozb_phy_types.h>	/* Include the PHY types. */
#include <phy/ozb_phy_pd.h>	/* Include the PD-SAP definition. */
#include <phy/ozb_phy_plme.h>	/* Include the PLME-SAP definition. */

int8_t ozb_phy_init(void);

#endif /* Header Protection */
