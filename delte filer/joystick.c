/*
 * joystick.c
 *
 * Created: 25.09.2017 15:20:44
 *  Author: oystmol
 */ 
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
	int x_pos = (adc_read(channel_two)-134)*0.8264462809917355;
	int y_pos = (adc_read(channel_one)-133)*0.819672131147541;

	if (y_pos < -100) {y_pos = -100;}
	if (x_pos < -100) {x_pos = -100;}
	struct Joystick global_joystick;
	global_joystick.x_pos = x_pos;
	global_joystick.y_pos = y_pos;
	//printf("X: %i, Y: %i \n", x_pos,y_pos);

	return global_joystick;
}
struct Slider read_slider_position(uint8_t channel_one, uint8_t channel_two){
	int slider1 = adc_read(channel_one)*0.392156862745098;
	int slider2 = adc_read(channel_two)*0.392156862745098;
	struct Slider global_slider;
	global_slider.slider1 = slider1;
	global_slider.slider2 = slider2;
	return global_slider;
	//printf("Slider 1: %i, Slider 2: %i \n", slider1,slider2);
}

void joystick_navigate_vertical(){
	struct Joystick global_joystick = read_joystick_position(channel1,channel2);
	int y_pos = global_joystick.y_pos;	
	if(y_pos < 90 && y_pos > -90){
		pos.move = true;
	}
	else if(y_pos < -90 && pos.move){
		pos.move = false;
		pos.prev_page = pos.current_page;
		pos.current_page += 0x01;
		if(pos.current_page > 0x05){
			pos.current_page = 0x01;
		}
		oled_print_letter(' ',pos.prev_page,0x00,0x08);
		oled_print_letter('#',pos.current_page,0x00,0x08);
	}
	else if(y_pos > 90 && pos.move){
		
		pos.move = false;
		pos.prev_page = pos.current_page;
		pos.current_page -= 0x01;
		if(pos.current_page < 0x01){
			pos.current_page = 0x05;
		}
		oled_print_letter(' ',pos.prev_page,0x00,0x08);
		oled_print_letter('#',pos.current_page,0x00,0x08);
	}
}

uint8_t joystick_pressed(){
	if (!test_bit(PINB,PB2)){
		pos.pressed1 = true;
	}
	if (test_bit(PINB,PB2) && pos.pressed1){
		printf("Joystick\n");
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
		printf("Current page is: %x \n ", pos.current_page);
		return pos.current_page;
	}
	if (test_bit(PINB,PB0) && pos.pressed1){
		//printf("Slider 1\n");
		pos.pressed1 = false;
		printf("Current page is: %x \n ", pos.current_page);
		return pos.current_page;
	}
}
