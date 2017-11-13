/*
 * dag.h
 *
 * Created: 13.11.2017 10:46:09
 *  Author: oystmol
 */ 
#define set_bit( reg, bit ) (reg |= (1 << bit))
#define clear_bit( reg, bit ) (reg &= ~(1 << bit))
#include <avr/io.h>
#include <util/delay.h>
#include <stdlib.h>
void dac_init();
void dac_write(uint8_t value);