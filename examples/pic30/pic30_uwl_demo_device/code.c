#include "uwl_ieee802154.h"	
#include "kal/uwl_kal.h"	
#include "ee.h"
#include "cpu/pic30/inc/ee_irqstub.h"
#include <string.h>
#include <stdio.h> //TODO: REMOVE together with the sprintf() !!!!!


/* Primary (XT, HS, EC) Oscillator without PLL */
_FOSCSEL(FNOSC_PRIPLL);		
/* OSC2 Pin Function: OSC2 is Clock Output 
 * Primary Oscillator Mode: XT Crystanl */
_FOSC(OSCIOFNC_ON & POSCMD_XT);	
/* Watchdog Timer Enabled/disabled by user software */
_FWDT(FWDTEN_OFF);		
/* Disable Code Protection */		
_FGS(GCP_OFF);           	

/******************************************************************************/
/*                         Constant Definitions                               */
/******************************************************************************/

#define PERFORM_FAST_TEST

#define LCD_PERIOD 		100
#define TEST_PANID		0x000A
#define TEST_COORD_ADDR		0x0001
#define TEST_DEVICE_ADDR	0x0002
#define TEST_CHANNEL		24
#define TEST_PACKET_SIZE	110

#ifdef PERFORM_FAST_TEST
#define CHAT_PACKET_SIZE	10 /* min is 10! */
#else
#define CHAT_PACKET_SIZE	100
#endif

#ifdef UWL_HAL_EXTERNAL_TIMER

#define CHAT_SEND_OFFSET 	3000
#define TEST_SEND_CSMA_PERIOD	3000
#ifdef PERFORM_FAST_TEST
#define CHAT_SEND_PERIOD	100
#else
#define CHAT_SEND_PERIOD	1000
#endif

#else /* UWL_HAL_EXTERNAL_TIMER */

#define CHAT_SEND_OFFSET 	1000
#define TEST_SEND_CSMA_PERIOD	1000
#ifdef PERFORM_FAST_TEST
#define CHAT_SEND_PERIOD	25
#else
#define CHAT_SEND_PERIOD	500
#endif

#endif /* UWL_HAL_EXTERNAL_TIMER */

/******************************************************************************/
/*                         Global Variables                                   */
/******************************************************************************/
#ifdef __USE_DEMOBOARD__
static unsigned char lcd_pos = 0;
static char lcd_buf[32];
static volatile unsigned char wait_button = 1;
#endif /* __USE_DEMOBOARD__ */
uint8_t network_ready = 0;
volatile uint8_t keep_sending_gts = 0;
uint8_t test_packet[TEST_PACKET_SIZE];
uint16_t tx_counter = 0;
uint16_t tx_success = 0;
uint16_t rx_counter = 0;
uint16_t rx_seq_errors = 0;
uint16_t packet_ack = 0;


/******************************************************************************/
/*                          Function Definitions                              */
/******************************************************************************/
/* ---------------------------------------------------------------------------- 
|  Put String on LCD:                                                          |
|                                                                              |
|  Access the LCD through the distributed buffer and the lcd_writer meism      |
 ---------------------------------------------------------------------------- */
#ifdef __USE_DEMOBOARD__
static void lcd_puts(const char *ch)
{
	GetResource(LCD_MUTEX);
	while (*ch != '\0') {
		if (lcd_pos == 0) {			
			memcpy(lcd_buf, lcd_buf + 16, 16);
			memset(lcd_buf + 16, ' ', 16);
			lcd_pos = 16;
		}
		if (*ch == '\n') {
			memset(lcd_buf+lcd_pos, ' ', 32 - lcd_pos);
			ch++;
			lcd_pos = 31;
		} else {
			lcd_buf[lcd_pos] = *ch++;
		}
		lcd_pos = (lcd_pos + 1) % 32;
	}
	ReleaseResource(LCD_MUTEX);	
}
/* ---------------------------------------------------------------------------- 
|  Press button actons:                                                        |
|                                                                              |
|  Button 1: Reset the wait_button variable (allow active wait)                |
|  Button 2:                                                                   |
|  Button 3:                                                                   |
|  Button 4:                                                                   |
 ---------------------------------------------------------------------------- */
