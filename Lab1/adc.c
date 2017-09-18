/*
 * adc.c
 *
 * Created: 18.09.2017 11:31:37
 *  Author: oystmol
 */ 
#define set_bit( reg, bit ) (reg |= (1 << bit))
#define clear_bit( reg, bit ) (reg &= ~(1 << bit))
#define test_bit( reg, bit ) (reg & (1 << bit))
#define loop_until_bit_is_set( reg, bit ) while( !test_bit( reg, bit ) )
#define loop_until_bit_is_clear( reg, bit ) while( test_bit( reg, bit ) )
#include "adc.h"
#include <string.h>
//#include "uart.h"

void adc_init(void){
	set_bit(MCUCR,SRE);
	set_bit(SFIOR,XMM2);
	clear_bit(DDRE,DDE0);
}

uint8_t adc_read(uint8_t channel){
	
	volatile char* adc_adr = (char *) 0x1400;
	adc_adr[0] = channel;
	//check inter, while inter == high
	loop_until_bit_is_clear(PINE,PE0);
	uint8_t retreived_value = adc_adr[channel];
	return retreived_value;
	
}

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