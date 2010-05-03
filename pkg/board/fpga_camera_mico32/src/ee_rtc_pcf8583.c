/*
	RT-Clock library functions
*/

#ifdef __USE_MICO32BOARD_RTC_PCF8583__

#include "board/fpga_camera_mico32/inc/ee_rtc_pcf8583.h"

/* Global variables */
//...

int EE_rtc_write_time(const TTime *ttw)
{
	int ret;
	EE_UINT8 tx_data[7];
	
	/* Turn off rt-clock and change the time */					
   	tx_data[0] = RTC_OFF;
   	tx_data[1] = ((ttw->hundredths/10)<<4) + (ttw->hundredths%10);
   	tx_data[2] = ((ttw->seconds/10)<<4) + (ttw->seconds%10);
   	tx_data[3] = ((ttw->minutes/10)<<4) + (ttw->minutes%10);
   	tx_data[4] = ((ttw->hours/10)<<4) + (ttw->hours%10);
   	tx_data[5] = ((ttw->year%4)<<6) + ((ttw->day/10)<<4) +(ttw->day%10);
   	tx_data[6] = ((ttw->month/10)<<4) + (ttw->month%10);
   	
   	ret = EE_rtc_write_buffer(RTC_CSR_ADD, tx_data, 7);
   	if(ret == EE_I2C_OK)
   	{
		/* Save year in RAM */		
		ret = EE_rtc_write_byte(RTC_YEAR_ADD, ttw->year);						
   		if(ret == EE_I2C_OK)
   		{
			/* Turn on rt-clock */	
			ret = EE_rtc_write_byte(RTC_CSR_ADD, RTC_ON);		
		}
	}
	
	return ret;
}

int EE_rtc_read_time(TTime *ttr) 
{
	int ret;
	EE_UINT8 rx_data[7];
	EE_INT8 yearmod4, diff;
	
	/* Read the time */			
   	ret = EE_rtc_read_buffer(RTC_HSECONDS_ADD, rx_data, 6);	
   	if(ret == EE_I2C_OK)
   	{
		ttr->hundredths = (rx_data[0] >> 4)*10 + (rx_data[0] & 0x0F); 
   		ttr->seconds = (rx_data[1] >> 4)*10 + (rx_data[1] & 0x0F); 
   		ttr->minutes = (rx_data[2] >> 4)*10 + (rx_data[2] & 0x0F); 
   		ttr->hours = (rx_data[3] >> 4)*10 + (rx_data[3] & 0x0F); 
   		ttr->day = ((rx_data[4] & 0b00110000) >> 4)*10 + (rx_data[4] & 0x0F); 
   		yearmod4 = (rx_data[4] & 0b11000000) >> 6;        	
   		ttr->month = ((rx_data[5] & 0b00010000) >> 4)*10 + (rx_data[5] & 0x0F); 	
		/* Read the year stored in the rt-clock RAM */	
		rx_data[0] = EE_rtc_read_byte(RTC_YEAR_ADD);	
   		if(rx_data[0] >= 0)
   		{
			ret = EE_I2C_OK;
			diff = yearmod4 - (rx_data[0] & 0x03);			// Calculate the difference (3,2,1,0,-1,-2,-3)
			if (diff!=0 )  							// check if year is changed in RTC
   			{										// in this case the new value should be written to RTC RAM at address 16(0x10)  	
				ttr->year = rx_data[0] + ((diff+4) & 0x03);			
   				ret = EE_rtc_write_byte(RTC_YEAR_ADD, ttr->year);	
   			}
   			else
   			{
				ttr->year = rx_data[0];	
			}
   				
		}	
	}
  		
   	return ret;
}

int EE_rtc_set_alarm(void)
{
	// to do...
	return 0;
}

#endif //#ifdef __USE_MICO32BOARD_RTC_PCF8583__
