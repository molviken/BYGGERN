/*
 * pid.c
 *
 * Created: 16.11.2017 20:49:39
 *  Author: oystmol
 */
#define Kp 0.9
#define Ki 0.15
#define Kd 0.06
#define T 0.01
#include "pwm.h"
#include "pi.h"
#include "motor.h"
#include "CAN_bus.h"
#include "joystick.h"

struct PI_reg reg;
int8_t speed;
void PItimer_setup(){
	// setting up timer 3
	set_bit(TCCR3B, CS31);	//Prescalar 8
	set_bit(TCCR3B, WGM32); //Set CTC mode, TOP at OCR3A
	
	OCR3B = 20000;
}


void pid_init(){
	//motor_cal();

	set_bit(DDRB, PB6);
	set_bit(TCCR1A, COM1B1);
	// Setter prescaler til 8
	set_bit(TCCR1B, CS11);
	// Enabler fast pwm mode
	set_bit(TCCR1A, WGM11);
	set_bit(TCCR1B, WGM12);
	set_bit(TCCR1B, WGM13);
	// Definerer PWM perioden på 20 ms
	ICR1 = 39999;
	// Regulerer på OCR1B = 1.5ms (1.5/20)*39999
	OCR1B = 3000;
	
	//Enable timer interrupt
	set_bit(TIMSK3, TOIE3);
	//sei();
	
	//_delay_ms(200);
}

void PI_regulator(uint8_t position, int16_t maxvalue){
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
	
	if(abs(reg.e) < 0x07 ){
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
	printf("e: %d	int: %d	speed: %d	r: %d	y: %d \n", reg.e, integral, speed, reg.r, reg.y);
	dac_write(speed);
}

void joystick_drive(uint8_t x_pos, uint8_t servo){
	uint8_t speed;
	PWM_control(servo);
	if(x_pos>137){
		speed = (x_pos- 137)*0x1.6p-1;
		Go_Right;

	}
	else if(x_pos<127){
		speed = (127 - x_pos)*0x1.6p-1;
		Go_Left;

	}
	else{
		speed = 0x00;
	}
		printf("X: %d		speed: %d\n",x_pos,speed);
	dac_write(speed);
	
}