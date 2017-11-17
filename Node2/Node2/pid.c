/*
 * pid.c
 *
 * Created: 16.11.2017 20:49:39
 *  Author: oystmol
 */
#define Kp 1
#define Ki 0.1 
#define T 0.01
#include "pid.h"
#include "motor.h"
#include "CAN_bus.h"
struct PI_reg reg;
int8_t speed;

void timer_setup(){
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

uint8_t PI_regulator(){
	reg.y = motor_read()/(0x21);
	reg.r = CAN_receive().data[3];
	reg.e = reg.r-reg.y;
	
	if (reg.e<0){reg.e = -reg.e;}
	static uint8_t integral;
	integral  = integral + reg.e;
	reg.u = Kp*reg.e+T*Ki*integral;
	
	if(reg.u > 0){
		speed = reg.u;
		if (speed < 0x00)
		{speed = -speed;}
		}
	printf("y: %d	  r: %d	   speed: %d	u: %d	e: %d \n", reg.y, reg.r,speed, reg.u, reg.e);
	if ( reg.e < 0x0a){
		dac_write(0x00);
	}
	else if(reg.y > reg.r){
		printf("Going left\n");
		Go_Left;
		dac_write(speed);
	}
	else{
		printf("Going right \n");
		Go_Right;
		dac_write(speed);
	}
}


//ISR(TIMER3_OVF_vect){
	//PI_regulator();
//}