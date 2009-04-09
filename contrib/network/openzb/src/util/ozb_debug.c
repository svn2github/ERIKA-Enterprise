#ifdef OZB_DEBUG

#include <util/ozb_debug.h>
#include <string.h>

#define OZB_DEBUG_CONSOLE 0
/* TODO: chris: shall waste memory for this check variable or not? */
static uint8_t _ozb_debug_initialized = 0; 

int8_t ozb_debug_init(void)
{
	_ozb_debug_initialized = 0;
	console_descriptor_t *des = NULL;
	#ifdef OZB_DEBUG_SERIAL 
	des = console_serial_config(OZB_DEBUG_SERIAL_PORT, 
				    OZB_DEBUG_SERIAL_BAUDRATE,
				    OZB_DEBUG_SERIAL_OPT);
	#endif
	if (des == NULL)
		return -1;
	if (console_init(OZB_DEBUG_CONSOLE, des) < 0)
		return -1;
	_ozb_debug_initialized = 1;
	return console_open(OZB_DEBUG_CONSOLE);
}

int8_t ozb_debug_write(uint8_t *msg, uint16_t len) 
{
	if (_ozb_debug_initialized)
		return console_write(OZB_DEBUG_CONSOLE, msg, len);
	return -1;
}

int8_t ozb_debug_print(const char *msg) 
{
	int8_t retv = 0;
	const char *m = "\n\rOZB_DEBUG: ";

	if (_ozb_debug_initialized) {
		retv = console_write(OZB_DEBUG_CONSOLE, (uint8_t*)m, strlen(m));
		if (retv < 0)
			return retv;
		return console_write(OZB_DEBUG_CONSOLE, (uint8_t *) msg, 
				     strlen(msg));
	}
	return -1;
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


#endif /* OSB_DEBUG */
