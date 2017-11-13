/*
 * joystick_can.c
 *
 * Created: 23.10.2017 14:53:11
 *  Author: oystmol
 */ 
#include "joystick_can.h"
#include "joystick.h"
#include "adc.h"
#include "CAN_bus.h"


void send_joy_pos(struct CAN_message joy_pos){
	joy_pos.data[0] = read_joystick_position(channel1, channel2).x_pos;
	joy_pos.data[1] = read_joystick_position(channel1, channel2).y_pos;
	CAN_transmit(joy_pos);
}

void send_slider_pos(){
	struct Slider pos = get_slider_pos();
	struct CAN_message new_message;
	printf("Sli left = %x , Sli right = %x \n", pos.slider1, pos.slider2);
	new_message.id = 4;
	new_message.length = 2;
	new_message.data[0] = pos.slider1;
	new_message.data[1] = pos.slider2;
}

