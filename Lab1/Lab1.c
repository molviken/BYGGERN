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
volatile char* oled_adresse = 0x1200;
volatile char* adc_adresse = 0x1400;
volatile char* ram_adresse = 0x1800;
int main(void)
{
	DDRB = 0b00000000;
	adc_init();
	EXT_MEM_Init();
    USART_Init(31);
	//SRAM_test();
	//printf("Hei det funker enda\n");
	printf("noe funker hvertfall");
	while(1)
    {
		struct Joystick temp = read_joystick_position(channel1,channel2);
		struct Slider temp2 = read_slider_position(channel3,channel4);
		//printf("slider1: %i, slider2: %i \n",temp2.slider1,temp2.slider2);
		//printf("X pos: %i, Y pos: %i \n",temp.x_pos,temp.y_pos);
		//read_slider_position(channel3,channel4);
		//read_joystick_position(channel1,channel2);
		//adc_read(channel2);
	}
}