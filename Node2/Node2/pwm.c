
#include <avr/io.h>
#include <stdlib.h>
#include <avr/interrupt.h>
#include "bit_operations.h"
#include "pwm.h"


void pwm_setup(void){
	
	// Setter compare match mode for fast pwm
	set_bit(TCCR1A, COM1B1);
	set_bit(DDRB, PB6);
	
	
	// Setter prescaler til 8
	set_bit(TCCR1B, CS11);		
	
	// Enabler fast pwm mode
	set_bit(TCCR1A, WGM11);		
	set_bit(TCCR1B, WGM12);
	set_bit(TCCR1B, WGM13);
	
	// Setter pulsbredden 1.5ms (1.5/20)*39999
	OCR1B = 3000;
	
	// Definerer PWM perioden på 20 ms 
	ICR1 = 39999;
	
	// Tillater timer compare interrupt
	//set_bit(TIMSK1, OCIE1A); 
	
	//sei();
}	


int PWM_set_puls_width(double angle){
	
	if (angle >= 2000 && angle <= 4002){
		angle = 6001 - angle; // Inverting control
		OCR1B = angle;
	}
	return 0;
}

double PWM_control(uint8_t x_pos){
	return PWM_set_puls_width((x_pos*7.85+2000));
}