static void button_action(void)
{
	static char b2_pressed = 0;
	static char b3_pressed = 0;
	static char b4_pressed = 0;

	if (EE_button_get_S1() == 1 && wait_button == 1) {
		wait_button = 0;
		EE_leds_off();
	} else if (EE_button_get_S2() == 1 && network_ready) {
		if (b3_pressed) {
			keep_sending_gts = 0;
		} else {
			keep_sending_gts = 1;
			ActivateTask(TEST_SEND_GTS);
		}
		b2_pressed = !b2_pressed;
	} else if (EE_button_get_S3() == 1 && network_ready) {
		if (b3_pressed)
			CancelAlarm(TEST_SEND_CSMA_ALARM);
		else
			SetRelAlarm(TEST_SEND_CSMA_ALARM, 100, 
				    TEST_SEND_CSMA_PERIOD);
		b3_pressed = !b3_pressed;
	} else if (EE_button_get_S4() == 1 && network_ready) {
		if (b4_pressed)
			CancelAlarm(CHAT_SEND_ALARM);
		else
			SetRelAlarm(CHAT_SEND_ALARM, CHAT_SEND_OFFSET, 
				    CHAT_SEND_PERIOD);
		b4_pressed = !b4_pressed;
	}
}
#endif /* __USE_DEMOBOARD__ */
/* ---------------------------------------------------------------------------- 
|  Rx callback function:                                                       |
|                                                                              |
|  Called by the network stack when data have been received.                   |
 ---------------------------------------------------------------------------- */
static void rx_data(int8_t status, uint8_t *data, uint8_t len, uint16_t addr)
{
	if (len <= TEST_PACKET_SIZE) {
		memcpy(test_packet, data, len);
		ActivateTask(CHAT_RECEIVE);
	}
}
/* ---------------------------------------------------------------------------- 
|  Setup system timers:                                                        |
|                                                                              |
|  Timer1: used for system ticks (CounterTick)                                 |
 ---------------------------------------------------------------------------- */
static void timer_set(void)
{
	/* TIMER 1  */

	T1CON = 0;		/* Stops the Timer1 and reset control reg */
	TMR1 = 0;		/* Clear contents of the timer register	*/
	#ifdef UWL_HAL_EXTERNAL_TIMER
	PR1 = 0x3200;		/* Load the Period register -> 320us @ 40MHz */
	#else
	PR1 = 0x9C40;		/* Load the Period register -> 1ms @ 40MHz */
	#endif
	//PR1 = 0x4E20;		/* Load the Period register -> 500us @ 40MHz */
	//PR1 = 0x2710;		/* Load the Period register -> 250us @ 40MHz */
	IPC0bits.T1IP = 5;	/* Set Timer1 priority to 5 */
	IFS0bits.T1IF = 0;	/* Clear the Timer1 interrupt status flag */
	IEC0bits.T1IE = 1;	/* Enable Timer1 interrupts */
	T1CONbits.TON = 1;	/* Start Timer1 without prescaler */
}

/******************************************************************************/
/*                                  TASKs                                     */
/******************************************************************************/
/* ---------------------------------------------------------------------------- 
|  LCD Writer                                                                  |
|                                                                              |
|  Manage writing on the LCD                                                   |
 ---------------------------------------------------------------------------- */
TASK(LCD_WRITE)
{
	#ifdef __USE_DEMOBOARD__
	unsigned char i;

	GetResource(LCD_MUTEX);
	for (i = 0; i < 16; i++)
		EE_lcd_putc(lcd_buf[i]);
	EE_lcd_line2();
	for (i = 16; i < 32;i++)
		EE_lcd_putc(lcd_buf[i]);
	EE_lcd_home();	
	ReleaseResource(LCD_MUTEX);	
	#endif /* __USE_DEMOBOARD__ */
}
/* ---------------------------------------------------------------------------- 
|  Test Sender                                                                 |
|                                                                              |
|  Send packet to the coordinator using GTS                                    |
 ---------------------------------------------------------------------------- */
TASK(TEST_SEND_GTS)
{
	static uint16_t send_gts_ok = 0;
	static uint16_t send_gts_errors = 0;
	int8_t retv;
	uint16_t i;
	#ifdef __USE_DEMOBOARD__
	char str[100];
	#endif

	test_packet[0] = 0xA2;
	test_packet[1] = 0xB2;
	test_packet[2] = 0xC2;
	test_packet[3] = 0xD2;
	test_packet[4] = 0xE2;
	test_packet[5] = 0xF2;
	test_packet[6] = 0x00;
	i = 0;
	while (keep_sending_gts) {
		test_packet[7] = i >> 8;
		test_packet[8] = i & 0xFF;
		retv = uwl_simple154_send(test_packet, TEST_PACKET_SIZE, 0, 1);
		if (retv < 0) {
			send_gts_errors++;
			EE_led_off();
			//for (;;) ;
		} else {
			send_gts_ok++;
			EE_led_on();
		}
		i++;
	}
	#ifdef __USE_DEMOBOARD__
	sprintf(str, "\nS_154 E=%u\nGTS TXs=%u", send_gts_errors, send_gts_ok);
	lcd_puts(str);
	#endif /* __USE_DEMOBOARD__ */
}
/* ---------------------------------------------------------------------------- 
|  Test Sender                                                                 |
|                                                                              |
|  Send packet to the coordinator using CSMA                                   |
 ---------------------------------------------------------------------------- */
