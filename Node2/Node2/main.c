/*
 * Node2.c
 *
 * Created: 23.10.2017 08:32:38
 *  Author: oystmol
 */ 
#include "uart.h"
#include "SPI.h"
#include "MCPkontroll.h"
#include "CAN_bus.h"


#include <avr/io.h>

int main(void)
{
	USART_Init(31);
	SPI_MasterInit();
	CAN_init();
    while(1)
    {
        //TODO:: Please write your application code 
    }
}