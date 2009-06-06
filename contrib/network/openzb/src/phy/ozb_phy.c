#include <phy/ozb_phy_internal.h>
#include <mac/ozb_mac_mutexes.h>
#include <util/ozb_debug.h>
#include <kal/ozb_kal.h>
#include <hal/ozb_radio.h>
#ifdef OZB_DEBUG_LOG
#include <stdio.h> //TODO: REMOVE together with the sprintf() !!!!!
#endif

/* chris: if the PLME and PD code is not so much their implementation
	can be done just in this file. This helps to hide some global
	variable with the static keyword, otherwise we can try to limit the
	scope using the phy_internal header.
*/

/******************************************************************************/
/*                          PHY Layer Private Data                            */
/******************************************************************************/
static struct ozb_phy_pib_t ozb_phy_pib = {
	OZB_RADIO_CURRENT_CHANNEL_INIT,
	OZB_RADIO_CHANNEL_SUPPORTED_INIT,
	OZB_RADIO_TRANSMIT_POWER_INIT,
	OZB_RADIO_CCA_MODE_INIT,
	OZB_RADIO_CURRENT_PAGE_INIT,
	OZB_RADIO_MAX_FRAME_DURATION_INIT,
	OZB_RADIO_SHR_DURATION_INIT,
	OZB_RADIO_SYMBOLS_PER_OCTET_INIT
};

static struct {
	unsigned radio : 4;
	unsigned initialized : 1;
	unsigned reserved : 3;
} phy_status = {OZB_PHY_TRX_OFF, 0, 0};

/******************************************************************************/
/*                          PHY Layer TASK and ISR                            */
/******************************************************************************/
OZB_KAL_TASK_ASYNC(PHY_READ_DISPATCHER, 30);

OZB_PHY_IMPORT_MAC_MUTEXES(PHY_READ_DISPATCHER); /* TODO: write notes!! */

static void phy_read_dispatcher(void)
{
	uint8_t rssi, lqi;
	uint8_t buf[OZB_RADIO_RX_BUFFER_SIZE];
	int8_t len = 0;

	#ifdef OZB_DEBUG_LOG
	/* ozb_debug_print("OZB_TASK: PHY_READ_DISPATCHER Activated!"); */
	#endif
	/* chris: FIXME: maybe the error was in that part! */
	/* chris: TODO: this part has been copied by the old ieee802154 stack.
			maybe this is too dependent on the cc2420? can we
			abstract something?
	*/
	len = ozb_radio_get_msg(buf);
	if(len < 13)
		return; /* chris: TODO: - Make something: notify to upper layer
					(raise an error) or ignore
					(return immediately)
					- Check if the condition < 13 is ok (now
					it is because of the minimal packet
					size);
			*/
	len += 1; 	/* chris: TODO: Lenght doe's not consider the first
					byte (which is length itself)
					so add it! Is this correct????
			*/
	if (!(buf[len - 1] & 0x80))
		return;	/* chris: TODO: - Make something: notify to upper layer
					(raise an error) or ignore
					(return immediately)
			*/
	/* The last two bytes in the buffer are the RSSI value
	* and the CRC value respectively. They are not part
	* of the message (payload), then we can discard them.
	* For further information see the CC2420 datasheet
	*/
	lqi = buf[len - 1] & 0x7F;
	rssi= 255 - buf[len - 2];
	len -= 2;
	ozb_PD_DATA_indication((uint8_t) len - 1, buf + 1, lqi);
}

static void phy_read_isr(void)
{
	#ifdef OZB_DEBUG_LOG
	//ozb_debug_print("!-> BCN <-!");
	#endif
	ozb_kal_activate(PHY_READ_DISPATCHER);
}

