/*
 * mirtes_conf.h
 *
 *  Created on: 30/nov/2009
 *      Author: Daniele Alessandrelli
 */

#ifndef MIRTES_CONF_H_
#define MIRTES_CONF_H_

#ifdef __LM32__
#ifdef __USE_LEDS__
#define EE_leds_init() EE_led_init()
#else
#define EE_leds_init()
#endif
#endif

/* This sensor node will be support the following sensors */
//#define MIRTES_DB_TEMPERATURE
//#define MIRTES_DB_ILLUMINANCE
//#define MIRTES_DB_ACCELERATION
#define MIRTES_DB_IPERMOB_PARKING

///**************************/
///* 802.15.4 configuration */
///**************************/
//#define MIRTES_COORD_ADDR  0x0001
//#define MIRTES_PAN_ID      0x0001
//#define MIRTES_CHANNEL     0x10
//#define MIRTES_DEV_ADDR 0x0007

/**************************/
/* 802.15.4 configuration */
/**************************/
#define MIRTES_COORD_ADDR	0x0001
#define MIRTES_PAN_ID		0x000A
#define MIRTES_CHANNEL		0x0D
#define MIRTES_DEV_ADDR		0x0007

/************************/
/*    DO NOT CHANGE     */
/************************/
#define MIRTES_DB_TYPE_ARCHIVE_SIZE 8

#define MIRTES_SELECTED_COLUMN_MAX_NR (25)
#define MIRTES_WHERE_CONDITION_MAX_NR (0)
#define MIRTES_HAVING_CONDITION_MAX_NR (0)
#define MIRTES_AGGREGATION_MAX_NR (0)

#define MIRTES_BIG_ENDIAN_NETWORK


#endif /* MIRTES_CONF_H_ */
