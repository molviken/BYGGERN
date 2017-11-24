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

#include <util/delay.h>
#include "uart.h"
#include "CAN_bus.h"

#include "dac.h"
#include "motor.h"
#include "sonoid.h"
#include "PID.h"
#include "game_options.h"

int main(void){
	sei();//Enable Global interrupts
	USART_Init(103);
	adc_node2_init();
	CAN_init();
	pwm_setup();
	motor_init();
	TWI_Master_Initialise();
	PID_timer_init();
	CAN_timer_init();

	printf("Init er good... \n");
	

	while (1){
		choose_game_options();
	}
	return 0;
}