/******************************************************************************/
/*                      PHY Layer General Functions                           */
/******************************************************************************/
int8_t ozb_phy_init(void)
{
	/* TODO: Check if already initialized do something special?? */

	#ifdef OZB_DEBUG_LOG
	ozb_debug_print("Initializing PHY...");
	#endif
	if (ozb_kal_init(0) < 0)
		return -OZB_PHY_ERR_KAL_ERROR;
	if (ozb_kal_set_body(PHY_READ_DISPATCHER, phy_read_dispatcher) < 0)
		return -OZB_PHY_ERR_KAL_ERROR;
	#ifdef OZB_DEBUG_LOG
	ozb_debug_print("KAL init OK!");
	#endif
	if (ozb_radio_set_rx_callback(phy_read_isr) < 0)
		return -OZB_PHY_ERR_HW_FAILURE;
	if (ozb_radio_init() < 0)
		return -OZB_PHY_ERR_HW_FAILURE;
	#ifdef OZB_DEBUG_LOG
	ozb_debug_print("Radio init OK!");
	#endif
	/*if (ozb_radio_set_rx() < 0)
		return -OZB_PHY_ERR_HW_FAILURE;
	phy_status.radio = OZB_PHY_RX_ON;
	*/
	phy_status.radio = OZB_PHY_TRX_OFF;
	/* TODO: initialize the PLME and PD */
	phy_status.initialized = 1;
	return OZB_PHY_ERR_NONE;
}

/* chris: TODO: do we handle other error condition? :
		- the psduLength > 127
		- ozb_radio failure
*/



/******************************************************************************/
/*                      PD-SAP Definition (PHY SIDE)                          */
/******************************************************************************/
int8_t ozb_PD_DATA_request(uint8_t psduLength, uint8_t *psdu)
{
	enum ozb_phy_code_t status = OZB_PHY_SUCCESS;
	#ifdef OZB_DEBUG_LOG
	char s[100];
	sprintf(s, "PD_DATA_request(len=%u, *p=%u)", psduLength,(uint16_t)psdu);
	ozb_debug_print(s);
	#endif

	if (!phy_status.initialized)
		return -OZB_PHY_ERR_NOT_INITIALIZED;
	switch (phy_status.radio) {
	case OZB_PHY_TRX_OFF:
		status = OZB_PHY_TRX_OFF;
		break;
	case OZB_PHY_RX_ON:
		status = OZB_PHY_RX_ON;
		break;
	case OZB_PHY_BUSY_TX:
		status = OZB_PHY_BUSY_TX;
		break;
	case OZB_PHY_TX_ON:
		ozb_debug_print("   case TX_ON:");// TODO: REMOVE
		if (psduLength > OZB_aMaxPHYPacketSize)
			return -OZB_PHY_ERR_INVALID_PARAM;
		phy_status.radio = OZB_PHY_BUSY_TX;	//chris: do i need this?
		if (ozb_radio_send(psdu, psduLength) < 0)
			return -OZB_PHY_ERR_HW_FAILURE;
		phy_status.radio = OZB_PHY_TX_ON;
		break;
	}
	ozb_PD_DATA_confirm(status);
	return OZB_PHY_ERR_NONE;
}

/******************************************************************************/
/*                      PLME-SAP Definition (PHY SIDE)                        */
/******************************************************************************/
int8_t ozb_PLME_CCA_request(void)
{
	enum ozb_phy_code_t status;
	#ifdef OZB_DEBUG_LOG
	ozb_debug_print("PLME_CCA_request()");
	#endif

	if (!phy_status.initialized)
		return -OZB_PHY_ERR_NOT_INITIALIZED;
	switch (phy_status.radio) {
	case OZB_PHY_TRX_OFF:
		status = OZB_PHY_TRX_OFF;
		break;
	case OZB_PHY_TX_ON:
		status = OZB_PHY_BUSY;
		break;
	case OZB_PHY_RX_ON:
		if (ozb_radio_get_cca())
			status = OZB_PHY_IDLE;
		else
			status = OZB_PHY_BUSY;
		break;
	default:
		return -OZB_PHY_ERR_INVALID_PARAM;
	}
	ozb_PLME_CCA_confirm(status);
	return OZB_PHY_ERR_NONE;
}

