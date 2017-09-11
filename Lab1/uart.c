#include <avr/io.h>
#include "uart.h"
#include <stdlib.h>

//void EXT_MEM_Init(void){
	//set_bit(MCUCR,SRE);
	//set_bit(SFIOR,XMM2);
	////set_bit(SFIOR,XMM0);
//}
void USART_Init( unsigned int ubrr){
	// Set baud rate
	UBRR0H = (unsigned char) (ubrr>>8);
	UBRR0L = (unsigned char) ubrr;
	
	/* Enable receiver and transmitter	*/
	UCSR0B = (1<<TXEN0)|(1<<RXEN0);
	fdevopen(USART_Transmit,USART_Receive);
	// Set frame format: 8data, 2stop bit
	//UCSR0C |= (1<<URSEL0)|(1<<USBS0)|(3<<UCSZ00);
}

void USART_Transmit( unsigned char data ){

// Wait for empty transmit buffer
	while( !( UCSR0A & (1<<UDRE0)) );
  
//Put data into buffer, sends the data
	UDR0 = data;
}

unsigned char USART_Receive( void ){

//Wait for data to be received
	while ( !(UCSR0A & (1<<RXC0)) );
//Get and return received data from buffer
	return UDR0;
}

//void SRAM_test(void)
//{
	//volatile char *ext_ram = (char *) 0x1800; // Start address for the SRAM
	//uint16_t ext_ram_size	= 0x100;
	//uint16_t write_errors	= 0;
	//uint16_t retrieval_errors	= 0;
//
	//printf("Starting SRAM test...\n");
	//// rand() stores some internal state, so calling this function in a loop will
	//// yield different seeds each time (unless srand() is called before this function)
	//uint16_t seed = rand();
	//// Write phase: Immediately check that the correct value was stored
	//srand(seed);
	//for (uint16_t i = 0; i < ext_ram_size; i++) {
		//uint8_t some_value = rand();
		//ext_ram[i] = some_value;
		//uint8_t retreived_value = ext_ram[i];
		//if (retreived_value != some_value) {
			//printf("Write phase error: ext_ram[%4d] = %02X (should be %02X)\n", i,	retreived_value, some_value);
			//write_errors++;
		//}
	//}
	//// Retrieval phase: Check that no values were changed during or after the write phase
	//srand(seed);
	//// reset the PRNG to the state it had before the write phase
	//for (uint16_t i = 0; i < ext_ram_size; i++) {
		//uint8_t some_value = rand();
		//uint8_t retreived_value = ext_ram[i];
		//if (retreived_value != some_value) {
			//printf("Retrieval phase error: ext_ram[%4d] = %02X (should be %02X)\n",	i, retreived_value, some_value);
			//retrieval_errors++;
		//}
	//}
	//printf("SRAM test completed with\n%4d errors in write phase and\n%4d errors	in retrieval phase\n\n", write_errors, retrieval_errors);
//}