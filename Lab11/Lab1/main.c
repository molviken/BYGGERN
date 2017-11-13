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
#include "adc.h"
#include "oled.h"
#include "joystick.h"
#include "SPI.h"
#include "MCPkontroll.h"
#include "CAN_bus.h"
#include "MCP2515.h"


volatile char* oled_adresse = 0x1200;
volatile char* adc_adresse = 0x1400;
volatile char* ram_adresse = 0x1800;
int main(void)
{
	EXT_MEM_Init();
	USART_Init(31);
	oled_init();
	oled_reset();
	adc_init();
	initialize_menu();
	DDRB = 0b00000000;
	CAN_init();
	printf("Init er GOOD\n");
	struct CAN_message usb_board;
	usb_board.id = 3;
	usb_board.length = 4;
	

	while(1)
    {
		//struct Joystick temp = read_joystick_position(channel1,channel2);

		usb_board.data[0] = (uint8_t)read_joystick_position(channel1, channel2).x_pos;
		usb_board.data[1] = (uint8_t)read_joystick_position(channel1, channel2).y_pos;
		usb_board.data[2] = (uint8_t)read_slider_position(channel3,channel4).slider1;
		usb_board.data[3] = (uint8_t)read_slider_position(channel3,channel4).slider2;
		printf("x pos: %d		slider right: %d \n", usb_board.data[0],usb_board.data[3]);
		int status = CAN_transmit(usb_board);
		//printf("Status:  %i \n", status);

		//slider_button();
		//joystick_pressed();
		//joystick_navigate_vertical();
		_delay_ms(100);
	}
}