int8_t ozb_PLME_ED_request(void)
{
	enum ozb_phy_code_t status;
	uint8_t energy = 0;
	#ifdef OZB_DEBUG_LOG
	ozb_debug_print("PLME_ED_request");
	#endif

	if (!phy_status.initialized)
		return -OZB_PHY_ERR_NOT_INITIALIZED;
	switch (phy_status.radio) {
	case OZB_PHY_TRX_OFF:
		status = OZB_PHY_TRX_OFF;
		break;
	case OZB_PHY_TX_ON:
		status = OZB_PHY_TX_ON;
		break;
	case OZB_PHY_RX_ON:
		if (ozb_radio_get_rx_power(&energy) < 0)
			return -OZB_PHY_ERR_HW_FAILURE;
		status = OZB_PHY_SUCCESS;
		break;
	default:
		return -OZB_PHY_ERR_INVALID_PARAM;
	}
	ozb_PLME_ED_confirm(status, energy);
	return OZB_PHY_ERR_NONE;
}

int8_t ozb_PLME_GET_request(enum ozb_phy_pib_id_t PIBAttribute)
{
	enum ozb_phy_code_t status = OZB_PHY_SUCCESS;
	void *value = NULL;
	#ifdef OZB_DEBUG_LOG
	char s[100];
	sprintf(s, "PLME_GET_request(%u)", PIBAttribute);
	ozb_debug_print(s);
	#endif

	if (!phy_status.initialized)
		return -OZB_PHY_ERR_NOT_INITIALIZED;
	switch (PIBAttribute) {
	case OZB_PHY_CURRENT_CHANNEL :
		value = (void *) &(ozb_phy_pib.phyCurrentChannel);
		break;
	case OZB_PHY_CHANNEL_SUPPORTED :
		value =  (void *) &(ozb_phy_pib.phyChannelsSupported);
		break;
	case OZB_PHY_TRANSMIT_POWER :
		value = (void *) &(ozb_phy_pib.phyTransmitPower);
		break;
	case OZB_PHY_CCA_MODE :
		value = (void *) &(ozb_phy_pib.phyCCAMode);
		break;
	case OZB_PHY_CURRENT_PAGE :
		value = (void *) &(ozb_phy_pib.phyCurrentPage);
		break;
	case OZB_PHY_MAX_FRAME_DURATION :
		value = (void *) &(ozb_phy_pib.phyMaxFrameDuration);
		break;
	case OZB_PHY_SHR_DURATION :
		value = (void *) &(ozb_phy_pib.phySHRDuration);
		break;
	case OZB_PHY_SYMBOLS_PER_OCTET :
		value = (void *) &(ozb_phy_pib.phySymbolsPerOctet);
		break;
	default:
		status = OZB_PHY_UNSUPPORTED_ATTRIBUTE;
		break;
	}
	ozb_PLME_GET_confirm(status, PIBAttribute, value);
	return OZB_PHY_ERR_NONE;
}

