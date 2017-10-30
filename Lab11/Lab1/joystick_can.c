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

struct CAN_message joy_message_init(){
	struct CAN_message joy_pos;
	joy_pos.id = 3;
	joy_pos.length = 2; 
	return joy_pos;
}

void send_joy_pos(struct CAN_message joy_pos){
	joy_pos.data[0] = read_joystick_position(channel1, channel2).x_pos;
	joy_pos.data[1] = read_joystick_position(channel1, channel2).y_pos;
	CAN_transmit(joy_pos);
}

void received_joy_pos(){
	struct CAN_message received_pos;
	received_pos = CAN_receive();
	uint8_t x_pos = received_pos.data[0];
	uint8_t y_pos = received_pos.data[1];
	//printf("X POS: %x, Y POS: %x \n", x_pos,y_pos);
}