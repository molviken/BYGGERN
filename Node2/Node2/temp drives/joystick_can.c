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

struct Joystick get_joy_pos(){
	struct Joystick temp;
	temp = read_joystick_position(channel1,channel2);
	return temp;
}

void send_joy_pos(){
	struct Joystick pos = get_joy_pos();
	struct CAN_message new_message;
	new_message.id = 3;
	new_message.length = 2;
	new_message.data[0] = pos.x_pos;
	new_message.data[1] = pos.y_pos;
}

void received_joy_pos(){
	struct CAN_message received_pos;
	received_pos = CAN_receive();
	uint8_t x_pos = received_pos.data[0];
	uint8_t y_pos = received_pos.data[1];
}