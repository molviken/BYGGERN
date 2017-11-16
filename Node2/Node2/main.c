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
int main(void)
{

	USART_Init(103);
	adc_node2_init();
	CAN_init();
	pwm_setup();
	adc_node2_init();
	motor_init();
	TWI_Master_Initialise();
	sei();
	
	//DDRB = 0b00000000;
	
	uint16_t threshold = ir_threshold(0xa);
	int tempScore = 0;
	struct Score game;
	game.score = 0;
	game.flag = 1;
	struct CAN_message copy_message;
	//while(1){
		//clear_bit(PORTH,PH1);
		//dac_write(0x55);
		////printf("moving left way:    %x \n", motor_read());
				//_delay_ms(2000);
				//printf("%d\n",motor_read());
		//set_bit(PORTH,PH1);
		//dac_write(0x55);
		////printf("moving right way:   %x \n", motor_read());
				//_delay_ms(2000);
				//printf("%d\n",motor_read());
	//}

	printf("Init er good... \n");
	motor_cal();
	struct PI_reg reg = motor_reg_init();
	
	while(1) {
		//printf("kp: %d \n", reg.Kp);
		
		copy_message = CAN_receive();
		if (copy_message.id != 0xff){
			PWM_control(copy_message.data[0]);
			//printf("sonoid: %d \n", copy_message.data[4]);
			motor_position_control(copy_message.data[3],reg);
		}
		//printf("Motor enc: %d \n", motor_read());

		tempScore = game.score;
		sonoid_fire(copy_message.data[4]);
		game = ir_score_update(threshold, game);
		if(tempScore != game.score){
			//printf("Dine poeng: %i \n", game.score);
		}
		//printf("Running..\n");
		_delay_ms(100);
		
	}
}
