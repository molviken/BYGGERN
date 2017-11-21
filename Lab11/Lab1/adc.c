/*
 * adc.c
 *
 * Created: 18.09.2017 11:31:37
 *  Author: oystmol
 */ 

#include <string.h>
#include <avr/io.h>
#include <util/delay.h>
#include "bit_operations.h"
#include "adc.h"

void adc_init(void){
	set_bit(MCUCR,SRE);
	set_bit(SFIOR,XMM2);
	clear_bit(DDRE,DDE0);
}

uint8_t adc_read(uint8_t channel){
	
	volatile char* adc_adr = (char *) 0x1400;
	adc_adr[0] = channel;
	_delay_us(200);
	volatile uint8_t retreived_value = adc_adr[channel];
	return retreived_value;
	
}
