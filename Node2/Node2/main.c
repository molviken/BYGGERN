/*
 * Node2.c
 *
 * Created: 23.10.2017 08:32:38
 *  Author: oystmol
 */ 
#include "../../delte filer/uart.h"
#include "../../delte filer/SPI.h"
#include "../../delte filer/MCPkontroll.h"
#include "../../delte filer/CAN_bus.h"
#include "../../delte filer/adc.h"
#include "../../delte filer/fonts.h"
#include "../../delte filer/joystick_can.h"
#include "../../delte filer/joystick.h"
#include "../../delte filer/MCP2515.h"
#include <avr/io.h>

int main(void)
{
	USART_Init(103);
	SPI_MasterInit();
	CAN_init();
	//while (!USART_Receive());
	struct CAN_message copy_message;
	while(1) {
		received_joy_pos();
	}
}