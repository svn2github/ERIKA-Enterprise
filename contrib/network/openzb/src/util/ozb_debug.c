#ifdef OZB_DEBUG_LOG

#include <util/ozb_debug.h>
#include <string.h>

#ifdef OZB_DEBUG_TIME
struct ozb_debug_stat_t ozb_debug_stats;
#endif

#define OZB_DEBUG_LOG_CONSOLE 0
/* TODO: chris: shall waste memory for this check variable or not? */
static uint8_t _ozb_debug_initialized = 0; 

int8_t ozb_debug_init(void)
{
	#ifdef OZB_DEBUG_TIME
	/* TODO: change this hardcoding!!!!! */
	if (daq_time_init(40000) < 0)
		return -1;
	/* TODO: initialize ozb_debug_stats */
	#endif

	#ifdef OZB_DEBUG_LOG
	_ozb_debug_initialized = 0;
	console_descriptor_t *des = NULL;
	#ifdef OZB_DEBUG_LOG_SERIAL 
	des = console_serial_config(OZB_DEBUG_LOG_SERIAL_PORT, 
				    OZB_DEBUG_LOG_SERIAL_BAUDRATE,
				    OZB_DEBUG_LOG_SERIAL_OPT);
	#endif
	if (des == NULL)
		return -1;
	if (console_init(OZB_DEBUG_LOG_CONSOLE, des) < 0)
		return -1;
	_ozb_debug_initialized = 1;
	return console_open(OZB_DEBUG_LOG_CONSOLE);
	#endif /* OZB_DEBUG_LOG */
}

int8_t ozb_debug_write(uint8_t *msg, uint16_t len) 
{
	if (_ozb_debug_initialized)
		return console_write(OZB_DEBUG_LOG_CONSOLE, msg, len);
	return -1;
}

int8_t ozb_debug_print(const char *msg) 
{
	#ifdef OZB_DEBUG_LOG_HAS_PRINT
	int8_t retv = 0;
	const char *m = "\n\rOZB_DEBUG_LOG: ";

	if (_ozb_debug_initialized) {
		retv = console_write(OZB_DEBUG_LOG_CONSOLE, (uint8_t *) m, 
				     strlen(m));
		if (retv < 0)
			return retv;
		return console_write(OZB_DEBUG_LOG_CONSOLE, (uint8_t *) msg, 
				     strlen(msg));
	}
	return -1;
	#else
	return 1;
	#endif /* OZB_DEBUG_LOG_DEVEL */
}

void ozb_debug_print_phycode(enum ozb_phy_code_t c, char *out) 
{
	switch (c) {
	case OZB_BUSY:
		strcpy(out, "OZB_BUSY");
		break;
	case OZB_BUSY_RX:
		strcpy(out, "OZB_BUSY_RX");
		break;
	case OZB_BUSY_TX:
		strcpy(out, "OZB_BUSY_TX");
		break;
	case OZB_FORCE_TRX_OFF:
		strcpy(out, "OZB_FORCE_TRX_OFF");
		break;
	case OZB_IDLE:
		strcpy(out, "OZB_IDLE");
		break;
	case OZB_INVALID_PARAMETER:
		strcpy(out, "OZB_INVALID_PARAMETER");
		break;
	case OZB_RX_ON:
		strcpy(out, "OZB_RX_ON");
		break;
	case OZB_SUCCESS:
		strcpy(out, "OZB_SUCCESS");
		break;
	case OZB_TRX_OFF:
		strcpy(out, "OZB_TRX_OFF");
		break;
	case OZB_TX_ON:
		strcpy(out, "OZB_TX_ON");
		break;
	case OZB_UNSUPPORTED_ATTRIBUTE:
		strcpy(out, "OZB_UNSUPPORTED_ATTRIBUTE");
		break;
	case OZB_READ_ONLY:
		strcpy(out, "OZB_READ_ONLY");
		break;
	}
}

