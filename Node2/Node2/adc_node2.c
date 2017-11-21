

#define F_CPU 16000000
#include <avr/io.h>
#include <util/delay.h>
#include "adc_node2.h"
#include "bit_operations.h"


int ADC_ready = 0;

void adc_node2_switch(int channel){
	//Use channel 1
	switch(channel){
		case 0:
		ADMUX &= ~(1 << MUX4) & ~(1 << MUX3) & ~(1 << MUX2) & ~(1 << MUX1) & ~(1 << MUX0);
		set_bit(PINF,PF1);
		clear_bit(PINF,PF0);
		break;
		
		case 1:
		ADMUX &= ~(1 << MUX4) & ~(1 << MUX3) & ~(1 << MUX2) & ~(1 << MUX1);
		set_bit(ADMUX, MUX0);
		set_bit(PINF,PF0);
		clear_bit(PINF,PF1);
		break;

		default:
		break;
	}
}

void adc_node2_init(void) {
	//Use AVCC as reference, result left adjusted
	ADMUX |= (1 << REFS0) | (1 << REFS1);
	// Use channel 0
	ADMUX &= ~(1 << MUX4) & ~(1 << MUX3) & ~(1 << MUX2) & ~(1 << MUX1) & ~(1 << MUX0);
	//Enable ADC
	set_bit(ADCSRA, ADEN);
	//Set prescalar 128
	set_bit(ADCSRA, ADPS2);
	set_bit(ADCSRA, ADPS1);
	set_bit(ADCSRA, ADPS0);
	//Enable interrupt
	//set_bit(ADCSRA, ADIE);
	// input pins on arduino
	clear_bit(DDRF,PF0);



}

uint16_t adc_node2_read(void) {
	//Start the ADC
	ADCSRA |= (1 << ADSC);
	_delay_us(50);
	ADC_ready = 0;
	uint16_t data = ADCL | ADCH << 8;
	return data;
	
	
}

/*
ISR(ADC_vect){
	ADC_ready = 1;
}*/