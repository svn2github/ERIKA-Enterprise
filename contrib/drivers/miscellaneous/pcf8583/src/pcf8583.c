/** 
* @file pcf8583.c
* @brief PCF8583 real time clock driver
* @author Dario Di Stefano 
* @date 2010-08-30
*/

#include "pcf8583.h"
#include "pcf8583_hal.h"


int EE_rtc_write_time(const TTime *ttw)
{
	uint8_t tx_data[7];
	
	/* Turn off rt-clock and change the time */					
   	tx_data[0] = RTC_OFF;
   	tx_data[1] = ((ttw->hundredths/10)<<4) + (ttw->hundredths%10);
   	tx_data[2] = ((ttw->seconds/10)<<4) + (ttw->seconds%10);
   	tx_data[3] = ((ttw->minutes/10)<<4) + (ttw->minutes%10);
   	tx_data[4] = ((ttw->hours/10)<<4) + (ttw->hours%10);
   	tx_data[5] = ((ttw->year%4)<<6) + ((ttw->day/10)<<4) +(ttw->day%10);
   	tx_data[6] = ((ttw->month/10)<<4) + (ttw->month%10);
	
   	EE_rtc_write_buffer(RTC_CSR_ADD, tx_data, 7);
	
   	/* Save year in RAM */		
	EE_rtc_write_byte(RTC_YEAR_ADD, ttw->year);						
   	/* Turn on rt-clock */	
	EE_rtc_write_byte(RTC_CSR_ADD, RTC_ON);		
	
	return RTC_NO_ERROR;
}

int EE_rtc_read_time(TTime *ttr) 
{
	uint8_t rx_data[7];
	int8_t yearmod4, diff;
	
	/* Read the time */			
   	EE_rtc_read_buffer(RTC_HSECONDS_ADD, rx_data, 6);	
   	
	ttr->hundredths = (rx_data[0] >> 4)*10 + (rx_data[0] & 0x0F); 
	ttr->seconds = (rx_data[1] >> 4)*10 + (rx_data[1] & 0x0F); 
	ttr->minutes = (rx_data[2] >> 4)*10 + (rx_data[2] & 0x0F); 
	ttr->hours = (rx_data[3] >> 4)*10 + (rx_data[3] & 0x0F); 
	ttr->day = ((rx_data[4] & 0b00110000) >> 4)*10 + (rx_data[4] & 0x0F); 
	yearmod4 = (rx_data[4] & 0b11000000) >> 6;        	
	ttr->month = ((rx_data[5] & 0b00010000) >> 4)*10 + (rx_data[5] & 0x0F);
 	
	/* Read the year stored in the rt-clock RAM */	
	rx_data[0] = EE_rtc_read_byte(RTC_YEAR_ADD);	
	if(rx_data[0] >= 0){
		diff = yearmod4 - (rx_data[0] & 0x03);	// Calculate the difference (3,2,1,0,-1,-2,-3)
		if (diff!=0 )  							// check if year is changed in RTC
		{										// in this case the new value should be written to RTC RAM at address 16(0x10)  	
			ttr->year = rx_data[0] + ((diff+4) & 0x03);			
			EE_rtc_write_byte(RTC_YEAR_ADD, ttr->year);	
		}
		else
		{
			ttr->year = rx_data[0];	
		}	
	}	
  		
   	return RTC_NO_ERROR;
}



