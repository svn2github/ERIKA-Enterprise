/**
* @file uwl_radio_mrf24j40.h
* @brief Abstract Radio functions
* @author Gianluca Franchino
* @author Christian Nastasi
* @author Mauro Nino Marinoni
* @version 0.1
* @date 2009-11-30
*
* This file contains the declarations of the abstract radio used by the uWireless
* modules.
*
*/
#ifndef __uwl_radio_mrf24j40_h__
#define __uwl_radio_mrf24j40_h__


#include <hal/uwl_radio.h>
#include <mac/uwl_mac_types.h>

#ifndef USE_MRF24J40
#error "UWL_RADIO ERROR: the MRF24J40 radio driver is required for this!"
#endif

#include <mrf24j40.h>

#ifdef UWL_DEBUG
#include <util/uwl_debug.h> //TODO: REMOVE together with the sprintf() !!!!!
#include <stdio.h> //TODO: REMOVE together with the sprintf() !!!!!
#endif

#define UWL_RADIO_RX_BUFFER_SIZE MRF24J40_BUFFER_SIZE

/**
* @name Phy PAN Information Base Init Value
*
* \todo Check if the initial values adopted in this case are compliant with the
* 	standard and set according to a certain policy, e.g. can read this
*	values from the specific transceiver (hal_radio)?.
* @{ */
#define UWL_RADIO_CURRENT_CHANNEL_INIT 		11
#define UWL_RADIO_CHANNEL_SUPPORTED_INIT	{0x00000000} //TODO
#define UWL_RADIO_TRANSMIT_POWER_INIT		0x00
#define UWL_RADIO_CCA_MODE_INIT 		0x03
#define UWL_RADIO_CURRENT_PAGE_INIT 		0
#define UWL_RADIO_MAX_FRAME_DURATION_INIT	266
#define UWL_RADIO_SHR_DURATION_INIT		10
#define UWL_RADIO_SYMBOLS_PER_OCTET_INIT 	2

#define UWL_RADIO_CHANNEL_FIRST 	11
#define UWL_RADIO_CHANNEL_LAST 		26
/**  @} */

/*
     TODO TODO TODO TODO TODO TODO TODO TODO TODO TODO TODO TODO
 TODO								TODO
 TODO	All the functions must have the syntax:			TODO
 TODO 		int8_t oab_radio_funcname(params...) 		TODO
 TODO	where							TODO
 TODO		- the return value is a status code of the 	TODO
 TODO		  function (1=success, < 0 failure), 		TODO
 TODO		  not a return value!				TODO
 TODO		- the params are for IN and OUT!!!!!|!		TODO
 TODO								TODO
     TODO TODO TODO TODO TODO TODO TODO TODO TODO TODO TODO TODO
*/

//int8_t uwl_radio_init(void *todo);/*TODO: chris: define params */
/**
* @brief Initializes the radio.
*
* This routine returns 0 if everything goes well, -1 otherwise.
*
* @return initialization result (0 ok, -1 failed).
 */
COMPILER_INLINE int8_t uwl_radio_init(void)
{
	/* GF: interrupt set up is hard coded. May be a better way to do that
	*	is needed!
	*
	*Set interrupts register with 0xF6, which means:
	* 7 = '1' = Disables the Sleep alert interrupt
	* 6 = '1' = Disables the wake-up alert interrupt
	* 5 = '1' = Disables the half symbol timer interrupt
	* 4 = '1' = Disables the security key request interrupt
	* 3 = '0' = Enables the RX FIFO reception interrupt
	* 2 = '1' = Disables the TX GTS2 FIFO transmission interrupt
	* 1 = '1' = Disables the TX GTS1 FIFO transmission interrupt
	* 0 = '0' = Enables the TX Normal FIFO transmission interrupt	
	*/
#ifdef __USE_MOTIONBOARD__
	return mrf24j40_init(0xF6, 11, MRF24J40_SPI_PORT_1);
	#else
	return mrf24j40_init(0xF6, 11, MRF24J40_SPI_PORT_2);
	#endif

}


int8_t uwl_radio_mac_create_beacon(void);

int8_t uwl_radio_mac_send_beacon(void);


COMPILER_INLINE uint32_t uwl_radio_phy_get_bitrate(void)
{
	/* TODO: change this hard-coding! */
	return 250000;
}


/* chris: Sending function, can be used by the MAC or implement part of the
	  MAC itself! */
/*TODO: chris: do we use the same paradigm (store+send) for all the 4 type?
	Maybe is better to use only send for data, command, ack?
*/
/*TODO: chris: do we want to assume the auto ack generation?
	How do we model this in the generic radio?
*/

COMPILER_INLINE int8_t uwl_radio_slotted_csma_init(void)
{
	return 1;
}


int8_t uwl_radio_store_data(uint8_t *buf, uint8_t len);
int8_t uwl_radio_send_data(void);

int8_t uwl_radio_store_command(uint8_t *buf, uint8_t len);

int8_t uwl_radio_send_command(void);

int8_t uwl_radio_store_ack(uint8_t *buf, uint8_t len);

int8_t uwl_radio_send_ack(void);

