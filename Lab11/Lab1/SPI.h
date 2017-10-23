/*
 * SPI.h
 *
 * Created: 02.10.2017 10:40:55
 *  Author: arefv
 */ 
#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/sleep.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

void SPI_MasterInit(void);
void SPI_MasterTransmit(char cData);
char SPI_MasterReceive(void);