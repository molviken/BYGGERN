/*
 * joystick.c
 *
 * Created: 25.09.2017 15:20:44
 *  Author: oystmol
 */ 
#include <util/delay.h>
#include <avr/io.h>
#include <stdbool.h>
#include "bit_operations.h"
#include "usb_board_inputs.h"
#include "adc.h"



struct Menu_position pos;
struct Joystick read_joystick_position(uint8_t channel_one, uint8_t channel_two){
	int x_pos = (adc_read(channel_two));
	int y_pos = (adc_read(channel_one));

	if (y_pos < 0) {y_pos = 0;}
	if (x_pos < 0) {x_pos = 0;}
	//if (y_pos > 255) {y_pos = 255;}
	//if (x_pos > 255) {x_pos = 255;}
	struct Joystick temp;
	temp.x_pos = x_pos;
	temp.y_pos = y_pos;

	return temp;
}
struct Slider read_slider_position(uint8_t channel_one, uint8_t channel_two){
	int slider1 = adc_read(channel_one);
	//_delay_ms(100);
	int slider2 = adc_read(channel_two);
	struct Slider temp;
	temp.slider1 = slider1;
	temp.slider2 = slider2;
	return temp;
	//printf("Slider 1: %i, Slider 2: %i \n", slider1,slider2);
}
uint8_t joystick_pressed(){
	if (!test_bit(PINB,PB2)){
		pos.pressed1 = true;
	}
	if (test_bit(PINB,PB2) && pos.pressed1){
		//printf("Joystick\n");
		pos.pressed1 = false;
		return pos.current_page;
	}
}
uint8_t slider_button(){
	if (!test_bit(PINB,PB1)){
		pos.pressed2 = true;
	}
	if (!test_bit(PINB,PB0)){
		pos.pressed1 = true;
	}
	if (test_bit(PINB,PB1) && pos.pressed2){
		//printf("Slider 2\n");
		pos.pressed2 = false;
		//printf("Current page is: %x \n ", pos.current_page);
		return pos.current_page;
	}
	if (test_bit(PINB,PB0) && pos.pressed1){
		//printf("Slider 1\n");
		pos.pressed1 = false;
		//printf("Current page is: %x \n ", pos.current_page);
		return pos.current_page;
	}
}

int sonoid_button(){
	if (!test_bit(PINB,PB2)){
		return 1;
	}
	else{
		return 0;
	}
}