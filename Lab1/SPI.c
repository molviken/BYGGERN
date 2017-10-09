/*
 * SPI.c
 *
 * Created: 02.10.2017 10:40:42
 *  Author: arefv
 */ 
#define DD_MOSI PB5
#define DD_SCK PB7
#define DD_MISO PB6
#define DD_SS PB4
#include "SPI.h"

void SPI_MasterInit(void)
{
	/* Set MOSI and SCK output, all others input */
	DDRB = (1<<DD_MOSI)|(1<<DD_SCK);
	
	/* Enable SPI, Master, set clock rate fck/16 */
	SPCR = (1<<SPE)|(1<<MSTR)|(1<<SPR0);
}
void SPI_MasterTransmit(char cData){
	/* Start transmission */
	SPDR = cData;
	
	/* Wait for transmission complete */
	while	(!(SPSR & (1<<SPIF)));
}

char SPI_MasterReceive(void)
{
	/* Wait for reception complete */
	SPI_MasterTransmit(0);
	while	(!(SPSR & (1<<SPIF)));
	/* Return data register */
	
	return	SPDR;
}
