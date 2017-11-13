/*
 * motor.c
 *
 * Created: 13.11.2017 10:11:17
 *  Author: oystmol
 */ 

#define set_bit( reg, bit ) (reg |= (1 << bit))
#define clear_bit( reg, bit ) (reg &= ~(1 << bit))
#include "motor.h"
#include "TWI_Master.h"
#include "dac.h"
#include <stdlib.h>
#include <avr/interrupt.h>
#include <avr/io.h>
#include <util/delay.h>

static int16_t encoder_maxvalue;
static int16_t reference_value = 0;

void motor_init(){
	//set_bit(TWCR, TWEN);
	DDRK = 0x00;		// Set PortK (ADCH) as input
	DDRH = 0xFF;		// Set PortH (MJ1) as output
	DDRD = 0x00;		// Set PortD (MJ2) as input
	set_bit(DDRD, PD0); //SCL port
	set_bit(DDRD, PD1); //SDA port
	set_bit(PORTH, EN); // Enable encoder
	set_bit(PORTH, RST); // Toggle !RST to set internal counter = 0
	set_bit(PORTH, RST);   // Toggle on to start counting
	//_delay_ms(200);
	//motor_set_ref(0);
	//sumError = 0;
	clear_bit(PORTH,PH1);

}
void motor_change_dir(int direction){
	if (direction == 1){
		set_bit(PORTH,DIR);
	}
	else if(direction == 0){
		clear_bit(PORTH, DIR);
	}
	else{
		dac_write(0x00);
	}
}

int16_t motor_read(){
	int16_t bits = 0x00;
	clear_bit(PORTH, OE); // Toggle !OE low to enable output of encoder
	clear_bit(PORTH, SEL);  // Clears Sel
	_delay_us(100);
	bits = (PINK << 8);
	set_bit(PORTH, SEL); // Sets Sel
	_delay_us(100);
	bits |= PINK;
	
	//encoder_reset();
	set_bit(PORTH, RST); 
	set_bit(PORTH, OE); // sets !OE high to disable output of encoder
	if (-bits < 0x0000){
		bits = -0x0000;
	}
	else if(-bits > 0x2134){
		bits = -0x2134;
	}
	return -bits;
}

void encoder_reset(){
	clear_bit(PORTH, RST); // Toggle !RST to set internal counter = 0
	_delay_us(20);

}

//void motor_set_ref(uint8_t value){
	//reference_value = value;
//}
//int get_maxvalue(){
	//return encoder_maxvalue;
//}
//
//void control_set_joystick_flag(int flag){
	//joystick_flag = flag;
//}

void test_program(){

	if(motor_read()>8000){

		Go_Left;
		dac_write(0x55);
		printf("Going left%d \n", motor_read());
	}
	else if (motor_read() <1000){

		Go_Right;
		dac_write(0x55);
		printf("Going right: %d \n", motor_read());
	}
}

void motor_cal(){
	Go_Left;
	dac_write(0x55);
	_delay_ms(2000);
	motor_change_dir(-1);
	encoder_reset();
}

struct PI_reg motor_reg_init(){
	struct PI_reg regulator;
	regulator.Kp = -0x1p-1;
	regulator.Ki = 1;
	regulator.T = 1;
	return regulator;
}

struct PI_reg motor_reg_calc(uint8_t slider_right){
	// Regulator parameters
	struct PI_reg reg;
	reg.Kp = 1;
	reg.r = (uint16_t)slider_right*0x0021;
	reg.y = motor_read();
	reg.e = reg.r-reg.y;
	reg.u = reg.Kp*reg.e;
	//printf("r: %d		y: %d	e: %d		u: %d		kp: %d \n",reg.r,reg.y,reg.e,reg.u, reg.Kp);
	return reg;	
}
int8_t motor_speed_control(int8_t speed){
	if (speed > 0xff){speed = 0xff;}
	else if (speed < 0x00){speed = -speed; Go_Left;}
	return speed;
}
void motor_position_control(uint8_t slider_right, struct PI_reg reg){

	reg = motor_reg_calc(slider_right);

	int8_t speed = (int8_t)(reg.u*(0x1.33p-2));
	speed = motor_speed_control(speed);
	printf("y: %d	  r: %d	   speed: %d	u: %d	e: %d	 kp: %d \n", reg.y, reg.r,speed, reg.u, reg.e, reg.Kp);
	if (abs(reg.u) < 30){
		motor_change_dir(-1);
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