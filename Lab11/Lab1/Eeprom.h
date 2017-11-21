/*
 * IncFile1.h
 *
 * Created: 21.11.2017 06:49:46
 *  Author: arefv
 */ 


#ifndef EEPROM_H_
#define EEPROM_H_
#include <avr/io.h>

void EEPROM_write(uint8_t uiAddress, uint8_t ucData);
char* EEPROM_read(uint8_t uiAddress);
#endif /* INCFILE1_H_ */