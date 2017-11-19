/*
 * joystick.c
 *
 * Created: 25.09.2017 15:20:44
 *  Author: oystmol
 */ 
#include <util/delay.h>
#define set_bit( reg, bit ) (reg |= (1 << bit))
#define clear_bit( reg, bit ) (reg &= ~(1 << bit))
#define test_bit( reg, bit ) (reg & (1 << bit))
#define loop_until_bit_is_set( reg, bit ) while( !test_bit( reg, bit ) )
#define loop_until_bit_is_clear( reg, bit ) while( test_bit( reg, bit ) )
#include "joystick.h"
#include "adc.h"
#include <stdbool.h>
struct Menu_position pos;
struct Joystick read_joystick_position(uint8_t channel_one, uint8_t channel_two){
	int x_pos = (adc_read(channel_two));//-134)*0.8264462809917355;
	int y_pos = (adc_read(channel_one));//-133)*0.819672131147541;

	if (y_pos < 0) {y_pos = 0;}
	if (x_pos < 0) {x_pos = 0;}
	//if (y_pos > 255) {y_pos = 255;}
	//if (x_pos > 255) {x_pos = 255;}
	struct Joystick global_joystick;
	global_joystick.x_pos = x_pos;
	global_joystick.y_pos = y_pos;
	//printf("X: %i, Y: %i \n", x_pos,y_pos);

	return global_joystick;
}
struct Slider read_slider_position(uint8_t channel_one, uint8_t channel_two){
	int slider1 = adc_read(channel_one);
	//_delay_ms(100);
	int slider2 = adc_read(channel_two);
	struct Slider global_slider;
	global_slider.slider1 = slider1;
	global_slider.slider2 = slider2;
	return global_slider;
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

struct Slider get_slider_pos(){
	struct Slider temp;
	temp = read_slider_position(channel3,channel4);
	return temp;
}
struct Joystick get_joy_pos(){
	struct Joystick temp;
	temp = read_joystick_position(channel1,channel2);
	return temp;
}

int sonoid_button(){
	if (!test_bit(PINB,PB2)){
		return 1;
	}
	else{
		return 0;
	}
}