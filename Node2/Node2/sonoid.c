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


struct Sonoid sonoid_fire(struct Sonoid shooter){
	
	if (shooter.fire == 1 && shooter.can_shoot){
		printf("FIRING!!!! \n");
		set_bit(PORTB,PB4);	
		shooter.can_shoot = 1;	
	}
	else if (!shooter.fire){
		clear_bit(PORTB,PB4);
		shooter.can_shoot = 0;
	}
	return shooter;
}