/*
 * joystick.h
 *
 * Created: 25.09.2017 15:20:55
 *  Author: oystmol
 */ 
#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/sleep.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

struct Menu_position {
	uint8_t current_page;
	uint8_t prev_page;
	bool move;
	bool pressed1;
	bool pressed2;
};
struct Slider{
	int slider1;
	int slider2;
};
struct Joystick{
	int x_pos;
	int y_pos;
};
struct Joystick read_joystick_position(uint8_t channel_one, uint8_t channel_two);
struct Slider read_slider_position(uint8_t channel_one, uint8_t channel_two);
uint8_t joystick_pressed();
uint8_t slider_button();
int sonoid_button();