/*TODO: chris: do we assume to use the CSMA in the abstract radio?
	we can use a specific function or a flag in the former send functions
*/
int8_t uwl_radio_send_csma(void *todo); /*TODO: chris: define params */

/* chris: Receiving function (callbback mechanism), can be used by the MAC! */
int8_t uwl_radio_set_beacon_rx_callback(void *todo); /*TODO: chris: def params*/
int8_t uwl_radio_set_data_rx_callback(void *todo); /*TODO: chris: def params */
int8_t uwl_radio_set_command_rx_callback(void *todo); /*TODO: chris: def parms*/
int8_t uwl_radio_set_ack_rx_callback(void *todo); /*TODO: chris: define params*/

/* chris: this should be the set of common functionalities used by the PHY
	  TODO: add what is missing!
*/

/**
* @brief Send the packet memorized in buf.
*
* This routine stores a packet in the TX fifo of the radio,
* then transmits it.
*
* @param[in] *buf 	The message pointer
* @param[in] buf_legth 	The message lenght
* @return 0 if the initialization goes well, -1 otherwise.
*/
COMPILER_INLINE int8_t uwl_radio_send(uint8_t *buf, uint8_t len)
{

//uwl_debug_print("   uwl_radio_send(...)");// TODO: REMOVE
	if (mrf24j40_store_norm_txfifo( buf, len) < 0)
		return -1; // len is either less than 0 or
			   // greter than 127.
//uwl_debug_print("      Store FIFO OK!");// TODO: REMOVE
	mrf24j40_set_tx();
//uwl_debug_print("      Set TX OK!");// TODO: REMOVE
	/* Wait until the transmission has finished. */
	while (mrf24j40_get_status() & 80);
//uwl_debug_print("      Loop 0x08 ok!");// TODO: REMOVE

//uwl_debug_print("      returning OK!");// TODO: REMOVE
	/* Everything goes well. */
	return UWL_RADIO_ERR_NONE;
}

/**
* @brief Put the transceiver on transmission.
*
* This routine sets the radio on tx, such that a
* message stored into the txfifo will be sent.
*
*/
COMPILER_INLINE int8_t uwl_radio_start_tx(void)
{
	mrf24j40_set_tx();
	return UWL_RADIO_ERR_NONE;
}

/**
* @brief Put the transceiver on transmission.
*
* \todo
*
*/
COMPILER_INLINE int8_t uwl_radio_set_tx(void)
{
	return UWL_RADIO_ERR_NONE;
}

/**
* @brief Verify
*
* \todo
*
*/
COMPILER_INLINE uint8_t uwl_radio_busy_tx(void)
{
	return (mrf24j40_get_status() & 80);
}


/**
* @brief Link a callback to the isr of the radio.
*
* This routine sets the callback for the isr of the radio.
*
* @param[in] rx_callback The callback function.
*/
COMPILER_INLINE int8_t uwl_radio_set_rx_callback(void (*rx_callback)(void))
{
	mrf24j40_set_rx_callback(rx_callback);
	return UWL_RADIO_ERR_NONE;
}

/**
* @brief Get a msg from the rx_fifo.
*
* This routine retrives a msg from the radio rx_fifo.
*
* @param[in] *msg 	The buffer where to store the message from the FIFO
*
* @return the lenght of the received message, or -1 if something has gone wrong.
*/
COMPILER_INLINE int8_t uwl_radio_get_msg(uint8_t *msg)
{
	return mrf24j40_get_fifo_msg(msg);
}


/**
* @brief Set the transmission power.
*
* This routine retrives a msg from the radio rx_fifo.
*
* @param[in] pwr The pwr level setting (see cc2420.h for the available valuses).
*
*/
COMPILER_INLINE int8_t uwl_radio_set_tx_power(uint8_t pwr)
{
	/* TODO: translate the value of pwr from PIB to radio related value! */
	
	pwr = MRF24J40_TX_PWR_SET(MRF24J40_TXPWRL_0dB,
				MRF24J40_TXPWRS_0dB);

	mrf24j40_set_pa(pwr);

	return UWL_RADIO_ERR_NONE;
}

/**
* @brief Get the RSSI
*
* This routine returns the rssi value mesured in dbm
*
* @return the rssi value in dbm, INVALID_RSSI otherwise
*/
COMPILER_INLINE int8_t uwl_radio_get_rx_power(uint8_t *energy)
{
	/*TODO: calculate according to standard*/
	*energy = mrf24j40_get_rssi();
	return UWL_RADIO_ERR_NONE;
}

/**
* @brief Start sleep
*
* This routine puts the radio in sleep mode.
*
* @param[in] sleep_level 	The sleep mode: POWER_DOWN or IDLE
*
*/
COMPILER_INLINE int8_t uwl_radio_sleep(void)
{
	mrf24j40_put_to_sleep();
	return UWL_RADIO_ERR_NONE;
}

/**
* @brief Wake up the radio
*
* This routine resume the radio from sleep.
*
* @param[in] status 	The new working status: RX (st = SLEEP2RX)
* 						or TX (st = SLEEP2TX).
*/
#define SLEEP2RX 0
#define SLEEP2TX 1

