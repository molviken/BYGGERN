/*
 * adc.h
 *
 * Created: 18.09.2017 11:31:49
 *  Author: oystmol
 */ 
#define channel1 (0x4)
#define channel2 (0x5)
#define channel3 (0x6)
#define channel4 (0x7)
#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/sleep.h>
#include <stdlib.h>
#include <stdio.h>
//#include <time.h>


void adc_init();
uint8_t adc_read(uint8_t channel);
struct Joystick read_joystick_position(uint8_t channel_one, uint8_t channel_two);
struct Slider read_slider_position(uint8_t channel_one, uint8_t channel_two);