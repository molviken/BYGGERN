/*
 * adc.c
 *
 * Created: 06.11.2017 15:51:31
 *  Author: oystmol
 */ 
//#include "libarduino.c"
//#include <rtm.h>
#define set_bit( reg, bit ) (reg |= (1 << bit))
#define clear_bit( reg, bit ) (reg &= ~(1 << bit))
#include <avr/io.h>
#include "adc_node2.h"
int ADC_ready = 0;

void adc_node2_init(void) {
	//Use AVCC as reference, result left adjusted
	ADMUX |= (1 << REFS0) | (1 << REFS1);
	
	//Use channel 0
	ADMUX &= ~(1 << MUX4) & ~(1 << MUX3) & ~(1 << MUX2) & ~(1 << MUX1) & ~(1 << MUX0);

	//Enable ADC
	set_bit(ADCSRA, ADEN);
	//Set prescalar 128
	set_bit(ADCSRA, ADPS2);
	set_bit(ADCSRA, ADPS1);
	set_bit(ADCSRA, ADPS0);
	//Enable interrupt
	set_bit(ADCSRA, ADIE);

	clear_bit(DDRF,PF0);


}

uint16_t ADC_node2_read(void) {
	//Start the ADC
	ADCSRA |= (1 << ADSC);
	while (!ADC_ready){
		ADC_ready = 0;
		uint16_t data = ADCL | ADCH << 8;
		return data;
	}
	
	
}
//
//void ADC_node2_stop(void) {
	////Stop the ADC
	//ADCSRA &= ~(1 << ADEN);
//}

ISR(ADC_vect){
	ADC_ready = 1;
}