/*
 * Node2.c
 *
 * Created: 23.10.2017 08:32:38
 *  Author: oystmol
 */ 
#define __Atmega2560__
#define F_CPU 16000000UL
#include <avr/interrupt.h>
#include "uart.h"
#include "SPI.h"
#include "MCPkontroll.h"
#include "CAN_bus.h"
#include "adc.h"
#include "fonts.h"
#include "joystick_can.h"
#include "joystick.h"
#include "MCP2515.h"
#include <avr/io.h>
#include "adc_node2.h"
#include "ir_detector.h"
#include "dac.h"
#include "motor.h"
#include <util/delay.h>
#include "sonoid.h"
#include "pi.h"
int main(void)
{

	USART_Init(103);
	adc_node2_init();
	CAN_init();
	pwm_setup();
	adc_node2_init();
	motor_init();
	TWI_Master_Initialise();
	motor_cal();
	PItimer_setup();
	CAN_timer_setup();
	printf("Init er good... \n");
	sei();//Enable Global interrupts

	uint16_t threshold = ir_threshold(0xa);
	int tempScore = 0;
	struct Score game;
	game.score = 0;
	game.flag = 1;
	struct CAN_message copy_message;
	struct Sonoid shooter;	
	
	struct CAN_message test_copy;
	while(1) {
		
		if(TIFR5 & (1 << OCF5B)){ // if counter has reached OCR5B
			copy_message = CAN_receive();
			// Clear interrupt and reset counter
			TCNT5 = 0;
			TIFR5 |= (1 << OCF5B);
		}
		//
		//test_program();
		shooter.fire = copy_message.data[4];
		if (copy_message.id != 0xff){
			//printf("Fire: %i \n",shooter.fire);
			PWM_control(copy_message.data[0]);
			shooter = sonoid_fire(shooter);
		}
		
		// Checking if the counter has counted the integral period
		if(TIFR3 & (1 << OCF3B)){ // if counter has reached OCR3B
			PI_regulator(copy_message.data[3]);
			// Clear interrupt and reset counter
			TCNT3 = 0;
			TIFR3 |= (1 << OCF3B);
		}
		_delay_ms(100);
		//int16_t y = motor_read()/(0x21);
		//uint8_t r = copy_message.data[3];
		//uint8_t x = copy_message.data[0];
		//
		//printf("	y: %d,	r: %d,	x: %d \n", y, r, x); 
		//tempScore = game.score;
		//game = ir_score_update(threshold, game);
		//if(tempScore != game.score){
			//printf("Dine poeng: %i \n", game.score);
		//printf("Running..\n");
	}
}
