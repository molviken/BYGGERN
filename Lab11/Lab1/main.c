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
#include "menu_system.h"
volatile char* oled_adresse = 0x1200;
volatile char* adc_adresse = 0x1400;
volatile char* ram_adresse = 0x1800;
int main(void)
{
	DDRB = 0b00000000;

	EXT_MEM_Init();
	USART_Init(31);				
	oled_init();
	oled_reset();
	adc_init();
	CAN_init();
	//menu_system();
	menu_initialize();
	printf("Init er good\n");
	//SRAM_test();
	//printf("Init er GOOD\n");
	struct CAN_message usb_board;
	usb_board.id = 3;
	usb_board.length = 4;
	oled_reset();
	//oled_print_letter("K",0x01,0x09,0x11);
	menu_create();

	while(1)
    {
		menu_nav();	
		usb_board.data[0] = (uint8_t)read_joystick_position(channel1, channel2).x_pos;
		usb_board.data[1] = (uint8_t)read_joystick_position(channel1, channel2).y_pos;
		usb_board.data[2] = (uint8_t)read_slider_position(channel3,channel4).slider1;
		usb_board.data[3] = (uint8_t)read_slider_position(channel3,channel4).slider2;
		//usb_board.data[4] = (int)sonoid_button();
		//printf("x pos: %d		slider right: %d		Sonoid: %i \n", usb_board.data[0],usb_board.data[3], usb_board.data[4]);
		
		CAN_transmit(usb_board);
	
		//printf("Status:  %i \n", status);

		//slider_button();
		//joystick_pressed();
		//joystick_navigate_vertical();
	}
}