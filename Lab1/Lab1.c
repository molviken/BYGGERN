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
	CAN_int_vect();
	
	printf("Init er good\n");
	
	while(1)
    {
		//MCP_write(0xff, 0x36);

		//slider_button();
		//joystick_pressed();
		//joystick_navigate_vertical();
		//struct Joystick temp = read_joystick_position(channel1,channel2);
		//struct Slider temp2 = read_slider_position(channel3,channel4);
		//printf("slider1: %i, slider2: %i \n",temp2.slider1,temp2.slider2);
		//printf("X pos: %i, Y pos: %i \n",temp.x_pos,temp.y_pos);
		//read_slider_position(channel3,channel4);
		//read_joystick_position(channel1,channel2);
		//adc_read(channel2);
		_delay_ms(100);
	}
}