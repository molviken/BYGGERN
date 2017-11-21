/*
 * pid.c
 *
 * Created: 16.11.2017 20:49:39
 *  Author: oystmol
 */
#define Kp 0.7
#define Ki 0.15
#define Kd 0.06
#define T 0.01
#include <avr/io.h>
#include <stdlib.h>
#include "bit_operations.h"
#include "PID.h"
#include "motor.h"



struct PI_reg reg;
int8_t speed;
void PID_timer_init(){
	// setting up timer 3
	set_bit(TCCR3B, CS31);	//Prescalar 8
	set_bit(TCCR3B, WGM32); //Set CTC mode, TOP at OCR3A
	
	OCR3B = 20000;
}

void PID_regulator(uint8_t position, int16_t maxvalue){
	int16_t den = maxvalue/0x00ff;
	//reg.y = motor_read()/den;
	reg.y = motor_read()/(den);
	reg.r = position; //Slider position
	reg.e = reg.r-reg.y;
	
	static int integral = 0;
	integral  = integral + reg.e;
	
	static int prev_pos = 0;
	static int derivative = 0;
	derivative = reg.y - prev_pos;

	reg.u = Kp*reg.e + Ki*integral + Kd*derivative;
	
	speed = abs(reg.u);
	
	prev_pos = reg.y;
	
	if(abs(reg.e) < 0x07){
		speed = 0;
		reg.e = 0;
		integral = 0;
		}
	else if(reg.y < reg.r){
		//printf("Going left\n");
		Go_Right;
	}
	else{
		//printf("Going right \n");
		Go_Left;
	}
	//printf("e: %d	int: %d	speed: %d	r: %d	y: %d \n", reg.e, integral, speed, reg.r, reg.y);
	dac_write(speed);
}

