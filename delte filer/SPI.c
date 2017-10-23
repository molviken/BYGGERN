/*
 * SPI.c
 *
 * Created: 02.10.2017 10:40:42
 *  Author: arefv
 */ 
#ifdef __Atmega2560__
	#define DD_MOSI PB2
	#define DD_SCK PB1
	#define DD_MISO PB3
	#define DD_SS PB7
#else
	#define DD_MOSI PB5
	#define DD_SCK PB7
	#define DD_MISO PB6
	#define DD_SS PB4
#endif

#include "SPI.h"

void SPI_MasterInit(void){
	/* Set MOSI,SCK and SS output, all others input */
	DDRB = (1<<DD_MOSI) | (1<<DD_SCK) | (1 << DD_SS) | (1 << PB0);
	
	/* Enable SPI, Master, set clock rate fck/16 */
	SPCR = (1<<SPE) | (1<<MSTR) | (1<<SPR0);
}
void SPI_MasterTransmit(char cData){
	/* Start transmission */
	SPDR = cData;
	
	/* Wait for transmission complete */
	while	(!(SPSR & (1<<SPIF)));
}

char SPI_MasterReceive(void){
	/* Send dummy data to read from slave */	
	SPI_MasterTransmit(0);
	
	/* Wait for reception complete */
	// while	(!(SPSR & (1<<SPIF)));
	
	/* Return data register */
	return	SPDR;
}