void ozb_debug_print_maccode(enum ozb_mac_code_t c, char *out)
{
	switch (c) {
	case OZB_MAC_SUCCESS:
		strcpy(out, "OZB_MAC_SUCCESS");
		break;
	case OZB_MAC_PAN_AT_CAPACITY:
		strcpy(out, "OZB_MAC_PAN_AT_CAPACITY");
		break;
	case OZB_MAC_PAN_ACCESS_DENIED:
		strcpy(out, "OZB_MAC_PAN_ACCESS_DENIED");
		break;
	case OZB_MAC_COUNTER_ERROR:
		strcpy(out, "OZB_MAC_COUNTER_ERROR");
		break;
	case OZB_MAC_IMPROPER_KEY_TYPE:
		strcpy(out, "OZB_MAC_IMPROPER_KEY_TYPE");
		break;
	case OZB_MAC_IMPROPER_SECURITY_LEVEL:
		strcpy(out, "OZB_MAC_IMPROPER_SECURITY_LEVEL");
		break;
	case OZB_MAC_UNSUPPORTED_LEGACY:
		strcpy(out, "OZB_MAC_UNSUPPORTED_LEGACY");
		break;
	case OZB_MAC_UNSUPPORTED_SECURITY:
		strcpy(out, "OZB_MAC_UNSUPPORTED_SECURITY");
		break;
	case OZB_MAC_BEACON_LOSS:
		strcpy(out, "OZB_MAC_BEACON_LOSS");
		break;
	case OZB_MAC_CHANNEL_ACCESS_FAILURE:
		strcpy(out, "OZB_MAC_CHANNEL_ACCESS_FAILURE");
		break;
	case OZB_MAC_DEFINED:
		strcpy(out, "OZB_MAC_DEFINED");
		break;
	case OZB_MAC_DISABLE_TRX_FAIULURE:
		strcpy(out, "OZB_MAC_DISABLE_TRX_FAIULURE");
		break;
	case OZB_MAC_FRAME_TOO_LONG:
		strcpy(out, "OZB_MAC_FRAME_TOO_LONG");
		break;
	case OZB_MAC_SECURITY_ERROR:
		strcpy(out, "OZB_MAC_SECURITY_ERROR");
		break;
	case OZB_MAC_INVALID_GTS:
		strcpy(out, "OZB_MAC_INVALID_GTS");
		break;
	case OZB_MAC_INVALID_HANDLE:
		strcpy(out, "OZB_MAC_INVALID_HANDLE");
		break;
	case OZB_MAC_INVALID_PARAMETER:
		strcpy(out, "OZB_MAC_INVALID_PARAMETER");
		break;
	case OZB_MAC_NO_ACK:
		strcpy(out, "OZB_MAC_NO_ACK");
		break;
	case OZB_MAC_NO_BEACON:
		strcpy(out, "OZB_MAC_NO_BEACON");
		break;
	case OZB_MAC_NO_DATA:
		strcpy(out, "OZB_MAC_NO_DATA");
		break;
	case OZB_MAC_NO_SHORT_ADDRESS:
		strcpy(out, "OZB_MAC_NO_SHORT_ADDRESS");
		break;
	case OZB_MAC_OUT_OF_CAP:
		strcpy(out, "OZB_MAC_OUT_OF_CAP");
		break;
	case OZB_MAC_PAN_ID_CONFLICT:
		strcpy(out, "OZB_MAC_PAN_ID_CONFLICT");
		break;
	case OZB_MAC_REALIGNMENT:
		strcpy(out, "OZB_MAC_REALIGNMENT");
		break;
	case OZB_MAC_TRANSACTION_EXPIRED:
		strcpy(out, "OZB_MAC_TRANSACTION_EXPIRED");
		break;
	case OZB_MAC_TRANSACTION_OVERFLOW:
		strcpy(out, "OZB_MAC_TRANSACTION_OVERFLOW");
		break;
	case OZB_MAC_TX_ACTIVE:
		strcpy(out, "OZB_MAC_TX_ACTIVE");
		break;
	case OZB_MAC_UNAVAILABLE_KEY:
		strcpy(out, "OZB_MAC_UNAVAILABLE_KEY");
		break;
	case OZB_MAC_UNSUPPORTED_ATTRIBUTE:
		strcpy(out, "OZB_MAC_UNSUPPORTED_ATTRIBUTE");
		break;
	case OZB_MAC_INVALID_ADDRESS:
		strcpy(out, "OZB_MAC_INVALID_ADDRESS");
		break;
	case OZB_MAC_ON_TIME_TOO_LONG:
		strcpy(out, "OZB_MAC_ON_TIME_TOO_LONG");
		break;
	case OZB_MAC_PAST_TIME:
		strcpy(out, "OZB_MAC_PAST_TIME");
		break;
	case OZB_MAC_TRACKING_OFF:
		strcpy(out, "OZB_MAC_TRACKING_OFF");
		break;
	case OZB_MAC_INVALID_INDEX:
		strcpy(out, "OZB_MAC_INVALID_INDEX");
		break;
	case OZB_MAC_LIMIT_REACHED:
		strcpy(out, "OZB_MAC_LIMIT_REACHED");
		break;
	case OZB_MAC_READ_ONLY:
		strcpy(out, "OZB_MAC_READ_ONLY");
		break;
	case OZB_MAC_SCAN_IN_PROGRESS:
		strcpy(out, "OZB_MAC_SCAN_IN_PROGRESS");
		break;
	case OZB_MAC_SUPERFRAME_OVERLAP:
		strcpy(out, "OZB_MAC_SUPERFRAME_OVERLAP");
		break;
	case OZB_MAC_BEACON_LOST:
		strcpy(out, "OZB_MAC_BEACON_LOST");
		break;
	}
} 

#endif /* OZB_DEBUG */
