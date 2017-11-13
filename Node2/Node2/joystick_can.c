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

void received_joy_pos(){
	struct CAN_message received_pos;
	received_pos = CAN_receive();
	uint8_t x_pos = received_pos.data[0];
	uint8_t y_pos = received_pos.data[1];
	//printf("X POS: %x, Y POS: %x \n", x_pos,y_pos);
}
void received_slider_pos(){
	struct CAN_message received_pos;
	received_pos = CAN_receive();
	uint8_t slider_left = received_pos.data[0];
	uint8_t slider_rigth = received_pos.data[1];
	//printf("Sli left: %x, Sli right: %x \n", slider_left, slider_right);
}