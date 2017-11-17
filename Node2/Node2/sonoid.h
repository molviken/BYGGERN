/*
 * sonoid.h
 *
 * Created: 16.11.2017 17:40:49
 *  Author: oystmol
 */ 

struct Sonoid {
	int can_shoot;
	int fire;
	};

#include <avr/io.h>
#include <util/delay.h>
struct Sonoid sonoid_fire(struct Sonoid shooter);