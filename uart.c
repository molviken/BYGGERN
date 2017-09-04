#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/sleep.h>
#include <stdio.h>

#define FOSC 1843200// Clock Speed
#define BAUD 9600
#define MYUBRR FOSC/16/BAUD-

void USART_Init( unsigned int ubrr){
	// Set baud rate
	UBRRH = (usnigned char) (ubrr>>8);
	UBBRL = (usnigned char) ubrr;
	
	/* Enable receiver and transmitter	*/
	UCSRB = (1<<RXEN)|(1<<TXEN);
 
	// Set frame format: 8data, 2stop bit
	UCSRC = (1<<URSEL)|(1<<USBS)|(3<<UCSZ0);
}