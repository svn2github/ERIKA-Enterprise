
int8_t ozb_mac_init(void) 
{
	if (ozb_phy_init() < 0)
		return -OZB_MAC_PHY_INIT_ERROR;

	#ifdef OZB_DEBUG
	if (ozb_debug_init() < 0)
		return -OZB_MAC_DEBUG_INIT_ERROR;
	#endif

	return OZB_MAC_SUCCESS;
}