TASK(TEST_SEND_CSMA)
{
	static uint16_t send_csma_ok = 0;
	static uint16_t send_csma_errors = 0;
	int8_t retv;
	uint16_t i;
	#ifdef __USE_DEMOBOARD__
	char str[100];
	#endif

	test_packet[0] = 0xA1;
	test_packet[1] = 0xB1;
	test_packet[2] = 0xC1;
	test_packet[3] = 0xD1;
	test_packet[4] = 0xE1;
	test_packet[5] = 0xF1;
	test_packet[6] = 0x00;
	for (i = 0; i < 1000; i++) {
		test_packet[7] = i >> 8;
		test_packet[8] = i & 0xFF;
		retv = uwl_simple154_send(test_packet, TEST_PACKET_SIZE, 0, 0);
		if (retv < 0) {
			send_csma_errors++;
			EE_led_off();
			//for (;;) ;
		} else {
			send_csma_ok++;
			EE_led_on();
		}
	}
	#ifdef __USE_DEMOBOARD__
	sprintf(str, "\nS_154 E=%u\nCSMA TXs=%u",send_csma_errors,send_csma_ok);
	lcd_puts(str);
	#endif /* __USE_DEMOBOARD__ */
}
/* ---------------------------------------------------------------------------- 
|  Test SIMPLE154 TX                                                           |
|                                                                              |
|  This task is the sending part of a 'chat' test application.                 |
|  This simply sends a packet to a remote node with two increasing IDs:        |
|  one for this node, the other to acknowledge the eventually received ID      |
 ---------------------------------------------------------------------------- */
TASK(CHAT_SEND)
{
	int8_t retv;
	static uint8_t packet[CHAT_PACKET_SIZE];
	static char tx_led = 0;

	memset(packet, 0, 100);
	packet[0] = 0xAA;
	packet[1] = 0xBB;
	packet[2] = 0xCC;
	packet[3] = 0xDD;
	packet[4] = 0xEE;
	packet[5] = 0xFF;
	packet[6] = tx_counter >> 8;
	packet[7] = tx_counter & 0x00FF;
	packet[8] = packet_ack >> 8;
	packet[9] = packet_ack & 0x00FF;
	if (tx_led) {
		tx_led = 0;
		#if defined __USE_MOTIONBOARD__
		EE_led_0_off();
		#elif defined __USE_DEMOBOARD__
		EE_led_6_off();
		EE_led_7_on();
		#endif
	} else {
		tx_led = 1;
		#if defined __USE_MOTIONBOARD__
		EE_led_0_on();
		#elif defined __USE_DEMOBOARD__
		EE_led_6_on();
		EE_led_7_off();
		#endif
	}
	retv = uwl_simple154_send(packet, CHAT_PACKET_SIZE, 0, 1);
	tx_counter++;
	if (retv < 0) {
	//	#ifdef __USE_DEMOBOARD__
	//	EE_leds_on();
	//	lcd_puts("\nCHAT error\nSEND GTS");
	//	#endif /* __USE_DEMOBOARD__ */
		EE_led_off();
		//for (;;) ;
	} else {
		tx_success++;
	}
}
/* ---------------------------------------------------------------------------- 
|  Test SIMPLE154 RX                                                           |
|                                                                              |
| ....                                                                         |
 ---------------------------------------------------------------------------- */
