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
#include "menu_functions.h"
#include "Eeprom.h"
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
//	menu_initialize();
	printf("Init er good\n");
	//struct CAN_message usb_board;
	//usb_board.id = 3;
	//usb_board.length = 4;
	
    // Lager spillet i denne CAN_messagen
    struct CAN_message chosen_game;
    // Velger at hele data arrayet skal kunne brukes.
    chosen_game.length = 8;
    // Setter spillet i default -> survival med slider control
    chosen_game.id = 0x0a;
    chosen_game.data[5] = 1;
    chosen_game.data[6] = 2;
	
	oled_reset();
	
	MENU *main_menu = menu_create();
	//oled_reset();
	printf("reseted\n");
	//oled_print("main1,main2,main3,amin3",0x01,0x09,0x11);
	
	
	//EEPROMTEST
	uint8_t Adr = 0x01;
	uint8_t Data = 0x02;
	EEPROM_write(Adr, Data);
	char* dat = EEPROM_read(Adr);
	printf("data inn %x, data ut %x", Data, dat);
	
	
	
	while(1)
    {
		//main_menu = menu_nav(main_menu);	
		
		
		//usb_board.data[0] = (uint8_t)read_joystick_position(channel1, channel2).x_pos;
		//usb_board.data[1] = (uint8_t)read_joystick_position(channel1, channel2).y_pos;
		//usb_board.data[2] = (uint8_t)read_slider_position(channel3,channel4).slider1;
		//usb_board.data[3] = (uint8_t)read_slider_position(channel3,channel4).slider2;
		//usb_board.data[4] = (int)sonoid_button();
		
		//chosen_game = CAN_receive();
		//CAN_transmit(usb_board);
	}
}