COMPILER_INLINE int8_t uwl_radio_wakeup(uint8_t status)
{
	/* chris: FIXME: wrong comparison: status cannot be less than 0!!*/
	if (status > SLEEP2TX)
		return -1;
	mrf24j40_wake();

	if (SLEEP2RX){ }; /* 
			   * Do nothing, the transceiver is already on raceiving
			   * mode. 
			   */

	if (SLEEP2TX)
		mrf24j40_set_tx();
	return 0;

}

/**
* @brief Start receiving
*
* This routine puts the radio on RX mode.
*/
COMPILER_INLINE int8_t uwl_radio_set_rx()
{
	/*
	* Check if the transceiver is on sleep. If so, wake it up!
	*/
	if (mrf24j40_get_status() == 0x40) {
		mrf24j40_wake();

		return UWL_RADIO_ERR_NONE; 
	}
	
	/*
	* If the transceiver is transmitting, wait.
	*/
	while (mrf24j40_get_status() & 80);

	return UWL_RADIO_ERR_NONE;
}

/**
*
* @brief Check if the radio is receiving a message
*
* GF: with the mrf24j40 radio we cannot check if the radio is receiving a packet.
* At this time the function returns 0: no busy. It should return an error, since
* the busy on rx check is not available
*/
//
COMPILER_INLINE uint8_t uwl_radio_busy_rx()
{
	//return cc2420_get_sfd();
	return 0;
}

/**
* @brief Set channel
*
* This routine sets the channel to tune in the CC2420.
*
* @param[in] ch 	The channel to tune in (must be in the interval [11, 26] )
*
 */
COMPILER_INLINE int8_t uwl_radio_set_channel(uint8_t ch)
{
	mrf24j40_set_channel(ch);
	return UWL_RADIO_ERR_NONE;
}

/**
* @brief Store MAC address
*
* This routine sets the MAC address (short or long) in the CC2420.
*
* @param[in] add 	The array containing the MAC address to store in the transceiver.
* @param[in] length The number of bytes forming the address. If length = 2,
* 					store the short address; if length = 8 store the long address.
* @return 0  if length is correct, -1 otherwise.
*/
COMPILER_INLINE int8_t uwl_radio_set_mac_address(uint8_t* add, uint8_t length)
{
	if (length == 2)
		mrf24j40_set_short_mac_add(add);
	else
		if (length == 8)
			mrf24j40_set_ex_mac_add(add);
		else
			return -1;
	return UWL_RADIO_ERR_NONE;
}

/**
* @brief Store MAC PAN ID
*
* This routine sets the MAC PAN ID in the CC2420.
*
* @param[in] id 	The MAC PAN ID to store in the transceiver.
*
 */
/*COMPILER_INLINE int8_t uwl_radio_set_mac_pan_id(uint8_t *id)
{
	cc2420_set_mac_pan_id(id);
}
*/
/**
* @brief Enable the auto CRC capability.
*
* This routine sets the auto CRC function of the radio.
*
*
*/

//COMPILER_INLINE int8_t uwl_radio_set_auto_crc()
//{
//	uint8_t low, high;
//
//	CC2420_REG_READ_CSn(CC2420_REG_MDMCTRL0, high, low)
//	/* chris: FIXME: check the constant! maybe 0b.... better to use 0x...*/
//	CC2420_REG_WRITE_CSn(CC2420_REG_MDMCTRL0, high | 0xb00100000, low);
//}

/**
* @brief Set the CCA (Clear Channel Assessment)
*
* This routine sets the CCA function of the radio.
*
* Note: the CCA is valid when the receiver has been enabled for at least
* 8 sysmbol period (8 * 16us = 128us).
*
* @param[in] mode. This mask is used to set the CCA mode.
*/

#define ENERGY 0x80 /* Clear channel when receiving energy is below
							 threshold. */
#define VALID_FRAME 0x40 /* clear channel when not receiving a
								  valid frame */
#define VALID_FRAME_AND_ENERGY 0xC0 /* clear channel when energy is below
						the threshold and not receiving
						a valid frame */
COMPILER_INLINE int8_t uwl_radio_set_cca_mode(uint8_t mode)
{
	/** Program CCA */
	mrf24j40_set_short_add_mem(MRF24J40_BBREG2, mode | 0x38);
    
	/** Program CCA, RSSI threshold values */
	mrf24j40_set_short_add_mem(MRF24J40_CCAEDTH, 0x60);

	return UWL_RADIO_ERR_NONE;
}

COMPILER_INLINE uint8_t uwl_radio_get_cca(void)
{
	/* GF:
	 * MRF24J40 do not have a CCA pin. So this routine returns
	 * UWL_RADIO_ERR_PHY_FAILURE. Pay attention, looking at uwl_radio.h,
	 * UWL_RADIO_ERR_PHY_FAILURE = 1; We should use a negative value, such as -1;
	 * FIX THIS PROBLEM!!!
	 * 
	 * Note: under uwl, uwl_radio_get_cca(void) = 1 means channel idle.
	 */ 
				
	return UWL_RADIO_ERR_PHY_FAILURE; 
}


#endif /* Header Protection */
