/*
 * adc.c
 *
 * Created: 18.09.2017 11:31:37
 *  Author: oystmol
 */ 
#define set_bit( reg, bit ) (reg |= (1 << bit))
#define clear_bit( reg, bit ) (reg &= ~(1 << bit))
#define test_bit( reg, bit ) (reg & (1 << bit))
#define loop_until_bit_is_set( reg, bit ) while( !test_bit( reg, bit ) )
#define loop_until_bit_is_clear( reg, bit ) while( test_bit( reg, bit ) )
#include "adc.h"
#include <string.h>
#include "uart.h"
#include <avr/io.h>
#include <util/delay.h>

//void adc_init(void){
	//set_bit(MCUCR,SRE);
	//set_bit(SFIOR,XMM2);
	//clear_bit(DDRE,DDE0);
//}

uint8_t adc_read(uint8_t channel){
	
	volatile char* adc_adr = (char *) 0x1400;
	adc_adr[0] = channel;
	_delay_us(200);
	volatile uint8_t retreived_value = adc_adr[channel];
	return retreived_value;
	
}
