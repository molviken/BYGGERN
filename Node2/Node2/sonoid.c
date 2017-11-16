/*
 * shooter.c
 *
 * Created: 16.11.2017 17:40:21
 *  Author: oystmol
 */ 
#define F_CPU 16000000
#include <avr/io.h>
#include <util/delay.h>
#include "sonoid.h"
#define set_bit( reg, bit ) (reg |= (1 << bit))
#define clear_bit( reg, bit ) (reg &= ~(1 << bit))

void sonoid_init(){
	clear_bit(DDRB,PB4);
	clear_bit(PORTB, PB4);
	
	set_bit(DDRB, PB4);
	set_bit(PORTB, PB4);
	
	set_bit(TCCR2B,CS22);
	set_bit(TCCR2A, CS20);
	
	clear_bit(PORTB, PB4);
	TCNT2 = 0; //timer to 0
	int i = 0;
	while (i<20){
		if(TCNT2 > 100){
			i++;
			TCNT2 = 0;
		}
	}
	//set_bit(PORTB,PB4);
}

void sonoid_fire(int fire){
	clear_bit(PORTB, PB4);
	if (fire == 1){
		//printf("FIRING!!!! \n");
		set_bit(PORTB,PB4);	
		_delay_ms(150);	
	}
	else{
		clear_bit(PORTB,PB4);
	}
}