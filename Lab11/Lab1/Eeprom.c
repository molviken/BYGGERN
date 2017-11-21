/*
 * CFile1.c
 *
 * Created: 21.11.2017 06:39:14
 *  Author: arefv
 */ 
#include "Eeprom.h"

void EEPROM_write(uint8_t uiAddress, uint8_t ucData){
	/* 
	Wait for completion of previous write
	 */
	while(EECR & (1<<EEWE)){}

	
	/* Set up address and data registers */
	EEAR = uiAddress;
	EEDR = ucData;
	/* 
	Write logical one to EEMWE */
	EECR |= (1<<EEMWE);


	/* Start eeprom write by setting EEWE */
	EECR |= (1<<EEWE);
}

char* EEPROM_read(uint8_t uiAddress){
	/* Wait for completion of previous write */
	while(EECR & (1<<EEWE)){
		
	}
	/* Set up address register */
	EEAR = uiAddress;
	/*
	Start eeprom read by writing EERE */
	EECR |= (1<<EERE);
	/* Return data from data register */
	return EEDR;
}