/*
 * Lab1.c
 *
 * Created: 04.09.2017 09:14:12
 *  Author: oystmol
 */ 

#define set_bit( reg, bit ) (reg |= (1 << bit));
#define clear_bit( reg, bit ) (reg &= ~(1 << bit));
#define test_bit( reg, bit ) (reg & (1 << bit));
#define loop_until_bit_is_set( reg, bit ) while( !test_bit( reg, bit ) );
#define loop_until_bit_is_clear( reg, bit ) while( test_bit( reg, bit ) );
#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/sleep.h>

int main(void)
{
    while(1)
    {
        //TODO:: Please write your application code 
		
		DDRA |= (1<<0);
		PORTA |= (1<<PA0);

		// Buttons input (the whole port)
		/*DDRA = 0;
		// Leds output (the whole port)
		DDRB = 0xFF;
		*/
	}
}