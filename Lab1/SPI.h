/*
 * SPI.h
 *
 * Created: 02.10.2017 10:40:55
 *  Author: arefv
 */ 
void SPI_MasterInit(void);
void SPI_MasterTransmit(char cData);
char SPI_MasterReceive(void);