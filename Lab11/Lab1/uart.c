#include <avr/io.h>
#include "uart.h"
#include <stdlib.h>
#include "bit_operations.h"



void EXT_MEM_Init(void){
	set_bit(MCUCR,SRE);
	set_bit(SFIOR,XMM2);
	//set_bit(SFIOR,XMM0);
}
void USART_Init( unsigned int ubrr){
	// Set baud rate
	UBRR0H = (unsigned char) (ubrr>>8);
	UBRR0L = (unsigned char) ubrr;
	
	// Enable receiver and transmitter	
	UCSR0B = (1<<TXEN0)|(1<<RXEN0);
	fdevopen(USART_Transmit,USART_Receive);
	// Set frame format: 8data, 2stop bit
	//UCSR0C |= (1<<URSEL0)|(1<<USBS0)|(3<<UCSZ00);
}

void USART_Transmit( unsigned char data ){

	// Wait for empty transmit buffer
	while(!(UCSR0A & (1<<UDRE0)));
  
	//Put data into buffer, sends the data
	UDR0 = data;
}

unsigned char USART_Receive( void ){

	//Wait for data to be received
	while ( !(UCSR0A & (1<<RXC0)) );
	//Get and return received data from buffer
	return UDR0;
}

void timer_setup(){
	// setting up timer 1
	set_bit(TCCR1B, CS11);	//Prescalar 8
	set_bit(TCCR1B, WGM12); //Set CTC mode, TOP at OCR3A
	
	OCR1B = 10000;
}