/*
 * pid.h
 *
 * Created: 16.11.2017 20:49:47
 *  Author: oystmol
 */ 
#define F_CPU 16000000
#include <avr/io.h>
#include <util/delay.h>
#define set_bit( reg, bit ) (reg |= (1 << bit))
#define clear_bit( reg, bit ) (reg &= ~(1 << bit))

void PItimer_setup();
void PI_regulator(uint8_t position);
void pid_init();
struct PI_reg{
	int16_t r, y, e, u;
};