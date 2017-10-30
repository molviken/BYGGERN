/*
 * Node2.c
 *
 * Created: 23.10.2017 08:32:38
 *  Author: oystmol
 */ 
#define __Atmega2560__

#include "uart.h"
#include "SPI.h"
#include "MCPkontroll.h"
#include "CAN_bus.h"
#include "adc.h"
#include "fonts.h"
#include "joystick_can.h"
#include "joystick.h"
#include "MCP2515.h"
#include <avr/io.h>

int main(void)
{
	USART_Init(103);
	DDRB = 0b00000000;
	CAN_init();
	struct CAN_message copy_message;
	
	while(1) {
		copy_message = CAN_receive();
		
		printf("X: %i	Y: %i	 \n",copy_message.data[0], copy_message.data[1]);
		_delay_ms(100);
	}
}