int8_t ozb_PLME_SET_TRX_STATE_request(enum ozb_phy_code_t state)
{
	enum ozb_phy_code_t status;
	#ifdef OZB_DEBUG_LOG
	char s[100];
	char s1[30];
	ozb_debug_sprint_phycode(state, s1);
	sprintf(s, "PLME_SET_TRX_STATE_request(%s)", s1);
	ozb_debug_print(s);
	#endif

	if (!phy_status.initialized)
		return -OZB_PHY_ERR_NOT_INITIALIZED;
	if (phy_status.radio == state) {
		status = phy_status.radio;
	} else {
		switch (state) {
		case OZB_PHY_TX_ON :
			if (ozb_radio_set_tx() < 0)
				return -OZB_PHY_ERR_HW_FAILURE;
			phy_status.radio = OZB_PHY_TX_ON;
			break;
		case OZB_PHY_FORCE_TRX_OFF :
			if (ozb_radio_sleep() < 0)
				return -OZB_PHY_ERR_HW_FAILURE;
			phy_status.radio = OZB_PHY_TRX_OFF;
			break;
		case OZB_PHY_TRX_OFF :
			if (phy_status.radio == OZB_PHY_RX_ON)
				while (ozb_radio_busy_rx()) ;
			else if (phy_status.radio == OZB_PHY_TX_ON)
				while (ozb_radio_busy_tx()) ;
			else
				return -OZB_PHY_ERR_INVALID_PARAM;
			if (ozb_radio_sleep() < 0)
					return -OZB_PHY_ERR_HW_FAILURE;
			phy_status.radio = OZB_PHY_TRX_OFF;
			break;
		case OZB_PHY_RX_ON :
			while (ozb_radio_busy_tx()) ;
			if (ozb_radio_set_rx() < 0)
				return -OZB_PHY_ERR_HW_FAILURE;
			phy_status.radio = OZB_PHY_RX_ON;
			break;
		default :
			return -OZB_PHY_ERR_INVALID_PARAM;
		}
		status = OZB_PHY_SUCCESS;
	}
	ozb_PLME_SET_TRX_STATE_confirm(status);
	return OZB_PHY_ERR_NONE;
}

int8_t ozb_PLME_SET_request(enum ozb_phy_pib_id_t PIBAttribute,
			    void *PIBAttributeValue)
{
	enum ozb_phy_code_t status = OZB_PHY_SUCCESS;
	uint8_t param = *((uint8_t*) PIBAttributeValue);
	#ifdef OZB_DEBUG_LOG
	char s[100];
	sprintf(s, "PLME_SET_request(a=%u, val=%u)", PIBAttribute, param);
	ozb_debug_print(s);
	#endif

	if (!phy_status.initialized)
		return -OZB_PHY_ERR_NOT_INITIALIZED;
	switch (PIBAttribute) {
	case OZB_PHY_CURRENT_CHANNEL :
		if (param > OZB_RADIO_CHANNEL_LAST || 
		    param < OZB_RADIO_CHANNEL_FIRST) {
			status = OZB_PHY_INVALID_PARAMETER;
			break;
		}
		if (ozb_radio_set_channel(param) < 0)
			return -OZB_PHY_ERR_HW_FAILURE;
		ozb_phy_pib.phyCurrentChannel = param;
		break;
	case OZB_PHY_TRANSMIT_POWER :
		param = ozb_phy_pib.phyTransmitPower | (param & 0x3F);
		/* TODO: chris: call the radio primitive for this ...
				check on param is useless, right????  */
		if (ozb_radio_set_tx_power(param) < 0)
			return -OZB_PHY_ERR_HW_FAILURE;
		ozb_phy_pib.phyTransmitPower = param;
		break;
	case OZB_PHY_CCA_MODE :
		if (param < 1 || param > 3) {
			status = OZB_PHY_INVALID_PARAMETER;
			break;
		}
		if (ozb_radio_set_cca_mode(param) < 0)
			return -OZB_PHY_ERR_HW_FAILURE;
		ozb_phy_pib.phyCCAMode = param;
		break;
	case OZB_PHY_CURRENT_PAGE :
		/* chris: should I need to check according to the define
			   OZB_PHY_CHANNEL_PAGES ???
		 */
		if (param > OZB_PHY_CHANNEL_PAGE_LAST) {
			status = OZB_PHY_INVALID_PARAMETER;
			break;
		}
		/* TODO: chris: call the radio primitive for this ... exists??*/
		ozb_phy_pib.phyCurrentPage = param;
		break;
	case OZB_PHY_MAX_FRAME_DURATION :
	case OZB_PHY_SHR_DURATION :
	case OZB_PHY_SYMBOLS_PER_OCTET :
	case OZB_PHY_CHANNEL_SUPPORTED :
		status = OZB_PHY_READ_ONLY;
		break;
	default:
		status = OZB_PHY_UNSUPPORTED_ATTRIBUTE;
		break;
	}
	ozb_PLME_SET_confirm(status, PIBAttribute);
	return OZB_PHY_ERR_NONE;
}
