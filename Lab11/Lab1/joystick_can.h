/*
 * joystick_can.h
 *
 * Created: 23.10.2017 14:53:26
 *  Author: oystmol
 */ 
struct CAN_message joy_message_init();
void joystick_get_pos();
void received_joy_pos();
void send_joy_pos();