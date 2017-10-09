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
#include "CAN_bus.h"
#include "MCPkontroll.h"
volatile char* oled_adresse = 0x1200;
volatile char* adc_adresse = 0x1400;
volatile char* ram_adresse = 0x1800;
int main(void)
{

	DDRB = 0b00000000;
	adc_init();
	//CAN_init();
	//CAN_int_vect();
	EXT_MEM_Init();
    USART_Init(31);
	oled_init();
	oled_reset();
	oled_print("Meny1 Meny2 Meny3 Meny4 Meny5");
	initialize_menu();
	MCP_init();
	printf("Init er good\n");
	
	/*
	struct CAN_message first_message;
	first_message.id = 0b10110010;
	first_message.data[0] = 0xFF;
	CAN_transmit(first_message);
	
	struct CAN_message copy_message;
	copy_message = CAN_receive();
	printf("first message id = %x", first_message.id); 
	printf("copy message id = %x \n", copy_message.id);
	printf("first message data[0] = %x", first_message.data[0]) 
	printf("copy message data[0} = %x \n", copy_message.data[0]);*/
	
	
	uint8_t data = 0x55;
	MCP_write(data, 0b00110110);
	
	uint8_t test = MCP_read(0b00110110);
	printf("data = %d data lest = %d \n\n",data, test);
	while(1)
    {
		
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