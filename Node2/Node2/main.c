/*
 * Node2.c
 *
 * Created: 23.10.2017 08:32:38
 *  Author: oystmol
 */ 
#define __Atmega2560__

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
int main(void)
{
	int tempScore = 0;
	struct Score game;
	game.score = 0;
	game.flag = 1;
	USART_Init(103);
	adc_node2_init();
	DDRB = 0b00000000;
	CAN_init();
	pwm_setup();
	uint16_t threshold = ir_threshold(0xa);
	adc_node2_init();
	struct CAN_message copy_message;
	while(1) {
		//printf("0 eller 1: %i			threshold: %x \n",ir_detection(0x4, threshold), threshold);
		copy_message = CAN_receive();
		if (copy_message.id != 0xff){
			PWM_control(copy_message.data[0]);
			//printf("COUNTER: %i \n", OCR1B);
			//printf("X: %i	Y: %i	 \n",copy_message.data[0], copy_message.data[1]);
		}
		tempScore = game.score;
		
		game = ir_score_update(threshold, game);
		if(tempScore != game.score){
			printf("Dine poeng: %i \n", game.score);
		}
		_delay_ms(100);
	}
}