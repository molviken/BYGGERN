/*
 * Node2.c
 *
 * Created: 23.10.2017 08:32:38
 *  Author: oystmol
 */ 
#define __Atmega2560__
#define F_CPU 16000000UL
#include <avr/interrupt.h>
#include <stdbool.h>
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
	sei();//Enable Global interrupts
	USART_Init(103);
	adc_node2_init();
	CAN_init();
	pwm_setup();
	adc_node2_init();
	motor_init();
	TWI_Master_Initialise();
	//motor_cal();
	int16_t maxvalue = motor_set_enc_maxval();
	printf("max value: %d", maxvalue);
	PItimer_setup();
	CAN_timer_setup();
	printf("Init er good... \n");
	int channel_change = 0;
	uint16_t threshold = ir_threshold(0xa);
	int tempScore = 0;
	int temp2Score = 0;
	struct Score game1;
	struct Score game2;
	game1.score = 0;
	game1.flag = 1;
	game2.score = 0;
	game2.flag = 1;
	struct CAN_message copy_message;
	struct Sonoid shooter;	
	
	struct CAN_message test_copy;
	while(1) {
		//printf("Yes/no:  %i\n", ir_detection(0xa,threshold));
		
		if(TIFR5 & (1 << OCF5B)){ // if counter has reached OCR5B
			copy_message = CAN_receive();
			tempScore = game1.score;
			temp2Score = game2.score;
			if(channel_change){
				game1 = ir_score_update(threshold, game1);
				if(tempScore != game1.score){
					//printf("Dine poeng: %i \n", game1.score);
				}
			}
			if(!channel_change){
				game2 = ir_score_update(threshold, game2);
				if(temp2Score != game2.score){
					//printf("Dine poeng: %i \n", game2.score);
				}
			}
			adc_node2_switch(channel_change);
			channel_change = !channel_change;
			// Clear interrupt and reset counter
			TCNT5 = 0;
			TIFR5 |= (1 << OCF5B);
		}
		
		shooter.fire = copy_message.data[4];
		if (copy_message.id != 0xff){
			//printf("Fire: %i \n",shooter.fire);
			PWM_control(copy_message.data[0]);	//Slider steering
			//shooter = sonoid_fire(shooter);
			//joystick_drive(copy_message.data[0],copy_message.data[3]); //Joy steer
		}
		
		// Checking if the counter has counted the integral period
		if(TIFR3 & (1 << OCF3B)){ // if counter has reached OCR3B
			//PI_regulator(copy_message.data[3], maxvalue);
			// Clear interrupt and reset counter
			TCNT3 = 0;					// Counter
			TIFR3 |= (1 << OCF3B);		// bit in interrupt register changes on match between top and counter
		}
		_delay_ms(100);
		

		
		printf("GS1: %i		GS2: %i\n", game1.score, game2.score);
		
	}
	return 0;
}
