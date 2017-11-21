/*
 * shooter.c
 *
 * Created: 16.11.2017 17:40:21
 *  Author: oystmol
 */ 
#include <avr/io.h>
#include <stdlib.h>
#include "sonoid.h"
#include "bit_operations.h"


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