TASK(CHAT_RECEIVE)
{
	#ifdef __USE_DEMOBOARD__
	char str[100];
	#endif
	static char rx_led = 0;

	if (test_packet[0] != 0x0A || test_packet[1] != 0x0B ||
	    test_packet[2] != 0x0C || test_packet[3] != 0x0D ||
	    test_packet[4] != 0x0E || test_packet[5] != 0x0F) {
		#ifdef __USE_DEMOBOARD__
		EE_led_3_on();
		#endif
		return;
	}
	packet_ack = test_packet[7];
	packet_ack += ((uint16_t) test_packet[6]) << 8;
	if (packet_ack != rx_counter)
		rx_seq_errors++;
	rx_counter = packet_ack;
	rx_counter++;
	if (rx_led) {
		rx_led = 0;
		#if defined __USE_MOTIONBOARD__
		EE_led_1_off();
		#elif defined __USE_DEMOBOARD__
		EE_led_4_off();
		EE_led_5_on();
		#endif
	} else {
		rx_led = 1;
		#if defined __USE_MOTIONBOARD__
		EE_led_1_on();
		#elif defined __USE_DEMOBOARD__
		EE_led_4_on();
		EE_led_5_off();
		#endif
	}
	#ifdef __USE_DEMOBOARD__
	sprintf(str, "\nCHAT:D ETX=%u\nRX=%u ERR=%u", 
		tx_counter - tx_success, rx_counter, rx_seq_errors);
	lcd_puts(str);
	#endif /* __USE_DEMOBOARD__ */
}


/******************************************************************************/
/*                                   MAIN                                     */
/******************************************************************************/
int main(void)
{
	int8_t retv;

	/* Clock setup for 40 MHz */
	CLKDIVbits.DOZEN   = 0;
	CLKDIVbits.PLLPRE  = 0;
	CLKDIVbits.PLLPOST = 0;
	PLLFBDbits.PLLDIV  = 78;
	while (OSCCONbits.LOCK != 1) ;
	/* Init basic components */	
	timer_set();		
	EE_leds_init();
	#if defined __USE_MOTIONBOARD__
	EE_daughter_leds_init();
	EE_buttons_init(NULL, 0x00);
	#elif defined __USE_DEMOBOARD__
	EE_demoboard_leds_init();
	EE_buttons_init(&button_action, 0x0F);
	EE_lcd_init();
	EE_lcd_clear();
	EE_led_off();
	EE_leds_off();
	lcd_puts("\nHullo! Press\n1 to start D.");
	SetRelAlarm(LCD_WRITE_ALARM, 1000, LCD_PERIOD); /* Start LCD writer */
	wait_button = 1;
	while (wait_button) ;
	#endif /* __USE_DEMOBOARD__ */
	/* Init the Network Stack */
	uwl_simple154_set_rx_callback(rx_data);
	retv = uwl_simple154_init_device(TEST_DEVICE_ADDR, TEST_COORD_ADDR, 
					 TEST_PANID, TEST_CHANNEL);
	if (retv < 0) {
		#ifdef __USE_DEMOBOARD__
		EE_leds_on();
		lcd_puts("\nS_154 error\ninit device");
		#endif /* __USE_DEMOBOARD__ */
		for (;;) ;
	}
	#if defined __USE_MOTIONBOARD__
	SetRelAlarm(CHAT_SEND_ALARM, CHAT_SEND_OFFSET, CHAT_SEND_PERIOD);
	#elif defined __USE_DEMOBOARD__
	lcd_puts("\nD. is alive!\nReady!");
	#endif /* __USE_DEMOBOARD__ */
	/* Start the application */
	network_ready = 1;
	EE_led_on();

		
	/* Forever loop: background activities (if any) should go here */
	for (;;) ;

	return 0;
}



/******************************************************************************/
/*                                     ISRs                                   */
/******************************************************************************/
static volatile unsigned char counter_scaler = 0;
/* ---------------------------------------------------------------------------- 
|  ISR2 Timer1:                                                                |
|                                                                              |
|  Calls CounterTick for TASK_COUNTER                                          |
 ---------------------------------------------------------------------------- */
ISR2(_T1Interrupt)
{
	IFS0bits.T1IF = 0;
	#ifdef UWL_HAL_EXTERNAL_TIMER
	counter_scaler = (counter_scaler + 1) % 3;
	if (counter_scaler == 0)
		CounterTick(TASK_COUNTER);
	uwl_kal_external_timer_action();
	#else
	CounterTick(TASK_COUNTER);
	#endif /* UWL_HAL_EXTERNAL_TIMER */
}


/******************************************************************************/
/*                                    TRAPs                                   */
/******************************************************************************/
//void _ISRFAST _OscillatorFail(void) { for(;;); }
//
//void _ISRFAST _AddressError(void) { for(;;); }
//
//void _ISRFAST _StackError(void) { for(;;); }
//
//void _ISRFAST _MathError(void) 	{ for(;;); }
//
//void _ISRFAST _DMACError(void) { for(;;); }
