/*
 * joystick.c
 *
 * Created: 25.09.2017 15:20:44
 *  Author: oystmol
 */ 
#include "joystick.h"
#include "oled.h"
#include "adc.h"
#include <stdbool.h>
struct Menu_position pos;
bool move;
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
void initialize_menu(){
	oled_print_letter('#',0x01,0x00,0x08);
	pos.current_page = 0x01;

}
void joystick_navigate_vertical(){
	struct Joystick global_joystick = read_joystick_position(channel1,channel2);
	int y_pos = global_joystick.y_pos;
	if(y_pos < -90 && pos.current_page!=0x07){
		move = !move;
		pos.prev_page = pos.current_page;
		pos.current_page += 0x01;
		oled_print_letter(' ',pos.prev_page,0x00,0x08);
		oled_print_letter('#',pos.current_page,0x00,0x08);
	}
	
	
}