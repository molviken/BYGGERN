/*
 * Lab1.c
 *
 * Created: 04.09.2017 09:14:12
 *  Author: oystmol
 */ 


#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/sleep.h>
#include "uart.h"

int main(void)
{
	
	EXT_MEM_Init();
    USART_Init(31);
	SRAM_test();
	//printf("Hei det funker enda\n");
	//set_bit(PORTA, PA0);
	//set_bit(PORTA, PA1);
	//set_bit(PORTA, PA2);
	//set_bit(PORTA, PA3);
	//set_bit(PORTA, PA4);
	//set_bit(PORTA, PA5);
	//set_bit(PORTA, PA6);
	//set_bit(PORTA, PA7);
	//set_bit(PORTE, PE1);
	while(1)
    {
		//USART_Transmit(USART_Receive());
        //TODO:: Please write your application code 
		


		// Buttons input (the whole port)
		/*DDRA = 0;
		// Leds output (the whole port)
		DDRB = 0xFF;
		*/
	}
}