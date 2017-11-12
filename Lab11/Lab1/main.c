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
	struct CAN_message test;
	test.id = 3;
	test.length = 2;
	test.data[0] = 0x22;
	test.data[1] = 0x69;
	
	//struct CAN_message copy_message;
	//test = joy_message_init();
	while(1)
    {
		struct Joystick temp = read_joystick_position(channel1,channel2);
		//test.data[0] = 22;
		//test.data[1] = 69;
		test.data[0] = (uint8_t)read_joystick_position(channel1, channel2).x_pos;
		test.data[1] = (uint8_t)read_joystick_position(channel1, channel2).y_pos;
		int status = CAN_transmit(test);
		//printf("Status:  %i \n", status);
		//send_joy_pos();
		//copy_message = CAN_receive();
		//printf("data 1: %x, data 2: %x   , ID: %x     , length: %x \n",copy_message.data[0], copy_message.data[1], copy_message.id, copy_message.length);	
		
		//printf("%x,   %x \n", test.data[0], test.data[1]);
		//CAN_transmit(test);
		//slider_button();
		//joystick_pressed();
		//joystick_navigate_vertical();
		
		//struct Slider temp2 = read_slider_position(channel3,channel4);
		//printf("slider1: %i, slider2: %i \n",temp2.slider1,temp2.slider2);
		printf("X pos: %i, Y pos: %i \n",temp.x_pos,temp.y_pos);
		_delay_ms(100);
	}
}